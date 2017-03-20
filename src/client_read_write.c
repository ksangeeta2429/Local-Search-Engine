/*********************************************************************
*
*    File name: client_read_write.c
*
*    Description: read and write the socket
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
*    Func name: client_write
*
*    Description: send the pattern to be searched
*
*    Return value: SUCCESS
*************************************************************************/
int client_write
                 (
                  int sd /* socket descriptor */
                 )
{
    char buffer[SIZE];  /* to store the pattern to be sent  */
    int len,  /* length of the pattern */
        bytes_written,  /* no of bytes written to sd */
        bytes = 0;  /* to assure all the bytes have been written */

    printf ("\nEnter the pattern you want to search\n");
    fgets (buffer, SIZE, stdin); /* get the pattern from user */
    len = strlen (buffer);
    if ('\n' == buffer[(len - 1)]) /* if \n is also stored as a character */
    {
        buffer[(len - 1)] = '$'; /* append a $ to mark end */
        buffer[len] = '\0';
    }
    else /* if \n is not stored as a character */
    {
        buffer[len] = '$'; /* append a $ to mark end */
        buffer[(len + 1)] = '\0';
    }

    while (bytes < len)
    {
        bytes_written = write (sd, (buffer + bytes), (len - bytes));
        bytes += bytes_written;
    } /* end of while loop */

    return SUCCESS;
}

/************************************************************************
*    Func name: client_read
*
*    Description: receive the dir paths
*
*    Return value: SUCCESS or FAILURE
*************************************************************************/
int client_read
                (
                 int sd /* socket descriptor */
                )
{
    char *buffer,  /* to get the pattern from client */
         local_buffer = {'\0'};  /* buffer to read socket byte by byte */
    int bytes_read,  /* no of bytes read from sd */
        buffer_index = 0, /* index for buffer */
        index_max; /* max value of index of dir path */

    buffer = (char *)malloc (BUF_SIZE * sizeof (buffer));
    if (NULL == buffer)
    {
        A_ERROR(MAJOR_ERROR, MALLOC_FAILURE);
        exit (FAILURE);
    }

    memset (buffer, '\0', BUF_SIZE * sizeof (char)); /* clear the buffer */
    while ((bytes_read = read (sd, &local_buffer, 1)) > 0)
    {
        if ('$' == local_buffer)
        {
            break;
        }
        buffer[buffer_index] = local_buffer;
        buffer[(buffer_index + 1)] = '\0';
        buffer_index += 1;
        buffer = (char *)realloc (buffer, (buffer_index + 2));
    } /* end of while loop */
 
    /* display the dir paths in user friendly manner */
    if ('\0' != local_buffer)  
    {
        /* if some data has been read, call display func */
        index_max = display_dir_path(buffer);
        /* write the index no for path name to be opened into socket */
        index_write(sd, index_max);
    }
    else /* if nothing is read */
    {
        printf ("\t----------No results found----------\n");
    }

    /* release the memory after use */
    free (buffer);
    buffer = NULL;

    return SUCCESS;
}
