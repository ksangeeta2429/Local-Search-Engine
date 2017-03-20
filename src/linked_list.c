/*********************************************************************
*
*    File name: linked_list.c
*
*    Description: creation of linked list
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

/***********************************************************************
*                           Global variables
************************************************************************/
NODE *head = NULL; /* start pointer for the linked list */
static int index_no; /* global variable to store index no */

/************************************************************************
*    Func name: make_list
*
*    Description: create a linked list and store each dir path
*
*    Return value: SUCCESS or FAILURE
*************************************************************************/
int make_list
              (
               char *path /* stores the path of the directory searched */
              )
{
    NODE *ptr; /* variable to traverse the node */
    NODE *new_node; /* new node allocated the memory */

    /* assigning space to the new node */
    new_node = (NODE *)malloc (sizeof (NODE));
    /* error message if memory allocation fails */
    if (NULL == new_node)
    {
        A_ERROR(MAJOR_ERROR, MALLOC_FAILURE);
        exit (FAILURE);
    }

    /* assigning memory to store the dir path */
    new_node->path_name = (char *)malloc (MAX * sizeof (char));
    /* error message if memory allocation fails */
    if (NULL == new_node->path_name)
    {
        A_ERROR(MAJOR_ERROR, MALLOC_FAILURE);
        exit (FAILURE);
    }

    /* filling entries in the newly created node */
    new_node->index = ++index_no;
    strcpy (new_node->path_name, path);
    new_node->next = NULL;

    if (NULL == head)
    {
        head = new_node;  /* if list is empty head points to the new node */
    }
    else 
    {
        /* traverse the list till last node */
        ptr = head;
        while (NULL != ptr->next)
        {
            ptr = ptr->next;  /* point to next node */
        } /* end of while loop */
        ptr->next = new_node;  /* ptr points to the next node */
    }

    return SUCCESS;
}

/************************************************************************
*    Func name: display_list
*
*    Description: display the list on server side
*
*    Return value: SUCCESS
*************************************************************************/
int display_list(void)
{
    A_TRACE(DETAILED_TRACE, ("Entering the display_list func\n"));  

    NODE *ptr; /* variable to traverse the list */
    ptr = head; /* ptr points to start of list */
    printf ("List\n");
    while (NULL != ptr)
    {
        printf ("\t%4d %s\n", ptr->index, ptr->path_name);
        ptr = ptr->next; /* point to next node */
    } /*end of while loop */

    A_TRACE(DETAILED_TRACE, ("Leaving the dispaly_list func\n");)

    return SUCCESS;
}

/************************************************************************
*    Func name: free_all
*
*    Description: on exit free all the allocated memory
*
*    Return value: SUCCESS
*************************************************************************/
int free_all(void)
{
    A_TRACE(BREIF_TRACE, ("Entering the function free_all\n"));

    NODE *ptr;  /* variable to traverse the list */

    /* free the memory till head becomes NULL */
    while (NULL != head)
    {
        ptr = head; /* ptr points to start of list */
        head = ptr->next; /* head points to next node */
        free (ptr->path_name); /* free the path_name member */
        free (ptr); /* free the complete node */
    } /* end of while loop */
 
    ptr = NULL;
    index_no = 0;

    return SUCCESS;
}
