#include <iostream>
#include "funciones.h"
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;
void mayuscula(string &sector)
{
    for (int i=0; i< sector.length(); i++ )
        {
            sector[i]= toupper(sector[i]); //pasa a mayuscula
                                            //tolower pasa a minusculas
        }
}

void estaocupado( int col,  matriz mat)
{
    int i=0;
    while ( i<maximo )
    {
        if (i != col )
        {   mat[i][col].ocupado= true;
        }
     i++;
    }
}

void estadisponible(int col, matriz mat)
{
    int i=0;
    while (i<maximo )
    {
        if (i != col)
        {
            mat[i][col].ocupado= false;
        }
     i++;
    }
}

void cargarposicion(matriz mat, string iniciofin, int fil, int col, int tiempo)
{
    if (iniciofin == "Inicio")
    {

        if (mat[fil][col].ocupado == true )
        {
            mat[fil][col].cantocupado = mat[fil][col].cantocupado + 1;
        }
        else
        {

            mat[fil][col].cantllamadas = mat[fil][col].cantllamadas + 1;
            estaocupado(col,mat);

            mat[fil][col].inicio = tiempo;

        }
    }
    else
    {
        if (mat[fil][col].ocupado == true)
        {
            mat[fil][col].tiempototal = mat[fil][col].tiempototal + tiempo - mat[fil][col].inicio;
            estadisponible(col,mat);
        }
    }
}

void inicializarmatriz(matriz mat)
{
    for(int i=0; i<maximo ; i++ )
    {
        for(int j=0; j<maximo; j++)
        {
           if (i != j)
           {    mat[i][j].ocupado= false;
                mat[i][j].cantllamadas= 0;
                mat[i][j].cantocupado=0;
                mat[i][j].inicio=0;
                mat[i][j].fin=0;
                mat[i][j].tiempototal= 0;
           }
        }
    }
}

void buscarposicion(string sectores[maximo], string sector, int &pos)
{
    bool encontrado= false;
    int p=0;
    while (encontrado ==false && p<maximo)
    {
        if (sector== sectores[p])
        {
            encontrado=true;
        }
        p++;
    }
    if (encontrado==true)
    {
        pos=p-1;
    }
}

void nuevosector(string sectores[maximo], string sector, int &posicion )
{
    posicion=0;
    while( (sectores[posicion]!= sector) && (sectores[posicion]!= " ") && (posicion<maximo) )
    {
        posicion++;
    }
    if (sectores[posicion] == " ")
    {
        sectores[posicion]= sector;
    }
}

void parseo(string datos, string &iniciofin, string &sector1, string &sector2, int &tiempo)
{
    string cadenaaux,tiempostring;
    int posespacio =datos.find(" "); // busca posicion vacio
    iniciofin =datos.substr(0,posespacio); // crea subcadena desde 0 hasta posespacio
    cadenaaux =datos.substr(posespacio+1);

    posespacio=cadenaaux.find(" ");
    sector1=cadenaaux.substr(0,posespacio);
    cadenaaux=cadenaaux.substr(posespacio+1);

    posespacio=cadenaaux.find(" ");
    sector2=cadenaaux.substr(0,posespacio);
    cadenaaux=cadenaaux.substr(posespacio+1);
    tiempostring=cadenaaux;
    tiempo= atoi(tiempostring.c_str()); //convierte la cadena a valor numerico
}

void cargararchivo()
 {
    string datos, iniciofin,sector1,sector2;
    int tiempo;
    matriz mat;

    string sectores[maximo];
    for(int f=0; f<maximo ; f++) //inicializo sectores en vacio
    {
        sectores[f]=" ";
    }

    inicializarmatriz(mat);

    ifstream salida("pruebatp.txt");
    getline(salida,datos);
    parseo(datos,iniciofin, sector1, sector2, tiempo);
    sectores[0]=sector1;
    sectores[1]=sector2;

    int posicion1=0, posicion2=1;
    cargarposicion( mat,iniciofin,posicion1, posicion2,tiempo);

    while (getline(salida,datos))
    {
        parseo(datos,iniciofin, sector1, sector2, tiempo);
        nuevosector(sectores,sector1, posicion1);
        nuevosector(sectores,sector2, posicion2);
        cargarposicion( mat, iniciofin, posicion1, posicion2, tiempo);
    }

    cout << "Archivos cargados..."<< endl;

    int opcion;
    menu( opcion);
    while (opcion !=0)
    {
        system("cls");
        opcionelegida(opcion, mat);
        menu(opcion);
    }
    cout <<endl;
    imprimematriz( mat);
    salida.close();
}

void opcion1(matriz mat, int internoX, int internoY)
{
    cout << "Detalles de llamadas del interno: " << internoX << "al interno: " << internoY << endl;
    cout << "Cantidad de llamadas:" << mat[internoX][internoY].cantllamadas << endl;
    cout << "Cantidad de tiempo hablado: " << mat[internoX][internoY].tiempototal << endl;
    cout << "Cantidad de veces ocupado: " << mat[internoX][internoY].cantocupado << endl;

    int total=0;
    for (int i=0; i<maximo ; i++)
    {
        if (i!= internoX)
        {
            total = total + mat[i][internoX].cantocupado;
        }
    }
    cout << "Cantidad de veces ocupado que el interno " << internoX << "estuvo para los demas internos: "<< total << endl;
}

void opcion2(matriz mat, int &interno)
{
    int max=0, aux;
    for (int j=0; j< maximo ; j++)
    {
        for (int k=0; k<maximo ;k++)
        {
            aux=0;
            if (j!=k)
                aux= aux + mat[j][k].tiempototal;
        }
        if (aux > max)
        {
            max = aux;
            interno = j;
        }
    }
}

void opcion3(matriz mat, int &interno)
{
    int max=0, aux;
    for (int j=0; j< maximo ; j++)
    {
        for (int k=0; k<maximo ;k++)
        {
            aux=0;
            if (j!=k)
                aux= aux + mat[j][k].cantllamadas;
        }
        if (aux > max)
        {
            max = aux;
            interno = j;
        }
    }
}

void opcion5(matriz mat, int &interno)
{
    int max=0, aux;
    for (int j=0; j< maximo ; j++)
    {
        for (int k=0; k<maximo ;k++)
        {
            aux=0;
            if (j!=k)
                aux= aux + mat[k][j].cantllamadas;
        }
        if (aux > max)
        {
            max = aux;
            interno = j;
        }
    }
}

void opcion6(matriz mat, int &interno)
{
    int max=0, aux;
    for (int j=0; j< maximo ; j++)
    {
        for (int k=0; k<maximo ;k++)
        {
            aux=0;
            if (j!=k)
                aux= aux + mat[k][j].tiempototal;
        }
        if (aux > max)
        {
            max = aux;
            interno = j;
        }
    }
}

void opcion7(matriz mat, int &interno)
{
    int max=0, aux;
    for (int j=0; j< maximo ; j++)
    {
        for (int k=0; k<maximo ;k++)
        {
            aux=0;
            if (j!=k)
                aux= aux + mat[k][j].cantocupado;
        }
        if (aux > max)
        {
            max= aux;
            interno = j;
        }
    }
}

void opcion8 (matriz mat, int interno)
{
    int totaldellamadas=0, totalocupados=0, tiempototalhablado=0;
    for (int j=0; j<maximo ; j++)
    {
        if (j!= interno)
        {
            totaldellamadas= totaldellamadas + mat[interno][j].cantllamadas;
            totalocupados= totalocupados + mat[interno][j].cantocupado;
            tiempototalhablado= tiempototalhablado + mat[interno][j].tiempototal;
        }
    }
    cout << " Detalles del interno:" << interno << endl;
    cout << "Total de llamadas: " << totaldellamadas<< endl;
    cout << "Total cantidad de ocupados: " << totalocupados<< endl;
    cout << "Tiempo total hablado: " << tiempototalhablado << endl;
}

void opcion9(matriz mat, int interno)
{
    int totaldellamadas=0, totalocupados=0, tiempototalhablado=0;
    for (int j=0; j<maximo ; j++)
    {
        if (j!= interno)
        {
            totaldellamadas= totaldellamadas + mat[j][interno].cantllamadas;
            totalocupados= totalocupados + mat[j][interno].cantocupado;
            tiempototalhablado= tiempototalhablado + mat[j][interno].tiempototal;
        }
    }
    cout << " Detalles del interno:" << interno << endl;
    cout << "Total de llamadas recibidas: " << totaldellamadas<< endl;
    cout << "Total cantidad de ocupados recibidos: " << totalocupados<< endl;
    cout << "Tiempo total hablado: " << tiempototalhablado << endl;
}
void opcionelegida(int opcion, matriz mat)
{
    int internoX, internoY;
    switch (opcion)
    {
        case 1 :   cout << "Ingrese interno x:";
                   cin >> internoX;
                   cout <<endl;
                   cout << "Ingrese interno y:" ;
                   cin>> internoY;
                   cout<<endl;
                   opcion1(mat, internoX,internoY);
                   break;
        case 2 :   opcion2(mat, internoX);
                   cout << "El interno que mas hablo: "<< internoX << endl;
                   break;
        case 3 :   opcion3( mat, internoX);
                   cout << "El interno que mas llamo: " << internoX << endl;
                   break;
        case 5 :   opcion5(mat, internoX);
                   cout << "El interno al que mas llamaron: " << internoX<< endl;
                   break;
        case 6 :   opcion6(mat, internoX);
                   cout << "El interno al que mas le hablaron: " << internoX<< endl;
                   break;
        case 7 :   opcion7(mat, internoX);
                   cout << "El interno al que mas dio ocupado: " << internoX<< endl;
                   break;
        case 8 :   cout << "Ingrese interno x:";
                   cin >> internoX;
                   opcion8(mat, internoX);
                   break;
        case 9 :   cout << "Ingrese interno x:";
                   cin >> internoX;
                   opcion9(mat, internoX);
                   break;
        default :cout <<"opcion no valida"<< endl;
    }

}

void menu(int &opcion)
{
    cout << endl;
    cout << "---OPCIONES---"<< endl;
    cout<< "1: detalles de llamadas del interno x al interno y. "<< endl;
    cout<< "2: interno que mas hablo." << endl;
    cout<< "3: interno que mas llamo." << endl;
    cout<< "5: interno al que mas llamaron."<< endl;
    cout<< "6: interno al que mas le hablaron."<< endl;
    cout<< "7: interno que mas dio ocupado."<< endl;
    cout<< "8: detalles de llamadas emitidas por el interno x."<< endl;
    cout<< "9: detalles de llamadas recibidas por el interno x."<< endl;
    cout <<"0: salir." << endl;

    cout<< "ingrese opcion: " ;
    cin>> opcion ;

}

void imprimematriz(matriz mat)
{
    for (int j=0; j<maximo ; j++)
    {
        for (int k=0; k<maximo ; k++)
        {
            if (j!=k)
            {
                //cout << mat[j]k].ocupado <<endl;
                //cout <<"Cant de llamadas: "<< mat[j][k].cantllamadas << " en la pos "<< j<<" "<< k << endl;
                //cout << "Cant de ocupados: "<<  mat[j][k].cantocupado << " en la pos "<< j<<" "<< k << endl;
                //cout << mat[j][k].inicio << endl;
                //cout << mat[j][k].fin << endl;
                cout << "Tiempo total hablado: "<< mat[j][k].tiempototal << " en la pos "<< j<<" "<< k << endl;
            }
        }
    }
}
