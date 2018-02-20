/*
TP5 probleme 2
AUTEURS: Ines Jussaume 1900361 & Mathieu Marchand 1894847
*/
#define F_CPU (8000000)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b000000001;
const uint8_t ROUGE = 0b00000010;

const uint8_t SECONDE = 8000; //une seconde correspond a 8000 cycle de CPU
const uint8_t d_SECONDE = 800;//dixieme de seconde

volatile uint8_t couleur;
volatile bool minuterieExpiree=false;
volatile bool boutonPoussoir=false;

volatile long ds=0;
void etatSuivant();
void initialisation();
bool estClique();
void partirMinuterie(uint16_t duree);

volatile bool enTrainPeser = false;

ISR(INT0_vect) {
	
	EIFR |= (1 << INTF0);
	boutonPoussoir =true;
	
}

ISR(TIMER1_COMPA_vect){
	ds++;
	switch(ds){
			case 100:
				PORTA = ROUGE;
				break;
			case 101 :
				PORTA = ETEINT;
				break;
			case 111 :
				minuterieExpiree = true;
	}
}

int main(){
	
	initialisation();
	PORTA = ETEINT;
	partirMinuterie(800);
	
	
//--------------
	do {
		// attendre qu'une des deux variables soit modifiée
		// par une ou l'autre des interruptions.
	} while(!minuterieExpiree && !boutonPoussoir);
	// Une interruption s'est produite. Arrêter toute
	// forme d'interruption. Une seule réponse suffit.
	cli ();
	if(minuterieExpiree){
			PORTA = ROUGE;
	}else{
			PORTA = VERT;
	}

	// Verifier la réponse

	//'modifier ici'
	return 0;
}

void partirMinuterie(uint16_t duree){
	minuterieExpiree = false;
		
	
	//mode CTC du timer 1 avec horloge divisée par 1024
	// interruption après la durée spécifiée

	TCNT1 = 0;//compteur (0 a OCR1A)

	OCR1A = duree;

	//TCCR1A |= 

	TCCR1B |= ( 1 << (WGM12));
	TCCR1B |= ( 1 << (CS12));
	TCCR1B |= ( 1 << (CS10));
	TCCR1C = 0;
	
	TIMSK1 |= ( 1 << (OCIE1A));
}


void initialisation() {
	cli(); //pas d'interuption
	PORTA = ROUGE;
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

bool estClique(){
	if(PIND & (1<<2)){
		_delay_ms(10);
		}
	if(PIND & (1<<2)){
		return true;
		}	
		
	return false;
	}

