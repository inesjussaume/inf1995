/*La DEL est branche sur la premiere PIN du PORT A
 *
 *  
*/
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU = 8000000;
///

const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b000000001;
const uint8_t ROUGE = 0b00000010;

void delay(int delay);

int main(){
	
	int period_us = 1000*2;
	DDRA = 0xff; //PORT A est en sortie
	DDRB = 0xff; //PORT B en sortie
	DDRC = 0xff; //PORT C en sortie
	DDRD = 0x00; //PORT D en entree
	PORTA = ROUGE;
	int a = period_us, b = 0;

	

	while(a >= 0){
	
		a-=1;
		b = period_us - a;	
		PORTA = ROUGE;	
		delay(a);
		PORTA = ETEINT;
		delay(b);			
	}
	
		
return 0;
}
/********************************************************************************
 *  delay()
 *  la fonction prend en charge la gestion des delais et prend en paramètre un int
 *  qui sera utilisé pour la longueur du délais voulu
 ********************************************************************************/
void delay(int delay){
	while(delay-- >=0)
	{
		_delay_us(1);
	}
	
	
}
