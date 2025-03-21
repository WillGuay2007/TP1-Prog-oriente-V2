#include "entrypoint.h"
#include <raylib.h>
#include <time.h>


#define RECT_SIZE 50
#define NUM_ROWS 20
#define NUM_COLS 20
#define WIN_H NUM_COLS * RECT_SIZE
#define WIN_W NUM_ROWS * RECT_SIZE

bool Tiles[NUM_ROWS][NUM_COLS] = {0};

int GetNeighbourAmount(int x, int y) {
    int Neighbours = 0;
    if ((x+1) < NUM_COLS && Tiles[x+1][y]) Neighbours ++;
    if ((x+1) < NUM_COLS && (y+1) < NUM_ROWS && Tiles[x+1][y+1]) Neighbours ++;
    if ((y+1) < NUM_ROWS && Tiles[x][y+1]) Neighbours ++;
    if ((x-1) > -1 && (y+1) < NUM_ROWS && Tiles[x-1][y+1]) Neighbours ++;
    if ((x-1) > -1 && Tiles[x-1][y]) Neighbours ++;
    if ((x-1) > -1 && (y-1) > -1 && Tiles[x-1][y-1]) Neighbours ++;
    if ((y-1) > -1 && Tiles[x][y-1]) Neighbours ++;
    if ((x+1) < NUM_COLS && (y-1) > -1 && Tiles[x+1][y-1]) Neighbours ++;
    return Neighbours;
}

void raylib_start(void){
    InitWindow(WIN_W,WIN_H, "Test");

    //Randomise les cellules vivantes et mortes avant le loop
    for (int x = 0; x < NUM_COLS; x++) {
        for (int y = 0; y < NUM_ROWS; y++) {
            Tiles[x][y] = (GetRandomValue(0, 2) == 0) ? true : false;
        }
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        for (int x = 0; x < NUM_COLS; x++) {
            for (int y = 0; y < NUM_ROWS; y++) {
                if (GetNeighbourAmount(x,y) > 2) {
                    Tiles[x][y] = false;
                }
            }
        }

    //Dessiner les tuiles
        for (int x = 0; x < NUM_COLS; x++) {
            for (int y = 0; y < NUM_ROWS; y++) {
                Rectangle rect = {float(RECT_SIZE * x), float(RECT_SIZE * y), RECT_SIZE, RECT_SIZE};
                if (Tiles[x][y] == false) {
                    DrawRectangleRec(rect, DARKBROWN); //((x + y) % 2 == 0) ? BLACK : WHITE); //(pour visualiser)
                } else {
                    DrawRectangleRec(rect, RED);//((x + y) % 2 == 0) ? BLACK : WHITE); //(pour visualiser)
                }
                DrawRectangleLines(rect.x,rect.y,rect.width,rect.height,BLACK);
            }
        }

        //DrawText(TextFormat("Current neighbours of 5,5: %d", GetNeighbourAmount(5,5)), 200, 200, 50, BLUE);
        EndDrawing();
    }
   


}
