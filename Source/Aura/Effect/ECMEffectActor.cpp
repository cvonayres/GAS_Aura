// Copyright Electronic CAD Monkey [ECM]


#include "ECMEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Aura/AbilitySystem/ECMAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AECMEffectActor::AECMEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AECMEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AECMEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AECMEffectActor::EndOverlap);
}

void AECMEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply a Gameplay Effect. This is a hack!
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UECMAttributeSet* ECMAttributeSet = Cast<UECMAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UECMAttributeSet::StaticClass()));

		UECMAttributeSet* MutableECMAttributeSet = const_cast<UECMAttributeSet*>(ECMAttributeSet);
		MutableECMAttributeSet->SetHealth(ECMAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AECMEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}