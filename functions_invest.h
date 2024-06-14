#ifndef FUNCTIONS_READ_INVEST_H
#define FUNCTIONS_READ_INVEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// INIT das funções

int lerInteiro(const char *mensagem);
double lerDouble(const char *mensagem);
void lerString(const char *mensagem, char *str, int tamanho);
void criarInvestimento(struct Investimentos *investimentos);
void adicionarIndicador(struct GroupIndicFinanc *grupo);
void listarInvestimentos(struct Investimentos *investimentos);
void excluirInvestimento(struct Investimentos *investimentos);
void listarIndicadores(struct GroupIndicFinanc *grupo);
void excluirIndicador(struct GroupIndicFinanc *grupo);
void gravarInvestimentos(struct Investimentos *invest, const char *nomeArquivo);
void carregarInvestimentos(struct Investimentos *invest, const char *nomeArquivo);
void gravarIndicadores(struct GroupIndicFinanc *grupo, const char *nomeArquivo);
void carregarIndicadores(struct GroupIndicFinanc *grupo, const char *nomeArquivo);
void simularInvestimento(struct Investimentos *invest, struct GroupIndicFinanc *grupo);
void print_line(void);


#endif 
