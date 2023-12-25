#include <iostream>
#include <raylib.h>
#include <math.h>
#include <string.h>
#include <format>

float rota = 0;
double speed = 0.04;
float stub = 0;
unsigned int  balls = 10;
unsigned framecounter = 0;
float nowspeed = 0;
int colnum = 1;
float red =10;
float green =10;
float blue =10;
Color col = RED;

int main() {
    InitWindow(1920, 1200, "Loading..");
    SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    //SetTargetFPS(160);
    //ToggleFullscreen();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP)) {
            speed += 0.02;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            speed -= 0.02;
        }
        if (IsKeyDown(KEY_B)) {
            framecounter++;
            if (framecounter > 4) {
                framecounter = 0;
                balls += 10;
            }
        }
        if (IsKeyDown(KEY_V)) {
            framecounter++;
            if (framecounter > 4) {
                framecounter = 0;
                balls -= 10;
            }
        }
        //speed += 0.0001;
        stub = GetScreenHeight()/2;
        
        if ( balls < 1000) {
            balls += 1;

        }
        //speed += 0.0002;
        if (IsKeyPressed(KEY_E)) {
            if (colnum < 6) {
                colnum++;
            } else {
                colnum = 1;
            }
        }

        switch(colnum) {
            case 1:
                col = BLUE;
                break;
            case 2:
                col = RED;
                break;
            case 3:
                col = GREEN;
                break;

            case 4:
                col = PINK;
                break;
            default:
                col = WHITE;
        }
        rota +=speed;
        nowspeed += 0.008;
        speed = sin(nowspeed)*0.04;
        
        BeginDrawing();
            //speed=GetMouseX()*0.0001;

            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color(ColorAlpha(BLACK, 0.25)));            
            DrawFPS(10, 200);
            DrawText(TextFormat("Balls: %d\nSpeed: %f \nRotation: %f \nSpeedChange: %f", balls, speed, rota, sin(nowspeed)), 10, 20, 25, WHITE);
            
            

            DrawCircle(200+speed*1500, 200, 15, WHITE);
            DrawLine(100, 200, 300, 200, WHITE);

            for (int i = 0; i<balls; i++) {
                DrawCircle(GetScreenWidth()/2+sin(rota-i)*stub, GetScreenHeight()/2+cos(rota+i)*stub, 100*cos(rota+i), ColorAlpha(col, i/100));
            }
        EndDrawing();
        /* code */
    }
    CloseWindow();
    return 0;
}   
