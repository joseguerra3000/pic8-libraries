

#include <xc.h>
#include "SPISoft.h"
#include "SPISoft_config.h"
#include "system.h"


void SPISoft_Initialize(){
    COM_TRIS &= ~(SDO_mask | CLK_mask);     // SDO y CLK salidas
    COM_TRIS |= SDI_mask;                   // SDI entrada
    COM_PORT &= ~(SDO_mask | CLK_mask);     // SDO y CLK = 0
}


void SPISoft_SendByteMode00(uint8_t byte){ // CKP = 0, CKE = 1
    uint8_t i = 8;
    
    CLK_OFF;
    
    while( i-- ){
        if( byte & 0x80 )
            SDO_ON;
        else
            SDO_OFF;
        
        wait();
        CLK_ON;
        wait();
        CLK_OFF;
        
        byte <<= 1;
    }
}

void SPISoft_SendByteMode10(uint8_t byte){ // CKP = 1, CKE = 1
    uint8_t i = 8;
    CLK_ON;
    
    while( i-- ){
        if( byte & 0x80 )
            SDO_ON;
        else
            SDO_OFF;
        
        wait();
        CLK_OFF;
        wait();
        CLK_ON;
        
        byte <<= 1;
    }
}