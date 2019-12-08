#include "fattoreX.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>

static Candidati candidati;
static Output out;
static int inizializzato = 0;

void inizializza() {
    int i;
    int j;

    if(inizializzato == 1) {
        return;
    }

    for(i = 0; i < MAXCANDIDATI; i++) {
        strcpy(candidati.candidato[i].candidato, "L");
        strcpy(candidati.candidato[i].giudice, "L");
        candidati.candidato[i].categoria = 'L';
        strcpy(candidati.candidato[i].nomeFile, "L");
        candidati.candidato[i].fase = 'L';
        candidati.candidato[i].voto = -1;
    }

    strcpy(candidati.candidato[3].candidato, "Lucone il gigante");
    strcpy(candidati.candidato[3].giudice, "Rato Hosbor");
    candidati.candidato[3].categoria = 'O';
    strcpy(candidati.candidato[3].nomeFile, "LuconeIlGignte.txt");
    candidati.candidato[3].fase = 'B';
    candidati.candidato[3].voto = 35;

    strcpy(candidati.candidato[6].candidato, "Simone, parcheggiatore abusivo");
    strcpy(candidati.candidato[6].giudice, "Sù LadroGe");
    candidati.candidato[6].categoria = 'U';
    strcpy(candidati.candidato[6].nomeFile, "Simone.txt");
    candidati.candidato[6].fase = 'S';
    candidati.candidato[6].voto = 100;

    strcpy(candidati.candidato[9].candidato, "Luca trentotto");
    strcpy(candidati.candidato[9].giudice, "Ale Diomai");
    candidati.candidato[9].categoria = 'U';
    strcpy(candidati.candidato[9].nomeFile, "Luca.txt");
    candidati.candidato[9].fase = 'S';
    candidati.candidato[9].voto = 85;

    strcpy(candidati.candidato[12].candidato, "GVNGDROGV");
    strcpy(candidati.candidato[12].giudice, "Cara Madonna");
    candidati.candidato[12].categoria = 'B';
    strcpy(candidati.candidato[12].nomeFile, "gang.txt");
    candidati.candidato[12].fase = 'A';
    candidati.candidato[12].voto = 110;

    inizializzato = 1;

    printf("Terminata iniializzazione struttura dati\n");
}

int compare(Giudice o1, Giudice o2) {
    int result;

    if(o1.punteggio < o2.punteggio) {
        result = -1;
    } else if(o1.punteggio > o2.punteggio) {
        result = 1;
    }

    return result;
}

void scambia(Giudice *a, Giudice *b) {
    Giudice temp = *a;
    *a = *b;
    *b = temp;
}

void quicksortR(Output a, int inizio, int fine) {
    int i, j, iPivot;
    Giudice pivot;

    if(inizio < fine) {
        i = inizio;
        j = fine;
        iPivot = fine;
        pivot = a.giudici[iPivot];

        do {
            while(i < j && compare(a.giudici[i], pivot) <= 0) {
                i++;
            }

            while(j > i && compare(a.giudici[j], pivot) >= 0) {
                j--;
            }
        } while(i < j);

        if(i != iPivot && compare(a.giudici[i], a.giudici[iPivot])) {
            scambia(&a.giudici[i], &a.giudici[iPivot]);
            iPivot = i;
        }

        if(inizio < iPivot - 1) {
            quicksortR(a, inizio, iPivot - 1);
        }

        if(iPivot + 1 < fine) {
            quicksortR(a, iPivot + 1, fine);
        }
    }
}

void ordina(Output v, int dim) {
    quicksortR(v, 0, dim - 1);
}

Output * classifica_giudici_1_svc(void *in, struct svc_req *rp) {
    inizializza();

    ordina(out, MAXGIUDICI);

    return &out;
}

int * esprimi_voto_1_svc(Input *in, struct svc_req *rp) {
    inizializza();

    char *nome;
    char *operazione;
    int i = 0;
    int trovato = 0;

    strcpy(nome, in->candidato);
    strcpy(operazione, in->operazione);

    while(!trovato) {
        if(strcmp(candidati.candidato[i].candidato, nome) == 0) {
            trovato = 1;

            if(strcmp(operazione, "aggiunta") == 0) {
                candidati.candidato[i].voto++;
            } else if(strcmp(operazione, "sottrazione") == 0) {
                candidati.candidato[i].voto--;
            } else {
                return -1;
            }
        }
        i++;
    }

    return 0;
}

