#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    Isograms = GetValidWords(Words);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &PlayerInput)
{
    // Basic Game Loop
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(PlayerInput);
    }
    // End Of The Game Loop
}

void UBullCowCartridge::SetupGame()
{

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("WELCOME TO THE BULL COWS!"));
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len()); // Magic Number
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord);
    PrintLine(TEXT("Type in your guess and press enter to continue:"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Game Is Over! Press \"ENTER"
                   " to continue game."));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    WinGame(Guess);

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }
    if (CompareLengths(Guess))
    {
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Soory, try guessing again, \nyou have %i lives remaining"), Lives);
        return;
    }

    void DecreaseLive();
    Dead();

    FBullCowCount Score = GetBullCows(Guess);
    PrintLine(TEXT("You have %i bulls and %i cows"), Score.BullCount, Score.CowCount);
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

bool UBullCowCartridge::CompareLengths(const FString &Guess) const
{
    return Guess.Len() != this->HiddenWord.Len() ? 1 : 0;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> &WordList) const
{
    TArray<FString> ValidWords;

    for (FString word : WordList)
    {
        if (word.Len() >= 4 && word.Len() <= 8 && IsIsogram(word))
        {
            ValidWords.Emplace(word);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString &Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.BullCount++;
            continue;
        }
        for (int32 HiddenWordIndex = 0; HiddenWordIndex < Guess.Len(); HiddenWordIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenWordIndex])
            {
                Count.CowCount++;
                break;
            }
        }
    }
    return Count;
}

void UBullCowCartridge::Dead()
{
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }
}

void UBullCowCartridge::DecreaseLive()
{
    PrintLine(TEXT("You Lost 1 Life."));
    --Lives;
}

void UBullCowCartridge::WinGame(const FString &Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("YOU HAVE WON!!!"));
        EndGame();
        return;
    }
}