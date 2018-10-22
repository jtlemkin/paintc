//
// Created by James Lemkin on 12/6/17.
//

#ifndef PAINT_CANVAS_H
#define PAINT_CANVAS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Canvas_struct{
  char** cells;
  int numRows;
  int numCols;
}Canvas;

Canvas newCanvas(int numRows, int numCols);
void printCanvas(Canvas* canvas);
void resizeCanvas(Canvas* canvas, int numRows, int numCols);
void addRow(Canvas* canvas, int newRowIndex);
void addColumn(Canvas* canvas, int newColIndex);
void deleteRow(Canvas* canvas, int rowIndex);
void deleteColumn(Canvas* canvas, int colIndex);
void saveCanvas(Canvas* canvas, char* fileName);
void loadCanvas(Canvas* canvas, char* fileName);
void deleteCanvas(Canvas* canvas);

#endif //PAINT_CANVAS_H
