#include "bspi.h"

int main(){

	bspi_t master[1] = {};		//MASTER
	bspi_t slaves[3] = {};		//SLAVES.
 	resp_st_t status = {};

	init_t(&master,status,  &slaves);		//MASTER configurado.

	while(1){
 		switch (status.estado){
        	case MOSI:	status = f_MOSI(status, &master);
											break;
					case SDI:		status = f_SDI(status, &master,  &slaves);
            					break;
       	 	case SDO: 	status = f_SDO(status, &master,  &slaves);
											break;
        	case MISO: 	status = f_MISO(status,  &master);
											break;
      	}
	}

	 return 0;
}
