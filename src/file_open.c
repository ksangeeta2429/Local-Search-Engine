/*********************************************************************
*
*    File name: file_open.c
*
*    Description: open the file requested
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
*    Func name: file_open
*
*    Description: retrieve the name of file from linked list and open it
*
*    Return value: SUCCESS or FAILURE
*************************************************************************/
int file_open
              (
               int connfd, /* connection descriptor */
               char *index /* index received from client */
              )
{
    A_TRACE(DETAILED_TRACE, ("Entering file_open\n"));

    NODE *ptr; /* ptr to traverse the list */
    char my_index[SIZE] = {'\0'}; /* index nos already saved in linked list */
    int fd, /* file descriptor for file to be opened */
        file_size, /* size of the file */
        bytes_read; /* no of bytes read */
    struct stat stat_buf; /* varaible to stat the file */
    int close_ret; /* variable to store return value of close */

    ptr = head; /* ptr pointing to start of list */
    sprintf (my_index, "%d", ptr->index);    

    /* keep forwarding ptr till index in LL matches with index no received */
    while (0 != strcmp(index, my_index))
    {
        ptr = ptr->next; /* ptr pointing to next node */
        sprintf (my_index, "%d", ptr->index);
    } /* end of while loop */

    printf ("\n\tPath of the file required = %s\n", ptr->path_name);

    /* open the file in read only mode */
    fd = open (ptr->path_name, O_RDONLY);
    if (0 > fd)
    {
        A_ERROR(MINOR_ERROR, FILE_OPEN_FAIL);
        exit (FAILURE);
    }

    /* stat the file name to get its size */
    fstat (fd, &stat_buf);
    file_size = stat_buf.st_size;

    char buffer[file_size + 1]; /* variable to store the contents of file */
    memset (buffer, '\0', file_size + 1);

    /* read the contents of file */
    while ((bytes_read = read (fd, buffer, file_size + 1)) > 0);

    strcat (buffer, "$"); /* $ at last marks the end of data */

    /* write the content of the file into socket */
    write_file_content(connfd, buffer, file_size);

    /* close the file */
    close_ret = close (fd);
    if (0 != close_ret)
    {
        A_ERROR(MINOR_ERROR, FILE_CLOSE_FAIL);
    }

    A_TRACE(DETAILED_TRACE, ("Leaving the file_open func\n"));

    return SUCCESS;
}
