/*********************************************************************
*
*    File name: server_read_write.c
*
*    Description: perform read and write function through socket
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
*    Func name: read_socket
*
*    Description: read the pattern sent by client
*
*    Return value: SUCCESS
*************************************************************************/
int read_socket
                (
                 int connfd, /* the connection descriptor from which to read */ 
                 char *buf /* buffer into which received pattern will be stored */  
                )
{
    A_TRACE(DETAILED_TRACE, ("Entering read_socket function\n"));

    int bytes_read; /* no of bytes read from socket */
    char local_buffer[BUF_SIZE]; /* buffer used in this function to read */

    memset (local_buffer, '\0', sizeof (local_buffer));
    printf ("\nWaiting for a pattern ...\n");
    /* read the pattern from client */
    while ((bytes_read = read (connfd, local_buffer, 1)) > 0)
    {
        if (0 == strcmp (local_buffer, "$"))
        {
            break;
        }
        /* concatenate each byte read through socket in the main buffer */
        strcat (buf, local_buffer);
    } /* end of while loop */
    
    /* Display appropriate messages */
    printf ("\n\tPattern to be searched: %s\n\n", buf);

    A_TRACE(DETAILED_TRACE, ("Exiting the read_socket function\n"));

    return SUCCESS;
}

/************************************************************************
*    Func name: write_socket
*
*    Description: write the merged directory paths into socket
*
*    Return value: SUCCESS or FAILURE
*************************************************************************/
int write_socket
                 (
                  int connfd /* connection descriptor into which to write */
                 )
{
    A_TRACE(DETAILED_TRACE, ("Entering the write_socket function\n"));

    NODE *ptr; /* variable to traverse the linked list storing dir paths */
    int len, /* length of each dir path */
        buffer_len; /* length of the buffer */
    int bytes_written, /* no of bytes written into socket */
        bytes = 0; /* to maintain total bytes written in each iteration of write */

    ptr = head; /* ptr pointing to start of the list */
    len = strlen (ptr->path_name);

    char *buffer;
    /* assigning len no of bytes to buffer and one extra for \0 */
    buffer = (char *)malloc ((len * sizeof (char)) + 1);
    if (NULL == buffer)
    {
        A_ERROR(MAJOR_ERROR, MALLOC_FAILURE);
        exit (FAILURE);
    }

    /* copy first dir path to buffer */
    strcpy (buffer, ptr->path_name);
    buffer[len] = '\0';
    ptr = ptr->next; /* move ptr to next node */

    while (NULL != ptr)
    {
        len = strlen (ptr->path_name);
        buffer_len = strlen (buffer);
        buffer = (char *)realloc (buffer, (buffer_len + 1 + len + 1)); /* new size = previous size + space + len of new str + \0 */
        strcat (buffer, " "); /* append a space as a delimiter */
        strcat (buffer, ptr->path_name); /* concatenate */
        buffer[(buffer_len + 1 + len)] = '\0';
        ptr = ptr->next; /* move pte to next node */
    } /* end of while loop */

    /* append a $ at the end of the final buffer string to mark the end */
    buffer_len = strlen (buffer);
    buffer = (char *)realloc (buffer, (buffer_len + 1 + 1)); /* new size = previous size + $ + \0 */
    buffer[buffer_len] = '$';
    buffer[buffer_len + 1] = '\0';
    buffer_len += 1;

    /* write the concatenated buffer to socket */
    while (bytes < buffer_len)
    {
        bytes_written = write (connfd, (buffer + bytes), (buffer_len - bytes));
        bytes += bytes_written;
    } /* end of while loop */

    /* release the memory after use */
    free (buffer);
    buffer = NULL;

    A_TRACE(DETAILED_TRACE, ("Leaving the write_socket function\n"));

    return SUCCESS;
}
