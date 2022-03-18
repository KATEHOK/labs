#pragma once
#define _CRTDBG_MAP_ALLOC
#define VECTOR
#define A_H
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>

#ifdef VECTOR
#include "vector.h"
#else
#include "list.h"
#endif

#include "stack.h"
#include "funcs.h"