/*
Jogo da Forca
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define VERMELHO     "\x1b[31m"
#define AMARELO    "\033[33m"
#define RESET   "\x1b[0m"

//Variáveis
int vidas = 6, repetir = 1;
char cabeca = ' ', tronco = ' ', besq = ' ', bdir = ' ', pesq = ' ', pdir = ' ';
char palavra[21], dica[25], lacuna[21], jogador[15], erradas[6], acertadas[21];

//Funções
void fganhou();// "Desenho" de quando o jogador ganha
void fperdeu();// "Desenho" de quando o jogador perde
void ftelainicial();// Função do "Desenho" de apresentação
void fcreditos();// Informações da Faculdade/Aluno/Ano
void fatualizarBoneco();// Função que atualiza o boneco da forca com base na quantidade de erros do usuário
void fboneco();// "Desenho" da forca
void fjogo();// Função principal do jogo
void fpalavraSecreta();// Função que sorteia uma palavra

//main
int main()
{
	int opcao = 0;
	setlocale(LC_ALL, "Portuguese");
    ftelainicial();
    printf(" Escolha uma Opção:\n");
    printf("\n 1 - Jogar");
    printf("\n 2 - Sair\n");
    do
    {
    	printf("\n Digite o número de uma das opções acima: ");
        fflush(stdin);
        scanf("%d", &opcao);
        if(opcao != 1 && opcao != 2)
		{
	    	printf("[ERRO]: Opção não reconhecida pelo sistema!");
		}
		else
		{
			switch (opcao)
    		{
    			case 1: // Opção que inicia o jogo
    			{
    				printf("\n Digite o seu nome (Até 15 Caracteres): ");
    				fflush(stdin);
    				scanf("%s", &jogador);
    				int i = strlen(jogador);
    				if(i > 15)// Limite do tamanho do nome do jogador
    				{
        				while(i != 15)
       			    	{
        					jogador[i] = 0;
        					i--;
   						}
					}
    				system("cls");
    				do
    				{
    					for(i = 0; i < strlen(acertadas); i++)// "Limpando" array de tentativas que o jogador acertou
						{
							acertadas[i] = ' ';
						}
						for(i = 0; i < strlen(erradas); i++)// "Limpando" array de tentativas que o jogador errou
						{
							erradas[i] = ' ';
						}
    					fpalavraSecreta();// Chamando a função para sortear uma palavra
    					fjogo();// Função chamando as opções do jogo
					}
					while(repetir == 1);// Repete enquanto o jogador decide não sair
					break;
				}
				case 2:
				{
					break;
				}
				default: printf("[ERRO]: Opção não reconhecida pelo sistema!");
			}
		}
	}   	
	while(opcao != 1 && opcao != 2);// Repete enquanto o jogador não escolher uma opção válida
	return 0;
}

//Funções
//Função do jogo "principal"
void fjogo()
{
	//Variáveis locais
	int i, acertou, finalizar = 0, jaerrou = 0, jaacertou = 0, pos = 0, pos2 = 0, opcao = 0, sair = 0, esc = 0;
	char letra;
	//Laço de repetição
	do
	{
		system("cls");
		fcreditos(); // Função que apresenta a linha de informações
		fboneco(); // Função que apresenta informações do jogo e o desenho da forca
		acertou = 0;
		for(i = 0; i < strlen(palavra); i++)// Cria as lacunas que serão apresentadas na tela
		{
			printf("%c  ",lacuna[i]);
		}
		printf("\n\t Letras erradas: %s", erradas);// Apresenta as tentativas erradas do Jogador
		if(finalizar == strlen(palavra) || vidas <= 0)// Verifica se o jogador perdeu todas as vidas OU completou a palavra, se uma das condições for verdade sai do loop
		{
			sair = 1;
			break;
		}
		// Interação com o jogador
		printf("\n\n\t Digite uma letra: ");
		fflush(stdin);
     	letra = toupper(getch());
     	if(letra == 27) break;// Opção de sair da "rodada"
     	printf("%c", letra);
		if(!isalpha(letra))
		{
			printf("\n\t Você não digitou uma letra válida!");
			if(finalizar != strlen(palavra) && vidas > 0)
			{
				printf("\n\t Pressione qualquer tecla para continuar! ");
				esc = getch();
     			if(esc == 27) break;// Opção de sair da "rodada"
     		}
		}
		else
		{
			//letraM = toupper(letra);// Transforma a letra digitada em caracter maiúsculo
			for(i = 0; i < strlen(palavra); i++)
			{
				if(letra == palavra[i])// verifica se a letra digitada existe na palavra
				{
					lacuna[i] = letra;// transforma a lacuna na letra digitada
					acertou++;
				}
			}
			if(acertou != 0)
			{
				for(i = 0; i < strlen(acertadas); i++)// Verifica se o jogador já acertou determinada letra
				{
					if(letra == acertadas[i])
					{
						jaacertou++;
					}
				}
				if(jaacertou == 0)
				{
			   	    printf("\n\tParabéns você acertou uma letra!");
			    	finalizar = finalizar + acertou;
			    	acertadas[pos] = letra;
					pos++;
				}
				else
				{
					printf("\n\tVocê já digitou essa letra e ela estava certa!");
					jaacertou = 0;
				}
			}
			else
			{
				for(i = 0; i < strlen(erradas); i++)// Verifica se o jogador já errou determinada letra
				{
					if(letra == erradas[i])
					{
						jaerrou++;
					}
				}
				if(jaerrou == 0)
				{
					printf("\n\tVocê errou uma letra, restam %0.2d vidas!", vidas-1);
					erradas[pos2] = letra;
					pos2++;
					vidas--;
					fatualizarBoneco();
				}
				else
				{
					printf("\n\tVocê já digitou essa letra e ela estava errada!");
					jaerrou = 0;
				}
			}
			if(finalizar != strlen(palavra) && vidas > 0)
			{
				printf("\n\t Pressione qualquer tecla para continuar! ");
				esc = getch();
     			if(esc == 27) break;// Opção de sair da "rodada"
     		}
		}
	}
	while(sair != 1);
	if(vidas <= 0)// Se o jogador perder todas as vidas
	{
		printf("\n\n\tVocê foi enforcado, a palavra era: %s !", palavra);
		fperdeu();
	}
	if(finalizar == strlen(palavra))// Se o jogador acertar a palavra secreta
	{
		printf("\n\n\tParabéns!!! Você acertou a palavra secreta, a resposta era: %s !", palavra);
		fganhou();
	}
	//Opção de Jogar novamente
	printf("\n\tEscolha uma Opção:\n");
   	printf("\n\t 1 - Jogar novamente");
    printf("\n\t 2 - Sair\n");
	do
	{
    	printf("\n\t Digite o número de uma das opções acima: ");
        fflush(stdin);
        scanf("%d", &opcao); 
        if(opcao != 1 && opcao != 2)
		{
	    	printf("\t[ERRO]: Opção não reconhecida pelo sistema!");
		}
		else
		{
			switch (opcao)
    		{
    			case 1: 
    			{
    				vidas = 6;
    				cabeca = ' ';
					tronco = ' ';
					besq = ' ';
					bdir = ' ';
					pesq = ' ';
					pdir = ' ';
    				repetir = 1;
					break;
				}
				case 2:
				{
					repetir = 0;
					break;
				}
				default: printf("[ERRO]: Opção não reconhecida pelo sistema!");
			}
		}
	}
	while(opcao != 1 && opcao != 2);	
}
//Função de sortear palavra
void fpalavraSecreta()
{
	int i;
	int pal;
	srand(time(NULL));
	pal = rand() % 50;
	switch(pal)
	{
	    case 1:
		{
			strcpy(palavra, "AZUL");
			strcpy(dica, "CORES");
			break;
		}
		case 2:
		{
			strcpy(palavra, "VERDE");
			strcpy(dica, "CORES");
			break;
		}
		case 3:
		{
			strcpy(palavra, "AMARELO");
			strcpy(dica, "CORES");
			break;
		}
		case 4:
		{
			strcpy(palavra, "ROSA");
			strcpy(dica, "CORES");
			break;
		}
		case 5:
		{
			strcpy(palavra, "VERMELHO");
			strcpy(dica, "CORES");
			break;
		}
		case 6:
		{
			strcpy(palavra, "BRANCO");
			strcpy(dica, "CORES");
			break;
		}
		case 7:
		{
			strcpy(palavra, "PRETO");
			strcpy(dica, "CORES");
			break;
		}
		case 8:
		{
			strcpy(palavra, "ROXO");
			strcpy(dica, "CORES");
			break;
		}
		case 9:
		{
			strcpy(palavra, "CINZA");
			strcpy(dica, "CORES");
			break;
		}
		case 10:
		{
			strcpy(palavra, "MARROM");
			strcpy(dica, "CORES");
			break;
		}
		case 11:
		{
			strcpy(palavra, "CAMISA");
			strcpy(dica, "VESTUÁRIO");
			break;
		}
		case 12:
		{
			strcpy(palavra, "SAIA");
			strcpy(dica, "VESTUÁRIO");
			break;
		}
		case 13:
		{
			strcpy(palavra, "VESTIDO");
			strcpy(dica, "VESTUÁRIO");
			break;
		}
		case 14:
		{
			strcpy(palavra, "BLUSA");
			strcpy(dica, "VESTUÁRIO");
			break;
		}
		case 15:
		{
			strcpy(palavra, "MEIA");
			strcpy(dica, "VESTUÁRIO");
			break;
		}
		case 16:
		{
			strcpy(palavra, "BERMUDA");
			strcpy(dica, "VESTUÁRIO");
			break;
		}
		case 17:
		{
			strcpy(palavra, "TENIS");
			strcpy(dica, "VESTUÁRIO");
			break;
		}
		case 18:
		{
			strcpy(palavra, "BONE");
			strcpy(dica, "VESTUÁRIO");
			break;
		}
		case 19:
		{
			strcpy(palavra, "FADA");
			strcpy(dica, "PERSONAGEM DE CONTOS");
			break;
		}
		case 20:
		{
			strcpy(palavra, "BRUXA");
			strcpy(dica, "PERSONAGEM DE CONTOS");
			break;
		}
		case 21:
		{
			strcpy(palavra, "FEITICEIRA");
			strcpy(dica, "PERSONAGEM DE CONTOS");
			break;
		}
		case 22:
		{
			strcpy(palavra, "PRINCIPE");
			strcpy(dica, "PERSONAGEM DE CONTOS");
			break;
		}
		case 23:
		{
			strcpy(palavra, "PRINCESA");
			strcpy(dica, "PERSONAGEM DE CONTOS");
			break;
		}
		case 24:
		{
			strcpy(palavra, "RAINHA");
			strcpy(dica, "PERSONAGEM DE CONTOS");
			break;
		}
		case 25:
		{
			strcpy(palavra, "ARROZ");
			strcpy(dica, "ALIMENTO");
			break;
		}
		case 26:
		{
			strcpy(palavra, "FEIJAO");
			strcpy(dica, "ALIMENTO");
			break;
		}
		case 27:
		{
			strcpy(palavra, "MELANCIA");
			strcpy(dica, "ALIMENTO");
			break;
		}
		case 28:
		{
			strcpy(palavra, "CAFE");
			strcpy(dica, "ALIMENTO");
			break;
		}
		case 29:
		{
			strcpy(palavra, "LEITE");
			strcpy(dica, "ALIMENTO");
			break;
		}
		case 30:
		{
			strcpy(palavra, "BOLACHA");
			strcpy(dica, "ALIMENTO");
			break;
		}
		case 31:
		{
			strcpy(palavra, "CHOCOLATE");
			strcpy(dica, "ALIMENTO");
			break;
		}
		case 32:
		{
			strcpy(palavra, "BATATA");
			strcpy(dica, "ALIMENTO");
			break;
		}
		case 33:
		{
			strcpy(palavra, "MACARRAO");
			strcpy(dica, "ALIMENTO");
			break;
		}
		case 34:
		{
			strcpy(palavra, "GAIVOTA");
			strcpy(dica, "ANIMAL");
			break;
		}
		case 35:
		{
			strcpy(palavra, "ARARA");
			strcpy(dica, "ANIMAL");
			break;
		}
		case 36:
		{
			strcpy(palavra, "CACHORRO");
			strcpy(dica, "ANIMAL");
			break;
		}
		case 37:
		{
			strcpy(palavra, "GAVIAO");
			strcpy(dica, "ANIMAL");
			break;
		}
		case 38:
		{
			strcpy(palavra, "CARCARA");
			strcpy(dica, "ANIMAL");
			break;
		}
		case 39:
		{
			strcpy(palavra, "COELHO");
			strcpy(dica, "ANIMAL");
			break;
		}
		case 40:
		{
			strcpy(palavra, "BRASIL");
			strcpy(dica, "PAÍS");
			break;
		}
		case 42:
		{
			strcpy(palavra, "ALEMANHA");
			strcpy(dica, "PAÍS");
			break;
		}
		case 43:
		{
			strcpy(palavra, "CHINA");
			strcpy(dica, "PAÍS");
			break;
		}
		case 44:
		{
			strcpy(palavra, "PORTUGAL");
			strcpy(dica, "PAÍS");
			break;
		}
		case 45:
		{
			strcpy(palavra, "MEXICO");
			strcpy(dica, "PAÍS");
			break;
		}
		case 46:
		{
			strcpy(palavra, "ARGENTINA");
			strcpy(dica, "PAÍS");
			break;
		}
		case 47:
		{
			strcpy(palavra, "URUGUAI");
			strcpy(dica, "PAÍS");
			break;
		}
		case 48:
		{
			strcpy(palavra, "ESPANHA");
			strcpy(dica, "PAÍS");
			break;
		}
		case 49:
		{
			strcpy(palavra, "PARAGUAI");
			strcpy(dica, "PAÍS");
			break;
		}
		default:
		{
			strcpy(palavra, "CHILE");
			strcpy(dica, "PAÍS");
			break;
		}
	}
	for(i = 0; i < strlen(palavra); i++)
	{
		lacuna[i] = '_';
	}	
}
//Função que apresenta um troféu ao vencedor
void fganhou()
{
	printf( AMARELO "\n\t       ___________      \n");
	printf("\t      '._==_==_=_.'     \n");
	printf("\t      .-\\:      /-.    \n");
	printf("\t     | (|:.     |) |    \n");
	printf("\t      '-|:.     |-'     \n");
	printf("\t        \\::.    /      \n");
	printf("\t         '::. .'        \n");
	printf("\t           ) (          \n");
	printf("\t         _.' '._        \n");
	printf("\t        '-------'       \n\n" RESET);

}
//Função que apresenta uma caveira ao perdedor
void fperdeu()
{
	printf( VERMELHO "\n\t    _______________         \n");
	printf("\t   /               \\       \n"); 
	printf("\t  /                 \\      \n");
	printf("\t /                   \\  \n");
	printf( "\t |   XXXX     XXXX   |   \n");
	printf("\t |   XXXX     XXXX   |    \n");
	printf("\t |   XXX       XXX   |      \n");
	printf("\t |                   |      \n");
	printf( "\t \\__      XXX      __/     \n");
	printf("\t   |\\     XXX     /|       \n");
	printf("\t   | |           | |        \n");
	printf("\t   | I I I I I I I |        \n");
	printf("\t   |  I I I I I I  |        \n");
	printf("\t   \\_             _/       \n");
	printf("\t     \\_         _/         \n");
	printf("\t       \\_______/           \n" RESET);
}
//Função que apresenta a tela inicial
void ftelainicial()
{
	printf("===================================================================================================\n\n");
	printf("\n\tFFFFFFFFFF  OOOOOOOOOOOO  RRRRRRRRRRR    CCCCCCCCCC       AAAA            _________");
	printf("\n\tFFFFFFFFFF  OOOOOOOOOOOO  RRRRRRRRRRR    CCCCCCCCCC      AAAAAA           |       |");
	printf("\n\tFFF         OOO      OOO  RRR     RRR    CCC           AAA    AAA         |      ( )");
	printf("\n\tFFF         OOO      OOO  RRR     RRR    CCC          AAA      AAA        |       |");
	printf("\n\tFFFFFFFF    OOO      OOO  RRRRRRRRRRR    CCC         AAA        AAA       |      /|\\");
	printf("\n\tFFFFFFFF    OOO      OOO  RRRRRRRRRRRRR  CCC         AAAAAAAAAAAAAA       |       |");
	printf("\n\tFFF         OOO      OOO  RRR       RRR  CCC         AAAAAAAAAAAAAA       |      / \\");
	printf("\n\tFFF         OOO      OOO  RRR       RRR  CCC         AAA        AAA       |");
	printf("\n\tFFF         OOOOOOOOOOOO  RRR       RRR  CCCCCCCCCC  AAA        AAA       |");
	printf("\n\tFFF         OOOOOOOOOOOO  RRR       RRR  CCCCCCCCCC  AAA        AAA  _____|_____\n\n");
	printf("\n\tDesenvolvido por: Patrick Waldera\n\n");
	printf("===================================================================================================\n\n");
}
//Função que apresenta créditos do programa
void fcreditos()
{
	printf("FACULDADES INTEGRADAS CAMÕES - JOGO DA FORCA\t ALUNO: PATRICK WALDERA\t ANO:2020");
}
//Função que atualiza o boneco da forca
void fatualizarBoneco()
{
	if(vidas == 5)
	{
		cabeca = 'O';//Desenha a cabeça
	}
	else if(vidas == 4)
	{
		tronco = '|';//Desenha o tronco
	}
	else if(vidas == 3)
	{
		besq = '/';//Desenha o braço
	}
	else if(vidas == 2)
	{
		bdir = '\\';//Desenha o braço
	}
	else if(vidas == 1)
	{
		pesq = '/';// Desenha a perna
	}
	else if(vidas == 0)
	{
		pdir = '\\';// Desenha a perna
	}
}
//Função que apresenta informações de jogo junto a forca e o boneco
void fboneco()
{
	printf("\n\n");
	printf("    BOA SORTE: %s | DICA: %s | VIDAS: %d | PARA SAIR TECLE ' ESC '\n", jogador, dica, vidas);
	printf("\t     _______       \n");
	printf("\t    |       |      \n");
	printf("\t    |       %c\n", cabeca);
	printf("\t    |      %c%c%c   \n",besq,tronco,bdir); 
	printf("\t    |      %c %c   \n",pesq, pdir);
	printf("\t    |              \n");
	printf("\t ___|___   ");
	printf("");
}

