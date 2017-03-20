/*********************************************************************
*
*    File name: server_index_read.c
*
*    Description: read socket for index no
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
*    Func name: index_read
*
*    Description: function to read the index no of the path required by
*                 client
*
*    Return value: SUCCESS
*************************************************************************/
int index_read
               (
                int connfd /* connection descriptor to read the data */
               )
{
    int bytes_read; /* bytes read from the socket */
    char str[SIZE]; /* variable to store the string received */

    /* clearing the memory */
    memset (str, '\0', sizeof (str)); 
    printf ("\nWaiting for the index no ...\n");
    /* read the socket */
    while ((bytes_read = read (connfd, str, SIZE)) > 0)
    {
        if (NULL != str)
        {
            break;
        }
    }
    
    printf ("\nFile index no required = %s\n", str);

    /* open the file whose index no is received */
    file_open(connfd, str);

    return SUCCESS;
}
