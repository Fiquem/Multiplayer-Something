#pragma once

#include "stdio.h"
#include "stdlib.h"

#define MAX_MESSAGE_LEN 32767

//char * current_message;
//int current_message_len;

void init_message();
bool get_user_input_from_console();
char * getline();
