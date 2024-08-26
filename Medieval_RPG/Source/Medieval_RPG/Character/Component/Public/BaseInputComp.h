#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "BaseInputComp.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInputComponent, Log, All);

UCLASS()
class UBaseInputComp : public UActorComponent
{
	GENERATED_BODY()
public:
	UBaseInputComp();
	virtual void SetUpInputComp(UInputComponent* PlayerInputComponent);

protected:
	void AddKeyMapping(UInputAction* Action, FKey Key, const TArray<UInputModifier*>& Modifiers);

	UPROPERTY()
	UInputMappingContext* IMC;
};
