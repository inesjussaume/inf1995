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


enum Etat{ //énumétation de tous les états de la machine à état
	RELACHE_DEPART_ROUGE,
	PESE_AMBRE,
	RELACHE_VERT,
	PESE_ROUGE,
	RELACHE_ETEINT,
	PESE_VERT
};

void etatSuivant();
void initialisation();
bool estClique();

volatile Etat etat = RELACHE_DEPART_ROUGE;
volatile bool enTrainPeser = false;

ISR(INT0_vect) {
	// laisser un delai avant de confirmer la réponse du
	// bouton-poussoir: environ 30 ms (anti-rebond)
	//_delay_ms(30);
	if(estClique()){
		//enTrainPeser = true;
		etatSuivant();
		//PORTA = ROUGE;
		//PORTA = VERT;
		//etatSuivant();
		}
		
	
	
	//PORTA = ROUGE;
	// se souvenir ici si le cf récédente
	//'modifier ici'
	// Voir la note plus bas pour comprendre cette instruction et son rôle
	EIFR |= (1 << INTF0);
	
}


int main(){
	
	initialisation();
	
    while(true){
		
	
		//if(!estClique() && enTrainPeser){
			//enTrainPeser = false;
			//etatSuivant();
			//} 

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
void etatSuivant(){
	switch(etat){
		case RELACHE_DEPART_ROUGE:
			etat = PESE_AMBRE;
			break;
		case PESE_AMBRE:
			etat = RELACHE_VERT;
			PORTA = VERT;
			break;
		case RELACHE_VERT:
			etat = PESE_ROUGE;
			PORTA = ROUGE;
			break;
		case PESE_ROUGE:
			etat = RELACHE_ETEINT;
		    PORTA = ETEINT;
			break;
		case RELACHE_ETEINT:
		     etat = PESE_VERT;
		     PORTA = VERT;
		       break;
		case PESE_VERT:
			etat = RELACHE_DEPART_ROUGE;
			PORTA=ROUGE;
	}

}

void initialisation() {
	cli(); //pas d'interuption
	PORTA = ROUGE;
	DDRA = 0xff; //PORT A est en sortie
	DDRB = 0xff; //PORT B en sortie
	DDRC = 0xff; //PORT C en sortie
	DDRD = 0x00; //PORT D en entree
	EIMSK |= (1 << INT0); //INT0 = interuption 0
	EICRA |= (1<< ISC01); //external interupt control register A -- s'occupe des interruptions

	sei(); //peut reprendre les interuptions ici
}

bool estClique(){
	if(PIND & (1<<2)){
		_delay_ms(10);
		}
	if(PIND & (1<<2)){
		return true;
		}	
		
	return false;
	}

