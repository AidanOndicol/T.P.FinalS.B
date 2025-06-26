#ifndef STCLIENTE_H_INCLUDED
#define STCLIENTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "stDomicilio.h"

typedef struct
{
    int id; /// Campo único y autoincremental
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30];
    stDomicilio domicilio;
    char telefonoFijo[12];
    char telefonoMovil[12];
    int eliminado; /// 0 si está activo - 1 si está eliminado

} stCliente;


stCliente cargarUnCliente();
void mostrarCliente(stCliente cliente);
int esEmailValido(char *email);

int existeClientePorDNI(char dni[]);
int generarIdCliente();
void altaCliente();
void bajaCliente(char dni[]);
void modificarCliente(char dni[]);
void listarClientes();
void listarClientesInactivos();
void reactivarCliente(char dni[]);
void buscarClientesPorApellido();
void buscarClientesPorId();
void buscarClientePorDNI();
#endif // STCLIENTE_H_INCLUDED
