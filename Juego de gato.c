#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/* ↑ Librerias(estandar)*/
#define true 1
#define false 0
/* ↑ Valores true false*/
typedef struct{
	unsigned short computerPoints;
	unsigned short playerPoints;
	char playerToken;
	char computerToken;
}onePlayerGame;
typedef struct{
	unsigned short player1Points;
	unsigned short player2Points;
	char player1Token;
	char player2Token;
}twoPlayersGame;
/* ↑ Estructuras para manejar mejor los datos*/
void onePlayer(char table[3][3],onePlayerGame *game1);
void twoPlayers(char table[3][3],twoPlayersGame *game2);
void Positions(char table[3][3]);
void board(char table[3][3]);
int check(char table[3][3], char token);
void playerTurn(char table[3][3], char token);
void computerTurn(char table[3][3], char token);
/* ↑ Prototipos de funciones*/
int main()
{
	int key=true, op;
	char table[3][3]; /*This is the matix that it's going to store the values*/
	
	/*Initialices the games, this can be changed to make more than one game */
	onePlayerGame game1;
	twoPlayersGame game2;
	game1.playerPoints=0;
	game1.computerPoints=0;
	game1.playerToken='X';
	game1.computerToken='O';
	game2.player1Points=0;
	game2.player2Points=0;
	game2.player1Token='X';
	game2.player2Token='O';

	do
	{
		system("cls");/*Cleans the screen*/
		printf("Que quieres hace?:\n1)Partida jugador-maquina\n2)Partidad jugador1-jugador2\n3)Mostrar puntos jugador-maquina\n4)Mostrar puntos jugador1-jugador2\n5)Salir\n");
		/* ↑ The menu of selection*/
		fflush(stdin);/*Cleans the keyboard because in a loop it could resuld in problems if not*/
		scanf("%i", &op); /*Gets the selected operation*/
		switch(op){ 
			case 1: onePlayer(table, &game1);break;
			case 2: twoPlayers(table, &game2);break;
			case 3:
				printf("Los puntos del jugador son: %i\n",game1.playerPoints);
				printf("Los puntos de la maquina son: %i\n",game1.computerPoints);
				break;
				
			case 4:
				printf("Los puntos del jugador 1 son: %i\n",game2.player1Points);
				printf("Los puntos del jugador 2 son: %i\n",game2.player2Points);
				break;
				
			case 5: key=false;break;
			default: printf("Operacion no valida\n");break;
		}
		system("pause");
	} while (key==true);
	printf("Adios\n");
	system("pause"); /*Pauses the system to make it posible for user to read what has been done*/
	return 0; 
}
void onePlayer(char table[3][3],onePlayerGame *game1){/*Methods used for a one player game/behavior of a one player game*/
	int winned=false, turns=0;
	Positions(table); /*Places cordinates/positions so the player can understand how to select a position*/
	while(turns<9){ /*Repeats until there are no free spaces left*/
		board(table); /*Shows board so the player can select a move*/
		playerTurn(table, game1->playerToken); /*Let's the player select a position and places the player's tocken*/
		turns++; /*Theres one cordinate/position/turn less*/
		board(table);
		if (check(table, game1->playerToken)==true){ /*Checks if the player has won, in wich case felicitates and gives one point to the player*/
			printf("\nFelicidades '%c' has ganado\n", game1->playerToken);
			winned=true; /*The game has been won*/ 
			game1->playerPoints++;
			break;/*It's not necesary to continue the game so finishes the while*/
		}
		if (turns<9) /*decides if it's necesary to continue with the game*/
		{
			computerTurn(table, game1->computerToken); 
			turns++;
			board(table); 
			if (check(table, game1->computerToken)==true){ /*Checks if the computer has won in which  gives one point to the computer*/
				printf("\nLastima la computadora ha ganado\n");
				winned=true;
				game1->computerPoints++;
				break;
			}
		}
	}
	if (winned==false){ /*If nobody won and there are no positions left, its tacken like a tie/draw*/
		printf("\nNadie ha ganado\n");
	}
}
void twoPlayers(char table[3][3],twoPlayersGame *game2){/*methods used for a two players game/behavior of a two players game*/
	/*The same as the one player with some changes*/
	int winned=false, turns=0;
	Positions(table);
	while(turns<9){
		board(table);
		playerTurn(table, game2->player1Token);
		turns++;
		board(table);
		if (check(table, game2->player1Token)==true){
			printf("\nFelicidades '%c' has ganado\n", game2->player1Token);
			winned=true;
			game2->player1Points++;
			break;
		}
		if (turns<9){
			playerTurn(table, game2->player2Token); /*instead of making the computer  decide a position makes the other player decide*/
			turns++;
			board(table);
			winned=check(table, game2->player2Token);
			if (winned==true){
				printf("\nFelicidades '%c' has ganado\n", game2->player2Token);
				game2->player2Points++;
				break;
			}
		}
	}
	if (winned==false)
	{
		printf("\nNadie ha ganado\n");
	}
}
void Positions(char table[3][3]){ /*Fills the board's game with the cordinates that will be able to select*/
	int cordinate=49;/*49 it's for ASCII code of '1' */
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			table[i][j]=cordinate;
			cordinate++;
		}
	}
}
void board(char table[3][3]){ /*Shows the board's game*/
	system("cls");/*Cleans the screen*/
	for (int i = 0; i < 3; ++i) /*Used for rows*/
	{
		for (int j = 0; j < 3; ++j) /*Used for columns*/
		{
			if (j<2){ /*Decides if it's necesary printing a vertical line to separe the values or not*/
				printf(" %c |",table[i][j]);
			}
			else{
				printf(" %c ",table[i][j]);
			}
		}
		if (i<2){ /*Decides if it's necesary printing a horizontal line to separe the values or not*/
			printf("\n----------\n");
		}
		else{
			printf("\n");
		}
	}
}
int check(char table[3][3], char token){ /*Checks if the game has been won*/
	int compleated=false; /*Indicates if there's a line of tokens of the same player*/
	for (int i = 0; i < 3; ++i)
	{
		if (table[i][0]==token){/*Checks the rows*/
			if(table[i][1]==token && table[i][2]==token){
				compleated=true; /*Makes true because a player has compleated a line of three*/
				break; /*Finishes the loop*/
			}
		}
		if (table[0][i]==token){/*Checks the columns*/
			if (table[1][i]==token && table[2][i]==token){
				compleated=true;
				break; 
			}
		}
	}
	if ((table[0][0]==token && table[1][1]==token && table[2][2]==token) || (table[0][2]==token && table[1][1]==token && table[2][0]==token)){/*Checks diagonals*/
		compleated=true;
	}
	if(compleated==true){ /*Decides what to send to the function who callled check()*/
		return true; /*Tells the function who called check() that the game has been won*/
	}
	else{
		return false; /*Tells the function who called check() that there's not a line of thre*/
	}
}
void playerTurn(char table[3][3], char token){/*Gets the position wanted and places the player's token*/
	int position;
	char occuped;
	do{
		do{/*Makes the player select a valid position*/
			printf("Introduce la posicion que quieres poner tu ficha (turno de '%c'):", token); /*Asks for a position and tells whose turn is */
			fflush(stdin);
			scanf("%i", &position);
		} while (position<1 || position>9);
		switch (position){/*Makes the player select a free position*/
			case 1: occuped=table[0][0];break;
			case 2: occuped=table[0][1];break;
			case 3: occuped=table[0][2];break;
			case 4: occuped=table[1][0];break;
			case 5: occuped=table[1][1];break;
			case 6: occuped=table[1][2];break;
			case 7: occuped=table[2][0];break;
			case 8: occuped=table[2][1];break;
			case 9: occuped=table[2][2];break;
			default:
				printf("Aqui hay un error\n");
				system("pause");
				break;
		}
		if (occuped=='X' || occuped=='O'){/*Tells the user that the position is already taken*/
			printf("\nEsta posicion ya esta tomada, por favor elija otra\n");
		}
	} while(occuped=='X' || occuped=='O');
	switch (position){/*Puts the playe's token on the selected position*/
		case 1: table[0][0]=token;break;
		case 2: table[0][1]=token;break;
		case 3: table[0][2]=token;break;
		case 4: table[1][0]=token;break;
		case 5: table[1][1]=token;break;
		case 6: table[1][2]=token;break;
		case 7: table[2][0]=token;break;
		case 8: table[2][1]=token;break;
		case 9: table[2][2]=token;break;
		default:
				printf("Aqui hay un error\n");
				system("pause");
				break;
	}
}
void computerTurn(char table[3][3], char token){/*Makes the computer select a position and places its token*/
	short position;
	char occuped;
	srand(time(NULL));/*makes the random numbers got by rand() change everytime random() is called*/
	do{/*Makes the player select a free position*/
		position=(rand()%9+1);/*Gives a random number between 1 and 9 (included 1 and 9)*/
		switch (position){ 
			case 1: occuped=table[0][0];break;
			case 2: occuped=table[0][1];break;
			case 3: occuped=table[0][2];break;
			case 4: occuped=table[1][0];break;
			case 5: occuped=table[1][1];break;
			case 6: occuped=table[1][2];break;
			case 7: occuped=table[2][0];break;
			case 8: occuped=table[2][1];break;
			case 9: occuped=table[2][2];break;
			default:
				printf("Aqui hay un error\n");
				system("pause");
				break;
		}
	} while(occuped=='X' || occuped=='O');
	switch (position){ /*puts the player's token on the selected position*/
		case 1: table[0][0]=token;break;
		case 2: table[0][1]=token;break;
		case 3: table[0][2]=token;break;
		case 4: table[1][0]=token;break;
		case 5: table[1][1]=token;break;
		case 6: table[1][2]=token;break;
		case 7: table[2][0]=token;break;
		case 8: table[2][1]=token;break;
		case 9: table[2][2]=token;break;
		default:
			printf("Aqui hay un error\n");
			system("pause");
			break;
	}
}