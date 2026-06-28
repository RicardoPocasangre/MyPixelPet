#include <iostream>  //cout, cin  -> entrada y salida en consola
#include <fstream>   //ifstream, ofstream -> leer y escribir archivos
#include <string>    //string, getline, to_string -> manejo de texto
#include <ctime>     //time(), time_t, difftime() -> cooldowns y temporizador
#include <cstdlib>   //system("cls") -> limpiar la pantalla
#include <windows.h> //SetConsoleOutputCP, Sleep -> consola Windows

using namespace std;

//Variables constantes que nunca van a cambiar en su contexto
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

//Declaracion de variables

//funcion leerEntero
int valor; 

//funcion esperarEnter
string basura; //variable temporal para absorber lo que quede en el buffer(la memoria temporal) lo podemos ver como una sala de espera

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

//Lee el numero entero que ingresa el usuario y lo valida de entrada
//Si el usuario escribe letras o simbolos, limpia el error y lo vuelve a pedir.
//Si la entrada se agota (EOF) *solo en casos especiales que el usuario presione una combinacion de teclas especiales*
//Y da la indicacion de cerrar el programa o darle fin, devuelve 5 (= "Guardar y salir") para salir limpio.
int leerEntero()
{
    //Inicia un bucle infinito hasta que el usuario ingrese un valor valido
    while(true) {
        if(cin >> valor) //Se lee lo que el usuario ingreso para validar que si es un valor entero
        {
            cin.ignore(10000, '\n'); //si la lectura fue correcta, se limpia la memora temporal y ignora los siguientes 10000 caracteres o hasta encontrar un salto de linea "\n"
            return valor;
        }
        //si llegamos aqui es por que el usuario ingreso un valor invalido(hola, abc, etc) osea que encontramos el error en la capa 8
        if (cin.eof()) return 5; //si el usuario manda la señal de fin del archivo el programa devuelve el valor 5 para guardar y salir
        cin.clear(); //limpia la entrada que esta con un error
        cin.ignore(10000, '\n'); // aqui reiniciamos el cin para dejar el canal completamente limpio y que el usuario pueda ocupar la entrada nuevamente
        cout << "Entrada no valida. Ingrese un numero: "; //mostramos el mensaje en que se equivoco para que lo vuelva ingresar y lo haga correctamente
    }
}

//Pausa el programa hasta que el jugador presione ENTER.
//Se usa despues de mostrar resultados para que el jugador pueda leerlos.
void esperarEnter()
{
    cout << "\n  Presione ENTER para continuar..."; //nos aseguramos de que el mensaje no quede pegado en el texto anterior de la consola
    getline(cin, basura); //Leemos toda la linea de texto hasta cuando el usuario presiona la tecla enter, y se guarde en la variable basura
}