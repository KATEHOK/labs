#pragma once


typedef struct {
	char* pData;
	void* pPrevious;
} Item;

typedef struct {
	Item* top;
} Release;