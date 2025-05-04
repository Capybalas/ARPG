// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CaAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ACaAIController::ACaAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoardComponent");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);
}
