// Fill out your copyright notice in the Description page of Project Settings.


#include "Events/EventBus.h"
#include "Events/EventListener.h"
#include "Events/EventData.h"

void UEventBus::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	EventListeners.Empty();
}

void UEventBus::Deinitialize() {
	EventListeners.Empty();
	Super::Deinitialize();
}

void UEventBus::AddListener(FName EventName, TScriptInterface<IEventListener> Listener) {
	if (EventListeners.Contains(EventName)) EventListeners.Find(EventName)->AddUnique(Listener);
	else EventListeners.Add(EventName, { Listener });
}

void UEventBus::RemoveListener(FName EventName, TScriptInterface<IEventListener> Listener) {
	if (TArray<TScriptInterface<IEventListener>>* Listeners = EventListeners.Find(EventName)) {
		Listeners->Remove(Listener);
		if (Listeners->IsEmpty()) EventListeners.Remove(EventName);
	}
}

void UEventBus::Broadcast(FName EventName, TArray<FEventData>& Params) {
	if (TArray<TScriptInterface<IEventListener>>* Listeners = EventListeners.Find(EventName)) {
		for (int i = Listeners->Num() - 1; i >= 0; --i) {
			if ((*Listeners)[i]) (*Listeners)[i]->Execute_OnEventReceived((*Listeners)[i].GetObject(), EventName, Params);
		}
	}
}
