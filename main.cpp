#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <iomanip>
using namespace std;

const int MAXWORDS = 186930;

void drawHangMan(int);
bool alreadyUsed(string, string);
bool wrongUsed(string, string);
bool vowelPick(string &, string &, string &, string &, int &, int &);
void findAll(string, string, string);
void pickNext(string &, string &, string &, string &, int &, int &);

int main(){
	srand(time(NULL));
	int wins = 0, numGames = 0;
	char response;
	string wordToGuess, correctGuesses, wrongLetters;
	string wordChoices[MAXWORDS];
	ifstream in;
	cout << "Loading dictionary..." << endl;
	in.open("hangMan.txt");
	int k = MAXWORDS;
	for(int i = 0; i < k; i++)
		in >> wordChoices[i];		

	in.close();
	cout << "Press enter to continue...";
	cin.get();
	system("cls");

	cout << setw(50) << "Welcome to hangman!" << endl << endl
		 << " ___________.._______" << endl
		 <<	"| .__________))______|" << endl
		 <<	"| | / /      ||" << endl
		 <<	"| |/ /       ||" << endl
		 <<	"| | /        ||.-\'\'." << endl
		 <<	"| |/         |/  _  \\" << endl
		 <<	"| |          ||  `/,|" << endl
		 <<	"| |          (\\`_.' " << endl
		 <<	"| |         .-`--'." << endl
		 <<	"| |        /Y . . Y\\\\" << endl
		 <<	"| |       // |   |  \\\\" << endl
		 <<	"| |      //  | . |   \\\\" << endl
		 <<	"| |     ')   |   |    (`" << endl
		 <<	"| |          || ||" << endl
		 <<	"| |          || ||" << endl
		 <<	"| |          || ||" << endl
		 <<	"| |          || ||" << endl
		 <<	"| |         / | | \\" << endl
		 <<	"__________| `-  `-  |_____|" << endl
		 <<	"| |       \\ \         | |" << endl
		 <<	"| |        \\ \        | |" << endl
		 <<	": :         \\ \       : :  sk" << endl
		 << "Art by http://ascii.co.uk/art/hangman" << endl << endl;

	cout << "Rules of the game: " << endl
		 << "You have 8 chances to guess the word correctly." << endl
		 << "If not, stickman will hang!!!" << endl
		 << "You will not be charged more than once for " 
		 << "making the same mistake."
		 << endl << endl;
	system("pause");
	system("cls");

	bool repeat = true;
	string letterPicked;
	do{
		//picking a random word in the range of the MAXWORD list
		wordToGuess = wordChoices[(rand() % 186930 + 1)];
		int len = wordToGuess.length(), miss = 0, hit = 0;
		drawHangMan(0);
		correctGuesses.assign(len, '.');

		while(miss < 8){
			cout << "The correct word has "<< len << " letters: "
				 << correctGuesses << endl 
				 <<"Your misses so far " << miss << ": "<< wrongLetters << endl << endl
			     << "Pick a letter: ";
			cin >> letterPicked;

			int pick = wordToGuess.find(letterPicked, 0);
			// checking to see if a letter has been used already
			if(alreadyUsed(correctGuesses, letterPicked) || wrongUsed(wrongLetters, letterPicked)){
				cout << "You have used that letter already!" << endl; 
				system("pause");
			}
			//increments miss by 1 when letter is not an element of wordToGuess
			else if(pick < 0){
				miss++;
				wrongLetters += letterPicked;
			}
			// the letter is an element of wordToGuess,
			else{
				//finds all positions of the letter picked
				bool found = true;
				int positionFound, lastPosition = 0;
				do{
					positionFound = wordToGuess.find(letterPicked, lastPosition);
					if(positionFound >= 0){
						correctGuesses.replace(positionFound, 1, letterPicked);
						lastPosition = positionFound + 1;
						hit++;
					}
					else{
						found = false;
					}
				}while(found);
			}
			system("cls");
			drawHangMan(miss);
			//game over with a loss
			if(miss >= 8){
				cout << "You killed stickman!" << endl
					 << "The word was " << wordToGuess << "." << endl				     
				     << "Who will raise his stick babies?" << endl << endl;
			}
			//game over with a win
			if(hit == correctGuesses.length()){
				system("cls");
				drawHangMan(9);
				cout << "Hooray!! You saved stickman!! " << endl
					 << "The word was " << correctGuesses << "!" << endl << endl;
				wins++;
				break;
			}
		}
		numGames++;
		cout << "Would you like to play again? (Y or N): ";
		cin >> response;
		if(response == 'n' || response == 'N')
			repeat = false;
		system("cls");
		wrongLetters.erase();
	}while(repeat);

	cout << "Thank you for playing hangman! You had " << wins  
		 << " win" <<((wins > 1 || wins == 0) ? 's' : ' ') << " out of "
		 << numGames << " game" << ((numGames > 1 || numGames == 0) ? 's' : ',') <<endl
		 << "Goodbye!!" << endl;
	system("pause");
 	return 0;
}

void drawHangMan(int x){
	switch(x){
		case 0: cout << "_________" << endl
					 << " |     | " << endl
					 << " | " << endl
					 << " | " << endl
					 << " | " << endl
					 << " | " << endl
					 << "``````````" << endl;
			break;
		case 1: cout << "_________" << endl
					 << " |     | " << endl
					 << " |   (   )" << endl
					 << " | " << endl
					 << " | " << endl
					 << " | " << endl
					 << "``````````" << endl;
			break;
		case 2: cout << "_________" << endl
					 << " |     | " << endl
					 << " |   (o_o)" << endl
					 << " |     " << endl
					 << " |     " << endl
					 << " | " << endl
					 << "``````````" << endl;
			break;
		case 3: cout << "_________" << endl
					 << " |     | " << endl
					 << " |   (o_o)" << endl
					 << " |     | " << endl
					 << " |     |" << endl
					 << " | " << endl
					 << "``````````" << endl;
			break;
		case 4: cout << "_________" << endl
					 << " |     | " << endl
					 << " |   (o_o)" << endl
					 << " |    _| " << endl
					 << " |     |" << endl
					 << " | " << endl
					 << "``````````" << endl;
			break;
		case 5: cout << "_________" << endl
					 << " |     | " << endl
					 << " |   (o_o)" << endl
					 << " |    _|_ " << endl
					 << " |     |" << endl
					 << " |     " << endl
					 << "``````````" << endl;
			break;
		case 6: cout << "_________" << endl
					 << " |     | " << endl
					 << " |   (o_o)" << endl
					 << " |    _|_ " << endl
					 << " |     |" << endl
					 << " |    / " << endl
					 << "``````````" << endl;
			break;
		case 7: cout << "_________" << endl
					 << " |     | " << endl
					 << " |   (O_O)" << endl
					 << " |    \\|/ " << endl
					 << " |     |" << endl
					 << " |    / \\" << endl
					 << "``````````" << endl;
			break;
		case 8: cout << "_________" << endl
					 << " |     | " << endl
					 << " |   (x_x)" << endl
					 << " |     | " << endl
					 << " |    /|\\" << endl
					 << " |    / \\" << endl
					 << " ````\\" << endl
					 << "      \\" << endl;
			break;
		case 9: cout << endl
					 << "    (^_^)" << endl
					 << "     \\|/ " << endl
					 << "      |" << endl
					 << "     / \\" << endl;
			break;
	}
	return;
}

bool alreadyUsed(string s, string t){
	int x = s.find(t, 0);
	if(x >= 0)
		return true;
	return false;
}

bool wrongUsed(string s, string t){
	int x = s.find(t, 0);
	if(x >= 0)
		return true;
	return false;
}

bool vowelPick(string guess, string picked, string wrong, string right, int hit, int miss){
	string vowel = "";
	switch(miss){
		case 0:
			vowel = "e";
			int x = guess.find(vowel, 0);
			if(x < 0){
				miss++;
				wrong += vowel;
				return false;
			}
			findAll(picked, guess, vowel);
			hit++;
			return true;
			break;
			  
		case 1:
			vowel = "i";
			int x = guess.find(vowel, 0);
			if(x < 0){
				miss++;
				wrong += vowel;
				return false;
			}
			findAll(picked, guess, vowel);
			hit++;
			return true;
			break;

		case 2:
			vowel = "o";
			int x = guess.find(vowel, 0);
			if(x < 0){
				miss++;
				wrong += vowel;
				return false;
			}
			findAll(picked, guess, vowel);
			hit++;
			return true;
			break;

		case 3:
			vowel = "a";
			int x = guess.find(vowel, 0);
			if(x < 0){
				miss++;
				wrong += vowel;
				return false;
			}
			findAll(picked, guess, vowel);
			hit++;
			return true;
			break;

		case 4:
			vowel = "u";
			int x = guess.find(vowel, 0);
			if(x < 0){
				miss++;
				wrong += vowel;
				return false;
			}
			findAll(picked, guess, vowel);
			hit++;
			return true;
			break;
	}
}

void findAll(string picked, string guess, string c){
		bool found = true;
		int positionFound, lastPosition = 0;
		do{
			positionFound = guess.find(c, lastPosition);
			if(positionFound >= 0){
				picked.replace(positionFound, 1, c);
				lastPosition = positionFound + 1;
			}
			else{
				found = false;
			}
		}while(found);
}

void pickNext(string guess, string pick, string wrong, string right, int miss, int hit){

}
