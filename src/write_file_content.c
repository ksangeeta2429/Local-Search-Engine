/*********************************************************************
*
*    File name: write_file_content.c
*
*    Description: write file contents to the socket
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

/************************************************************************
*    Func name: write_file_content
*
*    Description: write the file contents to the socket
*
*    Return value: SUCCESS or FAILURE
*************************************************************************/
int write_file_content
                       (
                        int connfd, /* connection descriptor */
                        char *buffer, /* buffer containing the file content */
                        int file_size /* size of the file to be sent */
                       )
{
    A_TRACE(DETAILED_TRACE, ("Entering write_file_content func\n"));

    int bytes_written; /* no of bytes written */

    /* write the file content into socket */
    bytes_written = write (connfd, buffer, (file_size + 1)); 
    if (0 >= bytes_written)
    {
        printf ("Error in writing the socket\n");
        exit (FAILURE);
    }

    A_TRACE(DETAILED_TRACE, ("Leaving write_file_content func\n"));
    return SUCCESS;
}
