// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
////==========================================================================
// MISSÃO: 
// Modularização: Implementar as funções exibir_mapa, realizar_ataque e verificar_vitoria;
// Missões: Crias sistema com até 3 missões, com sorteio de missões;
// Criar uma função de verificação de vitória, onde irá analisar se as condições das missões foram cumpridas
//
// =========================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

// --- Definição de Estrutura (Struct) ---

struct Territorio {
    char nome [30];
    char cor [10];
    int tropas;
};

// --- Protótipos das Funções ---
void limparBufferEntrada();
void exibirTerritorios(struct Territorio *lista, int total);
void simularAtaque(struct Territorio *lista, int total, int atacante, int defensor);
int verificarVitoria(struct Territorio *lista, int total, int idMissao, char *minhaCor, char *corAlvo);
void exibirMissoes();
int sortearMissao();
int corValida(char *texto);

// Lista de missões
const char *missoes[] = {
    "Destruir Exercito.",
    "Conquistar 3 territorios.",
    "Ter pelo menos 10 topas no total do seu exercito."
};


int main() {
    struct Territorio *territorios = NULL;
    int totalterritorios = 0;
    int opcaoMenu;
    int atacante, defensor, missaoEscolhida;
    char minhaCor[10];
    char corAlvo[10] = "";

    srand(time(NULL));

    // ---- Laço Principal do Menu ---
    // Cadastro dos territórios
    printf("\n========================================\n");
    printf("   WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("========================================\n\n");

    while (1) {
        char nomeTemp[30];
        int validaCor;

        printf("--- Cadastro do %dº Territorio ---\n\n", totalterritorios + 1);
        printf("Nome do Territorio (ou '0' para sair): ");
        fgets(nomeTemp, 30, stdin);
        nomeTemp[strcspn(nomeTemp, "\n")] = '\0';

        if (strcmp(nomeTemp, "0") == 0) { // precisa pelo menos 2 terrítorios para jogar
            if (totalterritorios < 2) {
                printf("Você precisa de pelo menos 2 territórios para jogar! Continue cadastrando.\n\n");
                continue;
            }
            break;
        }
        // Cria espaço novo para caber o território que já existem + 1 novo
        struct Territorio *novoEspaco = malloc((totalterritorios + 1) * sizeof(struct Territorio));

        if (novoEspaco == NULL) {
            printf("Erro: Falha ao alocar memoria.\n");
            return 1;
        }
        // Se já existir território, copiamos eles para o novo espaço
        for (int j = 0; j < totalterritorios; j++) {
            novoEspaco[j] = territorios[j];
        }

        strcpy(novoEspaco[totalterritorios].nome, nomeTemp);

        do { // Validação da Cor
            printf("Digite a cor do exército: ");
            fgets(novoEspaco[totalterritorios].cor, 10, stdin);
            novoEspaco[totalterritorios].cor[strcspn(novoEspaco[totalterritorios].cor, "\n")] = '\0';

            validaCor = corValida(novoEspaco[totalterritorios].cor);

            if (!validaCor) {
                printf("Erro: digite apenas texto para a cor.\n");
            }

        } while (!validaCor);

        printf("Quantidade de tropas: ");
        scanf("%d", &novoEspaco[totalterritorios].tropas);
        limparBufferEntrada();
        printf("\n");
        // Libera o espaço antigo para não vazar memória
        if (territorios != NULL) {
            free(territorios);
        }
        // Aponta o ponteiro principal para o novo endereço
        territorios = novoEspaco;
        totalterritorios++;
    }

    exibirMissoes(); // Exibe missões
    printf("\nEscolha uma missao inicial (1 a 3): ");
    scanf("%d", &missaoEscolhida);
    limparBufferEntrada();

    while (missaoEscolhida < 1 || missaoEscolhida > 3) {
        printf("Missao invalida. Escolha uma missao de 1 a 3: ");
        scanf("%d", &missaoEscolhida);
        limparBufferEntrada();
    }

    missaoEscolhida--; // transforma 1..3 em 0..2


    do { // Laço do Jogo
        exibirTerritorios(territorios, totalterritorios);

        printf("\n=========== MENU DO JOGO ===========\n");
        printf("1. Realizar ataque\n");
        printf("2. Escolher outra missao\n");
        printf("0. Sair do jogo\n");
        printf("====================================\n");
        printf("Escolha: ");
        scanf("%d", &opcaoMenu);
        limparBufferEntrada();

        if (opcaoMenu == 1) { // 1ª opção (Realizar ataque)
            printf("\nEscolha o território atacante (1 a %d) ou 0 para sair: ", totalterritorios);
            scanf("%d", &atacante);

            if (atacante == 0) {
                opcaoMenu = 0;
                break;
            }

            while (atacante < 1 || atacante > totalterritorios) {
                printf("Território atacante inválido. Escolha novamente: ");
                scanf("%d", &atacante);
            }

            printf("Escolha o território defensor (1 a %d) ou 0 para sair: ", totalterritorios);
            scanf("%d", &defensor);

            if (defensor == 0) {
                opcaoMenu = 0;
                break;
            }

            while (defensor < 1 || defensor > totalterritorios) {
                printf("Território defensor inválido. Escolha novamente: ");
                scanf("%d", &defensor);
            }

            limparBufferEntrada();

            strcpy(minhaCor, territorios[atacante - 1].cor);

            if (missaoEscolhida == 0) {
                strcpy(corAlvo, territorios[defensor - 1].cor);
            }
            // Chama a função simular ataque
            simularAtaque(territorios, totalterritorios, atacante, defensor);
            // Verifica quem ganhou
            if (verificarVitoria(territorios, totalterritorios, missaoEscolhida, minhaCor, corAlvo)) {
            break;
            }
        }
        else if (opcaoMenu == 2) { // Volta para o menu de escolha de missões
            exibirMissoes();
            printf("\nEscolha uma nova missao (1 a 3): ");
            scanf("%d", &missaoEscolhida);
            limparBufferEntrada();

            while (missaoEscolhida < 1 || missaoEscolhida > 3) {
                printf("Missao invalida. Escolha uma missao de 1 a 3: ");
                scanf("%d", &missaoEscolhida);
                limparBufferEntrada();
            }

            missaoEscolhida--;
            printf("\nMissao alterada com sucesso!\n");
        }
        else if (opcaoMenu == 0) { // Sai do jogo
            printf("\nSaindo do jogo...\n");
        }
        else {
            printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcaoMenu != 0);

    free(territorios);
    return 0; // Fim do programa
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int corValida(char *texto) { // Valida se a string só contém letras e espaços (sem números ou símbolos)
    int i = 0;

    if (texto[0] == '\0') {
        return 0;
    }

    while (texto[i] != '\0') {
        if (!((texto[i] >= 'A' && texto[i] <= 'Z') ||
              (texto[i] >= 'a' && texto[i] <= 'z') ||
              texto[i] == ' ')) {
            return 0;
        }
        i++;
    }

    return 1;
}

int sortearMissao() {
    return rand() % 3;
}

// Função Exibir territórios
void exibirTerritorios(struct Territorio *lista, int total) {
    printf("\n==================== MAPA DO MUNDO =====================\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %-20s (Exercito: %-10s, Tropas: %2d)\n", i + 1, lista[i].nome, lista[i].cor, lista[i].tropas);
    }
    printf("==========================================================\n");
    
}
// Função Exibir Missões
void exibirMissoes() {
    printf("\n=========== MISSÕES ===========\n");
    printf("1. Destruir Exercito.\n");
    printf("2. Conquistar 3 territorios.\n");
    printf("3. Ter pelo menos 10 tropas no total do seu exercito.\n");
    printf("===============================\n");
}

// Função Verificar Vitória
int verificarVitoria(struct Territorio *lista, int total, int idMissao, char *minhaCor, char *corAlvo) {
    int objetivoCumprido = 0;

    if (idMissao == 0) { // Escolha de destruir exercito
        int inimigoVivo = 0;
        for (int i = 0; i < total; i++) {
            if (strcmp(lista[i].cor, corAlvo) == 0) {
                inimigoVivo++;
                break;
            }
        }
        if (inimigoVivo == 0) {
            objetivoCumprido = 1;
        }
    }
    else if (idMissao == 1) { // Escolha de conquistar 3 territórios
        int contador = 0;
        for (int i = 0; i < total; i++) {
            if (strcmp(lista[i].cor, minhaCor) == 0) {
                contador++;
            }
        }
        if (contador >= 3) {
            objetivoCumprido = 1;
        }
    }
    else if (idMissao == 2) { // Escolho de ter pelo menos 10 tropas no total do seu exercito
        int somaTropas = 0;
        for (int i = 0; i < total; i++) {
            if (strcmp(lista[i].cor, minhaCor) == 0) {
                somaTropas += lista[i].tropas;
            }
        }

        printf("\nTotal de tropas do exercito %s: %d\n", minhaCor, somaTropas);

        if (somaTropas >= 10) {
            objetivoCumprido = 1;
        }
    }

    if (objetivoCumprido) { // Se objetivo cumprido = 1, OBJETIVO CONCLUIDO 
        printf("\n================================================");
        printf("\n       VITORIA! OBJETIVO CONCLUIDO!");
        printf("\n================================================\n");
        return 1;
    }
    else {
        if (idMissao == 0) {// Se objetivo 1 não for cumprido
            printf("\n[STATUS]: Missao em andamento. Alvo: destruir o exercito %s\n", corAlvo);
        }
        else if (idMissao == 1) { // Se objetivo 2 não for cumprido
            int contador = 0;
            for (int i = 0; i < total; i++) {
                if (strcmp(lista[i].cor, minhaCor) == 0) {
                    contador++;
                }
            }
            printf("\n[STATUS]: Missao em andamento. Voce controla %d de 3 territorios.\n", contador);
        }
        else if (idMissao == 2) { // Se objetivo 3 não for cumprido
            int somaTropas = 0;
            for (int i = 0; i < total; i++) {
                if (strcmp(lista[i].cor, minhaCor) == 0) {
                    somaTropas += lista[i].tropas;
                }
            }
            printf("\n[STATUS]: Missao em andamento. Seu exercito possui %d de 10 tropas.\n", somaTropas);
        }

        return 0;
    }
}


// Função Simular ataque
void simularAtaque(struct Territorio *lista, int total, int atacante, int defensor) {
    if (total < 2) {
        printf("\nErro: Você precisa de pelo menos 2 territórios para atacar!\n");
        return;
    }

    // Verifica se os territórios existem
    if (atacante <= 0 || atacante > total || defensor <= 0 || defensor > total) {
        printf("\nErro: Territorio não existe\n");
        return;
    }

    int a = atacante - 1;
    int d = defensor - 1;

    // Não pode atacar a si mesmo
    if (a == d) {
        printf("\nErro: Um territorio não pode atacar a si mesmo!\n");
        return;
    }

    // Precisa de no minimo 2 tropas para atacar
    if (lista[a].tropas <= 1) {
        printf("\nErro: O atacante %s tem apenas %d tropa(s). Precisa de no minimo 2!\n",
               lista[a].nome, lista[a].tropas);
        return;
    }

    // Território derrotado
    if (lista[d].tropas <= 0) {
        printf("\nErro: O territorio %s já foi derrotado e não tem mais tropas para defender!\n",
               lista[d].nome);
        return;
    }

    // Lançamento dos dados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    // Escolha dos oponentes
    printf("\n--- SIMULAÇÃO DE ATAQUE ---\n");
    printf("\nO atacante %s rolou um dado e tirou: %d", lista[a].nome, dadoAtacante);
    printf("\nO defensor %s rolou um dado e tirou: %d", lista[d].nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nVITORIA DO ATAQUE! %s perdeu 1 tropa.", lista[d].nome);
        lista[d].tropas--;

        // Conquista do território
        if (lista[d].tropas == 0) {
            printf("\n\n*********************************************");
            printf("\n    CONQUISTA! O territorio %s foi dominado pelo %s\n",
                   lista[d].nome, lista[a].nome);
            printf("\n*********************************************");

            strcpy(lista[d].cor, lista[a].cor);
            lista[d].tropas = 1;
            lista[a].tropas--;
        }
    }
    else {
        printf("\nVITORIA DA DEFESA! %s perdeu 1 tropa.", lista[a].nome);
        lista[a].tropas--;
    }

    printf("\n\n");
}