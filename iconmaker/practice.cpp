#include "pngwriter.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std; 


// GLOBAL FUNCTION DEFINITIONS 
string pathMaker(string combo) {
  string pathToFiles = "/home/mac568/Smart-Traffic-Lights/controller/files/";
  string prefix = "i";  
  string suffix = ".png"; 
  string stringPath = pathToFiles + prefix + combo + suffix; 
 
  return stringPath; 
}

// draws a horizontal street on a 64x64 canvas 
void drawHorizontal(pngwriter &png) {
  png.filledsquare(0, 29, 63, 35, 1.0, 0.0, 0.0);
}

// draws a TL to BR diagonal street on a 64x64 canvas 
void drawTLtoBR(pngwriter &png) {
  png.line(1, 61, 61, 1, 1.0, 0.0, 0.0);
  png.line(1, 62, 62, 1, 1.0, 0.0, 0.0);
  png.line(1, 63, 63, 1, 1.0, 0.0, 0.0);
  png.line(1, 64, 64, 1, 1.0, 0.0, 0.0);
  png.line(2, 64, 64, 2, 1.0, 0.0, 0.0);
  png.line(3, 64, 64, 3, 1.0, 0.0, 0.0);
  png.line(4, 64, 64, 4, 1.0, 0.0, 0.0);
}

// draws a vertical street on a 64x64 canvas 
void drawVertical(pngwriter &png) {
  png.filledsquare(29, 1, 35, 64, 0.0, 1.0, 0.0); 
}

// draws a TR to BL diagonal street on a 64x64 canvas 
void drawTRtoBL(pngwriter &png) {
  png.line(1, 4, 61, 64, 0.0, 1.0, 0.0);
  png.line(1, 3, 62, 64, 0.0, 1.0, 0.0);
  png.line(1, 2, 63, 64, 0.0, 1.0, 0.0);
  png.line(1, 1, 64, 64, 0.0, 1.0, 0.0);
  png.line(2, 1, 64, 63, 0.0, 1.0, 0.0);
  png.line(3, 1, 64, 62, 0.0, 1.0, 0.0);
  png.line(4, 1, 64, 61, 0.0, 1.0, 0.0);
}

// draws a horizontal street on a 64x64 canvas 
// void drawHorizontal(pngwriter png, string color) {
//   if (color == "r") {
//     png.filledsquare(1, 29, 64, 35, 1.0, 0.0, 0.0);
//   }
//   else if (color == "g") {
//     png.filledsquare(1, 29, 64, 35, 0.0, 1.0, 0.0);
//   }
//   else {
//     png.filledsquare(1, 29, 64, 35, 1.0, 1.0, 0.0);
//   }
// }

// // draws a TL to BR diagonal street on a 64x64 canvas 
// void drawTLtoBR(pngwriter png, string color) {
//   if (color == "r") {
//     png.line(1, 61, 61, 1, 1.0, 0.0, 0.0);
//     png.line(1, 62, 62, 1, 1.0, 0.0, 0.0);
//     png.line(1, 63, 63, 1, 1.0, 0.0, 0.0);
//     png.line(1, 64, 64, 1, 1.0, 0.0, 0.0);
//     png.line(2, 64, 64, 2, 1.0, 0.0, 0.0);
//     png.line(3, 64, 64, 3, 1.0, 0.0, 0.0);
//     png.line(4, 64, 64, 4, 1.0, 0.0, 0.0);
//   }
//   else if (color == "g") {
//     png.line(1, 61, 61, 1, 0.0, 1.0, 0.0);
//     png.line(1, 62, 62, 1, 0.0, 1.0, 0.0);
//     png.line(1, 63, 63, 1, 0.0, 1.0, 0.0);
//     png.line(1, 64, 64, 1, 0.0, 1.0, 0.0);
//     png.line(2, 64, 64, 2, 0.0, 1.0, 0.0);
//     png.line(3, 64, 64, 3, 0.0, 1.0, 0.0);
//     png.line(4, 64, 64, 4, 0.0, 1.0, 0.0);
//   }
//   else {
//     png.line(1, 61, 61, 1, 1.0, 1.0, 0.0);
//     png.line(1, 62, 62, 1, 1.0, 1.0, 0.0);
//     png.line(1, 63, 63, 1, 1.0, 1.0, 0.0);
//     png.line(1, 64, 64, 1, 1.0, 1.0, 0.0);
//     png.line(2, 64, 64, 2, 1.0, 1.0, 0.0);
//     png.line(3, 64, 64, 3, 1.0, 1.0, 0.0);
//     png.line(4, 64, 64, 4, 1.0, 1.0, 0.0);
//   }
// }

// // draws a vertical street on a 64x64 canvas 
// void drawVertical(pngwriter png, string color) {
//   if (color == "r") {
//     png.filledsquare(29, 1, 35, 64, 1.0, 0.0, 0.0); 
//   }
//   else if (color == "g") {
//     png.filledsquare(29, 1, 35, 64, 0.0, 1.0, 0.0); 
//   }
//   else {
//     png.filledsquare(29, 1, 35, 64, 1.0, 1.0, 0.0); 
//   }
// }

// // draws a TR to BL diagonal street on a 64x64 canvas 
// void drawTRtoBL(pngwriter png, string color) {
//   if (color == "r") {
//     png.line(1, 4, 61, 64, 1.0, 0.0, 0.0);
//     png.line(1, 3, 62, 64, 1.0, 0.0, 0.0);
//     png.line(1, 2, 63, 64, 1.0, 0.0, 0.0);
//     png.line(1, 1, 64, 64, 1.0, 0.0, 0.0);
//     png.line(2, 1, 64, 63, 1.0, 0.0, 0.0);
//     png.line(3, 1, 64, 62, 1.0, 0.0, 0.0);
//     png.line(4, 1, 64, 61, 1.0, 0.0, 0.0);
//   }
//   else if (color == "g") {
//     png.line(1, 4, 61, 64, 0.0, 1.0, 0.0);
//     png.line(1, 3, 62, 64, 0.0, 1.0, 0.0);
//     png.line(1, 2, 63, 64, 0.0, 1.0, 0.0);
//     png.line(1, 1, 64, 64, 0.0, 1.0, 0.0);
//     png.line(2, 1, 64, 63, 0.0, 1.0, 0.0);
//     png.line(3, 1, 64, 62, 0.0, 1.0, 0.0);
//     png.line(4, 1, 64, 61, 0.0, 1.0, 0.0);
//   }
//   else {
//     png.line(1, 4, 61, 64, 1.0, 1.0, 0.0);
//     png.line(1, 3, 62, 64, 1.0, 1.0, 0.0);
//     png.line(1, 2, 63, 64, 1.0, 1.0, 0.0);
//     png.line(1, 1, 64, 64, 1.0, 1.0, 0.0);
//     png.line(2, 1, 64, 63, 1.0, 1.0, 0.0);
//     png.line(3, 1, 64, 62, 1.0, 1.0, 0.0);
//     png.line(4, 1, 64, 61, 1.0, 1.0, 0.0);
//   }
// }

int main()
{  
  // pngwriter png(64, 64, 1.0, "/home/mac568/Smart-Traffic-Lights/controller/files/test2.png");
  string path = pathMaker("practice"); 
  pngwriter png(64, 64, 1.0, path.c_str()); 

  drawHorizontal(png);
  drawTLtoBR(png); 
  drawVertical(png);
  drawTRtoBL(png);  

  png.close(); 

  cout << "I did it!"; 
  return 0;
}