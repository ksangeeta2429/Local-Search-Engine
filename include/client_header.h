/*********************************************************************
*
*    File name: client_header.h
*
*    Description: header file for the client program
*
*    Name    Date    Reference    Reason
*    Grp4            TH6_grp4     Initial Creation
*
*    Copyright 2014, Aricent Technologies (Holdings) Limited
**********************************************************************/
#ifndef client_hh
#define client_hh

/**********************************************************************
*                              Header files
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/***********************************************************************
*                                MACROS
************************************************************************/
#define SUCCESS      0
#define FAILURE      1
#define SIZE      1024
#define BUF_SIZE     5
#define TOKEN_SIZE 500

/* trace macros */
#define NO_TRACE       1
#define BREIF_TRACE    2
#define DETAILED_TRACE 3

/* error macros */
#define NO_ERROR    1
#define MAJOR_ERROR 2
#define MINOR_ERROR 3

/* error_indices */
#define NO_ADDRESS     0
#define NO_PORT        1
#define SOCKET_ERROR   2
#define CONNECT_ERROR  3
#define MALLOC_FAILURE 4

/* error function */
#define A_ERROR(error_level, error_index) error(error_level, error_index)

/* trace function */
#ifdef TRACE_FEATURE
  #define A_TRACE(level, x) if (g_trace_level >= level) printf x
#else
  #define A_TRACE(level, x) /* do nothing */
#endif

/************************************************************************
*                            Global variables
*************************************************************************/
extern int g_trace_level;
extern int g_error_level;

/************************************************************************
*                           Function Prototype
*************************************************************************/ 
int client_write(int);
int client_read(int);
int display_dir_path(char *);
int index_write(int, int);
int read_file_content(int);
int write_path(int);
void error(int, int);

#endif
