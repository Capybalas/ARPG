// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FCaItem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "物品名称"))
	FName Name = "Default";

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "是否可堆叠"))
	bool bIsStackable = true;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "物品图标"))
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "最大堆叠数"))
	int32 MaxStackSize = 1;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "是否是消耗品"))
	bool bIsConsumable = false;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "物品描述"))
	FText Description;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "物品的静态网格体"))
	TSoftObjectPtr<UStaticMesh> StaticMesh;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ARPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
