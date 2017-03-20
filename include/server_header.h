/*********************************************************************
*
*    File name: server_header.h
*
*    Description: header file for the server program
*
*    Name    Date    Reference    Reason
*    Grp4            TH6_grp4     Initial Creation
*
*    Copyright 2014, Aricent Technologies (Holdings) Limited
**********************************************************************/
#ifndef server_hh
#define server_hh

/**********************************************************************
*                            Header files
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

/***********************************************************************
*                               Structure 
************************************************************************/
typedef struct node
{
    int index;
    char *path_name;
    struct node *next;
}NODE;

/***********************************************************************
*                                MACROS
************************************************************************/
#define ROOT_PATH "/user/gur36647"

#define MYPORT      36600
#define QSIZE           5
#define BUFSIZE       100
#define BUF_SIZE        5
#define MAX_PATH_SIZE 500
#define SUCCESS         0
#define FAILURE         1
#define SIZE         1024
#define MAX          1024

/* error indices */
#define SOCKET_ERROR      0
#define BIND_ERROR        1
#define LISTEN_ERROR      2
#define CONNECTION_ERROR  3
#define DIR_OPEN_FAIL     4
#define PATH_LEN_EXCEEDED 5
#define DIR_CLOSE_FAIL    6
#define MALLOC_FAILURE    7
#define FILE_OPEN_FAIL    8
#define FILE_CLOSE_FAIL   9

/* trace Macros */
#define NO_TRACE       1
#define BREIF_TRACE    2
#define DETAILED_TRACE 3

/* error Macros */
#define NO_ERROR    1
#define MAJOR_ERROR 2
#define MINOR_ERROR 3

/* error function */
#define A_ERROR(error_level, error_index) error(error_level, error_index)

/* macro function */
#ifdef TRACE_FEATURE
  #define A_TRACE(level, x) if (g_trace_level >= level) printf x
#else
  #define A_TRACE(level, x) /* do nothing */
#endif

/************************************************************************
*                             Global Variables
*************************************************************************/
extern int sd;
extern int g_trace_level;
extern int g_error_level;
extern NODE *head;

/************************************************************************
*                            Function prototype
*************************************************************************/
int read_socket(int, char *);
int write_socket(int);
int dir_path(char *, char *);
int make_list(char *);
int display_list(void);
int free_all(void);
int index_read(int);
int file_open(int, char *);
int write_file_content(int, char *, int);
int open_file_path(int);
void error(int, int);

#endif
