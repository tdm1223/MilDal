// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(MilDal, Log, All);

#define MD_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define MD_LOG_CALLONLY(Verbosity) UE_LOG(MilDal, Verbosity, TEXT("%s"), *MD_LOG_CALLINFO)
#define MD_LOG(Verbosity, Format, ...) UE_LOG(MilDal, Verbosity, TEXT("%s %s"), *MD_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__)) 