#ifndef _ARGPARSER_H_
#define _ARGPARSER_H_

#include<stdio.h>
#include<string.h>

#ifdef __cplusplus
extern "C" {
#endif

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

// Display the help to stdout.
static inline void argparser_help(struct ARGPARSER_DATA* data_array, int data_array_size)
{
  // Get maximum length of the flag names.
  int name_len_max = 0;
  for(int n = 0; n < data_array_size; n++)
  {
    int len = strlen(data_array[n].name);
    if(name_len_max < len)
      name_len_max = len;
  }

  char format[16];
  sprintf(format, "--%%-%ds   %%s\r\n", name_len_max);

  for(int n = 0; n < data_array_size; n++)
    printf(format, data_array[n].name, data_array[n].description);
}

// Parsing arguments.
static inline void argparser_parse(int argc, char** argv, struct ARGPARSER_DATA* data_array, int data_array_size)
{
  for(int n = 0; n < argc; n++)
  {
    char* flag_name_start;
    // If argv[n] is flag, try to set value which name is match.
    if(!strncmp(argv[n], "--", 2))
      flag_name_start = &argv[n][2];
    else if(!strncmp(argv[n], "-", 1))
      flag_name_start = &argv[n][1];
    else
      continue;

    for(int d = 0; d < data_array_size; d++)
    {
      // Get data_array[d]'s flag name's length. It uses at strncmp().
      int flag_name_len = strlen(data_array[d].name);
      // If flag name is equal to data_array[d]'s one, check if it has value.
      if(!strncmp(flag_name_start, data_array[d].name, flag_name_len))
      {
        // flag_equal[0] is '=' if current argv has any value.
        char* flag_equal = &flag_name_start[flag_name_len];
        // Flag value. If the argv has any value, this will contain it.
        // Otherwise, it will empty string. (strlen(flag_value_start) is 0)
        char* flag_value_start = flag_equal;

        // If this flag has value, set value.
        if(flag_equal[0] == '=')
          flag_value_start = &flag_equal[1];
        // Set value to the flag data.
        data_array[d].value = flag_value_start;
        break;
      }
    }
  }
}

// Check if flag, name, has specified and its value.
static inline char* argparser_has(char* name, struct ARGPARSER_DATA* data_array, int data_array_size)
{
  for(int n = 0; n < data_array_size; n++)
    // If data_array[n] is relevant flag, return its value.
    // If the flag is not specified, it return initializing value.
    if(!strcmp(data_array[n].name, name))
      return data_array[n].value;
  // Not any relevant flag has found, return NULL.
  return NULL;
}

#ifdef ___cplusplus
}
#endif

#endif