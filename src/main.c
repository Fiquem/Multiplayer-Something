// started 19/08/16
// looks like a proj I can copy from https://github.com/dtolj/simple-chat-client-server/blob/master/chat.c

#include <stdio.h>
#include "network.h"

int main(int argc, char **argv) {

    init_network();

    if (argv[1][0] == '0'){
        printf("running server\n");
        server();
    } else if (argv[1][0] == '1'){
        printf("running client\n");
        client(argc, argv);
    } else {
        printf("num args: %d. first arg: %s. second arg: %s\n", argc, argv[1], argv[2]);
        printf("u fuct up sun\n");
    }

}
