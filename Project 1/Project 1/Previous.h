//
//  Previous.h
//  Project 1
//
//  Created by James Wu on 6/24/22.
//

#ifndef Previous_h
#define Previous_h
#include "globals.h"

class Previous
{
public:
     Previous(int nRows, int nCols);
     bool dropACrumb(int r, int c);
     void showPreviousMoves() const;
    
private:
    int rows;
    int cols;
    char grid[MAXROWS][MAXCOLS];
};

#endif /* Previous_h */
