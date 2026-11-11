/*
 * PSE em Acao - Sistema de Planejamento e Acompanhamento
 * de Acoes de Saude na Escola
 *
 * AEP - 2o semestre de 2026 - Engenharia de Software (ESOFT2S)
 * UniCesumar
 *
 * Integrantes:
 *   Miguel de Souza Rodrigues - RA 26000989-2
 *   Antonio Augusto Fuggi     - RA 26003652-2
 *   Rafael Lacava Rampazzo    - RA 26001885-2
 *
 * O sistema guarda apenas informacoes coletivas sobre as acoes.
 * Nenhum dado de estudante (nome, diagnostico, prontuario) e cadastrado.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ACOES 100
#define TAM_TEXTO 61

#define PLANEJADA 1
#define REALIZADA 2
#define CANCELADA 3

#define TOTAL_TEMAS 14
#define TOTAL_PUBLICOS 6

struct Acao {
    int codigo;
    char escola[TAM_TEXTO];
    int tema;
    int dia;
    int mes;
    int ano;
    int publico_alvo;
    char responsavel[TAM_TEXTO];
    int previstos;
    int efetivos;
    int situacao;
};

/* Variaveis globais: o vetor de acoes e a quantidade cadastrada */
struct Acao acoes[MAX_ACOES];
int total_acoes = 0;

/* As 14 tematicas do PSE (Nota Tecnica n. 30/2024 do Ministerio da Saude) */
const char *temas[TOTAL_TEMAS] = {
    "Saude ambiental",
    "Promocao da atividade fisica",
    "Alimentacao saudavel e prevencao da obesidade",
    "Promocao da cultura de paz e direitos humanos",
    "Prevencao das violencias e dos acidentes",
    "Prevencao de doencas negligenciadas",
    "Verificacao da situacao vacinal",
    "Saude sexual e reprodutiva",
    "Prevencao ao uso de alcool, tabaco e outras drogas",
    "Saude bucal",
    "Saude auditiva",
    "Saude ocular",
    "Prevencao a Covid-19",
    "Saude mental"
};

const char *publicos[TOTAL_PUBLICOS] = {
    "Educacao Infantil",
    "Ensino Fundamental - anos iniciais",
    "Ensino Fundamental - anos finais",
    "Ensino Medio",
    "Educacao de Jovens e Adultos (EJA)",
    "Comunidade escolar (familias e profissionais)"
};

/* ---------- Funcoes de apoio para leitura do teclado ---------- */

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* Le um numero inteiro. Se o usuario digitar letras, pede de novo. */
int ler_inteiro() {
    int numero;
    while (scanf("%d", &numero) != 1) {
        limpar_buffer();
        printf("Entrada invalida. Digite apenas numeros: ");
    }
    limpar_buffer();
    return numero;
}

/* Le uma linha de texto (aceita espacos) e tira o "enter" do final. */
void ler_texto(char texto[], int tamanho) {
    int i;
    if (fgets(texto, tamanho, stdin) == NULL) {
        texto[0] = '\0';
        return;
    }
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            texto[i] = '\0';
            return;
        }
    }
    /* Se o texto for maior que o campo, descarta o que sobrou */
    limpar_buffer();
}

/* Retorna 1 se o texto estiver vazio ou so tiver espacos. */
int texto_vazio(char texto[]) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

/* Copia o texto convertendo todas as letras para minusculas. */
void para_minusculas(char destino[], char origem[]) {
    int i;
    for (i = 0; origem[i] != '\0'; i++) {
        destino[i] = tolower(origem[i]);
    }
    destino[i] = '\0';
}

/* Procura uma acao pelo codigo. Retorna a posicao no vetor ou -1. */
int buscar_posicao_por_codigo(int codigo) {
    int i;
    for (i = 0; i < total_acoes; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

/* ---------- Funcoes de exibicao ---------- */

void exibir_lista_temas() {
    int i;
    printf("\nTematicas do PSE:\n");
    for (i = 0; i < TOTAL_TEMAS; i++) {
        printf("  %2d - %s\n", i + 1, temas[i]);
    }
}

void exibir_lista_publicos() {
    int i;
    printf("\nPublico-alvo:\n");
    for (i = 0; i < TOTAL_PUBLICOS; i++) {
        printf("  %d - %s\n", i + 1, publicos[i]);
    }
}

const char *nome_situacao(int situacao) {
    if (situacao == PLANEJADA) {
        return "Planejada";
    } else if (situacao == REALIZADA) {
        return "Realizada";
    } else {
        return "Cancelada";
    }
}

void exibir_acao(int i) {
    printf("----------------------------------------------------\n");
    printf("Codigo ........: %d\n", acoes[i].codigo);
    printf("Escola ........: %s\n", acoes[i].escola);
    printf("Tema ..........: %s\n", temas[acoes[i].tema - 1]);
    printf("Data prevista .: %02d/%02d/%04d\n", acoes[i].dia, acoes[i].mes, acoes[i].ano);
    printf("Publico-alvo ..: %s\n", publicos[acoes[i].publico_alvo - 1]);
    printf("Responsavel ...: %s\n", acoes[i].responsavel);
    printf("Previstos .....: %d participantes\n", acoes[i].previstos);
    if (acoes[i].situacao == REALIZADA) {
        printf("Efetivos ......: %d participantes\n", acoes[i].efetivos);
    }
    printf("Situacao ......: %s\n", nome_situacao(acoes[i].situacao));
}

/* ---------- Funcionalidades do menu ---------- */

void cadastrar_acao() {
    int codigo, tema, dia, mes, ano, publico_alvo, previstos;
    char escola[TAM_TEXTO];
    char responsavel[TAM_TEXTO];
    char data[20];
    int valido;

    printf("\n===== CADASTRAR ACAO =====\n");

    if (total_acoes >= MAX_ACOES) {
        printf("Limite de armazenamento atingido (%d acoes). Nao e possivel cadastrar.\n", MAX_ACOES);
        return;
    }

    /* Codigo: positivo e sem repeticao */
    do {
        printf("Informe o codigo da acao: ");
        codigo = ler_inteiro();
        valido = 1;
        if (codigo <= 0) {
            printf("O codigo deve ser um numero positivo.\n");
            valido = 0;
        } else if (buscar_posicao_por_codigo(codigo) != -1) {
            printf("Codigo ja cadastrado. Informe outro codigo.\n");
            valido = 0;
        }
    } while (valido == 0);

    /* Escola: obrigatoria */
    do {
        printf("Informe a escola: ");
        ler_texto(escola, TAM_TEXTO);
        if (texto_vazio(escola)) {
            printf("Campo obrigatorio.\n");
        }
    } while (texto_vazio(escola));

    /* Tema: escolhido na lista */
    do {
        exibir_lista_temas();
        printf("Escolha o tema (1 a %d): ", TOTAL_TEMAS);
        tema = ler_inteiro();
        if (tema < 1 || tema > TOTAL_TEMAS) {
            printf("Tema invalido.\n");
        }
    } while (tema < 1 || tema > TOTAL_TEMAS);

    /* Data prevista no formato dd/mm/aaaa */
    do {
        printf("Informe a data prevista (dd/mm/aaaa): ");
        ler_texto(data, 20);
        valido = 1;
        if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
            valido = 0;
        } else if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 2000 || ano > 2100) {
            valido = 0;
        }
        if (valido == 0) {
            printf("Data invalida. Use o formato dd/mm/aaaa.\n");
        }
    } while (valido == 0);

    /* Publico-alvo: escolhido na lista */
    do {
        exibir_lista_publicos();
        printf("Escolha o publico-alvo (1 a %d): ", TOTAL_PUBLICOS);
        publico_alvo = ler_inteiro();
        if (publico_alvo < 1 || publico_alvo > TOTAL_PUBLICOS) {
            printf("Opcao invalida.\n");
        }
    } while (publico_alvo < 1 || publico_alvo > TOTAL_PUBLICOS);

    /* Responsavel: equipe ou funcao, nunca nome de estudante */
    do {
        printf("Informe a equipe ou funcao responsavel (sem nomes de estudantes): ");
        ler_texto(responsavel, TAM_TEXTO);
        if (texto_vazio(responsavel)) {
            printf("Campo obrigatorio.\n");
        }
    } while (texto_vazio(responsavel));

    /* Quantidade prevista: maior que zero */
    do {
        printf("Informe a quantidade prevista de participantes: ");
        previstos = ler_inteiro();
        if (previstos <= 0) {
            printf("A quantidade deve ser maior que zero.\n");
        }
    } while (previstos <= 0);

    /* Tudo validado: grava no vetor */
    acoes[total_acoes].codigo = codigo;
    strcpy(acoes[total_acoes].escola, escola);
    acoes[total_acoes].tema = tema;
    acoes[total_acoes].dia = dia;
    acoes[total_acoes].mes = mes;
    acoes[total_acoes].ano = ano;
    acoes[total_acoes].publico_alvo = publico_alvo;
    strcpy(acoes[total_acoes].responsavel, responsavel);
    acoes[total_acoes].previstos = previstos;
    acoes[total_acoes].efetivos = 0;
    acoes[total_acoes].situacao = PLANEJADA;
    total_acoes++;

    printf("\nAcao cadastrada com sucesso! Situacao inicial: Planejada.\n");
}

void listar_acoes() {
    int i;

    printf("\n===== LISTA DE ACOES =====\n");

    if (total_acoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    for (i = 0; i < total_acoes; i++) {
        exibir_acao(i);
    }
    printf("----------------------------------------------------\n");
    printf("Total: %d acao(oes) cadastrada(s).\n", total_acoes);
}

void pesquisar_acao() {
    int criterio, busca_numero, encontrados, i;
    char busca_texto[TAM_TEXTO];
    char busca_minuscula[TAM_TEXTO];
    char escola_minuscula[TAM_TEXTO];

    printf("\n===== PESQUISAR ACAO =====\n");

    if (total_acoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("Pesquisar por: 1 - Codigo | 2 - Escola | 3 - Tema\n");
    printf("Opcao: ");
    criterio = ler_inteiro();

    if (criterio < 1 || criterio > 3) {
        printf("Opcao invalida.\n");
        return;
    }

    busca_numero = 0;
    if (criterio == 1) {
        printf("Informe o codigo: ");
        busca_numero = ler_inteiro();
    } else if (criterio == 2) {
        printf("Informe o nome ou parte do nome da escola: ");
        ler_texto(busca_texto, TAM_TEXTO);
        para_minusculas(busca_minuscula, busca_texto);
    } else {
        exibir_lista_temas();
        printf("Escolha o tema (1 a %d): ", TOTAL_TEMAS);
        busca_numero = ler_inteiro();
    }

    encontrados = 0;
    for (i = 0; i < total_acoes; i++) {
        if (criterio == 1 && acoes[i].codigo == busca_numero) {
            exibir_acao(i);
            encontrados++;
        } else if (criterio == 2) {
            para_minusculas(escola_minuscula, acoes[i].escola);
            if (strstr(escola_minuscula, busca_minuscula) != NULL) {
                exibir_acao(i);
                encontrados++;
            }
        } else if (criterio == 3 && acoes[i].tema == busca_numero) {
            exibir_acao(i);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum registro encontrado.\n");
    } else {
        printf("----------------------------------------------------\n");
        printf("%d registro(s) encontrado(s).\n", encontrados);
    }
}

void atualizar_situacao() {
    int codigo, posicao, nova_situacao, efetivos;

    printf("\n===== ATUALIZAR SITUACAO =====\n");

    if (total_acoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("Informe o codigo da acao: ");
    codigo = ler_inteiro();
    posicao = buscar_posicao_por_codigo(codigo);

    if (posicao == -1) {
        printf("Acao nao encontrada.\n");
        return;
    }

    printf("Acao encontrada: %s\n", acoes[posicao].escola);
    printf("Tema: %s | Situacao atual: %s\n",
           temas[acoes[posicao].tema - 1], nome_situacao(acoes[posicao].situacao));
    printf("Nova situacao: 1 - Planejada | 2 - Realizada | 3 - Cancelada\n");
    printf("Opcao: ");
    nova_situacao = ler_inteiro();

    if (nova_situacao == PLANEJADA) {
        acoes[posicao].situacao = PLANEJADA;
        acoes[posicao].efetivos = 0;
    } else if (nova_situacao == REALIZADA) {
        do {
            printf("Informe a quantidade efetiva de participantes: ");
            efetivos = ler_inteiro();
            if (efetivos < 0) {
                printf("A quantidade nao pode ser negativa.\n");
            }
        } while (efetivos < 0);
        acoes[posicao].situacao = REALIZADA;
        acoes[posicao].efetivos = efetivos;
    } else if (nova_situacao == CANCELADA) {
        acoes[posicao].situacao = CANCELADA;
        acoes[posicao].efetivos = 0;
    } else {
        printf("Opcao invalida. Nada foi alterado.\n");
        return;
    }

    printf("Situacao atualizada com sucesso para: %s.\n", nome_situacao(nova_situacao));
}

void gerar_resumo() {
    int planejadas = 0, realizadas = 0, canceladas = 0;
    int soma_previstos = 0, soma_efetivos = 0;
    float percentual;
    int i;

    printf("\n===== RESUMO GERAL =====\n");

    if (total_acoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    for (i = 0; i < total_acoes; i++) {
        if (acoes[i].situacao == PLANEJADA) {
            planejadas++;
        } else if (acoes[i].situacao == REALIZADA) {
            realizadas++;
            soma_previstos = soma_previstos + acoes[i].previstos;
            soma_efetivos = soma_efetivos + acoes[i].efetivos;
        } else if (acoes[i].situacao == CANCELADA) {
            canceladas++;
        }
    }

    /* Evita divisao por zero quando ainda nao ha acao realizada */
    if (soma_previstos > 0) {
        percentual = (float) soma_efetivos / soma_previstos * 100;
    } else {
        percentual = 0;
    }

    printf("Total de acoes cadastradas ..............: %d\n", total_acoes);
    printf("Planejadas ..............................: %d\n", planejadas);
    printf("Realizadas ..............................: %d\n", realizadas);
    printf("Canceladas ..............................: %d\n", canceladas);
    printf("Participantes previstos (acoes realizadas): %d\n", soma_previstos);
    printf("Participantes efetivos ..................: %d\n", soma_efetivos);
    printf("Percentual de participacao ..............: %.1f%%\n", percentual);
}

void resumo_por_escola() {
    int total_escolas = 0, escolas_atendidas = 0;
    int qtd_acoes, qtd_realizadas, soma_efetivos;
    int ja_contada;
    float percentual;
    int i, j, k;

    printf("\n===== RESUMO POR ESCOLA =====\n");

    if (total_acoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    for (i = 0; i < total_acoes; i++) {
        /* Verifica se esta escola ja apareceu antes no vetor */
        ja_contada = 0;
        for (j = 0; j < i; j++) {
            if (strcmp(acoes[j].escola, acoes[i].escola) == 0) {
                ja_contada = 1;
            }
        }

        if (ja_contada == 0) {
            total_escolas++;
            qtd_acoes = 0;
            qtd_realizadas = 0;
            soma_efetivos = 0;

            for (k = i; k < total_acoes; k++) {
                if (strcmp(acoes[k].escola, acoes[i].escola) == 0) {
                    qtd_acoes++;
                    if (acoes[k].situacao == REALIZADA) {
                        qtd_realizadas++;
                        soma_efetivos = soma_efetivos + acoes[k].efetivos;
                    }
                }
            }

            printf("\n%s\n", acoes[i].escola);
            printf("  Acoes: %d | Realizadas: %d | Participantes: %d\n",
                   qtd_acoes, qtd_realizadas, soma_efetivos);

            if (qtd_realizadas > 0) {
                escolas_atendidas++;
            } else {
                printf("  ATENCAO: nenhuma acao realizada nesta escola.\n");
            }
        }
    }

    percentual = (float) escolas_atendidas / total_escolas * 100;
    printf("\nEscolas com ao menos uma acao realizada: %d de %d (%.1f%%)\n",
           escolas_atendidas, total_escolas, percentual);
}

/* ---------- Programa principal ---------- */

void exibir_menu() {
    printf("\n========== PSE EM ACAO ==========\n");
    printf("1 - Cadastrar acao\n");
    printf("2 - Listar acoes\n");
    printf("3 - Pesquisar acao\n");
    printf("4 - Atualizar situacao e participantes\n");
    printf("5 - Gerar resumo geral\n");
    printf("6 - Gerar resumo por escola\n");
    printf("7 - Encerrar\n");
    printf("=================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;

    do {
        exibir_menu();
        opcao = ler_inteiro();

        switch (opcao) {
            case 1:
                cadastrar_acao();
                break;
            case 2:
                listar_acoes();
                break;
            case 3:
                pesquisar_acao();
                break;
            case 4:
                atualizar_situacao();
                break;
            case 5:
                gerar_resumo();
                break;
            case 6:
                resumo_por_escola();
                break;
            case 7:
                printf("\nEncerrando o sistema. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
