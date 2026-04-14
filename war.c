// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 


// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

struct Territorio {
    char nome [30];
    char cor [10];
    int tropas;
};


// --- Protótipos das Funções ---


// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função Exibir territórios
void exibirTerritorios(struct Territorio *lista, int total) {
    if (total == 0) {
        printf("\nNenhum território cadastrado ainda.\n");
        return; 
    }

    printf("\n============================================\n");
    printf(" MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("============================================\n\n");

     for (int i = 0; i < total; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, lista[i].nome, lista[i].cor, lista[i].tropas);
        }
    
}
// Função Simular ataque
void simularAtaque(struct Territorio *lista, int total) {

    int atacante, defensor;
    


    if (total < 2) {
        printf("\nErro: Você precisa de pelo menos 2 territórios para atacar!\n");
        return;
    }
       
    
    // Escolha dos oponentes
    printf("\n--- SIMULAÇÃO DE ATAQUE ---\n");
    printf("\nEscolha o território atacante (1 a %d) ou 0 para sair: ", total);
    scanf("%d", &atacante);

    // Verifica se o atacante quer seguir com o ataque
    if (atacante == 0) {
        printf("\nAtaque Cancelado.\n");
        limparBufferEntrada();
        exit(0);
        return;
    }

    printf("Escolha o território defensor (1 a %d) ou 0 para sair: ", total);
    scanf("%d", &defensor);

    // Verifica se o defensor quer seguir com a defesa
    if (defensor == 0) {
        printf("\nAtaque Cancelado.\n");
        limparBufferEntrada();
        exit(0);
        return;
    }
    limparBufferEntrada();

    // Verifica se os territórios existem
    if (atacante > total || defensor > total || atacante < 0 || defensor < 0) {
        printf("\nErro: Territorio não existe\n");
        return;
    }

    int a = atacante - 1;
    int d = defensor - 1;

    //Não pode atacar a si mesmo
    if (a == d) {
        printf("\nErro: Um territorio não pode atacar a si mesmo!\n");
        return;
    }
    //precisa de no minimo 2 tropas para atacar
   if (lista[a].tropas <= 1){
        printf("\nErro: O atacante %s tem apenas %d tropa(s). Precisa de no minimo 2!\n", lista[a].nome, lista[a].tropas);
        return;
    }
    //Território derrotado
    if (lista[d].tropas <= 0) {
        printf("\nErro: O territorio %s já foi derrotado e não tem mais tropas para defender!\n", lista[d].nome);
        return;
    }
    
    //Laçamento dos DADOS
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nO atacante %s rolou um dado e tirou: %d", lista[a].nome, dadoAtacante);
    printf("\nO defensor %s rolou um dado e tirou: %d", lista[d].nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nVITORIA DO ATAQUE! %s perdeu 1 tropa.", lista[d].nome);
        lista[d].tropas--;
        //Conquista do territorio
        if (lista[d].tropas == 0) {
        printf("\n\n*********************************************");
        printf("\n    CONQUISTA! O terrritorio %s foi dominado pelo %s", lista[d].nome, lista[a].nome);
        printf("\n*********************************************");
        }
    } else {
        printf("\nVITORIA DA DEFESA! %s perdeu 1 tropa.", lista[a].nome);
        lista[a].tropas--;
    }
    printf("\n\n");

}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    struct Territorio *territorios = NULL; // Começa vazio 
    int totalterritorios = 0;
    int opcao;
    srand(time(NULL));

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    
    // ---- Laço Principal do Menu ---
    
        
    printf("\n========================================\n");
    printf("   WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("========================================\n\n");
    printf("\n\n");


    while (1) {
        char nomeTemp[30];

        printf("--- Cadastro do %dº Territorio ---\n\n", totalterritorios + 1);

        printf("Nome do Territorio (ou 'o' para sair): ");
        fgets(nomeTemp, 30, stdin);
        nomeTemp[strcspn(nomeTemp, "\n")] = '\0';

        if (strcmp(nomeTemp, "0") == 0) {
            if (totalterritorios < 2) {
                printf("Você precisa de pelo menos 2 territórios para jogar! Continue cadastrando.\n\n");
                continue;
            }
            break;
        }

        // Cria espaço novo para caber o território que já existem + 1 novo
        struct Territorio *novoEspaco = (struct Territorio*) malloc((totalterritorios + 1) * sizeof(struct Territorio));

        if (novoEspaco == NULL) {
            printf("Erro: Falha ao alocar memoria.\n");
            return 1; //Retorna 1 para indicar um erro.
        }

        // Se já existir território, copiamos eles para o novo espaço
        for (int j = 0; j < totalterritorios; j++) {
            novoEspaco[j] = territorios[j];
        }
        
        strcpy(novoEspaco[totalterritorios].nome, nomeTemp);
       
        printf("Digite a cor do exército: ");
        fgets(novoEspaco[totalterritorios].cor, 10, stdin);
        novoEspaco[totalterritorios].cor[strcspn(novoEspaco[totalterritorios].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &novoEspaco[totalterritorios].tropas);
        printf("\n\n");
        limparBufferEntrada();

        // Retorna um ponteiro para a memória alocada ou NULL em caso de falha.
        if (territorios != NULL) {
            free(territorios);
        }
        // Aponta o ponteiro principal para o novo endereço
        territorios = novoEspaco;
        totalterritorios++;

    }
    
    //Mostra os territorios cadastrados
    exibirTerritorios(territorios, totalterritorios);

    //Simular ataque

    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        simularAtaque(territorios, totalterritorios);
        exibirTerritorios(territorios, totalterritorios);
        printf("\nDeseja ir para o proximo turno? (s/n): ");
        scanf(" %c", &continuar);
        limparBufferEntrada();
    }        

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
    
    if (territorios != NULL) free(territorios);
    printf("\nFim de jogo!\n\n");

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.


// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
