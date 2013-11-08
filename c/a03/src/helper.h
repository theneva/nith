#pragma once

#include <stdio.h>

#ifdef IS_DEBUG
	#define DEBUG(x, ...) fprintf(stderr, x, __VA_ARGS__)
#else
	#define DEBUG(x, ...)
#endif
