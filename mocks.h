#ifndef MOCKS_H_INCLUDED
#define MOCKS_H_INCLUDED

void cargaNombreRandom(char nombre[]);
void cargaApellidoRandom(char apellido[]);
void cargaDniRandom(char dni[]);
void cargaEmailRandom(char email[], char nombre[]);
void cargaTelefonoRandom(char telefono[]);
void cargaCliente2ArchivoRandom(char nombreArchivo[]);
void cargaCalleRandom(char calle []);
void cargaLocalidad (char localidad []);
void cargaProvinciaRandom (char provincia []);
void cargaCpostalRandom (char cPos []);
void cargaNumDomicilioRandom (char numeroDomicilio []);
stDomicilio cargaDomicilioRandom ();
stDomicilio cargaDomicilioRandom ();
void cargarDetalleSaldoNegativo(char detalle[]);
float cargarImporte();
int cargaDia();
int cargaMes();
int cargaAnio();
stMovimiento cargaMovimientosRandom();
int cargaMovimientosRandomEnArchi(char nombreArchivoMov[],char nombreArchivoCuen[], int idCuenta);
int cargaIdCuentaRandom(char nombreArchivo[]);
void cargaMilMovimientosRandomEnArchi(char nombreArchivoMov[], char nombreArchivoCuenta[]);

#endif // MOCKS_H_INCLUDED
