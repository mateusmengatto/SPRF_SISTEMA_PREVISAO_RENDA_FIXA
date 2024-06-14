#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "struct_invest.h"
#include "functions_invest.h"


//carregar dados
void load(struct Investimentos *invest, struct GroupIndicFinanc *grupo, const char *arquivoInvestimentos, const char *arquivoIndicadores){
    carregarInvestimentos(invest, arquivoInvestimentos);
    carregarIndicadores(grupo, arquivoIndicadores);

}
//salvar dados
void save(struct Investimentos *invest, struct GroupIndicFinanc *grupo, const char *arquivoInvestimentos, const char *arquivoIndicadores) {
    gravarInvestimentos(invest, arquivoInvestimentos);
    gravarIndicadores(grupo, arquivoIndicadores);
}

void print_header(){
    printf("\n");
    printf(" _________________________________________________________________________________________________________________ \n");
    printf("|                                                                                                                 |\n");
    printf("|                       $   $   $   $   $  Sistema de Previsao de Renda Fixa  $   $   $   $   $                   |\n");
    printf("|_________________________________________________________________________________________________________________|\n");
}

void fechar_funcao(){
    printf("Pressione enter para continuar...");
    getchar();
    getchar();
}


int main() {
    struct Investimentos investimentos = { .num_invests = 0 };
    struct GroupIndicFinanc indicadores = { .num_inds = 0 };

    int opcao;
    bool sair = false;

    // Inicializa os dados
    load(&investimentos, &indicadores, "investimentos.dat", "indicadores.dat");

    do {
        system("cls");
        print_header();
        printf("|------------------------------------------------------Menu-------------------------------------------------------|\n");
        printf("                                        | 1 | Simulacao de investimento                                           |\n");
        printf("                                        | 2 | Exibir investimentos cadastrados                                    |\n");
        printf("                                        | 3 | Criar investimento                                                  |\n");
        printf("                                        | 4 | Exibir previsoes de indicadores cadastrados                         |\n"); 
        printf("                                        | 5 | Adicionar previsao de indicadores                                   |\n");
        printf("                                        | 6 | Excluir Investimento                                                |\n");
        printf("                                        | 7 | Excluir previsao de indicadores                                     |\n");
        printf("                                        | 0 | Salvar e Sair                                                       |\n");
        printf("------------------------------------------------------------------------------------------------------------------|\n");
                
        printf(">Digite uma opcao:  ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                print_header();
              
                printf("| 1 | Simulacao de investimento-------------------------------------------------------------------------------->\n\n");
                simularInvestimento(&investimentos, &indicadores); // Corrigido de print() para printf()
                fechar_funcao();
                break;

            case 2:
                system("cls");
                print_header();
                printf("| 2 | Investimentos cadastrados-------------------------------------------------------------------------------->\n");
                listarInvestimentos(&investimentos);
                fechar_funcao();
                break;
                
            case 3:
                system("cls");
                print_header();
                printf("| 3 | Criacao de investimento-----------------------------------------------------------------------------------> \n");
                criarInvestimento(&investimentos);
                fechar_funcao();
                break;

            case 4:
                system("cls");
                print_header();
                printf("| 4 | Previsoes de indicadores cadastrados-----------------------------------------------------------------------> \n");
                listarIndicadores(&indicadores);
                fechar_funcao();
                break;

            case 5:
                system("cls");
                print_header();
                printf("| 5 | Criacao de investimento-------------------------------------------------------------------------------------> \n");
                adicionarIndicador(&indicadores);
                fechar_funcao();
                break;

            case 6:
                system("cls");
                print_header();
                printf("| 6 | Excluir investimento----------------------------------------------------------------------------------------> \n");
                excluirInvestimento(&investimentos);
                fechar_funcao();
                break;
            
            case 7:
                system("cls");
                print_header();
                printf("| 7 | Excluir previsao de indicadores----------------------------------------------------------------------------> \n");
                excluirIndicador(&indicadores);
                fechar_funcao();
                break;

            case 0:
                printf("Saindo...\n");
                sair = true; // Definir a flag sair como true para sair do loop
                break;

            default:
                printf("Opcao invalida!\n");
                fechar_funcao();
        }
    } while(!sair); // Corrigido para verificar a flag sair

    //salva os dados
    save(&investimentos, &indicadores, "investimentos.dat", "indicadores.dat");
    return 0;
}



        

