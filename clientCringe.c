#include "fattoreX.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>

int main(int argc, char const *argv[]) {

    CLIENT *client;
    char *server;
    int servizio;
    int operazione;
    int *result;

    void *in;

    char nomeCandidato[32];

    Output *out;

    if(argc != 2) {
        printf("Numero argomenti non valido..\n");
        exit(1);
    }

    server = argv[1];

    client = clnt_create(server, FATTOREXPROG, FATTOREXVERS, "udp");
    if(client == NULL) {
        clnt_pcreateerror(server);
        exit(2);
    }

    while(1) {
        printf("************************************\n\nScegli il servizio (1/2/3)\n1 - Classifica\n2 - Vota\n3 - Esci\n\n************************************\n");

        char str_i[20];
        fgets(str_i, 20, stdin);
        servizio = strtol(str_i, NULL, 0);

        if(servizio == 1) {
            printf("Servizio di visualizzazione della classifica\n\n");
            
            out = classifica_giudici_1(in, client);

            if(out == NULL) {
                clnt_perror(client, server);
                printf("Errore: out is null\n");
                continue;
            } else if(&out == NULL) {
                clnt_perror(client, server);
                printf("Errore: & out is null\n");
            }

            for(int i = 0; i < MAXGIUDICI; i++) {
                if(strcmp(&out->giudici[i], "L")) {
                    printf("Giudice: %s\t\tPunteggio: %d\n", out->giudici[i].nomeGiudice, out->giudici[i].punteggio);
                }
            }

        } else if(servizio == 2) {
            printf("Servizio di votazione\n\n");
            printf("Chi vuoi votare?\n");

            fgets(nomeCandidato, 32, stdin);
            nomeCandidato[strcspn(nomeCandidato, "\n")] = 0;
            printf("Votazione di %s\n\t1 - aggiungi voto\n\t2 - sottrai voto\n\n");

            char str[20];
            fgets(str, 20, stdin);
            operazione = strtol(str, NULL, 0);

            if(operazione == 1) {
                Input in;

                strcpy(in.candidato, nomeCandidato);
                strcpy(in.operazione, "aggiunta");

                result = esprimi_voto_1(&in, client);
                
                if(result == NULL) {
                    clnt_perror(client, server);
                    printf("errore RPC\n");
                } else if(*result == 0) {
                    printf("Votazione avvenuta\n");
                } else if(*result == -1) {
                    clnt_perror(client, server);
                    printf("errore protocollo\n");
                } else if(*result == 1) {
                    clnt_perror(client, server);
                    printf("Candidato non trovato\n");
                }
            } else if(operazione = 2) {
                Input in;
                strcpy(in.candidato, nomeCandidato);
                strcpy(in.operazione, "sottrazione");

                result = esprimi_voto_1(&in, client);
                
                if(result == NULL) {
                    clnt_perror(client, server);
                    printf("errore RPC\n");
                } else if(*result == 0) {
                    printf("Votazione avvenuta\n");
                } else if(*result == -1) {
                    clnt_perror(client, server);
                    printf("errore protocollo\n");
                } else if(*result == 1) {
                    clnt_perror(client, server);
                    printf("Candidato non trovato\n");
                }
            }
        } else if(servizio == 3) {
             printf("Termino...\n");
             break;
        } else {
            printf("Servizio non valido...\n");
            continue;
        }
    }

    clnt_destroy(client);
}

