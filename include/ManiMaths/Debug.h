#pragma once

#include <assert.h>

#ifndef SUPPRESS_ASSERT
#define MANIMATHS_ASSERT(EXPRESSION) assert(EXPRESSION);
#else
#define MANIMATHS_ASSERT(EXPRESSION)
#endif
