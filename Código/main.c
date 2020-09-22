#include "bspi.h"

int main(){

	bspi_t master[1] = {};
	bspi_t slaves[3] = {};
 	resp_st_t status = {};

	init_t(&master,status,  &slaves);
	resp_st_t (*BSPI[4])(resp_st_t, bspi_t*, bspi_t*) = { f_MOSI, f_SDI, f_SDO, f_MISO };

	while(1){
		status = ( *BSPI[status.estado] )(status,&master,&slaves);
	}

	return 0;
}
