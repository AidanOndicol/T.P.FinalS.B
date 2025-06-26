#include "stDomicilio.h"
#include "stCliente.h"

stDomicilio cargaUnDomicilio()
{
    stDomicilio d;
    printf("Ingresa la calle: ");
    gets(d.calle);
    printf("Ingresa el numero de la calle: ");
    gets(d.nro);
    printf("Ingresa la localidad: ");
    gets(d.localidad);
    printf("Ingresa la provincia: ");
    gets(d.provincia);
    printf("Ingresa el codigo postal: ");
    gets(d.cpos);
    fflush(stdin);

    return d;
}

void mostrarDomicilio(stDomicilio d)
{
    printf("Domicilio:\n");
    printf("-> Calle y Nro........: %s %s\n", d.calle, d.nro);
    printf("-> Localidad..........: %s\n", d.localidad);
    printf("-> Provincia..........: %s\n", d.provincia);
    printf("-> Codigo Postal......: %s\n", d.cpos);
}
