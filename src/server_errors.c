/*********************************************************************
*
*    File name: server_errors.c
*
*    Description: contains error function for server
*
*    Name    Date       Reference    Reason
*    Grp4    3-May-2014 TH6_grp4     Initial Creation
*
*    Copyright 2014, Aricent Technologies (Holdings) Limited
**********************************************************************/

/**********************************************************************
*                           Header files
***********************************************************************/
#include"server_header.h"

/* array of pointer to hold different error messages */
char *error_msg[] = 
                {
                    "Error in socket creation",
                    "Error in binding",
                    "Cannot listen to the client",
                    "Connection failure",
                    "Directory open failure",
                    "Path length is more than max limit",
                    "Directory not closed properly",
                    "Memory not available",
                    "Error in opening the file",
                    "Error in closing the file"
                };


/************************************************************************
*    Func name: error
*
*    Description: print appropriate error messages
*
*    Arguments: error_level set by user
*               error_index for approprite error msg index
*
*    Return value: void
*************************************************************************/
void error(int error_level, int error_index)
{
    if (g_error_level >= error_level)
    {
        printf ("%s\n", error_msg[error_index]);
    }
}
