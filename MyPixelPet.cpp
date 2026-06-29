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

//Dibujamos la cabecera decorativa del juego con el titulo.
void dibujarTitulo()
{
    cout << "  +----------------------------------------------+\n";
    cout << "  |        **  M Y   P I X E L   P E T  **       |\n";
    cout << "  |      Simulador de mascota virtual            |\n";
    cout << "  +----------------------------------------------+\n";
}
//En esta parte mostramos un mensaje de advertencia si la estadistica esta debajo de 20%
// de lo contrario, devuelve una cadena vacia
string obtenerAdvertencia(int valor, int idx)
{
    if (valor >= UMBRAL_ADVERTENCIA) return ""; // sin peligro: no muestra nada

    // Mensaje personalizado segun que estadistica esta en peligro
    if (idx == 0) return " <-- Advertencia: Mucha Hambre!"; // aca es por si el hambre esta abaja y la mascota necesita comer
    if (idx == 1) return " <-- Advertencia: Muy Cansado!"; // aca es por si la mascota esta cansada, necesita dormir
    if (idx == 2) return " <-- Advertencia: Muy Sucio!"; // aca la mascota necesita un baño
    if (idx == 3) return " <-- Advertencia: Muy Triste!"; // aca la mascota necesita jugar para no estar triste
    return "";
}
// Recorta cada estadistica para que no salga del rango valido [0, 100].
// Usa if-else (requisito del enunciado, no usa min/max de libreria).
void truncarEstadisticas(Mascota& m)
{
    for (int i = 0; i < TOTAL_ESTADISTICAS; i++) {
        if      (m.estadisticas[i] > LIMITE_MAXIMO) m.estadisticas[i] = LIMITE_MAXIMO; // compara las estadisticas para que no se pase del maximo 
        else if (m.estadisticas[i] < LIMITE_MINIMO) m.estadisticas[i] = LIMITE_MINIMO;// compara las estadisticas para que no se pasen del minimo
    }
}
// Aca se pondra lo que sucede cuando el jugador decide utilizar alguna opcion, algunas estadisticas bajaran y otras subiran
void aplicarAccion(Mascota& m, int opcion)
{
    switch (opcion) {
        case 1: // Dar comida: sube Alimentacion y Felicidad, baja Higiene
            m.estadisticas[0] += 35;  // Alimentacion: +35
            m.estadisticas[3] += 10;  // Felicidad:    +10
            m.estadisticas[2] -= 10;  // Higiene:      -10
            break;
        case 2: // Bañar: sube Higiene y Energia, baja Felicidad y Alimentacion
            m.estadisticas[2] += 100; // Higiene:      +100
            m.estadisticas[1] += 15;  // Energia:      +15
            m.estadisticas[3] -= 10;  // Felicidad:    -10
            m.estadisticas[0] -= 20;  // Alimentacion: -20
            break;
        case 3: // Dormir: sube Energia y Felicidad, baja Higiene y Alimentacion
            m.estadisticas[1] += 100; // Energia:      +100
            m.estadisticas[3] += 35;  // Felicidad:    +35
            m.estadisticas[2] -= 15;  // Higiene:      -15
            m.estadisticas[0] -= 35;  // Alimentacion: -35
            break;
        case 4: // Jugar: sube Felicidad pero baja mucho Higiene y Energia
            m.estadisticas[3] += 100; // Felicidad:    +100
            m.estadisticas[2] -= 50;  // Higiene:      -50
            m.estadisticas[1] -= 50;  // Energia:      -50
            break;
    }
    // Despues de modificar, asegura que ningun valor quede fuera de [0, 100], con la funcion que hcimos anteriormente
    truncarEstadisticas(m);
}

// Verifica si la accion indicada sigue en cooldown de 60 segundos.
// Escribe en segsRestantes cuantos segundos faltan para que se libere.
// Devuelve true si esta bloqueada, false si ya puede usarse.
bool accionEnCooldown(const Mascota& m, int idx, int& segsRestantes)
{
    // Calcula cuantos segundos han pasado desde el ultimo uso de esta accion
    double transcurrido = difftime(time(0), m.ultimaAccion[idx]);

    if (transcurrido < SEGUNDOS_COOLDOWN) {
        // La accion todavia esta en cooldown se calcula el tiempo restante
        segsRestantes = SEGUNDOS_COOLDOWN - (int)transcurrido;
        return true; // bloqueada
    }
    segsRestantes = 0;
    return false; // disponible
}

// Recorre las 4 estadisticas y devuelve el indice de la primera que llego a 0%.
// Si ninguna llego a 0%, devuelve -1 (todo esta bien).
int indiceEstadisticaCritica(const Mascota& m)
{
    for (int i = 0; i < TOTAL_ESTADISTICAS; i++) {
        if (m.estadisticas[i] <= LIMITE_MINIMO) {
            return i; // esta estadistica esta en 0%: es critica
        }
    }
    return -1; // ninguna estadistica en 0% (todo bien)
}
