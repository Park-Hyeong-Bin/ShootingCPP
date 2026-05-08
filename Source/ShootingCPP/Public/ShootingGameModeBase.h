// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
	void AddScore(int32 point);
	
	//BP_MainWidge파일을 담는 변수
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> mainWidget;

	protected:
	virtual void BeginPlay() override;
	
private:
	int32 currentScore = 0;
	
	// 에디터 뷰포트에 로드된 위젯 저장용 변수
	class UMainWidget* mainUI;
	
	// 점수 UI 갱신 함수
	void PrintScore();
	
	
};
