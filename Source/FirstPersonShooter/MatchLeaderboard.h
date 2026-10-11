#pragma once

#include "CoreMinimal.h"

#include "Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "MatchLeaderboard.generated.h"

#ifndef ADD_CHARACTER_TO_LEADERBOARD
#define ADD_CHARACTER_TO_LEADERBOARD(CharacterName) \
    do \
    { \
        if (const UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull); \
            const UGameInstance* GameInstance = World->GetGameInstance()) \
        { \
            if (UMatchLeaderboard* MatchLeaderboard = GameInstance->GetSubsystem<UMatchLeaderboard>()) \
                MatchLeaderboard->AddCharacter(CharacterName); \
        } \
    } while (0)
#endif

#ifndef ADD_KILL_TO_LEADERBOARD
#define ADD_KILL_TO_LEADERBOARD(CharacterThatKilled, CharacterThatDied) \
    do \
    { \
        if (const UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull); \
            const UGameInstance* GameInstance = World->GetGameInstance()) \
        { \
            if (UMatchLeaderboard* MatchLeaderboard = GameInstance->GetSubsystem<UMatchLeaderboard>()) \
                MatchLeaderboard->AddKill(CharacterThatKilled, CharacterThatDied); \
        } \
    } while (0)
#endif

#ifndef ORDER_LEADERBOARD
#define ORDER_LEADERBOARD() \
    do \
    { \
        if (const UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull); \
            const UGameInstance* GameInstance = World->GetGameInstance()) \
        { \
            if (UMatchLeaderboard* MatchLeaderboard = GameInstance->GetSubsystem<UMatchLeaderboard>()) \
                MatchLeaderboard->OrderLeaderboard(); \
        } \
    } while (0)
#endif

#ifndef CLEAR_LEADERBOARD
#define CLEAR_LEADERBOARD() \
    do \
    { \
        if (const UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull); \
            const UGameInstance* GameInstance = World->GetGameInstance()) \
        { \
            if (UMatchLeaderboard* MatchLeaderboard = GameInstance->GetSubsystem<UMatchLeaderboard>()) \
                MatchLeaderboard->ClearLeaderboard(); \
        } \
    } while (0)
#endif

UCLASS()
class FIRSTPERSONSHOOTER_API UMatchLeaderboard : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void AddCharacter(const FName& CharacterName);

    UFUNCTION(BlueprintCallable)
    void AddKill(const FName& CharacterThatKilled, const FName& CharacterThatDied);

    UFUNCTION(BlueprintCallable)
    void OrderLeaderboard();

    UFUNCTION(BlueprintCallable)
    void ClearLeaderboard();

    const TArray<FName>& GetLeaderBoard() const { return Leaderboard; }

    const TMap<FName, int32>& GetKills() const { return Kills; }

    const TMap<FName, int32>& GetDeaths() const { return Deaths; }

private:
    void OrderLeaderboardInternal();

    void EnsureStatsExist(const FName& CharacterName);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
    TArray<FName> Leaderboard;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
    TMap<FName, int32> Kills;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
    TMap<FName, int32> Deaths;
};
