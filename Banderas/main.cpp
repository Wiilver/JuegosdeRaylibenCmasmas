#include "raylib.h"

struct Coor{
    int x;
    int y;
};

struct Direcciones{
    bool arr = false;
    bool aba = false;
    bool izq = false;
    bool der = false;
};

class Entidad{
    public:
        Coor pos;
        Color color;

        int rad;

        void dibujar(){
            DrawCircle(pos.x, pos.y, rad, color);
        }
};

class Jugador : public Entidad{
    public:
        Direcciones dir;
        
        int vel = 10;
        int puntuacion = 0;

        void iniciarJugador(Coor &dim){
            pos.x = dim.x/2;
            pos.y = dim.y/2;
            rad = 30;
            color = WHITE;
        }

        void detectarDirecciones(){
            dir.arr = (IsKeyDown(KEY_W)||IsKeyDown(KEY_UP));
            dir.izq = (IsKeyDown(KEY_A)||IsKeyDown(KEY_LEFT));
            dir.aba = (IsKeyDown(KEY_S)||IsKeyDown(KEY_DOWN));
            dir.der = (IsKeyDown(KEY_D)||IsKeyDown(KEY_RIGHT));
        }

        void cambiarPosicion(Coor &dim){
            if((dir.arr)&&(pos.y>rad)) pos.y-=vel;
            if((dir.izq)&&(pos.x>rad)) pos.x-=vel;
            if((dir.aba)&&(pos.y<dim.y-rad)) pos.y+=vel;
            if((dir.der)&&(pos.x<dim.x-rad)) pos.x+=vel;
        }
};

struct Bandera : public Entidad{
    void iniciarBandera(){
        pos.x = 0;
        pos.y = 0;
        rad = 35;
        color = RED;
    }

    void generarPosicion(Coor &dim){
        pos.x = GetRandomValue(int(dim.x/4), dim.x-rad);
        pos.y = GetRandomValue(int(dim.y/4), dim.y-rad);

        int rnd = GetRandomValue(0,3);

        switch(rnd){
            case 0:
                return;
            case 1:
                pos.x*=-1;
                return;
            case 2:
                pos.y*=-1;
                pos.x*=-1;
                return;
            case 3:
                pos.y*=-1;
                return;
        }
    }

};

int main(){
    Coor dimensiones;
    dimensiones.y = 800;
    dimensiones.x = 800;

    const Color FONDO = {138, 199, 159, 1};
    
    Jugador jugador;
    Bandera bandera;

    jugador.iniciarJugador(dimensiones);
    bandera.iniciarBandera();

    bandera.generarPosicion(dimensiones);

    InitWindow(dimensiones.y, dimensiones.x, "Mi juego");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        //Manejar

        jugador.detectarDirecciones();

        //Actualizar
        jugador.cambiarPosicion(dimensiones);

        //Dibujar
        BeginDrawing();
        ClearBackground(FONDO);
        jugador.dibujar();
        bandera.dibujar();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}