#include "input.h"

chat_message init_message()
{
    chat_message m;
    m.len = 0;
    m.message = (char*)malloc(MAX_MESSAGE_LEN);
}

bool get_user_input_from_console(chat_message * m)
{
    char c = fgetc(stdin);
    printf("adding %c to string", c);
    if(c == '\n')
    {
        *(m->message) = '\0';
        return true;
    }
    m->len++;
    *(m->message)++ = c;
}

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

        if(c == '\n')
            break;
        *line++ = c;
    }
    *line = '\0';
    return linep;
}
