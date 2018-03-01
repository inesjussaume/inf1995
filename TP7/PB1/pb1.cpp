/*
TP7 probleme 1
AUTEURS: Ines Jussaume 1900361 & Mathieu Marchand 1894847
*/

#define F_CPU (8000000)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/********************************************************************************
 *	POSITION DES BRANCHEMENTS DES FILS SUR LA CARTE MERE
 *  DEL: elle est branchee sur les broches identifiees 1 et 2 du port B
 * 	PHOTORESISTANCE: le fil bleu est branche sur la broche identifiee 2 du port A 
 * 					et le brun sur la broche 1
 * 	GND VCC: le fil rouge est branche sur le VCC du port B et le noir sur le GND
 ********************************************************************************/
 
const uint8_t ETEINT = 0b00000000, VERT = 0b000000001, ROUGE = 0b00000010;

//temps en dixiemes de secondes
const uint8_t DELAIS_DS1 = 5, DELAIS_DS2 = 20, DELAIS_DS3 = 30, DELAIS_DS4 = 120; 

const uint16_t d_SECONDE = 800;//dixieme de seconde

//liste des minutries : 
volatile bool minuterieExpiree1=false, minuterieExpiree2 = false, minuterieExpiree3 = false, minuterieExpiree4 = false, minuterieExpiree5 = false;
volatile bool boutonPoussoirAppuye = false;
volatile bool enTrainPeser = false;
volatile long compteur_ds=1;
volatile long compteurTempsAppuye= 0;

/********************************************************************************
 *	FONCTIONS UTILISEES
 ********************************************************************************/

void initialisation();
bool estClique();
void partirMinuterie(uint16_t duree);
void reset();

/********************************************************************************
 *	FONCTION: ISR(INT0_vect)
 *  PARAM IN:  INT0_vect
 *  DESCRIPTION: si le bouton poussoir est appuye, interrompt le code 
 ********************************************************************************/

ISR(INT0_vect) {
	_delay_ms(30);
	boutonPoussoirAppuye = !boutonPoussoirAppuye;
	EIFR |= (1 << INTF0);
}

/********************************************************************************
 *	FONCTION: ISR(INT0_vect)
 *  PARAM IN:  INT0_vect
 *  DESCRIPTION: quand la minuterie CTC atteint OCR1A, il y a interruption et clear
 ********************************************************************************/

ISR(TIMER1_COMPA_vect){
	compteur_ds++;
	//1 sec = 10 compteur_ds
	if (compteur_ds == DELAIS_DS4) {
		minuterieExpiree1 = true;
	}
	
	if(minuterieExpiree1){
		
		if(compteur_ds == DELAIS_DS1){
			minuterieExpiree2 = true;
			}
		else if(compteur_ds == DELAIS_DS2){
			minuterieExpiree3 = true;
		}
		else if (compteur_ds ==(DELAIS_DS2 + compteurTempsAppuye/2)){
			minuterieExpiree4 = true;
		}
		else if(compteur_ds == (DELAIS_DS3 + compteurTempsAppuye/2)){
			minuterieExpiree5 = true;
		}
	}
}

/********************************************************************************
 *	MAIN
 ********************************************************************************/
 
int main(){
	initialisation();
	partirMinuterie(d_SECONDE);//compte une fois par dixième de seconde (10 fois par seconde)
	do {	
		if (boutonPoussoirAppuye) 
		{
			reset(); //compteur = 0 et bools des minuterieExpireeN = false
			while (boutonPoussoirAppuye && !minuterieExpiree1)
			{
			}
			
			minuterieExpiree1 = true;
			compteurTempsAppuye = compteur_ds;
			compteur_ds = 0;
		}
		
		if (compteur_ds == 0) {

			while (!minuterieExpiree2)//DEL verte clignote
			{
				PORTB = VERT;
				_delay_ms(30);
				PORTB = ETEINT;
			}

			while (!minuterieExpiree3)//Programme attend 2 secondes
			{
			}
		
			while (!minuterieExpiree4)//DEL rouge clignote 2 fois par seconde pour compteur/2
			{
				if(compteur_ds%5 == 0){
					PORTB = ROUGE;
					_delay_ms(30);
					PORTB = ETEINT;
				}
			}

			PORTB = VERT;
			
			while (!minuterieExpiree5)
			{
			}
			
			PORTB = ETEINT;
		}
	}while(true);
	
	return 0;
}

/********************************************************************************
 *	FONCTION: partirMinuterie(uint16_t duree)
 *  PARAM IN:  uint16_t duree de la minuterie
 *  DESCRIPTION: initialisation de la duree de la minuterie et de ses registres
 ********************************************************************************/

void partirMinuterie(uint16_t duree){	
	
	//mode CTC du timer 1 avec horloge divisée par 1024
	// interruption après la durée spécifiée

	TCNT1 = 0;//compteur (0 a OCR1A)

	OCR1A = duree;

	//TCCR1A |= 
	//initialisation des bits des registres TIMER CONTROL REGISTER
	TCCR1B |= ( 1 << (WGM12));
	TCCR1B |= ( 1 << (CS12));
	TCCR1B |= ( 1 << (CS10));
	TCCR1C = 0;
	
	TIMSK1 |= ( 1 << (OCIE1A));
}

/********************************************************************************
 *	FONCTION: initialisation() 
 *  DESCRIPTION: la fonction initialise le port A en entree et le port B en sortie
 * 				active les interruptions 
 ********************************************************************************/

void initialisation() {
	
	cli(); //pas d'interuption
	
	DDRA = 0x00; //PORT A est en entree
	DDRB = 0xff; //PORT B en sortie

	EIMSK |= (1 << INT0); //INT0 = interuption 0	
	EICRA &= ~(1 << ISC01);//0 au bit 00000010
	EICRA |= (1<< ISC00);//1 au bit 00000000
	//total = XXXXXX01
	
	sei(); //peut reprendre les interuptions ici
}

/********************************************************************************
 *	FONCTION: estClique()
 *  SORTIE: bool 
 *  DESCRIPTION: la fonction regarde si le bouton poussoir est appuye et gere les rebonds
 ********************************************************************************/
 
bool estClique(){
	if(~PIND & (1<<2)){
		_delay_ms(10);
		}
	if(~PIND & (1<<2)){
		return true;
		}	
		
	return false;
	}
	
/********************************************************************************
 *	FONCTION: reset() 
 *  DESCRIPTION: la fonction reinitialise les booleens des minuteries pour repartir le programme
 * 				et remet le compteur de dixiemes de secondes a 0
 ********************************************************************************/
	
void reset(){
	minuterieExpiree1 = false;
	minuterieExpiree2 = false;
	minuterieExpiree3 = false; 
	minuterieExpiree4 = false; 
	minuterieExpiree5 = false;
	compteur_ds=1;
}


