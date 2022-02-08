// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

GAMEPLAYCOMBATSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogCombat, Display, All);

#define GCS_LOG(Verbosity, Format, ...) \
{ \
	UE_LOG(LogCombat, Verbosity, Format, ##__VA_ARGS__); \
}


/*
 *
 * Fatal
 * Fatal等级日志总是会打印到控制台和日志文件以及crash文件中，甚至logging功能被禁用。
 *
 * Error
 * Error等级日志被打印到控制台和日志文件中，默认以红色显示。
 *
 * Warning
 * Warning等级日志被打印到控制台和日志文件中，默认以黄色显示。
 *
 * Display
 * Display等级日志被打印到控制台和日志文件中。
 *
 * Log
 * Log等级日志打印到日志文件中但是不出现在game模式的控制台中，但是通过编辑器的日志输出窗口还是能够被看到。
 *
 * Verbose
 * Verbose等级日志打印到日志文件中但是不出现在game模式的控制台中，这个通常被用来作为详细日志和调试使用。
 *
 * VeryVerbose
 * VeryVerbose等级日志被打印到日志文件中但是不出现在game模式的控制台中，这通常用来打印非常详细的日志记录否则会产生很多不必要的垃圾输出。
 *
 */

