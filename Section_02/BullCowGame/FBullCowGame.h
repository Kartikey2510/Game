#pragma once
#include <string>
using FString = std::string;
using int32 = int;
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};
enum class EGuessStatus
{   Invalid_Guess,
	OK,
	Not_isogram,
	Wrong_Length,
	Not_Lowercase,
};
class FBullCowGame
{
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 Hiddenwordlength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsLowercase(FString) const;

	void Reset();//TODO make a more rich value return
	FBullCowCount SubmitValidGuess(FString);
    //^^please try and ignore this and focus on the code above^^
private:
	//see constructor for initialisation
	int32 MyMaxTry;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;

};
