/*********************************************************************
*
*    File write_path.c
*
*    Description: client sends the path of file required
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
*    Func name: write_path
*
*    Description: gets the path from client and sends it to server over the socket
*
*    Return value: SUCCESS
*************************************************************************/
int write_path
              (
               int sd /* socket descriptor */
              )
{
    char path[SIZE]; /* variable to store path */
    int len; /* len of the path entered */

    /* ask client to enter the path required */
    printf ("\nEnter the path\n");
    fgets (path, SIZE, stdin);

    len = strlen (path); /* length of path */ 

    /* check if last character is \n */
    if ('\n' == path[len - 1])
    {
        path[len - 1] = '$'; /* append a $ to mark end of string */
        path[len] = '0';
    }
    else
    {
        path[len] = '$'; /* append a $ to mark end of string */
        path[len + 1] = '\0';
        len++;
    }

    /* write the path to socket */
    write (sd, path, len);

    return SUCCESS;    

}
