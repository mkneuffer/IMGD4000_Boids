// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockingManager.h"

#define AGENT_COUNT 500 //number of cones in the flock

void UFlockingManager::Init(UWorld* world, UStaticMeshComponent* mesh, AActor* target) {
    UE_LOG(LogTemp, Warning, TEXT("Manager initialized"));

    World = world;
    Target = target;

    float incr = (PI * 2.f) / AGENT_COUNT;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (World != nullptr) {
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::Sin(incr * i) * 500.f + 500;
            location.Z = FMath::Cos(incr * i) * 500.f + 500;

            AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

#define SPEED 100
void UFlockingManager::Flock() {
    for (int i = 0; i < Agents.Num(); i++) {
        AAgent* agent = Agents[i];

        FVector v1 = Rule1(agent);
        FVector v2 = Rule2(agent);
        FVector v3 = Rule3(agent);
        FVector v4 = Rule4(agent);

        agent->Velocity = agent->Velocity + (v1 + v2 + v3 + v4) / SPEED;
    }
}

//Rule 1: Boids try to fly towards the centre of mass of neighbouring boids.
#define RULE1_PARAM 100 //Default value given is 100. Smaller makes flock tighter. Larger makes flock looser.
//average position
FVector UFlockingManager::Rule1(AAgent* Agent) {
    FVector averagePos = FVector();
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (Agents[i] == Agent)
            continue;
        averagePos = averagePos + Agents[i]->GetActorLocation();
    }
    averagePos /= AGENT_COUNT - 1;
    return (averagePos - Agent->GetActorLocation()) / RULE1_PARAM;

}

//Rule 2: Boids try to keep a small distance away from other objects (including other boids).
#define RULE2_PARAM 100 //Default value given is 100. Smaller means less space between objects (including other boids). Larger means more space.
FVector UFlockingManager::Rule2(AAgent* b) {
    FVector c = FVector(0.f);
    for (int i = 0; i < AGENT_COUNT; i++) {
        AAgent* agent = Agents[i];
        if (agent != b) {
            float dist = FVector::Dist(agent->GetActorLocation(), b->GetActorLocation());
            if (FMath::Abs(dist) < RULE2_PARAM) {
                c = c - (agent->GetActorLocation() - b->GetActorLocation());
            }
        }
    }

    return c;
}

//Rule 3: Boids try to match velocity with near boids.
#define RULE3_PARAM 8 //Default value given is 8.
FVector UFlockingManager::Rule3(AAgent* b) {
    FVector pv = FVector(0.f);
    for (int i = 0; i < AGENT_COUNT; i++) {
        AAgent* agent = Agents[i];
        if (agent != b) {
            pv = pv + agent->Velocity;
        }
    }

    pv = pv / (Agents.Num() - 1);
    return (pv - b->Velocity) / RULE3_PARAM;
}

//Rule 4: Boids will follow and go toward target
#define RULE4_PARAM 200 //How drawn to the Target the flock is. Larger is less, Smaller is more
FVector UFlockingManager::Rule4(AAgent* b) {
    if (!Target) return FVector(0.f);

    FVector location = Target->GetActorLocation();
    return (location - b->GetActorLocation()) / RULE4_PARAM;
}