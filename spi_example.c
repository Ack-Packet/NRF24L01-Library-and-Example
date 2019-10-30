#include <16f877a.h>
#use delay(crystal=16MHz)
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG
#FUSES NOWDT

#define CE pin_c0 
#define CSN pin_c1 
#define IRQ pin_c2

#use spi (MASTER, SPI1, MODE=0, BITS=8)
#include <my_nrf.c>

#define trisd *((unsigned int*)0x88)
#define portd *((unsigned int*)0x08)
#define trisb *((unsigned int*)0x86)
#define portb *((unsigned int*)0x06)

unsigned int Rx_address[]={0xB3, 0xB4, 0xB5, 0xB6, 0x05};
unsigned int Tx_address[]={0xB3, 0xB4, 0xB5, 0xB6, 0x05};
unsigned int *TX;
unsigned int *RX;
unsigned int data[10]={0x01};

void main()
{
   TX=Tx_address;
   RX=Rx_address;
   ///////////
   trisd=0x00;
   portd=0x00;
   trisb=0x00;
   portb=0x80;
   //PTX device
   
   rf_init();
   TX_config(0x0E);
   Enhanced_Shockburst(0x00);
   RX_addresses(0x3F);
   address_width(0x03);
   Auto_retransmit(0x00);
   RF_channel(0x02);
   RF_set(0x26);
   write_STATUS(0x7E);
   write_RX_ADDR(RX,0x0A);
   write_TX_ADDR(TX,0x10);
   write_dynp(0x00);
   write_feature(0x01);
   
   flushrx();
   flushtx();
   
   delay_ms(500);
   while(true)
   {
      write_payload(data);
      portd=data[0];
      if(!input(IRQ))
      {
         write_STATUS(0x7E);
         delay_ms(5);
         if(TX_DS())
         {
            flushtx();
            data[0]++;
         }
      }
      delay_ms(100);
   }
}
