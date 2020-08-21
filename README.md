# TP-Proyecto-Info-II
Repositorio para el Proyecto de Informática II 2020

# Descripción
El tema elegido para el proyecto es el Protocolo de Comunicación SPI.

## **PROTOCOLO DE COMUNICACIÓN SPI:**

El Bus SPI (Serial Peripheral Interface) es un estándar de comunicaciones, usado mayormente para la transferencia de información entre circuitos integrados en equipos electrónicos, en distancias cortas y a alta velocidad, que aceptan un flujo de bits serie regulado por un clock.

Bajo el uso de este protocolo, el equipo que maneja el clock es conocido como **Master** y cualquier equipo que sea habilitado por él para establecer una comunicación será nombrado como **Slave**.

### **Operación:**

El SPI es un protocolo sincrónico. La sincronización y la transmisión de datos se realizan por medio de 4 señales:

* SCLK (Clock): Es el pulso que marca la sincronización. Con cada pulso de este reloj, se lee o se envía un bit. También llamado TAKT (en alemán).

* MOSI (Master Output Slave Input): Salida de datos del Master y entrada de datos al Esclavo. También llamada SIMO o SDI (Slave Data In) en el equipo Slave.

* MISO (Master Input Slave Output): Salida de datos del Esclavo y entrada al Master. También conocida por SOMI o SDO (Slave Data Out) en el equipo Slave.

* SS/Select: Para seleccionar un Esclavo, o para que el Master le diga al Esclavo que se active. También llamada SSTE o CS (Chip Select) en el e	quipo Slave.

![SPI con un Slave](C:/Users/Outlet/Documents/GitHub/TP-Proyecto-Info-II/SPI_1slave.jpg)

*Figura I: Conexión SPI para un Slave.*

![SPI con múltiples Slaves](C:/Users/Outlet/Documents/GitHub/TP-Proyecto-Info-II/SPI_3slave.jpg)

*Figura II: Conexión SPI para múltiples Slaves.*

La Cadena de bits es enviada de manera sincrónica con los pulsos del clock, es decir con cada pulso, el Master envía un bit. Para que empiece la transmisión el Master baja la señal SSTE o SS/Select a nivel bajo, con esto el Slave se activa y empieza la transmisión, con un pulso de clock al mismo tiempo que el primer bit es leído.

### **Modos del SPI:**

Existen 4 diferentes modos en los que el Protocolo SPI puede ser inicializado. Esto es: los pulsos del clock pueden estar programados de manera que la transmisión del bit se realice de 4 maneras distintas. Los modos son determinados por el estado de:

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

  ![Ejemplo de Comunicación](C:/Users/Outlet/Documents/GitHub/TP-Proyecto-Info-II/ej_comm.jpg)
  
