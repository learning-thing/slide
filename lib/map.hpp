#include <raylib.h>


class DefaultMap {
    public:
    void draw() {
        DrawCubeV((Vector3){-100, -1, -100},(Vector3){200, 2, 200}, GRAY);
        DrawCubeWiresV((Vector3){-100, -1, -100},(Vector3){200, 2, 200}, BLACK);
    }

};