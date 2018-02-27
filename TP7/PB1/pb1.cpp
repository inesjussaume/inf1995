/*
TP7 probleme 1
AUTEURS: Ines Jussaume 1900361 & Mathieu Marchand 1894847
*/
#define F_CPU (8000000)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b000000001;
const uint8_t ROUGE = 0b00000010;

const uint16_t SECONDE = 8000; //une seconde correspond a 8000 cycle de CPU
const uint16_t d_SECONDE = 800;//dixieme de seconde
//liste des minutries : 
volatile bool minuterieExpiree1=false,
minuterieExpiree2=false,
minuterieExpiree3 = false, 
minuterieExpiree4 = false, 
minuterieExpiree5 = false;
volatile bool boutonPoussoirAppuye = false;

volatile long compteur_ds=1;
volatile long compteurTempsAppuye= 0;

void initialisation();
bool estClique();
void partirMinuterie(uint16_t duree);
void reset();


volatile bool enTrainPeser = false;

ISR(INT0_vect) {
	if(estClique())
	{
		boutonPoussoirAppuye=true;
	}
	else if(!estClique() && boutonPoussoirAppuye)
	{
		boutonPoussoirAppuye = false;
	}
	EIFR |= (1 << INTF0);
}

ISR(TIMER1_COMPA_vect){
	compteur_ds++;
	//1 sec = 10 compteur_ds
	if (compteur_ds == 120) {
		minuterieExpiree1 = true;
	}
	
	if(minuterieExpiree1){
		
		if(compteur_ds==5){
			minuterieExpiree2 = true;
			}
		else if(compteur_ds==20){
			minuterieExpiree3 = true;
		}
		else if (compteur_ds==20 + compteurTempsAppuye/2){
			minuterieExpiree4 = true;
			//compteurTempsAppuye = (20 + compteurTempsAppuye / 2);
		}
		else if(compteur_ds==30 + compteurTempsAppuye/2){
			minuterieExpiree5 = true;
	}
}
}

int main(){
	
	initialisation();
	partirMinuterie(800);//compte une fois par dixième de seconde (10 fois par seconde)
	do {	
		if (boutonPoussoirAppuye)
		{
			
			
			boutonPoussoirAppuye = true;
			while (boutonPoussoirAppuye && !minuterieExpiree1)
			{
				PORTA = ROUGE;
				PORTA = ETEINT;
			}
			minuterieExpiree1 = true;
			compteurTempsAppuye = compteur_ds;
			compteur_ds = 0;
		}
		
		if (compteur_ds == 0) {

			while (!minuterieExpiree2)//DEL verte clignote
			{
				PORTA = VERT;
				_delay_ms(30);
				PORTA = ETEINT;
			}

			while (!minuterieExpiree3)//Programme attend 2 secondes
			{
			
			}

			while (!minuterieExpiree4)//DEL rouge clignote 2 fois par seconde pour compteur/2
			{
				PORTA = ROUGE;
				_delay_ms(30);
				PORTA = ETEINT;
				_delay_ms(100);
				PORTA = ROUGE;
				_delay_ms(30);
				PORTA = ETEINT;
			}

			PORTA = VERT;
			while (!minuterieExpiree5)
			{

			}
			PORTA = ETEINT;
			reset();
			
		}
	
	} while(true);

	return 0;
}

void partirMinuterie(uint16_t duree){	
	
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
	if(~PIND & (1<<2)){
		_delay_ms(10);
		}
	if(~PIND & (1<<2)){
		return true;
		}	
		
	return false;
	}
	
void reset(){
	minuterieExpiree1=false;
	minuterieExpiree2=false;
	minuterieExpiree3 = false; 
	minuterieExpiree4 = false; 
	minuterieExpiree5 = false;
	boutonPoussoirAppuye = false;
	compteur_ds=1;
}


