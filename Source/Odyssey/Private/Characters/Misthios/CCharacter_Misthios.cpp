#include "Characters/Misthios/CCharacter_Misthios.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CMovementComponent.h"
#include "Datas/CharacterData.h"
#include "Characters/CMisthiosController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CWeaponComponent.h"
#include "Games/CMainPS.h"
#include "AbilitySystemComponent.h"

ACCharacter_Misthios::ACCharacter_Misthios()
{
	PrimaryActorTick.bCanEverTick = true;

	Init();
}

void ACCharacter_Misthios::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// 데이터 애셋이 유효한지 확인
	if (CharacterDataAsset)
	{
		// 데이터 애셋에서 현재 선택된 캐릭터 타입에 맞는 외형 정보 로드
		const FCharacterAppearance& appearance = CharacterDataAsset->CharacterAppearances[(int32)CharacterType];

		// 스켈레탈 메시가 유효하다면 캐릭터의 메시를 변경
		if (appearance.SkeletalMesh)
			GetMesh()->SetSkeletalMesh(appearance.SkeletalMesh);
	}
}

void ACCharacter_Misthios::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacter_Misthios::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// MovementComponent에 입력 설정 위임
		MovementComponent->SetupPlayerInput(enhancedInputComponent);

		// WeaponComponent에 입력 설정 위임
		WeaponComponent->SetupPlayerInput(enhancedInputComponent);
	}
}

void ACCharacter_Misthios::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilityActorInfo();
	
	if (ACMisthiosController* controller = Cast<ACMisthiosController>(NewController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
			Subsystem->AddMappingContext(IMC_Misthios, 0);
	}
}

void ACCharacter_Misthios::Init()
{
	Super::Init();

	// 캐릭터가 컨트롤러의 회전을 따라가지 않고, 움직이는 방향을 바라보도록 설정
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	{ // Components
		CHelpers::CreateComponent<USpringArmComponent>(this, SpringArmComponent, TEXT("SpringArmComponent"), RootComponent);
		SpringArmComponent->SetRelativeLocation(FVector(0, 0, 100));
		SpringArmComponent->TargetArmLength = 350.f;
		SpringArmComponent->bUsePawnControlRotation = true; // 카메라가 컨트롤러(마우스)의 회전을 따라가도록 설정
		SpringArmComponent->bEnableCameraLag = true;
		SpringArmComponent->bDoCollisionTest = true; // 카메라가 벽 뒤로 숨지 않도록 충돌을 활성화

		CHelpers::CreateComponent<UCameraComponent>(this, CameraComponent, TEXT("CameraComponent"), SpringArmComponent);
	}
	
	{ // Actor Components
<<<<<<< Updated upstream
		CHelpers::CreateActorComponent<UCMovementComponent>(this, MovementComponent, TEXT("CMovementComponent"));
=======
		CHelpers::CreateActorComponent<UAbilitySystemComponent>(this, AbilitySystemComponent, TEXT("AbilitySystemComponent"));
		
		CHelpers::CreateActorComponent<UCMovementComponent>(this, MovementComponent, TEXT("MovementComponent"));
		
		CHelpers::CreateActorComponent<UCWeaponComponent>(this, WeaponComponent, TEXT("WeaponComponent"));
>>>>>>> Stashed changes
	}
}

void ACCharacter_Misthios::BeginPlay()
{
	Super::BeginPlay();
}

void ACCharacter_Misthios::InitAbilityActorInfo()
{
	// PlayerState 로드
	ACMainPS* PS = GetPlayerState<ACMainPS>();
	if (PS)
	{
		// PlayerState로부터 ASC와 AttributeSet 포인터를 가져와 멤버 변수에 저장
		AbilitySystemComponent = PS->GetAbilitySystemComponent();
		AttributeSet = PS->GetAttributeSet();
	
		// ASC가 이 캐릭터를 '아바타'로 인식하도록 초기화
		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->InitAbilityActorInfo(PS, this);
		}
	}
}

void ACCharacter_Misthios::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	InitAbilityActorInfo();
}
