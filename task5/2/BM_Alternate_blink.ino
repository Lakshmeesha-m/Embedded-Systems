#include <avr/io.h>
#include<util/delay.h>
int main(void){
  DDRB = DDRB|(1<<DDB5);
  DDRB = DDRB|(1<<DDB4);
  while(1)
  {
    PORTB = PORTB|(1<<PORTB5);
    PORTB = PORTB&~(1<<PORTB4);
    _delay_ms(1000);

    PORTB = PORTB&~(1<<PORTB5);
    PORTB = PORTB|(1<<PORTB4);
    _delay_ms(1000);    
  }
}
