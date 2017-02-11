// Copyright Chase Hennion 2017

#pragma once

#include "Components/ActorComponent.h"
#include "MultiPlatePuzzle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FMultiPlatePuzzleEvent );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UMultiPlatePuzzle : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMultiPlatePuzzle();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Gets the index of the plate that the plaer is overlapping or returns -1 if no plate is overlapped.
	int32 GetOverlappingPlateIndex();

	UPROPERTY( BlueprintAssignable )
	FMultiPlatePuzzleEvent OnSolved;

	UPROPERTY( BlueprintAssignable )
	FMultiPlatePuzzleEvent OnCorrectPlate;

	UPROPERTY( BlueprintAssignable )
	FMultiPlatePuzzleEvent OnWrongPlate;

private:

	AActor* Player = nullptr;

	// An array of pressure plates that must be pressed in order.
	UPROPERTY( EditAnywhere )
	TArray< ATriggerVolume* > PressurePlates;
	
	// The index of the next plate that must be pressed to continue the puzzle
	int32 NextPlateIndex = 0;
	
};
