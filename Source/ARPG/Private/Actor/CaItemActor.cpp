// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CaItemActor.h"


ACaItemActor::ACaItemActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetStaticMesh(StaticMesh);
}
