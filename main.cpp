// Cplusplus-projekti.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "menu.h"


int main()
{
    // Huomioidaan tulostuksissa skandinaaviset aakkoset (VS-editorin metodi):
    setlocale(LC_ALL, "fi-FI");

    // Luodaan instanssi Menu-luokasta:
    Menu program = Menu();

    // Käynnistetään ohjelma Menu-instanssin start-metodia kutsumalla:
    return program.start();
}

