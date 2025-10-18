#include "ItemActor.h"
#include "Components/SphereComponent.h"
#include "ItemManager.h"

AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	//아이템 범위를 루트로
	sphereCollider = CreateDefaultSubobject<USphereComponent>(FName("SphereCollider"));
	RootComponent = sphereCollider;

	//스태틱 메시
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMesh"));
	itemMesh->SetupAttachment(sphereCollider);
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	//최대 회전 속도가 최소 회전 속도보다 낮으면 안됨
	if (minRotatingSpeed > maxRotatingSpeed)
		maxRotatingSpeed = minRotatingSpeed;

	//이 아이템의 회전 속도
	float speed = FMath::RandRange(minRotatingSpeed, maxRotatingSpeed);
	rotatingValue = FRotator(0, speed, 0);
}

void AItemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnCharacterOverlap);
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(rotatingValue * DeltaTime);
}

void AItemActor::OnCharacterOverlap(UPrimitiveComponent* overlappedComp, AActor* otherActor,
	UPrimitiveComponent* otherComp, int otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	//아이템 효과 적용
	AItemManager::GetInstance()->InvokeItemEffect(itemID);

	//이 아이템 삭제
	AItemManager::GetInstance()->DeleteItem(this);
}
