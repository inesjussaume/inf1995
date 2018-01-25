/*
TP3 Mathieu Marchand et Ines Jussaume
*/

/*Table a etat :
 *
 * 
 * */

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU = 8000000

const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b00000001;
const uint8_t ROUGE = 0b00000010;

enum Etat{
    ETATETEINT,
    ETAT1,
    ETAT2,
    ETAT3,
    ETAT4,
    ETAT5,
    ETATALLUMER
};
 

bool antiRebond();


int main (){
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode entree
	uint8_t etat = 0;
	bool enTrainPeser = false;

  while(true){


  if(antiRebond() && !enTrainPeser){
	enTrainPeser = true;
	etat++;
	}

if(!antiRebond()){//relache le bouton
enTrainPeser = false;

	
	}

if(etat ==5){
PORTA = ROUGE;
_delay_ms(1000);
PORTA = ROUGE;
_delay_ms(1000);
etat=0;
PORTA = ETEINT;
}

}
return 0;
}


bool antiRebond(){
      if(PIND & (1 << 2)){//si le bouton est active
      _delay_ms(10);
      if(PIND & (1 << 2)){//si le bouton est toujours /////active apres 1 sec
         return true;
      }
    }
    return false;
}
