#include "Input.h"
#include "stCliente.h"
void opcionMainMenu()
{
    int opcion;

    do
    {
        printf("\n=== SISTEMA BANCARIO B.F.S ===\n");
        printf("1. Gestion de Clientes\n");
        printf("2. Gestion de Cuentas por Cliente\n");
        printf("3. Gestion de Movimientos\n");
        printf("4. Mostrar Cliente Random\n");  // 🔥 NUEVA OPCIÓN
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            menuClientes();
            break;
        case 2:
            menuCuentas();
            break;
        case 3:
            menuMovimientos();
            break;
        case 4:
            mostrarClienteRandom();  // 🔥 NUEVA FUNCIÓN
            break;
        case 0:
            printf("Saliendo del sistema...\n");
            break;
        }
    }
    while (opcion != 0);
}


void menuCuentas()
{
    int opcion;
    char nroCuenta[24];
    int idCliente;

    do
    {
        printf("\n--- MENU CUENTAS POR CLIENTE ---\n");
        printf("1. Alta de Cuenta\n");
        printf("2. Baja de Cuenta\n");
        printf("3. Modificacion de Cuenta\n");
        printf("4. Listado de Cuentas por Cliente\n");
        printf("5. Listar Cuentas Eliminadas\n");
        printf("0. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion)
        {
        case 1:
            printf("Ingrese ID del cliente: ");
            scanf("%d", &idCliente);
            fflush(stdin);
            altaCuenta(idCliente);
            break;

        case 2:
            printf("Ingrese numero de cuenta: ");
            fflush(stdin);
            fgets(nroCuenta, sizeof(nroCuenta), stdin);
            nroCuenta[strcspn(nroCuenta, "\n")] = 0; // eliminar salto de linea
            bajaCuenta(nroCuenta);
            break;

        case 3:
            printf("Ingrese numero de cuenta: ");
            fflush(stdin);
            fgets(nroCuenta, sizeof(nroCuenta), stdin);
            nroCuenta[strcspn(nroCuenta, "\n")] = 0;
            modificarCuenta(nroCuenta);
            break;

        case 4:
            printf("Ingrese ID del cliente: ");
            scanf("%d", &idCliente);
            fflush(stdin);
            listarCuentasPorCliente(idCliente);
            break;

        case 5:
            listarCuentasEliminadas();
            break;

        case 0:
            printf("Volviendo al menu principal...\n");
            break;

        default:
            printf("Opcion invalida.\n");
        }

    } while (opcion != 0);
}

void menuClientes()
{
    int opcion;
    char dni[10];
    int idCliente;
    stCliente cliente;

    do
    {
        printf("\n--- MENU CLIENTES ---\n");
        printf("1. Alta de Cliente\n");
        printf("2. Baja de Cliente\n");
        printf("3. Modificacion de Cliente\n");
        printf("4. Listado de Clientes Activos\n");
        // TO DO: printf("5. Listado completo (activos e inactivos)\n");
        printf("6. Reactivar cliente\n");
        printf("7. Buscar cliente por apellido\n");
        printf("8. Buscar cliente por DNI\n");
        printf("0. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            altaCliente();
            break;
        case 2:
            printf("Ingrese DNI: ");
            fflush(stdin);
            gets(dni);
            bajaCliente(dni);
            break;
        case 3:
            printf("Ingrese DNI: ");
            fflush(stdin);
            gets(dni);
            modificarCliente(dni);
            break;
        case 4:
            listarClientes();
            break;
        case 5:
            // listarTodosLosClientes(); (No implementada)
            break;
        case 6:
            printf("Ingrese DNI del cliente a reactivar: ");
            fflush(stdin);
            gets(dni);
            reactivarCliente(dni);
            break;
        case 7:
            buscarClientesPorApellido();
            break;
        case 8:
            buscarClientePorDNI();
            break;
        case 0:
            break;
        default:
            printf("Opcion invalida.\n");
        }
    }
    while (opcion != 0);
}

void menuMovimientos()
{
    int opcion, idMovimiento, idCuenta;
    do
    {
        printf("\n--- MENU MOVIMIENTOS ---\n");
        printf("1. Alta de Movimiento\n");
        printf("2. Baja de Movimiento\n");
        printf("3. Modificar Movimiento\n");
        printf("4. Consultar Movimiento por ID\n");
        printf("5. Listar Movimientos por Cuenta\n");
        printf("6. Listar Movimientos por Fecha (dia/mes)\n");
        printf("7. Listar Movimientos por Mes\n");
        printf("8. Listar TODOS los Movimientos\n");  // 👈 NUEVA OPCIÓN
        printf("0. Volver al menu principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);  // limpiar buffer

        switch (opcion)
        {
        case 1:
            printf("Ingrese ID de cuenta: ");
            scanf("%d", &idCuenta);
            altaMovimiento(idCuenta);
            break;

        case 2:
            printf("Ingrese ID del movimiento a eliminar: ");
            scanf("%d", &idMovimiento);
            bajaMovimiento(idMovimiento);
            break;

        case 3:
            printf("Ingrese ID del movimiento a modificar: ");
            scanf("%d", &idMovimiento);
            modificarMovimiento(idMovimiento);
            break;

        case 4:
            printf("Ingrese ID del movimiento a consultar: ");
            scanf("%d", &idMovimiento);
            consultarMovimientoPorID(idMovimiento);
            break;

        case 5:
            printf("Ingrese ID de cuenta: ");
            scanf("%d", &idCuenta);
            listarMovimientosPorCuenta(idCuenta);
            break;

        case 6:
            listarMovimientosPorFecha();
            break;

        case 7:
            listarMovimientosPorMes();
            break;

        case 8:
            listarTodosLosMovimientos();  // 👈 NUEVA FUNCIÓN LLAMADA
            break;

        case 0:
            printf("Volviendo al menu principal...\n");
            break;

        default:
            printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while (opcion != 0);
}
void mostrarClienteRandom()
{
    stCliente c;

    cargaNombreRandom(c.nombre);
    cargaApellidoRandom(c.apellido);
    cargaDniRandom(c.dni);
    cargaTelefonoRandom(c.telefonoFijo);   // ✅ uso de telefono fijo
    cargaTelefonoRandom(c.telefonoMovil);  // ✅ tambien podemos usar el movil
    //c.domicilio = cargaDomicilioRandom();
    cargaEmailRandom(c.email, c.nombre);
    c.eliminado = 0;
    c.id = 0;
    c.nroCliente = 0;

    printf("\n--- CLIENTE RANDOM GENERADO ---\n");
    printf("Nombre: %s\n", c.nombre);
    printf("Apellido: %s\n", c.apellido);
    printf("DNI: %s\n", c.dni);
    printf("Telefono Fijo: %s\n", c.telefonoFijo);     // ✅ impresion correcta
    printf("Telefono Movil: %s\n", c.telefonoMovil);   // ✅ impresion correcta
    printf("Email: %s\n", c.email);
    /*printf("Domicilio: %s %s, %s, %s, CP: %s\n",
           c.domicilio.calle,
           c.domicilio.nro,
           c.domicilio.localidad,
           c.domicilio.provincia,
           c.domicilio.cPos);*/
}

