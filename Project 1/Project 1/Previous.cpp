//
//  Previous.cpp
//  Project 1
//
//  Created by James Wu on 6/24/22.
//

#include "Previous.h"
#include <iostream>

Previous::Previous(int nRows, int nCols){
    rows = nRows;
    cols = nCols;
    
    //Populate grid "array" with dots to begin with ("array" since it's technically a C-string)
    for (int r = 0; r < rows; r++)
      for (int c = 0; c < cols; c++)
          grid[r][c] = '.';
}

bool Previous::dropACrumb(int r, int c){
    if(r > rows || r < 1 || c > cols || c < 1)
        return false;
    
    // Indicate player's positions traveled
    char current = grid[r-1][c-1];
    switch(current){
        case '.':
            current = 'A';
            break;
        case 'Z':
            break;
        default:
            current = (char)((int)current + 1); //This moves the char to be the next alphabetical letter
    }
    
    grid[r-1][c-1] = current;
    
    return true;
}

void Previous::showPreviousMoves() const {
    
    // Draw the grid
    clearScreen();
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
            std::cout << grid[r][c];
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
}
