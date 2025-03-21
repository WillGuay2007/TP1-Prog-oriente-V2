#include "entrypoint.h"
#include <raylib.h>
#include <time.h>


#define RECT_SIZE 2
#define NUM_ROWS 400
#define NUM_COLS 400
#define WIN_H NUM_COLS * RECT_SIZE
#define WIN_W NUM_ROWS * RECT_SIZE

int GetNeighbourAmount(int x, int y, bool tiles[NUM_COLS][NUM_ROWS]) {
    int Neighbours = 0;
    if ((x+1) < NUM_COLS && tiles[x+1][y]) Neighbours ++;
    if ((x+1) < NUM_COLS && (y+1) < NUM_ROWS && tiles[x+1][y+1]) Neighbours ++;
    if ((y+1) < NUM_ROWS && tiles[x][y+1]) Neighbours ++;
    if ((x-1) > -1 && (y+1) < NUM_ROWS && tiles[x-1][y+1]) Neighbours ++;
    if ((x-1) > -1 && tiles[x-1][y]) Neighbours ++;
    if ((x-1) > -1 && (y-1) > -1 && tiles[x-1][y-1]) Neighbours ++;
    if ((y-1) > -1 && tiles[x][y-1]) Neighbours ++;
    if ((x+1) < NUM_COLS && (y-1) > -1 && tiles[x+1][y-1]) Neighbours ++;
    return Neighbours;
}

bool Tiles[NUM_COLS][NUM_ROWS] = {0};
bool TilesTempModifications[NUM_COLS][NUM_ROWS] = {0};

void Underpopulation(int x, int y, bool tiles[NUM_COLS][NUM_ROWS]) {
    if (GetNeighbourAmount(x,y, tiles) < 2) TilesTempModifications[x][y] = false;
}

void Survival(int x, int y, bool tiles[NUM_COLS][NUM_ROWS]) {
    if (tiles[x][y] == true && (GetNeighbourAmount(x,y, tiles) == 2 || GetNeighbourAmount(x,y, tiles) == 3)) TilesTempModifications[x][y] = true;
}

void OverPopulation(int x, int y, bool tiles[NUM_COLS][NUM_ROWS]) {
    if (GetNeighbourAmount(x,y, tiles) > 3) TilesTempModifications[x][y] = false;
}

void Reproduction(int x, int y, bool tiles[NUM_COLS][NUM_ROWS]) {
    if (GetNeighbourAmount(x,y, tiles) == 3) TilesTempModifications[x][y] = true;
}

void raylib_start(void){
    InitWindow(WIN_W,WIN_H, "Test");

    SetTargetFPS(60);

    //Randomise les cellules vivantes et mortes avant le loop
    for (int x = 0; x < NUM_COLS; x++) {
        for (int y = 0; y < NUM_ROWS; y++) {
            Tiles[x][y] = (GetRandomValue(0,1) == 1) ? true : false;
            TilesTempModifications[x][y] = Tiles[x][y];
        }
    }

    while (!WindowShouldClose())
    {
        // Appliquer les modifications aux tuiles temporaires
        for (int x = 0; x < NUM_COLS; x++) {
            for (int y = 0; y < NUM_ROWS; y++) {
                Underpopulation(x,y, Tiles);
                Survival(x,y, Tiles);
                OverPopulation(x,y, Tiles);
                Reproduction(x,y, Tiles);
            }
        }

        // Donner les valeurs modifiés aux tuiles actuelles
        for (int x = 0; x < NUM_COLS; x++) {
            for (int y = 0; y < NUM_ROWS; y++) {
                Tiles[x][y] = TilesTempModifications[x][y];
            }
        }


        //Dessiner les tuiles
        BeginDrawing();
        ClearBackground(WHITE);

        for (int x = 0; x < NUM_COLS; x++) {
            for (int y = 0; y < NUM_ROWS; y++) {
                Rectangle rect = {float(RECT_SIZE * x), float(RECT_SIZE * y), RECT_SIZE, RECT_SIZE};
                if (Tiles[x][y]) {
                    DrawRectangleRec(rect, GREEN);
                } else {
                    DrawRectangleRec(rect, GRAY);
                }
                //DrawRectangleLines(rect.x,rect.y,rect.width,rect.height,BLACK); //(Décommenter pour voir les lignes de grid)
            }
        }

        //DrawText(TextFormat("Current neighbours of 5,5: %d", GetNeighbourAmount(5,5)), 200, 200, 50, BLUE);
        EndDrawing();
    }
}