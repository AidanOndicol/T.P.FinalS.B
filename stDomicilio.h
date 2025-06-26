#ifndef STDOMICILIO_H_INCLUDED
#define STDOMICILIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct
{
    char calle[30];
    char nro[6];
    char localidad[50];
    char provincia[40];
    char cpos[6];
} stDomicilio;

void mostrarDomicilio(stDomicilio d);
stDomicilio cargaUnDomicilio();

#endif // STDOMICILIO_H_INCLUDED
