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
	
	DDRA = 0xff; //PORT A est en sortie
	DDRB = 0xff; //PORT B en sortie
	DDRC = 0xff; //PORT C en sortie
	DDRD = 0x00; //PORT D en entree
	PORTA = ROUGE;
	int a = 1000, b = 0;
	while(true){
		b+=10;
		a-=10;	
		PORTA = ROUGE;	
		delay(a);
		PORTA = ETEINT;
		delay(b);			
	}
	
		
return 0;
}

void delay(int delay){
	for (int i = 0; i < delay; i++)
	{
		_delay_ms(1);
	}
	
	
	}
