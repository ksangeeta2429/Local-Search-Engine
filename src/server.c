/*********************************************************************
*
*    File name: server.c
*
*    Description: start of server program
*
*    Name    Date       Reference    Reason
*    Grp4    3-May-2014 TH6_grp4     Initial Creation
*
*    Copyright 2014, Aricent Technologies (Holdings) Limited
**********************************************************************/

/**********************************************************************
*                            Header files
***********************************************************************/
#include"server_header.h"

/***********************************************************************
*                           Global variables
************************************************************************/
int g_trace_level = NO_TRACE; /* global trace level */
int g_error_level = MINOR_ERROR; /* global error level */
int sd; /* glabal socket descriptor */

/************************************************************************
*    Func name: signal_handler
*
*    Description: signal handler for CTRL C keyboard interrupt
*
*    Return value: SUCCESS
*************************************************************************/
void signal_handler
                   (
                    int signo  /* arg to capture the interrupt */
                   )
{
    printf ("\n\tCtrl + C Captured ...\n");
    printf ("\n\tClosing the connections ...\n");
    close (sd);  /* close the socket */
    printf ("\n\tFreeing all memory ...\n");
    free_all();  /* free the linked list */
    printf ("\n\tDone!!!\n");
    exit (SUCCESS);
}

/************************************************************************
*    Func name: main
*
*    Description: start of the main server func
*
*    Return value: calls signal handler and exits
*************************************************************************/
int main
        (
         int argc,    /* no of and line rguments */
         char *argv[] /* array of pointers to hold the arguments */
        )
{
    /* if 2nd argument is passed set the global error level */
    if (NULL != argv[1])
    {
        g_error_level = atoi (argv[1]);
    }

    /* if 3rd argument is passed set the global trace level */
    if (NULL != argv[2])
    {
        g_trace_level = atoi (argv[2]);
    }

    A_TRACE(BREIF_TRACE, ("Entering the main function\n"));
    A_TRACE(BREIF_TRACE, ("Installing the signal for SIGINT\n"));
 
    /* signal SIGINT installation */
    signal (SIGINT, signal_handler);

    int connfd;  /* connection descriptor */
    int bind_ret,  /* return value of bind */
        listen_ret;  /* return value of listen */
    char addr_buf[BUFSIZE];  /* buffer to store address of client */
    socklen_t client_len;  /* length of client object*/
    char buf[SIZE];  /* buffer to store data received from client */
    char str[BUF_SIZE];

    struct sockaddr_in 
        serveraddress, clientaddress; /* objects for handling server and client attributes */

    /* populating the server object with IP address and port# */
    memset (&serveraddress, 0, sizeof (serveraddress));
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons (MYPORT);
    serveraddress.sin_addr.s_addr = htonl (INADDR_ANY);

    A_TRACE(DETAILED_TRACE, ("Creating the socket for server\n"));

    /* creating the socket descriptor */
    sd = socket (AF_INET, SOCK_STREAM, 0);
    if (0 > sd)
    {
        A_ERROR(MAJOR_ERROR, SOCKET_ERROR);
        exit (FAILURE);
    }

    /* assigning the socket with server attributes using bind */
    bind_ret = bind (sd, (struct sockaddr *)&serveraddress, sizeof (serveraddress));
    if (0 != bind_ret)
    {
        A_ERROR(MINOR_ERROR, BIND_ERROR);
        exit (FAILURE);
    }

    /* listen to any client request to connect */
    listen_ret = listen (sd, QSIZE);
    if (0 != listen_ret)
    {
        A_ERROR(MINOR_ERROR, LISTEN_ERROR);
        exit (FAILURE);
    }

    /* infinite loop */
    for ( ; ; )
    {
        A_TRACE(DETAILED_TRACE, ("Inside infinite for loop\n"));
        printf ("\nWaiting for a client...\n");
        client_len = sizeof (clientaddress);
        int flag = 0;  /* condition check whether to call index_read func or not */

        /* connect to the requesting client */
        connfd = accept (sd, (struct sockaddr *)&clientaddress, &client_len);
        if (0 > connfd)
        {
            A_ERROR(MINOR_ERROR, CONNECTION_ERROR);
            continue;
        }
        
        printf ("Connection from %s successful\n", 
                inet_ntop (AF_INET, &clientaddress.sin_addr, addr_buf, sizeof (addr_buf)));

        /* read the choice entered by client into str */
        read (connfd, str, BUF_SIZE);

        if (0 == strcmp (str, "1")) /* 1 corresponds to search by path */
        {
            open_file_path(connfd);
        }

        else if (0 == strcmp (str, "2")) /* 2 corresponds to search by pattern */
        {
            memset (buf, '\0', sizeof (buf)); /* clear the buffer */
            read_socket(connfd, buf); /* read the socket to get the pattern entered by client */
            A_TRACE(DETAILED_TRACE, ("Entering the function dir_path\n"));
            dir_path(ROOT_PATH, buf); /* search the entire dir structure to search the pattern */
            A_TRACE(DETAILED_TRACE, ("Exiting the function dir_path\n"));
            display_list(); /* display the entire list */

            if (NULL != head)
            {
                write_socket(connfd); /* write all searched paths to the socket */
            }
            else
            {
                printf ("\n\t------------Empty list-----------\n");
                printf ("\n\t----------No path found----------\n");
                flag = 1;
            }

            /* call this func to read the index value sent by client */
            if (0 == flag)
            {
                index_read(connfd);
            }

            close (connfd); /* close the connection */
            free_all(); /* free the linked list */
            A_TRACE(BREIF_TRACE, ("One client served\n"));
        }
    }
}
