#include <raylib.h>
#include "lib/TFPSMovement.hpp"
#include <iostream>
#include "lib/map.hpp"
#include "lib/gun.hpp" 

float frametime;
bool thirdperson = false;
float cubesize = 1;
float totalSpeed = 0;
int shots = 0;
int maxbullets = 100;
// Camera projection type
int framecounter = 0;


float OriginDistance(Vector3 pos) {
    //Satz des pythagoras
    float A = fabs(pos.z);
    float B = fabs(pos.x);//X distance
    float C;
    if (A == 0 || B == 0) {
        return 0;
    } else {
        C = fabs(sqrt((B*B)+(A*A)));
    }
    return C;
}

int main() {
    InitWindow(1920, 1200, "Smooth fps movement");
    ToggleFullscreen();
    //SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);

    DisableCursor();

    Movement movement;
    Camera3D camera = { 0 };
    Projectile bullets[maxbullets];
    Texture2D bill = LoadTexture("../res/heart.png");
    Vector3 billUp = { 0.0f, 1.0f, 0.0f };
    Enemy HerrWiescher;
    Enemy KunstMann;

    KunstMann.spawn();

    camera.position = (Vector3){ 0.0f, 2.0f,  0.0f};    // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };      // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;    

    movement.spawn(25.0f, 5.0f, 5.0f);

    

    while (!WindowShouldClose()) {
        frametime = GetFrameTime();
        movement.update(frametime);
        KunstMann.update(frametime, movement.getPos());
        for (int i = 0; i < maxbullets; i++) {
            bullets[i].update(frametime);
        }
        //Misc controls
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            framecounter++;
            if (framecounter == 5) {
                bullets[shots].shoot(movement.uprotation, movement.rotation, (Vector3){movement.posx, movement.posy, movement.posz});
            }
            shots++;
            if (framecounter == 5) {
                framecounter = 0;
            }
        }

        if (IsKeyPressed(KEY_F)) {
            if (thirdperson) {
                thirdperson = false;
            } else {
                thirdperson = true;
            }
        }

        if (IsKeyDown(KEY_R)) {
            movement.posx = 0;
            movement.posz = 0;
        }

    

        totalSpeed = fabs(movement.xSpeed)+fabs(movement.zSpeed);
        //std::clog << "uprotation: " << movement.uprotation << "\n" << "\n\nMouse pos: " << GetMouseY();
        //std::clog << "Framecount: " << framecounter << "\n";
        BeginDrawing();
            DrawFPS(10, 10);
            BeginMode3D(camera);
            ClearBackground(BLACK);

                DrawGrid(100, 100);
                DrawCube(KunstMann.getPos(), 10, 50, 10, WHITE);


                //Draw enemies
                
                


                //Draw projecrtile and updat ebullets
                for (int i = 0; i < maxbullets; i++) {
                    bullets[i].update(frametime);
                    if (bullets[i].am_live()) {
                        DrawCubeV(bullets[i].get_pos(),(Vector3){1, 1, 1},WHITE);
                    }
                }
                if (shots > maxbullets-1) {
                    shots = 0;
                }

                if (thirdperson) {
                    camera.position = (Vector3){movement.posx-sin(movement.rotation)*20, 
                                            movement.posy-sin(movement.uprotation)*20, 
                                            movement.posz-cos(movement.rotation)*20 
                                            };      // Camera looking at point
                //DrawBillboard(camera, bill, billPositionStatic, 6.0f, WHITE);
                    camera.target = (Vector3){ movement.posx, movement.posy, movement.posz };
                    
                } else {
                    {
                    camera.position = (Vector3){ movement.posx, movement.posy, movement.posz };
                    camera.target = (Vector3){movement.posx+sin(movement.rotation)*20, 
                                            movement.posy+sin(movement.uprotation)*20, 
                                            movement.posz+cos(movement.rotation)*20 
                                            };      // Camera looking at point
                }
                }

                if (thirdperson) {
                    DrawCapsuleWires(camera.target, camera.target, 2, 5, 5, WHITE);
                } 
                //DrawCubeV(camera.target, (Vector3){ cubesize, cubesize, cubesize}, WHITE);
                


            EndMode3D();
            DrawText(TextFormat("X: %f \n\n\nY: %f\n\n\nxSpeed: %f\n\n\nzSpeed: %f\n\n\nTotalSpeed: %f", movement.posx, movement.posz, movement.xSpeed, movement.zSpeed, totalSpeed), 10, 30, 40, WHITE);
            if (!thirdperson) {
                DrawCircle(GetScreenWidth()/2,GetScreenHeight()/2,5, WHITE);
            }

            DrawLine(GetScreenWidth()/2, 100, GetScreenWidth()/2+sin(movement.rotation)*movement.xSpeed*10, 100+cos(movement.rotation)*totalSpeed, WHITE);
            //std::cout << "Player Distance from 0X: " << fabs(movement.posx) << "\n" << "\nTarget Distance from 0X: " << OriginDistance((Vector3){movement.posx, movement.posy, movement.posz}) << "\n";
            
            
            

        EndDrawing();
    }
    return 0;
}