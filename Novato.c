#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura da sala (nó da árvore)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Cria dinamicamente uma sala com o nome informado
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória para a sala.\n");
        exit(1);
    }
    strncpy(novaSala->nome, nome, sizeof(novaSala->nome) - 1);
    novaSala->nome[sizeof(novaSala->nome) - 1] = '\0';
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Libera recursivamente a árvore (todas as salas)
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

/*
  Permite a exploração a partir de salaInicial.
  Retorna 0 se a exploração terminou naturalmente (chegou em nó-folha),
  retorna 1 se o jogador saiu manualmente pressionando 's' (sair).
*/
int explorarSalas(Sala* salaInicial) {
    Sala* atual = salaInicial;
    char entrada[100];

    while (1) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        // Se chegou a um nó-folha, fim da exploração
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou ao fim da exploração!\n");
            printf("Esta sala não possui mais caminhos — é um nó-folha da mansão.\n");
            printf("Missão encerrada com sucesso!\n");
            return 0;
        }

        // Mostra opções disponíveis
        printf("Escolha o caminho:\n");
        if (atual->esquerda != NULL)
            printf(" (e) Ir para a esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita != NULL)
            printf(" (d) Ir para a direita -> %s\n", atual->direita->nome);
        printf(" (s) Sair da exploração\n");
        printf("Digite sua escolha: ");

        // Leitura segura de entrada (consome a linha inteira)
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }

        // Pega primeiro caractere não-espaço
        char escolha = '\0';
        for (size_t i = 0; entrada[i] != '\0'; ++i) {
            if (!isspace((unsigned char)entrada[i])) {
                escolha = (char) toupper((unsigned char)entrada[i]);
                break;
            }
        }

        // Processa escolha
        if (escolha == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Não há caminho para a esquerda. Escolha novamente.\n");
            }
        } else if (escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Não há caminho para a direita. Escolha novamente.\n");
            }
        } else if (escolha == 'S') {
            printf("Você optou por sair da exploração.\n");
            return 1; // sinaliza saída voluntária
        } else {
            printf("Entrada inválida. Digite 'e', 'd' ou 's'.\n");
        }
    }
}

// Função principal: monta a árvore, inicia exploração e libera memória
int main() {
    // Montagem manual da árvore (mapa da mansão)
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* jardim = criarSala("Jardim");
    Sala* biblioteca = criarSala("Biblioteca");

    // Estrutura da árvore (mansão)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = jardim;
    salaEstar->direita = biblioteca;
    // cozinha, jardim e biblioteca são nós-folha neste mapa

    printf("Bem-vindo ao Detective Quest!\n");
    printf("Explore a mansão e descubra o caminho.\n");
    printf("Use 'e' para esquerda, 'd' para direita e 's' para sair.\n");

    int saiu = explorarSalas(hall);

    if (saiu) {
        printf("\nExploração encerrada pelo jogador.\n");
    } else {
        printf("\nExploração concluída (chegou em um nó-folha).\n");
    }

    // Libera toda a memória antes de encerrar
    liberarArvore(hall);

    return 0;
}


