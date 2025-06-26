#include <stdio.h>      // Entrada y salida estándar
#include <stdlib.h>     // Para funciones como rand() y malloc()
#include <string.h>     // Para funciones de manejo de cadenas
#include <time.h>       // Para inicializar semilla aleatoria si se usa
#include "stCuenta.h"   // Estructura de datos de cuenta

// Carga una cuenta nueva desde teclado
stCuenta cargaUnaCuenta(int idCliente) {
    stCuenta cnueva;

    cnueva.id = generarIdCuenta();         // Genera ID nuevo y único
    cnueva.idCliente = idCliente;          // Asocia con cliente dado

    generarCadenaNumerica(cnueva.nroCuenta, 4);    // Genera número de cuenta aleatorio
    generarCadenaNumerica(cnueva.cbu, 22);         // Genera CBU aleatorio

    printf("Número de cuenta generado: %s\n", cnueva.nroCuenta);
    printf("CBU generado: %s\n", cnueva.cbu);

    printf("Tipo de cuenta (1: CA$ / 2: CAU$D / 3: Cta Corriente): ");
    scanf("%d", &cnueva.tipoDeCuenta);     // Selección de tipo de cuenta
    fflush(stdin);

    printf("Costo mensual: ");
    scanf("%f", &cnueva.costoMensual);     // Costo por mantenimiento
    fflush(stdin);

    printf("Saldo inicial: ");
    scanf("%f", &cnueva.saldo);            // Saldo que tendrá al inicio
    fflush(stdin);

    cnueva.eliminado = 0;                  // Se marca como activa

    return cnueva;
}

// Genera una cadena de dígitos numéricos aleatorios
void generarCadenaNumerica(char* destino, int len) {
    for (int i = 0; i < len; i++) {
        destino[i] = '0' + rand() % 10;    // Caracter entre '0' y '9'
    }
    destino[len] = '\0';                  // Fin de cadena
}

// Genera el siguiente ID de cuenta disponible
int generarIdCuenta() {
    FILE *pArch = fopen("cuentas.dat", "rb");
    stCuenta aux;
    int id = 0;

    if (pArch) {
        while (fread(&aux, sizeof(stCuenta), 1, pArch) == 1) {
            if (aux.id > id) id = aux.id;  // Encuentra el mayor ID
        }
        fclose(pArch);
    }

    return id + 1;  // Devuelve siguiente ID libre
}

// Muestra todos los datos de una cuenta
void mostrarCuenta(stCuenta cnueva) {
    printf("ID Cuenta: %d\n", cnueva.id);
    printf("ID Cliente: %d\n", cnueva.idCliente);
    printf("Número de cuenta: %s\n", cnueva.nroCuenta);
    printf("CBU: %s\n", cnueva.cbu);
    printf("Tipo de cuenta: %d\n", cnueva.tipoDeCuenta);
    printf("Costo mensual: %.2f\n", cnueva.costoMensual);
    printf("Saldo: %.2f\n", cnueva.saldo);
    printf("Eliminado: %d\n", cnueva.eliminado);
}

// Da de alta una cuenta y la guarda en archivo
void altaCuenta(int idCliente) {
    FILE *pArch = fopen("cuentas.dat", "ab");  // Abrir para agregar al final
    if (!pArch) {
        printf("Error al abrir archivo.\n");
        return;
    }

    stCuenta c = cargaUnaCuenta(idCliente);  // Crear cuenta desde input

    fwrite(&c, sizeof(stCuenta), 1, pArch);  // Guardar cuenta en archivo
    fclose(pArch);

    printf("Cuenta creada exitosamente.\n");
}

// Elimina lógicamente una cuenta (no borra físicamente)
void bajaCuenta(char nroCuenta[]) {
    FILE *pArch = fopen("cuentas.dat", "r+b");  // Lectura y escritura
    stCuenta c;
    int encontrado = 0;

    if (pArch) {
        while (fread(&c, sizeof(stCuenta), 1, pArch) == 1 && !encontrado) {
            if (strcmp(c.nroCuenta, nroCuenta) == 0 && c.eliminado == 0) {
                c.eliminado = 1;  // Marcar como eliminada
                fseek(pArch, -sizeof(stCuenta), SEEK_CUR);  // Volver para sobrescribir
                fwrite(&c, sizeof(stCuenta), 1, pArch);
                encontrado = 1;
            }
        }
        fclose(pArch);
    }

    if (encontrado) {
        printf("Cuenta eliminada lógicamente.\n");
    } else {
        printf("Cuenta no encontrada o ya eliminada.\n");
    }
}

// Modifica el costo mensual de una cuenta
void modificarCuenta(char nroCuenta[]) {
    FILE *pArch = fopen("cuentas.dat", "r+b");
    stCuenta c;
    int encontrado = 0;

    if (pArch) {
        while (fread(&c, sizeof(stCuenta), 1, pArch) == 1 && !encontrado) {
            if (strcmp(c.nroCuenta, nroCuenta) == 0 && c.eliminado == 0) {
                printf("Modificar costo mensual actual (%.2f): ", c.costoMensual);
                scanf("%f", &c.costoMensual);

                fseek(pArch, -sizeof(stCuenta), SEEK_CUR);
                fwrite(&c, sizeof(stCuenta), 1, pArch);
                encontrado = 1;
            }
        }
        fclose(pArch);
    }

    if (encontrado) {
        printf("Cuenta modificada exitosamente.\n");
    } else {
        printf("Cuenta no encontrada o eliminada.\n");
    }
}

// Lista todas las cuentas activas de un cliente
void listarCuentasPorCliente(int idCliente) {
    FILE *pArch = fopen("cuentas.dat", "rb");
    stCuenta c;

    if (pArch) {
        printf("Cuentas del Cliente ID %d:\n", idCliente);
        while (fread(&c, sizeof(stCuenta), 1, pArch) == 1) {
            if (c.idCliente == idCliente && c.eliminado == 0) {
                printf("ID: %d | Nro Cuenta: %s | Saldo: %.2f | Tipo: %d\n",
                       c.id, c.nroCuenta, c.saldo, c.tipoDeCuenta);
            }
        }
        fclose(pArch);
    } else {
        printf("No se encontraron cuentas.\n");
    }
}

// Muestra todas las cuentas que han sido eliminadas lógicamente
void listarCuentasEliminadas() {
    FILE *pArch = fopen("cuentas.dat", "rb");
    stCuenta c;
    int encontradas = 0;

    if (pArch) {
        printf("\n--- Cuentas Eliminadas ---\n");
        while (fread(&c, sizeof(stCuenta), 1, pArch) == 1) {
            if (c.eliminado == 1) {
                mostrarCuenta(c);
                printf("----------------------------\n");
                encontradas = 1;
            }
        }
        fclose(pArch);

        if (!encontradas) {
            printf("No hay cuentas eliminadas.\n");
        }
    } else {
        printf("No se pudo abrir el archivo cuentas.dat.\n");
    }
}
