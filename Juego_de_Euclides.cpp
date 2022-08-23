/*	Proyecto: Juego de Euclides
	Alumnos: Sebasti�n Landaeta, Gipsy Anaya, Antonietta Palazzo y Valery Medina
	Ingenier�a Inform�tica
	T�cnicas de Programaci�n II
	Secci�n 1
*/

// == LIBRERIAS ==
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include <windows.h>
#include <conio.h>

// == CONSTANTES ==
#define FILAS 8
#define COLUMNAS 8
#define NUMEROS FILAS*COLUMNAS
#define XX -1

// == ESTRUCTURAS ==

// Datos de cada jugador
struct Jugador 
{
    char nombre[30];   // Nombre del jugador
    int puntos;        // Puntos del jugador
};

// Datos de cada partida
struct Partida
{
    Jugador jb;                 // Datos del jugador blanco
	Jugador ja;                 // Datos del jugador az�l
	int tabla[FILAS][COLUMNAS]; // Tablero de juego
	int *jugadas;               // N�meros insertados en la tabla
	int longitud;               // Longitud del vector de jugadas
	int n_elementos;            // N�mero de elementos en la tabla
	int n_actual;               // �ltima jugada realizada
	int p_fila_actual;          // Coordenada fila del n�mero actual
	int p_columna_actual;       // Coordenada columna del n�mero actual
	int n_mayor;                // N�mero m�s grande de la tabla
	bool turno;                 // Identifica a qu� usuario le toca jugar
};

// == PROTOTIPOS DE LAS FUNCIONES ==

// Mostrar el men� del juego, para que los usuarios puedan interactuar con las opciones disponibles
void menu();

// Interfaz del men�
void titulo();

// Prepara la partida
void configuracion_de_juego();

// Identificar y mostrar en pantalla qui�n ser� el primer jugador
bool m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual);

// Meter los n�meros y las x's en la matriz de forma ordenada
void meter_numero(int tabla[FILAS][COLUMNAS], int n_actual, int &p_fila_actual, int &p_columna_actual);

// Escribe en un archivo todos los datos necesarios para una partida
void escribir_en_archivo(Partida partida);

// Comienza la partida
void juego();

// Verifica si fueron ingresados todos los n�meros posibles por partida
bool verificar_jugadas(int *&jugadas, int n_mayor);

// Imprimir en pantalla la interfaz de juego
void imprimir_tabla(int tabla[FILAS][COLUMNAS]);

// Imprimir datos del jugador actual
void imprimir_datos(bool jugador, Jugador jb, Jugador ja);

// Empeque�eser el tama�o de un arreglo de caracteres
void disminuir_arreglo_char(char *&entradas, int &l_entradas);

// Agrandar el tama�o de un arreglo de caracteres
void agrandar_arreglo_char(char *&entradas, int &l_entradas);

// Imprime al jugador que gan� la partida, si no hay ganador, se imprime un mensaje de empate
void imprimir_ganador(Jugador jb, Jugador ja);

// Imprime al jugador contrario al actual como ganador
void imprimir_ganador_contrario(Jugador jb, Jugador ja, bool jugador);

// Comprobar si el n�mero ingresado por el usuario cumple la condici�n de inserci�n
bool condicion_de_insercion(int n_actual, int *&jugadas, int &longitud);

// Aumenta el tama�o de un arreglo din�mico
void agrandar_arreglo_int(int *&jugadas, int &longitud);

// Comparar dos elementos, necesario para ordenar un vector con la funci�n qsort
int cmpfunc(const void *a, const void *b);

// Informaci�n sobre el juego
void acerca_del_juego();

// Preguntas frecuentes
void ayuda();

// Pintar las casillas de la tabla
void color(int n);

// Mover el cursor a una coordenada espec�fica
void gotoxy(int X, int Y);

using namespace std;

// == FUNCIONES ==

// Funci�n principal
int main()
{
	setlocale(LC_CTYPE, "Spanish");
    SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	SetConsoleTitleA("Juego de Euclides");
    
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
            case '1': // Comenzar partida
			    configuracion_de_juego();
				juego();
				break;

			case '2': // Cargar partida
				juego();
				break;

			case '3': // Acerca del juego
				system("cls");
                acerca_del_juego();
				break;
                
			case '4': // Ayuda
				system("cls");
                ayuda();
				break;
         
			case '0': // Salir del juego
				system("cls");
                cout << "\n\n\n\t\t\t\t\t  = Gracias por Jugar <(* U *)/ =\n\n\n";
                system("pause");
                menu = 1;
			    break;

            default:
                system("cls");
                cout << "\n\t\t\t\t     -Opci�n Incorrecta - Intente Nuevamente-\n\n";
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
	cout << "\t    # #   # ####  ####   ###     ####  ####    #### #   #  ###  #    ### ####  ####  ###   " << endl;
	cout << "\t    # #   # #    #   ## #   #    #   # #       #    #   # #   # #     #  #   # #    #   #  " << endl;
	cout << "\t    # #   # #    #      #   #    #   # #       #    #   # #     #     #  #   # #    #       " << endl;
	cout << "\t    # #   # ###  #  ### #   #    #   # ###     ###  #   # #     #     #  #   # ###   ###   " << endl;
	cout << "\t#   # #   # #    #   #  #   #    #   # #       #    #   # #     #     #  #   # #        #  " << endl;
	cout << "\t#   # #   # #    #   #  #   #    #   # #       #    #   # #   # #     #  #   # #    #   #  " << endl;
	cout << "\t ###   ###  ####  ###    ###     ####  ####    ####  ###   ###  #### ### ####  ####  ###   " << endl << endl << endl;
	
	color(14); // Color amarillo arena
	cout << "\t\t\t\t\t     1. Comenzar Juego\n\n\n";
	cout << "\t\t\t\t\t     2. Cargar Juego\n\n\n";
	cout << "\t\t\t\t\t     3. Acerca del Juego\n\n\n";
	cout << "\t\t\t\t\t     4. Ayuda\n\n\n";
	cout << "\t\t\t\t\t     0. Salir del juego\n\n";
	
	color(7); // Color blanco
	cout << "       ___________________________________________________________________________________________\n";
    cout << "\n       Opci�n (n�mero) --> "; 
}


// Funci�n configuracion_de_juego
void configuracion_de_juego()
{
	system("cls");

	// Semilla para el randomizer
    srand(time(0));

	Partida partida;

	partida.jb.puntos = 0, partida.ja.puntos = 0;
	partida.longitud = 2, partida.jugadas = new int[partida.longitud];
	partida.n_elementos = 2;

	// Solicitar los nombres de los jugadores
	cout << "       ___________________________________________________________________________________________\n\n\n";
	color(14); cout << "\t\t\t         = INGRESE LOS NOMBRES DE LOS JUGADORES =\n\n\n";
		    
	color(15); cout << "\t\t\t---> Jugador Blanco: "; color(7);
	cin >> partida.jb.nombre;
	fflush(stdin);

	color(11); cout << "\n\t\t\t---> Jugador Azul: "; color(7);
	cin >> partida.ja.nombre;
	fflush(stdin);

	// Inicializar tabla
	for (int i = 0; i < FILAS; i++)
	{
		for (int j = 0; j < COLUMNAS; j++)
		{
		    partida.tabla[i][j] = 0;
		}
	}

	// Generar los dos n�meros aleatorios
	partida.n_actual = 1+(rand()%NUMEROS);
	int n_aux = 1+(rand()%NUMEROS);

	// Evitar que los n�meros se repitan y que no se puedan realizar jugadas
	do
	{
		if ((partida.n_actual == n_aux) || ((partida.n_actual == 1 && n_aux == 2) || (partida.n_actual == 2 && n_aux == 1)))
		{
		    n_aux = 1+(rand()%NUMEROS);
		}
	} while ((partida.n_actual == n_aux) || ((partida.n_actual == 1 && n_aux == 2) || (partida.n_actual == 2 && n_aux == 1)));

	// Se meten los n�meros en el arreglo de jugadas en orden ascendente, y se almacena al n�mero mayor en una variable
	if (partida.n_actual < n_aux)
	{
	    partida.jugadas[0] = partida.n_actual;
	    partida.jugadas[1] = n_aux;
        partida.n_mayor = n_aux;
	}
	else
	{
	    partida.jugadas[0] = n_aux;
	    partida.jugadas[1] = partida.n_actual;
        partida.n_mayor = partida.n_actual;
	}

    // Generar la posici�n del primer n�mero
	partida.p_fila_actual = rand()%FILAS, partida.p_columna_actual = rand()%COLUMNAS;

	// Meter el primer n�mero en la tabla
	partida.tabla[partida.p_fila_actual][partida.p_columna_actual] = partida.n_actual;

	/* Mostrar quien es el primer jugador a partir de la 
		posici�n del primer n�mero*/
	partida.turno = m_primer_jugador(partida.jb, partida.ja, partida.p_fila_actual, partida.p_columna_actual);

	// Meter el segundo n�mero en la tabla
	partida.n_actual = n_aux;

	meter_numero(partida.tabla, partida.n_actual, partida.p_fila_actual, partida.p_columna_actual);

	escribir_en_archivo(partida);
}


// Funci�n m_primer_jugador
bool m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual)
{
    system("cls");
	cout << "       ___________________________________________________________________________________________\n\n\n\t\t\t\t       ";
    
	if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 == 0)) // Si la fila es par y la columna es par
    {
        color(15); cout << jb.nombre; color(7);
        cout << " ser� el primer jugador." << endl;
        cout << "\n       ___________________________________________________________________________________________\n\n\t";
        system("pause");
        return FALSE;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 != 0))  // Si la fila es impar y la columna es impar
    {
        color(15); cout << jb.nombre; color(7);
        cout << " ser� el primer jugador." << endl;
        cout << "\n       ___________________________________________________________________________________________\n\n\t";
        system("pause");
        return FALSE;
    }

    if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 != 0)) // Si la fila es par y la columna es impar
    {
        color(11); cout << ja.nombre; color(7); 
		cout << " ser� el primer jugador." << endl;
		cout << "\n       ___________________________________________________________________________________________\n\n\t";
        system("pause");
        return TRUE;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 == 0)) // Si la fila es impar y la columna es par
    {
        color(11); cout << ja.nombre; color(7); 
		cout << " ser� el primer jugador." << endl;
		cout << "\n       ___________________________________________________________________________________________\n\n\t";
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


// Funci�n escribir_en_archivo
void escribir_en_archivo(Partida partida)
{
    FILE *ptrfile = fopen("datos_de_partida.bin", "wb");

	if (ptrfile == NULL)
	{
		cout << "No se pudo escribir en el archivo" << endl;
		exit(1);
	}

	fprintf(ptrfile, "%s %s %i %i %i %i %i %i %i %i %i\n", 
		partida.jb.nombre, 
		partida.ja.nombre, 
		partida.jb.puntos, 
		partida.ja.puntos, 
		partida.n_actual, 
		partida.n_elementos,
		partida.n_mayor, 
		partida.p_fila_actual, 
		partida.p_columna_actual, 
		partida.turno, 
		partida.longitud
	);
    
	for (int i = 0; i < partida.longitud; i++)
	{
		fprintf(ptrfile, "%i\n", partida.jugadas[i]);
	}

	for (int i = 0; i < FILAS; i++)
	{
		for (int j = 0; j < COLUMNAS; j++)
		{
			fprintf(ptrfile, "%i\n", partida.tabla[i][j]);
		}
	}

	fclose(ptrfile);
}


// Funci�n juego
void juego()
{
    bool sin_movimientos;
    DWORD verificar_seg, verificar_min, tiempo;
    char aux;
    int l_entradas = 0, seg_min = 0, min = 0;

    Partida partida;
    
	// Se abre el archivo para lectura
    FILE *ptrfile = fopen("datos_de_partida.bin", "rb");

	if (ptrfile == NULL)
	{
		system("cls");
		cout << "       ___________________________________________________________________________________________\n\n\n";
				
		color(12);
		cout << "\t\t\t\t\t= NO SE PUDO CARGAR LA PARTIDA =\n\n";
		color(7);
		
		cout << "       ___________________________________________________________________________________________\n\n";
		system("pause");
		return;
	}
    
    fscanf(ptrfile, "%s %s %i %i %i %i %i %i %i %i %i\n", 
		&partida.jb.nombre, 
		&partida.ja.nombre, 
		&partida.jb.puntos, 
		&partida.ja.puntos, 
		&partida.n_actual, 
		&partida.n_elementos, 
		&partida.n_mayor, 
		&partida.p_fila_actual, 
		&partida.p_columna_actual, 
		&partida.turno, 
		&partida.longitud
	);
    
    partida.jugadas = new int[partida.longitud];

    for (int i = 0; i < partida.longitud; i++)
	{
		fscanf(ptrfile, "%i\n", &partida.jugadas[i]);
	}
    
	for (int i = 0; i < FILAS; i++)
	{
		for (int j = 0; j < COLUMNAS; j++)
		{
			fscanf(ptrfile, "%i\n", &partida.tabla[i][j]);
		}
	}
    
	// Se cierra el archivo
    fclose(ptrfile);
    
	verificar_min = GetTickCount() + 901000;
	
	do
	{
        // Comprobar si se pueden realizar movimientos
        sin_movimientos = verificar_jugadas(partida.jugadas, partida.n_mayor);
            
        if (sin_movimientos == TRUE)
		{
            imprimir_tabla(partida.tabla);
            color(10);
            cout <<"\n\t\t\t      == No se pueden realizar m�s movimientos. ==\n";
            color(7);
            imprimir_ganador(partida.jb, partida.ja);
			remove("datos_de_partida.bin");
            break;
		}


	    // Imprimir la interfaz de juego
	    imprimir_tabla(partida.tabla);
	    imprimir_datos(partida.turno, partida.jb, partida.ja);
	        
		int seg = 14, milseg = 1000;
		tiempo = GetTickCount();
		
        verificar_seg = GetTickCount()+16000; 
		// GetTickCount() devuelve el n�mero de microsegundos desde que se inici� el sistema
	        
		while ((verificar_seg > GetTickCount()))
        {
			if (GetTickCount() == tiempo + milseg)
            {
				partida.turno ? color(11) : color(15);
				
				gotoxy(44,22);

				if (seg < 10)
					cout << "0";

                cout << seg;
				seg--;
                milseg = milseg + 1000;
				color(7);

				partida.turno ? color(11) : color (15);

				gotoxy(33,24);

				seg_min++;
				if (min == 0)
				{
					if (seg_min < 10)
						cout <<"00:0";
					else
						cout <<"00:";
				
					cout << seg_min;
				}
				
				if (min > 0)
				{
					if (min < 10 && seg_min < 10)
						cout << "0" << min << ":" << "0" << seg_min;

					else if (min < 10 && seg_min > 9)
						cout << "0" << min << ":" << seg_min;

					else if (min > 9 && seg_min < 10)
						cout << min << ":" << "0" << seg_min;
					else
						cout << min << ":"<< seg_min;
					
				}
				
				if (seg_min == 59)
				{
					seg_min = -1;
					min++;
				}

				color(7);
					
            }

        	if (kbhit()) //khbit() [conio.h] es una funci�n que sirve para determinar si se presion� una tecla o no.
        	{
				char *entradas;
				gotoxy(34,28);
				aux = getch();
                
				//Solo se acepta que ingreses n�meros, enter o backspace
				if ((int)aux == 13 || (int(aux) >= 48 && int(aux) <= 57) || int(aux) == 8)
				{
                    if ((int)aux != 13 && int(aux) != 8 && l_entradas == 0) //Si colocas un d�gito cuando no hay nada, se reserva espacio y se mete en el arreglo
					{
                        l_entradas++;
						entradas = new char[l_entradas];
						entradas[l_entradas-1] = aux;
						cout << entradas[l_entradas-1];
					}
					else if ((int)aux != 13 && int(aux) != 8 && l_entradas > 0) //Si colocas un d�gito cuando ya hay otro, se agranda el arreglo y se coloca el otro
					{
                        agrandar_arreglo_char(entradas, l_entradas);
						entradas[l_entradas-1] = aux;

						for (int i = 0; i < l_entradas; i++)
						{
							cout << entradas[i];
						}
					}
					else if ((int)aux == 8 && l_entradas > 0) //Si colocas un backspace y hay n�meros, se borrar� el �ltimo d�gito insertado
					{	
						disminuir_arreglo_char(entradas, l_entradas);

					    for (int i = 0; i < l_entradas; i++)
						{
							cout << entradas[i];
						}
						cout << ' ' << "\b";
					}
					else if ((int)aux == 13 && l_entradas > 0) //Si colocas un enter y hay n�meros, entonces el arreglo se convierte a entero y se mete en la variable
					{
                        partida.n_actual = atoi(entradas);
						delete[] entradas;
						l_entradas = 0;
						break;
					}
				}
        	}
        }

        if (verificar_seg == GetTickCount())
        {
			system("cls");
			imprimir_tabla(partida.tabla);
            color(10);
            cout << "\n\t\t\t\t        == Se agot� el tiempo ==\n\n\t\t\t\t\t   Pasaron 15 segundos\n";
            color(7);
	        imprimir_ganador_contrario(partida.jb, partida.ja,partida.turno);
			remove("datos_de_partida.bin");
			break;
        }
	
	    // Si se ingresa un n�mero incorrecto, pierde una casilla
	    if (partida.n_actual < 1 || partida.n_actual > NUMEROS) 
	    {
	        partida.n_actual = XX;
	    }
	    else
	    {
	        bool confirmacion = condicion_de_insercion(partida.n_actual, partida.jugadas, partida.longitud);
	
	        if (confirmacion == TRUE) // Si el n�mero ingresado cumple con la condici�n de inserci�n, el jugador gana un punto
	        {
	            if (partida.turno == TRUE)
	            {
	                partida.ja.puntos++;
	            }
	            else
	            {
	                partida.jb.puntos++;
	            }
	        }
	        else // Si se ingresa un n�mero que no cumple con la condici�n, pierde una casilla
	        {
	            partida.n_actual = XX;
	        }
	    }
	        
	        
	    meter_numero(partida.tabla, partida.n_actual, partida.p_fila_actual, partida.p_columna_actual);
	    partida.n_elementos++;
			

	    if (partida.n_elementos == NUMEROS) // Si se terminan las casillas, gana el jugador que tenga m�s puntos
	    {
			imprimir_tabla(partida.tabla);
            color(10);
            cout << "\n\t\t\t\t     == El tablero ya est� lleno. ==\n";
            color(7);
	        imprimir_ganador(partida.jb, partida.ja);
			remove("datos_de_partida.bin");
			break;	            
	    }		
	    else // Si a�n quedan casillas, comienza el turno del siguiente jugador
	    {
	        partida.turno = !partida.turno;
            escribir_en_archivo(partida);
	    }

	} while(verificar_min > GetTickCount());
	
	if (verificar_min <= GetTickCount())
	{
		system("cls");
		imprimir_tabla(partida.tabla);
        color(10);
        cout << "\n\t\t\t\t        == Se agot� el tiempo ==\n\n\t\t\t\t\t   Pasaron 15 minutos\n";
        color(7);
	    imprimir_ganador(partida.jb, partida.ja);
		remove("datos_de_partida.bin");
	}
}


// Funci�n verificar_jugadas
bool verificar_jugadas(int *&jugadas, int n_mayor)
{
    int array[n_mayor];
    int igual = 0;
    
    for (int i = n_mayor; i >= 0; i--)
    {
        array[i] = i+1;
    }

    for (int i = 0; i < n_mayor; i++)
    {
        if (array[i] == jugadas[i])
            igual++;
        
        if (igual == n_mayor)
            return TRUE;

    }
	
    return FALSE;
}


// Funci�n imprimir_tabla
void imprimir_tabla(int tabla[FILAS][COLUMNAS])
{
	system("cls");

    cout << "\n";
    cout << "       ___________________________________________________________________________________________\n\n\n";

	for (int i = 0; i < FILAS; i++)
	{
		color(7);
        cout << "\t\t\t\t    ";
		for (int j = 0; j < COLUMNAS; j++)
		{
			if (((i+1) + (j)) % 2 == 0)
				color(176);

            else
				color(240);

            if (tabla[i][j] == XX)
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
	        	cout << "\n";			
		}    
	}
    color(7);
    cout << "\n";
    cout << "       ___________________________________________________________________________________________\n";
}


// Funci�n imprimir_datos
void imprimir_datos(bool jugador, Jugador jb, Jugador ja)
{
    cout << "\n\n";
    color(6);
    cout << "\t--> Datos del Jugador ";
    jugador ? color(11) : color(15); //Dependiendo del jugador se cambia de color
    cout << (jugador ? "Azul" : "Blanco") << endl;
    
    color(7);

    cout << "\n\t -> Nombre: ";
    jugador ? color(11) : color(15); //Indica los datos del jugador actual
    cout << (jugador ? ja.nombre : jb.nombre);

    color(7);

    cout << "\n\n\t -> Puntos: ";
    jugador ? color(11) : color(15); //Indica los datos del jugador actual
    cout << (jugador ? ja.puntos : jb.puntos);    
    
    color(7);

	cout << "\n\n\t -> Tiempo para realizar jugada: ";
    jugador ? color(11) : color(15); //Indica los datos del jugador actual
    cout << "00:15";
    
    color(7);

	cout << "\n\n\t -> Tiempo transcurrido: ";
    jugador ? color(11) : color(15); //Indica los datos del jugador actual
    cout << "00:00";
    
    color(7);
    cout << "\n\n";
    cout << "       ___________________________________________________________________________________________\n\n";

	cout << "       Ingrese n�mero a jugar --> ";	
}


// Funci�n agrandar_arreglo_char
void agrandar_arreglo_char(char *&entradas, int &l_entradas)
{
    l_entradas++;

	char *aux = new char[l_entradas];

	for (int i = 0; i < l_entradas-1; i++)
	{
		aux[i] = entradas[i];
	}

	delete[] entradas;

	entradas = aux;
}


// Funci�n disminuir_arreglo_char
void disminuir_arreglo_char(char *&entradas, int &l_entradas)
{
    l_entradas--;
	if (l_entradas == 0)
	{
        delete[] entradas;
		return;
	}

	char *aux = new char[l_entradas];

	for (int i = 0; i <= l_entradas; i++)
	{
		aux[i] = entradas[i];
	}

	delete[] entradas;

	entradas = aux;
}


// Funci�n imprimir_ganador
void imprimir_ganador(Jugador jb, Jugador ja)
{
	cout << "       ___________________________________________________________________________________________\n\n\n";
	color(12);

	cout << "\t\t\t\t\t = PARTIDA  TERMINADA =\n\n\n";
	color(7);
	
	if (jb.puntos > ja.puntos) //Si gana el jugador blanco
	{
		color(14);
		cout << "\t\t\t\t          * +  FELICIDADES  + *" << endl;
		color(15);
		
		cout << "\n\n\t\t\t\t\t\t " << jb.nombre << endl;
		
		color(14);
		cout << "\n\n\t\t\t\t           .*+ HAS  GANADO +*.\n" << endl;
		color(7);
	}
	else if (ja.puntos > jb.puntos) //Si gana el jugador az�l
    {	
    	color(14);
		cout << "\t\t\t\t          * +  FELICIDADES  + *" << endl;
		color(11);
    	
    	cout << "\n\n\t\t\t\t\t\t " << ja.nombre << endl;
    	
    	color(14);
		cout << "\n\n\t\t\t\t            .*+ HAS  GANADO +*.\n" << endl;
		color(7);
    }
    else if (ja.puntos == jb.puntos) // Si hay empate
    {	
    	color(14);
        cout << "\t\t\t\t\t     * + EMPATE + *" << endl;
        
        color(7);
        cout << "\n\n\t\t\t\t          .*+ NO HAY GANADOR +*.\n" << endl;
    }
	
	cout << "       ___________________________________________________________________________________________\n\n\t ";
	
	system ("pause");
	system("cls");
}


// Funci�n imprimir_ganador_contrario
void imprimir_ganador_contrario(Jugador jb, Jugador ja, bool jugador)
{
	
	cout << "       ___________________________________________________________________________________________\n\n\n";
	color(12); 
	cout << "\t\t\t\t\t = PARTIDA  TERMINADA =\n\n\n";
	color(7);
	
	if (jugador == TRUE) // Turno del jugador azul
	{
		
		color(14);
		cout << "\t\t\t\t          * +  FELICIDADES  + *" << endl;
		color(15);
		
		cout << "\n\n\t\t\t\t\t\t " << jb.nombre << endl;
		
		color(14);
		cout << "\n\n\t\t\t\t           .*+ HAS  GANADO +*.\n" << endl;
		color(7);
	}
	else // Turno del jugador blanco
	{
		color(14);
		cout << "\t\t\t\t          * +  FELICIDADES  + *" << endl;
		color(11);
    	
    	cout << "\n\n\t\t\t\t\t\t " << ja.nombre << endl;
    	
    	color(14);
		cout << "\n\n\t\t\t\t            .*+ HAS  GANADO +*.\n" << endl;
		color(7);
	}
	
	cout << "       ___________________________________________________________________________________________\n\n\t ";
	
	system ("pause");
	system("cls");
}


// Funci�n condici�n_de_insercion
bool condicion_de_insercion(int n_actual, int *&jugadas, int &longitud)
{
    for (int i = longitud-1; i >= 1; i--)
    {
        for (int j = longitud-2; j >= 0; j--)
        {
            if ((jugadas[i] - jugadas[j]) == n_actual) // Si se cumple la condici�n, se comprobar� que no hay n�meros repetidos
            {
                int cont = 0;

                for (int k = 0; k < longitud; k++)
                {
                    if (jugadas[k] != n_actual)
                    {
                        cont++;
                    }
                }

                if (cont == longitud)
                {
                    agrandar_arreglo_int(jugadas, longitud);
                    jugadas[longitud-1] = n_actual;
                    qsort(jugadas, longitud, sizeof(int), cmpfunc);
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}


// Funci�n agrandar_arreglo_int
void agrandar_arreglo_int(int *&jugadas, int &longitud)
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


// Funci�n cmpfunc
int cmpfunc(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}


//Funci�n acerca_del_juego
void acerca_del_juego() 
{
    char opcion;
    int menu = 0;
	
	do
	{
		cout << "       ___________________________________________________________________________________________\n\n\n";
	
		color(11); 
		cout << "\t\t\t\t          = ACERCA DEL JUEGO =\n\n\n";
		
		color(14);
		cout << "\t\t\t\t\t    1. Descripci�n\n\n\n";
		cout << "\t\t\t\t\t    2. Credenciales\n\n\n";
		cout << "\t\t\t\t\t    3. Salir\n\n";
		
		color(7);
		cout << "       ___________________________________________________________________________________________\n";
	    cout << "\n       Opci�n (n�mero) --> "; 
		
		cin >> opcion;
    	fflush(stdin);
		
		switch (opcion)
    	{
	        case '1':
	        	system("cls");
	        	cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t\t\t= DESCRIPCI�N DEL JUEGO =\n\n";
				color(7);
							
				cout << "\n\t Es un juego matem�tico creado por Euclides (ca. 325 a. C.-ca. 265 a. C), matem�tico y" << endl;
				cout << "\t ge�metra griego, el cual consiste en un tablero de (8x8), en donde dos jugadores deben" << endl;
				cout << "\t colocar dos n�meros enteros positivos desiguales (distintos) del 1 al 64, e ir creando" << endl;
				cout << "\t combinaciones de diferencias, o restas, entre los n�meros indicados en el tablero.  Se" << endl;
				cout << "\t debe  sortear  qu�  participante  ser�  el  primero  en  jugar.  Gana  el  que  tenga" << endl;
				cout << "\t m�s casillas correctas.\n" << endl;
							
				cout << "       ___________________________________________________________________________________________\n\n\t";
	        	system("pause");
				break;
	
			case '2':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t\t\t      = CREDENCIALES =\n\n";
			
				color(7);	
				cout << "\n\t\t\t\t      - ";
				
				color(12);
				cout << "DISE�O: " << endl;
				
				color(7);
				cout << "\n\t\t\t\t\t    1. Antonietta Palazzo\n\t\t\t\t\t    2. Valery Medina\n\t\t\t\t\t    3. Gipsy Anaya\n\n";
				
				color(7);	
				cout << "\n\t\t\t\t      - ";
				
				color(12);
				cout << "DESARROLLO: " << endl;
				
				color(7);
				cout << "\n\t\t\t\t\t    1. Sebasti�n Landaeta\n\t\t\t\t\t    2. Antonietta Palazzo\n\t\t\t\t\t    3. Valery Medina\n\n";
				
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '3':
				menu = 1;
				break;
	
	        default:
	            system("cls");
	            cout << "\n\t\t\t\t     -Opci�n Incorrecta - Intente Nuevamente-\n\n";
	            system("pause");
    	}
    	
    	system("cls");
	} while (menu == 0);
}


//Funci�n ayuda
void ayuda() 
{
    char opcion;
    int menu = 0;
	
	do
	{
		cout << "       ___________________________________________________________________________________________\n\n\n";
	
		color(11); 
		cout << "\t\t\t\t\t\t  = AYUDA =\n\n\n";
		
		color(14);
		cout << "\t\t\t\t1. C�mo iniciar la partida\n\n\n";
		cout << "\t\t\t\t2. C�mo jugar\n\n\n";
		cout << "\t\t\t\t3. Cu�nto tiempo dura una partida\n\n\n";
		cout << "\t\t\t\t4. Qu� significa cuando la casilla marca una X\n\n\n";
		cout << "\t\t\t\t5. C�mo ganar\n\n\n";
		cout << "\t\t\t\t6. Ya no tengo m�s combinaciones\n\n\n";
		cout << "\t\t\t\t7. C�mo culmino el juego\n\n\n";
		cout << "\t\t\t\t8. Tip\n\n\n";
		cout << "\t\t\t\t9. Salir\n\n";
		
		color(7);
		cout << "       ___________________________________________________________________________________________\n";
	    cout << "\n       Opci�n (n�mero) --> "; 
		
		cin >> opcion;
    	fflush(stdin);
		
		switch (opcion)
    	{
	        case '1':
	        	system("cls");
	        	cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t\t\t = C�MO INICIAR LA PARTIDA =\n\n";
				color(7);
				
				cout << "\n\t  Al abrir el juego le saldr� un men� con varias opciones, marcar�  un  n�mero  1  para " << endl;
				cout << "\t  seleccionar  \"Iniciar  Partida\". A  continuaci�n,  ambos  jugadores  ingresar�n  sus " << endl;
				cout << "\t  nombres, seleccionando el color de casilla de cada uno (casilla de color  azul  o  la " << endl;			
				cout << "\t  casilla blanca)  y  el juego seleccionar� al azar el participante que jugar� primero." << endl;
				cout << "\t  La  partida  inicia  con un tablero  de (8x8)  en  donde  se  encuentran dos  n�meros" << endl;
				cout << "\t  positivos diferentes en casillas de distinto color.\n" << endl;
				
				cout << "       ___________________________________________________________________________________________\n\n\t";
	        	system("pause");
				break;
	
			case '2':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t\t\t      = C�MO JUGAR =\n\n";
				color(7);
				
				cout << "\n\t  Por  turnos  sucesivos, cada jugador resta dos de los n�meros marcados  y  se�ala  el" << endl;
				cout << "\t  n�mero resultante en la tabla de la misma forma que los anteriores ya  marcados.  Por" << endl;
				cout << "\t  ejemplo,  sup�ngase que la tabla marca los n�meros 63  y  58,  los  jugadores  pueden" << endl;
				cout << "\t  realizar las siguientes restas:  (63 - 58) = 5,  (58 - 5) = 53,  (63 - 53) = 10..., y" << endl;
				cout << "\t  as� sucesivamente hasta que ya no se obtengan nuevos n�meros.\n" << endl;
							
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '3':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t             = CU�NTO TIEMPO DURA UNA PARTIDA =\n\n";
				color(7);

				cout << "\n\t  Cada partida tiene un lapso de 15 minutos,  d�ndole 15 segundos a cada  jugador  para" << endl;
				cout << "\t  realizar su movimiento. En caso de que se agote el tiempo para realizar una jugada, se" << endl;
				cout << "\t  agote el tiempo para realizar una jugada, se  nombrar�  autom�ticamente  ganador  el" << endl;
				cout << "\t  jugador contrario al que deb�a ejecutarla." << endl;
							
				cout << "       ___________________________________________________________________________________________\n\n";
				system("pause");
				break;
			
			case '4':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t      = QU� SIGNIFICA CUANDO LA CASILLA MARCA UNA X =\n\n";
				color(7);
				
				cout << "\n\t  Al colocar un n�mero que no cumple con  la  condici�n,  perder�  la  casilla  y  �sta" << endl;
				cout << "\t  ser� marcada con una X, es decir, cuando el  n�mero  ingresado  no  sea  v�lido.  Por" << endl;
				cout << "\t  ejemplo, en el tablero se encuentran los n�meros 41 y 17, la resta (41 - 17) = 24  es" << endl;
				cout << "\t  correcta, por lo tanto,  se marcar� el 24 en la casilla, la resta  (41 - 17) = 23  es" << endl;
				cout << "\t  incorrecta, de modo que se marcar� una X en la casilla, perdiendo la casilla.\n" << endl;
							
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '5':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
		
				color(6);
				cout << "\t\t\t\t\t      = C�MO GANAR =\n\n";
				color(7);
				
				
				cout << "\n\t  Se gana realizando las diferencias (restas) de los n�meros de manera correcta, por el " << endl;
				cout << "\t  contrario, se marcar� una  X,  perdiendo la casilla,  lo  que  significa  una ventaja" << endl;
				cout << "\t  para el otro jugador. Al llenar todo el tablero, gana  aquel  que  tenga m�s casillas" << endl;
				cout << "\t  correctas, en caso contrario se declarar� empate.\n" << endl;
							
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '6':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t\t      = YA NO TENGO M�S COMBINACIONES =\n\n";
				color(7);
				
				cout << "\n\t  El jugador que no puede moverse, es decir, aquel que no pueda colocar una  diferencia" << endl;
				cout << "\t  positiva diferente a los n�meros ya marcados en el tablero,  pierde la  partida,  por" << endl;
				cout << "\t  ende, aquel que marc� el �ltimo n�mero y puede  colocar  uno  nuevo  gana  el  juego." << endl;
				cout << "\t  Por ejemplo, si el tablero marca los n�meros  8  y  2,  el  primer  jugador  escoger�" << endl;
				cout << "\t  (8 - 2) = 6, y el siguiente (6 - 2) = 4, acabando  as� las  posibilidades  u opciones" << endl;
				cout << "\t  de un nuevo n�mero, quedando como el jugador que tenga mayor  cantidad  de  puntos o" << endl;
				cout << "\t  declarando finalmente un empate.\n" << endl;
							
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '7':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t\t          = C�MO CULMINO EL JUEGO =\n\n";
				color(7);
				
				cout << "\n\t  El  juego  culmina  cuando  todo  el  tablero  est�  lleno  o  cuando uno de los  dos " << endl;
				cout << "\t  participantes no pueda colocar un nuevo n�mero.\n" << endl;
				
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '8':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t\t\t          = TIP =\n\n";
				color(7);
				
				cout << "\n\t  Se recomienda estudiar y analizar las tablas de partidas ya  terminadas para  generar" << endl;
				cout << "\t  nuevas estrategias de juego, as� como analizar  todas  las  combinaciones  de  restas" << endl;
				cout << "\t  posibles.\n" << endl;
				
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '9':
				menu = 1;
				break;
	
	        default:
	            system("cls");
	            cout << "\n\t\t\t\t     -Opci�n Incorrecta - Intente Nuevamente-\n\n\t";
	            system("pause");
    	}
    	
    	system("cls");
	} while (menu == 0);
}


// Funci�n color
void color(int n)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}


// Funci�n gotoxy
void gotoxy(int X, int Y)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = X;
    dwPos.Y = Y;
    SetConsoleCursorPosition(hcon, dwPos);
}