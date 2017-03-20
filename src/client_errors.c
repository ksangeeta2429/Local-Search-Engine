/*********************************************************************
*
*    File name: error_msg.c
*
*    Description: contains error function
*
*    Name    Date       Reference    Reason
*    Grp4    3-May-2014 TH6_grp4     Initial Creation
*
*    Copyright 2014, Aricent Technologies (Holdings) Limited
**********************************************************************/

/**********************************************************************
*                           Header files
***********************************************************************/
#include"client_header.h"

/* array of pointer to hold different error messages */
char *error_msg[] = 
                {
                    "Please enter the IP address",
                    "Please enter the Port no",
                    "Socket creation error",
                    "Error in connecting to server",
                    "Memory not available"
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
