// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingTestActor.h"

// Sets default values
ACodingTestActor::ACodingTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodingTestActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
	
	UE_LOG(LogTemp, Warning,TEXT("%d"), number1);
	UE_LOG(LogTemp, Warning,TEXT("%.2f"), number2);
	
	UE_LOG(LogTemp, Warning,TEXT("%d"), real);
	
	if (number3 > 50)
	{
		UE_LOG(LogTemp, Warning,TEXT("number3는 50보다 큽니다"));
	}
	else if (number3 == 50)
	{
		UE_LOG(LogTemp, Warning,TEXT("number3는 50입니다"));
	}
	else
	{
		UE_LOG(LogTemp, Warning,TEXT("number3는 50보다 작습니다"));
	}
	
}

// Called every frame
void ACodingTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ACodingTestActor::AddCustom(int32 a, int32 b)
{
	return a + b;
}

