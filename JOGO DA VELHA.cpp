/*Jogo da velha (3X3 OU 4X4);
a) Apenas um tabuleiro 3x3 (ou 5x5)
b) Caso não exista o segundo jogador, o computador deve assumir a posição do
oponente;
c) Ranking em arquivo;
d) Deve haver menu com opções de Jogar, Ver Ranking, Créditos e Sair;
e) Utilize matriz com alocação dinâmica;    <------------------ NÃO ESTÁ EM ALOCAÇÃO DINÂMICA---------------
f) Utilize struct para armazenar dados em memória e depois transferir para arquivo;
g) Controle de jogada deve ser feito utilizando entrada de dados pelo teclado
contendo informação da posição e usuário;
*/


#include <stdio.h>  //padrão
#include <locale.h> //padrão para o texto ir certo 
#include <string.h>	//está sendo usada na parte de jogar contra o computador
#include <time.h>	//também está sendo usada para jogar contra o computador

//estrutura para guardar os dados dos jogadores
typedef struct dados{
	char nome[30];
	int vitorias;
}t_dados;


//variáveis globais necessárias
t_dados jogador1, jogador2; //importante para exibir o ranking
char jogo[3][3];
int l, c;

/*procedimento para inicializar as posições no jogo,
importante para a verificação de vencedor*/
void inicializar(){
	for(l = 0; l < 3; l++){
		for(c = 0; c < 3; c++)
		jogo[l][c] = ' ';
	}
}

/*procedimento que imprimi aquela tabela do jogo da velha,
e os números das posições*/
void imprimir(){
	printf("\n\t 0   1   2\n\n");
	for(l = 0; l < 3; l++){
		for(c = 0; c < 3; c++){
			if(c == 0)
			   printf("\t");
			printf(" %c ", jogo[l][c]);
			if(c < 2)
			   printf("|"); 
			if(c == 2)
			   printf("   %d", l);     
		}
		printf("\n");
		if(l < 2)
		     printf("\t-----------\n");
	}
}
/*
função para verificar se alguem venceu
1 - ganhou
0 - não ganhou ainda
*/
int verificarVencedor(){
	int i;
	
	for(i = 0; i < 3; i++){
		if(jogo[i][0] == jogo[i][1] && jogo[i][1] == jogo[i][2] && jogo[i][0] != ' ')
		   return 1;
		if(jogo[0][i] == jogo[1][i] && jogo[1][i] == jogo[2][i] && jogo[0][i] != ' ')   
		   return 1;
		}
	if(jogo[0][0] == jogo[1][1] && jogo[1][1] == jogo[2][2] && jogo[0][0] != ' ')
		return 1;
	if(jogo[0][2] == jogo[1][1] && jogo[1][1] == jogo[2][0] && jogo[0][2] != ' ')   
		return 1;
	else
	    return 0;	
		
}

/*função para verificar se uma ação é válida ou não
1 - válido
0 - não é valido
*/
int ehValida(int l, int c){
	if(l >= 0 && l < 3 && c >= 0 && c < 3 && jogo[l][c] == ' ')
	   return 1;
	else
	   return 0;   
}

/*procedimento para ler as jogados do jogador,
importante para guardar as jogadas*/
void lerJogadas(char j){
	int linha, coluna;
	
	printf("Digite linha e coluna entre 0 e 2: ");
	scanf("%d%d", &linha, &coluna);
	
	while(ehValida(linha, coluna) == 0){
		printf("Jogada invalida! Digite outra linha e coluna: ");
	    scanf("%d%d", &linha, &coluna);
	}
	jogo[linha][coluna] = j; 
}
//procedimento para jogar contra o computador
void jogadaComputador(char b){
	int i, k;
	
	printf("\nComputador está jogando...\n");
	for(i = 0; i < 3; i++){
		for(k = 0; k < 3; k++){
			if(jogo[i][k] == ' '){
				jogo[i][k] = b;
				return;
			}
		}
	}
}

//procedimento para exibir ranking
void exibirRanking(){
	printf("\n");
	printf("1. %s - %d vitória(s)\n", jogador1.nome, jogador1.vitorias);
    printf("2. %s - %d vitória(s)\n", jogador2.nome, jogador2.vitorias);
    printf("\n");
}

/*procedimento para jogar;
dentro dessa função são chamadas a maioria das outras;
porque basicamente as outras são partes separadas que 
juntando da forma certa nessa função formam o jogo;
*/
void jogar(int contraComputador){
	
	char jogarNovamente; //variavel necessaria para fazer pergunta se quer jogar de novo
	
	printf("Digite o nome do jogador 1: "); //coleta e armazena o nome dos joadores
	scanf(" %[^\n]", jogador1.nome);
	
	if (!contraComputador) {
        printf("Digite o nome do jogador 2: "); //se o modo de jogo for de duas pessoas, coleta o nome do jogador 2
        scanf(" %[^\n]", jogador2.nome);
    } else {
        strcpy(jogador2.nome, "Computador"); // se for modo computador, coloca automaticamente o nome "computador"
    }
	
	do{
		inicializar(); //posição inicial vazia
		int turno = 0; //controla o turno, necessario para trocar o jogador
	
	while(1){
		imprimir(); //tabela
		
		//troca os turnos
		if(turno % 2 == 0){ 
			printf("\n%s, é sua vez (X)! ", jogador1.nome);
			lerJogadas('X');  //reistra a jodada de X
		}else{
			if(contraComputador){
				jogadaComputador('O');
			}else{
				printf("\n%s, é sua vez (O)! ", jogador2.nome);
			    lerJogadas('O'); //registra a jogado de O
			}
			
		}
		//vê se alguém já ganhou
		if(verificarVencedor()){
			imprimir();
                if (turno % 2 == 0) {
                    printf("%s venceu!\n", jogador1.nome);
                    jogador1.vitorias++; //vai contando as vitorias e guardando para o ranking
                } else {
                    printf("%s venceu!\n", jogador2.nome);
                    jogador2.vitorias++; //vai contando as vitorias e guardando para o ranking
                }
                break;
		}
		//caso ninguém ganhe dá impate
		if(turno == 8){
			imprimir();
			printf("Empate! O jogo terminou sem vencedor.\n");
			break;
		}
		turno++;
	}
	/*pergunta se quer continuar jogando,
	se não quiser volta para o menu inicial*/
	printf("\nDeseja jogar novamente? (s/n): ");
	scanf(" %c", &jogarNovamente);
  }while(jogarNovamente == 's' || jogarNovamente == 'S');
}

int main(){
	
	setlocale(0,"portuguese");
	
	//variável importante para a criação do menu
	int opcao;
		
	//loop do menu
	do {
		printf("\n--- Jogo da Velha ---\n\n");
		printf("1. Jogar (2 jogadores)\n");
		printf("2. Jogar com o computador\n");
		printf("3. Ranking\n");
		printf("4. Créditos\n");
		printf("5. Sair\n");
		printf("\n\nEscolha uma opção(número):");
		scanf("%d", &opcao);
		
		//swith para chamar as funções void e mostra os créditos e a mensagem de saida
		switch(opcao){
			case 1:
				jogar(0);
				break;
			case 2:
				jogar(1); 
				break;
			case 3:
				printf("\n");
				exibirRanking();
				break;
			case 4:
			    printf("\nCréditos:\n\nEmmanuel Lacerda\nErika Regina\nIsadora Garcez\nVitória Gonçalves\n");
				break;
			case 5:
				printf("\nVocê está saindo, volte logo!");
				break;
			default: 
		        printf("\nOpção inválida! Tente novamente.");
		        break;
		}
	} while (opcao != 5);
	
}
