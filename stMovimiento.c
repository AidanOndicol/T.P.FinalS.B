#include "stMovimiento.h"  // Estructura del movimiento (debe definirse en este header)
#include "stCuenta.h"      // Estructura de cuenta (si está relacionada con los movimientos)

// Función que permite ingresar un movimiento manualmente
stMovimiento ingresarMovimientoManual()
{
    stMovimiento m;
    static int id = 0;   // ID autoincremental local a la función
    id++;
    m.id = id;

    printf("Detalle: ");
    fflush(stdin);       // Limpia el buffer de entrada
    gets(m.detalle);     // ⚠️ Inseguro, idealmente reemplazar por fgets

    printf("Importe: ");
    scanf("%f", &m.importe);

    printf("Año: ");
    scanf("%d", &m.anio);

    m.mes = pedirMes();              // Valida y asigna el mes
    m.dia = pedirDia(m.mes);         // Valida y asigna el día, según el mes

    return m;
}

// Muestra la información de un solo movimiento
void mostrarUnMovimiento(stMovimiento m)
{
    printf("El detalle es: %s ", m.detalle);
    printf("El importe es: %.2f ", m.importe);
    printf("El anio es: %d ", m.anio);
    printf("El mes es: %d ", m.mes);
    printf("El dia es: %d ", m.dia);
}

// Solicita y valida un mes (1 a 12)
int pedirMes()
{
    int mes;
    do
    {
        printf("Ingrese el mes (1-12): ");
        scanf("%d", &mes);
        if (mes < 1 || mes > 12)
        {
            printf("Mes inválido. Intente nuevamente.\n");
        }
    } while (mes < 1 || mes > 12);
    return mes;
}

// Solicita y valida un día dependiendo del mes (no considera años bisiestos)
int pedirDia(int mes)
{
    int dia;
    int maxDias;

    switch (mes)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            maxDias = 31;
            break;
        case 4: case 6: case 9: case 11:
            maxDias = 30;
            break;
        case 2:
            maxDias = 28;
            break;
        default:
            printf("Mes inválido.\n");
            return -1;
    }

    do
    {
        printf("Ingrese el día (1-%d): ", maxDias);
        scanf("%d", &dia);
        if (dia < 1 || dia > maxDias)
        {
            printf("Día inválido. Intente nuevamente.\n");
        }
    } while (dia < 1 || dia > maxDias);

    return dia;
}

// Guarda un movimiento en el archivo especificado
void guardarMovimiento(stMovimiento m, const char* archivo)
{
    FILE* fp = fopen(archivo, "ab");  // Abre el archivo en modo binario append
    if (fp != NULL)
    {
        fwrite(&m, sizeof(stMovimiento), 1, fp);  // Escribe el movimiento
        fclose(fp);
    }
    else
    {
        printf("Error al abrir el archivo para guardar el movimiento.\n");
    }
}

// Registra un nuevo movimiento para una cuenta específica
void altaMovimiento(int idCuenta)
{
    stMovimiento m = ingresarMovimientoManual();  // Solicita los datos
    m.idCuenta = idCuenta;                        // Asocia a la cuenta
    m.eliminado = 0;                              // Marca como activo
    guardarMovimiento(m, "movimientos.dat");      // Guarda en archivo
    printf("Movimiento guardado correctamente.\n");
}

// Lista todos los movimientos activos de una cuenta específica
void listarMovimientosPorCuenta(int idCuenta)
{
    FILE* fp = fopen("movimientos.dat", "rb");
    stMovimiento m;
    int encontrados = 0;

    if (fp != NULL)
    {
        printf("\nMovimientos para la cuenta ID: %d\n", idCuenta);
        printf("-----------------------------\n");

        while (fread(&m, sizeof(stMovimiento), 1, fp))
        {
            if (m.idCuenta == idCuenta && m.eliminado == 0)
            {
                mostrarUnMovimiento(m);
                printf("\n-----------------------------\n");
                encontrados++;
            }
        }

        if (encontrados == 0)
        {
            printf("No se encontraron movimientos para esta cuenta.\n");
        }

        fclose(fp);
    }
    else
    {
        printf("Error al abrir el archivo de movimientos.\n");
    }
}

// Lista todos los movimientos de un día específico
void listarMovimientosPorFecha()
{
    int mes, dia;
    printf("Ingrese el mes: ");
    mes = pedirMes();
    printf("Ingrese el día: ");
    dia = pedirDia(mes);

    FILE* fp = fopen("movimientos.dat", "rb");
    stMovimiento m;
    int encontrados = 0;

    if (fp != NULL)
    {
        printf("\nMovimientos en la fecha %02d/%02d:\n", dia, mes);
        printf("-------------------------------------\n");

        while (fread(&m, sizeof(stMovimiento), 1, fp))
        {
            if (m.mes == mes && m.dia == dia && m.eliminado == 0)
            {
                mostrarUnMovimiento(m);
                printf("\n-------------------------------------\n");
                encontrados++;
            }
        }

        if (encontrados == 0)
        {
            printf("No se encontraron movimientos para esta fecha.\n");
        }

        fclose(fp);
    }
    else
    {
        printf("No se pudo abrir el archivo de movimientos.\n");
    }
}

// Marca un movimiento como eliminado (baja lógica)
void bajaMovimiento(int idMovimiento)
{
    FILE* fp = fopen("movimientos.dat", "r+b");
    stMovimiento m;
    int encontrado = 0;

    if (fp != NULL)
    {
        while (fread(&m, sizeof(stMovimiento), 1, fp))
        {
            if (m.id == idMovimiento && m.eliminado == 0)
            {
                m.eliminado = 1;  // Marca como eliminado
                fseek(fp, -sizeof(stMovimiento), SEEK_CUR);  // Vuelve atrás
                fwrite(&m, sizeof(stMovimiento), 1, fp);  // Reescribe
                printf("Movimiento con ID %d eliminado lógicamente.\n", idMovimiento);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado)
        {
            printf("Movimiento no encontrado o ya eliminado.\n");
        }

        fclose(fp);
    }
    else
    {
        printf("Error al abrir archivo para baja.\n");
    }
}

// Permite modificar un movimiento existente
void modificarMovimiento(int idMovimiento)
{
    FILE* fp = fopen("movimientos.dat", "r+b");
    stMovimiento m;
    int encontrado = 0;

    if (fp != NULL)
    {
        while (fread(&m, sizeof(stMovimiento), 1, fp))
        {
            if (m.id == idMovimiento && m.eliminado == 0)
            {
                printf("Movimiento actual:\n");
                mostrarUnMovimiento(m);

                printf("\n\n--- Ingrese nuevos datos ---\n");
                m = ingresarMovimientoManual();  // Nuevos datos
                m.id = idMovimiento;             // Mantiene el mismo ID
                fseek(fp, -sizeof(stMovimiento), SEEK_CUR);  // Posiciona
                fwrite(&m, sizeof(stMovimiento), 1, fp);     // Actualiza
                printf("Movimiento modificado exitosamente.\n");
                encontrado = 1;
                break;
            }
        }

        if (!encontrado)
        {
            printf("Movimiento no encontrado o ya eliminado.\n");
        }

        fclose(fp);
    }
    else
    {
        printf("Error al abrir archivo para modificar.\n");
    }
}

// Busca y muestra un movimiento por su ID
void consultarMovimientoPorID(int idMovimiento)
{
    FILE* fp = fopen("movimientos.dat", "rb");
    stMovimiento m;
    int encontrado = 0;

    if (fp != NULL)
    {
        while (fread(&m, sizeof(stMovimiento), 1, fp))
        {
            if (m.id == idMovimiento && m.eliminado == 0)
            {
                printf("Movimiento encontrado:\n");
                mostrarUnMovimiento(m);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado)
        {
            printf("Movimiento no encontrado o eliminado.\n");
        }

        fclose(fp);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}

// Lista todos los movimientos de un mes específico
void listarMovimientosPorMes()
{
    int mes;
    printf("Ingrese el mes (1-12): ");
    mes = pedirMes();

    FILE* fp = fopen("movimientos.dat", "rb");
    stMovimiento m;
    int encontrados = 0;

    if (fp != NULL)
    {
        printf("\nMovimientos del mes %02d:\n", mes);
        printf("-----------------------------\n");

        while (fread(&m, sizeof(stMovimiento), 1, fp))
        {
            if (m.mes == mes && m.eliminado == 0)
            {
                mostrarUnMovimiento(m);
                printf("\n-----------------------------\n");
                encontrados++;
            }
        }

        if (!encontrados)
        {
            printf("No se encontraron movimientos para este mes.\n");
        }

        fclose(fp);
    }
    else
    {
        printf("Error al abrir archivo de movimientos.\n");
    }
}

// Lista todos los movimientos activos del archivo
void listarTodosLosMovimientos()
{
    FILE* fp = fopen("movimientos.dat", "rb");
    stMovimiento m;
    int encontrados = 0;

    if (fp != NULL)
    {
        printf("\n--- LISTADO DE TODOS LOS MOVIMIENTOS ACTIVOS ---\n");
        while (fread(&m, sizeof(stMovimiento), 1, fp))
        {
            if (m.eliminado == 0)
            {
                mostrarUnMovimiento(m);
                printf("\n-----------------------------\n");
                encontrados++;
            }
        }

        if (encontrados == 0)
        {
            printf("No hay movimientos activos registrados.\n");
        }

        fclose(fp);
    }
    else
    {
        printf("No se pudo abrir el archivo de movimientos.\n");
    }
}
