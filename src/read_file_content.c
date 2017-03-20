/*********************************************************************
*
*    File name: read_file_content.c
*
*    Description: read the content sent by server
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
*    Func name: read_file_content
*
*    Description: read the content of the file asked for
*
*    Return value: SUCCESS
*************************************************************************/
int read_file_content
                      (
                       int sd /* socket descriptor */
                      )
{
    A_TRACE(DETAILED_TRACE, ("Entering read_file_content func\n"));

    int bytes_read; /* bytes read from the socket */
    char buffer; /* buffer to read the data byte by byte */

    /* read the file content */
    while ((bytes_read = read (sd, &buffer, 1)) > 0)
    {
        /* while will terminate on reading the $ character */
        if ('$' == buffer)
        {
            break;
        }
 
        /* print the content byte by byte */
        printf ("%c", buffer); 
    }

    A_TRACE(DETAILED_TRACE, ("Leaving read_file_content func\n"));

    return SUCCESS;
}
