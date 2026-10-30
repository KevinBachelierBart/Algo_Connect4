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
void InsertJeton(char myTableau[line][column], int columPlayed, bool& isPlayerTurn);//------------------|
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
							{' ',' ',' ', ' ', ' ',' ',' '},//0
							{' ',' ',' ', ' ', ' ',' ',' '},//1
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

			InsertJeton(myTableau, columnPlayed - 1, isPlayerTurn);
		}
		else
		{
			int random = rand() % 7 + 1;
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

			cout << "\033[95m" << "Le random trouve = " << "\033[0m" << random << endl;
			system("pause");

			InsertJeton(myTableau, random, isPlayerTurn);
		}

		//Tu as insere le jeton. maintenant faut 
		if (CheckVictory(myTableau, line, columnPlayed, isPlayerTurn)) // verifier le gagnant
		{
			break;
		}
		else if (CheckGridFull(myTableau))
		{
			//Si oui Match null
			cout << "\033[95m" << "MATCH NUL" << "\033[0m" << endl;
			system("pause");
			break;
		}
		//				Si non // Alors t'as pas de gagnant, et ta grille est pas pleine. Donc ça tourne


		isPlayerTurn = !isPlayerTurn;
	}//fin du while ici

	//LOGIC END GAME

}


void InsertJeton(char myTableau[line][column], int columPlayed, bool& isPlayerTurn)
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
		cout << "\033[95m" << "INSERT JETON Je checke actuellement la ligne " << "\033[0m" << i << endl;

		if (myTableau[i][columPlayed] == ' ')//Si la case est vide
		{
			cout << "\033[95m" << "ton i checke = " << i << " et il est vide " << "\033[0m" << endl;
			isPlayerTurn == true ? myTableau[i][columPlayed] = 'X' : myTableau[i][columPlayed] = 'O';
			// myTableau[i][columPlayed] = (isPlayerTurn == true ? 'X' : 'O');

			if (CheckVictory(myTableau, i, columPlayed, isPlayerTurn))
			{
				cout << "WINNER" << endl;
				system("pause");
				WinningScreen();
				return;
			}
			break;
		}
		else
		{
			cout << "\033[95m" << "/!| ton i = " << i << " et il est PAS vide /!|" << "\033[0m" << endl;

		}


	}

	//if (CheckGridFull(myTableau,columnPlayed))
	//{
	//	//Ta grille est pleine
	//	WinningScreen();
	//}
}

bool CheckVictory(char myTableau[line][column], int linePlayed, int columnPlayed, bool& isPlayerTurn)
{
	int VictoryChecker = 1;

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
	for (int i = linePlayed - 1; i > linePlayed - 4 && i >= 0; i--)
	{
		cout << "\033[95m" << "Vertical bas : i = " << i << " " << "\033[0m" << endl;

		if (myTableau[i][columnPlayed] == 'X')
		{
			system("pause");
			cout << "Tu as trouve " << i + 1 << "victoire(s) en VERTICAL BAS" << endl;
			VictoryChecker++;

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

#pragma region GAUCHE
	for (int i = columnPlayed - 1; i > columnPlayed - 4 && i >= 0; i--)
	{
		cout << "\033[95m" << "GAUCHE : i = " << i << " " << "\033[0m" << endl;

		if (myTableau[i][columnPlayed] == 'X')
		{
			system("pause");
			cout << "Tu as trouve " << i + 1 << "victoire(s) a GAUCHE" << endl;
			VictoryChecker++;

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

#pragma region DROITE
	for (int i = columnPlayed + 1; i < columnPlayed - 4 && i <= column; i++)
	{
		cout << "\033[95m" << "DROITE : i = " << i << " " << "\033[0m" << endl;

		if (myTableau[i][columnPlayed] == 'X')
		{
			system("pause");
			cout << "Tu as trouve " << i + 1 << "victoire(s) a DROITE" << endl;
			VictoryChecker++;

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

#pragma region DIA HAUT GAUCHE
	//DIA HAUT GAUCHE
	for (int i = linePlayed, j = columnPlayed; i <= line && j >= 0; i++, j--)
	{
		if (myTableau[i][j] == 'X')
		{
			system("pause");
			VictoryChecker++;
			cout << "Tu as trouve " << i + 1 << "victoire(s) en DIA HAUT GAUCHE" << endl;
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

	cout << "\033[38;5;208m -1---2---3---4---5---6---7-- \033[0m" << endl;
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
			cout << gridColumnChecker << "/" << column + 1 << " colonnes verifiees" << endl;

			if (gridColumnChecker >= column)
			{
				//Ta grille est full
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