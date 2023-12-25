#include <raylib.h>
#include <math.h>
#include <iostream>

class Projectile {
    float xpos = 0;
    float ypos = 0;
    float zpos = 0;

    float xSpeed = 0;
    float ySpeed = 0;
    float zSpeed = 0;
    bool live = false;
    

    public:
        void shoot(float upwords_angle, float rotation, Vector3 startpoint) {
            live = true;
            xpos = startpoint.x;
            ypos = startpoint.y;
            zpos = startpoint.z;


            xSpeed = sin(rotation)*1000;
            ySpeed = sin(upwords_angle)*1000;
            zSpeed = cos(rotation)*1000;

    

        }
        void update(float frametime) {
            if (live) {
                xpos+=xSpeed*frametime;
                ypos+=ySpeed*frametime;
                zpos+=zSpeed*frametime;

            } else {
                xpos = 0;
                ypos = 0;
                zpos = 0;
            }
            

            if (fabs(xpos) > 10000 || fabs(ypos) > 10000 || fabs(zpos) > 10000) {
                live = false;
                //std::clog << "I despawned\n" << "--X: " << xpos << " --Y: " << ypos << "\n";
            }
        }

        bool am_live() {
            if (live) {
                return true;
            } else {
                return false;
            }
        }
        Vector3 get_pos() {
            return (Vector3){xpos, ypos, zpos};
        }
};