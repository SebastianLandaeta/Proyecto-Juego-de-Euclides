
/*	Proyecto: Juego de Euclides
	Alumnos: Sebasti�n Landaeta, Gipsy Anaya, Antonietta Palazzo y Valery Medina
	Ingenier�a Inform�tica
	T�cnicas de programaci�n II
	Secci�n 1
*/

// == LIBRERIAS ==
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include <windows.h>

// == CONSTANTES ==
#define FILAS 8
#define COLUMNAS 8
#define NUMEROS FILAS*COLUMNAS
#define X -1

// == ESTRUCTURAS ==

// Datos de cada jugador
struct Jugador 
{
    char nombre[30];   // Nombre del jugador
    int puntos;        // Puntos del jugador
};

// == PROTOTIPOS DE LAS FUNCIONES ==

/* Mostrar el men� del juego, para que los usuarios puedan 
   interactuar con las opciones disponibles*/
void menu();

// Interfaz del men�
void titulo();

// L�gica del juego
void juego();

// Identificar y mostrar en pantalla qui�n ser� el primer jugador
bool m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual);

// Meter los n�meros y las x's en la matriz de forma ordenada
void meter_numero(int tabla[FILAS][COLUMNAS], int n_actual, int &p_fila_actual, int &p_columna_actual);

// Imprimir en pantalla la interfaz de juego
void imprimir_tabla(int tabla[FILAS][COLUMNAS]);

// Imprimir datos del jugador actual
void imprimir_datos(bool jugador, Jugador jb, Jugador ja);

// Comprobar si el n�mero ingresado por el usuario cumple la condici�n de inserci�n
bool condicion_de_insercion(int n_actual, int *&jugadas, int &longitud);

// Aumenta el tama�o de un arreglo dinamico
void agrandar_arreglo(int *&jugadas, int &longitud);

// Ordena un arreglo unidimensional usando quicksort 
void ordenar_arreglo(int *&jugadas, int pri, int ult);

// Pintar las casillas de la tabla
void color(int n);

using namespace std;

// == FUNCIONES ==

// Funci�n principal
int main()
{
	setlocale(LC_CTYPE, "Spanish");
    SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	
	menu();
	
	return 0;
}


// Funci�n men�
void menu()
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
				break;*/
         
			case '0': // Terminar el programa
				system("cls");
                cout <<"\n\t\t\t\t\t  = Gracias por Jugar <(* U *)/ =\n\n";
                system("pause");
                menu = 1;
			    break;

            default:
                system("cls");
                cout <<"\n\t\t\t\t     -Opcion Incorrecta - Intente Nuevamente-\n\n";
                system("pause");
        }

        system("cls");
    } while (menu == 0);
}


// Funci�n t�tulo
void titulo()
{
    cout <<"       ___________________________________________________________________________________________\n\n\n";
    
    color(3); // Color azul
	cout <<"\t    # #   # ####  ####   ###     ####  ####    #### #   #  ###  #    ### ####  ####  ###   "<<endl;
	cout <<"\t    # #   # #    #   ## #   #    #   # #       #    #   # #   # #     #  #   # #    #   #  "<<endl;
	cout <<"\t    # #   # #    #      #   #    #   # #       #    #   # #     #     #  #   # #    #       "<<endl;
	cout <<"\t    # #   # ###  #  ### #   #    #   # ###     ###  #   # #     #     #  #   # ###   ###   "<<endl;
	cout <<"\t#   # #   # #    #   #  #   #    #   # #       #    #   # #     #     #  #   # #        #  "<<endl;
	cout <<"\t#   # #   # #    #   #  #   #    #   # #       #    #   # #   # #     #  #   # #    #   #  "<<endl;
	cout <<"\t ###   ###  ####  ###    ###     ####  ####    ####  ###   ###  #### ### ####  ####  ###   "<<endl<<endl<<endl;
	
	color(14); // Color amarillo arema
	cout <<"\t\t\t\t\t     1. Comenzar Juego\n\n\n";
	cout <<"\t\t\t\t\t     2. Cargar Juego\n\n\n";
	cout <<"\t\t\t\t\t     3. Acerca del Juego\n\n\n";
	cout <<"\t\t\t\t\t     4. Ayuda\n\n\n";
	cout <<"\t\t\t\t\t     0. Salir del juego\n\n";
	
	color(7); // Color blanco
	cout <<"       ___________________________________________________________________________________________\n";
    cout << "\n       Opcion (numero) --> "; 
}


// Funci�n juego
void juego()
{
	// Semilla para el randomizer
    srand(time(0));
	
    system("cls");
	
    Jugador jb, ja;
    jb.puntos = 0, ja.puntos = 0;
    int tabla[FILAS][COLUMNAS];
    int longitud = 2, *jugadas = new int[longitud];
    int n_actual, n_aux;
    
    /*Aqu� ir� un Do While para que se pueda empezar otra partida*/

    // Solicitar los nombres de los jugadores
	cout << "       ___________________________________________________________________________________________\n\n\n";
	color(14); cout << "\t\t\t         = INGRESE LOS NOMBRES DE LOS JUGADORES =\n\n\n";
	    
	color(15); cout << "\t\t\t---> Jugador Blanco: "; color(7);
	cin >> jb.nombre;
	fflush(stdin);

	color(11); cout << "\n\t\t\t---> Jugador Azul: "; color(7);
	cin >> ja.nombre;
	fflush(stdin);

	color(12); cout << "\n\n\n\t\t\t\t\t    - Guardado Exitoso -\n\n";
	color(7); cout << "       ___________________________________________________________________________________________\n\n";
	    
    system("pause");
    system("cls");
    
    // Inicializar la tabla
	for (int i = 0; i < FILAS; i++)
	{
	    for (int j = 0; j < COLUMNAS; j++)
	    {
	        tabla[i][j] = 0;
	    }
	}

    // Generar los dos n�meros aleatorios
	n_actual = 1+(rand()%NUMEROS);
	n_aux = 1+(rand()%NUMEROS); 
    
    // Evitar que los n�meros se repitan
	do
	{
	    if (n_actual == n_aux)
	    {
	        n_aux = 1+(rand()%NUMEROS);
	    }
	} while (n_actual == n_aux);
    
    // Se meten los n�meros en el arreglo de jugadas en orden ascendente
    if (n_actual < n_aux)
    {
        jugadas[0] = n_actual;
        jugadas[1] = n_aux;
    }
    else
    {
        jugadas[0] = n_aux;
        jugadas[1] = n_actual;
    }

    // Generar la posici�n del primer n�mero
    int p_fila_actual = rand()%FILAS, p_columna_actual = rand()%COLUMNAS;

    // Meter el primer n�mero en la tabla
    tabla[p_fila_actual][p_columna_actual] = n_actual;
    
    /* Mostrar quien es el primer jugador a partir de la 
	   posici�n del primer n�mero*/
    bool jugador = m_primer_jugador(jb, ja, p_fila_actual, p_columna_actual);
    
    // Meter segundo n�mero en la tabla
    n_actual = n_aux;
    
    meter_numero(tabla, n_actual, p_fila_actual, p_columna_actual);
    
    do
    {
        // Imprimir tabla con los espacios vac�os y los dos n�meros
        imprimir_tabla(tabla);
        imprimir_datos(jugador, jb, ja);
        
        cin >> n_actual;
        fflush(stdin);

        /*Si metes un n�mero incorrecto, pierdes una casilla */
        if (n_actual < 1 || n_actual > NUMEROS) 
        {
            n_actual = X;
        }
        else
        {
            bool confirmacion = condicion_de_insercion(n_actual, jugadas, longitud);

            if (confirmacion == TRUE)
            {
                if (jugador == TRUE)
                {
                    ja.puntos++;
                }
                else
                {
                    jb.puntos++;
                }
            }
            else /*Si metes un n�mero que no cumple la condici�n, pierdes una casilla*/
            {
                n_actual = X;
            }
        }
        
        meter_numero(tabla, n_actual, p_fila_actual, p_columna_actual);

        //Se intercambia de jugador
        jugador = !jugador;
    } while(1); //Lo puse solo para probarlo
}


// Funci�n m_primer_jugador
bool m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual)
{
    cout << "       ___________________________________________________________________________________________\n\n\n\t\t\t\t       ";
    
	if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 == 0)) // Si la fila es par y la columna es par
    {
        color(15); cout << jb.nombre; color(7);
        cout << " ser� el primer jugador." << endl;
        cout << "\n       ___________________________________________________________________________________________\n\n";
        system("pause");
        return FALSE;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 != 0))  // Si la fila es impar y la columna es impar
    {
        color(15); cout << jb.nombre; color(7);
        cout << " ser� el primer jugador." << endl;
        cout << "\n       ___________________________________________________________________________________________\n\n";
        system("pause");
        return FALSE;
    }

    if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 != 0)) // Si la fila es par y la columna es impar
    {
        color(11); cout << ja.nombre; color(7); 
		cout << " ser� el primer jugador." << endl;
		cout << "\n       ___________________________________________________________________________________________\n\n";
        system("pause");
        return TRUE;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 == 0)) // Si la fila es impar y la columna es par
    {
        color(11); cout << ja.nombre; color(7); 
		cout << " ser� el primer jugador." << endl;
		cout << "\n       ___________________________________________________________________________________________\n\n";
        system("pause");
        return TRUE;
    }
}


// Funci�n meter_numeros
void meter_numero(int tabla[FILAS][COLUMNAS], int n_actual, int &p_fila_actual, int &p_columna_actual)
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


// Funci�n imprimir
void imprimir_tabla(int tabla[FILAS][COLUMNAS])
{
	system("cls");

    cout << "\n";
    cout << "       ___________________________________________________________________________________________\n\n\n";

	for (int i = 0; i < FILAS; i++)
	{
		color(7);
        cout << "\t\t\t\t   ";
		for (int j = 0; j < COLUMNAS; j++)
		{
			if (((i+1) + (j)) % 2 == 0)
				color(176);

            else
				color(240);

            if(tabla[i][j] == X)
            {
                cout << " XX ";
            }

            if (tabla[i][j] == 0)
                cout << "    ";  

			if (tabla[i][j] > 0 && tabla[i][j] < 10)
				cout << " 0" << tabla[i][j] << " ";
			
            else if (tabla[i][j] > 9)
				cout << " " << tabla[i][j] << " ";  

			if (j == 8-1)
	        	cout << "\n" ;			
		}    
	}
    color(7);
    cout << "\n";
    cout << "       ___________________________________________________________________________________________\n";
}


void imprimir_datos(bool jugador, Jugador jb, Jugador ja)
{
    cout << "\n";
    cout << "\t\t\t\t\t Datos de Jugador ";
    jugador ? color(11) : color(15);    //Dependiendo del jugador se cambia de color
    cout << (jugador ? "Azul:" : "Blanco:") << endl;
    
    color(7);

    cout << "\t\t\t\t\t    Nombre:";
    jugador ? color(11) : color(15);    //Indica los datos del jugador actual
    cout << (jugador ? ja.nombre : jb.nombre);

    color(7);

    cout << "\n\t\t\t\t\t    Puntos:";
    jugador ? color(11) : color(15);    //Indica los datos del jugador actual
    cout << (jugador ? ja.puntos : jb.puntos);    
    
    color(7);
    cout << "\n\n\n";
    cout << "       ___________________________________________________________________________________________\n\n";

	cout << "\t Ingrese n�mero a jugar --> ";	
}

bool condicion_de_insercion(int n_actual, int *&jugadas, int &longitud)
{
    for (int i = longitud-1; i >= 1; i--)
    {
        for (int j = longitud-2; j >= 0; j--)
        {
            if ((jugadas[i] - jugadas[j]) == n_actual) // Si se cumple la condici�n, entonces el n�mero puede entrar en la tabla
            {
                agrandar_arreglo(jugadas, longitud);
                jugadas[longitud-1] = n_actual;
                ordenar_arreglo(jugadas, 0, longitud-1);
                return TRUE;
            }
        }
    }

    return FALSE;
}

void agrandar_arreglo(int *&jugadas, int &longitud)
{
    longitud++;

    int *aux = new int[longitud];

    for (int i = 0; i < longitud-1; i++)
    {
        aux[i] = jugadas[i];
    }

    delete[] jugadas;

    jugadas = aux;
}

void ordenar_arreglo(int *&jugadas, int pri, int ult)
{
    int i, j, cen, piv, aux;
	
	cen = (pri + ult) / 2;
	piv = jugadas[cen];
	i = pri;
	j = ult;
	
	do
	{
		while(jugadas[i] < piv) i++;
		while(jugadas[j] > piv) j--;
		
		if (i <= j)
		{
		    aux = jugadas[i];
		    jugadas[i] = jugadas[j];
		    jugadas[j] = aux;
			i++;
			j--;
		}
		
	} while (i <= j);
	
	if (pri < j)
	{
		ordenar_arreglo(jugadas, pri, j);
	}
	
	if (i < ult)
	{
		ordenar_arreglo(jugadas, i, ult);
	}
}

// Funci�n color
void color(int n)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}