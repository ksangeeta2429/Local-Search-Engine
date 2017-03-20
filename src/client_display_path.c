/*********************************************************************
*
*    File name: client_display.c
*
*    Description: display searched dir paths
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

/***********************************************************************
*                           Global variables
************************************************************************/
static int client_index; /* global variable to display index nos for dir paths */

/************************************************************************
*    Func name: display_dir_path
*
*    Description: tokenize the string received from server and display to
*                 the client
*
*    Return value: max value of index
*************************************************************************/
int display_dir_path
                     (
                      char *buffer /* variable to receive all paths in concatenated form */
                     )
{
    A_TRACE(DETAILED_TRACE, ("Entering dispaly_dir_path_func\n"));

    char *token; /* variable to store tokens */

    token = strtok (buffer, " "); /* tokenizing with space as delimiter */
    printf ("\nChoose from the foll paths\n\n");

    while (NULL != token)
    {
        printf ("\t%4d %s\n", ++client_index, token); /* print as index# path name */
        token = strtok (NULL, " ");
    } /* end of while loop */
    printf ("\n");

    A_TRACE(DETAILED_TRACE, ("Returning from dispaly_dir_path\n"));

    return client_index;
}
