/*La DEL est branche sur la premiere PIN du PORT A
 *
 *  
*/

#define F_CPU (8000000)
#include <avr/io.h>
#include <util/delay.h>


///

const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b000000001;
const uint8_t ROUGE = 0b00000010;

void delay_us(int delay);

int main(){
	
	int period_us = 1000;
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
		delay_us(a);
		PORTA = ETEINT;
		delay_us(b);			
	}
	
		
return 0;
}
/********************************************************************************
 *  delay()
 *  la fonction prend en charge la gestion des delais et prend en paramètre un int
 *  qui sera utilisé pour la longueur du délais voulu
 ********************************************************************************/
void delay_us(int nb_us){
	while(nb_us-- >=0)
	{
		_delay_us(1);
	}
}
