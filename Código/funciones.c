#include "bspi.h"

fbit_t gen_byte(fbit_t byte, int c){

	int a,b,i;

	printf("\tBYTE a trasmitir:");

	for(i = 0; i < 8; i++){

		a = rand()%c;	//Depende del número que divide se creará un determinado byte.

		if(a > 5){
			b = 1;
			printf("1");
		}
		else{
			b = 0;
			printf("0");
		}

		switch(i){
			case 0:	byte.B7 = b;
				break;
			case 1:	byte.B6 = b;
				break;
			case 2:	byte.B5 = b;
				break;
			case 3:	byte.B4 = b;
				break;
			case 4:	byte.B3 = b;
				break;
			case 5:	byte.B2 = b;
				break;
			case 6:	byte.B1 = b;
				break;
			case 7:	byte.B0 = b;
				break;
		}
	}
	printf("\n");
	return byte;
}

int txbyte(fbit_t byte,int i){

	switch(i){
			case 0:	return byte.B7;
				break;
			case 1:	return byte.B6;
				break;
			case 2:	return byte.B5;
				break;
			case 3:	return byte.B4;
				break;
			case 4:	return byte.B3;
				break;
			case 5:	return byte.B2;
				break;
			case 6:	return byte.B1;
				break;
			case 7:	return byte.B0;
				break;
	}
}

fbit_t rxbyte(fbit_t byte,int a,int i){

	switch(i){
			case 0:	byte.B7 = a;
				break;
			case 1:	byte.B6 = a;
				break;
			case 2:	byte.B5 = a;
				break;
			case 3:	byte.B4 = a;
				break;
			case 4:	byte.B3 = a;
				break;
			case 5:	byte.B2 = a;
				break;
			case 6:	byte.B1 = a;
				break;
			case 7:	byte.B0 = a;
				break;
	}

	return byte;
}

void init_t(bspi_t *master, resp_st_t status, bspi_t *slaves){

	FILE *conf;
	int i;
	char *a,*p;
	char cadena[30], nModo[10] = "", nSlave[10] = "", nAcc[10] = "";
	char opc_modo[2][10] = {"modo0","modo2"};
	char opc_slave[3][10] = {"slave1","slave2","slave3"};
	char opc_acc[2][10] = {"hab","inhab"};

	conf = fopen("config_SPI.conf","rb");

	fgets(cadena, 30, conf);

	do{
		a = cadena;

		if( (*a) != '#' && strlen(a) >= 0){

			p = strchr(cadena, '\n');
			p--;
			*p = 0;

			for(i = 0; i < 2; i++){
				if( strcmp( cadena, opc_modo[i] ) == 0){
					switch(i){
						case 0:	strcpy(nModo, opc_modo[i]);		break;
						case 1:	strcpy(nModo, opc_modo[i]);		break;
					}
				}
			}

			for(i = 0; i < 3; i++){
				if( strcmp( cadena, opc_slave[i] ) == 0){
					switch(i){
						case 0:	strcpy(nSlave, opc_slave[i]);		break;
						case 1:	strcpy(nSlave, opc_slave[i]);		break;
						case 2:	strcpy(nSlave, opc_slave[i]);		break;
					}
				}
			}

			for(i = 0; i < 2; i++){
				if( strcmp( cadena, opc_acc[i] ) == 0){
					switch(i){
						case 0:	strcpy(nAcc, opc_acc[i]);		break;
						case 1:	strcpy(nAcc, opc_acc[i]);		break;
					}
				}
			}
		}

		fgets(cadena, 30, conf);

	}while( !feof(conf) );

	fclose(conf);

	if( strcmp( nModo,"modo0") == 0)
		master[0].SSTE.modo = modo0;
	if( strcmp( nModo,"modo2") == 0)
		master[0].SSTE.modo = modo2;

	if( strcmp( nSlave,"slave1") == 0)
		master[0].SSTE.select = slave1;
	if( strcmp( nSlave,"slave2") == 0)
		master[0].SSTE.select = slave2;
	if( strcmp( nSlave,"slave3") == 0)
		master[0].SSTE.select = slave3;

	if( strcmp( nAcc,"hab") == 0)
		master[0].SSTE.pmt = hab;
	if( strcmp( nAcc,"inhab") == 0)
		master[0].SSTE.pmt = inhab;

	master[0].MOSI = gen_byte(master[0].MOSI,12);		//CARGA DEL MOSI DEL MASTER
	slaves[master[0].SSTE.select].MISO = gen_byte(slaves[master[0].SSTE.select].MISO, 16);		//CARGA DEL MISO DEL SLAVE.

	status.m_clock = 0;
	status.s_clock = 0;
	status.estado = MOSI;		// Estado Inicializado.

	printf("Configuracion:\n");
	printf("MODO: %d\n",master[0].SSTE.modo);
	printf("SLAVE: %d\n",master[0].SSTE.select+1);
	printf("Acceso: %d\n",master[0].SSTE.pmt);
}

resp_st_t f_MOSI(resp_st_t status, bspi_t *master){

	if( status.s_clock > 7 ){
			status.m_clock = 0;
			status.s_clock = 0;

			Sleep(300);
			return status;
		}
	if(!master[0].SSTE.pmt){
		if(status.m_clock < 8){
			status.a = txbyte(master[0].MOSI, status.m_clock);
			printf("Bit trasmitido:%d\n", txbyte(master[0].MOSI,status.m_clock));
			status.estado = SDI;

			Sleep(300);
			return status;
		}
		if(status.m_clock >= 8){
			status.estado = SDI;

			Sleep(300);
			return status;
		}
	}

	if(master[0].SSTE.pmt){
		printf("El Slave elegido no se encuentra habilitado.\n");
		Sleep(2000);
	}
}

resp_st_t f_SDI(resp_st_t status, bspi_t *master, bspi_t *slaves){

	if( status.m_clock < 8 ){

		slaves[master[0].SSTE.select].MOSI = rxbyte(slaves[master[0].SSTE.select].MOSI, status.a, status.m_clock);
		status.estado = MOSI;
		status.m_clock++;
		Sleep(300);
		return status;
	}
	printf("BYTE recibido exitosamente en el SLAVE.\n");
	status.estado = SDO;

	printf("\tSlaves:\n");
	printf("\tSLAVE 1 - MOSI:%d\n",slaves[0].MOSI);
	printf("\tSLAVE 2 - MOSI:%d\n",slaves[1].MOSI);
	printf("\tSLAVE 3 - MOSI:%d\n",slaves[2].MOSI);
	Sleep(1000);

	return status;
}

resp_st_t f_SDO(resp_st_t status,bspi_t *master, bspi_t *slaves){

	if(status.s_clock < 8){
		status.a = txbyte(slaves[master[0].SSTE.select].MISO, status.s_clock);
		printf("Bit trasmitido:%d\n", txbyte(slaves[master[0].SSTE.select].MISO,status.s_clock));
		status.estado = MISO;

		Sleep(300);
		return status;
		}
	if(status.s_clock >= 8){
		status.estado = MISO;

		Sleep(300);
		return status;
	}
}

resp_st_t f_MISO(resp_st_t status, bspi_t *master){

	if( status.s_clock < 8 ){

		master[0].MISO = rxbyte(master[0].MISO, status.a, status.s_clock);
		status.estado = SDO;
		status.s_clock++;
		Sleep(300);
		return status;
	}
	printf("BYTE recibido exitosamente en el MASTER.\n");
	status.estado = MOSI;

	printf("\tMASTER - MISO:%d\n", master[0].MISO);
	Sleep(1000);


	return status;
}
