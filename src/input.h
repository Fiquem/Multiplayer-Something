#pragma once

#include "stdio.h"
#include "stdlib.h"

#define MAX_MESSAGE_LEN 32767

struct chat_message{
  char * message;
  int len;
};

chat_message init_message();
bool get_user_input_from_console(chat_message*);
char * getline();
