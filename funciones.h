#include <iostream>
#include <string>
#include <fstream>

using namespace std;
typedef struct{bool ocupado; int cantllamadas; int cantocupado; int tiempototal; int inicio; int fin;} info;
const int maximo=10;
typedef info matriz[maximo][maximo];

void estadisponible(int col, matriz mat);
void estaocupado( int col, matriz mat);
void cargarposicion(matriz mat, string iniciofin, int posicion1, int posicion2, int tiempo);
void inicializarmatriz(matriz mat);
void parseo(string datos, string &iniciofin, string &sector1, string &sector2, int &tiempo); // parseo ok
void cargararchivo(); // principal
void opcion1(matriz mat, int internoX, int internoY);
void opcion2(matriz mat, int &interno);
void opcion3(matriz mat, int &interno);
void opcion5(matriz mat, int &interno);
void opcion6(matriz mat, int &interno);
void opcion7(matriz mat, int &interno);
void opcion8 (matriz mat, int interno);
void opcion9(matriz mat, int interno);
void nuevosector(string sectores[maximo], string sector, int &posicion);
void buscarposicion(string sectores[maximo], string sector, int &pos);
void opcionelegida(int opcion,matriz mat);
void menu(int &opcion);
void imprimematriz(matriz mat);
void mayuscula(string &sector);

