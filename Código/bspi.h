#ifndef _HEADER_BUS_SPI_
#define _HEADER_BUS_SPI_

#include <stdio.h>
#include <windows.h>
#include <string.h>

/*ESTRUCTURAS Y VARIABLES*/

//ESTADOS.
typedef enum{
  MOSI = 0,
  SDI = 1,
  SDO = 2,
  MISO = 3
}estado_t;

//Estructura BYTE.
typedef struct{
	unsigned int B0:1;
	unsigned int B1:1;
	unsigned int B2:1;
	unsigned int B3:1;
	unsigned int B4:1;
	unsigned int B5:1;
	unsigned int B6:1;
	unsigned int B7:1;
}fbit_t;

//MODOS
typedef enum{
	modo0 = 0,
	modo2 = 2
}modo_t;

//SLAVES
typedef enum{
	slave1 = 0,
	slave2 = 1,
	slave3 = 2
}ss_t;

//HABILITADOR.
typedef enum{
	hab = 0,
	inhab = 1
}hab_t;

//BUS Selector/Habilitador.
typedef struct{
	modo_t modo;
	ss_t select;
	hab_t pmt;
}SSTE_t;

//BUS SPI.
typedef struct{
	fbit_t MOSI;
	fbit_t MISO;
	SSTE_t SSTE;
}bspi_t;

//Respuesta de Status.
typedef struct{
	estado_t estado;
	int m_clock;
	int s_clock;
	int a;
}resp_st_t;

/*FIN ESTRUCTURAS Y VARIABLES*/

/*PROTOTIPO DE FUNCIONES*/

/*Función gen_byte*/
/*
Parámetro: Campo de bits fbit_t, entero.
Retorno: Campo de bits fbit_t.
Se genera un byte (8 bits), se carga en el campo y se retorna.
*/
fbit_t gen_byte(fbit_t,int a);

/*Función txbyte*/
/*
Parámetros: Campo de bits fbit_t (Byte a trasmitir bit por bit), entero.
Retorno: Entero (Bit trasmitido).
Retorna el bit del byte dado que sea indicado por el entero dado.
*/
int txbyte(fbit_t,int);

/*Función rxbyte*/
/*
Parámetros: Campo de bits fbit_t (Byte a recibir bit por bit), entero (bit trasmitido), indice.
Retorno: Campo de bits modificado.
Retorna el byte con el bit indicado cargado por el bit recibido.
*/
fbit_t rxbyte(fbit_t,int,int);

/*Función Inicialización*/
/*
Parámetro: Estructura bspi_t, estructura resp_st_t, estructura bspi_t.
Retorno: No retorno.
Se encarga de leer la configuración del archivo .conf para configurar el Master.
*/
void init_t(bspi_t*, resp_st_t, bspi_t*);

//FUNCIONES DE ESTADO:
resp_st_t f_MOSI(resp_st_t, bspi_t*);

resp_st_t f_SDI(resp_st_t, bspi_t*, bspi_t*);

resp_st_t f_SDO(resp_st_t, bspi_t*, bspi_t*);

resp_st_t f_MISO(resp_st_t, bspi_t*);

/*FIN DE PROTOTIPO DE FUNCIONES*/

#endif
