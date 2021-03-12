/* --COPYRIGHT--,BSD
* Copyright (c) 2017, Texas Instruments Incorporated
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* *  Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
* *  Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* *  Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* --/COPYRIGHT--*/

#include <msp430f2617.h>

// P1
#define  STATUS_LED        0x80
#define  I_Encoder_3_3V    0x20
#define  B_Encoder_3_3V    0x08
#define  A_Encoder_3_3V    0x04
#define  STALL_BUT         0x02
#define  DIR_BUT           0x01

// P2
#define  TOFF              0x80
#define  M0                0x40
#define  TRQ0              0x20
#define  STEP              0x10
#define  M1                0x08
#define  TRQ1              0x04

// P4
#define  nFAULT            0x40
#define  nSLEEP            0x20
#define  BDECAY            0x10
#define  DIR               0x04
#define  ADECAY            0x02
#define  ENABLE            0x01

// P6
#define  VREF              0x80
#define  ATE               0x40
#define  POT               0x04

// Global Variables
unsigned int STEPTXD;                         // Transmitted step Variable
unsigned int STEPRXD;                         // Received step Variable
unsigned int STEPINT;                         // Transmitted Step interval
unsigned char EncScan0;                       // GrayScale old
unsigned char EncCount;                       // Encoder count
unsigned char STALL;                          // Stall_Detection_Register
const unsigned int PHASESPEED[16] ={            // Look Up Table Timer
0, 20000, 17997, 16728, 15459, 14190, 12921, 11652, 10383, 9114, 7845,
6576, 4038, 2769,2200, 2000};
const char Gray_Tab16[16] = {
  0x00,                                       // 00->00 B1|A1|B0|A0
  0x01,                                       // 00->01 Clockwise
  0xFF,                                       // 00->10 CC
  0x00,                                       // 00->11
  0xFF,                                       // 01->00 CC
  0x00,                                       // 01->01
  0x00,                                       // 01->10
  0x01,                                       // 01->11 Clockwise
  0x01,                                       // 10->00 Clockwise
  0x00,                                       // 10->01
  0x00,                                       // 10->10
  0xFF,                                       // 10->11 CC
  0x00,                                       // 11->00
  0xFF,                                       // 11->01 CC
  0x01,                                       // 11->10 Clockwise
  0x00                                        // 11->11
};

int main(void) {
  WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer
    BCSCTL1 = CALBC1_8MHZ;                    // Set DCO to 8MHz
    DCOCTL = CALDCO_8MHZ;
    P1OUT |= DIR_BUT;                         // Direction select
    P1DIR |= STATUS_LED;                      // Status LED
    P1REN |= DIR_BUT;                         // Enable Pullup R for DIR_BUT
    P2OUT= TRQ0;                              // TRQ75 + TOFF20us + FULL STEP
    P2DIR=STEP + M0 + M1 + TRQ0 + TRQ1+ TOFF;
    P4OUT = nSLEEP + ENABLE + DIR;            // nSLEEP High + Enable High + DIR
    P4DIR = BDECAY + ADECAY + nSLEEP + DIR;   // Decay modes, nSleep + DIR
    P6OUT = VREF + ATE;                       // VREF and autotune High
    P6DIR = VREF + ATE;
    P6SEL |= POT;                             // P6.2-ADC option select
    P4DIR |= ENABLE;                          // Global enable DRV
    ADC12CTL0 = SHT0_2 + ADC12ON;             // Set sampling time, turn on ADC12
    ADC12CTL1 = SHP;                          // Use sampling timer
    ADC12MCTL0 = INCH_2;                      // ref+=AVcc, channel = A2
    ADC12CTL0 |= ENC;                         // Conversion enabled
    TACCTL0 = CCIE;                           // CCR0 interrupt enabled
    TACCR0 = 20;                              // Quad decoder interval
    TACCTL2 = CCIE;                           // CCR1 interrupt enabled
    TACTL = ID_3 + TASSEL_2 + MC_2 + TAIE;    // SMCLK/8, contmode, interrupt
    STALL = 0;                                // No Error
    EncCount = 10;                            // Initialize Enc Count Register
    STEPTXD = 0;                              // Default speed

while(1){
    _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
/*------------------------------------------------------------------------------
  Error check - input STALL
                output STALL, STATUS_LED, STEPTXD
------------------------------------------------------------------------------*/
      if (STALL == 1) {
      P1OUT ^= STATUS_LED;                    // Error
      STALL = 0;                              // Flag, Normal operation
      EncCount = 10;                            // Initialize Enc Count Register
      STEPTXD = 0;                            // Default speed
    }
    else {
      P1OUT |= STATUS_LED;                    // Normal operation
    }

/*------------------------------------------------------------------------------
   Direction - input STEPTXD, DIR_BUT,
             output DIR, speed == 0 to change direction
------------------------------------------------------------------------------*/
    if (STEPTXD == 0) {
      if (P1IN & DIR_BUT) {
        P4OUT |= DIR;                        // Forward
        }
      else {
        P4OUT &= ~DIR;                      // Reverse
        }
   }

/*------------------------------------------------------------------------------
  Get speed - input POTI,
              output is STEPRXD (0-15)
------------------------------------------------------------------------------*/
    ADC12CTL0 |= ADC12SC;                     // Start conversion
    while (ADC12CTL1 & ADC12BUSY);            // ADC12BUSY?
    STEPRXD = (ADC12MEM0 >> 8);               // Mask upper 4-bits

/*------------------------------------------------------------------------------
  Acceleration - input DIR_BUT, DIR, STEPRXD
                 output STEPTXD, TACCTL2.CCIE, STEPINT
------------------------------------------------------------------------------*/
    if (((P1IN & DIR_BUT) && (P4OUT & DIR)) ||
       (!(P1IN & DIR_BUT)) && (!(P4OUT & DIR))) {
      if (STEPTXD < STEPRXD){
        STEPTXD++;                           // Same direction, Speed-up
      }
      else if (STEPTXD > STEPRXD){
        STEPTXD--;                           // Same direction, Slow down
      }
    }
    else if (!(STEPTXD == 0)) {
      STEPTXD--;                              // Mismatch direction, Slow down
    }
    if (STEPTXD == 0) {                       // Zero speed?
      TACCTL2 = 0;                            // yes, Disable interrupt, no step
      STALL = 0;                              // Flag, Normal operation
      EncCount = 10;                          // Initialize Enc Count Register

    }
    else {
      TACCTL2 = CCIE;                         // no, Enable interrupt
    }
    STEPINT = PHASESPEED[STEPTXD];            // Step interval
  }
}

/*------------------------------------------------------------------------------
  Timer A0 interrupt service routine
  Scan 2-bit Grayscale Encoder, called 20us intervals
------------------------------------------------------------------------------*/
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void) {
  unsigned char i,j;
  i = (P1IN >> 2)& 3;                         // P1.2|1 Encoder scan input
  EncScan0 = ((EncScan0 << 2) + i) & 0x0F;
  j = Gray_Tab16[EncScan0];                   // +/- 1 or 0
//  EncCount += j;                              // Adjust encoder count
  EncCount -= j;                              // Adjust encoder count
  TACCR0 += 20;                               // Next Scan Period
}

/*------------------------------------------------------------------------------
  Timer_A3 Interrupt Vector (TAIV) handler
------------------------------------------------------------------------------*/
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void) {
  switch( TAIV ) {
    case  2:
    P2OUT &= ~STEP;                           // STEP low
    TACCTL1 = 0   ;                           // Disable
    break;
    case  4:
    TACCR1 = TACCR2 + 100;
    TACCTL1 = CCIE;                           // Enable interrupt
    TACCR2 += STEPINT;                        // Increments Timer period
    if (EncCount < 10) {
      STALL = 1;                              // Flag, Not sufficent counts
    }
    EncCount = 0;                             // Reset counts
    P2OUT |= STEP;                            // STEP high
    break;                                    // CCR2
    case 10:                                  // overflow
    _BIC_SR_IRQ(LPM0_bits);                   // Clear LPM0 bits from 0(SR)
    break;
  }
}
