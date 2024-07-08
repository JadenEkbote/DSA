#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Define the grid size
#define ROW 5
#define COL 5

// A structure to represent a cell in the grid
typedef struct
{
    int parentRow, parentCol;
    double f, g, h;
} Cell;

// Function to check if a given cell is valid (inside the grid)
bool isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// Function to check if a given cell is an obstacle or not
bool isUnBlocked(int grid[ROW][COL], int row, int col)
{
    return grid[row][col] == 1;
}

// Function to check if the destination cell has been reached
bool isDestination(int row, int col, int destRow, int destCol)
{
    return row == destRow && col == destCol;
}

// Heuristic function to calculate the 'h' value (Euclidean distance)
double calculateHValue(int row, int col, int destRow, int destCol)
{
    return sqrt((row - destRow) * (row - destRow) + (col - destCol) * (col - destCol));
}

// Function to trace the path from the source to the destination
void tracePath(Cell cellDetails[ROW][COL], int destRow, int destCol)
{
    printf("The path is:\n");
    int row = destRow;
    int col = destCol;
    while (!(cellDetails[row][col].parentRow == row && cellDetails[row][col].parentCol == col))
    {
        printf("-> (%d,%d) ", row, col);
        int tempRow = cellDetails[row][col].parentRow;
        int tempCol = cellDetails[row][col].parentCol;
        row = tempRow;
        col = tempCol;
    }
    printf("-> (%d,%d)\n", row, col);
}

// Function to implement the A* Search Algorithm
void aStarSearch(int grid[ROW][COL], int srcRow, int srcCol, int destRow, int destCol)
{
    // If the source is out of range
    if (!isValid(srcRow, srcCol))
    {
        printf("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if (!isValid(destRow, destCol))
    {
        printf("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked
    if (!isUnBlocked(grid, srcRow, srcCol) || !isUnBlocked(grid, destRow, destCol))
    {
        printf("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(srcRow, srcCol, destRow, destCol))
    {
        printf("We are already at the destination\n");
        return;
    }

    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    Cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parentRow = -1;
            cellDetails[i][j].parentCol = -1;
        }
    }

    i = srcRow, j = srcCol;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parentRow = i;
    cellDetails[i][j].parentCol = j;

    bool foundDest = false;

    while (true)
    {
        double min = FLT_MAX;
        int minRow = -1, minCol = -1;

        for (i = 0; i < ROW; i++)
        {
            for (j = 0; j < COL; j++)
            {
                if (!closedList[i][j] && cellDetails[i][j].f < min)
                {
                    min = cellDetails[i][j].f;
                    minRow = i;
                    minCol = j;
                }
            }
        }

        if (minRow == -1 && minCol == -1)
        {
            printf("Failed to find the Destination Cell\n");
            return;
        }

        i = minRow;
        j = minCol;
        closedList[i][j] = true;

        int newRow, newCol;

        // Explore 8 possible movements from the current cell
        for (int dRow = -1; dRow <= 1; dRow++)
        {
            for (int dCol = -1; dCol <= 1; dCol++)
            {
                newRow = i + dRow;
                newCol = j + dCol;

                if (isValid(newRow, newCol))
                {
                    if (isDestination(newRow, newCol, destRow, destCol))
                    {
                        cellDetails[newRow][newCol].parentRow = i;
                        cellDetails[newRow][newCol].parentCol = j;
                        printf("The destination cell is found\n");
                        tracePath(cellDetails, destRow, destCol);
                        foundDest = true;
                        return;
                    }
                    else if (!closedList[newRow][newCol] && isUnBlocked(grid, newRow, newCol))
                    {
                        double gNew = cellDetails[i][j].g + 1.0;
                        double hNew = calculateHValue(newRow, newCol, destRow, destCol);
                        double fNew = gNew + hNew;

                        if (cellDetails[newRow][newCol].f == FLT_MAX || cellDetails[newRow][newCol].f > fNew)
                        {
                            cellDetails[newRow][newCol].f = fNew;
                            cellDetails[newRow][newCol].g = gNew;
                            cellDetails[newRow][newCol].h = hNew;
                            cellDetails[newRow][newCol].parentRow = i;
                            cellDetails[newRow][newCol].parentCol = j;
                        }
                    }
                }
            }
        }

        if (foundDest)
            break;
    }
}

int main()
{
    int grid[ROW][COL] =
        {
            {1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1},
            {1, 1, 1, 0, 1},
            {0, 0, 1, 1, 1},
            {1, 1, 1, 1, 1}};

    int srcRow = 0, srcCol = 0;
    int destRow = 4, destCol = 4;

    aStarSearch(grid, srcRow, srcCol, destRow, destCol);

    return 0;
}
