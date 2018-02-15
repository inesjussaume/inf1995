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

volatile uint8_t couleur;
volatile bool minuterieExpiree=false;
volatile bool boutonPoussoir=false;

void etatSuivant();
void initialisation();
bool estClique();

volatile bool enTrainPeser = false;

void delais_dS(uint8_t temps_S);

ISR(INT0_vect) {
	boutonPoussoir=true;
	
	EIFR |= (1 << INTF0);
}

ISR(){
	minuterieExpiree=true;
}

int main(){
	
	initialisation();
	delais_dS(100);
	PORTA = ROUGE;
	delais_dS(1);
	PORTA = ETEINT;
	
	partirMinuterie();
	
	do {
		// attendre qu'une des deux variables soit modifiée
		// par une ou l'autre des interruptions.
	} while (!minuterieExpiree && !boutonPoussoir);
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
	partirMinuterie = false;
	//mode CTC du timer 1 avec horloge divisée par 1024

	// interruption après la durée spécifiée

	TCNT1 = 1 ;

	OCR1A = duree;

	TCCR1A |= ( 1 << (CS12)));
	TCCR1A |= ( 1 << (CS10)));
	

	TCCR1B = 'modifier ici' ;

	TCCR1C = 0;
	
	TIMSK1 = 'modifier ici' ;
}

void delais_dS(uint8_t temps_dS){
	for (int i = 0; i < temps_dS; i++){
			_delay_ms(100);
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
	
	EICRA &= ~(1 << ISC01);//0 au bit 00000010
	EICRA |= (1<< ISC00);//1 au bit 00000000
	//total = XXXXXX01
	
	//EICRA |= (1<< ISC00);
	
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

