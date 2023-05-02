// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlockingGameModeBase.h"

AFlockingGameModeBase::AFlockingGameModeBase() {
    AgentMesh = CreateDefaultSubobject<UStaticMeshComponent>("AgentMesh");
    PrimaryActorTick.bCanEverTick = true;
}

void AFlockingGameModeBase::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("GAMEMODE BEGINPLAY()"));

    // Spawn Goal Object
    if (Blueprint) Target = GetWorld()->SpawnActor<AActor>(Blueprint);

    // Spawn Flocking Manager
    Manager = NewObject<UFlockingManager>();
    Manager->Init(GetWorld(), AgentMesh, Target);
}

void AFlockingGameModeBase::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    Manager->Flock();
};