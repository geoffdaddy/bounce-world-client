#include <conio.h>
#include <stdint.h>
#include "chardef.h"
#include <video/tms99x8.h>
#include "conio_helpers.h"
#include <sys/ioctl.h>
#include <eos.h>

#ifdef __ADAM__

void init_vdp()
{
    //set up the vdp vram with tile data, both tile and color... change to mode 1 first thing.
    //change background to medium green...
    int mode = 1;
    console_ioctl(IOCTL_GENCON_SET_MODE, &mode);
    void *param = &bounce_udgs;
    console_ioctl(IOCTL_GENCON_SET_UDGS,&param);
    vdp_color(VDP_INK_WHITE,VDP_INK_MEDIUM_GREEN,VDP_INK_MEDIUM_GREEN);

	//doesn't have to do with the video in any case, but a helpful place to stash it...
	eos_start_read_keyboard();
}

void cputsxy(uint8_t x, uint8_t y, char *s) {
	gotoxy(x, y);
	cputs(s);
}

void cputcxy(uint8_t x, uint8_t y, char c) {
	gotoxy(x, y);
	cputc(c);
}

void gotox(unsigned char x)
{
	gotoxy(x,wherey());
}

unsigned char doesclrscrafterexit(void) {
	return 1;
}

void chlinexy(unsigned char x, unsigned char y, unsigned char length) {
	gotoxy(x, y);
	while(length--)
		cputc(CH_HLINE);
}

unsigned char revers(unsigned char onoff)
{
	return 0;
}

#endif
