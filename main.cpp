#include <iostream>
#include "raylib.h"
#include <math.h>

class posi {
    public:
    float yPos = 10;
    float xPos = 200;
    float ySpeed = 0;
    float xSpeed = 0;
    float accel;
    float rotation = 0;
    float Acceleration = 2;
    float framtime;
    float recposx, recposy = 0;
    bool gas;
    int radius = 40;
    int framecounter = 0;

    void infiniteBorder() {
        if (xPos > GetScreenWidth()) {
            xPos = 1;
        }
        if (yPos > GetScreenHeight()) {
            yPos = 1;
        }

        if (xPos < 0) {
            xPos = GetScreenWidth();
        }
        if (yPos < 0) {
            yPos = GetScreenHeight();
        }
    }


    void rendergoal() {
        DrawRectangle(recposx, recposy, 20, 20, WHITE);
    }


    void bounceBorder() {
        if (xPos > GetScreenWidth()+radius) {
            xPos = GetScreenWidth()-1+radius;
            xSpeed *= -0.8;
            xSpeed--;
        }
        if (yPos > GetScreenHeight()+radius) {
            yPos = GetScreenHeight()-1+radius;
            ySpeed *= -0.8;
            ySpeed--;
        }

        if (xPos < 0) {
            xPos = 1;
            xSpeed *= -0.8;
        }
        if (yPos < 0) {
            yPos = 1;
            ySpeed *= -0.8;
        }
    }

    void update() {
        float framtime = GetFrameTime();
        framecounter+=1;
        
        xPos += xSpeed*framtime*60;
        yPos += ySpeed*framtime*60;

        xSpeed*= 0.98;
        ySpeed*= 0.98;
    }

    void controls() {
        if (IsKeyDown(KEY_W)) {
            ySpeed-=Acceleration;
        }
        if (IsKeyDown(KEY_S)) {
            ySpeed+=Acceleration;
        }
        if (IsKeyDown(KEY_A)) {
            xSpeed-=Acceleration;
        }
        if (IsKeyDown(KEY_D)) {
            xSpeed+=Acceleration;
        }

        if (IsKeyReleased(KEY_UP)) {
            Acceleration+=0.1;
        }

        if (IsKeyReleased(KEY_DOWN)) {
            if (Acceleration > 0) {
                Acceleration-=0.1;  
            }
        }

    }
    void turnControls() {
        framtime = GetFrameTime()*60;

        if (IsKeyDown(KEY_W)) {
            gas = true;
            ySpeed-=sin(rotation)*Acceleration*framtime;
            xSpeed-=cos(rotation)*Acceleration*framtime;
        } else {
            gas = false;
        }
        if (IsKeyDown(KEY_S)) {
            ySpeed+=sin(rotation)*Acceleration*framtime;
            xSpeed+=cos(rotation)*Acceleration*framtime;
        }
        if (IsKeyDown(KEY_A)) {
            rotation -= 0.1*framtime;
        }
        if (IsKeyDown(KEY_D)) {
            rotation += 0.1*framtime;
        }

        if (IsKeyReleased(KEY_UP)) {
            Acceleration+=0.5*framtime;
        }

        if (IsKeyReleased(KEY_DOWN)) {
            if (Acceleration > 0) {
                Acceleration-=0.5;  
            }
        }

        if (IsKeyPressed(KEY_E)) {
            radius += 1.5;
        }
        if (IsKeyPressed(KEY_Q)) {
            radius -= 1.5;
        }
    }
};

posi pos;

int tposx = GetRandomValue(10, 20)*3;
int tposy = GetRandomValue(10, 20)*3;


int main() {
    InitWindow(1920, 1200, "Sliding");
    SetWindowState(FLAG_VSYNC_HINT);
    //SetTargetFPS(120);
    ToggleFullscreen();
    std::clog << "Hello\n";
    DisableCursor();

    while (!WindowShouldClose())
    {
        /* code */
        BeginDrawing();
            DrawFPS(10, 10);
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color(ColorAlpha(BLACK, 0.2)));

            DrawCircle(pos.xPos, pos.yPos, pos.radius+10, WHITE);
            if (pos.gas) {
                DrawCircle(pos.xPos+sin(pos.rotation)*pos.radius, pos.yPos+cos(pos.rotation)*pos. radius, pos.radius, RED);
            } else {
                DrawCircle(pos.xPos+sin(pos.rotation)*pos.radius, pos.yPos+cos(pos.rotation)*pos.radius, pos.radius, WHITE);
            }

            DrawCircle(tposx, tposy, 20, WHITE);

            pos.update();
            //pos.infiniteBorder();
            pos.bounceBorder();
            pos.turnControls();


        EndDrawing();
    }
    
    return 0;
}