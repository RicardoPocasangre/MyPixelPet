#include <iostream>  //cout, cin  -> entrada y salida en consola
#include <fstream>   //ifstream, ofstream -> leer y escribir archivos
#include <string>    //string, getline, to_string -> manejo de texto
#include <ctime>     //time(), time_t, difftime() -> cooldowns y temporizador
#include <cstdlib>   //system("cls") -> limpiar la pantalla
#include <windows.h> //SetConsoleOutputCP, Sleep -> consola Windows

using namespace std;
const int TOTAL_ESTADISTICAS = 4;
const int TOTAL_ESPECIES = 4;
const int MAX_PARTIDAS = 5;
const int VALOR_INICIAL = 50;
const int LIMITE_MAXIMO = 100;
const int LIMITE_MINIMO = 0;
const int SEGUNDOS_COOLDOWN = 60;
const int SEGUNDOS_RESCATE = 10;
const int UMBRAL_ADVERTENCIA = 20;
const int LARGO_BARRA = 10;
const int RETARDO_ANIMACION = 12;

struct Mascota {
    string nombre;
    int indiceEspecie;
    int estadisticas[TOTAL_ESTADISTICAS];
    time_t ultimaAccion[TOTAL_ESTADISTICAS];
};

int main (){

    
    return 0;
}

//Pausa el programa la cantidad de milisegundos indicada.
//Usa Sleep() de <windows.h> (no necesita <thread>) => programacion en multihilos.
void pausar(int ms)
{
    Sleep(ms);
}

//Limpieza de la consola usando el comando del sistema operativo.
//"cls" funciona en las terminales de windows (cmd y PowerShell).
void limpiarPantalla()
{
    system("cls");
}