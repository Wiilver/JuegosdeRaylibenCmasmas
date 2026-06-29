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

        bool checarColision(Coor &ban, const int RAD){
            if((pos.x>ban.x-RAD)&&(pos.x<ban.x+RAD)&&(pos.y>ban.y-RAD)&&(pos.y<ban.y+RAD)) return true;
            return false;
        }

        void aumentarPuntuacion(){
            puntuacion++;
        }
};

struct Bandera : public Entidad{
    private:
        void generarComponente(int &comp, int rango){
            int rnd = GetRandomValue(0,2);
            switch(rnd){
                case 0:
                    comp = GetRandomValue(rad, rango-rad);
                    rnd = GetRandomValue(0,2);
                    break;
                case 1:
                    comp = GetRandomValue(comp-rad, rango*2-rad);
                    break;
                case 2:
                    comp = GetRandomValue(rango*2-rad, rango*3-rad);
                    break;
            }
        }
    public:
        void iniciarBandera(){
            pos.x = 0;
            pos.y = 0;
            rad = 35;
            color = RED;
        }

        void generarPosicion(Coor &dim){
            int rnd, x, y, ant;

            x = dim.x/3;
            y = dim.y/3;

            generarComponente(pos.x, x);            
            generarComponente(pos.y, y);            
        }

};

void dibujarEntidades(Jugador &jug, Bandera &ban, Color fondo){
    BeginDrawing();
    ClearBackground(fondo);
    DrawText(TextFormat("Puntuacion : %i", jug.puntuacion),40, 40, 30, BLACK);
    jug.dibujar();
    ban.dibujar();
    EndDrawing();
}

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
        if(jugador.checarColision(bandera.pos, bandera.rad)) {
            bandera.generarPosicion(dimensiones);
            jugador.aumentarPuntuacion();
        }

        //Dibujar
        dibujarEntidades(jugador, bandera, FONDO);
    }

    CloseWindow();

    return 0;
}