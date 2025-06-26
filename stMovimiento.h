#ifndef STMOVIMIENTO_H_INCLUDED
#define STMOVIMIENTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct
{
    int id; /// campo único y autoincremental
    int idCuenta; /// Id de la cuenta
    char detalle[100];
    float importe;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int eliminado; /// 0 si está activo - 1 si está eliminado

} stMovimiento;

stMovimiento ingresarMovimientoManual();
void mostrarUnMovimiento(stMovimiento m);
int pedirMes();
int pedirDia(int mes);
void guardarMovimiento(stMovimiento m, const char* archivo);
void mostrarMovimientosDesdeArchivo(const char* archivo);
void altaMovimiento(int idCuenta);
void listarMovimientosPorCuenta(int idCuenta);
void listarMovimientosPorFecha();
void bajaMovimiento(int idMovimiento);
void modificarMovimiento(int idMovimiento);
void consultarMovimientoPorID(int idMovimiento);
void listarMovimientosPorMes();
void listarTodosLosMovimientos();
#endif // STMOVIMIENTO_H_INCLUDED
