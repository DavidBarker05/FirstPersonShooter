#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Events/EventListener.h"
#include "MatchLeaderboard.generated.h"

namespace Internal
{
    static UMatchLeaderboard* GetMatchLeaderboardFromContext(const UObject* contextObject)
    {
        if (!contextObject || !IsValid(contextObject)) return nullptr;
        const UWorld* world = nullptr;
        if (const AActor* actor = Cast<AActor>(contextObject)) world = actor->GetWorld();
        else if (const USceneComponent* sceneComponent = Cast<USceneComponent>(contextObject)) world = sceneComponent->GetWorld();
        else if (const UActorComponent* component = Cast<UActorComponent>(contextObject))
        {
            if (AActor* owner = component->GetOwner()) world = owner->GetWorld();
        }
        if (!world) return nullptr;
        if (UGameInstance* gameInstance = world->GetGameInstance()) return gameInstance->GetSubsystem<UMatchLeaderboard>();
        return nullptr;
    }
}

#ifndef ADD_CHARACTER_TO_LEADERBOARD
#define ADD_CHARACTER_TO_LEADERBOARD(CharacterName)\
		do\
		{\
			if (UMatchLeaderboard* MatchLeaderboard = Internal::GetMatchLeaderboardFromContext(this))\
				MatchLeaderboard->AddCharacter(CharacterName);\
		} while (0)
#endif

#ifndef ADD_KILL_TO_LEADERBOARD
#define ADD_KILL_TO_LEADERBOARD(CharacterThatKilled, CharacterThatDied)\
		do\
		{\
			if (UMatchLeaderboard* MatchLeaderboard = Internal::GetMatchLeaderboardFromContext(this))\
				MatchLeaderboard->AddKill(CharacterThatKilled, CharacterThatDied);\
		} while (0)
#endif

#ifndef ORDER_LEADERBOARD
#define ORDER_LEADERBOARD()\
		do\
		{\
			if (UMatchLeaderboard* MatchLeaderboard = Internal::GetMatchLeaderboardFromContext(this))\
				MatchLeaderboard->OrderLeaderboard();\
		} while (0)
#endif

#ifndef CLEAR_LEADERBOARD
#define CLEAR_LEADERBOARD()\
		do\
		{\
			if (UMatchLeaderboard* MatchLeaderboard = Internal::GetMatchLeaderboardFromContext(this))\
				MatchLeaderboard->ClearLeaderboard();\
		} while (0)
#endif

UCLASS()
class FIRSTPERSONSHOOTER_API UMatchLeaderboard : public UGameInstanceSubsystem, public IEventListener
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TArray<FName> Leaderboard;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TMap<FName, int32> Kills;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TMap<FName, int32> Deaths;

public:
    UFUNCTION(BlueprintCallable)
    void AddCharacter(FName CharacterName);

    UFUNCTION(BlueprintCallable)
    void AddKill(FName CharacterThatKilled, FName CharacterThatDied);

    UFUNCTION(BlueprintCallable)
    void OrderLeaderboard();

    UFUNCTION(BlueprintCallable)
    void ClearLeaderboard();

private:
    void OrderLeaderboardInternal();

    void EnsureStatsExist(const FName& CharacterName);
};
