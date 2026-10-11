#include "Character/PlayerHUD.h"

#include "Blueprint/UserWidget.h"
#include "FirstPersonGameMode.h"
#include "Kismet/GameplayStatics.h"

void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();
    SUBSCRIBE_TO_EVENTS();
    APlayerController* PC = GetOwningPlayerController();
    PlayerScreenWidget = CreateWidget<UUserWidget>(PC, PlayerScreenWidgetBlueprint);
    StartCountdownWidget = CreateWidget<UUserWidget>(PC, StartCountdownWidgetBlueprint);
    EndLeaderboardWidget = CreateWidget<UUserWidget>(PC, EndLeaderboardWidgetBlueprint);
    PauseScreen = CreateWidget<UUserWidget>(PC, PauseScreenBlueprint);
    switch (const AFirstPersonGameMode* GameMode = Cast<AFirstPersonGameMode>(UGameplayStatics::GetGameMode(this));
            GameMode->GetCurrentMatchState())
    {
        case EGameMatchState::StartCountdownPhase:
            ShowStartCountdownWidget();
            break;
        case EGameMatchState::MatchRoundPhase:
            ShowPlayerScreenWidget();
            break;
        case EGameMatchState::EndLeaderboardPhase:
            ShowEndLeaderboardWidget();
            break;
        default:
            HideMouse();
            break;
    }
}

void APlayerHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UNSUBSCRIBE_FROM_EVENTS();
    Super::EndPlay(EndPlayReason);
}

void APlayerHUD::OnEventReceived_Implementation(const FName& EventName, const TArray<FAny>& Params)
{
    if (EVENT_MATCHES(TEXT("DisplayStartCountdownEvent"), 0)) ShowStartCountdownWidget();
    else if (EVENT_MATCHES(TEXT("DisplayPlayerScreenEvent"), 1) && PARAMS_ARE_VALID &&
             PARAMS_ARE_CORRECT_TYPES(APlayerController*))
    {
        if (*Params[0].Get<APlayerController*>() != GetOwningPlayerController()) return;
        ShowPlayerScreenWidget();
    }
    else if (EVENT_MATCHES(TEXT("DisplayPauseScreenEvent"), 0)) ShowPauseScreen();
    else if (EVENT_MATCHES(TEXT("DisplayEndLeaderboardEvent"), 0)) ShowEndLeaderboardWidget();
    else if (EVENT_MATCHES(TEXT("DeathEvent"), 1) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(APawn*))
    {
        if (*Params[0].Get<APawn*>() != GetOwningPawn()) return;
        RemoveAllScreens();
    }
}

void APlayerHUD::RemoveAllScreens()
{
    HideMouse();
    if (IsValid(StartCountdownWidget) && StartCountdownWidget->IsInViewport()) StartCountdownWidget->RemoveFromParent();
    if (IsValid(PlayerScreenWidget) && PlayerScreenWidget->IsInViewport()) PlayerScreenWidget->RemoveFromParent();
    if (IsValid(PauseScreen) && PauseScreen->IsInViewport()) PauseScreen->RemoveFromParent();
    if (IsValid(EndLeaderboardWidget) && EndLeaderboardWidget->IsInViewport()) EndLeaderboardWidget->RemoveFromParent();
}

void APlayerHUD::ShowStartCountdownWidget()
{
    HideMouse();
    if (IsValid(StartCountdownWidget) && !StartCountdownWidget->IsInViewport())
        StartCountdownWidget->AddToPlayerScreen();
    if (IsValid(PlayerScreenWidget) && PlayerScreenWidget->IsInViewport()) PlayerScreenWidget->RemoveFromParent();
    if (IsValid(PauseScreen) && PauseScreen->IsInViewport()) PauseScreen->RemoveFromParent();
    if (IsValid(EndLeaderboardWidget) && EndLeaderboardWidget->IsInViewport()) EndLeaderboardWidget->RemoveFromParent();
}

void APlayerHUD::ShowPlayerScreenWidget()
{
    HideMouse();
    if (IsValid(StartCountdownWidget) && StartCountdownWidget->IsInViewport()) StartCountdownWidget->RemoveFromParent();
    if (IsValid(PlayerScreenWidget) && !PlayerScreenWidget->IsInViewport()) PlayerScreenWidget->AddToPlayerScreen();
    if (IsValid(PauseScreen) && PauseScreen->IsInViewport()) PauseScreen->RemoveFromParent();
    if (IsValid(EndLeaderboardWidget) && EndLeaderboardWidget->IsInViewport()) EndLeaderboardWidget->RemoveFromParent();
}

void APlayerHUD::ShowPauseScreen()
{
    ShowMouse();
    if (IsValid(StartCountdownWidget) && StartCountdownWidget->IsInViewport()) StartCountdownWidget->RemoveFromParent();
    if (IsValid(PlayerScreenWidget) && PlayerScreenWidget->IsInViewport()) PlayerScreenWidget->RemoveFromParent();
    if (IsValid(PauseScreen) && !PauseScreen->IsInViewport()) PauseScreen->AddToPlayerScreen();
    if (IsValid(EndLeaderboardWidget) && EndLeaderboardWidget->IsInViewport()) EndLeaderboardWidget->RemoveFromParent();
}

void APlayerHUD::ShowEndLeaderboardWidget()
{
    ShowMouse();
    if (IsValid(StartCountdownWidget) && StartCountdownWidget->IsInViewport()) StartCountdownWidget->RemoveFromParent();
    if (IsValid(PlayerScreenWidget) && PlayerScreenWidget->IsInViewport()) PlayerScreenWidget->RemoveFromParent();
    if (IsValid(PauseScreen) && PauseScreen->IsInViewport()) PauseScreen->RemoveFromParent();
    if (IsValid(EndLeaderboardWidget) && !EndLeaderboardWidget->IsInViewport())
        EndLeaderboardWidget->AddToPlayerScreen();
}

void APlayerHUD::ShowMouse() const
{
    APlayerController* PC = GetOwningPlayerController();
    FInputModeGameAndUI InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
    InputMode.SetHideCursorDuringCapture(false);
    PC->SetInputMode(InputMode);
    PC->bShowMouseCursor = true;
    int32 HRes, VRes;
    PC->GetViewportSize(HRes, VRes);
    PC->SetMouseLocation(HRes / 2, VRes / 2);
}

void APlayerHUD::HideMouse() const
{
    APlayerController* PC = GetOwningPlayerController();
    PC->SetInputMode(FInputModeGameOnly());
    PC->bShowMouseCursor = false;
}
