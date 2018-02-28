/*
TP7 probleme 2
AUTEURS: Ines Jussaume 1900361 & Mathieu Marchand 1894847
*/
#define F_CPU (8000000)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <can.h>

// diode électroluminescente sur PORTA
const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b000000001;
const uint8_t ROUGE = 0b00000010;

const uint8_t SECONDE = 8000; //une seconde correspond a 8000 cycle de CPU
const uint8_t d_SECONDE = 800;//dixieme de seconde

//seuils d'insent lumineuse pour lectures de la photoresistance
const uint8_t SEUIL_VERT = 50;
const uint8_t SEUIL_ROUGE = 100;

//àphotoresistance est branchee sur le PORTA
const uint8_t PHOTORESISTANCE = 3;

void initialisation();

//convertir le signal de lecture à 16 bits en signal de 10 bits
uint8_t conversionLecture(can& conversion, uint8_t position);



int main(){
	
	initialisation();
    can conversion = can();
    uint8_t intensiteLumiere = 0;
    
    while (true) {
        
        //prend la valeur retournée par la photorésiatance
        intensiteLumiere = conversionLecture(conversion, PHOTORESISTANCE);
        
        if (intensiteLumiere <= SEUIL_VERT) { //VERT
            PORTA = VERT;
        }
        else if (intensiteLumiere > SEUIL_VERT && intensiteLumiere < SEUIL_ROUGE) { //AMBRE
            PORTA = ROUGE;
            _delay_ms(10);
            PORTA = VERT;
            _delay_ms(10);
        }
        else { //ROUGE
            PORTA = ROUGE;
        }
    }

	return 0;
}


void initialisation() {
	PORTA = ROUGE;
	DDRA = 0xff; //PORT A est en sortie
	DDRB = 0xff; //PORT B en sortie
	DDRC = 0xff; //PORT C en sortie
	DDRD = 0x00; //PORT D en entree
}

uint8_t conversionLecture(can& conversion, uint8_t position){
    return conversion.lecture(position-1) >> 2;
}

