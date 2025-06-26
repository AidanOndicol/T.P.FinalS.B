#include "stCliente.h"
#include "stDomicilio.h"
#include "stCuenta.h"

// Carga los datos de un nuevo cliente desde el teclado
stCliente cargarUnCliente()
{
    stCliente cliente;
    cliente.id = generarIdCliente();                  // Genera un ID unico
    cliente.nroCliente = cliente.id + 1000;           // Calcula el numero de cliente

    // Solicita el nombre del cliente
    printf("-> Nombre...................: ");
    fflush(stdin);
    gets(cliente.nombre);

    // Solicita el apellido del cliente
    printf("-> Apellido.................: ");
    fflush(stdin);
    gets(cliente.apellido);

    // Solicita el email y valida su formato
    printf("-> Email....................: ");
    do
    {
        fflush(stdin);
        gets(cliente.email);
        if(!esEmailValido(cliente.email))
        {
            printf("Email invalido. Intente nuevamente: ");
        }
    } while(!esEmailValido(cliente.email));

    // Solicita el domicilio (usa funcion externa)
    printf("-> Domicilio:\n");
    cliente.domicilio = cargaUnDomicilio();

    // Telefonos
    printf("-> Telefono fijo............: ");
    fflush(stdin);
    gets(cliente.telefonoFijo);

    printf("-> Telefono movil...........: ");
    fflush(stdin);
    gets(cliente.telefonoMovil);

    cliente.eliminado = 0; // Marca el cliente como activo

    printf("----------------------------------------------\n");
    return cliente;
}

// Muestra por pantalla la informacion de un cliente
void mostrarCliente(stCliente cliente)
{
    printf("---------------------------------------------\n");
    printf("              DATOS DEL CLIENTE              \n");
    printf("---------------------------------------------\n");

    printf("ID Cliente...........: %d\n", cliente.id);
    printf("Nro Cliente..........: %d\n", cliente.nroCliente);
    printf("Nombre...............: %s %s\n", cliente.nombre, cliente.apellido);
    printf("DNI..................: %s\n", cliente.dni);
    printf("Email................: %s\n", cliente.email);

    mostrarDomicilio(cliente.domicilio); // Llama funcion externa

    printf("Telefono Fijo........: %s\n", cliente.telefonoFijo);
    printf("Telefono Movil.......: %s\n", cliente.telefonoMovil);

    printf("----------------------------------------------\n\n");
}

// Verifica si el email ingresado tiene un formato valido
int esEmailValido(char *email)
{
    int esVal = 1;
    char *arroba = strchr(email, '@');
    char *punto =  strrchr(email, '.');

    // Reglas basicas:
    // - Contener '@' y '.'
    // - '@' no debe estar al principio
    // - '.' debe estar despues de '@'
    if(arroba && arroba != email && punto && punto > arroba)
    {
        esVal = 1;
    }
    else
    {
        esVal = 0;
    }

    return esVal;
}

// Genera un nuevo ID para un cliente incrementando el mayor existente en archivo
int generarIdCliente()
{
    static int id = 0;
    FILE *pArch = fopen("clientes.dat", "rb");
    stCliente aux;

    // Recorre el archivo para encontrar el mayor ID
    while (fread(&aux, sizeof(stCliente), 1, pArch) == 1)
    {
        if (aux.id > id) id = aux.id;
    }
    fclose(pArch);

    return id + 1;  // Retorna el siguiente ID disponible
}

// Da de alta un nuevo cliente, verificando que no exista por DNI
void altaCliente()
{
    printf("----------------------------------------------\n");
    printf("            ALTA DE NUEVO CLIENTE             \n");
    printf("----------------------------------------------\n");

    char dni[10];
    printf("Ingrese DNI del cliente: ");
    fflush(stdin);
    gets(dni);

    // Verifica existencia por DNI
    if (existeClientePorDNI(dni))
    {
        printf("Ya existe un cliente con ese DNI. No se puede dar de alta.\n");
    }
    else
    {
        stCliente c = cargarUnCliente();
        strcpy(c.dni, dni); // Copia el DNI capturado

        FILE *pArch = fopen("clientes.dat", "ab");
        if (pArch)
        {
            fwrite(&c, sizeof(stCliente), 1, pArch);
            fclose(pArch);
            printf("Cliente dado de alta correctamente.\n");
        }
    }
}

// Da de baja a un cliente (logica de "soft delete")
void bajaCliente(char dni[])
{
    stCliente c;
    FILE *src = fopen("clientes.dat", "rb");
    FILE *dst = fopen("clientesInactivos.dat", "ab");
    FILE *temp = fopen("temp.dat", "wb");

    // Si se abrieron los archivos correctamente
    if (src && dst && temp)
    {
        while(fread(&c, sizeof(stCliente), 1, src) == 1)
        {
            if (strcmp(c.dni, dni) == 0)
            {
                c.eliminado = 1;  // Marca como eliminado
                fwrite(&c, sizeof(stCliente), 1, dst);  // Guarda en archivo de inactivos
            }
            else
            {
                fwrite(&c, sizeof(stCliente), 1, temp); // Copia a archivo temporal
            }
        }

        fclose(src);
        fclose(dst);
        fclose(temp);

        // Reemplaza archivo original por el temporal
        remove("clientes.dat");
        rename("temp.dat", "clientes.dat");

        printf("Cliente dado de baja correctamente.\n");
    }
    else
    {
        printf("Error al abrir los archivos.\n");
    }
}

// Lista todos los clientes activos
void listarClientes()
{
    FILE *pArch = fopen("clientes.dat", "rb");
    stCliente c;

    if(pArch)
    {
        printf("Listado de Clientes:\n");
        while (fread(&c, sizeof(stCliente), 1, pArch) == 1)
        {
            if(c.eliminado == 0)
            {
                printf("ID: %d | Nombre: %s %s | DNI: %s | Email: %s\n",
                       c.id, c.nombre, c.apellido, c.dni, c.email);
            }
        }

        fclose(pArch);
    }
    else
    {
        printf("No hay clientes cargados aun.\n");
    }
}

// Modifica el email y telefono movil de un cliente activo por su DNI
void modificarCliente(char dni[])
{
    FILE *pArch = fopen("clientes.dat", "r+b");
    stCliente c;
    int encontrado = 0;

    if (pArch)
    {
        while (fread(&c, sizeof(stCliente), 1, pArch) == 1 && !encontrado)
        {
            if (strcmp(c.dni, dni) == 0 && c.eliminado == 0)
            {
                printf("Modificando datos de %s %s\n", c.nombre, c.apellido);

                printf("Nuevo email: ");
                do
                {
                    fflush(stdin);
                    gets(c.email);
                    if (!esEmailValido(c.email))
                        printf("Email invalido. Intente nuevamente: ");
                } while (!esEmailValido(c.email));

                printf("Nuevo telefono movil: ");
                fflush(stdin);
                gets(c.telefonoMovil);

                fseek(pArch, -(long)sizeof(stCliente), SEEK_CUR);
                fwrite(&c, sizeof(stCliente), 1, pArch);
                encontrado = 1;
            }
        }
        fclose(pArch);
    }

    if (!encontrado)
    {
        printf("Cliente no encontrado.\n");
    }
}

// Reactiva un cliente previamente dado de baja
void reactivarCliente(char dni[])
{
    FILE *pInactivos = fopen("clientesInactivos.dat", "rb");
    FILE *pTemp = fopen("temp.dat", "wb");
    FILE *pActivos = fopen("clientes.dat", "ab");
    stCliente c;
    int reactivado = 0;

    if (!pInactivos || !pTemp || !pActivos)
    {
        printf("Error al abrir los archivos.\n");
        return;
    }

    while (fread(&c, sizeof(stCliente), 1, pInactivos) == 1)
    {
        if (strcmp(c.dni, dni) == 0 && c.eliminado == 1)
        {
            c.eliminado = 0;
            fwrite(&c, sizeof(stCliente), 1, pActivos);
            reactivado = 1;
        }
        else
        {
            fwrite(&c, sizeof(stCliente), 1, pTemp);
        }
    }

    fclose(pInactivos);
    fclose(pTemp);
    fclose(pActivos);

    remove("clientesInactivos.dat");
    rename("temp.dat", "clientesInactivos.dat");

    if(reactivado)
    {
        printf("Cliente reactivado correctamente y movido a clientes.dat.\n");
    }
    else
    {
        printf("No se encontro un cliente eliminado con ese DNI.\n");
    }
}

// Lista clientes que estan marcados como eliminados (inactivos)
void listarClientesInactivos()
{
    FILE *pInactivos = fopen("clientesInactivos.dat", "rb");
    stCliente c;

    if (pInactivos)
    {
        printf("Listado de Clientes Inactivos:\n");
        while (fread(&c, sizeof(stCliente), 1, pInactivos) == 1)
        {
            printf("ID: %d | Nombre: %s %s | DNI: %s | Email: %s\n",
                   c.id, c.nombre, c.apellido, c.dni, c.email);
        }
        fclose(pInactivos);
    }
    else
    {
        printf("No se encontro el archivo de inactivos.\n");
    }
}

// Verifica si un cliente existe y esta activo mediante su DNI
int existeClientePorDNI(char dni[])
{
    FILE *pArch = fopen("clientes.dat", "rb");
    stCliente c;
    int existe = 0;

    if (pArch)
    {
        while (fread(&c, sizeof(stCliente), 1, pArch) == 1 && !existe)
        {
            if (strcmp(c.dni, dni) == 0 && c.eliminado == 0)
            {
                existe = 1;
            }
        }
        fclose(pArch);
    }

    return existe;
}

// Busca clientes activos por apellido (ignora mayusculas/minusculas)
void buscarClientesPorApellido() {
    char apellidoBuscado[50];
    stCliente c;
    int encontrados = 0;

    printf("Ingrese el apellido del cliente a buscar: ");
    fflush(stdin);
    gets(apellidoBuscado);

    FILE *pArch = fopen("clientes.dat", "rb");

    if (pArch) {
        printf("\n--- Resultados de busqueda por apellido: %s ---\n", apellidoBuscado);
        while (fread(&c, sizeof(stCliente), 1, pArch) == 1) {
            if (c.eliminado == 0 && strcmpi(c.apellido, apellidoBuscado) == 0) {
                mostrarCliente(c);
                encontrados = 1;
            }
        }
        fclose(pArch);

        if (!encontrados) {
            printf("No se encontraron clientes con ese apellido.\n");
        }
    } else {
        printf("No se pudo abrir el archivo de clientes.\n");
    }
}

// Busca clientes por ID
void buscarClientesPorId() {
    int idBuscado = 0;
    stCliente c;
    int encontrados = 0;

    printf("Ingrese el ID a buscar: ");
    fflush(stdin);
    scanf("%d", &idBuscado);

    FILE *pArch = fopen("clientes.dat", "rb");

    if (pArch) {
        printf("\n--- Resultados de busqueda por id: %d ---\n", idBuscado);
        while (fread(&c, sizeof(stCliente), 1, pArch) == 1) {
            if (c.eliminado == 0 && c.id == idBuscado) {
                mostrarCliente(c);
                encontrados = 1;
            }
        }
        fclose(pArch);

        if (!encontrados) {
            printf("No se encontraron clientes con ese ID.\n");
        }
    } else {
        printf("No se pudo abrir el archivo de clientes.\n");
    }
}
void buscarClientePorDNI()
{
    char dni[10];
    stCliente c;
    int encontrado = 0;

    printf("Ingrese el DNI del cliente a buscar: ");
    fflush(stdin);
    gets(dni);

    FILE *pArch = fopen("clientes.dat", "rb");

    if (pArch)
    {
        while (fread(&c, sizeof(stCliente), 1, pArch) == 1 && !encontrado)
        {
            if (strcmp(c.dni, dni) == 0 && c.eliminado == 0)
            {
                mostrarCliente(c);  // Muestra el cliente con esa funcion existente
                encontrado = 1;
            }
        }
        fclose(pArch);

        if (!encontrado)
        {
            printf("No se encontro un cliente activo con ese DNI.\n");
        }
    }
    else
    {
        printf("No se pudo abrir el archivo de clientes.\n");
    }
}
