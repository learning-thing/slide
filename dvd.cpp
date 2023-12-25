#include <raylib.h>


float posx = 1;
float posy = 1;
float xSpeed = 20;
float ySpeed = 20;
float frametime;

float win_width;
float win_height;

void updatePhysics() {
    frametime = GetFrameTime()*60;
    posx += xSpeed*frametime;
    posy += ySpeed*frametime;

    win_width = GetScreenWidth();
    win_height = GetScreenHeight();

    if (posx < GetScreenWidth()/2) {
        xSpeed+=5;
    } else {
        xSpeed-=5;
    }


    if(IsKeyDown(KEY_A)) {
        posx= 10;
        posy = 10;
        xSpeed += 100;
    }

    if (posx > win_width) {
        posx = win_width;
        xSpeed *= -0.9;
    }
    if (posx < 0) {
        posx = 0;
        xSpeed *= -0.9; 
        } 
    if (posy > win_height) {
        posy = win_height;
        ySpeed *= -0.8;
        }


    if (posy < 0) {
        posy = 0;
        ySpeed *= -0.8;

    }
    if (xSpeed<0) {
        xSpeed += 0.05;
    }
    else {
        xSpeed -= 0.05;
     }
    ySpeed += 1;
}



int main() {
    InitWindow(1900, 1080, "DVD");
    ToggleFullscreen();
    SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    //SetTargetFPS(60);
    win_width = GetScreenWidth();
    win_height = GetScreenHeight();
    while(true) {
        updatePhysics();
        BeginDrawing();
            DrawRectangle(0, 0, win_width, win_height, ColorAlpha(BLACK, 0.4));
            DrawFPS(20, 20);
            //ClearBackground(BLACK);
            DrawText("Dunya", posx, posy-80, 100, RAYWHITE);
            DrawCircle(10, GetScreenHeight()/2+((xSpeed+ySpeed)/2), 10, RAYWHITE);
            DrawText("Ace", GetScreenWidth()-posx, posy-80, 100, RAYWHITE);
        EndDrawing();
    }
    return 0;
}