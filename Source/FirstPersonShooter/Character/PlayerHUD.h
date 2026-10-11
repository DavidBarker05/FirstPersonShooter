#pragma once

#include "CoreMinimal.h"

#include "Events/EventListener.h"
#include "GameFramework/HUD.h"

#include "PlayerHUD.generated.h"

class UUserWidget;

UCLASS(Abstract, meta = (DisplayName = "Player HUD"))
class FIRSTPERSONSHOOTER_API APlayerHUD : public AHUD,
                                          public IEventListener
{
    GENERATED_BODY()

    EVENTS_TO_LISTEN_TO(TEXT("DisplayStartCountdownEvent"), TEXT("DisplayPlayerScreenEvent"),
                        TEXT("DisplayPauseScreenEvent"), TEXT("DisplayEndLeaderboardEvent"), TEXT("DeathEvent"))

protected:
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    UFUNCTION(BlueprintCallable)
    virtual void OnEventReceived_Implementation(const FName& EventName, const TArray<FAny>& Params) override;

    UFUNCTION(BlueprintCallable)
    virtual void RemoveAllScreens();

    UFUNCTION(BlueprintCallable)
    virtual void ShowStartCountdownWidget();

    UFUNCTION(BlueprintCallable)
    virtual void ShowPlayerScreenWidget();

    UFUNCTION(BlueprintCallable)
    virtual void ShowPauseScreen();

    UFUNCTION(BlueprintCallable)
    virtual void ShowEndLeaderboardWidget();

    const UUserWidget* GetStartCountdownWidget() const { return StartCountdownWidget; }
    UUserWidget* GetStartCountdownWidget() { return StartCountdownWidget; }

    const UUserWidget* GetPlayerScreenWidget() const { return PlayerScreenWidget; }
    UUserWidget* GetPlayerScreenWidget() { return PlayerScreenWidget; }

    const UUserWidget* GetPauseScreen() const { return PauseScreen; }
    UUserWidget* GetPauseScreen() { return PauseScreen; }

    const UUserWidget* GetEndLeaderboardWidget() const { return EndLeaderboardWidget; }
    UUserWidget* GetEndLeaderboardWidget() { return EndLeaderboardWidget; }

private:
    void ShowMouse() const;
    void HideMouse() const;

    UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = true))
    TSubclassOf<UUserWidget> StartCountdownWidgetBlueprint;

    UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = true))
    UUserWidget* StartCountdownWidget;

    UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = true))
    TSubclassOf<UUserWidget> PlayerScreenWidgetBlueprint;

    UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = true))
    UUserWidget* PlayerScreenWidget;

    UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = true))
    TSubclassOf<UUserWidget> PauseScreenBlueprint;

    UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = true))
    UUserWidget* PauseScreen;

    UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = true))
    TSubclassOf<UUserWidget> EndLeaderboardWidgetBlueprint;

    UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = true))
    UUserWidget* EndLeaderboardWidget;
};
