/*
TP7 probleme 2
AUTEURS: Ines Jussaume 1900361 & Mathieu Marchand 1894847
*/

#define F_CPU (8000000)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <can.h>

/********************************************************************************
 *	POSITION DES BRANCHEMENTS DES FILS SUR LA CARTE MERE
 *  DEL: elle est branchee sur les broches identifiees 1 et 2 du port B
 * 	PHOTORESISTANCE: le fil bleu est branche sur la broche identifiee 2 du port A 
 * 					et le brun sur la broche 1
 * 	GND VCC: le fil rouge est branche sur le VCC du port B et le noir sur le GND
 ********************************************************************************/
 
const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b000000001;
const uint8_t ROUGE = 0b00000010;
const uint8_t PHOTORESISTANCE = OCF1B;

//seuils d'intensite lumineuse pour lectures de la photoresistance
const uint8_t SEUIL_VERT = 100;
const uint8_t SEUIL_ROUGE = 250;

/********************************************************************************
 *	FONCTIONS UTILISEES
 ********************************************************************************/

void initialisation();

//convertir le signal de lecture à 16 bits en signal de 10 bits
uint8_t conversionLecture(can& signalCapteur, uint8_t position);

/********************************************************************************
 *	MAIN
 ********************************************************************************/

int main(){
	
	initialisation();
    can signalCapteur = can(); //aller chercher le signal renvoye par la photoresistance
    uint16_t intensiteLumiere = 0;
    
    while (true) {
        
        //prend la valeur retournée par la photorésiatance et la convertit 
        intensiteLumiere = signalCapteur.lecture(0);
        intensiteLumiere = intensiteLumiere >> 0x2;
        
        if (intensiteLumiere <= SEUIL_VERT) { //VERT
            PORTB = VERT;
        }
        else if (intensiteLumiere > SEUIL_VERT && intensiteLumiere < SEUIL_ROUGE) { //AMBRE
            PORTB = ROUGE;
            _delay_ms(10);
            PORTB = VERT;
            _delay_ms(10);
        }
        else { //ROUGE
            PORTB = ROUGE;
        }
    }

	return 0;
}

/********************************************************************************
 *	FONCTION: initialisation() 
 *  DESCRIPTION: la fonction initialise le port A en entree et le port B en sortie
 ********************************************************************************/

void initialisation() {

	DDRA = 0x00; //PORT A est en entree
	DDRB = 0xff; //PORT B en sortie
}
/********************************************************************************
 *	FONCTION: conversionLecture(can& signalCapteur, uint8_t position) 
 *  PARAM IN: can& adresse de la lecture 16 bits a convertir en 10 bits
 * 			  uint8_t position de laquelle on veut debuter la conversion 
 *  SORTIE: signal a 10 bits 
 *  DESCRIPTION: la fonction prend en entree le signal a 16 bits envoye par la photoresistance
 * 				et le converti en signal a 10 bits qu'elle renvoit en sortie 
 ********************************************************************************/

uint8_t conversionLecture(can& signalCapteur, uint8_t position){
	
    return signalCapteur.lecture(position-1) >> 2;
}

/*

FONCTIONS DONNEES AU LABORATOIRE PAR PHILIPPE CARPHIN

void transmmit_UART(uint8_t byte)

void transmmit_UART_str(uint8_t * str){
    uint8_t c;
    uint8_t *p = str;
    while ((c=*p++)!='10'){
		UART_transmit(c);
    }
}

void transmmit_UART_number(uint16_t n){
    uint8_t buff[100];
    sprintf(buff, "number is %u\n");
    transmmit_UART_str(buff);
}
*/




