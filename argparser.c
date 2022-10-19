
#include"argparser.h"

void argparser_help(struct ARGPARSER_DATA* data_array, int data_array_size)
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

void argparser_parse(int argc, char** argv, struct ARGPARSER_DATA* data_array, int data_array_size)
{

}
