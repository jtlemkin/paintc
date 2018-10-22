//
// Created by James Lemkin on 12/6/17.
//

#include "draw.h"

Point newPoint(int row, int col) {
  Point point;

  point.row = row;
  point.col = col;

  return point;
}

void erase(Canvas* canvas, Point p) {
  canvas->cells[p.col][p.row] = '*';
}

void write(Canvas* canvas, Point p1, Point p2) {
  if (p1.row == p2.row) {
    drawHorizontal(canvas, p1, p2);
  } else if(p1.col == p2.col) {
    if(p1.row < p2.row) {
      drawVertical(canvas, p1, p2);
    } else {
      drawVertical(canvas, p2, p1);
    }
  } else if (fabs(getSlope(p1, p2) - 1.0) < 0.00001) {
    drawRightDiagonal(canvas, p1, p2);
  } else if (fabs(getSlope(p1, p2) + 1.0) < 0.00001) {
    drawLeftDiagonal(canvas, p1, p2);
  } else if (p1.col == p2.col && p1.row == p2.row) {
    canvas->cells[p1.row][p1.col] = getStroke('-', canvas->cells[p1.col][p1.row]);
  } else {
    printf("Cannot draw the line as it is not straight.\n");
  }
}

void drawRightDiagonal(Canvas* canvas, Point right, Point left) {
  int y = right.row;
  for(int x = right.col; x <= left.col; ++x) {
    canvas->cells[y][x] = getStroke('/', canvas->cells[y][x]);
    ++y;
  }
}

void drawLeftDiagonal(Canvas* canvas, Point right, Point left) {
  int y = right.row;
  for(int x = right.col; x <= left.col; ++x) {
    canvas->cells[y][x] = getStroke('\\', canvas->cells[y][x]);
    --y;
  }
}

void drawHorizontal(Canvas* canvas, Point right, Point left) {
  for(int x = right.col; x <= left.col; ++x) {
    canvas->cells[right.row][x] = getStroke('-', canvas->cells[right.row][x]);
  }
}

void drawVertical(Canvas* canvas, Point bottom, Point top) {
  for(int y = bottom.row; y <= top.row; ++y) {
    canvas->cells[y][bottom.col] = getStroke('|', canvas->cells[y][bottom.col]);
  }
}

char getStroke(char new, char old) {
  if (old == '*' || old == new) {
    return new;
  } else {
    return '+';
  }
}

double getSlope(Point p1, Point p2) {
  return (double)(p2.row - p1.row)/(double)(p2.col - p1.col);
}
