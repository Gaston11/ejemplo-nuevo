#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    struct  alumno
            {
                string ape;
                int numeropadron;
            };

    alumno vector[20];
    string linea;
    ifstream archivo("apellidospadron.txt");
    string apellido, cadenaaux;
    int padron,posespacio;
    int i=0;
    while (getline(archivo,linea))
    {

        posespacio =linea.find(" "); // busca posicion vacio

        apellido =linea.substr(0,posespacio); // crea subcadena desde 0 hasta posespacio
        cadenaaux =linea.substr(posespacio+1);

        padron= atoi(cadenaaux.c_str()); //convierte la cadena a valor numerico

        vector[i].ape= apellido;
        vector[i].numeropadron= padron;
        i++;
        //cout << apellido << endl;
        //cout << padron << endl;
    }

    cout << vector[3].ape << endl;
    cout << vector[7].numeropadron << endl;

    return 0;
}
