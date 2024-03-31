// Fill out your copyright notice in the Description page of Project Settings.


#include "Ring/GPIV_RingItem.h"

#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Player/GPIV_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGPIV_RingItem::AGPIV_RingItem()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(SceneComponent);
	SphereCollider->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh"));
	CoinMesh->SetupAttachment(SphereCollider);
	CoinMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 180, 0);
}

// Called when the game starts or when spawned
void AGPIV_RingItem::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AGPIV_RingItem::OnSphereOverlap);
}

void AGPIV_RingItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGPIV_PlayerCharacter* PlayerCharacter = Cast<AGPIV_PlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->AddRing();

		Destroy();

	}
}

