#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <set>
#include "../Qubit/Qubit.h"


void singleGSA(unsigned, unsigned = 0);

void multipleGSA(unsigned, unsigned = 0, std::vector<unsigned> = {});
