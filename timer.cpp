/*
Program: Timer
Description: Sets timer according to the time provided by the user.
Author: Lord Hypersonic
Email: lordhypersonic.522@gmail.com
Website: www.lordhypersonic.blogspot.com
*/
#include <iostream>
#include <stdlib.h> //for system()
#include <windows.h> //for Sleep() and Beep()

using namespace std;

//timer function
void timer(int h, int m, int s)
{
    for(;;)
    {
        if (h == 0 && m == 0 && s == 0)
        {
            break;
        }
        if (s == 0 && m ==0)
        {
            m = 60;
            h--;
        }
        if (s == 0)
        {
            s = 60;
            m--;
        }
        system("cls");
        cout<<h<<":"<<m<<":"<<s--;
        Sleep(1000);
    }
}

int main()
{
    int h, m, s;
    cout<<"Hours: "; cin>>h;
    cout<<"Minutes: "; cin>>m;
    cout<<"Seconds: "; cin>>s;
    timer(h,m,s);
    for (int i = 100; ; i = i + 50)
        Beep(i,1000);
}