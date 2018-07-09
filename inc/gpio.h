#ifndef __GPIO_H
#define __GPIO_H

#define LED_OK 			P3_25
#define LED_ERROR 	P3_26

#define A1	P0_0
#define A2	P0_1
#define A3	P0_2
#define A4	P0_3
#define A5	P0_4
#define A6	P0_5
#define A7	P0_6
#define A8	P0_7
#define A9	P0_23
#define A10	P0_24
#define A11	P0_25
#define A12	P0_26
#define A13	P0_27
#define A14	P0_28
#define A15	P0_29
#define A16	P0_30
#define A17 P1_0
#define A18 P1_1
#define A19 P1_4
#define A20 P1_8
#define A21 P1_9
#define A22 P1_10
#define A23 P1_14
#define A24 P1_15
#define A25 P1_16
#define A26 P1_17
#define A27 P1_18
#define A28 P1_19
#define A29 P1_20
#define A30 P1_21

#define OE1 P2_7
#define OE2 P2_8
#define OE3 P2_9
#define OE4 P2_10
#define OE5 P2_11

#define L1 P2_2
#define L2 P2_3
#define L3 P2_4
#define L4 P2_5
#define L5 P2_6

#define MAXRED 5
#define MAXSTUPAC	5
#define MAXPINS 20		//ima mjesta za 23 pina, onda radi (provjeriti), za 24 ne radi

#define  util_GetBitMask(bit)          ((uint32_t)1<<(bit))
#define  util_BitSet(x,bit)            ((x) |=  util_GetBitMask(bit))
#define  util_BitClear(x,bit)          ((x) &= ~util_GetBitMask(bit))
#define  util_BitToggle(x,bit)         ((x) ^=  util_GetBitMask(bit))
#define  util_UpdateBit(x,bit,val)     ((val)? util_BitSet(x,bit): util_BitClear(x,bit))

#define  util_GetBitStatus(x,bit)      (((x)&(util_GetBitMask(bit)))!=0u)
#define  util_IsBitSet(x,bit)          (((x)&(util_GetBitMask(bit)))!=0u)
#define  util_IsBitCleared(x,bit)      (((x)&(util_GetBitMask(bit)))==0u)

void GPIO_PinWrite(uint8_t pinNumber, uint8_t pinValue);
uint8_t GPIO_PinRead(uint8_t pinNumber);
void postavi_ulaze(uint8_t adresa, uint8_t demux);
void read_inputs(uint8_t demux, uint8_t adresa, uint8_t aktivni_pin, bool *p);
void postavi_izlaz(uint8_t adresa, uint8_t demux);


#define B(x) S_to_binary_(#x)

typedef enum
{
    P0_0, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, P0_8, P0_9, P0_10,P0_11,P0_12,P0_13,P0_14,P0_15,
    P0_16,P0_17,P0_18,P0_19,P0_20,P0_21,P0_22,P0_23,P0_24,P0_25,P0_26,P0_27,P0_28,P0_29,P0_30,P0_31,

    P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, P1_8, P1_9, P1_10,P1_11,P1_12,P1_13,P1_14,P1_15,
    P1_16,P1_17,P1_18,P1_19,P1_20,P1_21,P1_22,P1_23,P1_24,P1_25,P1_26,P1_27,P1_28,P1_29,P1_30,P1_31,

    P2_0, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7, P2_8, P2_9, P2_10,P2_11,P2_12,P2_13,P2_14,P2_15,
    P2_16,P2_17,P2_18,P2_19,P2_20,P2_21,P2_22,P2_23,P2_24,P2_25,P2_26,P2_27,P2_28,P2_29,P2_30,P2_31,

    P3_0, P3_1, P3_2, P3_3, P3_4, P3_5, P3_6, P3_7, P3_8, P3_9, P3_10,P3_11,P3_12,P3_13,P3_14,P3_15,
    P3_16,P3_17,P3_18,P3_19,P3_20,P3_21,P3_22,P3_23,P3_24,P3_25,P3_26,P3_27,P3_28,P3_29,P3_30,P3_31,

    P4_0, P4_1, P4_2, P4_3, P4_4, P4_5, P4_6, P4_7, P4_8, P4_9, P4_10,P4_11,P4_12,P4_13,P4_14,P4_15,
    P4_16,P4_17,P4_18,P4_19,P4_20,P4_21,P4_22,P4_23,P4_24,P4_25,P4_26,P4_27,P4_28,P4_29,P4_30,P4_31,

    P_MAX,
    P_NC = 0xff
}gpioPins_et;

#endif
