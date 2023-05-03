// @File		DHT11.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		02/05/23
//
//
// Copyright (C) 2023  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef DHT11_H
#define DHT11_H

#define DHT11_DATA PORTAbits.RA0 
#define DHT11_DATA_TRIS TRISAbits.RA0 

void __delay(unsigned int t)
{
    for(volatile unsigned int n=0; n < t ; n++) 
    {
         __asm__ __volatile__("nop");
    }
}

void DHT11_Init(void)
{
    DHT11_DATA_TRIS = 0;    
    DHT11_DATA = 1;
}

void DHT11_Start(void)
{   
    DHT11_DATA_TRIS = 0;
    
    DHT11_DATA = 0;
    
    __delay( 18000 );
    
    DHT11_DATA = 1;
    
    DHT11_DATA_TRIS = 1;
    
    while(DHT11_DATA);
    while(!DHT11_DATA);
    while(DHT11_DATA);
}

// When DHT is sending data to MCU, 
// every bit of data begins with the 50us low-voltage-level 
// and the length of the following high-voltage-level 
// signal determines whether data bit is "0" or "1" 
unsigned char DHT11_data()
{
    unsigned char data = 0;

    for(unsigned char mask = 0x80; mask; mask >>= 1)
    {
        while(!DHT11_DATA);

        __delay( 15 );
        
        data <<= 1;
        if (DHT11_DATA)  data |= 0x01; 
        
        while(DHT11_DATA);
    }
    
    DHT11_DATA_TRIS = 0;    
    DHT11_DATA = 1;
	
    return data;
}

#endif
