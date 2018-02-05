#define F_CPU (8000000)
#include <avr/io.h>
#include <util/delay.h>



const uint8_t ETEINT = 0b00000000;
const uint8_t AVANCE = 0b00000101;
const uint8_t RECULE = 0b00001010;

void delay_us(int delay);
void nextStep();

int a = 0;
int b = 0;

const double rapport0 = 0.0;
const double rapport25 = 0.25;
const double rapport50 = 0.50;
const double rapport75 = 0.75;
const double rapport100 = 1.00;

enum Etat {
	rapport_0,
	rapport_25,
	rapport_50,
	rapport_75,
	rapport_100,
	rapport_0_2,
	rapport_25_2,
	rapport_50_2,
	rapport_75_2,
	rapport_100_2
	};
	
Etat step = rapport_0;

	int period_us60Hz = 16667;
    int period_us400Hz = 2500;
    
 bool isDone = false;   
int main(){
	// période = inverse de la fréquence? donc si fréquence 1 = 60s^-1, période = 16 667us et fréquence 2 = 400Hz, période 2 = 2500us
	DDRA = 0xff; //PORT A en sortie
	DDRB = 0xff; //PORT B en sortie
	DDRC = 0xff; //PORT C en sortie
	DDRD = 0x00; //PORT D en entree
	PORTB = AVANCE;
	int temps = 70;
	PORTA = AVANCE;
	while(!isDone){
		if(temps > 0){
			temps--;
			PORTB = AVANCE;	
			delay_us(a);
			PORTB = ETEINT;
			delay_us(b-a);
		}else{
			nextStep();
			temps =70;
			}			
	}
	
return 0;
}
/********************************************************************************
 *  delay()
 *  la fonction prend en charge la gestion des delais et prend en paramètre un int
 *  qui sera utilisé pour la longueur du délais voulu
 ********************************************************************************/
void delay_us(int nb_us){
	while(nb_us-- >=0)
	{
		_delay_us(1);
	}
} 

void nextStep(){
		switch(step){
			case rapport_0:
				step = rapport_25;
				a = rapport25 * period_us60Hz;
				b = period_us60Hz;
				//break;
			case rapport_25:
				step = rapport_50;
				a = rapport50 * period_us60Hz;
				b = period_us60Hz;
				//break;
			case rapport_50:
				step = rapport_75;
				a = rapport75 * period_us60Hz;
				b = period_us60Hz;
				//break;
			case rapport_75:
				step = rapport_100;
				a = rapport100 * period_us60Hz;
				b = period_us60Hz;
				//break;
			case rapport_100:
				PORTA = RECULE;
				step = rapport_0_2;
				a = rapport100 * period_us400Hz;
				b = period_us400Hz;
				//break;
			case rapport_0_2:
				step = rapport_25_2;
				a = rapport25 * period_us400Hz;
				b = period_us400Hz;
				break;
			case rapport_25_2:
				step = rapport_50_2;
				a = rapport50 * period_us400Hz;
				b = period_us400Hz;
				break;
			case rapport_50_2:
				step = rapport_75_2;
				a = rapport75 * period_us400Hz;
				b = period_us400Hz;
				break;
			case rapport_75_2:
				step = rapport_100_2;
				a = rapport100 * period_us400Hz;
				b = period_us400Hz;	
				break;
			case rapport_100_2:
				PORTA = ETEINT;
				isDone =true;
				break;
			}
	}
