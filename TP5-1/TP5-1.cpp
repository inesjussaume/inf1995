/*
TP5 probleme 1
AUTEURS: Ines Jussaume 1900361 & Mathieu Marchand 1894847
*/
#define F_CPU (8000000)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b000000001;
const uint8_t ROUGE = 0b00000010;

volatile Etat etat = RELACHE_DEPART_ROUGE;

volatile bool enTrainPeser = false;

enum Etat{ //énumétation de tous les états de la machine à état
	RELACHE_DEPART_ROUGE,
	PESE_AMBRE,
	RELACHE_VERT,
	PESE_ROUGE,
	RELACHE_ETEINT,
	PESE_VERT
};

void etatSuivant(Etat &etatActuel);
void initialisation();


ISR('modifier ici') {
	// laisser un delai avant de confirmer la réponse du
	// bouton-poussoir: environ 30 ms (anti-rebond)
	_delay_loop_ms(30);
	// se souvenir ici si le bouton est pressé ou relâché
	'modifier ici'
		if (enTrainPeser) {
			
		}
		else
		{
			enTrainPeser = false;
		}
		
		// changements d'états tels que ceux de la
		// semaine précédente
		'modifier ici'
		// Voir la note plus bas pour comprendre cette instruction et son rôle
		EIFR |= (1 << INTF0);

}



int main(){
	initialisation();
	PINA = ROUGE ;
	
    while(true){

        if(etat == PESE_AMBRE){
            PORTA = ROUGE;
            _delay_ms(1);
            PORTA = VERT;
            _delay_ms(1);
            PORTA=ETEINT;
        }
    }

    return 0;
}

/********************************************************************************
 *  etatSuivant() prend en prarmètre l'état actuel et le modifie pour l'état suivant
 *  le switch détermine quel sera l'état suivant selon l'état actuel et allume ou étaint
 *  la del d'une certaine couleur
 ********************************************************************************/
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
		    PORTA = ETEINT;
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

void initialisation() {
	cli();

	DDRA = 0xff; //PORT A est en sortie
	DDRB = 0xff; //PORT B en sortie
	DDRC = 0xff; //PORT C en sortie
	DDRD = 0x00; //PORT D en entree

	EIMSK |= (1 << INT0);

	EICRA |= 'modifier ici';

	sei();
}

