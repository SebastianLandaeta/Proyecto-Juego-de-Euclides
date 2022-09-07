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
#include <string.h>

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
	Jugador ja;                 // Datos del jugador azul
	int tabla[FILAS][COLUMNAS]; // Tablero de juego
	int *jugadas;               // N�meros insertados en la tabla
	int longitud;               // Longitud del vector de jugadas
	int n_elementos;            // N�mero de elementos en la tabla
	int n_actual;               // �ltima jugada realizada
	int p_fila_actual;          // Coordenada fila del n�mero actual
	int p_columna_actual;       // Coordenada columna del n�mero actual
	bool turno;                 // Identifica a qu� usuario le toca jugar
	int seg;                    // Segundos del contador de 15 minutos
	int min;                    // Minutos del contador de 15 minutos
};

// == PROTOTIPOS DE LAS FUNCIONES ==

// Muestra el men� del juego, para que los usuarios puedan interactuar con las opciones disponibles
void menu();

// Muestra la interfaz del men�
void titulo();

// Prepara la partida
void configuracion_de_juego();

// Identifica y muestra en pantalla qui�n ser� el primer jugador
bool m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual);

// Mete los n�meros y las x's en la matriz de forma ordenada
void meter_numero(int tabla[FILAS][COLUMNAS], int n_actual, int &p_fila_actual, int &p_columna_actual);

// Escribe en un archivo todos los datos relevantes de la partida
void escribir_en_archivo(Partida partida);

// Comienza la partida
void juego();

// Verifica si fueron ingresados todos los n�meros posibles por partida
bool verificar_jugadas(int *&jugadas, int longitud);

// Imprime en pantalla el tablero de juego
void imprimir_tabla(int tabla[FILAS][COLUMNAS]);

// Imprime en pantalla los datos del jugador actual
void imprimir_datos(bool jugador, Jugador jb, Jugador ja);

// Empeque�eser el tama�o de un arreglo dinamico de caracteres
void disminuir_arreglo_char(char *&entradas, int &l_entradas);

// Aumenta el tama�o de un arreglo dinamico de caracteres
void agrandar_arreglo_char(char *&entradas, int &l_entradas);

// Imprime al jugador que gan� la partida, si no hay ganador, se imprime un mensaje de empate
void imprimir_ganador(Jugador jb, Jugador ja, int min);

// Imprime al jugador contrario al actual como ganador
void imprimir_ganador_contrario(Jugador jb, Jugador ja, bool jugador);

// Comprueba si el n�mero ingresado por el usuario cumple la condici�n de inserci�n
bool condicion_de_insercion(int n_actual, int *&jugadas, int &longitud);

// Aumenta el tama�o de un arreglo din�mico de enteros
void agrandar_arreglo_int(int *&jugadas, int &longitud);

// Compara dos elementos. Es necesario para ordenar un vector con la funci�n qsort
int cmpfunc(const void *a, const void *b);

// Informaci�n referente al juego
void acerca_del_juego();

// Preguntas frecuentes
void ayuda();

// Pinta las casillas de la tabla
void color(int n);

// Mueve el cursor a una coordenada espec�fica
void gotoxy(int X, int Y);

using namespace std;

// == FUNCIONES ==

// Funci�n principal
int main()
{
	// Posibilitar el uso de caracteres especiales del idioma espa�ol
	setlocale(LC_CTYPE, "Spanish");
    SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	// Cambiar el titulo de la ventana por el nombre del juego
	SetConsoleTitleA("Juego de Euclides");
    
	// Abrir el men� de opciones
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
		// Mostrar la intefaz del men�
        titulo();
        
		// Almacenar la opci�n escogida por el usuario
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
				cout << "       ___________________________________________________________________________________________\n\n\n";
				color(10);
				cout << "\n\t\t\t\t\t  = Gracias por Jugar <(* U *)/ =\n\n\n";
				color(7);
				cout <<"       ___________________________________________________________________________________________\n\n\t";
                system("pause");
                menu = 1;
			    break;

            default: // Mostrar mensaje en caso de equivocaci�n
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
	cout << "\t    # #   # ####  ####   ###     ####  ####    #### #   #  ###  #    ### ####  ####  ###  " << endl;
	cout << "\t    # #   # #    #   ## #   #    #   # #       #    #   # #   # #     #  #   # #    #   # " << endl;
	cout << "\t    # #   # #    #      #   #    #   # #       #    #   # #     #     #  #   # #    #     " << endl;
	cout << "\t    # #   # ###  #  ### #   #    #   # ###     ###  #   # #     #     #  #   # ###   ###  " << endl;
	cout << "\t#   # #   # #    #   #  #   #    #   # #       #    #   # #     #     #  #   # #        # " << endl;
	cout << "\t#   # #   # #    #   #  #   #    #   # #       #    #   # #   # #     #  #   # #    #   # " << endl;
	cout << "\t ###   ###  ####  ###    ###     ####  ####    ####  ###   ###  #### ### ####  ####  ###  " << endl << endl << endl;
	
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

    // Declarar una variable de tipo Partida e inicializar sus miembros
	Partida partida;

	partida.jb.puntos = 0, partida.ja.puntos = 0;
	partida.longitud = 2, partida.jugadas = new int[partida.longitud];
	partida.n_elementos = 2;
	partida.min = 0, partida.seg = 0;

	// Solicitar y almacenar los nombres de los jugadores
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

	// Se meten los n�meros en el arreglo de jugadas en orden ascendente, y se almacena el n�mero mayor en una variable
	if (partida.n_actual < n_aux)
	{
	    partida.jugadas[0] = partida.n_actual;
	    partida.jugadas[1] = n_aux;
	}
	else
	{
	    partida.jugadas[0] = n_aux;
	    partida.jugadas[1] = partida.n_actual;
	}

    // Generar la posici�n del primer n�mero
	partida.p_fila_actual = rand()%FILAS, partida.p_columna_actual = rand()%COLUMNAS;

	// Meter el primer n�mero en la tabla
	partida.tabla[partida.p_fila_actual][partida.p_columna_actual] = partida.n_actual;

	// Mostrar quien es el primer jugador a partir de la posici�n del primer n�mero
	partida.turno = m_primer_jugador(partida.jb, partida.ja, partida.p_fila_actual, partida.p_columna_actual);

	// Meter el segundo n�mero en la tabla
	partida.n_actual = n_aux;
	meter_numero(partida.tabla, partida.n_actual, partida.p_fila_actual, partida.p_columna_actual);
   
   // Escribir todos los datos en un archivo
	escribir_en_archivo(partida);
}


// Funci�n m_primer_jugador
bool m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual)
{
    system("cls");

	cout << "       ___________________________________________________________________________________________\n\n\n\t\t\t\t       ";
    
	if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 == 0)) // Si la fila es par y la columna es par, el primer jugador ser� el blanco
    {
        color(15); cout << jb.nombre; color(7);
        cout << " ser� el primer jugador." << endl;
        cout << "\n       ___________________________________________________________________________________________\n\n\t";
        system("pause");
        return FALSE;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 != 0))  // Si la fila es impar y la columna es impar, el primer jugador ser� el blanco
    {
        color(15); cout << jb.nombre; color(7);
        cout << " ser� el primer jugador." << endl;
        cout << "\n       ___________________________________________________________________________________________\n\n\t";
        system("pause");
        return FALSE;
    }

    if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 != 0)) // Si la fila es par y la columna es impar, el primer jugador ser� el azul
    {
        color(11); cout << ja.nombre; color(7); 
		cout << " ser� el primer jugador." << endl;
		cout << "\n       ___________________________________________________________________________________________\n\n\t";
        system("pause");
        return TRUE;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 == 0)) // Si la fila es impar y la columna es par, el primer jugador ser� el azul
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
	// Creaci�n de archivo para escritura
    FILE *ptrfile = fopen("datos_de_partida.bin", "wb");

    // Comprobar si se cre� el archivo correctamente
	if (ptrfile == NULL)
	{
		cout << "No se pudo crear el archivo" << endl;
		exit(1);
	}
    
	// Escribir todo en el archivo
	fprintf(ptrfile, "%s %s %i %i %i %i %i %i %i %i %i %i\n", 
		partida.jb.nombre, 
		partida.ja.nombre, 
		partida.jb.puntos, 
		partida.ja.puntos, 
		partida.n_actual, 
		partida.n_elementos,
		partida.p_fila_actual, 
		partida.p_columna_actual, 
		partida.turno, 
		partida.longitud,
		partida.seg, 
		partida.min
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
    
	// Cerrar archivo
	fclose(ptrfile);
}


// Funci�n juego
void juego()
{
	// Crear variables locales necesarias para la partida
    bool sin_movimientos;
    DWORD verificar_seg, verificar_min, tiempo;
    char aux, *entradas;
    int l_entradas = 1;
    
	// Se declara una variable de tipo Partida
    Partida partida;
    
	// Se abre el archivo para lectura
    FILE *ptrfile = fopen("datos_de_partida.bin", "rb");

    // Comprobar si se abrio el archivo correctamente
	if (ptrfile == NULL)
	{
		system("cls");
		cout << "       ___________________________________________________________________________________________\n\n\n";
				
		color(12);
		cout << "\t\t\t\t\t= NO SE PUDO CARGAR LA PARTIDA =\n\n";
		color(7);
		
		cout << "       ___________________________________________________________________________________________\n\n\t";
		system("pause");
		return;
	}
    
	// Se almacenan todos los datos del archivo en la variable de tipo Partida
    fscanf(ptrfile, "%s %s %i %i %i %i %i %i %i %i %i %i\n", 
		&partida.jb.nombre, 
		&partida.ja.nombre, 
		&partida.jb.puntos, 
		&partida.ja.puntos, 
		&partida.n_actual, 
		&partida.n_elementos, 
		&partida.p_fila_actual, 
		&partida.p_columna_actual, 
		&partida.turno, 
		&partida.longitud,
		&partida.seg, 
		&partida.min
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
	
	// Se inicia la partida
	do
	{
        // Comprobar si se pueden realizar movimientos
        sin_movimientos = verificar_jugadas(partida.jugadas, partida.longitud);
            
        if (sin_movimientos == TRUE)
		{
            remove("datos_de_partida.bin");
			imprimir_tabla(partida.tabla);
            color(10);
            cout <<"\n\t\t\t      == No se pueden realizar m�s movimientos. ==\n";
            color(7);
            imprimir_ganador(partida.jb, partida.ja, partida.min);
            break;
		}

	    // Imprimir la interfaz de juego
	    imprimir_tabla(partida.tabla);
	    imprimir_datos(partida.turno, partida.jb, partida.ja);

		// Se inicializan los contadores y se muestran en pantalla
		int seg = 14, milseg = 1000;
		tiempo = GetTickCount();
		
        verificar_seg = GetTickCount()+16000; // GetTickCount() devuelve el n�mero de milisegundos desde que se inici� el sistema
		
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

				partida.seg++;

				if (partida.min == 0)
				{
					if (partida.seg < 10)
						cout << "00:0";
					else
						cout << "00:";
				
					cout << partida.seg;
				}
				
				if (partida.min > 0)
				{
					if (partida.min < 10 && partida.seg < 10)
						cout << "0" << partida.min << ":" << "0" << partida.seg;

					else if (partida.min < 10 && partida.seg > 9)
						cout << "0" << partida.min << ":" << partida.seg;

					else if (partida.min > 9 && partida.seg < 10)
						cout << partida.min << ":" << "0" << partida.seg;
					else
						cout << partida.min << ":"<< partida.seg;
				}
				
				if (partida.seg == 59)
				{
					partida.seg = -1;
					partida.min++;
				}

				color(7);	
            }

            // Se comprueba constantemente si el jugador presion� una tecla
        	if (kbhit()) //khbit() [conio.h] es una funci�n que sirve para determinar si se presion� una tecla o no.
        	{
				gotoxy(34,28);
				aux = getch();
                
				// En partida solo se acepta el uso de n�meros, enter y backspace
				if ((int)aux == 13 || (int(aux) >= 48 && int(aux) <= 57) || int(aux) == 8)
				{
                    if ((int)aux != 13 && int(aux) != 8 && l_entradas == 1) //Si colocas un d�gito cuando no hay nada, se reserva espacio y se mete en el arreglo
					{
						entradas = new char[l_entradas];
						agrandar_arreglo_char(entradas, l_entradas);
						entradas[l_entradas-2] = aux;

						cout << entradas[l_entradas-2];
					}
					else if ((int)aux != 13 && int(aux) != 8 && l_entradas > 1) //Si colocas un d�gito cuando ya hay otro, se agranda el arreglo y se coloca el otro
					{
                        agrandar_arreglo_char(entradas, l_entradas);
						entradas[l_entradas-2] = aux;

						for (int i = 0; i < l_entradas; i++)
						{
							cout << entradas[i];
						}
					}
					else if ((int)aux == 8 && l_entradas > 1) //Si colocas un backspace y hay n�meros, se borrar� el �ltimo d�gito insertado
					{	
						disminuir_arreglo_char(entradas, l_entradas);                     

						if (l_entradas > 1)
						{
                            for (int i = 0; i < l_entradas; i++)
							{
                                cout << entradas[i];
							}
						}

						cout << ' ' << "\b";
					}
					else if ((int)aux == 13 && l_entradas > 1) // Si colocas un enter y hay n�meros, entonces el arreglo se convierte a entero y se mete en la variable
					{
                        partida.n_actual = atoi(entradas);
						delete[] entradas;
						l_entradas = 1;
						break;
					}
				}
        	}
        }

        if (verificar_seg == GetTickCount()) // Si al jugador se le acaba el tiempo, gana su contrincante
        {
			remove("datos_de_partida.bin");
			system("cls");
			imprimir_tabla(partida.tabla);
            color(10);
            cout << "\n\t\t\t\t        == Se agot� el tiempo ==\n\n\t\t\t\t\t   Pasaron 15 segundos\n";
            color(7);
	        imprimir_ganador_contrario(partida.jb, partida.ja,partida.turno);
			break;
        }
	
	    if (partida.n_actual < 1 || partida.n_actual > NUMEROS) // Si se ingresa un n�mero incorrecto, el jugador pierde una casilla
	    {
	        partida.n_actual = XX;
	    }
	    else
	    {
			// Se revisa el n�mero que ingres� el jugador
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
	        else // Si se ingresa un n�mero que no cumple con la condici�n, el jugador pierde una casilla
	        {
	            partida.n_actual = XX;
	        }
	    }
	        
	    // Se mete el n�mero en la tabla y aumenta el n�mero de elementos en la misma
	    meter_numero(partida.tabla, partida.n_actual, partida.p_fila_actual, partida.p_columna_actual);
	    partida.n_elementos++;
		
	    if (partida.n_elementos == NUMEROS) // Si se terminan las casillas, gana el jugador que tenga m�s puntos
	    {
			remove("datos_de_partida.bin");
			imprimir_tabla(partida.tabla);
            color(10);
            cout << "\n\t\t\t\t     == El tablero ya est� lleno. ==\n";
            color(7);
	        imprimir_ganador(partida.jb, partida.ja, partida.min);
			break;	            
	    }		
	    else // Si a�n quedan casillas, comienza el turno del siguiente jugador
	    {
	        partida.turno = !partida.turno;
            escribir_en_archivo(partida);
	    }

	} while(partida.min != 15);
	
	if (partida.min == 15) // Si pasan 15 minutos y el juego no ha terminado, gana el jugador que tenga m�s puntos
	{
		remove("datos_de_partida.bin");
		system("cls");
		imprimir_tabla(partida.tabla);
        color(10);
        cout << "\n\t\t\t\t        == Se agot� el tiempo ==\n\n\t\t\t\t\t   Pasaron 15 minutos\n";
        color(7);
	    imprimir_ganador(partida.jb, partida.ja, partida.min);
	}
}


// Funci�n verificar_jugadas
bool verificar_jugadas(int *&jugadas, int longitud)
{
	int cont = 0, comp = 0;
    
    for (int i = 1; i < longitud; i++)
	{
        comp += i;
	}

    for (int i = longitud-1; i >= 1; i--)
    {
        for (int j = longitud-2; j >= 0; j--)
        {
			for (int k = longitud-1; k >= 0; k--)
			{
                if ((jugadas[i] - jugadas[j]) == jugadas[k])
			    {
                    cont++;
			    }
			}
		}
	}

	if (cont == comp) // No hay m�s movimientos posibles
	{
        return TRUE;
	}

	return FALSE; // Hay m�s movimientos posibles
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
			if (((i+1) + (j)) % 2 == 0)              // Condici�n para mostrar las casillas azules
				color(176);

            else                                     // Condici�n para mostrar las casillas blancas
				color(240);

            if (tabla[i][j] == XX)                   // Condici�n para mostrar las x's
                cout << " XX ";
            
            if (tabla[i][j] == 0)                    // Condici�n para mostrar los espacios vac�os
                cout << "    ";  

			if (tabla[i][j] > 0 && tabla[i][j] < 10) // Condici�n para mostrar los n�meros menores a 10
				cout << " 0" << tabla[i][j] << " ";
			
            else if (tabla[i][j] > 9)                // Condici�n para mostrar los n�meros mayores a 10
				cout << " " << tabla[i][j] << " ";  

			if (j == COLUMNAS-1)                     // Condici�n para imprimir la siguiente fila
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
    jugador ? color(11) : color(15); // Dependiendo del jugador se cambia de color
    cout << (jugador ? "Azul" : "Blanco") << endl;
    
    color(7);

    cout << "\n\t -> Nombre: ";
    jugador ? color(11) : color(15); // Indica los datos del jugador actual
    cout << (jugador ? ja.nombre : jb.nombre);

    color(7);

    cout << "\n\n\t -> Puntos: ";
    jugador ? color(11) : color(15); // Indica los datos del jugador actual
    cout << (jugador ? ja.puntos : jb.puntos);    
    
    color(7);

	cout << "\n\n\t -> Tiempo para realizar jugada: ";
    jugador ? color(11) : color(15); // Indica los datos del jugador actual
    cout << "00:15";
    
    color(7);

	cout << "\n\n\t -> Tiempo transcurrido: ";
    jugador ? color(11) : color(15); // Indica los datos del jugador actual
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
	
	entradas[l_entradas - 1] = '\0';

	char *aux = new char[l_entradas];

	for (int i = 0; i <= l_entradas-1; i++)
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
	
	entradas[l_entradas-1] = '\0';

	if (l_entradas == 1)
	{
		return;
	}

	char *aux = new char[l_entradas];

	for (int i = 0; i <= l_entradas-1; i++)
	{
		aux[i] = entradas[i];
	}

	delete[] entradas;

	entradas = aux;
}

// Funci�n imprimir_ganador
void imprimir_ganador(Jugador jb, Jugador ja, int min)
{
	int Y = 25;//Coordenada de la funcion gotoxy

	cout << "       ___________________________________________________________________________________________\n\n\n";
	color(12);

	cout << "\t\t\t\t\t = PARTIDA  TERMINADA =\n\n\n";
	color(7);
	
	if (min == 15)
	{
		Y += 2;
	}
	
	if (jb.puntos > ja.puntos)       //Si gana el jugador blanco
	{
		color(14);
		cout << "\t\t\t\t          * +  FELICIDADES  + *" << endl;
		color(15);
		
		gotoxy((52 - (strlen(jb.nombre)/2)), Y);	//Para que el nombre del ganador quede en el centro - strlen()devuelve la longitud de la cadena
		cout << jb.nombre << endl;
		
		color(14);
		cout << "\n\n\t\t\t\t           .*+ HAS  GANADO +*.\n" << endl;
		color(7);
	}
	else if (ja.puntos > jb.puntos)  //Si gana el jugador az�l
    {	
    	color(14);
		cout << "\t\t\t\t          * +  FELICIDADES  + *" << endl;
		color(11);
    	
    	gotoxy((52 - (strlen(ja.nombre)/2)), Y);
		cout << ja.nombre << endl;
    	
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
	
	cout << "       ___________________________________________________________________________________________\n\n\t";
	
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
		
		gotoxy((52 - (strlen(jb.nombre)/2)), 27);
		cout << jb.nombre << endl;
		
		color(14);
		cout << "\n\n\t\t\t\t           .*+ HAS  GANADO +*.\n" << endl;
		color(7);
	}
	else                 // Turno del jugador blanco
	{
		color(14);
		cout << "\t\t\t\t          * +  FELICIDADES  + *" << endl;
		color(11);
    	
    	gotoxy((52 - (strlen(ja.nombre)/2)), 27);
		cout << ja.nombre << endl;
    	
    	color(14);
		cout << "\n\n\t\t\t\t            .*+ HAS  GANADO +*.\n" << endl;
		color(7);
	}
	
	cout << "       ___________________________________________________________________________________________\n\n\t";
	
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

                if (cont == longitud) // Si no hay n�meros repetidos, se devuelve TRUE
                {
                    agrandar_arreglo_int(jugadas, longitud);
                    jugadas[longitud-1] = n_actual;
                    qsort(jugadas, longitud, sizeof(int), cmpfunc);
                    return TRUE;
                }
            }
        }
    }

    return FALSE; // Si no se cumplen los dos requisitos, se devuelve FALSE
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
							
				cout << "\n\t Es  un  juego  cuyo  nombre  hace  referencia  al matem�tico y ge�metra griego Euclides" << endl;
				cout << "\t (ca. 325 a. C.-ca. 265 a. C), el cual consiste en un tablero  de  (8x8), en  donde  dos" << endl;
				cout << "\t jugadores deben colocar dos n�meros enteros positivos desiguales (distintos) del  1  al" << endl;
				cout << "\t 64 e ir creando combinaciones de diferencias o restas entre los  n�meros  indicados  en" << endl;
				cout << "\t el tablero. Se debe sortear qu� participante ser� el primero  en  jugar y gana  el  que" << endl;
				cout << "\t tenga m�s casillas correctas.\n" << endl;
							
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
		cout << "\t\t\t\t1. C�mo iniciar una partida\n\n\n";
		cout << "\t\t\t\t2. C�mo jugar\n\n\n";
		cout << "\t\t\t\t3. Cu�nto tiempo dura una partida\n\n\n";
		cout << "\t\t\t\t4. Qu� significa cuando la casilla marca dos X\n\n\n";
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
				cout << "\t\t\t\t\t = C�MO INICIAR UNA PARTIDA =\n\n";
				color(7);

				cout << "\n\t  Al iniciar el programa, en el men� aparecer� la opci�n \"Nueva partida\". En  ella,  se" << endl;
				cout << "\t  le pedir� a los usuarios ingresar sus nombres (la elecci�n  del  color queda de parte" << endl;
				cout << "\t  de los jugadores), y una vez hecho eso, se elegir� al azar cual de los  dos  ser�  el" << endl;
				cout << "\t  primer jugador para, posteriormente, empezar la partida. En caso  de  haber  empezado" << endl;
				cout << "\t  una partida y haber cerrado el juego, los jugadores pueden  continuarla  selecionando" << endl;
				cout << "\t  la opci�n \"Cargar Partida\" disponible en el men�.\n" << endl;

				cout << "       ___________________________________________________________________________________________\n\n\t";	
	        	system("pause");
				break;
	
			case '2':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t\t\t      = C�MO JUGAR =\n\n";
				color(7);
				
				cout << "\n\t  Por turnos, cada jugador debe ingresar un  n�mero  que  sea  igual  a  la  diferencia" << endl;
				cout << "\t  positiva de dos n�meros que se encuentren en la tabla, la cual, tiene  una  dimensi�n" << endl;
				cout << "\t  de (8x8) y comienza con dos n�meros enteros  positivos  y  distintos.  No  se  pueden" << endl;
				cout << "\t  repetir n�meros y el n�mero a ingresar debe estar entre 1 y 64." << endl;

				cout << "\n\t  Por ejemplo:  (63 - 58) = 5,  (58 - 5) = 53,  (63 - 53) = 10..., y  as� sucesivamente" << endl;
				cout << "\t  hasta que ya no se obtengan nuevos n�meros.\n" << endl;
							
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '3':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t             = CU�NTO TIEMPO DURA UNA PARTIDA =\n\n";
				color(7);

				cout << "\n\t  Cada partida puede durar m�ximo 15 minutos. Pasado  ese  tiempo,  ganar�  el  jugador" << endl;
				cout << "\t  que m�s puntos haya obtenido. Los jugadores tienen un  m�ximo  de  15  segundos  para" << endl;
				cout << "\t  realizar una  jugada, y en caso  de  no  hacerlo,  se  nombrar�  ganador  al  jugador" << endl;
				cout << "\t  contrario.\n" << endl;
							
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '4':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t      = QU� SIGNIFICA CUANDO LA CASILLA MARCA DOS X =\n\n";
				color(7);

				cout << "\n\t  Al colocar un n�mero que no cumpla con  las  condiciones  descritas  en  la  secci�n:" << endl;
				cout << "\t  \"C�mo jugar\" se marcar� esa casilla con  dos  X, denotando que el jugador  perdi�  la" << endl;
				cout << "\t  misma." << endl;

				cout << "\n\t  Por ejemplo: la resta (41 - 17) = 24 es correcta, por lo tanto,  se marcar� el 24  en" << endl;
				cout << "\t  la casilla. Por otra parte, la resta  (41 - 17) = 23  es incorrecta, de modo  que  se" << endl;
				cout << "\t  marcar�n dos X en la casilla.\n" << endl;
							
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '5':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
		
				color(6);
				cout << "\t\t\t\t\t      = C�MO GANAR =\n\n";
				color(7);
				
				cout << "\n\t  Cuando un jugador inserte una respuesta correcta, se le  sumar�  un  punto.  Gana  el" << endl;
				cout << "\t  jugador que tenga m�s puntos al finalizar la partida. Tambi�n se puede  ganar  si  el" << endl;
				cout << "\t  contrincante no inserta un n�mero en el lapso de 15 segundos. Si  los  dos  jugadores" << endl;
				cout << "\t  tienen la misma cantidad de puntos al finalizar la partida, se declarar� empate\n" << endl;
					
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '6':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t\t      = YA NO TENGO M�S COMBINACIONES =\n\n";
				color(7);

				cout << "\n\t  Si ya no es posible realizar movimientos, se terminar�  la  partida  y  se  declarar�" << endl;
				cout << "\t  ganador al jugador que tenga m�s puntos." << endl;

				cout << "\n\t  Por ejemplo: si el tablero marca los n�meros  8  y  2,  el  primer  jugador  escoger�" << endl;
				cout << "\t  (8 - 2) = 6, y el siguiente (6 - 2) = 4, acabando  as� las  posibilidades  u opciones" << endl;
				cout << "\t  de un nuevo n�mero.\n" << endl;
							
				cout << "       ___________________________________________________________________________________________\n\n\t";
				system("pause");
				break;
			
			case '7':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(6);
				cout << "\t\t\t\t          = C�MO CULMINO EL JUEGO =\n\n";
				color(7);
				
				cout << "\n\t  El  juego  puede  terminar  cuando: se  llene  la  tabla,  ya  no  hayan  movimientos" << endl;
				cout << "\t  disponibles, pasen 15 minutos o un jugador no inserte un n�mero en  su  lapso  de  15" << endl;
				cout << "\t  segundos.\n" << endl;
				
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