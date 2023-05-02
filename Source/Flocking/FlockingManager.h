// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Agent.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{

public:
	GENERATED_BODY()

	void Init(UWorld* world, UStaticMeshComponent* mesh, AActor* target);
	void Flock();

private:
	FVector Rule1(AAgent* b);
	FVector Rule2(AAgent* b);
	FVector Rule3(AAgent* b);
	FVector Rule4(AAgent* b);

	UWorld* World;
	AActor* Target;
	bool initialized;
	TArray<class AAgent*> Agents;
};