#include <math.h>
#include <raylib.h>
#include <stdio.h>

class Movement {
    private:
    public:
    bool life = false;
    float posx = 5;
    float posy = 5;
    float posz = 5;
    float maxAccel = 5;
    float xSpeed = 0;
    float ySpeed = 0;
    float zSpeed = 0;
    float Accel = 0;
    float rotation = 0;

    float uprotation = 0;

    float sideAccel = 0;

    float gravity = 8;
    bool is_on_floor= false; 

    void spawn(float startx, float starty, float startz) {
        posx = startx;
        posy = starty;
        posz = startz;

        life = true;
    }

    void physics(float frametime) {

        if (posy < 11) {
            posy = 11;
            is_on_floor = true;
        } else {
            ySpeed -= gravity*frametime;
            is_on_floor = false;
        }

        xSpeed += Accel*frametime*sin(rotation);
        zSpeed += Accel*frametime*cos(rotation);

        xSpeed -= sideAccel*frametime*cos(-rotation);
        zSpeed -= sideAccel*frametime*sin(-rotation);

        //printf("On floor: %b\n", is_on_floor);

        //ySpeed += Accel*frametime*sin(udprotation);

        posx+=xSpeed;
        posz+=zSpeed;
        posy+=ySpeed;
        
        if (is_on_floor) {
            xSpeed *= 0.9;
            zSpeed *= 0.9;
        } else {
            xSpeed *= 0.95;
            zSpeed *= 0.95;
        }
        
    }

    void update(float frametime) {
        mouseControls(frametime);
        physics(frametime);
        
    }

    void mouseControls(float frametime) {
        //3.8;
        //2.7;
        if (is_on_floor) {

            if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
                if (fabs(sideAccel) < maxAccel/2) {
                    sideAccel -= 0.5;
                }
            } 
            if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) {
                if (fabs(sideAccel) < maxAccel/2) {
                    sideAccel += 0.5;
                }
            }

            if (IsKeyDown(KEY_W)) {
                if (fabs(Accel) < maxAccel) {
                    Accel += 0.5;
                }
            } 

            if (IsKeyDown(KEY_S)) {
                if (fabs(Accel) < maxAccel) {
                    Accel -= 0.5;
                }
            } 
            if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
                Accel = 0;
            }
            
            if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
                sideAccel = 0;
            }
            
            if (IsKeyDown(KEY_SPACE)) {
                if (is_on_floor) {
                    ySpeed = 4;
                }
            }

            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                maxAccel = 60;
            } else {
                maxAccel = 35;
            }
        }


        rotation = -(float)GetMouseX()/350;
        uprotation = (float)GetMouseY()/350;
        //SetMousePosition();

        //790 max Y
        if (GetMouseY() < 790) {
            SetMousePosition(GetMouseX(), 790);
        }
        

        if (GetMouseY() > 1317) {
            SetMousePosition(GetMouseX(), 1317);
        }

        if (uprotation < 2.27f) {
            uprotation = 2.27f;
        }
        if (uprotation > 3.8f) {
            uprotation = 3.8f;
        }

    }

    Vector3 getPos() {
            return (Vector3){posx, posy, posz};
    }

    void controls(float frametime) {
        if (IsKeyDown(KEY_A)) {
            rotation += 1*frametime;
        }

        if (IsKeyDown(KEY_D)) {
            rotation -= 1*frametime;
        }

        if (IsKeyDown(KEY_W)) {
            Accel += 0.2;
        } 

        if (IsKeyDown(KEY_S)) {
            Accel -= 0.2;
        } 
        if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
            Accel = 0;
        }

        if (IsKeyDown(KEY_E)) {
            uprotation += 1*frametime;
        }

        if (IsKeyDown(KEY_Q)) {
            uprotation -= 1*frametime;
        }
    }

};



class Enemy {
    private:
    bool life = false;
    float posx = 5;
    float posy = 5;
    float posz = 5;
    float maxAccel = 5;
    float xSpeed = 0;
    float ySpeed = 0;
    float zSpeed = 0;
    float Accel = 0;
    float rotation = 0;
    
    void physics(float frametime) {
        //printf("On floor: %b\n", is_on_floor);
        //ySpeed += Accel*frametime*sin(udprotation);
        posx+=xSpeed*frametime;
        posz+=zSpeed*frametime;
        posy+=ySpeed*frametime;
    }

    

    void think(float frametime, Vector3 targetPosition) {
        if (posx < targetPosition.x) {
            if (xSpeed < 0) {
                xSpeed = 0;
            }
            xSpeed+= 1;
        } else {
            if (xSpeed > 0) {
                xSpeed = 0;
            }
            xSpeed-= 1;

        }

        if (posz < targetPosition.z) {
            if (zSpeed < 0) {
                zSpeed = 0;
            }
            zSpeed+= 1;
        } else {
            if (zSpeed > 0) {
                zSpeed = 0;
            }
            zSpeed-= 1;

        }

    }
    public:

    void spawn() {
        life = true;
    }


    void update(float frametime, Vector3 targetPosition) {
        if (life) {
            physics(frametime);
            think(frametime, targetPosition);
        }
    }

    Vector3 getPos() {
            return (Vector3){posx, posy, posz};
    }

};