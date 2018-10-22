//
// Created by James Lemkin on 12/6/17.
//

#ifndef PAINT_COMMAND_H
#define PAINT_COMMAND_H

#include <printf.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "draw.h"
#include "inputValidation.h"
typedef struct Command_struct {
  char type;
  char userInput[50];
  int argc;
  char* args[5];
}Command;

void newCommand(Canvas* canvas);
bool getValidCommand(Command* command, Canvas* canvas);
bool isValidWriteCommand(Command* command, Canvas* canvas);
void quit(Canvas* canvas);
void help();
int mygetline(char *buf, size_t size);

#endif //PAINT_COMMAND_H
