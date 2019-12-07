#include "fattoreX.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>

int main(int argc, char const *argv[]) {

    CLIENT *client;
    char *server;
    int servizio;

    if(argc != 2) {
        printf("Numero argomenti non valido..\n");
        exit(1);
    }

    server = argv[1];

    client = clnt_create(server, )


    return 0;
}

