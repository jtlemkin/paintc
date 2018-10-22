//
// Created by James Lemkin on 12/6/17.
//

#include "command.h"

void newCommand(Canvas* canvas) {
  Command command;

  if (!getValidCommand(&command, canvas)) {
    return;
  }

  if (command.type == 'q') {
    quit(canvas);
  } else if (command.type == 'h') {
    help();
  } else if (command.type == 'w') {
    Point p1 = newPoint(atoi(command.args[1]), atoi(command.args[2]));
    Point p2 = newPoint(atoi(command.args[3]), atoi(command.args[4]));

    if (p1.col < p2.col) {
      write(canvas, p1, p2);
    } else {
      write(canvas, p2, p1);
    }
  } else if (command.type == 'e') {
    Point p = newPoint(atoi(command.args[1]), atoi(command.args[2]));
    erase(canvas, p);
  } else if (command.type == 'r') {
    resizeCanvas(canvas, atoi(command.args[1]), atoi(command.args[2]));
  } else if (command.type == 'a') {
    if (*(command.args[1]) == 'r') {
      addRow(canvas, atoi(command.args[2]));
    } else if (*(command.args[1]) == 'c') {
      addColumn(canvas, atoi(command.args[2]));
    } else {
      quit(canvas);
    }
  } else if (command.type == 'd') {
    if (*(command.args[1]) == 'r') {
      deleteRow(canvas, atoi(command.args[2]));
    } else if (*(command.args[1]) == 'c') {
      deleteColumn(canvas, atoi(command.args[2]));
    } else {
      quit(canvas);
    }
  } else if (command.type == 's') {
    saveCanvas(canvas, command.args[1]);
  } else if (command.type == 'l') {
    loadCanvas(canvas, command.args[1]);
  } else {
    quit(canvas);
  }
}

bool getValidCommand(Command* command, Canvas* canvas) {
  char* token;
  int i;
  int num1;
  int num2;

  printf("Enter your command: ");
  mygetline(command->userInput, 20);

  i = 0;

  token = strtok(command->userInput, " \n");
  command->args[i] = token;
  ++i;

  while (i < 5) {
    token = strtok(NULL, " \n");

    if (token == NULL) break;

    command->args[i] = token;
    ++i;
  }

  command->argc = i;
  command->type = *command->args[0];

  if ((command->type == 'h' || command->type == 'q') && command->argc == 1) {
    return true;
  } else if (command->type == 'w') {
    if (isValidWriteCommand(command, canvas)) {
      return true;
    } else {
      printf("Improper draw command.\n");
      return false;
    }
  } else if (command->type == 'e'){
    if (command->argc == 3) {
      num1 = atoi(command->args[1]);
      num2 = atoi(command->args[2]);

      if (num1 != -1 && num2 != -1) {
        if (num1 < canvas->numRows && num2 < canvas->numCols) {
          return true;
        }
      }
    }

    printf("Improper erase command.\n");
    return false;
  } else if (command->type == 'r') {
    if (command->argc == 3) {
      num1 = atoi(command->args[1]);
      num2 = atoi(command->args[2]);

      if (num1 >= 1 && num2 >= 1) {
        return true;
      }
    }

    printf("Improper resize command.\n");
    return false;
  } else if (command->type == 'a') {
    if (command->argc == 3) {
      num1 = atoi(command->args[2]);

      if (*(command->args[1]) == 'r' && strlen(command->args[1]) == 1) {
        if (num1 >= 0 && num1 <= canvas->numRows + 1) {
          return true;
        }
      } else if (*(command->args[1]) == 'c' && strlen(command->args[1]) == 1) {
        if (num1 >= 0 && num1 <= canvas->numCols + 1) {
          return true;
        }
      }
    }

    printf("Improper add command.\n");
    return false;
  } else if (command->type == 'd') {
    if (command->argc == 3) {
      num1 = atoi(command->args[2]);

      if (*(command->args[1]) == 'r' && strlen(command->args[1]) == 1) {
        if (num1 >= 0 && num1 < canvas->numRows) {
          return true;
        }
      } else if (*(command->args[1]) == 'c' && strlen(command->args[1]) == 1) {
        if (num1 >= 0 && num1 < canvas->numCols) {
          return true;
        }
      }
    }

    printf("Improper delete command.\n");
    return false;
  } else if (command->type == 's') {
    if (command->argc == 2) {
      return true;
    }

    printf("Improper save command or file could not be created.\n");
    return false;
  } else if (command->type == 'l') {
    bool fileExists = false;

    FILE* file = fopen(command->args[1], "r");

    if(file != NULL) {
      fileExists = true;
    }

    fclose(file);

    if (fileExists) return true;

    printf("Failed to open file: %s\n", command->args[1]);
    return false;
  } else {
    printf("Unrecognized command. Type h for help.\n");
    return false;
  }
}

void quit(Canvas* canvas) {
  deleteCanvas(canvas);
  exit(0);
}

void help(){

  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}

bool isValidWriteCommand(Command* command, Canvas* canvas) {
  int num;
  if (command->argc == 5) {
    for (int x = 1; x < 5; ++x) {
      num = atoi(command->args[x]);
      if (x % 2 == 1) {
        if (!(num >= 0 && num < canvas->numCols)) {
          return false;
        }
      } else {
        if (!(num >= 0 && num < canvas->numRows)) {
          return false;
        }
      }
    }
  } else {
    return false;
  }

  return true;
}

int mygetline(char *buf, size_t size) {
  assert(size > 0 && size < INT_MAX);
  size_t i = 0;
  int ch;
  while ((ch = fgetc(stdin)) != EOF) {
    if (i + 1 < size) {
      buf[i++] = ch;
    }
    if (ch == '\n') {
      break;
    }
  }
  buf[i] = '\0';
  if (i == 0) {
    return EOF;
  }
  return (int)i;
}