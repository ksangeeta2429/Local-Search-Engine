/*********************************************************************
*
*    File name: client_index_write.c
*
*    Description: write index no into socket
*
*    Name    Date       Reference    Reason
*    Grp4    3-May-2014 TH6_grp4     Initial Creation
*
*    Copyright 2014, Aricent Technologies (Holdings) Limited
**********************************************************************/

/**********************************************************************
*                            Header files
***********************************************************************/
#include"client_header.h"

/************************************************************************
*    Func name: index_write
*
*    Description: required index no of file to be opened is written to socket
*
*    Return value: SUCCESS
*************************************************************************/
int index_write
                       (
                        int sd, /* socket descriptor */
                        int index_max /* max index value allowed */
                       )
{
    int index_no, /* index no entered by client */
        bytes = 0, /* variable to check no of bytes written */
        bytes_written, /* bytes written in one write */
        len; /* len of str */
    int scanned_variables; /* return value of scanf */
    char str[SIZE]; /* to store the index no */ 
    char character; /* to hold character entered by client during choice */

    while (1)
    {
        /* takes client's choice for index no */
        printf ("Enter the index no for file you want to open\n");
        scanned_variables = scanf ("%d%c", &index_no, &character);
        if (2 != scanned_variables) /* if client has entered anything except integer value */
        {
            printf ("\tPlease enter only integer values\n\n");
            while ('\n' != getchar()); /* clear the internal buffer for next input */
            continue; /* ask for input again */
        }
        else 
        {
            if ('\n' != character) /* if client entered only an integer */
            {
                printf ("\tInvalid choice\n\n"); 
                while ('\n' != getchar()); /* clear the internal buffer */
                continue; /* ask for input again */
            }
        }

        if ((0 < index_no) && (index_max >= index_no)) /* if index value lies between 1 and the max value */
        {
            break;
        }
        else /* if anything outside the range of indexes is entered */
        {
            printf ("\tInvalid index no\n\n");
            continue; /* ask for input again */
        }
    } /* end of while loop */

    memset (str, '\0', sizeof (str));
    sprintf (str, "%d", index_no);
    len = strlen (str); /* length of index as a string */

    while (bytes < len)
    {
        bytes_written = write (sd, (str + bytes), (len - bytes));
        bytes += bytes_written;
    } /* end of while loop */

    read_file_content(sd); /* call this function to read the contents of file whose index no is entered */

    return SUCCESS;
}
