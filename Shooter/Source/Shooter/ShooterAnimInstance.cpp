// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

		FRotator AimRotation = ShooterCharcter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharcter->GetVelocity());
		
		//FString RotationMessage = FString::Printf(TEXT("Base Aim Rotation: %f"), AimRotation.Yaw);
		//FString MovementRotationMessage = FString::Printf(TEXT("Movement Rotation: %f"), MovementRotation.Yaw);

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(
			MovementRotation,
			AimRotation).Yaw;

		/*
		FString OffsetMessage = FString::Printf(TEXT("Movement Offset Yaw: %f"), MovementOffsetYaw);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Blue, OffsetMessage);
		}
		*/
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharcter = Cast<AShooterCharacter>(TryGetPawnOwner());
}
