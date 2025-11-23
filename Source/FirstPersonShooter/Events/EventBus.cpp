#include "Events/EventBus.h"
#include "Events/EventListener.h"

void UEventBus::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	EventListeners.Empty();
}

void UEventBus::Deinitialize()
{
	EventListeners.Empty();
	Super::Deinitialize();
}

void UEventBus::AddListener(FName EventName, TScriptInterface<IEventListener> Listener)
{
	if (EventListeners.Contains(EventName)) EventListeners.Find(EventName)->AddUnique(Listener);
	else EventListeners.Add(EventName, { Listener });
}

void UEventBus::RemoveListener(FName EventName, TScriptInterface<IEventListener> Listener)
{
	if (TArray<TScriptInterface<IEventListener>>* Listeners = EventListeners.Find(EventName))
	{
		Listeners->Remove(Listener);
		if (Listeners->IsEmpty()) EventListeners.Remove(EventName);
	}
}

void UEventBus::Broadcast(FName EventName, const TArray<FEventData>& Params)
{
	if (!EventListeners.Contains(EventName)) return;
	if (TArray<TScriptInterface<IEventListener>>* Listeners = EventListeners.Find(EventName))
	{
		if (Listeners->IsEmpty()) return;
		for (int i = Listeners->Num() - 1; i >= 0; --i)
			if ((*Listeners)[i]) (*Listeners)[i]->Execute_OnEventReceived((*Listeners)[i].GetObject(), EventName, Params);
	}
}
