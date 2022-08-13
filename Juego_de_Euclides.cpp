/*	Proyecto: Juego de Euclides
	Alumnos: Sebastián Landaeta, Gipsy Anaya, Antonietta Palazzo y Valery Medina
	Ingenierí­a Informática
	Técnicas de programación II
	Sección 1
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

// Mostrar el menú del juego, para que los usuarios puedan interactuar con las opciones disponibles
void menu();

// Interfaz del menú
void titulo();

// Lógica del juego
void juego();

// Identificar y mostrar en pantalla quién será el primer jugador
bool m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual);

// Meter los números y las x's en la matriz de forma ordenada
void meter_numero(int tabla[FILAS][COLUMNAS], int n_actual, int &p_fila_actual, int &p_columna_actual);

// Imprimir en pantalla la interfaz de juego
void imprimir_tabla(int tabla[FILAS][COLUMNAS]);

// Imprimir datos del jugador actual
void imprimir_datos(bool jugador, Jugador jb, Jugador ja);

// Comprobar si el número ingresado por el usuario cumple la condición de inserción
bool condicion_de_insercion(int n_actual, int *&jugadas, int &longitud);

// Aumenta el tamaño de un arreglo dinámico
void agrandar_arreglo(int *&jugadas, int &longitud);

// Ordena un arreglo unidimensional usando quicksort 
void ordenar_arreglo(int *&jugadas, int pri, int ult);

// Imprime al jugador que ganó la partida, si no hay ganador, se imprime un mensaje de empate
void imprimir_ganador(Jugador jb, Jugador ja);

// Pintar las casillas de la tabla
void color(int n);

// Preguntarle a los jugadores si quieren empezar otra partida
bool terminar();

// Verifica si fueron ingresados todos los números posibles por partida
bool verificar_jugadas(int *&jugadas, int n_mayor);

using namespace std;

// == FUNCIONES ==

// Función principal
int main()
{
	setlocale(LC_CTYPE, "Spanish");
    SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	
	menu();
	
	return 0;
}


// Función menú
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


// Función tí­tulo
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


// Función juego
void juego()
{
	// Semilla para el randomizer
    srand(time(0));
	
    system("cls");
	
    Jugador jb, ja;
	jb.puntos = 0, ja.puntos = 0;
    int tabla[FILAS][COLUMNAS];
    int longitud = 2, *jugadas = new int[longitud];
    int n_actual, n_aux, cont = 2, n_mayor;
    bool sin_movimientos, finalizar = FALSE;
    
    do
	{
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
		color(7); cout << "       ___________________________________________________________________________________________\n\n\t";
		
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
	
	
	    // Generar los dos números aleatorios
		n_actual = 1+(rand()%NUMEROS);
		n_aux = 1+(rand()%NUMEROS);

	    // Evitar que los números se repitan y que no se puedan realizar jugadas
		do
		{
		    if ((n_actual == n_aux) || ((n_actual == 1 && n_aux == 2) || (n_actual == 2 && n_aux == 1)))
		    {
		        n_aux = 1+(rand()%NUMEROS);
		    }
		} while ((n_actual == n_aux) || ((n_actual == 1 && n_aux == 2) || (n_actual == 2 && n_aux == 1)));


	    // Se meten los números en el arreglo de jugadas en orden ascendente
	    if (n_actual < n_aux)
	    {
	        jugadas[0] = n_actual;
	        jugadas[1] = n_aux;
            n_mayor = n_aux;
	    }
	    else
	    {
	        jugadas[0] = n_aux;
	        jugadas[1] = n_actual;
            n_mayor = n_actual;
	    }
	
	
	    // Generar la posición del primer número
	    int p_fila_actual = rand()%FILAS, p_columna_actual = rand()%COLUMNAS;
	
	
	    // Meter el primer número en la tabla
	    tabla[p_fila_actual][p_columna_actual] = n_actual;
	    
	    
	    /* Mostrar quien es el primer jugador a partir de la 
		   posición del primer número*/
	    bool jugador = m_primer_jugador(jb, ja, p_fila_actual, p_columna_actual);
	    
	    
	    // Meter el segundo número en la tabla
	    n_actual = n_aux;
	    
	    
	    meter_numero(tabla, n_actual, p_fila_actual, p_columna_actual);
	    
	    
	    do
	    {
            // Comprobar si se pueden realizar movimientos
            sin_movimientos = verificar_jugadas(jugadas, n_mayor);
            
            if (sin_movimientos == TRUE)
			{
                imprimir_tabla(tabla);
                color(10);
                cout <<"\n\t\t\t      == No se pueden realizar más movimientos. ==\n";
                color(7);
                imprimir_ganador(jb, ja);
                finalizar = terminar();
                break;
			}


	        // Imprimir la intefaz de juego
	        imprimir_tabla(tabla);
	        imprimir_datos(jugador, jb, ja);
	        

	        // Almacernar el número ingresado por el usuario
	        cin >> n_actual;
	        fflush(stdin);
	
	
	        // Si se ingresa un número incorrecto, pierde una casilla
	        if (n_actual < 1 || n_actual > NUMEROS) 
	        {
	            n_actual = X;
	        }
	        else
	        {
	            bool confirmacion = condicion_de_insercion(n_actual, jugadas, longitud);
	
	            if (confirmacion == TRUE) // Si el número ingresado cumple con la condición de inserción, el jugador gana un punto
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
	            else // Si se ingresa un número que no cumple con la condición, pierde una casilla
	            {
	                n_actual = X;
	            }
	        }
	        
	        
	        meter_numero(tabla, n_actual, p_fila_actual, p_columna_actual);
	        cont++;
			

	        if (cont == NUMEROS) // Si se terminan las casillas, gana el jugador que tenga más puntos
	        {
				imprimir_tabla(tabla);
                color(10);
                cout << "\n\t\t\t\t     == El tablero ya está lleno. ==\n";
                color(7);
	            imprimir_ganador(jb, ja);

	            finalizar = terminar();
				break;	            
	        }
	        else // Si aún quedan casillas, comienza el turno del siguiente jugador
	        {
	            jugador = !jugador;
	        }
			
	    } while(1);
	    
	    system("cls");
	} while (finalizar == FALSE);
}


// Función m_primer_jugador
bool m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual)
{
    cout << "       ___________________________________________________________________________________________\n\n\n\t\t\t\t       ";
    
	if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 == 0)) // Si la fila es par y la columna es par
    {
        color(15); cout << jb.nombre; color(7);
        cout << " será el primer jugador." << endl;
        cout << "\n       ___________________________________________________________________________________________\n\n\t";
        system("pause");
        return FALSE;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 != 0))  // Si la fila es impar y la columna es impar
    {
        color(15); cout << jb.nombre; color(7);
        cout << " será el primer jugador." << endl;
        cout << "\n       ___________________________________________________________________________________________\n\n\t";
        system("pause");
        return FALSE;
    }

    if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 != 0)) // Si la fila es par y la columna es impar
    {
        color(11); cout << ja.nombre; color(7); 
		cout << " será el primer jugador." << endl;
		cout << "\n       ___________________________________________________________________________________________\n\n\t";
        system("pause");
        return TRUE;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 == 0)) // Si la fila es impar y la columna es par
    {
        color(11); cout << ja.nombre; color(7); 
		cout << " será el primer jugador." << endl;
		cout << "\n       ___________________________________________________________________________________________\n\n\t";
        system("pause");
        return TRUE;
    }
}


// Función meter_numeros
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


// Función imprimir_tabla
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

            if (tabla[i][j] == X)
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


// Función imprimir_datos
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
    cout << "\n\n";
    cout << "       ___________________________________________________________________________________________\n\n";

	cout << "       Ingrese número a jugar --> ";	
}

// Función para imprimir resultados
void imprimir_ganador(Jugador jb, Jugador ja)
{
	cout << "       ___________________________________________________________________________________________\n\n\n";
	color(12);
    /*                                       --------------------------------                                   */
    /*                                            = PARTIDA  TERMINADA =                                                           */
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
	else if (ja.puntos > jb.puntos) //Si gana el jugador azúl
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


// Función condición_de_insercion
bool condicion_de_insercion(int n_actual, int *&jugadas, int &longitud)
{
    for (int i = longitud-1; i >= 1; i--)
    {
        for (int j = longitud-2; j >= 0; j--)
        {
            if ((jugadas[i] - jugadas[j]) == n_actual) // Si se cumple la condición, se comprobará que no hay números repetidos
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
                    agrandar_arreglo(jugadas, longitud);
                    jugadas[longitud-1] = n_actual;
                    ordenar_arreglo(jugadas, 0, longitud-1);
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}


// Función verificar_jugadas
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


// Función agrandar_arreglo
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


// Función ordenar_arreglo
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


// Función terminar
bool terminar()
{
    char opcion;
	
	do
	{
		cout << "       ___________________________________________________________________________________________\n\n\n";
	
		color(12); 
		cout << "\t\t\t\t           = VOLVER A JUGAR =\n\n\n";
		
		color(14);
		cout << "\t\t\t\t\t        1. Si\n\n\n";
		cout << "\t\t\t\t\t        2. No\n\n";
		
		color(7);
		cout << "       ___________________________________________________________________________________________\n";
	    cout << "\n       Opcion (numero) --> "; 
		
		cin >> opcion;
    	fflush(stdin);
		
		switch (opcion)
    	{
	        case '1':
	        	system("cls");
				return FALSE;
				break;
	
			case '2':
				system("cls");
				cout << "       ___________________________________________________________________________________________\n\n\n";
				
				color(14);
				cout << "\t\t\t\t\t    = JUEGO FINALIZADO =\n\n";
				color(7);
				
				cout << "       ___________________________________________________________________________________________\n\n";
				
				system("pause");
				return TRUE;
				break;
	
	        default:
	            system("cls");
	            cout << "\n\t\t\t\t     -Opcion Incorrecta - Intente Nuevamente-\n\n";
	            system("pause");
    	}
    	
    	system("cls");
	} while (1);
}


// Función color
void color(int n)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}