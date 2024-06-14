#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


//importando structs
#include "struct_invest.h"


#define MAX_INVESTIMENTOS 100
#define MAX_INDICES 100

#define NUM_STRINGS 6
#define MAX_LENGTH 20

void limparBuffer(void);

const char INDIC_LIST[NUM_STRINGS][MAX_LENGTH] = {
    "Pre-fixado",
    "CDI", 
    "IPCA", 
    "SELIC", 
};


void print_line(void){
    printf("------------------------------------------------------------------------------------------------------------------\n");
}

int lerInteiro(const char *mensagem) {
    char entrada[100];
    int valor;
    while (1) {
        printf("%s", mensagem);
        fgets(entrada, sizeof(entrada), stdin);

        // Remove o newline, se existir
        entrada[strcspn(entrada, "\n")] = 0;

        // Verifica se todos os caracteres são dígitos
        int valido = 1;
        for (int i = 0; i < strlen(entrada); i++) {
            if (!isdigit(entrada[i])) {
                valido = 0;
                break;
            }
        }

        // Tenta converter para inteiro
        if (valido && sscanf(entrada, "%d", &valor) == 1) {
            return valor;
        } else {
            printf("Entrada invalida. Por favor, insira um numero inteiro.\n");
        }
    }
};

double lerDouble(const char *mensagem) {
    char entrada[100];
    double valor;
    
    while (1) {
        printf("%s", mensagem);
        fgets(entrada, sizeof(entrada), stdin);

        // Remove o newline, se existir
        entrada[strcspn(entrada, "\n")] = 0;

        if (sscanf(entrada, "%lf", &valor) == 1) {// Tenta converter para double
            return valor;
        } else {
            printf("Entrada invalida. Por favor, insira um numero.\n");
        }
    }
};

void lerString(const char *mensagem, char *str, int tamanho) {
    printf("%s", mensagem);
    getchar();
    if (fgets(str, tamanho, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    }
}

void criarInvestimento(struct Investimentos *investimentos) {
    if (investimentos->num_invests < MAX_INVESTIMENTOS) { // Corrigido para "<" em vez de ">"
        struct rendFix *rf = &investimentos->invests[investimentos->num_invests];
        rf->id = investimentos->num_invests + 1;
        
        print_line();
        lerString("Digite um nome para seu Investimento (pode ser utilizado posteriormente como um ID)(max 30 carac.): ", rf->nome, 30);
        do {
            rf->indicador = lerDouble("Indicador utilizado para rentabilidade\n Digite:\n(0) - Pre-fixado \n(1) - CDI \n(2) - IPCA \n(3) - SELIC \n->" );
            if (rf->indicador < 0 || rf->indicador > 3) {
                printf("Opcao inválida, digite novamente");
            }
        } while (rf->indicador < 0 || rf->indicador > 3);
        print_line();
        if (rf->indicador == 0) {
            rf->operador = 0;
            printf("Investimento pre-fixado selecionado");
        } else {
            do {
                rf->operador = lerInteiro("Digite\n(1) para Indice + taxa (ex. IPCA + 5%%), \n(2) para taxa * Referencial (ex. 100%% CDI): ");
                if (rf->operador != 1 && rf->operador != 2) {
                    printf("Opcao inválida, digite novamente");
                }
            } while (rf->operador != 1 && rf->operador != 2);
        }
        
        print_line();
        rf->rentabilidade_taxa = lerDouble("Digite a taxa de rentabilidade\nEX:\n se IPCA + 5%% -> Digite (5) \nse 100%% CDI -> Digite (100) |\n->  ");
        print_line();        
        rf->prazo = lerInteiro("Digite o prazo do investimento em ANOS: ");
        print_line();     
        rf->imposto_renda = lerDouble("Digite a aliquota do Imposto de Renda (%%): ");
        investimentos->num_invests++;
        printf("RendaFixa criada com sucesso!\n");
    } else {
        printf("Número máximo de investimentos atingido.\n");
    }
}


void listarInvestimentos(struct Investimentos *investimentos) {
    // Imprimir cabeçalho específico para CDB
    char tipo[12];

    printf("\n  ID   | Nome                          |   TIPO (a.a.)        | PRAZO (meses)| IR      | \n"); 
    if (investimentos->num_invests == 0) {
        printf("Nenhum investimento cadastrado.\n");
    }
        // Listar investimentos
    for (int i = 0; i < investimentos->num_invests; i++) {
    struct rendFix *rf = &investimentos->invests[i];
    char tipo[15];

    if (rf->operador == 0) {
        sprintf(tipo, "Pré Fixado   %.2lf%%", rf->rentabilidade_taxa);
    } else if (rf->operador == 1) {
        sprintf(tipo, "%s +%.2lf %%", INDIC_LIST[rf->indicador], rf->rentabilidade_taxa);
    } else if (rf->operador == 2) {
        sprintf(tipo, "%.2lf%% %s", rf->rentabilidade_taxa, INDIC_LIST[rf->indicador]);
    }

         
    printf("   %-3d | %-30s| %-21s|     %-4d     | %-5.2f % |\n", i+1, rf->nome, tipo , rf->prazo*12, rf->imposto_renda);
    }
    print_line();;

};


void excluirInvestimento(struct Investimentos *investimentos) {
    if (investimentos->num_invests == 0) {
        printf("Nenhum investimento cadastrado.\n");
        return;
    }

    listarInvestimentos(investimentos);
    int id = lerInteiro("Digite o ID do investimento que deseja excluir: ");
    

    if (id < 1 || id > investimentos->num_invests) {
        printf("ID de investimento inválido.\n");
        return;
    }

    // Deslocar os elementos subsequentes para a esquerda
    for (int i = id - 1; i < investimentos->num_invests - 1; i++) {
        investimentos->invests[i] = investimentos->invests[i + 1];
    }

    investimentos->num_invests--;
    printf("Investimento excluido com sucesso!\n");
}


void adicionarIndicador(struct GroupIndicFinanc *grupo) {
    if (grupo->num_inds < MAX_INDICES) {
        struct IndicFinanc *ind = &grupo->indices[grupo->num_inds];
        printf("Configuracao dos indices financeiro \nCaso queira utilizar somente um indice, digite (0) para os outros.\n");
        ind->id = grupo->num_inds + 1;
        print_line();
        lerString("Digite um nome para seu Indicador (pode ser utilizado posteriormente como um ID)(max 30 carac.): ", ind->nome, 30);
        print_line();
        ind->CDI = lerDouble("Digite o valor do CDI: ");
        print_line();
        ind->IPCA = lerDouble("Digite o valor do IPCA: ");
        print_line();
        ind->SELIC = lerDouble("Digite o valor da SELIC: ");
        print_line();
        grupo->num_inds++;
        printf("Indice criado com sucesso, id: %d | nome: %s  !\n", ind->id, ind->nome);
    } else {
        printf("Erro: Limite maximo de indicadores atingido (100).\n");
}
};


void listarIndicadores(struct GroupIndicFinanc *grupo) {
    if (grupo->num_inds == 0) {
        printf("Nenhum indicador cadastrado.\n");
        return;
    }

    printf("Listando todos os indicadores:\n");
    print_line();
    printf(" ID | Nome                           | CDI   | IPCA  | SELIC |\n");
    print_line();

    for (int i = 0; i < grupo->num_inds; i++) {
        struct IndicFinanc *ind = &grupo->indices[i];
        printf(" %2d | %-30s | %-5.2lf | %-5.2lf | %-5.2lf |\n",
               i+1, ind->nome, ind->CDI, ind->IPCA, ind->SELIC);
    }

    print_line();
}

void excluirIndicador(struct GroupIndicFinanc *grupo) {
    if (grupo->num_inds == 0) {
        printf("Nenhum indicador cadastrado.\n");
        return;
    }

    listarIndicadores(grupo);
    int id = lerInteiro("Digite o ID do indicador que deseja excluir: ");
    

    if (id < 1 || id > grupo->num_inds) {
        printf("ID de indicador inválido.\n");
        return;
    }

    // Deslocar os elementos subsequentes para a esquerda
    for (int i = id - 1; i < grupo->num_inds - 1; i++) {
        grupo->indices[i] = grupo->indices[i + 1];
    }

    grupo->num_inds--;
    printf("Indicador excluido com sucesso!\n");
}


void gravarInvestimentos(struct Investimentos *invest, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb"); // Abre o arquivo para escrita binária
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve o número total de investimentos
    fwrite(&invest->num_invests, sizeof(int), 1, arquivo);

    // Escreve cada investimento no arquivo
    fwrite(invest->invests, sizeof(struct rendFix), invest->num_invests, arquivo);

    fclose(arquivo);
    printf("Investimentos gravados com sucesso em '%s'.\n", nomeArquivo);
};

void carregarInvestimentos(struct Investimentos *invest, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb"); // Abre o arquivo para leitura binária
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo para leitura.\n");
        return;
    }

    fread(&invest->num_invests, sizeof(int), 1, arquivo);     // Lê o número total de investimentos
    fread(invest->invests, sizeof(struct rendFix), invest->num_invests, arquivo); // Lê cada investimento do arquivo

    fclose(arquivo);
    printf("Investimentos carregados com sucesso de '%s'.\n", nomeArquivo);
};

void gravarIndicadores(struct GroupIndicFinanc *grupo, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    fwrite(&grupo->num_inds, sizeof(int), 1, arquivo);
    fwrite(grupo->indices, sizeof(struct IndicFinanc), grupo->num_inds, arquivo);

    fclose(arquivo);
    printf("Indicadores financeiros gravados com sucesso em '%s'.\n", nomeArquivo);
};

void carregarIndicadores(struct GroupIndicFinanc *grupo, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo para leitura.\n");
        return;
    }

    fread(&grupo->num_inds, sizeof(int), 1, arquivo);
    fread(grupo->indices, sizeof(struct IndicFinanc), grupo->num_inds, arquivo);

    fclose(arquivo);
    printf("Indicadores financeiros carregados com sucesso de '%s'.\n", nomeArquivo);
};


void simularInvestimento(struct Investimentos *invest, struct GroupIndicFinanc *grupo) {
    double aporte_inicial, aporte_mensal, taxa_rendimento, composer_rendimento;
    limparBuffer();
    aporte_inicial = lerDouble("Digite o aporte inicial:  ");
    aporte_mensal = lerDouble("Digite o aporte mensal se existir:  ");

    print_line();
    printf("Calculo de investimento para:\nAPORTE INICIAL: R$ %.2f \nAPORTE MENSAL: R$%.2f \n", aporte_inicial, aporte_mensal);
    


    for (int g = 0; g < grupo->num_inds; g++) {
        struct IndicFinanc *ind = &grupo->indices[g];
        print_line();
        printf("Previsao indicadores-> %s", ind->nome);
        printf("\n| NOME                           |  TIPO (a.a.)         |  %% INDICE   |   PRAZO   | MONTANTE FINAL |  LUCRO LIQUIDO |\n");
        
        for (int i = 0; i < invest->num_invests; i++) {
            struct rendFix *rf = &invest->invests[i];

            taxa_rendimento = 0;
            composer_rendimento = 0;

            if (rf->indicador == 0) {
                composer_rendimento = 1;
            } else if (rf->indicador == 1) { // CDI
                composer_rendimento = ind->CDI;
            } else if (rf->indicador == 2) { // IPCA
                composer_rendimento = ind->IPCA;
            } else if (rf->indicador == 3) { // SELIC
                composer_rendimento = ind->SELIC;
            }

            if (rf->operador == 0) {
                taxa_rendimento = composer_rendimento * rf->rentabilidade_taxa;
            }
            else if (rf->operador == 1) {
                taxa_rendimento = composer_rendimento + rf->rentabilidade_taxa;
            } 
            else if (rf->operador == 2) {
                taxa_rendimento = rf->rentabilidade_taxa * composer_rendimento;
            }

            double montante = aporte_inicial;
            double taxa_mensal = taxa_rendimento / 12 / 100;
            double ir_mensal = rf->imposto_renda / 100;
            int total_meses = rf->prazo * 12;          //juro composto (aporte inicial * 1 + taxa rendimento)^tempo (anos, meses)
            double lucro_mensal = 0;                    
            double lucro_liquido_mensal;
            char tipo[50];

            for (int j = 0; j < total_meses; j++) {
                if (j > 0){
                    montante += aporte_mensal;
                }
                lucro_mensal = montante * taxa_mensal;
                lucro_liquido_mensal = lucro_mensal * (1 - ir_mensal);
                montante += lucro_liquido_mensal;
            }

            double lucro = montante - (aporte_inicial + (total_meses * aporte_mensal));

            if (rf->operador == 0) {
                sprintf(tipo, "%.2lf%%", rf->rentabilidade_taxa);
            } else if (rf->operador == 1) {
                sprintf(tipo, "%s + %.2lf%%", (rf->indicador == 1 ? "CDI" : (rf->indicador == 2 ? "IPCA" : "SELIC")), rf->rentabilidade_taxa);
            } else if (rf->operador == 2) {
                sprintf(tipo, "%.2lf%% %s", rf->rentabilidade_taxa, (rf->indicador == 1 ? "CDI" : (rf->indicador == 2 ? "IPCA" : "SELIC")));
            }

            if (composer_rendimento == 1){
                printf("| %-30s | %-20s | Pré-fixado  |  %-3d ANOS |   R$ %-10.2f| R$ %-10.2f  |\n", rf->nome, tipo, rf->prazo, montante, lucro);
            }
            else {
                printf("| %-30s | %-20s | %-5.2f%% a.a. |  %-3d ANOS |   R$ %-10.2f| R$ %-10.2f  |\n", rf->nome, tipo, composer_rendimento, rf->prazo, montante, lucro);
            }
            print_line();
            
        }
    }
}


void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}