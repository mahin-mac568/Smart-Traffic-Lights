#include "pngwriter.hpp"

int main()
{
  // specifies which folder to drop the icon in 
  // end of the path name is the icon name 
  pngwriter png(64, 64, 1.0, "/home/mac568/Smart-Traffic-Lights/controller/files/test.png");

  // horizontal street 
  png.filledsquare(1, 29, 64, 35, 1.0, 0.0, 0.0);

  // TL to BR diagonal street 
  png.line(1, 61, 61, 1, 1.0, 0.0, 0.0);
  png.line(1, 62, 62, 1, 1.0, 0.0, 0.0);
  png.line(1, 63, 63, 1, 1.0, 0.0, 0.0);
  png.line(1, 64, 64, 1, 1.0, 0.0, 0.0);
  png.line(2, 64, 64, 2, 1.0, 0.0, 0.0);
  png.line(3, 64, 64, 3, 1.0, 0.0, 0.0);
  png.line(4, 64, 64, 4, 1.0, 0.0, 0.0);

  // vertical street 
  png.filledsquare(29, 1, 35, 64, 0.0, 1.0, 0.0); 

  // TR to BL diagonal street 
  png.line(1, 4, 61, 64, 0.0, 1.0, 0.0);
  png.line(1, 3, 62, 64, 0.0, 1.0, 0.0);
  png.line(1, 2, 63, 64, 0.0, 1.0, 0.0);
  png.line(1, 1, 64, 64, 0.0, 1.0, 0.0);
  png.line(2, 1, 64, 63, 0.0, 1.0, 0.0);
  png.line(3, 1, 64, 62, 0.0, 1.0, 0.0);
  png.line(4, 1, 64, 61, 0.0, 1.0, 0.0);

  png.close();

  return 0;
}