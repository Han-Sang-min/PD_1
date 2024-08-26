#pragma once

#include "CoreMinimal.h"
#include "BaseInputComp.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "DefaultPlayerInputComp.generated.h"

UCLASS()
class UDefaultPlayerInputComp : public UBaseInputComp
{
	GENERATED_BODY()

public:
	UDefaultPlayerInputComp();
	virtual void SetUpInputComp(UInputComponent* PlayerInputComponent) override;

private:
	/* Actions */
	UPROPERTY()
	UInputAction* MoveAction;
	UPROPERTY()
	UInputAction* LookAction;
	UPROPERTY()
	UInputAction* JumpAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	/* Helpers */
	UEnhancedInputLocalPlayerSubsystem* GetInputSubsystem(APlayerCharacter* Character);
};
