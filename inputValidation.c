//
// Created by James Lemkin on 12/12/17.
//

#include "inputValidation.h"

bool isValidInput(char* str, const int numArgsNeeded, const int numArgsRead, const bool isLastElementOnLine) {

  char lastCharacterOnLine;

  // did we read everything we needed to read?
  bool correctFormat = (numArgsRead == numArgsNeeded);

  if (isLastElementOnLine) {  // if this is supposed to be the last thing on the line
    // check that it was by reading one more character
    // and seeing it it a newline (the end of the line)
    sscanf(str, "%c", &lastCharacterOnLine);
    correctFormat = correctFormat && lastCharacterOnLine == '\n';
  }
  return correctFormat;
}

// A utility function to check whether x is numeric
bool isNumericChar(char x)
{
  return (x >= '0' && x <= '9')? true: false;
}

// A simple atoi() function. If the given string contains
// any invalid character, then this function returns -1
int myAtoi(char *str, bool* isNumber)
{
  *isNumber = true;
  int sign = 1;

  if (str == NULL)
    return 0;

  int res = 0;  // Initialize result
  int i = 0;  // Initialize index of first digit

  if (str[0] == '-')
  {
    sign = -1;
    i++;
  }

  // Iterate through all digits of input string and update result
  for (; str[i] != '\0'; ++i)
  {
    if (isNumericChar(str[i]) == false) {
      *isNumber = false;
      return 0;
    }

    res = res*10 + str[i] - '0';
  }

  // Return result with sign
  return res*sign;
}