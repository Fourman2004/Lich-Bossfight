// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CPP_Rand_number.generated.h"

class UBlackboardKeyType;


/**
 * 
 */
UCLASS()
class GAM206_API UCPP_Rand_number : public UBTTaskNode
{
	GENERATED_BODY()

public:
		
	UBlackboardKeyType* key;

	void Execute_Ai(int Max_atk);
};