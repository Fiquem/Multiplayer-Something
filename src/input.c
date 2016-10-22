#include "input.h"
/*
void init_message()
{
    current_message_len = 0;
    current_message = (char*)malloc(MAX_MESSAGE_LEN);
}

bool get_user_input_from_console()
{
    current_message_len++;
    *current_message++ = fgetc(stdin);
    if(*current_message == '\n')
      return true;
}*/

char * getline() {
    char * line = (char*)malloc(100);
    char * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = (char*)realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}
