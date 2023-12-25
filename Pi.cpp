#include <raylib.h>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <format>
#include <string>
#include <iostream>

float posx = 700;
float posy = 550;
float rota = 2;
float radius = 0;
float bigrad = 600;
float cirle_thing = 0;
float dispo = 0;
float dispob = 0;
float offset = 0;
float offsetb  = 0;
float speed = 63/60;
double frametime = 0;
bool play = true;
float mousestoppos = 0;

float lastrota = 0;

int main() {
    SetWindowState(FLAG_VSYNC_HINT);
    //SetTargetFPS(120);
    //SetWindowState(FLAG_MSAA_4X_HINT);
    InitWindow(1920, 1200, "PI");
    ToggleFullscreen();
    posx = GetScreenHeight()/2;
    posx = GetScreenWidth()/2;
    cirle_thing = GetScreenHeight()/5;
    //SetTargetFPS(120);
    while(!WindowShouldClose()) {
        frametime = GetFrameTime();

        if (IsKeyDown(KEY_E)) {
            speed += 0.10;
        }

        if (IsKeyDown(KEY_Q)) {
            speed -= 0.10;
        }


        //radius control
        if (IsKeyDown(KEY_W)) {
            bigrad += 0.50;
        }

        if (IsKeyDown(KEY_S)) {
            bigrad -= 0.50;
        }


        if (IsKeyDown(KEY_RIGHT)) {
            rota += speed*0.01;
        }

        if (IsKeyDown(KEY_LEFT)) {
            rota -= speed*0.01;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            if (play) {
                play = false;
                lastrota = rota;

            } else {
                mousestoppos = rota+GetMouseX()*0.01;
                play = true;
            }
        }

        if (play) {
            rota += frametime*speed;
        }

        if (IsKeyPressed(KEY_V)) {
            SetTargetFPS(30);
        }
        if (IsKeyPressed(KEY_B)) {
            SetTargetFPS(50);
        }
        if (IsKeyPressed(KEY_N)) {
            SetTargetFPS(60);
        }
        if (IsKeyPressed(KEY_C)) {
            SetTargetFPS(10);
        }
        

        //bigrad += 0.1;
        BeginDrawing();
            //ClearBackground(BLACK);
            DrawFPS(20, 20);
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color(ColorAlpha(BLACK, 0.55*frametime*60)));
            //DrawCircle(posx+200*sin(rota), posy+200*cos(rota), radius, RAYWHITE);
            //DrawCircle(20, 200-speed*10, 10, WHITE);

            DrawLine(500, 0, 500+speed*10, 50, WHITE);

            for (float i= 0; i < 10; i++) {//draw balls
                dispo = bigrad+50;
                //dispo = bigrad+i*50;
                offset = rota-i*0.1*rota;

                //Draw
                if (i > 0) {
                    //std::cout << rota << "\n\n";

                    DrawLine(
                    posx+dispo*sin(offset), posy+dispo*cos(offset),
                    posx+dispo*sin(offset)/2, posy+dispo*cos(offset)/2,
                    ColorAlpha(BLUE, 0.5-sin(offset)) );
            
                    DrawLine(
                    posx, posy,
                    posx+dispo*sin(offset)/2, posy+dispo*cos(offset)/2,
                    ColorAlpha(RED, 0.5+sin(offset)) );
                    dispob = dispo;
                    offsetb = offset;
                } else {
                    dispob = dispo;
                    offsetb = offset;
                }
                

            }
            
            for (int i= 0; i < 10; i++) {//draw balls
                //dispo = bigrad+i*50;
                dispo = bigrad+50;
                offset = rota-i*0.1*rota;
                DrawCircle(posx+dispo*sin(offset), posy+dispo*cos(offset), radius, RAYWHITE);

                //Draw
            }

            //DrawCircle(posx+cirle_thing*sin(rota)+100*sin(rota*PI), posy+cirle_thing*cos(rota)+100*cos(rota*PI), radius, RAYWHITE);
            //DrawCircle(posx+cirle_thing*sin(rota)+100*sin(rota*PI), posy+cirle_thing*cos(rota)+100*cos(rota*PI), radius, RAYWHITE);
            //DrawLine(posx+cirle_thing*sin(rota), posy+cirle_thing*cos(rota), posx+10*sin(rota)+cirle_thing*sin(rota*PI), posy+10*cos(rota)+cirle_thing*cos(rota*PI), RAYWHITE);
        EndDrawing();
    }
    return 0;
}