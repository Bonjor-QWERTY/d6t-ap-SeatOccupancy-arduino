/*
 * MIT License
 * Copyright (c) 2019, 2018 - present OMRON Corporation
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/* includes */
#include <Wire.h>

/* defines */
#define D6T_ADDR 0x0A  // for I2C 7bit address
#define D6T_CMD 0x4C  // for D6T-44L-06/06H, D6T-8L-09/09H, for D6T-1A-01/02

#define N_ROW 8
#define N_PIXEL 8
#define N_READ ((N_PIXEL + 1) * 2 + 1)

#define SAMPLE_TIME_0010MS	10
#define SAMPLE_TIME_0012MS	12
#define SAMPLE_TIME_0016MS	16
#define SAMPLE_TIME_0025MS	25
#define SAMPLE_TIME_0050MS	50
#define SAMPLE_TIME_0070MS	70
#define SAMPLE_TIME_0140MS	140
#define SAMPLE_TIME_0250MS	250
#define SAMPLE_TIME_0500MS	500
#define SAMPLE_TIME_1000MS	1000
#define SAMPLE_TIME_2000MS	2000
#define SAMPLE_TIME_4000MS	4000
#define SAMPLE_TIME_8000MS	8000

#define PARA_0010MS_1	((uint8_t)0x90)
#define PARA_0010MS_2	((uint8_t)0x33)
#define PARA_0010MS_3	((uint8_t)0x87)
#define PARA_0012MS_1	((uint8_t)0x90)
#define PARA_0012MS_2	((uint8_t)0x34)
#define PARA_0012MS_3	((uint8_t)0x92)
#define PARA_0016MS_1	((uint8_t)0x90)
#define PARA_0016MS_2	((uint8_t)0x35)
#define PARA_0016MS_3	((uint8_t)0x95)
#define PARA_0025MS_1	((uint8_t)0x90)
#define PARA_0025MS_2	((uint8_t)0x36)
#define PARA_0025MS_3	((uint8_t)0x9C)
#define PARA_0050MS_1	((uint8_t)0x90)
#define PARA_0050MS_2	((uint8_t)0x37)
#define PARA_0050MS_3	((uint8_t)0x9B)
#define PARA_0070MS_1	((uint8_t)0x90)
#define PARA_0070MS_2	((uint8_t)0x38)
#define PARA_0070MS_3	((uint8_t)0xB6)
#define PARA_0140MS_1	((uint8_t)0x90)
#define PARA_0140MS_2	((uint8_t)0x39)
#define PARA_0140MS_3	((uint8_t)0xB1)
#define PARA_0250MS_1	((uint8_t)0x90)
#define PARA_0250MS_2	((uint8_t)0x3A)
#define PARA_0250MS_3	((uint8_t)0xB8)
#define PARA_0500MS_1	((uint8_t)0x90)
#define PARA_0500MS_2	((uint8_t)0x3B)
#define PARA_0500MS_3	((uint8_t)0xBF)
#define PARA_1000MS_1	((uint8_t)0x90)
#define PARA_1000MS_2	((uint8_t)0x3C)
#define PARA_1000MS_3	((uint8_t)0xAA)
#define PARA_2000MS_1	((uint8_t)0x90)
#define PARA_2000MS_2	((uint8_t)0x3D)
#define PARA_2000MS_3	((uint8_t)0xAD)
#define PARA_4000MS_1	((uint8_t)0x90)
#define PARA_4000MS_2	((uint8_t)0x3E)
#define PARA_4000MS_3	((uint8_t)0xA4)
#define PARA_8000MS_1	((uint8_t)0x90)
#define PARA_8000MS_2	((uint8_t)0x3F)
#define PARA_8000MS_3	((uint8_t)0xA3)

/***** Setting Parameter *****/
#define comparingNumInc 6  // x samplingTime ms  (range: 1 to 39)   (example) 6 x 250 ms -> 1.5 sec
#define comparingNumDec 6  // x samplingTime ms  (range: 1 to 39)   (example) 6 x 250 ms -> 1.5 sec
#define threshHoldInc 10 //  /10 degC   (example) 10 -> 1.0 degC (temperature change > 1.0 degC -> Enable) 
#define threshHoldDec 10 //  /10 degC   (example) 10 -> 1.0 degC (temperature change > 1.0 degC -> Enable) 
bool  enablePix[8] = {true, true, true, true, true, true, true, true};
/****************************/

/***** Setting Parameter 2 *****/
#define samplingTime SAMPLE_TIME_0250MS //ms (Can select only, 10ms, 12ms, 16ms, 25ms, 50ms, 70ms, 140ms, 250ms, 500ms, 1000ms, 2000ms, 4000ms, 8000ms)
/****************************/

uint8_t rbuf[N_READ];
int16_t pix_data[8] = {0};
int16_t seqData[8][40] = {0};
bool  occuPix[8] = {0};
bool  occuPixFlag = false;
uint8_t  resultOccupancy = 0;
uint16_t  totalCount = 0;

/** JUDGE_occupancy: judge occupancy*/
bool judge_seatOccupancy(void) { 
  int i = 0;
  int j = 0; 
  for (i = 0; i < 8; i++){
    for (j = 0; j < 39; j++){
      seqData[i][39 - j] = seqData[i][38 - j];
    }
    seqData[i][0] = pix_data[i];            
  }
  if (totalCount <= comparingNumInc){
    totalCount++;
  }
  if (totalCount > comparingNumInc){
    for (i = 0; i < 8; i++){
      if (enablePix[i] == true){
        if (occuPix[i] == false){
           if ((int16_t)(seqData[i][0] - seqData[i][comparingNumInc]) > (int16_t)threshHoldInc){
            occuPix[i] = true;
          }
        }
        else{   
		  if ((int16_t)(seqData[i][comparingNumDec] - seqData[i][0]) > (int16_t)threshHoldDec){
			occuPix[i] = false;
          }
        }
      }
    }
    if (resultOccupancy == 0) {
      for (i = 0; i < 8; i++){                   
        if(occuPix[i] == true){
          resultOccupancy = 1;
          break;
        }
      }
    }
    else{  //resultOccupancy == true
      occuPixFlag = false;
      for (i = 0; i < 8; i++){
        if (occuPix[i] == true){
          occuPixFlag = true;
          break;
        }
        else{                            
        }
      }
      if (occuPixFlag == false){
        resultOccupancy = 0;
      }
    }
  }
  return true;
}

uint8_t calc_crc(uint8_t data) {
    int index;
    uint8_t temp;
    for (index = 0; index < 8; index++) {
        temp = data;
        data <<= 1;
        if (temp & 0x80) {data ^= 0x07;}
    }
    return data;
}

/** <!-- D6T_checkPEC {{{ 1--> D6T PEC(Packet Error Check) calculation.
 * calculate the data sequence,
 * from an I2C Read client address (8bit) to thermal data end.
 */
bool D6T_checkPEC(uint8_t buf[], int n) {
    int i;
    uint8_t crc = calc_crc((D6T_ADDR << 1) | 1);  // I2C Read address (8bit)
    for (i = 0; i < n; i++) {
        crc = calc_crc(buf[i] ^ crc);
    }
    bool ret = crc != buf[n];
    if (ret) {
        Serial.print("PEC check failed:");
        Serial.print(crc, HEX);
        Serial.print("(cal) vs ");
        Serial.print(buf[n], HEX);
        Serial.println("(get)");
    }
    return ret;
}


/** <!-- conv8us_s16_le {{{1 --> convert a 16bit data from the byte stream.
 */
int16_t conv8us_s16_le(uint8_t* buf, int n) {
    int ret;
    ret = buf[n];
    ret += buf[n + 1] << 8;
    return (int16_t)ret;   // and convert negative.
}


/** <!-- setup {{{1 -->
 * 1. initialize a Serial port for output.
 * 2. initialize an I2C peripheral.
 */
void setup() {
	uint8_t para[3] = {0};
	switch(samplingTime){
		case SAMPLE_TIME_0010MS:
			para[0] = PARA_0010MS_1;
			para[1] = PARA_0010MS_2;
			para[2] = PARA_0010MS_3;
			break;
		case SAMPLE_TIME_0012MS:
			para[0] = PARA_0012MS_1;
			para[1] = PARA_0012MS_2;
			para[2] = PARA_0012MS_3;
			break;
		case SAMPLE_TIME_0016MS:
			para[0] = PARA_0016MS_1;
			para[1] = PARA_0016MS_2;
			para[2] = PARA_0016MS_3;
			break;
		case SAMPLE_TIME_0025MS:
			para[0] = PARA_0025MS_1;
			para[1] = PARA_0025MS_2;
			para[2] = PARA_0025MS_3;
			break;
		case SAMPLE_TIME_0050MS:
			para[0] = PARA_0050MS_1;
			para[1] = PARA_0050MS_2;
			para[2] = PARA_0050MS_3;
			break;
		case SAMPLE_TIME_0070MS:
			para[0] = PARA_0070MS_1;
			para[1] = PARA_0070MS_2;
			para[2] = PARA_0070MS_3;
			break;
		case SAMPLE_TIME_0140MS:
			para[0] = PARA_0140MS_1;
			para[1] = PARA_0140MS_2;
			para[2] = PARA_0140MS_3;
			break;
		case SAMPLE_TIME_0250MS:
			para[0] = PARA_0250MS_1;
			para[1] = PARA_0250MS_2;
			para[2] = PARA_0250MS_3;
			break;
		case SAMPLE_TIME_0500MS:
			para[0] = PARA_0500MS_1;
			para[1] = PARA_0500MS_2;
			para[2] = PARA_0500MS_3;
			break;
		case SAMPLE_TIME_1000MS:
			para[0] = PARA_1000MS_1;
			para[1] = PARA_1000MS_2;
			para[2] = PARA_1000MS_3;
			break;
		case SAMPLE_TIME_2000MS:
			para[0] = PARA_2000MS_1;
			para[1] = PARA_2000MS_2;
			para[2] = PARA_2000MS_3;
			break;
		case SAMPLE_TIME_4000MS:
			para[0] = PARA_4000MS_1;
			para[1] = PARA_4000MS_2;
			para[2] = PARA_4000MS_3;
			break;
		case SAMPLE_TIME_8000MS:
			para[0] = PARA_8000MS_1;
			para[1] = PARA_8000MS_2;
			para[2] = PARA_8000MS_3;
			break;
		default:
			para[0] = PARA_0250MS_1;
			para[1] = PARA_0250MS_2;
			para[2] = PARA_0250MS_3;
			break;
	}
	
    Serial.begin(115200);  // Serial baudrate = 115200bps
    Wire.begin();  // i2c master

    Wire.beginTransmission(D6T_ADDR);  // I2C client address
    Wire.write(0x02);                  // D6T register
    Wire.write(0x00);                  // D6T register
    Wire.write(0x01);                  // D6T register
    Wire.write(0xEE);                  // D6T register
    Wire.endTransmission();            // I2C repeated start for read
    Wire.beginTransmission(D6T_ADDR);  // I2C client address
    Wire.write(0x05);                  // D6T register
    Wire.write(para[0]);                  // D6T register
    Wire.write(para[1]);                  // D6T register
    Wire.write(para[2]);                  // D6T register
    Wire.endTransmission();            // I2C repeated start for read
    Wire.beginTransmission(D6T_ADDR);  // I2C client address
    Wire.write(0x03);                  // D6T register
    Wire.write(0x00);                  // D6T register
    Wire.write(0x03);                  // D6T register
    Wire.write(0x8B);                  // D6T register
    Wire.endTransmission();            // I2C repeated start for read
    Wire.beginTransmission(D6T_ADDR);  // I2C client address
    Wire.write(0x03);                  // D6T register
    Wire.write(0x00);                  // D6T register
    Wire.write(0x07);                  // D6T register
    Wire.write(0x97);                  // D6T register
    Wire.endTransmission();            // I2C repeated start for read
    Wire.beginTransmission(D6T_ADDR);  // I2C client address
    Wire.write(0x02);                  // D6T register
    Wire.write(0x00);                  // D6T register
    Wire.write(0x00);                  // D6T register
    Wire.write(0xE9);                  // D6T register
    Wire.endTransmission();            // I2C repeated start for read
}


/** <!-- loop - Thermal sensor {{{1 -->
 * 1. read sensor.
 * 2. output results, format is: [degC]
 */
void loop() {
    int i, j;

    memset(rbuf, 0, N_READ);
    // Wire buffers are enough to read D6T-16L data (33bytes) with
    // MKR-WiFi1010 and Feather ESP32,
    // these have 256 and 128 buffers in their libraries.
    Wire.beginTransmission(D6T_ADDR);  // I2C client address
    Wire.write(D6T_CMD);               // D6T register
    Wire.endTransmission();            // I2C repeated start for read
    Wire.requestFrom(D6T_ADDR, N_READ);
    i = 0;
    while (Wire.available()) {
        rbuf[i++] = Wire.read();
    }

    if (D6T_checkPEC(rbuf, N_READ - 1)) {
        return;
    }

    // 1st data is PTAT measurement (: Proportional To Absolute Temperature)
    int16_t itemp = conv8us_s16_le(rbuf, 0);
    Serial.print("PTAT:");
    Serial.print(itemp / 10.0, 1);
    Serial.print(", Temperature:");
    
    // loop temperature pixels of each thrmopiles measurements
    for (i = 0, j = 2; i < N_PIXEL; i++, j += 2) {
        itemp = conv8us_s16_le(rbuf, j);
        pix_data[i] = itemp;
        Serial.print(itemp / 10.0, 1);  // print PTAT & Temperature
        if ((i % N_ROW) == N_ROW - 1) {
            Serial.print(" [degC]");  // wrap text at ROW end.
        } else {
            Serial.print(", ");   // print delimiter
        }
    }
    judge_seatOccupancy(); //add
    Serial.print(", Occupancy:");
    Serial.println(resultOccupancy, 1);
    delay(samplingTime);
}
// vi: ft=arduino:fdm=marker:et:sw=4:tw=80
