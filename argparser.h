#ifndef _ARGPARSER_H_
#define _ARGPARSER_H_

#include<stdio.h>
#include<string.h>

typedef struct ARGPARSER_DATA
{
  // Argument name.
  char* name;
  // Argument description.
  // It is displayed when help() is called.
  char* description;
  // Argument value. When parse() is called, it may set.
  // You should initialize with NULL, or default value.
  // If flag is found at calling parse(), value will set non-NULL.
  char* value;
} ARGPARSER_DATA;

void argparser_help(struct ARGPARSER_DATA* data_array, int data_array_size);
void argparser_parse(int argc, char** argv, struct ARGPARSER_DATA* data_array, int data_array_size);

#endif