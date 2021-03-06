#include "pngwriter.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std; 

// GLOBAL FUNCTION DEFINITIONS 

// returns the file path for the icons' destination, in string form 
string pathMaker(string combo) {
  //  adjust the file path to start with `../controller/files`
  

  string pathToFiles = "../controller/files/";
  string prefix = "i";  
  string comboLen = to_string(combo.length()); 
  string suffix = ".png"; 

  string stringPath = pathToFiles + prefix + comboLen + combo + suffix; 
  return stringPath; 
}

// draws a horizontal street on a 64x64 canvas 
void drawHorizontal(pngwriter &png, char color) {
  if (color == 'r') {
    png.filledsquare(1, 29, 64, 35, 1.0, 0.0, 0.0);
  }
  else if (color == 'g') {
    png.filledsquare(1, 29, 64, 35, 0.0, 1.0, 0.0);
  }
  else {
    png.filledsquare(1, 29, 64, 35, 1.0, 1.0, 0.0);
  }
}

// draws a TL to BR diagonal street on a 64x64 canvas 
void drawTLtoBR(pngwriter &png, char color) {
  if (color == 'r') {
    png.line(1, 61, 61, 1, 1.0, 0.0, 0.0);
    png.line(1, 62, 62, 1, 1.0, 0.0, 0.0);
    png.line(1, 63, 63, 1, 1.0, 0.0, 0.0);
    png.line(1, 64, 64, 1, 1.0, 0.0, 0.0);
    png.line(2, 64, 64, 2, 1.0, 0.0, 0.0);
    png.line(3, 64, 64, 3, 1.0, 0.0, 0.0);
    png.line(4, 64, 64, 4, 1.0, 0.0, 0.0);
  }
  else if (color == 'g') {
    png.line(1, 61, 61, 1, 0.0, 1.0, 0.0);
    png.line(1, 62, 62, 1, 0.0, 1.0, 0.0);
    png.line(1, 63, 63, 1, 0.0, 1.0, 0.0);
    png.line(1, 64, 64, 1, 0.0, 1.0, 0.0);
    png.line(2, 64, 64, 2, 0.0, 1.0, 0.0);
    png.line(3, 64, 64, 3, 0.0, 1.0, 0.0);
    png.line(4, 64, 64, 4, 0.0, 1.0, 0.0);
  }
  else {
    png.line(1, 61, 61, 1, 1.0, 1.0, 0.0);
    png.line(1, 62, 62, 1, 1.0, 1.0, 0.0);
    png.line(1, 63, 63, 1, 1.0, 1.0, 0.0);
    png.line(1, 64, 64, 1, 1.0, 1.0, 0.0);
    png.line(2, 64, 64, 2, 1.0, 1.0, 0.0);
    png.line(3, 64, 64, 3, 1.0, 1.0, 0.0);
    png.line(4, 64, 64, 4, 1.0, 1.0, 0.0);
  }
}

// draws a vertical street on a 64x64 canvas 
void drawVertical(pngwriter &png, char color) {
  if (color == 'r') {
    png.filledsquare(29, 1, 35, 64, 1.0, 0.0, 0.0); 
  }
  else if (color == 'g') {
    png.filledsquare(29, 1, 35, 64, 0.0, 1.0, 0.0); 
  }
  else {
    png.filledsquare(29, 1, 35, 64, 1.0, 1.0, 0.0); 
  }
}

// draws a TR to BL diagonal street on a 64x64 canvas 
void drawTRtoBL(pngwriter &png, char color) {
  if (color == 'r') {
    png.line(1, 4, 61, 64, 1.0, 0.0, 0.0);
    png.line(1, 3, 62, 64, 1.0, 0.0, 0.0);
    png.line(1, 2, 63, 64, 1.0, 0.0, 0.0);
    png.line(1, 1, 64, 64, 1.0, 0.0, 0.0);
    png.line(2, 1, 64, 63, 1.0, 0.0, 0.0);
    png.line(3, 1, 64, 62, 1.0, 0.0, 0.0);
    png.line(4, 1, 64, 61, 1.0, 0.0, 0.0);
  }
  else if (color == 'g') {
    png.line(1, 4, 61, 64, 0.0, 1.0, 0.0);
    png.line(1, 3, 62, 64, 0.0, 1.0, 0.0);
    png.line(1, 2, 63, 64, 0.0, 1.0, 0.0);
    png.line(1, 1, 64, 64, 0.0, 1.0, 0.0);
    png.line(2, 1, 64, 63, 0.0, 1.0, 0.0);
    png.line(3, 1, 64, 62, 0.0, 1.0, 0.0);
    png.line(4, 1, 64, 61, 0.0, 1.0, 0.0);
  }
  else {
    png.line(1, 4, 61, 64, 1.0, 1.0, 0.0);
    png.line(1, 3, 62, 64, 1.0, 1.0, 0.0);
    png.line(1, 2, 63, 64, 1.0, 1.0, 0.0);
    png.line(1, 1, 64, 64, 1.0, 1.0, 0.0);
    png.line(2, 1, 64, 63, 1.0, 1.0, 0.0);
    png.line(3, 1, 64, 62, 1.0, 1.0, 0.0);
    png.line(4, 1, 64, 61, 1.0, 1.0, 0.0);
  }
}

// GLOBAL ARRAYS
vector<string> colorChars { "r", "g", "y" }; 
vector<string> combosOfTwo;               
vector<string> combosOfThree; 
vector<string> combosOfFour;  // Citation: https://stackoverflow.com/questions/755835/how-to-add-element-to-c-array 


int main()
{  
  // GENERATING ALL OF THE STREET LIGHT COMBINATIONS

  // Light combinations for 2 streets 
  for (int i=0; i<3; i++) {
    string color1 = colorChars[i]; 
    for (int j=0; j<3; j++) {
      string color2 = colorChars[j]; 
      string combo = color1 + color2; 
      combosOfTwo.push_back(combo); // Citation: https://stackoverflow.com/questions/755835/how-to-add-element-to-c-array 
    } 
  }

  // Light combinations for 3 streets 
  for (int i=0; i<3; i++) {
    string color1 = colorChars[i]; 
    for (int j=0; j<3; j++) {
      string color2 = colorChars[j]; 
      for (int k=0; k<3; k++) {
        string color3 = colorChars[k]; 
        string combo = color1 + color2 + color3; 
        combosOfThree.push_back(combo); 
      }
    } 
  }

  // Light combinations for 4 streets 
  for (int i=0; i<3; i++) {
    string color1 = colorChars[i]; 
    for (int j=0; j<3; j++) {
      string color2 = colorChars[j]; 
      for (int k=0; k<3; k++) {
        string color3 = colorChars[k]; 
        for (int p=0; p<3; p++) {
          string color4 = colorChars[p]; 
          string combo = color1 + color2 + color3 + color4; 
          combosOfFour.push_back(combo); 
        }
      }
    } 
  }

  // DRAWING ALL OF THE ICONS AND DROPPING THEM INTO FILES FOLDER 

  // drawing the combinations for 2 streets 
  for (int i=0; i<9; i++) {
    string combo = combosOfTwo[i]; // index the color combo 
    string path = pathMaker(combo); // make the path name 
    pngwriter png(64, 64, 1.0, path.c_str());   // Citation: https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char

    for (int j=0; j<2; j++) {
      if (j==0) {
        drawHorizontal(png, combo[j]); 
      }
      else if (j==1) {
        drawVertical(png, combo[j]); 
      }
    }

    png.close(); 
  }

  // drawing the combinations for 3 streets 
  for (int i=0; i<27; i++) {
    string combo = combosOfThree[i]; 
    string path = pathMaker(combo);             
    pngwriter png(64, 64, 1.0, path.c_str());   

    for (int j=0; j<3; j++) {
      if (j==0) {
        drawHorizontal(png, combo[j]); 
      }
      else if (j==1) {
        drawTLtoBR(png, combo[j]); 
      }
      else if (j==2) {
        drawVertical(png, combo[j]); 
      }
    }
    
    png.close(); 
  }

  // drawing the combinations for 4 streets 
  for (int i=0; i<81; i++) {
    string combo = combosOfFour[i]; 
    string path = pathMaker(combo);    
    pngwriter png(64, 64, 1.0, path.c_str());   

    for (int j=0; j<4; j++) {
      if (j==0) {
        drawHorizontal(png, combo[j]); 
      }
      else if (j==1) {
        drawTLtoBR(png, combo[j]); 
      }
      else if (j==2) {
        drawVertical(png, combo[j]); 
      }
      else {
        drawTRtoBL(png, combo[j]); 
      }
    }
    
    png.close(); 
  }

  cout << "I did it!" << endl; 
  return 0;
}