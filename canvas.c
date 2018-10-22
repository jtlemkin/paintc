//
// Created by James Lemkin on 12/6/17.
//

#include "canvas.h"

Canvas newCanvas(int numRows, int numCols) {
  Canvas canvas;

  canvas.numRows = numRows;
  canvas.numCols = numCols;
  canvas.cells = (char**)malloc(numRows * sizeof(char*));

  for(int row = 0; row < numRows; ++row) {
    canvas.cells[row] = (char*)malloc((numCols + 1) * sizeof(char));

    for(int col = 0; col < numCols; ++col) {
      canvas.cells[row][col] = '*';
    }

    canvas.cells[row][numCols] = '\0';
  }

  return canvas;
}

void printCanvas(Canvas* canvas) {
  for(int row = canvas->numRows - 1; row >=  0; --row) {
    printf("%d ", row);

    for(int col = 0; col < canvas->numCols; ++col) {
      printf("%c ", canvas->cells[row][col]);
    }
    printf("\n");
  }

  printf("  ");

  for(int col = 0; col < canvas->numCols; ++col) {
    printf("%d ", col);
  }

  printf("\n");
}

void resizeCanvas(Canvas* canvas, int numRows, int numCols) {
  int oldNumRows = canvas->numRows;
  int oldNumCols = canvas->numCols;

  canvas->numRows = numRows;
  canvas->numCols = numCols;

  for(int row = oldNumRows - 1; row >= canvas->numRows; --row) {
    free(canvas->cells[row]);
  }

  canvas->cells = (char**)realloc(canvas->cells, canvas->numRows * sizeof(char*));

  for(int row = canvas->numRows - 1; row >= oldNumRows; --row) {
    canvas->cells[row] = NULL;
  }

  for(int row = 0; row < numRows; ++row) {
    canvas->cells[row] = (char*)realloc(canvas->cells[row], (canvas->numCols + 1) * sizeof(char));

    if (row >= oldNumRows) {
      for(int col = 0; col < numCols; ++col) {
        canvas->cells[row][col] = '*';
      }
    } else {
      for(int col = oldNumCols; col < numCols; ++col) {
        canvas->cells[row][col] = '*';
      }
    }

    canvas->cells[row][canvas->numCols] = '\0';
  }
}

void addRow(Canvas* canvas, int newRowIndex) {
  resizeCanvas(canvas, canvas->numRows + 1, canvas->numCols);

  char* temp = canvas->cells[canvas->numRows - 1];

  for(int row = canvas->numRows - 1; row > newRowIndex; --row) {
    canvas->cells[row] = canvas->cells[row - 1];
  }

  canvas->cells[newRowIndex] = temp;
}

void addColumn(Canvas* canvas, int newColIndex) {
  resizeCanvas(canvas, canvas->numRows, canvas->numCols + 1);

  for (int row = canvas->numRows - 1; row >= 0; --row) {
    for (int col = canvas->numCols - 1; col > newColIndex; --col) {
      canvas->cells[row][col] = canvas->cells[row][col - 1];
    }

    canvas->cells[row][newColIndex] = '*';
  }
}

void deleteRow(Canvas* canvas, int rowIndex) {
  char* temp = canvas->cells[rowIndex];

  for (int row = rowIndex; row < canvas->numRows - 1; ++row) {
    canvas->cells[row] = canvas->cells[row + 1];
  }

  canvas->cells[canvas->numRows - 1] = temp;

  resizeCanvas(canvas, canvas->numRows - 1, canvas->numCols);
}

void deleteColumn(Canvas* canvas, int colIndex) {
  for (int row = canvas->numRows - 1; row >= 0; --row) {
    for (int col = colIndex; col < canvas->numCols - 1; ++col) {
      canvas->cells[row][col] = canvas->cells[row][col + 1];
    }
  }

  resizeCanvas(canvas, canvas->numRows, canvas->numCols - 1);
}

void saveCanvas(Canvas* canvas, char* fileName) {
  FILE* file = fopen(fileName, "w");

  fprintf(file, "%d %d\n", canvas->numRows, canvas->numCols);

  for(int row = canvas->numRows - 1; row >= 0; --row) {
    fprintf(file, "%s\n", canvas->cells[row]);
  }

  fclose(file);
}

void loadCanvas(Canvas* canvas, char* fileName) {
  FILE* file = fopen(fileName, "r");

  int numRows = 10;
  int numCols = 10;

  fscanf(file, "%d %d", &numRows, &numCols);

  resizeCanvas(canvas, numRows, numCols);

  for (int row = canvas->numRows - 1; row >= 0; --row) {
    fscanf(file, "%s", canvas->cells[row]);
  }

  fclose(file);
}

void deleteCanvas(Canvas* canvas) {
  for(int row = 0; row < canvas->numRows; ++row) {
    free(canvas->cells[row]);
    canvas->cells[row] = NULL;
  }

  free(canvas->cells);
  canvas->cells = NULL;
}