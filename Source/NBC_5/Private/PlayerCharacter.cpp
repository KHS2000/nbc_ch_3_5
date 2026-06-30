#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "MyPlayerController.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


APlayerCharacter::APlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
	
	//스프링암
	PlayerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	PlayerSpringArm->SetupAttachment(RootComponent);
	PlayerSpringArm->TargetArmLength = 370.f;
	PlayerSpringArm->bUsePawnControlRotation=true;
	
	
	
	//카메라
	PlayerCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(PlayerSpringArm);
	PlayerCamera->bUsePawnControlRotation=false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	
	//HP바
	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidget->SetupAttachment(RootComponent);
	HealthWidget->SetWidgetSpace(EWidgetSpace::World);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 120));
	
	//디버프 시간
	StatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusWidget"));
	StatusWidget->SetupAttachment(RootComponent);
	StatusWidget->SetWidgetSpace(EWidgetSpace::World);
	StatusWidget->SetRelativeLocation(FVector(0, 0, 120));
	StatusWidget->SetDrawSize(FVector2D(150, 30));
	
	MaxHealth = 100.f;
	Health = MaxHealth;
	PlayerMoveSpeed=1.0f;
	

}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateHealthUI();
	
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsSpinningCamera)
	{
		AddControllerYawInput(120.f * DeltaTime);
		
		SpinRemainTime -= DeltaTime;
		
		UpdateSpinUI();
	}

}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInput->BindAction(IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInput->BindAction(IA_Jump,ETriggerEvent::Started, this, &APlayerCharacter::StartJump);
		EnhancedInput->BindAction(IA_Jump,ETriggerEvent::Completed,this,&APlayerCharacter::StopJump);
		EnhancedInput->BindAction(IA_StartSprint,ETriggerEvent::Triggered,this,&APlayerCharacter::StartSprint);
		EnhancedInput->BindAction(IA_StartSprint,ETriggerEvent::Completed,this,&APlayerCharacter::EndSprint);
	}

}


void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();

	if (!Controller) return;

	const FRotator ControlRot = Controller->GetControlRotation();
	const FRotator YawRot(0.f, ControlRot.Yaw, 0.f); //바라보는 방향 값만

	const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X); //월드좌표를 기준으로 현재 내 캐릭터가 바라보고 있는 방향의 값을 반환
	const FVector Right   = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	FVector MoveDir = Forward * Input.Y + Right * Input.X;

	if (!MoveDir.IsNearlyZero())
	{
		FRotator TargetRot = MoveDir.Rotation();

		FRotator CurrentRot = GetActorRotation();

		FRotator NewRot = FMath::RInterpTo(
			CurrentRot,
			TargetRot,
			GetWorld()->GetDeltaSeconds(),
			10.f
		);

		SetActorRotation(NewRot);
	}

	AddMovementInput(MoveDir*PlayerMoveSpeed);
}


void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Vec = Value.Get<FVector2D>();

	AddControllerYawInput(Vec.X);
	AddControllerPitchInput(Vec.Y);
}


void APlayerCharacter::StartJump()
{
	Jump(); // ACharacter 내장 함수
}

void APlayerCharacter::StopJump()
{
	StopJumping(); // ACharacter 내장 함수
}

void APlayerCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed=900.f;
	isSprint=true;
}

void APlayerCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed=600.f;
	isSprint=false;
}

void APlayerCharacter::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health+Amount,0.0f,MaxHealth);
	UE_LOG(LogTemp,Warning,TEXT("Health increased to: %f"), Health);
	UpdateHealthUI();
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health = FMath::Clamp(Health-DamageAmount,0.0f,MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health decreased to: %f"), Health);
	
	
	UpdateHealthUI();
	
	if (Health<=0.f)
	{
		OnDeath();
	}

	return ActualDamage;
}


float APlayerCharacter::GetHealth()
{
	return Health;
}

float APlayerCharacter::GetMaxHealth()
{
	return MaxHealth;
}

void APlayerCharacter::OnDeath()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->GameOver();
	}
}

void APlayerCharacter::SlowTime(float SlowTime)
{
	PlayerMoveSpeed*=SlowTime;
	
	FTimerHandle EndSlowTimeHandler;
	GetWorldTimerManager().SetTimer(
		EndSlowTimeHandler,
		[this]()
		{
			PlayerMoveSpeed=1.0f;
		},
		5.0f,
		false);
}

void APlayerCharacter::UpdateHealthUI()
{
	if (!HealthWidget) return;

	UUserWidget* UserWidget = HealthWidget->GetUserWidgetObject();
	if (!UserWidget) return;

	UHealthBarWidget* Widget = Cast<UHealthBarWidget>(UserWidget);
	if (!Widget) return;

	Widget->SetHealthPercent(Health / MaxHealth);
}


void APlayerCharacter::StartSpinCameraEffect(float Duration)
{
	bIsSpinningCamera = true;
	
	SpinDuration = Duration;
	SpinRemainTime = Duration;
	
	ShowSpinUI();

	GetWorldTimerManager().SetTimer(
		SpinCameraTimerHandle,
		this,
		&APlayerCharacter::StopSpinCameraEffect,
		Duration,
		false
	);
}

void APlayerCharacter::StopSpinCameraEffect()
{
	bIsSpinningCamera = false;
	HideSpinUI();
}

void APlayerCharacter::UpdateSpinUI()
{
	if (!StatusWidget) return;

	UUserWidget* Widget = StatusWidget->GetUserWidgetObject();
	if (!Widget) return;

	UTextBlock* Text = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("EffectTimeText")));

	if (Text)
	{
		FText FinalText = FText::Format(
			FText::FromString(TEXT("디버프 시간: {0}")),
			FText::AsNumber(FMath::CeilToInt(SpinRemainTime))
		);

		Text->SetText(FinalText);
	}
}

void APlayerCharacter::ShowSpinUI()
{
	if (!StatusWidget) return;

	StatusWidget->SetVisibility(true);
}

void APlayerCharacter::HideSpinUI()
{
	if (!StatusWidget) return;

	StatusWidget->SetVisibility(false);
}