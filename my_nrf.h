//Memory Map
#define CONFIG 0x00
#define EN_AA 0x01
#define EN_RXADDR 0x02
#define SETUP_AW 0x03
#define SETUP_RETR 0x04
#define RF_CH 0x05
#define RF_SETUP 0x06
#define STATUS 0x07
#define OBSERVE_TX 0x08
#define RPD 0x09
#define RX_ADDR_P0 0x0A
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P2 0x0C
#define RX_ADDR_P3 0x0D
#define RX_ADDR_P4 0x0E
#define RX_ADDR_P5 0x0F
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define RX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16
#define FIFO_STATUS 0x17
#define DYNPD 0x1C
#define FEATURE 0x1D

#define R_REGISTER 0x00
#define W_REGISTER 0x20
#define R_RX_PAYLOAD 0x61
#define W_TX_PAYLOAD 0xA0
#define FLUSH_TX 0xE1
#define FLUSH_RX 0xE2
#define R_RX_PL_WID 0x60
#define W_ACK_PAYLOAD 0xA8
#define W_TX_PAYLOAD_NO_ACK 0xB0

#define CSN_enable output_low(CSN)
#define CSN_disable output_high(CSN)
#define CE_enable output_high(CE)
#define CE_disable output_low(CE)

#ifndef CE
#define CE pin_c0
#endif

#ifndef CSN
#define CSN pin_c1
#endif

#ifndef IRQ
#define IRQ pin_c2
#endif

void pulse_CSN();
void TX_config(unsigned int data);
unsigned int read_config();
void RX_config(unsigned int data);
void Enhanced_Shockburst(unsigned int data);
void RX_addresses(unsigned int data);
void address_width(unsigned int data);
void Auto_retransmit(unsigned int data);
void RF_channel(unsigned int data);
void RF_set(unsigned int data);
void write_STATUS(unsigned int data);
unsigned int read_STATUS();
unsigned int read_observe_tx();
void write_RX_ADDR(unsigned int *data,unsigned int address);
unsigned int *read_RX_ADDR(unsigned int address);
void write_TX_ADDR(unsigned int *data,unsigned int address);
unsigned int *read_TX_ADDR(unsigned int address);
void write_num_of_points(unsigned int address,unsigned int data);
unsigned int read_num_of_points(unsigned int address);
unsigned int read_fifo_status();
void write_payload(unsigned int *data);
unsigned int read_payload();
void write_feature(unsigned int data);
void write_dynp(unsigned int data);
void flushtx();
void flushrx();
void rf_init();
int1 RX_DR();
int1 TX_DS();
int1 MAX_RT();
unsigned int RX_P_NO();
