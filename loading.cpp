#include <iostream>
#include <raylib.h>
#include <math.h>
#include <string.h>
#include <format>

float rota = 0;
double speed = 0.04;
float stub = 0;
unsigned int  balls = 0;
unsigned framecounter = 0;
float nowspeed = 0;
int colnum = 1;
float red =10;
float green =10;
float blue =10;
bool built = false;

Color col = RED;

int main() {
    InitWindow(1920, 1200, "Loading..");
    SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    //SetTargetFPS(160);
    //ToggleFullscreen();
    speed = .01;


    while (true) {
        if (IsKeyDown(KEY_P)) {
            return 0;
            break;
        }

        if (IsKeyDown(KEY_UP)) {
            speed += 0.01;
        }
        if (IsKeyDown(KEY_DOWN)) {
            speed -= 0.01;
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
        
        if (IsKeyPressed(KEY_R)) {
            balls = 90;
            built = false;
        }

        //speed += 0.0002;
        if (IsKeyPressed(KEY_E)) {
            if (colnum < 6) {
                colnum++;
            } else {
                colnum = 1;
            }
        }

        if (balls < 490) {
            if (!built) {
                balls++;
            }
        } else {
            built = true;
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
        rota +=speed*GetFrameTime();
        
        BeginDrawing();
            //speed=GetMouseX()*0.0001;

            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color(ColorAlpha(BLACK, 0.15)));            
            DrawFPS(10, 200);
            DrawText(TextFormat("Balls: %d\nSpeed: %f \nRotation: %f \nSpeedChange: %f", balls, speed, rota, speed), 10, 20, 25, WHITE);
            
            

            DrawCircle(200+speed*15, 200, 15, WHITE);
            DrawLine(100, 200, 300, 200, WHITE);

            for (int i = 0; i<balls; i++) {
                DrawCircle(GetScreenWidth()/2+sin(rota-i)*stub, GetScreenHeight()/2+cos(rota+i)*stub, 10, ColorAlpha(col, i/100));
            }
        EndDrawing();
        /* code */
    }
    CloseWindow();
    return 0;
}   
