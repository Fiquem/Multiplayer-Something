// started 19/08/16
#include <stdio.h>
#include "network.h"

int main(int argc, char **argv) {

    init_network();

    if (argv[2] == 0){
        printf("running server\n");
        server();
    }else{
        printf("running client\n");
        client(argc, argv);
    }
    
}