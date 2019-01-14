/*
 * Zadatak: servo motor i pir senzor
 * Kad pritisnemo taster RD0 motor se obrne za 90(zatvorena vrata), kad pritisnemo RD1 rotira se za -90(otvorena vrata i detektuje se senzor pokreta), 
 * kad pritisnemo RD2 postavi se na 0 stepeni, tj. poziciju poluotvorena vrata
 */

#include <p30fxxxx.h>
#include "tajmeri.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);
_FWDT(WDT_OFF);

//---------------------------------
unsigned int brojac_ms,stoperica,ms,sekund;
int stanje=0;
/*******************************************************************
//funkcija za kasnjenje u milisekundama
*********************************************************************/
void Delay_ms (int vreme)//funkcija za kasnjenje u milisekundama
	{
		stoperica = 0;
		while(stoperica < vreme);
	}

void __attribute__ ((__interrupt__)) _T2Interrupt(void) // svakih 1ms
{

		TMR2 =0;
     ms=1;//fleg za milisekundu ili prekid;potrebno ga je samo resetovati u funkciji

	brojac_ms++;//brojac milisekundi
    stoperica++;//brojac za funkciju Delay_ms

    if (brojac_ms==1000)//sek
        {
          brojac_ms=0;
          sekund=1;//fleg za sekundu
		 } 
	IFS0bits.T2IF = 0; 
       
}

void main (void) 
{
    ADPCFGbits.PCFG5=1;//defini?emo da pin B5 nije analogni vec digitalni
    TRISBbits.TRISB5=0;//konfigurisemo kao izlaz

	TRISDbits.TRISD0=1;//konfigurisemo kao izlaz
	TRISFbits.TRISF6=1;//konfigurisemo kao izlaz
    TRISDbits.TRISD2=1;//konfigurisemo kao izlaz
    


Init_T2();
//	Init_T1();
//	Init();

	while(1)
	{
        
        if(PORTDbits.RD0==1)
        {
		LATBbits.LATB5=1; //PWM signal na RB5
		Delay_ms (20); //vrijednosti u mikrosekundama
        LATBbits.LATB5=0;
        Delay_ms (1800);
        LATBbits.LATB5=1;
	//	LATDbits.LATD0=~LATDbits.LATD0;	
       }
        LATFbits.LATF6=0;
        if(PORTFbits.RF6==1){//detekcija PIR senzora na RF6, vrata se otvaraju
           if(stanje<110){
              stanje++;
           }
            else 
                stanje=0;
            if(stanje==100){ //staviti brojac koji ce mjkeriti da je proslo pola sekunde i onda ce raditi kako treba
                LATBbits.LATB5=1;
                Delay_ms(190);
                LATBbits.LATB5=0;
                Delay_ms (400);
                LATBbits.LATB5=1;
            }
        }
	//	LATDbits.LATD0=~LATDbits.LATD0;	
        
        if(PORTDbits.RD2==1){
		LATBbits.LATB5=1;
		Delay_ms (100);
        LATBbits.LATB5=0;
        Delay_ms (190);
        LATBbits.LATB5=1;
		LATDbits.LATD0=~LATDbits.LATD0;	
        }
//        
//               LATBbits.LATB5=0;
	}//while(1)



}//main


