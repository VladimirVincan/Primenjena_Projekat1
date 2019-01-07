#include <stdio.h>
#include <stdlib.h>
#include<p30fxxxx.h>
#include "UART.h"
#include "timer.h"


_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF);

unsigned char tempRX;
unsigned int broj1,broj2;
int n = 0,x=54;
unsigned char buf[]="" ;

// POCETAK MAINA -------------------------------------------------------------------
int main(int argc, char** argv) {
    
    
    initUART1();

	while(1)
	{
        int num = 321;
        char snum[5]="NINA";

   
        RS232_putst(snum);
       
        for(broj1=0;broj1<3000;broj1++)
        for(broj2=0;broj2<1000;broj2++);
    }//od whilea

    return (EXIT_SUCCESS);
}// od maina

