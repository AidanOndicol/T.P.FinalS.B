#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "stCliente.h"
#include "stMovimiento.h"
#include "mocks.h"
#include "stDomicilio.h"
#include "stCuenta.h"
#define ESC 27

void cargaNombreRandom(char nombre[])
{
    char nombres[][30]=
    {
        "Sofia", "Mateo", "Valentina", "Santiago", "Isabella", "Benjamin", "Camila", "Emilio", "Renata", "Lucas",
        "Martina", "Tomas", "Lucia", "Gabriel", "Paula", "Diego", "Antonia", "Andres", "Emma", "Leonardo",
        "Carla", "Joaquin", "Abril", "Adrian", "Mia", "Nicolas", "Josefina", "Daniel", "Mariana", "Bruno"
    };
    strcpy(nombre, nombres[rand()%(sizeof(nombres)/30)]);
}

void cargaApellidoRandom(char apellido[])
{
    char apellidos[][30]=
    {
        "Garcia", "Martinez", "Lopez", "Gonzalez", "Perez", "Rodriguez", "Sanchez", "Ramirez", "Torres", "Flores",
        "Rivera", "Diaz", "Cruz", "Morales", "Ortiz", "Gutierrez", "Chavez", "Ramos", "Vargas", "Castro",
        "Mendoza", "Herrera", "Jimenez", "Ruiz", "Aguilar", "Silva", "Delgado", "Romero", "Vega", "Navarro"


    };
    strcpy(apellido, apellidos[rand()%(sizeof(apellidos)/30)]);
}

void cargaDniRandom(char dni[])
{
    itoa(rand()%100 * 1000000 + rand()%1000 * 1000 + rand()%1000, dni, 10);
}

void cargaEmailRandom(char email[], char nombre[]) {
    const char *dominios[] = {
        "@gmail.com", "@yahoo.com", "@outlook.com", "@hotmail.com", "@mail.com"
    };

    int cantDominios = sizeof(dominios) / sizeof(dominios[0]);

    int numero = rand() % 1000;  // numero aleatorio entre 0 y 999
    const char *dominio = dominios[rand() % cantDominios];

    sprintf(email, "%s%d%s", nombre, numero, dominio);
}

void cargaTelefonoRandom(char telefono[])
{
    long numero = rand()%1000000+2233000000;
    char celu[12];

    sprintf(celu, "%lld", numero);
    strcpy(telefono, celu);
}

void cargaCliente2ArchivoRandom(char nombreArchivo[])
{
    FILE* archi= fopen(nombreArchivo, "ab");
    stCliente a;
    if(archi)
    {
        cargaNombreRandom(a.nombre);
        cargaApellidoRandom(a.apellido);
        cargaDniRandom(a.dni);
        cargaTelefonoRandom(a.telefonoFijo);
        a.domicilio=cargaDomicilioRandom();
        fseek(archi,0,SEEK_END);
        a.id= (ftell(archi)/sizeof(stCliente)+1);
        cargaEmailRandom(a.email, a.nombre);
        a.eliminado = 0;
        a.nroCliente=a.id;
        fwrite(&a,sizeof(stCliente),1, archi);


        fclose(archi);
    }
}

void cargaCalleRandom(char calle [])
{
    char calles[][30]= {"Avenida Constitucion","Avenida Colon","Avenida Independencia","Avenida Luro","Avenida Juan B. Justo","Avenida Jara",
                        "Avenida Mario Bravo","Avenida Champagnat","Avenida Pedro Luro","Boulevard Maritimo","Guemes","San Martin","Mitre","Alberti",
                        "Entre Rios","12 de Octubre","Peralta Ramos","Tucuman","Alsina","Buenos Aires"
                       };

    strcpy(calle,calles[rand()%(sizeof(calles)/30)]);
}

void cargaLocalidad (char localidad [])
{

    char localidades [] [30]= {"Mar del Plata","Batan","Chapadmalal","Sierra de los Padres"};

    strcpy ( localidad, localidades [rand () % (sizeof (localidades))/30]);

}

void cargaProvinciaRandom (char provincia [])
{

    char provincias [] [20]= {"Buenos Aires","CABA","Catamarca","Chaco","Chubut","Cordoba","Corrientes","Entre Rios","Formosa","Jujuy","La Pampa",
                              "La Rioja","Mendoza","Misiones","Neuquen","Rio Negro","Salta","San Juan","San Luis","Santa Cruz","Santa Fe","Santiago del Estero","Tierra del Fuego",
                              "Tucuman"
                             };


    strcpy (provincia, provincias [rand () % sizeof (provincias) /20]);

}

void cargaCpostalRandom (char cPos [])
{
    for (int i = 0; i < 4; i++)
    {
        cPos[i] = (rand() % 10) + '0'; // Convertir el n�mero a valor ASCII de char
    }
    cPos[4] = '\0'; // Agregar el car�cter nulo al final de la cadena

    return cPos;
}

void cargaNumDomicilioRandom (char numeroDomicilio [])
{

    int numDom=rand ()%100 + 999;
    char cadena [10];
    sprintf (cadena, "%d", numDom);
    strcpy ( numeroDomicilio, cadena);

}

stDomicilio cargaDomicilioRandom ()
{
    stDomicilio d;

    cargaCalleRandom(d.calle);
    cargaNumDomicilioRandom(d.nro);
    cargaLocalidad(d.localidad);
    cargaProvinciaRandom(d.provincia);
    cargaCpostalRandom(d.cpos);

    return d;
}

void cargaDetalleRandom(char detalle[]) ///descripcion del detalle de saldo positivo
{
    char detalles[][100]= {"Credito de haberes", "Transferencia de cuenta de ahorros","Acreditacion de plazo fijo",
                           "Transferencia electronica recibida","Cobro de dividendos", "Deposito de cheques","Pago por reembolso"
                          };


    strcpy(detalle,detalles[(rand()%(sizeof(detalles))/100)]);
}
void cargarDetalleSaldoNegativo(char detalle[]) ///descripcion del detalle de saldo negativo
{
    char detalleSaldoNegativo[][100]= {"Pago de factura","Retiro en cajero automatico","Transferencia a cuenta de terceros",
                                       "Pago de tarjeta de credito","Pago con tarjeta de debito","Pago de prestamo bancario"
                                      };

    strcpy(detalle,detalleSaldoNegativo[(rand()%(sizeof(detalleSaldoNegativo))/100)]);
}

float cargarImporte()
{
    return rand()%50000-rand()%40000;
}

int cargaDia()
{
    return rand()%31+1;
}

int cargaMes()
{
    return rand()%12+1;
}

int cargaAnio()
{
    return rand()%204+1822;
}

stMovimiento cargaMovimientosRandom() ///funcion que carga y retorna un movimiento
{
    stMovimiento mov;
    mov.importe=cargarImporte();
    if (mov.importe>0)
    {
        cargaDetalleRandom(mov.detalle);
    }
    else
    {
        cargarDetalleSaldoNegativo(mov.detalle);
    }
    mov.dia=cargaDia();
    mov.mes=cargaMes();
    mov.anio=cargaAnio();

    return mov;
}

int cargaMovimientosRandomEnArchi(char nombreArchivoMov[],char nombreArchivoCuen[], int idCuenta)
{
    FILE *archi=fopen(nombreArchivoMov,"ab");
    stMovimiento movimiento;
    int cantidadMovimientos = 0;
    char opcion=0;
    int idMovimiento =  cuentaRegistros(nombreArchivoMov, sizeof(stMovimiento));
    if (archi)
    {
        while(opcion!=ESC)

        {
            movimiento=cargaMovimientosRandom();
            idMovimiento++;
            movimiento.id=idMovimiento;
            movimiento.eliminado=0;
            movimiento.idCuenta=idCuenta;
            muestraMovimiento(movimiento);
            ///devuelve el nro de archivos que escribo
            cantidadMovimientos = cantidadMovimientos + fwrite(&movimiento,sizeof(stMovimiento),1,archi);
            //actualizarSaldo2(nombreArchivoCuen, movimiento);
            printf("Ingrese ESC para salir o cualquier otra tecla si desea agregar un nuevo movimiento:\n");
            fflush(stdin);
            opcion=getch();
            system("cls");
        }

        fclose(archi);
    }
    return cantidadMovimientos;
}
void muestraMovimiento(stMovimiento mov)
{
    printf("=====================================\n");
    printf("ID Movimiento: %d\n", mov.id);
    printf("ID Cuenta: %d\n", mov.idCuenta);
    printf("Importe: %.2f\n", mov.importe);
    printf("Detalle: %s\n", mov.detalle);
    printf("Fecha: %02d/%02d/%04d\n", mov.dia, mov.mes, mov.anio);
    printf("Estado: %s\n", mov.eliminado == 0 ? "Activo" : "Eliminado");
    printf("=====================================\n");
}

int cuentaRegistros(const char nombreArchivo[], int tamanioStruct)
{
    FILE* archi = fopen(nombreArchivo, "rb");
    int cantidad = 0;

    if (archi)
    {
        fseek(archi, 0, SEEK_END);
        long bytes = ftell(archi);
        cantidad = bytes / tamanioStruct;
        fclose(archi);
    }

    return cantidad;
}

int cargaIdCuentaRandom(char nombreArchivo[])
{
    int idCuenta;
    stCuenta cuenta;
    int cantidad=cuentaRegistros(nombreArchivo, sizeof(stCuenta));
    FILE* archi=fopen(nombreArchivo, "rb");
    if(archi)
    {
        do
        {
            fseek(archi,(rand()%cantidad)*sizeof(stCuenta),SEEK_SET);
            fread(&cuenta,sizeof(stCuenta),1,archi);
        }
        while(cuenta.eliminado==-1);
        idCuenta=cuenta.id;
        fclose(archi);
    }
    return idCuenta;
}

void cargaMilMovimientosRandomEnArchi(char nombreArchivoMov[], char nombreArchivoCuenta[])
{
    FILE *archi=fopen(nombreArchivoMov,"ab");
    stMovimiento movimiento;
    char opcion=0;
    int idMovimiento =  cuentaRegistros(nombreArchivoMov, sizeof(stMovimiento));
    if (archi)
    {
        for (int i=0; i<1000; i++)

        {
            movimiento=cargaMovimientosRandom();
            idMovimiento++;
            movimiento.id=idMovimiento;
            movimiento.idCuenta=cargaIdCuentaRandom(nombreArchivoCuenta);
            //actualizarSaldo2(nombreArchivoCuenta, movimiento);
            fwrite(&movimiento,sizeof(stMovimiento),1,archi);
        }

        fclose(archi);
    }
}

