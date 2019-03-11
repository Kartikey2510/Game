#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintGameSummary();
void Printintro();
bool AskToPlayAgain();
int main();
void PlayGame();
FBullCowGame BCGame;
FText GetValidGuess();
int main()
{
	bool bPlayAgain;
	do
    {
	Printintro();
	PlayGame();
	bPlayAgain = AskToPlayAgain();
	}

	while(bPlayAgain);

	return 0;
}
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries=BCGame.GetMaxTries();
	//looping
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries)
	{
		FText Guess = GetValidGuess();

		//submit the valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls=" << BullCowCount.Bulls;
		std::cout << "Cows=" << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
}//loop continues till a valid guess is obtained
    FText GetValidGuess()  //TODO change to GetValidGuess
	{
		FText Guess = "";
		EGuessStatus Status = EGuessStatus::Invalid_Guess;
		do{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "try ";
		std::cout << CurrentTry;
		std::cout << " of " << BCGame.GetMaxTries();
		std::cout << " :";
		std::cout << "What's your guess? ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
			{
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.Hiddenwordlength() << " letter word \n";
				break;
			case EGuessStatus::Not_isogram:
				std::cout << "Please enter an isogram \n\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Enter the word in lowercase \n\n";
				break;
			default:
				break;
			}
		}
		while (Status != EGuessStatus::OK);
		std::cout << "You guessed: ";
		return Guess;
	}
	void PrintGameSummary()
	{ if (BCGame.IsGameWon())
	{
		std::cout << "you won\n";
	}
	else
	{
		std::cout << "better luck next time\n";
	}
	}
	void Printintro()
	{
		//intro to game
		std::cout << "Welcome to Bulls And Cows Game" << std::endl;
		std::cout << "Can you guess the ";
		std::cout << BCGame.Hiddenwordlength();
		std::cout << " letter world i am thinking of" << std::endl;
		return;
	}
	bool AskToPlayAgain()
	{
		std::cout << "Do you want to play again(y/n)?";
		FText Response = "";
		std::getline(std::cin, Response);
		return ((Response[0] == 'y') || (Response[0] == 'Y'));
	}