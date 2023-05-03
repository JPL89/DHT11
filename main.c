// @File		MAIN.C		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		02/05/23
//
//
// Copyright (C) 2023 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#include "config.h"
#include "ks0066.h"
#include "dth11.h"

unsigned char integral_RH;
unsigned char decimal_RH;
unsigned char integral_T;
unsigned char decimal_T;
unsigned char check_sum;

void main(void)
{
    __delay_ms(500);
    
    PIC18F2520();
    
    KS0066_Init();
    
    KS0066_Clear(0);
    
    KS0066_Clear(1);
    
    KS0066_Goto(0, 0);
    
    DHT11_Init();
    
    DHT11_Start();
    
    integral_RH = DHT11_data(); 
    decimal_RH = DHT11_data(); 
    integral_T = DHT11_data();   
    decimal_T = DHT11_data(); 
    check_sum = DHT11_data(); 

    while(1)
    {
        DHT11_Start();
    
        integral_RH = DHT11_data(); 
        decimal_RH = DHT11_data(); 
        integral_T = DHT11_data();   
        decimal_T = DHT11_data(); 
        check_sum = DHT11_data(); 

        KS0066_Clear(1);    
        KS0066_Clear(0);  
        
        KS0066_Goto(0, 0);
        KS0066_Int( integral_RH );
        KS0066_Goto(0, 1);
        KS0066_Int( integral_T );

        __delay_ms(1000);
    }
    
    return;
}