#ifndef STCUENTA_H_INCLUDED
#define STCUENTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct
{
    int id; /// campo único y autoincremental
    int idCliente; /// Id del Cliente dueño de la Cuenta;
    char nroCuenta[24];
    char cbu[24];
    int tipoDeCuenta; /// 1. Caja de Ahorro en Pesos, 2. Caja de Ahorro en Dólares, 3. Cta Cte en $
    float costoMensual; /// Costo de mantenimiento del producto;
    float saldo; /// Debe actualizarse al modidificar o cargar un movimiento.
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stCuenta;

stCuenta cargaUnaCuenta(int idCliente);
void generarCadenaNumerica(char* destino, int len);
int generarIdCuenta();
void mostrarCuenta(stCuenta cnueva);
void altaCuenta(int idCliente);
void bajaCuenta(char nroCuenta[]);
void modificarCuenta(char nroCuenta[]);
void listarCuentasPorCliente(int idCliente);
void listarCuentasEliminadas();

#endif // STCUENTA_H_INCLUDED
