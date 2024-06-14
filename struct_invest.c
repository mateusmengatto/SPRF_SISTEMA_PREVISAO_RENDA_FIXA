#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_INVESTIMENTOS 100
#define MAX_INDICES 100

// Estrutura do CDB
struct rendFix {
    int id;
    char nome[30];
    double rentabilidade_taxa;
    int indicador; // taxa do referencial ano
    int operador;
    int prazo; // em meses
    double imposto_renda; // alíquota do IR
};

// Estrutura para armazenar todos os investimentos
struct Investimentos {
    struct rendFix invests[MAX_INVESTIMENTOS];
    int num_invests;
};

struct IndicFinanc {
    int id;
    char nome[30];
    double CDI;
    double IPCA;
    double SELIC;
};

struct GraoupIndicFinnc {
    struct IndicFinanc indices[MAX_INDICES];
    int num_inds;
};

