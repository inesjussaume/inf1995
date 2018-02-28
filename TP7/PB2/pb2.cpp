/*
TP7 probleme 2
AUTEURS: Ines Jussaume 1900361 & Mathieu Marchand 1894847
*/
#define F_CPU (8000000)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <can.h>


const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b000000001;
const uint8_t ROUGE = 0b00000010;

const uint8_t SECONDE = 8000; //une seconde correspond a 8000 cycle de CPU
const uint8_t d_SECONDE = 800;//dixieme de seconde

void initialisation();

int main(){
	
	initialisation();
	PORTA = ROUGE;
	return 0;
}


void initialisation() {
	cli(); //pas d'interuption
	DDRA = 0xff; //PORT A est en sortie
	DDRB = 0xff; //PORT B en sortie
	DDRC = 0xff; //PORT C en sortie
	DDRD = 0x00; //PORT D en entree
	EIMSK |= (1 << INT0); //INT0 = interuption 0
	EICRA &= ~(1 << ISC01);//0 au bit 00000010
	EICRA |= (1<< ISC00);//1 au bit 00000000
	//total = XXXXXX01
	sei(); //peut reprendre les interuptions ici
}


