//
// Created by James Lemkin on 12/12/17.
//

#ifndef PAINT_INPUTVALIDATION_H
#define PAINT_INPUTVALIDATION_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "command.h"
bool isValidInput(char* str, const int numArgsNeeded, const int numArgsRead, const bool isLastElementOnLine);
bool isNumericChar(char x);
int myAtoi(char *str, bool* isNumber);
#endif //PAINT_INPUTVALIDATION_H
