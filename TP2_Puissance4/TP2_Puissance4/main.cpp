#include <iostream>;
#include <windows.h> // for sleep
using std::cout;
using std::cin;
using std::endl;
//********************************************************************************************************30oct-21h11
const int line = 6;
const int column = 7;

//FONCTIONS PROTOTYPE-----------------------------------------------------------------------------------|
void GameplayTurn(char myTableau[line][column], bool& isPlayerTurn);//----------------------------------|
int InsertJeton(char myTableau[line][column], int columPlayed, bool& isPlayerTurn);//-------------------|
void PrintTableau(char myTableau[line][column]);//------------------------------------------------------|
bool CheckVictory(char myTableau[line][column], int linePlayed, int columnPlayed, bool& isPlayerTurn);//|
void EndingScreen(bool isPlayerTurn, bool CheckGridFull);//---------------------------------------------|
bool CheckGridFull(char myTableau[line][column]);//-----------------------------------------------------|
bool checkColumnFull(char myTableau[line][column], int columnPlayed);//---------------------------------|
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
							{'X','O','X', 'O', 'X','O','X'},//0
							{'O','X','O', 'X', 'O','X','O'},//1
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
		int lastIARandom = -1;

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

				cout << "\033[93m" << "Colonne pleine ? " << (checkColumnFull(myTableau, columnPlayed - 1) ? "Oui" : "Non") << "\033[0m" << endl;

				//system("pause");
			} while (columnPlayed < 1 || columnPlayed > 7 || checkColumnFull(myTableau, columnPlayed-1));

			tokenLine = InsertJeton(myTableau, columnPlayed - 1, isPlayerTurn);
		}
#pragma region IA
		else
		{
			system("cls");

			cout << "IA thinking." << endl;
			Sleep(300);
			system("cls");

			cout << "IA thinking.." << endl;
			Sleep(300);
			system("cls");

			cout << "IA thinking..." << endl;
			Sleep(300);
			system("cls");
			do
			{
				int random = rand() % 7 + 1;//Va entre 1 et 7 
				lastIARandom = random;
				PrintTableau(myTableau);
				cout << "AI joue dans la colonne (" << lastIARandom<< ")" << endl;
				
				
				//cout << "\033[95m" << "La colonne visee est = (" << random << ") donc la [" << random - 1 << "]" << "\033[0m" << endl;
				//cout << "\033[93m" << "Colonne pleine ? " << (checkColumnFull(myTableau, lastIARandom - 1) ? "Oui" : "Non") << "\033[0m" << endl;
				//system("pause");

			} while (checkColumnFull(myTableau, lastIARandom -1) == true);
			Sleep(2500);
			//cout << "\033[95m" << "La colonne visee est = (" << lastIARandom << ") donc la [" << lastIARandom - 1 << "]" << "\033[0m" << endl;

			tokenLine = InsertJeton(myTableau, lastIARandom -1, isPlayerTurn);
			columnPlayed = lastIARandom;
		}
#pragma endregion

		
		PrintTableau(myTableau);
		Sleep(1500);
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
		else if (CheckGridFull(myTableau))
		{
			//Si oui Match null
			cout << "\033[95m" << "MATCH NUL" << "\033[0m" << endl;
			//system("pause");
			break;
		}
		//Si non // Alors t'as pas de gagnant, et ta grille est pas pleine. Donc ça tourne
		

		cout << "\033[31m" << "FIN DU TOUR" << "\033[0m" << endl;

		isPlayerTurn = !isPlayerTurn;
	}//fin du while ici

	cout << "\033[31m" << "Je vais passer a lecran winning" << "\033[0m" << endl;
	//system("pause");
	
	PrintTableau(myTableau);

	EndingScreen(isPlayerTurn, CheckGridFull(myTableau));
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
			//system("pause");
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
			//system("pause");
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
			//system("pause");
			return true;
		}
	}
	cout << "----------------FIN de GAUCHE------------------------" << endl;
	cout << endl;

	
#pragma endregion

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
			//system("pause");
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
			//system("pause");
			return true;
		}
	}

	cout << "----------------FIN de DIA HAUT GAUCH------------------------" << endl;
	cout << endl;

#pragma endregion

#pragma region DIA BAS DROIT
	cout << "----------------Debut de DIA BAS DROIT----------------------" << endl;
	cout << "\033[31m" << "LinePlayed = [" << linePlayed << "]" << " et columnPlayed = [" << columnPlayed << "]" << "\033[0m" << endl;

	for (int i = linePlayed - 1, j = columnPlayed + 1; i >= 0 && j <= column; i--, j++)
	{
		if (myTableau[i][j] == currentSymboleLooking)
		{
			cout << "\033[31m" << "Ligne verifiee = [" << i << "] et colonne verifiee [" << j << "]" << "\033[0m" << endl;
			VictoryChecker++;
			cout << "VictoryChecker_DIABASDROIT = " << VictoryChecker << endl;
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
			//system("pause");
			return true;
		}
	}
	cout << "----------------FIN de DIA BAS DROIT------------------------" << endl;
	cout << endl;
#pragma endregion
	
	VictoryChecker = 1;

#pragma region DIA BAS GAUCHE
	cout << "----------------Debut de DIA BAS GAUCHE----------------------" << endl;
	cout << "\033[31m" << "LinePlayed = [" << linePlayed << "]" << " et columnPlayed = [" << columnPlayed << "]" << "\033[0m" << endl;

	for (int i = linePlayed - 1, j = columnPlayed - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (myTableau[i][j] == currentSymboleLooking)
		{
			cout << "\033[31m" << "Ligne verifiee = [" << i << "] et colonne verifiee [" << j << "]" << "\033[0m" << endl;
			VictoryChecker++;
			cout << "VictoryChecker_DIABASGAUCHE = " << VictoryChecker << endl;
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
			//system("pause");
			return true;
		}
	}

	cout << "----------------FIN de DIA BAS GAUCHE------------------------" << endl;
	cout << endl;
	
#pragma endregion

#pragma region DIA HAUT DROIT
	cout << "----------------Debut de DIA HAUT DROIT----------------------" << endl;
	cout << "\033[31m" << "LinePlayed = [" << linePlayed << "]" << " et columnPlayed = [" << columnPlayed << "]" << "\033[0m" << endl;

	for (int i = linePlayed+1, j = columnPlayed+1; i <= line && j <= column; i++, j++)
	{
		if (myTableau[i][j] == currentSymboleLooking)
		{
			cout << "\033[31m" << "Ligne verifiee = [" << i << "] et colonne verifiee [" << j << "]" << "\033[0m" << endl;
			VictoryChecker++;
			cout << "VictoryChecker_DIAHAUTDROIT = " << VictoryChecker << endl;
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
			//system("pause");
			return true;
		}
	}

	cout << "----------------FIN de DIA HAUT DROIT------------------------" << endl;
	cout << endl;
#pragma endregion
	
	cout << "\033[95m" << "---Tu as fait le tour des checkVictory et tu n'as trouve aucun gagnant----" << "\033[0m" << endl;
	//system("pause");
	return false;
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
}

bool CheckGridFull(char myTableau[line][column])
{
	int gridColumnChecker = 0;

	for (int j = 0; j < column; j++)
	{
		//cout << "Je checke [" << j << "]" << endl;
		if (myTableau[line - 1][j] == ' ')
		{
			//cout << "Je suis dans [" << line - 1 << "][" << j << "] = ->" << myTableau[line - 1][j] << "<-" << endl;
			//cout << "Jai trouve [5][" << j << "] qui est vide" << endl;

			return false;
		}
		else
		{
			gridColumnChecker++;
			//cout << gridColumnChecker << "/" << column << " colonnes pleines" << endl;
			if (gridColumnChecker == column)
				return true;
		}
		
	}
	
}

bool checkColumnFull(char myTableau[line][column], int columnPlayed)
{
	if (myTableau[line-1][columnPlayed] != ' ')
	{
		//cout << "|checkColumnFull+| je regarde actuellement [" << line-1 << "][" << columnPlayed << "]" << endl;
		//cout << "|checkColumnFull+| La colonne contient " << myTableau[line-1][columnPlayed] << endl;
		return true;//Colonne full
	}
	else 
	{
		//cout << "|checkColumnFull-| La colonne vide contient : ->" << myTableau[line-1][columnPlayed] << "<-" << endl;
		return false;//Comment ca je dois declarer un false ? C'est pas false par defaut MAX ? 
	}
}

void EndingScreen(bool isPlayerTurn, bool CheckGridFull)
{
	system("pause");

	cout << endl;
	cout << "\033[96m";
	cout << "==============================================" << endl;
	cout << "        PUISSANCE 4 - KEVIN BACHELIER         " << endl;
	cout << "==============================================" << endl;
	cout << "\033[0m" << endl;

	if (CheckGridFull) 
	{
		cout << "\033[93m";
		cout << "                MATCH NUL                     " << endl;
		cout << endl;
		cout << "                DRAW!                         " << endl;
		cout << "==============================================" << endl;
		cout << "\033[0m";

		return;
	}

	if (isPlayerTurn)
	{
		cout << "\033[92m";
		cout << "             V I C T O I R E !                " << endl;
		cout << endl;
		cout << "              PLAYER WINS!                    " << endl;
		cout << "==============================================" << endl;
		cout << "\033[0m";
	}
	else
	{
		cout << "\033[91m";
		cout << "              D E F A I T E                   " << endl;
		cout << endl;
		cout << "                AI WINS!                      " << endl;
		cout << "==============================================" << endl;
		cout << "\033[0m";
	}
	system("pause");
	cout << "Bonsoir" << endl;
}