#include "MatchLeaderboard.h"
#include "Algo/Sort.h"

void UMatchLeaderboard::AddCharacter(FName CharacterName)
{
	if (!Leaderboard.Contains(CharacterName))
	{
		Kills.Remove(CharacterName);
		Deaths.Remove(CharacterName);
	}
	Leaderboard.AddUnique(CharacterName);
	EnsureStatsExist(CharacterName);
}

void UMatchLeaderboard::AddKill(FName CharacterThatKilled, FName CharacterThatDied)
{
	if (!Leaderboard.Contains(CharacterThatKilled) || !Leaderboard.Contains(CharacterThatDied)) return;
	EnsureStatsExist(CharacterThatKilled);
	EnsureStatsExist(CharacterThatDied);
	++Kills[CharacterThatKilled];
	++Deaths[CharacterThatDied];
	OrderLeaderboardInternal();
}

void UMatchLeaderboard::OrderLeaderboard()
{
	for (const FName& Entry : Leaderboard) // Have to do this because OrderLeaderboard() can be called from anywhere
		EnsureStatsExist(Entry);
	OrderLeaderboardInternal();
}

void UMatchLeaderboard::OrderLeaderboardInternal()
{
	if (Leaderboard.IsEmpty()) return;
	Algo::Sort(Leaderboard, [this](const FName& A, const FName& B)
	{
		int32 KillsA = Kills.FindRef(A);
		int32 KillsB = Kills.FindRef(B);
		if (KillsA != KillsB) return KillsA > KillsB; // Sort by kills descending first
		int32 DeathsA = Deaths.FindRef(A);
		int32 DeathsB = Deaths.FindRef(B);
		if (DeathsA != DeathsB) return DeathsA < DeathsB; // Sort by deaths ascending second
		return A.LexicalLess(B); // Order alphabetically last
	});
}

void UMatchLeaderboard::EnsureStatsExist(const FName& CharacterName)
{
	if (!Kills.Contains(CharacterName)) Kills.Add(CharacterName, 0);
	if (!Deaths.Contains(CharacterName)) Deaths.Add(CharacterName, 0);
}
