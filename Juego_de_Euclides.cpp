/*
Proyecto: Juego de Euclides
Alumnos: Sebastián Landaeta, Gipsy Anaya, Antonietta Palazzo y Valery Medina
Ingeniería Informática
Técnicas de programación II
Sección 1
*/

/*Inclusión de las librerías a utilizar*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include <windows.h>

/*Declaración de macros*/
#define FILAS 8
#define COLUMNAS 8
#define NUMEROS FILAS*COLUMNAS

/*Declaración de la estructura "Jugador", la cual contendrá los datos de cada jugador*/
struct Jugador 
{
    char nombre[30]; /*Nombre del jugador*/
    int puntos; /*Puntos del jugador*/
    int fallos; /*Fallos del jugador*/
};

/*Prototipos de las funciones definidas en el código*/
void menu(); /*Esta función se encarga de mostrar el menú del juego, para que los usuarios puedan interactuar con las opciones disponibles*/
void titulo(); /*Esta función contiene la interfaz del menú*/
void juego(); /*En esta función se encuentra toda la lógica del juego, y por ende es la más grande de todas*/
void m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual); /*Esta función identifica y muestra en pantalla quién será el primer jugador*/
void meter_numero(int tabla[FILAS][COLUMNAS], int n_actual, int &p_fila_actual, int &p_columna_actual); /*Esta función se encarga de meter los números y las x's en la matriz de forma ordenada*/
void imprimir(int tabla[FILAS][COLUMNAS]); /*Esta función se encarga de imprimir en pantalla la interfaz de juego*/
void color(int n); /*Esta función la usamos para pintar las casillas de la tabla*/

using namespace std;

int main() /*Función principal*/
{
	setlocale(LC_CTYPE, "Spanish");
    SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	menu();
	
	return 0;
}

void menu() /*Función menú*/
{
    int menu = 0;
    char opcion;

    do
    {
        titulo();
        
        cin >> opcion;
        fflush(stdin);

        switch (opcion)
        {
            case '1': // Comenzar juego
				juego();
				break;

			/*case '2': // Cargar juego
				system("cls");
                cout << "2" << endl << endl;
                system("pause");
				break;

			case '3': // Acerca del juego
				system("cls");
                cout << "3" << endl << endl;
                system("pause");
				break;
                
			case '4': // Ayuda
				system("cls");
                cout << "4" << endl << endl;
                system("pause");
				break;

			case '0': // Terminar el programa
				system("cls");
                cout <<"\n\t\t\t\t\t  = Gracias por Jugar <(* U *)/ =\n\n";
                menu = 1;
			    break;

            default:
                system("cls");
                cout <<"\n\t\t\t\t     -Opcion Incorrecta - Intente Nuevamente-\n\n";
                system("pause");
                system("cls");*/
        }

        system("cls");
    } while (menu == 0);
}

void titulo() /*Función título*/
{
    cout <<"       ___________________________________________________________________________________________\n\n\n";
	cout <<"\t    # #   # ####  ####   ###     ####  ####    #### #   #  ###  #    ### ####  ####  ###   "<<endl;
	cout <<"\t    # #   # #    #   ## #   #    #   # #       #    #   # #   # #     #  #   # #    #   #  "<<endl;
	cout <<"\t    # #   # #    #      #   #    #   # #       #    #   # #     #     #  #   # #    #       "<<endl;
	cout <<"\t    # #   # ###  #  ### #   #    #   # ###     ###  #   # #     #     #  #   # ###   ###   "<<endl;
	cout <<"\t#   # #   # #    #   #  #   #    #   # #       #    #   # #     #     #  #   # #        #  "<<endl;
	cout <<"\t#   # #   # #    #   #  #   #    #   # #       #    #   # #   # #     #  #   # #    #   #  "<<endl;
	cout <<"\t ###   ###  ####  ###    ###     ####  ####    ####  ###   ###  #### ### ####  ####  ###   "<<endl<<endl<<endl;
	
	cout <<"\t\t\t\t\t     1. Comenzar Juego\n\n\n";
	cout <<"\t\t\t\t\t     2. Cargar Juego\n\n\n";
	cout <<"\t\t\t\t\t     3. Acerca del Juego\n\n\n";
	cout <<"\t\t\t\t\t     4. Ayuda\n\n\n";
	cout <<"\t\t\t\t\t     0. Salir del juego\n\n";
	
	cout <<"       ___________________________________________________________________________________________\n";
    cout << "\n       Opcion (número) --> "; 
}

void juego() /*Función juego*/
{
    srand(time(0)); /*Semilla para el randomizer*/

    system("cls");

    Jugador jb, ja;
    int tabla[FILAS][COLUMNAS]; /*Tabla que contendrá todo*/
    int n_actual, n_nuevo;
    /*Aquí irá en Do While para que se pueda empezar otra partida*/

    /*Aquí se piden los nombres de los jugadores*/
    cout << "Inserte el nombre del jugador blanco: ";
    cin >> jb.nombre;
    cout << "\nInserte el nombre del jugador azul: ";
    cin >> ja.nombre;
    
    system("cls");
    
    /*Se inicializa la tabla*/
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            tabla[i][j] = 0;
        }
    }

    /*Se generan los dos números aleatorios*/
    n_actual = 1+(rand()%NUMEROS);
    n_nuevo = 1+(rand()%NUMEROS); 
    
    do /*Esta parte es para evitar que los números se repitan*/
    {
        if (n_actual == n_nuevo)
        {
            n_nuevo = 1+(rand()%NUMEROS);
        }
    } while (n_actual == n_nuevo);
    
    /*Se genera la posición del primer número*/
    int p_fila_actual = rand()%FILAS, p_columna_actual = rand()%COLUMNAS;
    
    /*Se meter el primer número en la tabla*/
    tabla[p_fila_actual][p_columna_actual] = n_actual;
    
    /*Se muestra quien es el primer jugador a partir de la posición del primer número*/
    m_primer_jugador(jb, ja, p_fila_actual, p_columna_actual);
    
    n_actual = n_nuevo; /*Ahora se meterá el segundo número en la tabla*/
    
    meter_numero(tabla, n_actual, p_fila_actual, p_columna_actual);
    imprimir(tabla); /*Se imprime la tabla con los espacios vacíos y los dos números*/
}

void m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual) /*Función m_primer_jugador*/
{
    if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 == 0)) //Si la fila es par y la columna es par
    {
        cout << jb.nombre << " Será el primer jugador." << endl;
        system("pause");
        return;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 != 0))  //Si la fila es impar y la columna es impar
    {
        cout << jb.nombre << " Será el primer jugador." << endl;
        system("pause");
        return;
    }

    if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 != 0)) //Si la fila es par y la columna es impar
    {
        cout << ja.nombre << " Será el primer jugador." << endl;
        system("pause");
        return;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 == 0)) //Si la fila es impar y la columna es par
    {
        cout << ja.nombre << " Será el primer jugador." << endl;
        system("pause");
        return;
    }
}

void meter_numero(int tabla[FILAS][COLUMNAS], int n_actual, int &p_fila_actual, int &p_columna_actual) /*Función meter_numeros*/
{
    if ((p_fila_actual % 2 == 0) && (p_columna_actual < COLUMNAS-1))
    {
        int p_fila_nuevo = p_fila_actual;
        int p_columna_nuevo = p_columna_actual+1;

        tabla[p_fila_nuevo][p_columna_nuevo] = n_actual;

        p_fila_actual = p_fila_nuevo;
        p_columna_actual = p_columna_nuevo;
        return;
    }

    if ((p_fila_actual % 2 == 0) && (p_fila_actual < FILAS-1) && (p_columna_actual == COLUMNAS-1))
    {
        int p_fila_nuevo = p_fila_actual+1;
        int p_columna_nuevo = COLUMNAS-1;

        tabla[p_fila_nuevo][p_columna_nuevo] = n_actual;

        p_fila_actual = p_fila_nuevo;
        p_columna_actual = p_columna_nuevo;
        return;
    }
    
    if ((p_fila_actual % 2 == 0) && (p_fila_actual == FILAS-1) && (p_columna_actual == COLUMNAS-1))
    {
        int p_fila_nuevo = 0;
        int p_columna_nuevo = 0;

        tabla[p_fila_nuevo][p_columna_nuevo] = n_actual;

        p_fila_actual = p_fila_nuevo;
        p_columna_actual = p_columna_nuevo;
        return;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual > 0))
    {
        int p_fila_nuevo = p_fila_actual;
        int p_columna_nuevo = p_columna_actual-1;

        tabla[p_fila_nuevo][p_columna_nuevo] = n_actual;

        p_fila_actual = p_fila_nuevo;
        p_columna_actual = p_columna_nuevo;
        return;
    }
    
    if ((p_fila_actual % 2 != 0) && (p_fila_actual < FILAS-1) && (p_columna_actual == 0))
    {
        int p_fila_nuevo = p_fila_actual+1;
        int p_columna_nuevo = 0;

        tabla[p_fila_nuevo][p_columna_nuevo] = n_actual;

        p_fila_actual = p_fila_nuevo;
        p_columna_actual = p_columna_nuevo;
        return;
    }
    
    if ((p_fila_actual % 2 != 0) && (p_fila_actual == FILAS-1) && (p_columna_actual == 0))
    {
        int p_fila_nuevo = 0;
        int p_columna_nuevo = 0;

        tabla[p_fila_nuevo][p_columna_nuevo] = n_actual;

        p_fila_actual = p_fila_nuevo;
        p_columna_actual = p_columna_nuevo;
        return;
    }
}

void imprimir(int tabla[FILAS][COLUMNAS]) /*Función imprimir*/
{
	system("cls");
    cout << "\n";

	for (int i = 0; i < FILAS; i++)
	{
		color(7);
		cout << " ";
		for (int j = 0; j < COLUMNAS; j++)
		{
			if (((i+1) + (j)) % 2 == 0)
				color(176);
            else
				color(240);
			if (tabla[i][j] < 10)
				cout << " 0" << tabla[i][j] << " ";
			else
				cout << " " << tabla[i][j] << " ";
			if (j == 8-1)
	        	cout << "\n" ;			
		}
	}

	color(7);
	cout << "\n\n";	
	system("pause");
}

void color(int n) /*Función color*/
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}