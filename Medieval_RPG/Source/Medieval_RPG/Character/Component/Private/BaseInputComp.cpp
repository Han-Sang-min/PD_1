#include "BaseInputComp.h"
#include "InputMappingContext.h"

UBaseInputComp::UBaseInputComp()
{
	IMC = CreateDefaultSubobject<UInputMappingContext>(TEXT("InputMappingContext"));
}

void UBaseInputComp::SetUpInputComp(UInputComponent* PlayerInputComponent)
{
	
}

void UBaseInputComp::AddKeyMapping(UInputAction* Action, FKey Key, const TArray<UInputModifier*>& Modifiers)
{
	FEnhancedActionKeyMapping& KeyMapping = IMC->MapKey(Action, Key);

	for (UInputModifier* M : Modifiers)
	{
		if (M)
		{
			KeyMapping.Modifiers.Add(M);
		}
	}
}
