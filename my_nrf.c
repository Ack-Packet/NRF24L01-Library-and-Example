#include <my_nrf.h>
#include <Functions.c>

void pulse_CSN()
{
   CSN_disable;
   delay_us(20);
   CSN_enable;
}

void TX_config(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+CONFIG);
   spi_write(data);
   pulse_CSN();
}

unsigned int read_config()
{
   unsigned int data;
   pulse_CSN();
   spi_write(R_REGISTER+CONFIG);
   data=spi_read(0);
   pulse_CSN();
   
   return data;
}

void RX_config(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+CONFIG);
   spi_write(data);
   pulse_CSN();
}

void Enhanced_Shockburst(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+EN_AA);
   spi_write(data);
   pulse_CSN();
}

void RX_addresses(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+EN_RXADDR);
   spi_write(data);
   pulse_CSN();
}

void address_width(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+SETUP_AW);
   spi_write(data);
   pulse_CSN();
}

void Auto_retransmit(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+SETUP_RETR);
   spi_write(data);
   pulse_CSN();
}

void RF_channel(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+RF_CH);
   spi_write(data);
   pulse_CSN();
}

void RF_set(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+RF_SETUP);
   spi_write(data);
   pulse_CSN();
}

void write_STATUS(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+STATUS);
   spi_write(data);
   pulse_CSN();
}

unsigned int read_STATUS()
{
   unsigned int data;
   pulse_CSN();
   spi_write(R_REGISTER+STATUS);
   data=spi_read(0);
   pulse_CSN();
   
   return data;
}

unsigned int read_observe_tx()
{
   unsigned int data;
   pulse_CSN();
   spi_write(R_REGISTER+OBSERVE_TX);
   data=spi_read();
   pulse_CSN();
   
   return data;
}

void write_RX_ADDR(unsigned int *data,unsigned int address)
{
   pulse_CSN();
   spi_write(W_REGISTER+address);
   for(int i=0;i<5;i++)
   {
      spi_write(*(data+i));
   }
   pulse_CSN();
}
/*
unsigned int *read_RX_ADDR(unsigned int address)
{
   unsigned int *data;
   unsigned int d_data[5];
   pulse_CSN();
   spi_write(R_REGISTER+address);
   for(int i=0;i<5;i++)
   {
      d_data[i]=spi_read(0);
   }
   pulse_CSN();
   
   data=d_data;
   
   return data;
}
*/
void read_RX_ADDR(unsigned int address,unsigned int *data)
{
   pulse_CSN();
   spi_write(R_REGISTER+address);
   for(int i=0;i<5;i++)
   {
      *(data+i)=spi_read(0);
   }
   pulse_CSN();
}

void write_TX_ADDR(unsigned int *data,unsigned int address)
{
   pulse_CSN();
   spi_write(W_REGISTER+address);
   for(int i=0;i<5;i++)
   {
      spi_write(*(data+i));
   }
   pulse_CSN();
}
/*
unsigned int *read_TX_ADDR(unsigned int address)
{
   unsigned int *data;
   unsigned int d_data[5];
   pulse_CSN();
   spi_write(R_REGISTER+address);
   for(int i=0;i<5;i++)
   {
      d_data[i]=spi_read(0);
   }
   pulse_CSN();
   
   data=d_data;
   return data;
}
*/
void read_TX_ADDR(unsigned int address,unsigned int *data)
{
   pulse_CSN();
   spi_write(R_REGISTER+address);
   for(int i=0;i<5;i++)
   {
      *(data+i)=spi_read(0);
   }
   
   pulse_CSN();
}

void write_num_of_points(unsigned int address,unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+address);
   spi_write(data);
   pulse_CSN();
}

unsigned int read_num_of_points(unsigned int address)
{
   unsigned int data;
   pulse_CSN();
   spi_write(R_REGISTER+address);
   data=spi_read(0);
   pulse_CSN();
   
   return data;
}

unsigned int read_fifo_status()
{
   unsigned int data;
   pulse_CSN();
   spi_write(R_REGISTER+FIFO_STATUS);
   data=spi_read(0);
   pulse_CSN();
   
   return data;
}

void write_payload(unsigned int *data)
{
   pulse_CSN();
   spi_write(W_TX_PAYLOAD_NO_ACK);
   for(int i=0;i<i_length(data);i++)
   {
      spi_write(*(data+i));
   }
   
   CE_enable;
   delay_us(50);
   CE_disable;
   
   pulse_CSN();
}

void read_payload(unsigned int *data)
{
   pulse_CSN();
   CE_enable;
   spi_write(R_RX_PAYLOAD);
   for(int i=0;i<1;i++)
   {
      *(data+i)=spi_read(0); 
   }
   pulse_CSN();
   
   if(!input(IRQ))
   {
      write_STATUS(0x7E);
      delay_ms(5);
      if(RX_DR())
      {
         CE_disable;
         flushrx();
      }
   }
}

void write_feature(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+FEATURE);
   spi_write(data);
   pulse_CSN();
}

void write_dynp(unsigned int data)
{
   pulse_CSN();
   spi_write(W_REGISTER+DYNPD);
   spi_write(data);
   pulse_CSN();
}

void flushtx()
{
   pulse_CSN();
   spi_write(FLUSH_TX);
   pulse_CSN();
}

void flushrx()
{
   pulse_CSN();
   spi_write(FLUSH_RX);
   pulse_CSN();
}

void rf_init()
{
   pulse_CSN();
   CE_disable;
}

int1 RX_DR()
{
   if((read_STATUS()>>6)&0x01)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int1 TX_DS()
{
   if((read_STATUS()>>5)&0x01)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int1 MAX_RT()
{
   if((read_STATUS()>>4)&0x01)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

unsigned int RX_P_NO()
{
   return ((read_STATUS()>>1)&0x07);
}

void standby_1()
{
   CE_disable;
}
