/*********************************************************************
*
*    File name: dir_search.c
*
*    Description: find all absolute paths containing the string searched
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
*    Func name: dir_path
*
*    Description: searches the complete file system and gives the path of 
*                 required directories
*
*    Return value: SUCCESS or FAILURE
*************************************************************************/
int dir_path
             (
              char *dir_name, /* name of the directory currently searched */ 
              char *pattern  /* the pattern to be searched */
              )
{
    char path[SIZE]; /* variable to store the path */
    DIR *dir;  /* pointer of type DIR defined in dirent.h */

    /* open the directory */
    dir = opendir (dir_name);

    /* give an error if directory not opened */
    if (NULL == dir) 
    {
        A_ERROR(MAJOR_ERROR, DIR_OPEN_FAIL);
        exit (FAILURE);
    }

    while (1) 
    {
        struct dirent *directory;  /* pointer object for structure dirent */
        char *d_name;  /* to store the name of current directory being scanned */
     
        struct stat buf;

        /* readdir returning pointers to next directory in dirent structure */
        directory = readdir (dir);
        if (NULL == directory) 
        {
            break;
        }

        d_name = directory->d_name;

        /* skip '.' and '..' directories */
        if (0 != strcmp(d_name, ".") && 0 != strcmp(d_name, ".."))
        {
            /* print the path of directories matchong the pattern */
            if (NULL != strstr(d_name, pattern))
            {
                sprintf (path, "%s/%s", dir_name, d_name);
                stat (path, &buf); /* stat all the attributes of the path */
                if (S_ISREG(buf.st_mode))
                {
                    /* if the path refers to a file store it in the linked list */
                    make_list(path);
                }
            }
        }

        /* module to change the path to sub directory if parent is a directory */
        if (DT_DIR == directory->d_type) 
        {
            /* skip the steps for '.' and '..' */
            if (strcmp (d_name, ".") != 0 &&
                strcmp (d_name, "..") != 0) 
            {
                int path_len; /* variable to store length of the path */
                char path[MAX_PATH_SIZE]; /* new path changed to path of sub directory */
 
                /* store the current path in path variable with MAX_PATH_SIZE set as a macro */
                path_len = snprintf (path, MAX_PATH_SIZE, "%s/%s", dir_name, d_name);
                if (path_len >= MAX_PATH_SIZE) 
                {
                    A_ERROR(MINOR_ERROR, PATH_LEN_EXCEEDED);
                    exit (FAILURE);
                }
                /* recursively call the function till all directories scanned */
                dir_path(path, pattern);
            }
        }
    } /* end of while loop */

    /* give an error if directory is not closed properly */
    if (0 != closedir (dir)) 
    {
        A_ERROR(MINOR_ERROR, DIR_CLOSE_FAIL);
        exit (FAILURE);
    }

    return SUCCESS;
}
