
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

// == ESTRUCTURAS ==

// Datos de cada jugador
struct Jugador 
{
    char nombre[30];   // Nombre del jugador
    int puntos;        // Puntos del jugador
    int fallos;        // Fallos del jugador
};


// == PROTOTIPOS DE FUNCIONES ==

/* Mostrar el menú del juego, para que los usuarios puedan 
   interactuar con las opciones disponibles*/
void menu();

// Interfaz del menú
void titulo();

// Lógica del juego, y por ende es la más grande de todas
void juego();

/* Identificar y mostrar en pantalla quién será el primer 
   jugador*/
bool m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual);

//( Meter los números y las x's en la matriz de forma ordenada
void meter_numero(int tabla[FILAS][COLUMNAS], int n_actual, int &p_fila_actual, int &p_columna_actual);

// Imprimir en pantalla la interfaz de juego
void imprimir(int tabla[FILAS][COLUMNAS], Jugador jb, Jugador ja);

// Imprimir datos del jugador actual
void imprimirdatos(bool jugador, Jugador jb, Jugador ja);

// Pintar las casillas de la tabla
void color(int n);



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
				break;

			case '0': // Terminar el programa
				system("cls");
                cout <<"\n\t\t\t\t\t  = Gracias por Jugar <(* U *)/ =\n\n";
                menu = 1;
			    break;*/

            default:
                system("cls");
                cout <<"\n\t\t\t\t     -Opcion Incorrecta - Intente Nuevamente-\n\n";
                system("pause");
                system("cls");
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
    int tabla[FILAS][COLUMNAS];
    int n_actual, n_nuevo;
    
    /*Aquí­ irá en Do While para que se pueda empezar otra partida*/

    // Solicitar los nombres de los jugadores
	cout << "       ___________________________________________________________________________________________\n\n\n";
	color(14); cout << "\t\t\t         = INGRESE LOS NOMBRES DE LOS JUGADORES =\n\n\n";
	    
	color(15); cout << "\t\t\t---> Jugador Blanco: "; color(7);
	cin >> jb.nombre;
	    
	color(11); cout << "\n\t\t\t---> Jugador Azul: "; color(7);
	cin >> ja.nombre;
	    
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

    // Generar los dos números aleatorios
	n_actual = 1+(rand()%NUMEROS);
	n_nuevo = 1+(rand()%NUMEROS); 
    
    // Evitar que los números se repitan
	do
	{
	    if (n_actual == n_nuevo)
	    {
	        n_nuevo = 1+(rand()%NUMEROS);
	    }
	} while (n_actual == n_nuevo);
    
    // Generar la posición del primer número
    int p_fila_actual = rand()%FILAS, p_columna_actual = rand()%COLUMNAS;
    
    // Meter el primer número en la tabla
    tabla[p_fila_actual][p_columna_actual] = n_actual;
    
    /* Mostrar quien es el primer jugador a partir de la 
	   posición del primer número*/
    bool jugador = m_primer_jugador(jb, ja, p_fila_actual, p_columna_actual);
    
    // Meter segundo número en la tabla
    n_actual = n_nuevo;

    do {
    
        meter_numero(tabla, n_actual, p_fila_actual, p_columna_actual);
    
        // Imprimir tabla con los espacios vací­os y los dos números
        imprimir(tabla, jb, ja);
        imprimirdatos(jugador, jb, ja);

        cin >> n_actual;

        //

        //Se intercambia de jugador
        jugador = !jugador;

    } while(5); //Lo puse solo para probarlo

}


// Función m_primer_jugador
bool m_primer_jugador(Jugador jb, Jugador ja, int p_fila_actual, int p_columna_actual)
{
    cout << "       ___________________________________________________________________________________________\n\n\n\t\t\t\t       ";
    
	if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 == 0)) // Si la fila es par y la columna es par
    {
        color(15); cout << jb.nombre; color(7);
        cout << " será el primer jugador." << endl;
        cout << "\n       ___________________________________________________________________________________________\n\n";
        system("pause");
        return 0;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 != 0))  // Si la fila es impar y la columna es impar
    {
        color(15); cout << jb.nombre; color(7);
        cout << " será el primer jugador." << endl;
        cout << "\n       ___________________________________________________________________________________________\n\n";
        system("pause");
        return 0;
    }

    if ((p_fila_actual % 2 == 0) && (p_columna_actual % 2 != 0)) // Si la fila es par y la columna es impar
    {
        color(11); cout << ja.nombre; color(7); 
		cout << " será el primer jugador." << endl;
		cout << "\n       ___________________________________________________________________________________________\n\n";
        system("pause");
        return 1;
    }

    if ((p_fila_actual % 2 != 0) && (p_columna_actual % 2 == 0)) // Si la fila es impar y la columna es par
    {
        color(11); cout << ja.nombre; color(7); 
		cout << " será el primer jugador." << endl;
		cout << "\n       ___________________________________________________________________________________________\n\n";
        system("pause");
        return 1;
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


// Función imprimir
void imprimir(int tabla[FILAS][COLUMNAS], Jugador jb, Jugador ja) /*Función imprimir*/
{
	system("cls");

    cout << "\n";
    cout <<"       ___________________________________________________________________________________________\n\n\n";

	for (int i = 0; i < FILAS; i++)
	{
		color(7);
        cout <<"\t\t\t\t   ";
		for (int j = 0; j < COLUMNAS; j++)
		{
			if (((i+1) + (j)) % 2 == 0)
				color(176);

            else
				color(240);

            if(tabla[i][j] == 0)
                cout << "    ";  

			if (tabla[i][j] > 0 && tabla[i][j] < 10)
				cout << " 0" << tabla[i][j] << " ";
			
            else if(tabla[i][j] > 9)
				cout << " " << tabla[i][j] << " ";  

			if (j == 8-1)
	        	cout << "\n" ;			
		}    
	}
    color(7);
    cout << "\n";
    cout <<"       ___________________________________________________________________________________________\n";
}


void imprimirdatos(bool jugador, Jugador jb, Jugador ja)
{
    cout <<"\n";
    cout<<"\t\t\t\t\t Datos de Jugador ";
    jugador ? color(11) : color(15);    //Dependiendo del jugador se cambia de color
    cout<< (jugador ? "Azul:" : "Blanco:")<<endl;
    
    color(7);

    cout<<"\t\t\t\t\t    Nombre:";
    jugador ? color(11) : color(15);    //Indica los datos del jugador actual
    cout << (jugador ? ja.nombre : jb.nombre);
    
    color(7);
    cout << "\n\n\n";
    cout <<"       ___________________________________________________________________________________________\n\n";

	cout << "\t Ingrese número a jugar --> ";	
}


// Función color
void color(int n)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}