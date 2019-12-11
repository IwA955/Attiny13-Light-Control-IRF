


#define F_CPU 9600000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>





volatile uint16_t result = 0, Vcc = 0;



int main(void)
{

	TCCR0A |= (0<<WGM01)|(1<<WGM00)|(1<<COM0A1)|(0<<COM0A0);

	//TCCR0A |= (1<<WGM01)|(1<<WGM00)|(1<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0); // ��� (Fast PWM)
	// TCCR0A |= (0<<WGM01)|(1<<WGM00)|(1<<COM0A1)|(0<<COM0A0)|(1<<COM0B1)|(0<<COM0B0);  // ���� ��� (PhaseCorrect PWM)

	TCCR0B |= 0<<CS02|0<<CS01|1<<CS00;// ������� �� ������ �������
	OCR0A = 0;
	OCR0B = 0;
	TCNT0 = 0;
	TIMSK0 = 0;

	sei();




	PORTB = 0b00010011; 
	DDRB  = 0b00000001; 

/*	GIMSK = 0b01000000; // ���������� ���������� INT0 �� ����� PB1
	MCUCR = 0b00000010; // ��� �������� �� 1 � 0
*/

ADC_Init();

	while(1)
	{
	
		ADC_Result();

	}
	return 0;
}


void ADC_Init(void)
{

// ���������� �������
//	ADMUX |= 1<<REFS0|1<<MUX0;
	//ADMUX |= 1<<REFS0|1<<MUX1;

// Vcc ��� �����
	ADMUX |= 1<<MUX1;

//	ADCSRA |= 1<<ADEN|1<<ADIE|1<<ADPS2|1<<ADPS1|1<<ADSC;
//	ADCSRA |= 1<<ADEN|1<<ADPS1;

	//27.05.2016 �� �������� ��� ������� �������� ������� ��������������
//	ADCSRA |= 1<<ADEN|1<<ADPS2; // f0/16  = 500kHz
	ADCSRA |= 1<<ADEN|1<<ADPS2|1<<ADPS0; // f0/32  = 250kHz



//	ADCSRA |= 1<<ADSC; // ������ ��������������
	//sei();
	//DDRC |= 1<<PC2; 	
/*	ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
	ADCSRA |= _BV(ADSC); // ������ ��������������
*/	

}


void ADC_Result(void)
{
	do{
		ADCSRA |=1<<ADSC;
	}

	while ((ADCSRA &(1<<ADIF)) ==0x00); // ���� ��������� ���������
	
	
	result = (ADCL|ADCH<<8);

	OCR0A = (result>>2)-1; // ���������/4 ����� � ������� �������

}

