const MAXCANDIDATI=15;
const MAXGIUDICI=5;

struct Candidato {
    char candidato[32];
    char giudice[32];
    char categoria;
    char nomeFile[32];
    char fase;
    int voto;
};

struct Candidati {
    Candidato candidato[MAXCANDIDATI];
};

struct Giudice {
    char nomeGiudice[32];
    int punteggio;
};

struct Output {
    Giudice giudici[MAXGIUDICI];
};

struct Input {
    char candidato[32];
    char operazione;
};

program FATTOREX {
    version FATTOREXVERS {
        Output CLASSIFICA_GIUDICI(void) = 1;
        Candidati ESPRIMI_VOTO(Input) = 2;
    } = 1;
} = 0x20000013;