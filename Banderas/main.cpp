#include "raylib.h"

int main(){
     const int ANCHO = 800;
    const int ALTO  = 800;
    InitWindow(ALTO, ANCHO, "Mi juego");
    SetTargetFPS(60);

    const Color FONDO = {138, 199, 159, 1};

    bool arr, aba, izq, der;
    arr = aba = izq = der = false;
    
    const int RAD = 30;
    const int VEL = 50;
    
    int posx, posy;
    posx = posy = 400;

    while(!WindowShouldClose()){
        //Manejar

        arr = (IsKeyDown(KEY_UP)   ||IsKeyDown(KEY_W));
        aba = (IsKeyDown(KEY_DOWN) ||IsKeyDown(KEY_S));
        izq = (IsKeyDown(KEY_LEFT) ||IsKeyDown(KEY_A));
        der = (IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D));
        
        //Actualizar
        if(arr){
            if(posy > VEL) posy -= VEL;  
            else posy = RAD;
        }
        if(aba){
            if(posy < (ALTO - VEL)) posy += VEL;  
            else posy = ALTO - RAD;
        }
        if(izq){
            if(posx > RAD) posx -= VEL;  
            else posx=RAD;
        }
        if(der){
            if(posx < (ANCHO - RAD)) posx += VEL;  
            else posx = ANCHO - RAD;
        }

        //Dibujar
        BeginDrawing();
        ClearBackground(FONDO);
        DrawCircle(posx, posy, RAD, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}