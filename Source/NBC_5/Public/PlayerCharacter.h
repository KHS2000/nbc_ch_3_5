#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h" //IA사용을 위한 헤더
#include "InputActionValue.h"    //입력 데이터의 형태를 정의하는 구조체
#include "PlayerCharacter.generated.h"

class USpringArmComponent; 
class UCameraComponent; //클래스 전방선언

UCLASS()
class NBC_5_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Camera")
	USpringArmComponent* PlayerSpringArm;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera")
	UCameraComponent* PlayerCamera;
	
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HealthWidget;
	
	UFUNCTION(BlueprintCallable, Category="Health")
	void AddHealth(float Amount);

	float PlayerMoveSpeed;
	
	void UpdateHealthUI();
	void SlowTime(float SlowTime);
	void OnDeath();
	
	float GetHealth();
	float GetMaxHealth();
	
	FTimerHandle SpinCameraTimerHandle;
	float SpinDuration = 0.f;
	float SpinRemainTime = 0.f;
	bool bIsSpinningCamera = false;
	
	void UpdateSpinUI();

	void StartSpinCameraEffect(float Duration);
	void StopSpinCameraEffect();
	
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* StatusWidget;
	
	void ShowSpinUI();
	void HideSpinUI();
	
	
protected:
	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")    //리플렉션으로 IA등록
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_StartSprint;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isSprint=false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float Health;

	
	
private:
	void Move(const FInputActionValue& Value); //이동함수 선언
	void Look(const FInputActionValue& Value);
	void StartJump();
	void StopJump();
	void StartSprint();
	void EndSprint();
	
};
