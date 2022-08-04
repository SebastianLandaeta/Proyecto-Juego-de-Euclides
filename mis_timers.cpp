#include <iostream>
#include <stdlib.h>
#include <locale>
#include <windows.h>
#include <pthread.h>

using namespace std;

void *timer(void*);

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
    
    cout << "00:00:0";
    
    for (int i = 1; i <= 10; i++)
    {
        cout << i;
        Sleep(1000);
        cout << "\b";
        if (i = 9)
        {
            cout << "\b";
        }
    }
    
    cout << endl;
    system("pause");
    return 0;
}