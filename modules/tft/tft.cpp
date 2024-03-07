//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "font.h"
#include "tft.h"

//=====[Declaration of private defines]========================================

#define TFT_RES_H 240
#define TFT_RES_V 320

#define SPI1_MOSI PA_7
#define SPI1_MISO PA_6
#define SPI1_SCK  PA_5
#define SPI1_CS   PD_14

#define NO_OP 0x00
#define SW_RST 0x01
#define SLP_OUT 0x11
#define NORM_ON 0x13
#define INV_OFF 0x20
#define INV_ON 0x21
#define DISP_ON 0x29
#define CA_SET 0x2A
#define RA_SET 0x2B
#define RAM_WR 0x2C
#define COL_MOD 0x3A


//=====[Declaration of private data types]=====================================




//=====[Declaration and initialization of public global objects]===============

SPI tft_spi(SPI1_MOSI, SPI1_MISO, SPI1_SCK);
DigitalOut tft_cs(SPI1_CS);
DigitalOut tft_rst(D8);
DigitalOut tft_dc(D9);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static void tftReset();
static void tftCommand(uint8_t cmd);
static void tftData(uint8_t arg);
static uint16_t tftDrawChar(uint16_t x0, uint16_t y0, char l, uint16_t c);

//=====[Implementations of public functions]===================================

void tftInit() {
    tftReset();
    tftCommand(SW_RST);
    delay(200);
    tftCommand(SLP_OUT);
    delay(20);
    tftCommand(COL_MOD);
    tftData(0x05);
    delay(20);
    tftSetRect(0, 0, 240, 320);
    delay(20);
    tftCommand(NORM_ON);
    delay(20);
    tftCommand(INV_ON);
    delay(20);
    tftCommand(DISP_ON);
    delay(20);
    tftShadeRect(0, 0, 240, 320, 0x0000);
}

void tftSetRect(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye) {
    if ((xs >= xe) || (ys > ye)) return;
    tftCommand(RA_SET);
    tftData((ys >> 8) & 0xFF);
    tftData(ys & 0xFF);
    tftData((ye >> 8) & 0xFF);
    tftData(ye & 0xFF);
    tftCommand(CA_SET);
    tftData(0x00);
    tftData(xs & 0xFF);
    tftData(0x00);
    tftData(xe & 0xFF);
}

void tftShadePixel(uint16_t x, uint16_t y, uint16_t c) {
    tftSetRect(x, x + 1, y, y + 1);
    tftCommand(RAM_WR);
    tftData((c >> 8) & 0xFF);
    tftData(c & 0xFF);
}

void tftShadeRect(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t c) {
    tftSetRect(xs, ys, xe, ye);
    tftCommand(RAM_WR);
    for (int i = 0; i < ((xe - xs)*(ye - ys)); i++) {
        tftData((c >> 8) & 0xFF);
        tftData(c & 0xFF);
    }
}

void tftDrawString(uint16_t x, uint16_t y, uint16_t c, char *str, int len) {
    for (int i = 0; i < len; i++) {
        x += 2 * tftDrawChar(x, y, str[i], c);
    }
}

void tftDrawCenteredString(uint16_t x, uint16_t y, uint16_t c, char *str, int len) {
    uint16_t d = 0;
    for(int i = 0; i < len; i++) {
        int mx = ((uint8_t) str[i]) - 32;
	    const uint16_t *chp = font[mx];
         d += chp[15];
    }
    tftDrawString(x - d, y, c, str, len);

}

//=====[Implementations of private functions]==================================

static void tftReset() {
    tft_rst.write(false);
    delay(10);
    tft_rst.write(true);
    delay(20);
}

static void tftCommand(uint8_t cmd) {
    tft_cs.write(false);
    tft_dc.write(false);
    tft_spi.write(cmd);
    tft_cs.write(true);
}

static void tftData(uint8_t arg) {
    tft_cs.write(false);
    tft_dc.write(true);
    tft_spi.write(arg);
    tft_cs.write(true);
}

static uint16_t tftDrawChar(uint16_t x0, uint16_t y0, char l, uint16_t c) {
	int mx = ((uint8_t) l) - 32;
	const uint16_t *chp = font[mx];
    uint16_t ret = chp[15];
    tftSetRect(x0, y0, x0 + 31, y0 + 32);
    tftCommand(RAM_WR);
    for(int j = 0; j < 15; j++) {
		uint16_t row = chp[j];
		uint16_t test = 0b1000000000000000;
		for(int i = 0; i < 16; i++) {
			if((row & test)==test) {
                tftData((c >> 8) & 0xFF);
                tftData(c & 0xFF);
                tftData((c >> 8) & 0xFF);
                tftData(c & 0xFF);
            } else {
                tftData(TXT_BGND);
                tftData(TXT_BGND);
                tftData(TXT_BGND);
                tftData(TXT_BGND);
            }
			test >>= 1;
		}
        test = 0b1000000000000000;
        for(int i = 0; i < 16; i++) {
			if((row & test)==test) {
                tftData((c >> 8) & 0xFF);
                tftData(c & 0xFF);
                tftData((c >> 8) & 0xFF);
                tftData(c & 0xFF);
            } else {
                tftData(TXT_BGND);
                tftData(TXT_BGND);
                tftData(TXT_BGND);
                tftData(TXT_BGND);
            }
			test >>= 1;
		}
	}
	return ret;
}
