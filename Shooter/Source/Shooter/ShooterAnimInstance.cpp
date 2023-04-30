// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UShooterAnimInstance::UpdateAnimationPropertires(float DeltaTime)
{
	if (ShooterCharcter == nullptr)
	{
		ShooterCharcter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if (ShooterCharcter)
	{
		// Get the speed of the character from velocity
		FVector Velocity{ ShooterCharcter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		// Is the character is in the air
		bIsInAir = ShooterCharcter->GetCharacterMovement()->IsFalling();

		// Is the character Accelerating
		if (ShooterCharcter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharcter = Cast<AShooterCharacter>(TryGetPawnOwner());
}
