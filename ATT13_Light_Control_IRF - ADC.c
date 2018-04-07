
#define F_CPU 9600000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define NO_BUTTON

volatile uint16_t result = 0, Vcc = 0;
#define Vref 50
volatile uint8_t Level = 0;

void ADC_Init(void)
{
	ADMUX |= 1<<MUX0; // опора от питания, вход АЦП ADC1 (PB2)
//	ADCSRA |= 1<<ADEN|1<<ADIE|1<<ADPS2|1<<ADPS1|1<<ADSC;
	ADCSRA |= 1<<ADEN;
//	ADCSRA |= 1<<ADSC; // начало преобразований
	//sei();
	//DDRC |= 1<<PC2; 	
/*	ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
	ADCSRA |= _BV(ADSC); // начало преобразований
*/	
}


void ADC_Result(void)
{
	do{
		ADCSRA |=1<<ADSC;
		
	}

	
	while ((ADCSRA &(1<<ADIF)) ==0); // ждем окончания измерения

	
	result = (ADCL|ADCH<<8);
	Vcc = (result*Vref)/1023;
/*	if(Vcc<45)
	OCR0A = 128;
	if(Vcc>45)
	OCR0A = 196;
*/
/*	if(result == 1023)
	OCR0A = 254;
	if(result == 958)
	OCR0A = 234;
	if(result == 894)
	OCR0A = 214;
	if(result == 830)
	OCR0A = 194;
	if(result == 766)
	OCR0A = 174;
	if(result == 702)
	OCR0A = 154;
	if(result == 638)
	OCR0A = 134;
	if(result == 574)
	OCR0A = 114;
	if(result == 510)
	OCR0A = 94;
	if(result == 446)
	OCR0A = 74;
	if(result == 382)
	OCR0A = 54;
	if(result == 318)
	OCR0A = 34;
	if(result == 254)
	OCR0A = 14;
	if(result < 254)
	OCR0A = 0;
*/
/*
	if(Vcc == 50)
	OCR0A = 254;
	if(Vcc == 46)
	OCR0A = 234;
	if(Vcc == 43)
	OCR0A = 214;
	if(Vcc == 40)
	OCR0A = 194;
	if(Vcc == 37)
	OCR0A = 174;
	if(Vcc == 34)
	OCR0A = 154;
	if(Vcc == 31)
	OCR0A = 134;
	if(Vcc == 28)
	OCR0A = 114;
	if(Vcc == 25)
	OCR0A = 94;
	if(Vcc == 21)
	OCR0A = 74;
	if(Vcc == 18)
	OCR0A = 54;
	if(Vcc == 15)
	OCR0A = 34;
	if(Vcc == 12)
	OCR0A = 14;
	if(Vcc < 11)
	OCR0A = 0;
*/

	if(Vcc == 50)
	OCR0A = 255;

	if(Vcc == 48)
	OCR0A = 247;

	if(Vcc == 46)
	OCR0A = 239;

	if(Vcc == 45)
	OCR0A = 231;

	if(Vcc == 43)
	OCR0A = 223;

	if(Vcc == 40)
	OCR0A = 215;

	if(Vcc == 39)
	OCR0A = 207;

	if(Vcc == 37)
	OCR0A = 199;

	if(Vcc == 35)
	OCR0A = 191;

	if(Vcc == 34)
	OCR0A = 183;

	if(Vcc == 32)
	OCR0A = 175;

	if(Vcc == 31)
	OCR0A = 167;

	if(Vcc == 29)
	OCR0A = 159;

	if(Vcc == 28)
	OCR0A = 151;

	if(Vcc == 26)
	OCR0A = 143;

	if(Vcc == 25)
	OCR0A = 135;

	if(Vcc == 23)
	OCR0A = 127;

	if(Vcc == 21)
	OCR0A = 119;

	if(Vcc == 20)
	OCR0A = 111;

	if(Vcc == 18)
	OCR0A = 103;

	if(Vcc == 17)
	OCR0A = 95;

	if(Vcc == 15)
	OCR0A = 87;

	if(Vcc == 14)
	OCR0A = 79;

	if(Vcc == 12)
	OCR0A = 71;

	if(Vcc == 10)
	OCR0A = 63;

	if(Vcc < 10)
	OCR0A = 0;



	
}




int main(void)
{
 // мой код
	TCCR0A |= (0<<WGM01)|(1<<WGM00)|(1<<COM0A1)|(0<<COM0A0);
	TCCR0B |= 0<<CS02|1<<CS01|0<<CS00;
	OCR0A = 64;
	OCR0B = 20;
	TCNT0 = 0;
	TIMSK0 = 0;
	ADC_Init();
	sei();



/*
// код с http://mega-avr.com.ua/shim-na-attiny13-upravlyaemyj-napryazheniem-ili-analogovym-signalom/
// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Phase correct PWM top=0xFF
// OC0B output: Non-Inverted PWM
// OC0A output: ????????????? ????????
TCCR0A=0xB1;
TCCR0B=0x03;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;
	TCNT0 = 0;
	TIMSK0 = 0;
*/

	PORTB |= (0<<PB0)|(0<<PB3)|(0<<PB4);
	//DDRB |= (1<<PB0)|(1<<PB2)|(1<<PB3)|(0<<PB4);
	DDRB |= (1<<PB0)|(1<<PB3)|(1<<PB4);



	while(1)
	{
		
	
	
	
	ADC_Result();

	_delay_ms(80);


		
		

	

	}
	return 0;
}
