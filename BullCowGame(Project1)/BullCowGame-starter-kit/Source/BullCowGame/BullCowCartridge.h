// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount{
	int32 BullCount = 0;
	int32 CowCount = 0;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString &Input) override;

	void SetupGame();
	void EndGame();
	void Dead();
	void WinGame(const FString& Guess);
	void DecreaseLive();
	void ProcessGuess(const FString& Guess);

	FBullCowCount GetBullCows(const FString &Guess) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
	
	bool IsIsogram(const FString& Word) const;
	bool CompareLengths(const FString& Guess) const;

private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	TArray<FString> Isograms;
};