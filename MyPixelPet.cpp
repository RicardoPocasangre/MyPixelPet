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

//Dibujamos el arte de los animales ocupando ASCII
//0 = Gato   1 = Perro   2 = Conejo   3 = Pajaro
void dibujarAnimal(int idx)
{
    if (idx == 0) { // Gato
        cout << "          /\\_____/\\\n";
        cout << "         /  o   o  \\\n";
        cout << "        ( ==  ^  == )\n";
        cout << "         )  (*)   (\n";
        cout << "        (  _____  )\n";
        cout << "       / \\(     )/ \\\n";
        cout << "      (   )     (   )\n";
    } else if (idx == 1) { // Perro
        cout << "          _____\n";
        cout << "        /|  o  o|\\\n";
        cout << "       / |  --- | \\\n";
        cout << "      /  |_______|  \\\n";
        cout << "     / //         \\\\ \\\n";
        cout << "    (  ||  [ __ ]  ||  )\n";
        cout << "     \\_||___|__|___||_/\n";
    } else if (idx == 2) { // Conejo
        cout << "       |\\     /|\n";
        cout << "       | \\   / |\n";
        cout << "       |  \\_/  |\n";
        cout << "      /  o   o  \\\n";
        cout << "     ( ==  w  == )\n";
        cout << "      \\   ___   /\n";
        cout << "      (_)     (_)\n";
    } else { // Pajaro (idx == 3)
        cout << "          ___\n";
        cout << "         /. .\\\n";
        cout << "        / \\_/ \\\n";
        cout << "       /  ---  \\\n";
        cout << "      ( |     | )\n";
        cout << "      |  \\___/  |\n";
        cout << "     /___________\\\n";
    }
}

//Impresion del dibujo del game over
void dibujarGameOverArt()
{
    cout << "\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |                                              |\n";
    cout << "  |          ###  GAME  OVER  ###                |\n";
    cout << "  |                                              |\n";
    cout << "  |    x_x   Tu mascota no sobrevivio...  x_x   |\n";
    cout << "  |   (   )  La proxima cuidala mejor!   (   )  |\n";
    cout << "  |    | |                                 | |   |\n";
    cout << "  +----------------------------------------------+\n";
}

/* ------------------------------------------------------------
 *  MENUS DE NAVEGACION
 * ------------------------------------------------------------ */

// Muestra el menu principal y devuelve la opcion elegida (1, 2 o 3).
// Valida que la entrada este en el rango correcto antes de devolver.
int menuPrincipal()
{
    limpiarPantalla();
    dibujarTitulo(); // cabecera del juego

    cout << "\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |              MENU PRINCIPAL                  |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |                                              |\n";
    cout << "  |   1.  Nueva Partida                         |\n";
    cout << "  |   2.  Cargar Partida                        |\n";
    cout << "  |   3.  Salir                                 |\n";
    cout << "  |                                              |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "\n  Selecciona una opcion (1-3): ";

    // Lee la opcion y la valida: debe ser 1, 2 o 3
    int op = leerEntero();
    while (op < 1 || op > 3) {
        cout << "  Opcion no valida. Elige 1, 2 o 3: ";
        op = leerEntero();
    }
    return op;  
}

// Lee y valida la especie seleccionada por el jugador.
// Devuelve el indice de la especie en base 0.
int seleccionarEspecie(const string especies[])
{
    int opcion = leerEntero();
    while (opcion < 1 || opcion > TOTAL_ESPECIES) {
        cout << "  Opcion no valida. Elige un numero entre 1 y "
             << TOTAL_ESPECIES << ": ";
        opcion = leerEntero();
    }
    return opcion - 1;
}

// Lee el nombre de la mascota. No permite cadenas vacias.
string pedirNombre()
{
    string nombre;
    getline(cin, nombre);
    while (nombre.empty()) {
        cout << "  El nombre no puede estar vacio. Ingresa un nombre: ";
        getline(cin, nombre);
    }
    return nombre;
}

// Inicializa todas las estadisticas al valor inicial y deja los cooldowns disponibles.
void inicializarEstadisticas(Mascota& m)
{
    for (int i = 0; i < TOTAL_ESTADISTICAS; i++) {
        m.estadisticas[i] = VALOR_INICIAL;
        m.ultimaAccion[i] = 0; // 0 significa que la accion esta disponible inmediatamente
    }
}

// Muestra todos los slots con la informacion de cada partida guardada.
// Deja elegir uno para cargarlo.
// Devuelve true si se cargo una partida, false si no habia o el usuario cancelo.
bool menuCargarPartida(Mascota& m, const string especies[])
{
    limpiarPantalla();
    dibujarTitulo();

    cout << "\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |              CARGAR PARTIDA                  |\n";
    cout << "  +----------------------------------------------+\n";

    int slotsDisponibles = 0; // contador de slots que tienen partida guardada

    // Recorre todos los slots del 1 al MAX_PARTIDAS y muestra su contenido
    for (int s = 1; s <= MAX_PARTIDAS; s++) {
        Mascota tmp; // struct temporal para leer los datos sin afectar la mascota actual
        cout << "  |\n";
        if (cargarSlot(s, tmp)) {
            // El slot tiene datos: muestra el resumen de la partida
            slotsDisponibles++;
            cout << "  |  Slot [" << s << "] >> " << tmp.nombre
                 << "  (" << especies[tmp.indiceEspecie] << ")\n";
            cout << "  |          Alim: "  << tmp.estadisticas[0]
                 << "%  Ener: "            << tmp.estadisticas[1]
                 << "%  Hig: "             << tmp.estadisticas[2]
                 << "%  Felic: "           << tmp.estadisticas[3] << "%\n";
        } else {
            // El slot esta vacio: lo muestra como disponible
            cout << "  |  Slot [" << s << "] -- vacio --\n";
        }
    }

    cout << "  |\n";
    cout << "  |  0.  Volver al menu principal\n";
    cout << "  |\n";
    cout << "  +----------------------------------------------+\n";

    // Si no hay ninguna partida guardada, informa y regresa al menu principal
    if (slotsDisponibles == 0) {
        cout << "\n  No hay partidas guardadas. Crea una nueva.\n";
        esperarEnter();
        return false; // no se cargo nada
    }

    // Pide al jugador que elija el numero de slot
    cout << "\n  Selecciona el slot a cargar (0 = volver): ";
    int slot = leerEntero();

    // Valida que el slot elegido exista, tenga datos y no sea 0
    while (slot != 0 && (slot < 1 || slot > MAX_PARTIDAS || !slotTienePartida(slot))) {
        cout << "  Slot no valido o vacio. Elige otro (0 = volver): ";
        slot = leerEntero();
    }

    if (slot == 0) return false; // el jugador decidio volver sin cargar

    // Carga los datos del slot elegido en la mascota
    cargarSlot(slot, m);

    // Muestra una confirmacion visual de la carga
    limpiarPantalla();
    dibujarTitulo();
    cout << "\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |         PARTIDA CARGADA CON EXITO            |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |  Nombre  : " << m.nombre << "\n";
    cout << "  |  Especie : " << especies[m.indiceEspecie] << "\n";
    cout << "  |  Alim: "    << m.estadisticas[0]
         << "%  Ener: "      << m.estadisticas[1]
         << "%  Hig: "       << m.estadisticas[2]
         << "%  Felic: "     << m.estadisticas[3] << "%\n";
    cout << "  +----------------------------------------------+\n\n";
    dibujarAnimal(m.indiceEspecie); // muestra el animalito de la especie cargada
    cout << "\n  Bienvenido de vuelta, " << m.nombre << "!\n";
    esperarEnter();
    return true; // partida cargada correctamente
}

// Configura una nueva mascota: pide la especie y el nombre,
// luego inicializa todas las estadisticas al 50%.
void menuNuevaPartida(Mascota& m, const string especies[])
{
    limpiarPantalla();
    dibujarTitulo();

    // Muestra el menu de seleccion de especie
    cout << "\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |              NUEVA PARTIDA                   |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |  Elige la especie de tu mascota:             |\n";
    cout << "  |                                              |\n";
    cout << "  |   1.  Gato                                  |\n";
    cout << "  |   2.  Perro                                 |\n";
    cout << "  |   3.  Conejo                                |\n";
    cout << "  |   4.  Pajaro                                |\n";
    cout << "  |                                              |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "\n  Opcion (1-4): ";

    // Lee y valida la especie; guarda el indice base-0 en la mascota
    m.indiceEspecie = seleccionarEspecie(especies);

    // Vista previa: muestra el animal que eligio antes de pedir el nombre
    limpiarPantalla();
    dibujarTitulo();
    cout << "\n  Tu " << especies[m.indiceEspecie] << ":\n\n";
    dibujarAnimal(m.indiceEspecie);
    cout << "\n  Ponle un nombre a tu " << especies[m.indiceEspecie] << ": ";

    // Lee el nombre (no permite cadenas vacias)
    m.nombre = pedirNombre();

    // Pone todas las estadisticas al 50% y los cooldowns disponibles
    inicializarEstadisticas(m);

    // Muestra confirmacion de la mascota creada
    limpiarPantalla();
    dibujarTitulo();
    cout << "\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |         MASCOTA CREADA CON EXITO!            |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |  Nombre  : " << m.nombre << "\n";
    cout << "  |  Especie : " << especies[m.indiceEspecie] << "\n";
    cout << "  |  Stats   : todas al 50%\n";
    cout << "  +----------------------------------------------+\n\n";
    dibujarAnimal(m.indiceEspecie); // muestra el animalito de la especie elegida
    cout << "\n  Cuida bien a " << m.nombre << "!\n";
    esperarEnter();
}


/* ------------------------------------------------------------
 *  INICIALIZACION DE DATOS
 * ------------------------------------------------------------ */

// Llena el arreglo de especies con los nombres disponibles.
// Requisito del enunciado: arreglo de strings para las especies.
void inicializarEspecies(string especies[])
{
    especies[0] = "Gato";
    especies[1] = "Perro";
    especies[2] = "Conejo";
    especies[3] = "Pajaro";
}

// Pone todas las estadisticas al valor inicial (50%) y
// resetea los cooldowns a 0 (epoch) para que todas las acciones
// esten disponibles desde el primer turno.
void inicializarEstadisticas(Mascota& m)
{
    for (int i = 0; i < TOTAL_ESTADISTICAS; i++) {
        m.estadisticas[i] = VALOR_INICIAL; // 50%
        m.ultimaAccion[i] = 0;             // cooldown: disponible desde el inicio
    }
}

// Muestra las especies numeradas y devuelve el indice base-0 de la elegida.
// Valida que la opcion este en el rango 1-TOTAL_ESPECIES antes de devolver.
int seleccionarEspecie(const string /*especies*/[])
{
    int sel = 0;
    do {
        sel = leerEntero(); // lee la opcion del jugador
        if (sel < 1 || sel > TOTAL_ESPECIES)
            cout << "  Opcion invalida (1-" << TOTAL_ESPECIES << "): ";
    } while (sel < 1 || sel > TOTAL_ESPECIES);
    return sel - 1; // convierte opcion(1-4) a indice(0-3)
}

// Pide el nombre de la mascota usando getline (permite nombres con espacios).
// Repite hasta que el jugador escriba algo (no permite nombre vacio).
string pedirNombre()
{
    string nombre;
    do {
        getline(cin, nombre); // getline lee toda la linea incluyendo espacios
    } while (nombre.empty());
    return nombre;
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
// aca se muestran algunas sugerencias para el jugador si alguna estadistica esta baja
string nombreAccionRecomendada(int idx)
{
    // digamos si alimentacion esta baja se mostrara, Dar comida, ya asi con todas las estadisticas
    if (idx == 0) return "Dar comida (opcion 1)"; // Alimentacion -> Dar comida
    if (idx == 1) return "Dormir     (opcion 3)"; // Energia      -> Dormir
    if (idx == 2) return "Bañar      (opcion 2)"; // Higiene      -> Bañar
    if (idx == 3) return "Jugar      (opcion 4)"; // Felicidad    -> Jugar
    return "una accion";
}

bool gestionarRescate(Mascota& m, int indiceCritico)
{
    // Arreglo local con los nombres de las estadisticas (para el mensaje de alerta)
    string nombresEstadistica[TOTAL_ESTADISTICAS] = {
        "Alimentacion", "Energia", "Higiene", "Felicidad"
    };

    // Muestra la pantalla de alerta critica
    limpiarPantalla();
    cout << "\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |       !! ALERTA CRITICA - EMERGENCIA !!      |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |\n";
    cout << "  |  '" << nombresEstadistica[indiceCritico]
         << "' de " << m.nombre << " llego a 0%!\n";
    cout << "  |\n";
    cout << "  |  Tienes " << SEGUNDOS_RESCATE
         << " SEGUNDOS para reaccionar o\n";
    cout << "  |  " << m.nombre << " no sobrevivira...\n";
    cout << "  |\n";
    cout << "  |  Accion recomendada:\n";
    cout << "  |    >> " << nombreAccionRecomendada(indiceCritico) << "\n";
    cout << "  |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |  1.Comida   2.Banar   3.Dormir   4.Jugar    |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "\n  Opcion de rescate: ";

    time_t inicio = time(0);      // marca de tiempo ANTES de esperar al jugador
    int    opcion = leerEntero(); // lectura bloqueante: espera al jugador
    double tReacc = difftime(time(0), inicio); // tiempo que tardo en responder

    // 1) Verifica que respondio dentro de los 10 segundos permitidos
    if (tReacc > SEGUNDOS_RESCATE) {
        cout << "\n  Tardaste " << (int)tReacc << " seg. Demasiado lento!\n";
        return false; // tiempo agotado: la mascota muere (Game over)
    }

    // 2) Valida que la opcion sea una de las 4 acciones del juego
    if (opcion < 1 || opcion > 4) {
        cout << "\n  Opcion invalida durante la emergencia.\n";
        return false; // opcion invalida: la mascota muere (Game over)
    }

    // Aplica la accion elegida (el cooldown se ignora en el rescate: es una emergencia)
    aplicarAccion(m, opcion);

    // 3) Verifica si la estadistica critica se recupero por encima de 0%
    if (m.estadisticas[indiceCritico] > LIMITE_MINIMO) {
        cout << "\n  Reaccionaste a tiempo! " << m.nombre << " se ha salvado.\n";
        return true; // rescate exitoso: la mascota sobrevivio (yeiii)
    }

    // La accion elegida no fue suficiente para recuperar la estadistica critica
    cout << "\n  Esa accion no recupero la estadistica critica.\n";
    return false; // rescate fallido: la mascota muere (Game over :c)
}

void mostrarGameOver(const Mascota& m, const string especies[])
{
    limpiarPantalla(); // se limpia la pantalla
    dibujarGameOverArt(); // se muestra arte ASCII de Game Over
    cout << "\n  " << m.nombre << " (" << especies[m.indiceEspecie]
         << ") no logro sobrevivir...\n";// se muestra un mensaje al jugador y una recomendacion
    cout << "  La proxima vez manten todas las estadisticas sobre 0%.\n\n";
    esperarEnter();
}

//GRACIA... 
//Declaracion de cada archivo.
// -- Persistencia (archivos slot1.txt ... slot5.txt) --
string nombreArchivo(int slot);          // devuelve "slot1.txt", "slot2.txt"(compartimentos donde se guardan las partidas, tambien puedes guardarse varias de diferente juego) 
bool   slotTienePartida(int slot);       // true si el archivo del slot existe y tiene datos
int    contarPartidas();                 // cuenta cuantos slots estan ocupados
bool   cargarSlot(int slot, Mascota& m); // lee el archivo y carga el estado en la mascota
void   guardarSlot(int slot, const Mascota& m); // escribe el estado en el archivo del slot
void   borrarSlot(int slot);             // elimina el archivo del slot (se usa al morir)

// Devuelve el nombre del archivo según el slot (ej: "slot1.txt")
string nombreArchivo(int slot) {
    return "slot" + to_string(slot) + ".txt";
}

// Verifica si el archivo del slot(compartimento) existe y tiene contenido 
bool slotTienePartida(int slot) {
    ifstream f(nombreArchivo(slot));
    return f.is_open() && f.peek() != EOF; // peek es para leerel siguiente caracter sin avanzar la lectura, y el EOF es para indicar que el archivo se termino o que esta vacio.
}

// Cuenta cuántos slots tienen una partida que esta activa. 
int contarPartidas() {
    int count = 0;
    for (int s = 1; s <= MAX_PARTIDAS; s++) {
        if (slotTienePartida(s)) count++;
    }
    return count;
} // bucle simple que recorre todos los slots permitidos (del 1 al 5) y pregunta a slotTienePartida(s) si hay algo guardado. Si la respuesta es true, suma 1 al contador.

// Carga los datos de la mascota desde el archivo al struct
bool cargarSlot(int slot, Mascota& m) {
    ifstream archivo(nombreArchivo(slot));
    if (!archivo.is_open()) return false;

    if (!getline(archivo, m.nombre) || m.nombre.empty()) { archivo.close(); return false; }
    if (!(archivo >> m.indiceEspecie))                   { archivo.close(); return false; }
    for (int i = 0; i < TOTAL_ESTADISTICAS; i++) {
        if (!(archivo >> m.estadisticas[i]))             { archivo.close(); return false; }
    }
    archivo.close();
    return true;
} //restaurador de estado. Toma la información de el archivo de disco y la mueve al struct Mascota).

//Este congela los datos. Toma el estado actual del struct Mascota y lo escribe de forma permanente en el disco.
// Guarda el estado de la mascota en el archivo correspondiente
void guardarSlot(int slot, const Mascota& m) {
    ofstream archivo(nombreArchivo(slot));
    if (archivo.is_open()) {
        archivo << m.nombre << "\n" << m.indiceEspecie << "\n";
        for (int i = 0; i < TOTAL_ESTADISTICAS; i++) {
            archivo << m.estadisticas[i] << "\n";
        }
        archivo.close();
    }
}

//elimina el archivo de la carpeta. En especial cuado se a perdido la partida y muere la mascota.
void borrarSlot(int slot) {
    remove(nombreArchivo(slot).c_str());
}