//
// Created by James Lemkin on 12/6/17.
//

#ifndef PAINT_DRAW_H
#define PAINT_DRAW_H

#include "canvas.h"
#include <math.h>
#include <printf.h>
typedef struct Point_struct {
  int row;
  int col;
}Point;

Point newPoint(int x, int y);
void write(Canvas* canvas, Point p1, Point p2);
void drawVertical(Canvas* canvas, Point bottom, Point top);
void drawHorizontal(Canvas* canvas, Point right, Point left);
double getSlope(Point p1, Point p2);
void drawRightDiagonal(Canvas* canvas, Point right, Point left);
void drawLeftDiagonal(Canvas* canvas, Point right, Point left);
char getStroke(char new, char old);
void erase(Canvas* canvas, Point p);
#endif //PAINT_DRAW_H
