/*********************************************************************
*
*    File name: client.c
*
*    Description: start of client program
*
*    Name    Date        Reference    Reason
*    Grp4    3-May-2014  TH6_grp4     Initial Creation
*
*    Copyright 2014, Aricent Technologies (Holdings) Limited
**********************************************************************/

/**********************************************************************
*                              Header files
***********************************************************************/
#include"client_header.h"

/***********************************************************************
*                               Global variables
************************************************************************/
int g_trace_level = NO_TRACE; /* global trace level */
int g_error_level = MINOR_ERROR; /* global error level */

/************************************************************************
*    Func name: main
*
*    Description: start of main client func
*
*    Return value: SUCCESS or FAILURE
*************************************************************************/
int main
        (
         int argc,    /* no of command line arguments */
         char *argv[] /* array of pointers to hold the arguments */
        )
{
    /* error message if IP address not mentioned */
    if (NULL == argv[1])
    {
        A_ERROR(MAJOR_ERROR, NO_ADDRESS);
        exit (FAILURE);
    }

    /* error message if port no not mentioned */
    if (NULL == argv[2])
    {
        A_ERROR(MAJOR_ERROR, NO_PORT);
        exit (FAILURE);
    }

    /* if 4th argument also given set global error level */
    if (NULL != argv[3])
    {
        g_error_level = atoi (argv[3]);
    }
    else
    {
        g_error_level = NO_ERROR;
    }
 
    /* if 5th argument given set global trace level */
    if (NULL != argv[4])
    {
        g_trace_level = atoi (argv[4]);
    }
    
    A_TRACE(BREIF_TRACE, ("Start of client main function\n"));

    int sd;  /* socket descriptor */
    int connect_ret;  /* to hold the connect return */
    int choice;  /* choice of user whether search by path or pattern */
    int scanned_variables; /* return value of scanf */
    char str[BUF_SIZE];  /* variable to store the user choice */
    char character; /* to hold character entered by client during choice */
    struct sockaddr_in clientaddress;  /* object for holding client attributes*/
    
    A_TRACE(DETAILED_TRACE, ("Creating socket for the client\n"));

    /* creating the socket descriptor */
    sd = socket (AF_INET, SOCK_STREAM, 0);
    if (0 > sd)
    {
        A_ERROR(MAJOR_ERROR, SOCKET_ERROR);
        exit (FAILURE);
    }

    /* populating the object with IP address and port# */
    memset (&clientaddress, 0 , sizeof (clientaddress));
    clientaddress.sin_family = AF_INET;
    clientaddress.sin_port = htons (atoi(argv[2]));
    clientaddress.sin_addr.s_addr = inet_addr (argv[1]);

    /* connecting to the server */
    connect_ret = connect (sd, (struct sockaddr *)&clientaddress, sizeof (clientaddress));
    if (0 != connect_ret)
    {
        A_ERROR(MAJOR_ERROR, CONNECT_ERROR);
        exit(FAILURE);
    }

    printf ("\nConnection with %s successful\n", argv[1]);  /* prints the server address */

    while (1)
    {
        /* ask user choice for search by path or pattern */
        printf ("\nHow would you like to search\n\n"
                "\tType 1 for search by path\n"
                "\tType 2 for search by pattern\n"
                "\tYour choice: "
               );

        scanned_variables = scanf ("%d%c", &choice, &character);
        if (2 != scanned_variables) /* if any character is scanned */
        {
            printf ("\n\tPlease enter only an integer\n");
            while ('\n' != getchar()); /* clear the internal buffer */
            continue; /* ask for input again */
        }
        else /* else if an integer is scanned */
        {
            if ('\n' == character)
            {
                break;
            }
            else /* if client entered integer followed by any character. Or client entered floating no */
            {
                printf ("\n\tInvalid input\n");
                while('\n' != getchar()); /* clear the internal buffer */
                continue; /* ask for input again */
            }
        }
    }

    /* store the client choice as a string */
    sprintf (str, "%d", choice);

    /* write it to the socket */
    write (sd, str, BUF_SIZE);

    if (1 == choice) /* 1 corresponds to search by path */
    {
        write_path(sd);
        read_file_content(sd);
        exit (SUCCESS);
    }
    else if (2 == choice) /* 2 corresponds to search by pattern */
    {
        /* call the read write function for client */
        client_write(sd);
        /* read the paths received from server */
        client_read(sd);
    }
    else
    {
        printf ("INVALID CHOICE. TRY AGAIN\n");
    }

    A_TRACE(BREIF_TRACE, ("Exiting client main function\n"));
    exit (SUCCESS);
}
