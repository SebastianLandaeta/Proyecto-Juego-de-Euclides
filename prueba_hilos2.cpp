#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale>
#include <windows.h>
#include <pthread.h>

using namespace std;

void *parar_programa(void*);
void meter_numero();

int n = 0;

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
    
    meter_numero();
    
    return 0;
}

void meter_numero()
{   
    pthread_t hilo;
    
    for (int i = 1; i <= 3; i++)
    {
        pthread_create(&hilo, NULL, &parar_programa, NULL);
        cout << "Inserte un número: ";
        cin >> n;
        pthread_join(hilo, NULL);
    }
    
    cout << "\nSe han insertado los números con éxito\n";
    exit(1);
}

void *parar_programa(void*)
{   
    for (int i = 5; i >= 0; i--)
    {
        if (n != 0)
        {
            n = 0;
            pthread_exit(NULL);
        }
        Sleep(1000);
    }

    system("cls");
    cout << "Ya han pasado 5 segundos." << endl << endl;
    exit(1);
}