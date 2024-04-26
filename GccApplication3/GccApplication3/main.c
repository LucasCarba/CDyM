/*
 * GccApplication3.c
 *
 * Created: 3/4/2024 15:56:31
 * Author : Notebook
 */ 
#include <avr/io.h>
#define F_CPU 20000000UL // Frecuencia de 20MHz
#include <util/delay.h> //Libreria de retardos
#define BUTTON_STATE() (PIND&(1<<PIND0))

int main(void)
{
	// 1 -> Salida|| 0 -> Entrada
	DDRB = 0xFF;   // Config como salida desde B0 a B7
	DDRD =  0b11111110; //Config como entrada el puerto D0
	PORTB = 0x00; // Inicio con todo apagado
	int ESTADO = 0; // 0 primera secuencia - 1 segunda secuencia
	while (1) //Bucle infinito
	{
		if (ESTADO == 0) // Inicio con el estado en 0.
		{
			_delay_ms(250); //retardo 250 ms
			while (ESTADO == 0) // Esperamos mientras el pulsador este presionado
				{
				for (int j=0; j<=3; j++) // Primera secuencia
					{
					PORTB = (1<<j) | (1<<(7-j)); // Enciende los leds 7&0--6&1--5&2--4&3
					_delay_ms(250); //retardo 250 ms
					if (BUTTON_STATE()!=1) // Si el pulsador fue presionado cambio el estado a 1
						{
							_delay_ms(250); //retardo 250 ms
							ESTADO = 1; // Cambio de estado.
						}
					//PORTB = 0b00000000; 
					}
				}
		} else {
				while (ESTADO == 1)
					{
					for (int i=7; i>=0; i--) // Segunda secuencia 
					{
						PORTB = (1<<i); // Enciende desde el led 7 al 0.
						_delay_ms(250); //retardo 250 ms
						if (BUTTON_STATE()!=1) // Si el pulsador fue presionado cambio el estado a 0
							{
								_delay_ms(250); //retardo 250 ms
								ESTADO = 0; // Cambio de estado.
							}
						// PORTB = 0b00000000; 
					}	
					
					}
			
				}
			

		}
}

