// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "GameFramework/Character.h"
#include "Windows/AllowWindowsPlatformTypes.h" 
#include "Windows/HideWindowsPlatformTypes.h"
#include "DrawDebugHelpers.h"
#include "MainCppPlayer.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	
	Super::BeginPlay();
	myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	Cam = myCharacter->FindComponentByClass<UCameraComponent>();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	pLayerLocation = myCharacter->GetActorLocation();
	//std::cout << "player location:";
	//std::cout << TXT("X = ", pLayerLocation.X, "| Y = ", pLayerLocation.Y, "| Z = ", pLayerLocation.Z, "\n");
	//performing raycast
	if (GetAsyncKeyState('E'))
	{
		//FHitResult* hitRes = new FHitResult;
			FVector startRay = Cam->GetComponentLocation(); // FVector(pLayerLocation.X, pLayerLocation.Y, pLayerLocation.Z);
			FVector FrVector = Cam->GetForwardVector();
			
			FVector endRay = ((FVector(FrVector.X, FrVector.Y, FrVector.Z) * 10000.f) + startRay);
			DrawDebugLine(GetWorld(), startRay, endRay, FColor::Red, 1);
			FActorSpawnParameters spawnParams;
			std::cout << FrVector.X << "|"<< FrVector.Y << "|" << FrVector.Z << "|" << std::endl;
			AActor* SpawnedBullet = GetWorld()->SpawnActor<AActor>(BulletClass->GetDefaultObject()->GetClass(),(startRay+ FrVector), FRotator(0,0,0),spawnParams);
	}
	
}

FVector AGun::GetForseDirection(float ForcePower)
{
	return ((Cam->GetForwardVector() + Cam->GetComponentLocation()) * ForcePower);
}

