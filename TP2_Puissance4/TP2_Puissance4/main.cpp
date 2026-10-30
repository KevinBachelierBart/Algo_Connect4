#include <iostream>;
#include <windows.h> // for sleep
using std::cout;
using std::cin;
using std::endl;
//********************************************************************************************************30oct-08h39
const int line = 6;
const int column = 7;

//FONCTIONS PROTOTYPE-----------------------------------------------------------------------------------|
void GameplayTurn(char myTableau[line][column], bool& isPlayerTurn);//----------------------------------|
int InsertJeton(char myTableau[line][column], int columPlayed, bool& isPlayerTurn);//------------------|
void PrintTableau(char myTableau[line][column]);//----------------------------------|
bool CheckVictory(char myTableau[line][column], int linePlayed, int columnPlayed, bool& isPlayerTurn);//|
void WinningScreen();//---------------------------------------------------------------------------------|
bool CheckGridFull(char myTableau[line][column]);//-----------------------------------|
bool checkColumnFull(char myTableau[line][column], int columnPlayed);//---------------------------------------------------|
//------------------------------------------------------------------------------------------------------|

//========================================================================================================
void main()
{
#pragma region VARIABLES
	//====VARIABLES====
	//Intro
	char playerChoice = ' ';
	int columnChosen = -1;

	//TurnChoice
	bool isPlayerTurn = false;

	//Victory
	bool winnerFound = false;

	//Random
	srand(time(0));

#pragma endregion

#pragma region CONSIGNES
	cout << "Bonjour, \nBienvenue dans Puissance 4 ! \n" << endl;
	cout << "Le but est d'aligner 4 jetons cote a cote. (horizontalement, verticalement ou diagonalement)" << endl;
	cout << "Premier joueur a avoir sa ligne gagne" << endl;
	cout << "Pour jouer, indique la colonne dans laquelle tu veux deposer le jeton" << endl;
	//cout << "Exemple, colonne : \033[31m 1 \033[0m " << endl;
	cout << "" << endl;
#pragma endregion

#pragma region LE TABLEAU

	//						 0    1   2    3    4   5   6 
	char myTableau[line][column] = {
							{'X',' ',' ', ' ', ' ',' ',' '},//0
							{'X',' ',' ', ' ', ' ',' ',' '},//1
							{' ',' ',' ', ' ', ' ',' ',' '},//2
							{' ',' ',' ', ' ', ' ',' ',' '},//3
							{' ',' ',' ', ' ', ' ',' ',' '},//4
							{' ',' ',' ', ' ', ' ',' ',' '} };//5

	cout << "============================= LE TABLEAU =============================" << endl;
	cout << "\033[31m************COLONNES***********\033[0m" << endl;
	cout << "\033[31m==1====2===3===4===5===6===7===\033[0m" << endl;
	for (int i = line - 1; i >= 0; i--) // rows
	{
		cout << " | ";
		for (int j = 0; j < column; j++) // columns
		{
			cout << myTableau[i][j] << " | ";
		}

		cout << endl << "-------------------------------" << endl;
	}

	cout << "======================================================================" << endl;
	cout << "======================================================================" << endl;


#pragma endregion

#pragma region CHOIX DU JOUEUR 1er tour

	while (playerChoice != 'o' && playerChoice != 'n')
	{
		cout << "Veux-tu jouer en premier ? \nChoisis une valeur o/n" << endl;
		cin >> playerChoice;
	}
	playerChoice == 'o' ? isPlayerTurn = true : isPlayerTurn = false;

	system("cls");
	//cout << "\033[95m" << "isPlayerTurn = " << "\033[0m" << isPlayerTurn << endl;

	GameplayTurn(myTableau, isPlayerTurn);

#pragma endregion

}

void GameplayTurn(char myTableau[line][column], bool& isPlayerTurn)
{
	while (true)
	{
		int columnPlayed = -1;
		int tokenLine = -1;

		if (isPlayerTurn)
		{
			cout << "\033[95m" << "C est au tour du joueur " << "\033[0m" << endl;
		}
		else
		{
			cout << "\033[95m" << "C est au tour de l IA " << "\033[0m" << endl;
		}

		PrintTableau(myTableau);

		if (isPlayerTurn)
		{
			do
			{
				cout << "Quelle colonne veux-tu jouer ? (1-7)" << endl;
				cin >> columnPlayed;

				if (checkColumnFull(myTableau, columnPlayed))
				{
					//Ta colonne columnPlayed est pleine. MISSING LOGIC HERE

				}

			} while (columnPlayed < 1 || columnPlayed > 7);

			//InsertJeton(myTableau, columnPlayed - 1, isPlayerTurn);
			tokenLine = InsertJeton(myTableau, columnPlayed - 1, isPlayerTurn);
		}
#pragma region IA
		else
		{
			int random = rand() % 7 + 1;//Va entre 1 et 7 
			system("cls");

			cout << "IA thinking." << endl;
			Sleep(500);
			system("cls");

			cout << "IA thinking.." << endl;
			Sleep(500);
			system("cls");

			cout << "IA thinking..." << endl;
			Sleep(500);
			system("cls");

			//cout << "\033[95m" << "Le random trouve = " << "\033[0m" << random << endl;
			cout << "\033[95m" << "La colonne visee est = ("  << random << ") donc la [" << random-1 <<"]" << "\033[0m" << endl;
			system("pause");

			//InsertJeton(myTableau, random, isPlayerTurn);
			tokenLine = InsertJeton(myTableau, random-1, isPlayerTurn);
			columnPlayed = random;
		}
#pragma endregion

		
		PrintTableau(myTableau);

		cout << "columnPlayed = [" << columnPlayed-1 << "]"<< endl;

		//Tu as insere le jeton. maintenant faut 
		if (CheckVictory(myTableau, tokenLine, columnPlayed-1, isPlayerTurn)) // verifier le gagnant
		{
			cout << "Tu as trouve un gagnant" << endl;
			if (isPlayerTurn) 
			{
				cout << "Le gagnant est PLAYER" << endl;
			}
			else 
			{
				cout << "Le gagnant est AI" << endl;
			}
			break;
		}
		/*
		else if (CheckGridFull(myTableau))
		{
			//Si oui Match null
			cout << "\033[95m" << "MATCH NUL" << "\033[0m" << endl;
			system("pause");
			break;
		}
		//Si non // Alors t'as pas de gagnant, et ta grille est pas pleine. Donc ça tourne
		*/

		cout << "\033[31m" << "FIN DU TOUR" << "\033[0m" << endl;
		system("pause");
		isPlayerTurn = !isPlayerTurn;
	}//fin du while ici

	//LOGIC END GAME
	cout << "\033[95m" << "LOGIC END MISSING HERE" << "\033[0m" << endl;


}


int InsertJeton(char myTableau[line][column], int columnPlayed, bool& isPlayerTurn)
{
	/* -1---2---3---4---5---6---7--
	5  |   |   |   |   |   |   |   |
	  ----------------------------
	4  |   |   |   |   |   |   |   |
	  ----------------------------
	3  |   |   |   |   |   |   |   |
	   ----------------------------
	2  |   |   |   |   |   |   |   |
	   ----------------------------
	1  |   |   |   |   |   |   |   |
	   ----------------------------
	0  |   |   |   |   |   |   |   |
	   ----------------------------*/
	for (int i = 0; i < line; i++)//Check les lignes depuis le bas, aussi longtemps que i >=0, tu tournes 
	{
		cout << "\033[95m" << "|-INSERT JETON-| Je checke actuellement la ligne [" << i << "] de la colonne [" << columnPlayed <<"]" << "\033[0m"  << endl;

		if (myTableau[i][columnPlayed] == ' ')//Si la case est vide
		{
			cout << "\033[95m" << "ton i checke = " << i << " et il est vide " << "\033[0m" << endl;
			system("pause");
			isPlayerTurn == true ? myTableau[i][columnPlayed] = 'X' : myTableau[i][columnPlayed] = 'O';
			// myTableau[i][columPlayed] = (isPlayerTurn == true ? 'X' : 'O');
			int tokenLine = i;
			return tokenLine;
			//break;
		}
		else
		{
			cout << "\033[31m" << "/!| ton i = " << i << " n'est PAS vide /!|" << "\033[0m" << endl;

		}
	}
}

bool CheckVictory(char myTableau[line][column], int linePlayed, int columnPlayed, bool& isPlayerTurn)
{
	int VictoryChecker = 1;
	char currentSymboleLooking = isPlayerTurn ? 'X' : 'O';//astuce du LLM mais je voulais eviter de dupliquer mes if X || if O

#pragma region QUELQUES DETAILS POUR MOI
	/*
	return horizontal()|| vertical()|| diagonal();
	*/

	//VERTICAL BAS --- aussi longtemps que i > que ta ligne jouee - 4 ET que i est positif
	/*
	Je mets linePlayed-1 car le jeton placé est deja bon donc je descends d'un cran
	Ensuite, aussi longtemps que i > linePlayed - 4 ==> je parcours 3 lignes max
	Ex:
	si linePlayed = 4
	Tour 0 : i=3 > que 0
	Tour 1 : i =2 > que 0
	tour 2 : i=1 > 0
	tour 3 i=0 > 0 DONC STOP
	puis, i >= 0 pour ne pas vérifier une ligne négative
	*/
#pragma endregion

#pragma region VERTICAL BAS

		cout << "----------------Debut de VERTICAL BAS----------------------" << endl;
		cout << "\033[31m" << "LinePlayed = ["<< linePlayed<< "]" <<" et columnPlayed = [" << columnPlayed <<"]" << "\033[0m" << endl;
		cout << "currentSymboleLooking = " << currentSymboleLooking << endl;

	for (int i = linePlayed - 1; i > linePlayed - 4 && i >= 0; i--)
	{
		if (myTableau[i][columnPlayed] == currentSymboleLooking)
		{
			cout << "\033[31m" << "Ligne verifiee = [" << i << "]" << "\033[0m" << endl;
			VictoryChecker++;
			cout << "VictoryChecker_VerTicalBas = " << VictoryChecker << endl;
			cout << "*****************************************************" << endl;
		}
		else
		{
			cout << "myTableau[" << i << "][" << columnPlayed << "] ne contient pas de " << currentSymboleLooking << endl;
			break;
		}

		if (VictoryChecker >= 4)
		{
			cout << "Tu as 4 jetons verticaux ! ";
			system("pause");
			return true;
		}
	}

	cout << "----------------FIN de VERTICAL BAS------------------------" << endl;
	cout << endl;

	
#pragma endregion
	
	VictoryChecker = 1;

#pragma region GAUCHE
		cout << "----------------Debut de GAUCHE----------------------" << endl;
		cout << "\033[31m" << "LinePlayed = [" << linePlayed << "]" << " et columnPlayed = [" << columnPlayed << "]" << "\033[0m" << endl;
		cout << "currentSymboleLooking = " << currentSymboleLooking << endl;

	for (int i = columnPlayed - 1; i > columnPlayed - 4 && i >= 0; i--)
	{

		if (myTableau[linePlayed][i] == currentSymboleLooking)
		{
			cout << "\033[31m" << "Ligne verifiee = [" << i << "]" << "\033[0m" << endl;
			VictoryChecker++;
			cout << "VictoryChecker_GAUCHE = " << VictoryChecker << endl;
			cout << "*****************************************************" << endl;
		}
		else
		{
			cout << "myTableau[" << i << "][" << columnPlayed << "] ne contient pas de " << currentSymboleLooking << endl;
			break;
		}

		if (VictoryChecker >= 4)
		{
			cout << "Tu as 4 jetons Horizontaux ! ";
			system("pause");
			return true;
		}
	}
	cout << "----------------FIN de GAUCHE------------------------" << endl;
	cout << endl;

	
#pragma endregion
	
	VictoryChecker = 1;

#pragma region DROITE
	cout << "----------------Debut de DROITE----------------------" << endl;
	cout << "\033[31m" << "LinePlayed = [" << linePlayed << "]" << " et columnPlayed = [" << columnPlayed << "]" << "\033[0m" << endl;

	
	for (int i = columnPlayed + 1; i < columnPlayed - 4 && i <= column; i++)
	{
		cout << "\033[31m" << "LinePlayed = [" << linePlayed << "]" << " et columnPlayed = [" << columnPlayed << "]" << "\033[0m" << endl;
		cout << "currentSymboleLooking = " << currentSymboleLooking << endl;

		if (myTableau[line][i] == currentSymboleLooking)
		{
			cout << "\033[31m" << "Ligne verifiee = [" << i << "]" << "\033[0m" << endl;
			VictoryChecker++;
			cout << "VictoryChecker_DROITE = " << VictoryChecker << endl;
			cout << "*****************************************************" << endl;
		}
		else
		{
			cout << "myTableau[" << i << "][" << columnPlayed << "] ne contient pas de " << currentSymboleLooking << endl;
			break;
		}

		if (VictoryChecker >= 4)
		{
			cout << "Tu as 4 jetons Horizontaux ! ";
			system("pause");
			return true;
		}
	}
	cout << "----------------FIN de DROITE------------------------" << endl;
	cout << endl;
	
#pragma endregion

	VictoryChecker = 1;

#pragma region DIA HAUT GAUCHE
	cout << "----------------Debut de DIA HAUT GAUCHE----------------------" << endl;
	cout << "\033[31m" << "LinePlayed = [" << linePlayed << "]" << " et columnPlayed = [" << columnPlayed << "]" << "\033[0m" << endl;

	for (int i = linePlayed+1, j = columnPlayed-1; i <= line && j >= 0; i++, j--)
	{
		if (myTableau[i][j] == currentSymboleLooking)
		{
			cout << "\033[31m" << "Ligne verifiee = [" << i << "] et colonne verifiee [" << j << "]" << "\033[0m" << endl;
			VictoryChecker++;
			cout << "VictoryChecker_DIAHAUTGAUCHE = " << VictoryChecker << endl;
			cout << "*****************************************************" << endl;
		}
		else
		{
			cout << "myTableau[" << i << "][" << columnPlayed << "] ne contient pas de " << currentSymboleLooking << endl;
			break;
		}

		if (VictoryChecker >= 4)
		{
			cout << "Tu as 4 jetons diagonaux ! ";
			system("pause");
			return true;
		}
	}

#pragma endregion

	VictoryChecker = 1;

#pragma region DIA BAS GAUCHE
	//DIA BAS GAUCHE
	for (int i = linePlayed - 1, j = columnPlayed - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (myTableau[i][j] == 'X')
		{
			system("pause");
			VictoryChecker++;
			cout << "Tu as trouve " << i + 1 << "victoire(s) en BAS GAUCHE" << endl;
		}
		else
		{
			break;
		}
	}
	if (VictoryChecker >= 4)
	{
		return true;//Le return continue t il la fonction ? Oui
	}
	VictoryChecker = 1;
#pragma endregion

#pragma region DIA HAUT DROIT
	//DIA HAUT DROIT
	for (int i = linePlayed, j = columnPlayed; i <= line && j <= column; i++, j++)
	{
		if (myTableau[i][j] == 'X')
		{
			system("pause");
			VictoryChecker++;
			cout << "Tu as trouve " << i + 1 << "victoire(s) en HAUT DROIT" << endl;
		}
		else
		{
			break;
		}
	}
	if (VictoryChecker >= 4)
	{
		return true;//Le return continue t il la fonction ? Oui
	}
	VictoryChecker = 1;


#pragma endregion

#pragma region DIA BAS DROIT
	//DIA BAS DROIT
	for (int i = linePlayed, j = columnPlayed; i >= 0 && j <= column; i--, j++)
	{
		if (myTableau[i][j] == 'X')
		{
			system("pause");
			VictoryChecker++;
			cout << "Tu as trouve " << i + 1 << "victoire(s) en BAS DROIT" << endl;
		}
		else
		{
			break;
		}
	}
	if (VictoryChecker >= 4)
	{
		return true;//Le return continue t il la fonction ? Oui
	}
	VictoryChecker = 1;
#pragma endregion


	cout << "\033[95m" << "---Tu as fait le tour des checkVictory et tu n'as trouve aucun gagnant----" << "\033[0m" << endl;
	system("pause");
}

void PrintTableau(char myTableau[line][column])
{
	system("cls");

	cout << "\033[38;5;208m --1---2---3---4---5---6---7-- \033[0m" << endl;
	for (int i = line - 1; i >= 0; i--) // rows
	{
		cout << " | ";
		for (int j = 0; j < column; j++) // columns
		{
			cout << myTableau[i][j] << " | ";
		}

		cout << endl << "-------------------------------" << endl;
	}


	//Sleep(1000);
}


bool CheckGridFull(char myTableau[line][column])
{
	int gridColumnChecker = 0;

	for (int j = 0; j <= column; j++)
	{
		if (myTableau[line][j] != ' ')
		{
			gridColumnChecker++;
			cout << gridColumnChecker << "/" << column << " colonnes verifiees" << endl;

			if (gridColumnChecker >= column)
			{
				//Ta grille est full
				cout  << "Ta grille est full" << endl;
				return true;
			}
		}
	}
}

bool checkColumnFull(char myTableau[line][column], int columnPlayed)
{
	if (myTableau[line][columnPlayed] != ' ')
	{
		return true;//Colonne full
	}
}

void WinningScreen()
{
	system("cls");
	cout << " --------------WINNING SCREEN--------------" << endl;
}