#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale>
#include <windows.h>
#include <thread>

using namespace std;

void parar_programa();
void meter_numero();


int n = 0;

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
    
    meter_numero();
    terminate();
    return 0;
}

void meter_numero()
{
    thread hilo();
    
    for (int i = 1; i <= 3; i++)
    {
        thread hilo = thread(&parar_programa);
        cout << "Inserte un número: ";
        cin >> n;
        hilo.join();
    }
    
    cout << "\nSe han insertado los números con éxito\n";
    exit(1);
}

void parar_programa()
{   
    for (int i = 5; i >= 0; i--)
    {
        if (n != 0)
        {
            n = 0;
            return;
        }
        Sleep(1000);
    }

    system("cls");
    cout << "Ya han pasado 5 segundos." << endl << endl;
    exit(1);
}