// Copyright 2023 German Lopez. All Rights Reserved.

#include "FixedCameraTrigger.h"
#include "UObject/ConstructorHelpers.h"

#pragma region UNREAL_ENGINE_EVENTS
/// <summary>
/// Sets default values for this actor's properties.
/// </summary>
AFixedCameraTrigger::AFixedCameraTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root Component");

	RootComponent = Root;

	Trigger1 = CreateDefaultSubobject<UBoxComponent>("Trigger 1");
	Trigger1->SetupAttachment(RootComponent);
	Trigger2 = CreateDefaultSubobject<UBoxComponent>("Trigger 2");
	Trigger2->SetupAttachment(RootComponent);

	DebugCollider1 = CreateDefaultSubobject<UStaticMeshComponent>("Debug Collider 1");
	DebugCollider1->SetupAttachment(RootComponent);

	DebugCollider2 = CreateDefaultSubobject<UStaticMeshComponent>("Debug Collider 2");
	DebugCollider2->SetupAttachment(RootComponent);

	#if WITH_EDITOR
		if (GEngine)
		{
			static ConstructorHelpers::FObjectFinder<UStaticMesh> DebugMeshRef(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
			if (DebugMeshRef.Object != nullptr && GEngine)
				DebugCollider1->SetStaticMesh(DebugMeshRef.Object);

			static ConstructorHelpers::FObjectFinder<UMaterial> DebugMeshMaterialRef(TEXT("Material'/FixedCameraSystem/Materials/M_FixedCameraTrigger_Blue.M_FixedCameraTrigger_Blue'"));
			if (DebugMeshMaterialRef.Object != nullptr)
			{
				UMaterial* M = (UMaterial*)DebugMeshMaterialRef.Object;
				DebugCollider1->SetMaterial(0, M);
			}

			if (DebugMeshRef.Object != nullptr && GEngine)
				DebugCollider2->SetStaticMesh(DebugMeshRef.Object);

			static ConstructorHelpers::FObjectFinder<UMaterial> DebugMeshMaterialRef2(TEXT("Material'/FixedCameraSystem/Materials/M_FixedCameraTrigger_Orange.M_FixedCameraTrigger_Orange'"));
			if (DebugMeshMaterialRef2.Object != nullptr)
			{
				UMaterial* M = (UMaterial*)DebugMeshMaterialRef2.Object;
				DebugCollider2->SetMaterial(0, M);
			}
		}
	#endif

	SetActorScale3D(FVector(1.f, 5, 5));

	Trigger1->OnComponentBeginOverlap.AddDynamic(this, &AFixedCameraTrigger::OnTriggerBeginOverlap1);
	Trigger2->OnComponentBeginOverlap.AddDynamic(this, &AFixedCameraTrigger::OnTriggerBeginOverlap2);

	Trigger1->OnComponentEndOverlap.AddDynamic(this, &AFixedCameraTrigger::OnTriggerEndOverlap1);
	Trigger2->OnComponentEndOverlap.AddDynamic(this, &AFixedCameraTrigger::OnTriggerEndOverlap2);
	
}

/// <summary>
/// Called in Editor.
/// </summary>
/// <param name="Transform"></param>
void AFixedCameraTrigger::OnConstruction(const FTransform& Transform)
{
	SetActorScale3D(FVector(.1f, GetActorScale3D().Y, GetActorScale3D().Z));

	Trigger1->SetRelativeLocation(FVector(-Trigger1->GetCollisionShape().GetExtent().X / GetActorScale3D().X, Trigger1->GetCollisionShape().GetExtent().Y / GetActorScale3D().Y, Trigger1->GetCollisionShape().GetExtent().Z / GetActorScale3D().Z));
	Trigger2->SetRelativeLocation(FVector(Trigger2->GetCollisionShape().GetExtent().X / GetActorScale3D().X, Trigger1->GetCollisionShape().GetExtent().Y / GetActorScale3D().Y, Trigger2->GetCollisionShape().GetExtent().Z / GetActorScale3D().Z));
	#if WITH_EDITOR
		if (GEngine)
		{
			DebugCollider1->SetWorldLocation(Trigger1->GetComponentLocation());
			DebugCollider1->SetWorldRotation(Trigger1->GetComponentRotation());
			DebugCollider1->SetWorldScale3D((Trigger1->GetCollisionShape().GetExtent() / 40.f) / 1.25f);

			DebugCollider2->SetWorldLocation(Trigger2->GetComponentLocation());
			DebugCollider2->SetWorldRotation(Trigger2->GetComponentRotation());
			DebugCollider2->SetWorldScale3D((Trigger2->GetCollisionShape().GetExtent() / 40.f) / 1.25f);
		}
	#endif

	DebugCollider1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DebugCollider1->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	DebugCollider2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DebugCollider2->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}
	
/// <summary>
/// Called when the game starts or when spawned.
/// </summary>
void AFixedCameraTrigger::BeginPlay()
{
	Super::BeginPlay();

	DebugCollider1->SetVisibility(false);
	DebugCollider2->SetVisibility(false);
}

/// <summary>
/// Called every frame.
/// </summary>
/// <param name="DeltaTime"></param>
void AFixedCameraTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
#pragma endregion

#pragma region CLASS_EVENTS
/// <summary>
/// Overlap event - Trigger 1.
/// </summary>
/// <param name="OverlappedComp"></param>
/// <param name="OtherActor"></param>
/// <param name="OtherComp"></param>
/// <param name="OtherBodyIndex"></param>
/// <param name="bFromSweep"></param>
/// <param name="SweepResult"></param>
void AFixedCameraTrigger::OnTriggerBeginOverlap1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Fill with custom code.
}

/// <summary>
/// Overlap event - Trigger 2.
/// </summary>
/// <param name="OverlappedComp"></param>
/// <param name="OtherActor"></param>
/// <param name="OtherComp"></param>
/// <param name="OtherBodyIndex"></param>
/// <param name="bFromSweep"></param>
/// <param name="SweepResult"></param>
void AFixedCameraTrigger::OnTriggerBeginOverlap2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Fill with custom code.
}

/// <summary>
/// End overlap event - Trigger 1.
/// </summary>
/// <param name="OverlappedComp"></param>
/// <param name="OtherActor"></param>
/// <param name="OtherComp"></param>
/// <param name="OtherBodyIndex"></param>
void AFixedCameraTrigger::OnTriggerEndOverlap1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!Camera1)
		return;

	if (Trigger2->IsOverlappingComponent(OtherComp))
	{
		return;
	}

	Camera2->DeactivateFixedCamera();
	Camera1->ActivateFixedCamera(fSmoothTransition1, BlendFunc1, fBlendExp1);
}

/// <summary>
/// End overlap event - Trigger 2.
/// </summary>
/// <param name="OverlappedComp"></param>
/// <param name="OtherActor"></param>
/// <param name="OtherComp"></param>
/// <param name="OtherBodyIndex"></param>
void AFixedCameraTrigger::OnTriggerEndOverlap2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!Camera2)
		return;

	if (Trigger1->IsOverlappingComponent(OtherComp))
	{
		return;
	}

	Camera1->DeactivateFixedCamera();
	Camera2->ActivateFixedCamera(fSmoothTransition2, BlendFunc2, fBlendExp2);
}
#pragma endregion