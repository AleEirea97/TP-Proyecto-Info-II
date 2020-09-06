# TP-Proyecto-Info-II
Repositorio para el Proyecto de Informática II 2020

### Descripción:
El tema elegido para el proyecto es el Protocolo de Comunicación SPI.

## **PROTOCOLO DE COMUNICACIÓN SPI:**

<div style="text-align: justify">El Bus SPI (Serial Peripheral Interface) es un estándar de comunicaciones, usado mayormente para la transferencia de información entre circuitos integrados en equipos electrónicos, en distancias cortas y a alta velocidad, que aceptan un flujo de bits serie regulado por un clock.</div>


<div style="text-align: justify">Bajo el uso de este protocolo, el equipo que maneja el clock es conocido como <strong>Master</strong> y cualquier equipo que sea habilitado por él para establecer una comunicación será nombrado como <strong>Slave</strong>.</div>

### **Operación:**

El SPI es un protocolo sincrónico. La sincronización y la transmisión de datos se realizan por medio de 4 señales:

* **SCLK** (**Clock**): Es el pulso que marca la sincronización. Con cada pulso de este reloj, se lee o se envía un bit. También llamado TAKT (en alemán).

* **MOSI** (**Master Output Slave Input**): Salida de datos del Master y entrada de datos al Slave. También llamada SIMO o SDI (Slave Data In) en el equipo Slave.

* **MISO** (**Master Input Slave Output**): Salida de datos del Slave y entrada al Master. También conocida por SOMI o SDO (Slave Data Out) en el equipo Slave.

* **SS/Select**: Para seleccionar un Slave, o para que el Master le diga al Slave que se active. También llamada SSTE o CS (Chip Select) en el equipo Slave.

![SPI con un Slave](https://github.com/AleEirea97/TP-Proyecto-Info-II/blob/master/img/SPI_1slave.png)
*Figura I: Conexión SPI para un Slave.*

![SPI con múltiples Slaves](https://github.com/AleEirea97/TP-Proyecto-Info-II/blob/master/img/SPI_3slave.png)
*Figura II: Conexión SPI para múltiples Slaves.*

<div style="text-align: justify">La Cadena de bits es enviada de manera sincrónica con los pulsos del clock, es decir con cada pulso, el Master envía un bit. Para que empiece la transmisión el Master baja la señal SSTE o SS/Select a nivel bajo, con esto el Slave se activa y empieza la transmisión, con un pulso de clock al mismo tiempo que el primer bit es leído.</div>

### **Modos del SPI:**

<div style="text-align: justify">Existen 4 diferentes modos en los que el Protocolo SPI puede ser inicializado. Esto es: los pulsos del clock pueden estar programados de manera que la transmisión del bit se realice de 4 maneras distintas. Los modos son determinados por el estado de:</div>

* Fase del Clock (**CPHA**).
* Polaridad del Clock (**CPOL**).

**MODO 0:** CPOL = 0 / CPHA: 0 -> 1.
El clock se inicializa en **nivel bajo** y la trasmisión se realiza cuando pasa a nivel alto (**Flanco de Subida**).

**MODO 1:**	CPOL = 0 / CPHA: 1 -> 0.
	El clock se inicializa en **nivel bajo** y la trasmisión se realiza cuando pasa de nivel alto a nivel bajo (**Flanco de Bajada**).

**MODO 2:**	CPOL = 1 / CPHA: 1 -> 0.
	El clock se inicializa en **nivel alto** y la trasmisión se realiza cuando pasa a nivel bajo (**Flanco de Bajada**).

**MODO 3:**	CPOL = 1 / CPHA: 0 -> 1.
	El clock se inicializa en **nivel alto** y la trasmisión se realiza cuando pasa de nivel bajo a nivel alto (**Flanco de Subida**).

  La siguiente imagen muestra un ejemplo de una comunicación usando el **Modo 0**:

  ![Ejemplo de Comunicación](https://github.com/AleEirea97/TP-Proyecto-Info-II/blob/master/img/ej_comm.png)

### **Diagrama de Estados:**

Se plantea un diagrama de estados del sistema tratado.

  ![Ejemplo de Comunicación](https://github.com/AleEirea97/TP-Proyecto-Info-II/blob/master/img/diagrama_std.png)

La máquina será simulada con 2 modos disponibles: **Modo 0** y **Modo 2**. Los estados son:

* **init_t:**		Estado inicial de la máquina. Configura al *Master* con el *modo* a utilizar para la trasmisión y la cantidad y habilitación de los *Slaves* utilizados.

* **MOSI:**		Estado del equipo *Master*. Se encarga de trasmitir al equipo *Slave* bit a bit de forma sincrónica con la señal de clock. Se trasmitirá 1 byte, o sea 8 veces.

* **SDI:**		Estado del equipo *Slave*. Se encarga de recibir la trasmisión del **MOSI** del *Master* de forma sincrónica con la señal de clock.

* **SDO:**		Estado del equipo *Slave*. Se encarga de trasmitir al equipo *Master* bit a bit de forma sincrónica con la señal de clock. Se trasmitirá 1 byte, o sea 8 veces.

* **MISO:**		Estado del equipo *Master*. Se encarga de recibir la trasmisión del **SDO** del *Slave* de forma sincrónica con la señal de clock.

#### Flags (Banderas) a  utilizar:

* **config_t**:		Configuración del equipo *Master*.

* **MHab_t**:		Habilitación pare trasmitir al equipo *Slave* configurado.

* **SHab_t**:		Indicación desde el *Slave* utilizado al *Master* que va a responder.

* **clock_fby**:		Indicación de fin de ciclo de clock **(El byte se ha trasmitido completamente)** para pasar de estados de trasmisión a estados de recepción.  

### Código: main.c:

<code>
#include "bspi.h"

int main(){

	bspi_t master[1] = {};		//MASTER
	bspi_t slaves[3] = {};		//SLAVES.
 	resp_st_t status = {};

	init_t(&master,status,  &slaves);		//MASTER configurado.

	while(1){
 		switch (status.estado){
        	case MOSI:	status = f_MOSI(status, &master);		break;
					case SDI:		status = f_SDI(status, &master,  &slaves);	break;
       	 	case SDO: 	status = f_SDO(status, &master,  &slaves);	break;
        	case MISO: 	status = f_MISO(status,  &master);	break;
      	}
	}
	return 0;
}
<code>
