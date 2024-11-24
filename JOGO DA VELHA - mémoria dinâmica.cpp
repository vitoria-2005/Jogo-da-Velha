/*Jogo da velha (3X3 OU 4X4);
a) Apenas um tabuleiro 3x3 (ou 5x5)
b) Caso n�o exista o segundo jogador, o computador deve assumir a posi��o do
oponente;
c) Ranking em arquivo;
d) Deve haver menu com op��es de Jogar, Ver Ranking, Cr�ditos e Sair;
e) Utilize matriz com aloca��o din�mica;    
f) Utilize struct para armazenar dados em mem�ria e depois transferir para arquivo;
g) Controle de jogada deve ser feito utilizando entrada de dados pelo teclado
contendo informa��o da posi��o e usu�rio;
*/

#include <stdio.h>  //padr�o 
#include <stdlib.h> //Necess�rio para aloca��o din�mica
#include <locale.h> //Necess�rio para acetua��o correta
#include <string.h> //Necess�rio na parte de jogar contra o computador

// Estrutura para guardar os dados dos jogadores
typedef struct dados {
    char nome[30];
    int vitorias;
} t_dados;

// Vari�veis globais necess�rias
t_dados jogador1, jogador2; // Importante para exibir o ranking
char **jogo;               // Matriz din�mica
int tamanho = 3;           // Tamanho padr�o do tabuleiro
int l, c;

// Fun��o para criar a matriz din�mica 
void criarMatriz() {
    jogo = (char **)malloc(tamanho * sizeof(char *));
    for (int i = 0; i < tamanho; i++) {
        jogo[i] = (char *)malloc(tamanho * sizeof(char));
    }
}

// Fun��o para liberar a mem�ria alocada para a matriz 
void liberarMatriz() {
    for (int i = 0; i < tamanho; i++) {
        free(jogo[i]);
    }
    free(jogo);
}

/* Procedimento para inicializar as posi��es no jogo,
importante para a verifica��o de vencedor */
void inicializar() {
    for (l = 0; l < tamanho; l++) {
        for (c = 0; c < tamanho; c++)
            jogo[l][c] = ' ';
    }
}

/* Procedimento que imprime o tabuleiro na tela,
e os n�meros das posi��es*/
void imprimir() {
    printf("\n\t");
    for (c = 0; c < tamanho; c++) {
        printf(" %d  ", c);
    }
    printf("\n\n");
    for (l = 0; l < tamanho; l++) {
        printf("\t");
        for (c = 0; c < tamanho; c++) {
            printf(" %c ", jogo[l][c]);
            if (c < tamanho - 1)
                printf("|");
        }
        printf("   %d\n", l);
        if (l < tamanho - 1) {
            printf("\t");
            for (c = 0; c < tamanho; c++) {
                printf("---");
                if (c < tamanho - 1)
                    printf("+");
            }
            printf("\n");
        }
    }
}

// Fun��o para verificar se h� vencedor 
int verificarVencedor() {
    int i, j;

    // Verificar linhas e colunas
    for (i = 0; i < tamanho; i++) {
        int linhaIgual = 1, colunaIgual = 1;
        for (j = 1; j < tamanho; j++) {
            if (jogo[i][j] != jogo[i][0] || jogo[i][0] == ' ')
                linhaIgual = 0;
            if (jogo[j][i] != jogo[0][i] || jogo[0][i] == ' ')
                colunaIgual = 0;
        }
        if (linhaIgual || colunaIgual)
            return 1;
    }

    // Verificar diagonais
    int diagPrincipal = 1, diagSecundaria = 1;
    for (i = 1; i < tamanho; i++) {
        if (jogo[i][i] != jogo[0][0] || jogo[0][0] == ' ')
            diagPrincipal = 0;
        if (jogo[i][tamanho - i - 1] != jogo[0][tamanho - 1] || jogo[0][tamanho - 1] == ' ')
            diagSecundaria = 0;
    }

    if (diagPrincipal || diagSecundaria)
        return 1;

    return 0;
}

// Fun��o para verificar se uma jogada � v�lida 
int ehValida(int l, int c) {
    if (l >= 0 && l < tamanho && c >= 0 && c < tamanho && jogo[l][c] == ' ')
        return 1;
    else
        return 0;
}

// Procedimento para ler as jogadas dos jogadores e guard�-las
void lerJogadas(char j) {
    int linha, coluna;

    printf("Digite linha e coluna entre 0 e %d: ", tamanho - 1);
    scanf("%d%d", &linha, &coluna);

    while (ehValida(linha, coluna) == 0) {
        printf("Jogada inv�lida! Digite outra linha e coluna: ");
        scanf("%d%d", &linha, &coluna);
    }
    jogo[linha][coluna] = j;
}

// Procedimento para a jogada do computador
void jogadaComputador(char b) {
    int i, k;
	
	printf("\nComputador est� jogando...\n");
	for(i = 0; i < 3; i++){
		for(k = 0; k < 3; k++){
			if(jogo[i][k] == ' '){
				jogo[i][k] = b;
				return;
			}
		}
    }
}

// Procedimento para exibir ranking
void exibirRanking(){
    printf("\n");
    printf("1. %s - %d vit�ria(s)\n", jogador1.nome, jogador1.vitorias);
    printf("2. %s - %d vit�ria(s)\n", jogador2.nome, jogador2.vitorias);
    printf("\n");
}

/*procedimento para jogar;
dentro dessa fun��o s�o chamadas a maioria das outras;
porque basicamente as outras s�o partes separadas que 
juntando da forma certa nessa fun��o formam o jogo;
*/
void jogar (int contraComputador) {
    char jogarNovamente; //necess�rio para jogar mais de uma vez ou sair

    printf("Digite o nome do jogador 1: ");       //coleta e armazena o nome dos joadores
    scanf(" %[^\n]", jogador1.nome);

    if (!contraComputador) {
        printf("Digite o nome do jogador 2: ");   //se o modo de jogo for de duas pessoas, coleta o nome do jogador 2
        scanf(" %[^\n]", jogador2.nome);
    } else {
        strcpy(jogador2.nome, "Computador");      /* se for modo computador, coloca automaticamente o nome "computador"
		                                           <string.h> sendo usada aqui*/
    }

    do {
        inicializar();  //chama a fun��o inicializar
        int turno = 0;  //necess�rio para troca de turno

        while (1) {
            imprimir(); //imprime o tabuleiro
            
            //troca o turno
            if (turno % 2 == 0) {
                printf("\n%s, � sua vez (X)! ", jogador1.nome);
                lerJogadas('X');     //registra a jodada de X
            } else {
                if (contraComputador) {
                    jogadaComputador('O');
                } else {
                    printf("\n%s, � sua vez (O)! ", jogador2.nome);
                    lerJogadas('O'); //registra a jodada de O
                }
            }
            
            //verifica o vencedor  e guarda as vit�rias
            if (verificarVencedor()) {
                imprimir();
                if (turno % 2 == 0) {
                    printf("%s venceu!\n", jogador1.nome);
                    jogador1.vitorias++;
                } else {
                    printf("%s venceu!\n", jogador2.nome);
                    jogador2.vitorias++;
                }
                break;
            }
            //caso ningu�m ganhe, d� empate
            if (turno == (tamanho * tamanho) - 1) {
                imprimir();
                printf("Empate! O jogo terminou sem vencedor.\n");
                break;
            }
            turno++;
        }
        /*pergunta se quer continuar jogando,
    	se n�o quiser volta para o menu inicial*/
        printf("\nDeseja jogar novamente? (s/n): ");
        scanf(" %c", &jogarNovamente);
    } while (jogarNovamente == 's' || jogarNovamente == 'S');
}

int main() {
    setlocale(0, "portuguese");
    
    //vari�vel importante para a cria��o do menu
    int opcao;
    
    //loop do menu
    do {
        printf("\n--- Jogo da Velha ---\n\n");
        printf("1. Jogar (2 jogadores)\n");
        printf("2. Jogar com o computador\n");
        printf("3. Ranking\n");
        printf("4. Cr�ditos\n");
        printf("5. Sair\n");
        printf("\n\nEscolha uma op��o (n�mero): ");
        scanf("%d", &opcao);
        
        //swith para chamar as fun��es void, mostrar os cr�ditos e a mensagem de saida
        switch (opcao) {
            case 1:
                criarMatriz();
                jogar(0);
                liberarMatriz();
                break;
            case 2:
                criarMatriz();
                jogar(1);
                liberarMatriz();
                break;
            case 3:
                exibirRanking();
                break;
            case 4:
                printf("\nCr�ditos:\n\nEmmanuel Lacerda\nErika Regina\nIsadora Garcez\nVit�ria Gon�alves\n");
                break;
            case 5:
                printf("\nVoc� est� saindo, volte logo!");
                break;
            default:
                printf("\nOp��o inv�lida! Tente novamente.");
                break;
        }
    } while (opcao != 5); 

    return 0;
}

