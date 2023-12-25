#include <raylib.h>


class ball {
    private:
    public:
        float xPos = 5, yPos = 5, xSpeed = 5, ySpeed = 5;
        unsigned int radius = 13;
        float frametime;
        void update() {
            frametime = GetFrameTime();
            xPos += xSpeed*frametime*60;
            yPos += ySpeed*frametime*60;

            if (yPos > GetScreenHeight()-radius) {
                yPos = GetScreenHeight()-radius;
                ySpeed *= -1;
            } 

            if ( yPos < 10) {
                yPos = 10;
                ySpeed *= -1;
            }

            
        }

        void bounceX() {
            if (xPos > 1060.0f) {
                xPos = 1060.0f;
                xSpeed *= -1.0f;
            }

            if (xPos < 20+radius) {
                xPos = 20+radius;
                xSpeed *= -1;
            }
        }
};

class bouncer {
    public:
    float  yPosa = 0;
    float  yPosb = 0;
    float frametime = GetFrameTime();

    void update() {
        frametime = GetFrameTime();
        if (IsKeyDown(KEY_S)) {
            yPosa += 10*frametime*60;
        }

        if (IsKeyDown(KEY_W)) {
            yPosa -= 10*frametime*60;
        }

        if (IsKeyDown(KEY_UP)) {
            yPosb -= 10*frametime*60;
        }


        if (IsKeyDown(KEY_DOWN)) {
            yPosb += 10*frametime*60;
        }
        
    }
};



int main() {
    InitWindow(1080, 720, "PONG");
    SetWindowState(FLAG_VSYNC_HINT);

    ball pong;
    bouncer pads;


    while(!WindowShouldClose()) {
        BeginDrawing();
            DrawFPS(30, 30);
            ClearBackground(BLACK);
            pong.update();
            pads.update();
            DrawCircle(pong.xPos, pong.yPos, pong.radius, WHITE);
            DrawRectangle(                 10, pads.yPosa, 10, 70, WHITE);
            DrawRectangle(1060, pads.yPosb, 10, 70, WHITE);

            if (pong.xPos < 100) {
                if (pads.yPosa > pong.yPos && pong.yPos < pads.yPosa+100) {
                    pong.bounceX();
                }
            }

            if (pong.xPos > 200) {
                if (pads.yPosb > pong.yPos && pong.yPos < pads.yPosb+100) {
                    pong.bounceX();
                }
            }

        EndDrawing();
    }

    return 0;
}