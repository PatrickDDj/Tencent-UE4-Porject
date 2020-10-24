// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSProjectile.h"
#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    // 创建一个第一人称摄像机组件。
    FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    // 将摄像机组件附加到胶囊体组件。
    FPSCameraComponent->SetupAttachment((USceneComponent*)GetCapsuleComponent());
    
    // 将摄像机放置在眼睛上方不远处。
    FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    // 用 pawn 控制摄像机旋转。
    FPSCameraComponent->bUsePawnControlRotation = true;
    
    

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
    
    if (GEngine)
    {
        // 显示调试信息五秒。-1"键"值（首个参数）说明我们无需更新或刷新此消息。
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
    }
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    // 设置"移动"绑定。
    PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
    
    PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);
    
    // 设置"动作"绑定。
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
    
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

}

void AFPSCharacter::MoveForward(float Value)
{
    // 明确哪个方向是"前进"，并记录玩家试图向此方向移动。
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
    // 明确哪个方向是"向右"，并记录玩家试图向此方向移动。
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, Value);
}


void AFPSCharacter::StartJump()
{
    bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
    bPressedJump = false;
}

void AFPSCharacter::Fire()
{
    // 尝试发射物体。
    if (ProjectileClass)
    {
        // 获取摄像机变换。
        FVector CameraLocation;
        FRotator CameraRotation;
        GetActorEyesViewPoint(CameraLocation, CameraRotation);

        // 将 MuzzleOffset 从摄像机空间变换到世界空间。
        FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
        FRotator MuzzleRotation = CameraRotation;
        // 将准星稍微上抬。
        MuzzleRotation.Pitch += 10.0f;
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            // 在枪口处生成发射物。
            AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                // 设置发射物的初始轨道。
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);
            }
        }
    }
}
