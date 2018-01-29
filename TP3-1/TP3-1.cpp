/*
TP3 Mathieu Marchand 1894847 et Ines Jussaume 1900361
*/

/*Table a etat :
 
 ÉTAT PRÉSENT              ->     ENTRÉE          ->        ÉTAT SUIVANT
 
 ÉTAT_ÉTEINT               ->     appuyer         ->        ÉTAT1
 ÉTAT1                     ->     appuyer         ->        ÉTAT2
 ÉTAT2                     ->     appuyer         ->        ÉTAT3
 ÉTAT3                     ->     appuyer         ->        ÉTAT4
 ÉTAT4                     ->     appuyer         ->        ETATALLUMER
 ETATALLUMER               ->     délais 1s       ->        ÉTAT_ÉTEINT
 
 si l'entrée diffère de celle qui figure dans la table, l'état demeure à l'état actuel sauf pour ETATALLUMER qui allumera toujours la DEL pour une seconde
 
 * */

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU = 8000000

const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b00000001;
const uint8_t ROUGE = 0b00000010;

 

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
