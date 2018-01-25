/*
TP3 Mathieu Marchand et Ines Jussaume
*/

/*Table a etat :
 *
 * 
 * */

#include <avr/io.h>
#include <util/delay.h>

//#define F_CPU = 16000000

enum Etat{
    ETATETEINT,
    ETAT1,
    ETAT2,
    ETAT3,
    ETAT4,
    ETAT5,
    ETATALLUMER
};
 

bool antiRebond();

int main (){
	
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  bool allumer = false;
  while(true){
    if(!allumer){
      allumer = antiRebond();
    }else {//si allumer
      PINA = 1;//0000001   
      _delay_ms(100);
      PINA = 2;
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
