#include "DefaultPlayerInputComp.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "PlayerCharacter.h"

DEFINE_LOG_CATEGORY(LogInputComponent);

UDefaultPlayerInputComp::UDefaultPlayerInputComp()
{
	MoveAction = CreateDefaultSubobject<UInputAction>(TEXT("MoveAction"));
	LookAction = CreateDefaultSubobject<UInputAction>(TEXT("LookAction"));
	JumpAction = CreateDefaultSubobject<UInputAction>(TEXT("JumpAction"));

	MoveAction->ValueType = EInputActionValueType::Axis2D;
	LookAction->ValueType = EInputActionValueType::Axis2D;

	/* Set up key mappings */
	UInputModifierNegate* NegateModifier = NewObject<UInputModifierNegate>();
	UInputModifierSwizzleAxis* SwizzleModifier = NewObject<UInputModifierSwizzleAxis>();
	SwizzleModifier->Order = EInputAxisSwizzle::YXZ;
	/* Set W */
	AddKeyMapping(MoveAction, EKeys::W, { SwizzleModifier });
	/* Set S */
	AddKeyMapping(MoveAction, EKeys::S, { SwizzleModifier, NegateModifier });
	/* Set A */
	AddKeyMapping(MoveAction, EKeys::A, { NegateModifier });
	/* Set D */
	AddKeyMapping(MoveAction, EKeys::D, {});
	/* Mouse */
	UInputModifierNegate* NM = NewObject<UInputModifierNegate>();
	NM->bX = false;
	NM->bZ = false;
	AddKeyMapping(LookAction, EKeys::Mouse2D, {NM});
	/* Set Jump */
	UInputTriggerPressed* PressedTrigger = NewObject<UInputTriggerPressed>();
	PressedTrigger->ActuationThreshold = 0.5f;
	UInputTriggerReleased* ReleasedTrigger = NewObject<UInputTriggerReleased>();
	ReleasedTrigger->ActuationThreshold = 0.5f;
	
	JumpAction->Triggers.Add(PressedTrigger);
	JumpAction->Triggers.Add(ReleasedTrigger);
	
	AddKeyMapping(JumpAction, EKeys::SpaceBar, {});
}

void UDefaultPlayerInputComp::SetUpInputComp(UInputComponent* PlayerInputComponent)
{
	Super::SetUpInputComp(PlayerInputComponent);

	APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetInputSubsystem(Character);

	if (Subsystem)
	{
		Subsystem->AddMappingContext(IMC, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UDefaultPlayerInputComp::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UDefaultPlayerInputComp::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, Character, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, Character, &ACharacter::StopJumping);
	}
}

void UDefaultPlayerInputComp::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	ACharacter* C = Cast<ACharacter>(GetOwner());
	if (!C) return;
	
	if (C->Controller != nullptr)
	{
		const FRotator Rotation = C->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 캐릭터를 기준으로 XYZ축을 얻어오는 것으로 보인다. 
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		C->AddMovementInput(ForwardDirection, MovementVector.Y);
		C->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void UDefaultPlayerInputComp::Look(const FInputActionValue& Value)
{
	ACharacter* C = Cast<ACharacter>(GetOwner());
	if (!C) return;
	
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (C != nullptr)
	{
		C->AddControllerYawInput(LookAxisVector.X);
		C->AddControllerPitchInput(LookAxisVector.Y);
	}
}

UEnhancedInputLocalPlayerSubsystem* UDefaultPlayerInputComp::GetInputSubsystem(APlayerCharacter* Character)
{
	if (!Character) return nullptr;

	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if (!PlayerController) return nullptr;

	return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
}
