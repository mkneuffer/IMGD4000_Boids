// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "Agent.h"

AAgent::AAgent() {
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AgentMesh"));
	RootComponent = Mesh;
	Velocity = FVector(FMath::RandRange(-1.f, 1.f), FMath::RandRange(-1.f, 1.f), FMath::RandRange(-1.f, 1.f));
}

void AAgent::BeginPlay() {
	Super::BeginPlay();
}

void AAgent::Init(UStaticMeshComponent* mesh, int id) {
	UE_LOG(LogTemp, Warning, TEXT("Agent initialized."));
	Mesh->SetStaticMesh(mesh->GetStaticMesh());
}

void AAgent::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector loc = GetActorLocation();
	SetActorLocation(loc + Velocity);

	FRotator rot = UKismetMathLibrary::FindLookAtRotation(FVector(0.f), Velocity);
	SetActorRotation(rot + FRotator(-90.f, 0.f, 0.f));
}

