// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#ifdef WIN32 

#define INT ::INT
#define UINT ::UINT
#define DWORD ::DWORD
#define FLOAT ::FLOAT

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


#endif
