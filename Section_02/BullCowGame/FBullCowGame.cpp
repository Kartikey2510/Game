#include "FBullCowGame.h"
#include <map>
#define TMap std::map 
using int32 = int;

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES=8;
	MyCurrentTry = 1;
	MyMaxTry = MAX_TRIES;
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTry;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::Hiddenwordlength() const
{   
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString MyWord) const
{
	if (!IsIsogram(MyWord))   //word is not an isogram
	{
		return EGuessStatus::Not_isogram;
	}
	else if (!IsLowercase(MyWord)) // not in lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (MyWord.length() != Hiddenwordlength()) //wrong length
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}
bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (islower(Letter))
			return true;
		else
			return false;
	}
}
//receives a VALID guess,increment turn, and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	//loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//compare letters against guess
			if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				if (MHWChar == GChar)
				{
					//if they match then
						//increment bulls if they're in the same place
					BullCowCount.Bulls++;
				}

				else
				{//increment cows if not
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	//treat 0 and 1 letter words as isogram
	if (Guess.length() <= 1)
	{
		return true;
	}
	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess)
	{
		//loop through all the letters of the word
		   //if the letter is in the map
		if (LetterSeen[Letter]) {
			//we do not have an isogram
			return false;
		}
		else { //add the letter to the map
			LetterSeen[Letter] = true;
		}
	}
}
