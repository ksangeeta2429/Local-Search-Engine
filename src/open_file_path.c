/*********************************************************************
*
*    File name: open_file_path.c
*
*    Description: open the file when absolute path is given
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
*    Func name: open_file_path
*
*    Description: get the absolute path, open it and write the contents
*                 to socket
*
*    Return value: SUCCESS
*************************************************************************/
int open_file_path
                  (
                   int connfd /* connection descriptor */
                  )
{
    char path[SIZE], /* variable to store the path after reading */
         buf[SIZE]; /* variable to store an error message */
    int bytes_read, /* no of bytes read */
        fd,        /* file descriptor for file opened */
        file_size; /* size of the file required */
    struct stat sbuf; /* object of structure stat */

    printf ("\nWaiting for the path ...\n");

    /* read the path sent by client */
    while ((bytes_read = read (connfd, path, SIZE)) > 0)
    {
        /* break the loop when $ is encountered */
        if ('$' == path[bytes_read - 1])
        {
            break;
        }
    } /* end of while loop */

    path[bytes_read - 1] = '\0'; 

    printf ("\tPath received = %s\n\n", path);

    /* open the file */
    fd = open (path, O_RDONLY);
    if (0 > fd)
    {
        /* if no such path exists send error message */
        sprintf (buf, "%s", "\n\tPlease check the path.\n$");
        write (connfd, buf, SIZE);
        return FAILURE;
    }
    
    stat (path, &sbuf); /* stat the file if opened successfully */
    file_size = sbuf.st_size; /* store the size of the file */
        
    char buffer[file_size + 1]; /* variable to store the contents of file */
    memset (buffer, '\0', file_size + 1);

    read (fd, buffer, file_size + 1); /* read the contents of file */
    
    strcat (buffer, "$"); /* $ at last marks the end of data */

    write_file_content(connfd, buffer, file_size); /* write the contents of file to socket */
    
    return SUCCESS;
}
