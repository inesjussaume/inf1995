/*
TP3 probleme 2
*/

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU = 8000000;
///

const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b000000001;
const uint8_t ROUGE = 0b00000010;

enum Etat{
	RELACHE_DEPART_ROUGE,
	PESE_AMBRE,
	RELACHE_VERT,
	PESE_ROUGE,
	RELACHE_ETEINT,
	PESE_VERT
};

bool antiRebond();
void etatSuivant(Etat &etatActuel);

int main(){
	DDRA = 0xff; //PORT A est en sortie
	DDRB = 0xff; //PORT B en sortie
	DDRC = 0xff; //PORT C en sortie
	DDRD = 0x00; //PORT D en entree
	bool enTrainPeser = false;
	Etat etat = RELACHE_DEPART_ROUGE;
	PINA = ROUGE ;
	
while(true){

	if(etat == PESE_AMBRE){
	PORTA = ROUGE;
	_delay_ms(100);
	PORTA = VERT;
	_delay_ms(100);
	}
		
	if(antiRebond() && !enTrainPeser){
	enTrainPeser = true;
	etatSuivant(etat);
	}

	if(!antiRebond() && enTrainPeser){
	enTrainPeser = false;
	etatSuivant(etat);	
	}
		
}

return 0;
}

void etatSuivant(Etat &etatActuel){
	switch(etatActuel){
		case RELACHE_DEPART_ROUGE:
			etatActuel = PESE_AMBRE;
			break;
		case PESE_AMBRE:
			etatActuel = RELACHE_VERT;
			PORTA = VERT;
			break;
		case RELACHE_VERT:
			etatActuel = PESE_ROUGE;
			PORTA = ROUGE;
			break;
		case PESE_ROUGE:
			etatActuel = RELACHE_ETEINT;
		    PORTA = ETEINT;//pour eteindre (point d'interrogation
			break;
		case RELACHE_ETEINT:
		     etatActuel = PESE_VERT;
		     PORTA = VERT;
		       break;
		case PESE_VERT:
			etatActuel = RELACHE_DEPART_ROUGE;
			PORTA=ROUGE;
	
	}

}


bool antiRebond(){
if(PIND & _BV(2)){//si le bouton est active
      _delay_ms(10);
      if(PIND & (1 << 2)){//si le bouton est toujours /////active apres 1 sec
         return true;
      }
    }
    return false;
}
