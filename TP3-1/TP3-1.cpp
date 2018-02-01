/*
TP3 Mathieu Marchand 1894847 et Ines Jussaume 1900361
*/

/*Table a etat :
 
 ÉTAT PRÉSENT              ->     ENTRÉE          ->        ÉTAT SUIVANT
 
 ÉTAT_ÉTEINT               ->     appuyer         ->        ÉTAT1
 ÉTAT1                     ->     appuyer         ->        ÉTAT2
 ÉTAT2                     ->     appuyer         ->        ÉTAT3
 ÉTAT3                     ->     appuyer         ->        ÉTAT4
 ÉTAT4                     ->     appuyer         ->        ETATALLUMER
 ETATALLUMER               ->     délais 1s       ->        ÉTAT_ÉTEINT
 
 si l'entrée diffère de celle qui figure dans la table, l'état demeure à l'état actuel sauf pour ETATALLUMER qui allumera toujours la DEL pour une seconde
 
 * */
#define F_CPU (8000000)
#include <avr/io.h>
#include <util/delay.h>



const uint8_t ETEINT = 0b00000000;
const uint8_t VERT = 0b00000001;
const uint8_t ROUGE = 0b00000010;

 

bool antiRebond();


int main (){
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode entree
	uint8_t etat = 0;
	bool enTrainPeser = false;
	

  while(true){


      if(antiRebond() && !enTrainPeser){ //si enTrainPeser est à true et que l'antirebond l'est aussi, il s'agit bien d'un vrai push
          enTrainPeser = true;
          etat++;
      }

      if(!antiRebond()){//relache le bouton lorsque antiRebond est à false
          enTrainPeser = false;
      }

      if(etat ==5){ //lorsque le compteur de push etat arrive à 5, la DEL est allumée puis éteinte après 1sec
          PORTA = ROUGE;
          _delay_ms(100);
          etat=0;
          PORTA = ETEINT;
      }

    }
    return 0;
}

/********************************************************************************
 *  antiRebond()
 *  la fonction valide si le bouton a bel et bien été pesé en vérifiant une première
 *  fois, puis une seconde fois après 10ms pour s'assurer que le push n'est appelé
 *  qu'une seule fois
 ********************************************************************************/
bool antiRebond(){
      if(PIND & (1 << 2))//si le bouton est active
          _delay_ms(10);
      if(PIND & (1 << 2))//si le bouton est toujours /////
         return true;
    
    return false;
}
