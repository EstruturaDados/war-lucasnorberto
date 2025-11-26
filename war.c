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

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// ============================================================================
// --- Constantes Globais ---
// ============================================================================
#define MAX_TERRITORIOS 5
#define MAX_MISSOES 3
#define TAM_NOME 50
#define TAM_COR 20

// ============================================================================
// --- Estrutura de Dados ---
// ============================================================================

// Territorio: Contém as informações de um território no mapa.
typedef struct {
    char nome[TAM_NOME];
    char corExercito[TAM_COR];
    int numTropas;
} Territorio;

// Missao: Descreve o objetivo do jogador.
typedef struct {
    int id;
    char descricao[256];
    char corAlvo[TAM_COR]; // Usado apenas para missões de destruição
    int territoriosAlvo;   // Usado apenas para missões de conquista
} Missao;

// ============================================================================
// --- Protótipos das Funções ---
// ============================================================================

// Funções de setup e gerenciamento de memória:
Territorio* alocarMapa();
void inicializarTerritorios(Territorio *mapa);
void liberarMemoria(Territorio *mapa);
Missao sortearMissao(const char *corJogador);

// Funções de interface com o usuário:
void exibirMenuPrincipal(void);
void exibirMapa(const Territorio *mapa, size_t tamanho);
void exibirMissao(const Missao *missao);

// Funções de lógica principal do jogo:
void faseDeAtaque(Territorio *mapa, const char *corJogador);
void simularAtaque(Territorio *ataque, Territorio *defesa);
int verificarVitoria(const Territorio *mapa, size_t tamanho, const Missao *missao, const char *corJogador);

// Função utilitária:
void limparBufferEntrada(void);

// ============================================================================
// --- Função Principal (main) ---
// ============================================================================
int main() {
    // 1. Configuração Inicial (Setup):
    setlocale(LC_ALL, "Portuguese"); // Define o locale para português.
    srand((unsigned int)time(NULL)); // Inicializa a semente para números aleatórios.

    Territorio *mapa = alocarMapa(); // Aloca a memória para o mapa.
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa.\n");
        return 1;
    }
    
    // Dados iniciais do jogo
    char corJogador[TAM_COR] = "Amarelo"; // Cor do jogador.
    Missao missaoJogador;
    int opcao = -1;
    int vitoria = 0;
    
    inicializarTerritorios(mapa); // Preenche os dados iniciais.
    missaoJogador = sortearMissao(corJogador); // Sorteia a missão.

    printf("Bem-vindo ao WAR Estruturado! Sua cor é: %s\n", corJogador);
    printf("Sua missão secreta foi sorteada.\n");
    
    // 2. Laço Principal do Jogo (Game Loop):
    do {
        printf("\n");
        exibirMapa(mapa, MAX_TERRITORIOS);
        exibirMissao(&missaoJogador);
        exibirMenuPrincipal();
        
        printf("Escolha sua ação (0-2): ");
        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            opcao = -1; // Garante que não entra em opção inválida se a leitura falhar
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                printf("\n--- FASE DE ATAQUE ---\n");
                faseDeAtaque(mapa, corJogador);
                break;
            case 2:
                // Verifica a condição de vitória
                vitoria = verificarVitoria(mapa, MAX_TERRITORIOS, &missaoJogador, corJogador);
                if (vitoria) {
                    printf("\n🎉🎉 **VITÓRIA!** Você cumpriu sua missão e conquistou o mundo! 🎉🎉\n");
                } else {
                    printf("\n... Missão ainda não cumprida. Continue lutando!\n");
                }
                break;
            case 0:
                printf("\nEncerrando o jogo. Obrigado por jogar!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }

        if (opcao != 0 && !vitoria) {
            printf("\nPressione ENTER para continuar a rodada...\n");
            getchar(); // Pausa a execução
        }
    } while (opcao != 0 && !vitoria);

    // 3. Limpeza:
    liberarMemoria(mapa);
    
    return 0;
}

// ============================================================================
// --- Implementação das Funções ---
// ============================================================================

// alocarMapa(): Aloca dinamicamente a memória.
Territorio* alocarMapa() {
    // calloc(num_elementos, tamanho_do_elemento) - Inicializa a memória com zero
    return (Territorio*)calloc(MAX_TERRITORIOS, sizeof(Territorio));
}

// inicializarTerritorios(): Preenche os dados iniciais.
void inicializarTerritorios(Territorio *mapa) {
    // ⚠️ Note: mapa é um ponteiro (passagem por referência), modificamos *diretamente* a memória.
    
    // Exemplo de dados iniciais
    if (mapa != NULL) {
        // Território 1
        strcpy(mapa[0].nome, "Nova York");
        strcpy(mapa[0].corExercito, "Amarelo");
        mapa[0].numTropas = 3;
        
        // Território 2
        strcpy(mapa[1].nome, "Texas");
        strcpy(mapa[1].corExercito, "Azul");
        mapa[1].numTropas = 4;
        
        // Território 3
        strcpy(mapa[2].nome, "Quebec");
        strcpy(mapa[2].corExercito, "Verde");
        mapa[2].numTropas = 5;
        
        // Território 4
        strcpy(mapa[3].nome, "California");
        strcpy(mapa[3].corExercito, "Amarelo");
        mapa[3].numTropas = 2;
        
        // Território 5
        strcpy(mapa[4].nome, "Mexico");
        strcpy(mapa[4].corExercito, "Azul");
        mapa[4].numTropas = 6;
    }
}

// liberarMemoria(): Libera a memória.
void liberarMemoria(Territorio *mapa) {
    // Verifica se o ponteiro não é NULL antes de liberar
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemória do mapa liberada com sucesso.\n");
    }
}

// exibirMenuPrincipal(): Exibe o menu.
void exibirMenuPrincipal(void) {
    printf("\n--- MENU DE AÇÕES ---\n");
    printf("1. ⚔️ Iniciar Fase de Ataque\n");
    printf("2. 🏆 Verificar Vitória\n");
    printf("0. 🚪 Sair do Jogo\n");
    printf("---------------------\n");
}

// exibirMapa(): Mostra o estado atual.
void exibirMapa(const Territorio *mapa, size_t tamanho) {
    // ⚠️ Note: O parâmetro 'mapa' é 'const', indicando que não podemos modificá-lo.
    if (mapa == NULL) return;

    printf("\n=== MAPA DE TERRITÓRIOS (STATUS) ===\n");
    printf("+----+--------------------+----------------+---------------+\n");
    printf("| ID | %-20s | %-14s | %-13s |\n", "Território", "Dono (Cor)", "Tropas");
    printf("+----+--------------------+----------------+---------------+\n");

    for (size_t i = 0; i < tamanho; i++) {
        printf("| %-2d | %-20s | %-14s | %-13d |\n",
               (int)i, // Exibimos o ID como índice
               mapa[i].nome,
               mapa[i].corExercito,
               mapa[i].numTropas);
    }
    printf("+----+--------------------+----------------+---------------+\n");
}

// exibirMissao(): Exibe a missão.
void exibirMissao(const Missao *missao) {
    // ⚠️ Note: O parâmetro 'missao' é 'const', apenas leitura.
    printf("\n📜 SUA MISSÃO SECRETA (ID %d):\n", missao->id);
    printf("  -> %s\n", missao->descricao);
}

// sortearMissao(): Sorteia e retorna uma missão.
Missao sortearMissao(const char *corJogador) {
    Missao m;
    int idSorteado = (rand() % MAX_MISSOES) + 1; // Sorteia ID 1, 2 ou 3
    m.id = idSorteado;

    // Define a cor alvo (exemplo) - diferente da cor do jogador
    const char *cores[] = {"Azul", "Verde", "Preto", "Vermelho"};
    int corIndex = rand() % 4;
    while (strcmp(cores[corIndex], corJogador) == 0) { // Garante que a cor alvo não é a do jogador
        corIndex = rand() % 4;
    }
    strcpy(m.corAlvo, cores[corIndex]);
    
    switch (m.id) {
        case 1:
            // Missão de Destruição
            m.territoriosAlvo = 0;
            snprintf(m.descricao, sizeof(m.descricao), 
                     "Destruir completamente o exército de cor %s.", m.corAlvo);
            break;
        case 2:
            // Missão de Conquista
            m.territoriosAlvo = 4; // Exemplo: conquistar 4 territórios
            snprintf(m.descricao, sizeof(m.descricao), 
                     "Conquistar %d territórios e manter a sua cor (total 5).", m.territoriosAlvo);
            break;
        case 3:
        default:
            // Missão de Conquista (Alternativa)
            m.territoriosAlvo = 3; // Exemplo: conquistar 3 territórios
            snprintf(m.descricao, sizeof(m.descricao), 
                     "Conquistar %d territórios do continente principal e manter (total 4).", m.territoriosAlvo);
            break;
    }
    return m; // Retorno por valor (cópia da struct)
}

// faseDeAtaque(): Gerencia a interface e inicia o ataque.
void faseDeAtaque(Territorio *mapa, const char *corJogador) {
    int idAtaque, idDefesa;
    
    printf("Digite o ID do seu território de ataque: ");
    if (scanf("%d", &idAtaque) != 1 || idAtaque < 0 || idAtaque >= MAX_TERRITORIOS) {
        printf("ID de ataque inválido.\n");
        return;
    }
    limparBufferEntrada();
    
    printf("Digite o ID do território vizinho a ser atacado: ");
    if (scanf("%d", &idDefesa) != 1 || idDefesa < 0 || idDefesa >= MAX_TERRITORIOS) {
        printf("ID de defesa inválido.\n");
        return;
    }
    limparBufferEntrada();

    // Validação básica:
    if (strcmp(mapa[idAtaque].corExercito, corJogador) != 0) {
        printf("Erro: O território %s não pertence a você.\n", mapa[idAtaque].nome);
        return;
    }
    if (strcmp(mapa[idAtaque].corExercito, mapa[idDefesa].corExercito) == 0) {
        printf("Erro: Você não pode atacar seus próprios territórios.\n");
        return;
    }
    if (mapa[idAtaque].numTropas <= 1) {
        printf("Erro: Você precisa de pelo menos 2 tropas para atacar (1 para defender).\n");
        return;
    }
    
    // Inicia a lógica da batalha
    // ⚠️ Passagem por referência (ponteiros) para *modificar* os dados dos territórios.
    simularAtaque(&mapa[idAtaque], &mapa[idDefesa]);
}

// simularAtaque(): Executa a lógica da batalha.
void simularAtaque(Territorio *ataque, Territorio *defesa) {
    // ⚠️ Note: ataque e defesa são ponteiros, modificamos *diretamente* suas structs.
    
    int dadosAtaque = (rand() % 3) + 1; // Rola 1 a 3 dados
    int dadosDefesa = (rand() % 2) + 1; // Rola 1 a 2 dados

    printf("\n[BATALHA] %s (%s) ⚔️ %s (%s)\n", 
           ataque->nome, ataque->corExercito, defesa->nome, defesa->corExercito);
    printf("  Ataque (Tropas: %d) rola %d. Defesa (Tropas: %d) rola %d.\n", 
           ataque->numTropas, dadosAtaque, defesa->numTropas, dadosDefesa);

    // Comparação simplificada:
    if (dadosAtaque > dadosDefesa) {
        defesa->numTropas -= 1;
        printf("  O ataque venceu! %s perdeu 1 tropa. Tropas restantes: %d\n", defesa->nome, defesa->numTropas);
    } else {
        ataque->numTropas -= 1;
        printf("  A defesa venceu ou empatou! %s perdeu 1 tropa. Tropas restantes: %d\n", ataque->nome, ataque->numTropas);
    }
    
    // Verificação de Conquista
    if (defesa->numTropas <= 0) {
        printf("  *** TERRITÓRIO CONQUISTADO! ***\n");
        printf("  %s agora pertence ao exército %s.\n", defesa->nome, ataque->corExercito);
        
        // Conquista: troca de dono e move 1 tropa
        strcpy(defesa->corExercito, ataque->corExercito);
        defesa->numTropas = 1; // Ocupa com uma tropa
        ataque->numTropas -= 1; // Tira a tropa do atacante
    }
}

// verificarVitoria(): Verifica se a missão foi cumprida.
int verificarVitoria(const Territorio *mapa, size_t tamanho, const Missao *missao, const char *corJogador) {
    // ⚠️ Note: A função e seus parâmetros são 'const' para garantir que os dados não sejam alterados.
    
    int territoriosJogador = 0;
    int corAlvoPresente = 0;
    
    for (size_t i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].corExercito, corJogador) == 0) {
            territoriosJogador++;
        }
        if (strcmp(mapa[i].corExercito, missao->corAlvo) == 0) {
            corAlvoPresente = 1;
        }
    }
    
    // Lógica para Missão de Destruição (ID 1)
    if (missao->id == 1) {
        if (corAlvoPresente == 0) {
            printf("[VERIFICAÇÃO] O exército %s foi destruído.\n", missao->corAlvo);
            return 1; // Missão cumprida!
        }
    }
    
    // Lógica para Missão de Conquista (ID 2 e 3)
    if (missao->id == 2 || missao->id == 3) {
        if (territoriosJogador >= missao->territoriosAlvo) {
             printf("[VERIFICAÇÃO] Você controla %d territórios. O objetivo (%d) foi alcançado.\n", 
                    territoriosJogador, missao->territoriosAlvo);
            return 1; // Missão cumprida!
        }
    }
    
    return 0; // Missão não cumprida.
}

// limparBufferEntrada(): Função utilitária.
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}