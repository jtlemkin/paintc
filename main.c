#include <stdbool.h>
#include "canvas.h"
#include "command.h"

void getValidArgs (int argc, char* argv[], int* numRows, int* numCols);

int main(int argc, char* argv[]) {
  int numRows = 10;
  int numCols = 10;
  bool isNumber1 = true;
  bool isNumber2 = true;

  if (argc != 3 && argc != 1) {
    printf("Wrong number of command line arguements entered.\n");
    printf("Usage: ./paint.out [num_rows num_cols]\n");
    printf("Making default board of 10 X 10.\n");
  } else if (argc == 3) {
    myAtoi(argv[1], &isNumber1);
    myAtoi(argv[2], &isNumber2);
    if (!isNumber1) {
      printf("The number of rows is not an integer.\n");
      printf("Making default board of 10 X 10.\n");
    } else if (atoi(argv[1]) < 1) {
      printf("The number of rows is less than 1.\n");
      printf("Making default board of 10 X 10.\n");
    } else if (!isNumber2) {
      printf("The number of columns is not an integer.\n");
      printf("Making default board of 10 X 10.\n");
    } else if (atoi(argv[2]) < 1) {
      printf("The number of columns is less than 1.\n");
      printf("Making default board of 10 X 10.\n");
    } else {
      numRows = atoi(argv[1]);
      numCols = atoi(argv[2]);
    }
  }

  Canvas canvas = newCanvas(numRows, numCols);

  do {
    printCanvas(&canvas);
    newCommand(&canvas);
  } while (true);

  return 0;
}
