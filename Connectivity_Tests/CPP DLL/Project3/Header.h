// MathLibrary.h - Contains declarations of math functions
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#ifdef Project3_EXPORTS
#define Project3_API __declspec(dllimport)
#else
#define Project3_API __declspec(dllexport)
#endif

typedef struct History
{
	int i=-1;
}History;
typedef struct a
{
	int i;
	char b[5];
	History hst[2];
	//int hst[2];
}a;

extern "C" __declspec(dllexport) a* __stdcall testRet(int* length);
extern "C" __declspec(dllexport) int __stdcall rem(a arr[]);
extern "C" __declspec(dllexport) int __stdcall remHst(History arr[]);
