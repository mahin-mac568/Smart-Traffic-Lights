#include "pngwriter.hpp"

int main()
{
  pngwriter png(64, 64, 1.0, "/home/mac568/4414-hw1/controller/files/test.png");

  png.filledsquare(0, 29, 63, 35, 1.0, 0.0, 0.0);

  png.line(0, 60, 60, 0, 1.0, 0.0, 0.0);
  png.line(0, 61, 61, 0, 1.0, 0.0, 0.0);
  png.line(0, 62, 62, 0, 1.0, 0.0, 0.0);
  png.line(0, 63, 63, 0, 1.0, 0.0, 0.0);
  png.line(1, 63, 63, 1, 1.0, 0.0, 0.0);
  png.line(2, 63, 63, 2, 1.0, 0.0, 0.0);
  png.line(3, 63, 63, 3, 1.0, 0.0, 0.0);

  png.filledsquare(29, 0, 35, 63, 0.0, 1.0, 0.0);

  png.line(0, 3, 60, 63, 0.0, 1.0, 0.0);
  png.line(0, 2, 61, 63, 0.0, 1.0, 0.0);
  png.line(0, 1, 62, 63, 0.0, 1.0, 0.0);
  png.line(0, 0, 63, 63, 0.0, 1.0, 0.0);
  png.line(1, 0, 63, 62, 0.0, 1.0, 0.0);
  png.line(2, 0, 63, 61, 0.0, 1.0, 0.0);
  png.line(3, 0, 63, 60, 0.0, 1.0, 0.0);

  png.close();

  return 0;
}