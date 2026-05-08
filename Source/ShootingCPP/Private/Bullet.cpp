// Fill out your copyright notice in the Description page of Project Settings.
#include "Bullet.h"

#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	// 플레이어와 동일 - 박스 콜리전 컴포넌트 생성
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Collider"));
	SetRootComponent(boxComp); // 생성된 박스 콜라이더 컴포넌트를 최상단 컴포넌트로 설정
	// 박스 콜라이더 크기를 50x50x50 설정
	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	boxComp->SetBoxExtent(boxSize);
	// Scale 조절 - 위 박스 크기를 총알 형태에 가깝도록 SetWorldScale3D 조절
	boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));
	
	// 스태틱 메시 컴포넌트 생성&설정
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My StaticMesh Component"));
	meshComp->SetupAttachment(boxComp); // 박스 콜라이더 컴포넌트의 자식 컴포넌트로 설정
	
	boxComp->SetCollisionProfileName(TEXT("Bullet"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	//OnComponentBeginOverlap 델리게이트에 OnOverlap함수를 등록
	//Overlap 발생하면 OnOverlap() 호출해 라고 엔진에 등록 설정
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//전방으로 이동될 위치계산
	//GetActorForwardVector() 로 전방 이동 쉽게 구현
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;
	// 계산된 위치 좌표를 섹터의 새 좌표로 틱당 넣기
	SetActorLocation(newLocation);
}

void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//충돌한 상대 벡터를 AEnemyActor클래스로 변경
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy != nullptr)
	{
		// 충돌 위치에 폭발 이펙트 스폰
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),explosionFX, GetActorTransform());
		
		OtherActor->Destroy();
	}
	//총알 자신도 제거
	Destroy();
}
