// #include <conio.h>
#include <stdint.h>
#include "chardef.h"
#include <video/tms99x8.h>
#include "conio_helpers.h"
#include <sys/ioctl.h>
#include <eos.h>
// #include <common/types.h>

#ifdef __ADAM__

static uint8_t x_pos;
static uint8_t y_pos;
extern uint8_t is_alt_screen;

void init_vdp()
{
  //set up the vdp vram with tile data, both tile and color... change to mode 1 first thing.
  //change background to medium green...
  int mode = 1;
  uint8_t chr = 0;
  console_ioctl(IOCTL_GENCON_SET_MODE, &mode);
  void *param = &bounce_udgs;
  console_ioctl(IOCTL_GENCON_SET_UDGS,&param);
  vdp_color(VDP_INK_WHITE,VDP_INK_MEDIUM_GREEN,VDP_INK_MEDIUM_GREEN);
  //doesn't have to do with the video in any case, but a helpful place to stash it...
  eos_start_read_keyboard();
}

void cputsxy(uint8_t x, uint8_t y, char *s) {
  uint16_t vramaddr;
  uint16_t count = strlen(s);
  x_pos = x;
  y_pos = y;
  if (is_alt_screen)
    vramaddr = 0x1c00;
  else
    vramaddr = 0x1800; //base address for name table in mode 1
  vramaddr += (y_pos << 5) + x_pos;
  if ((vramaddr + count) > 0x1800+768)
    return;
	// gotoxy(x, y);
	// cputs(s);
  vdp_vwrite(s, vramaddr,count);
  //update x/y
  y_pos += (count + x_pos) / 32;
  x_pos = (x_pos + count) % 32;
}

void cputcxy(uint8_t x, uint8_t y, char c) {
	// gotoxy(x, y);
	// cputc(c);
  // char temp[2];
  // temp[0] = c;
  // temp[1] = 0;
  x_pos = x;
  y_pos = y;
  cputc(c);

}

int cputc(char c)
{
  uint16_t vramaddr;
  char temp = c;

  if (is_alt_screen)
    vramaddr = 0x1c00;
  else
    vramaddr = 0x1800; //base address for name table in mode 1
  vramaddr += (y_pos << 5) + x_pos;
  vdp_vwrite(&temp, vramaddr,1);
  //update x/y
  if(x_pos == 31)
  {
    x_pos = 0;
    y_pos++;
  } else 
    x_pos++;
  if (y_pos > 23) y_pos = 0; //wrap the display

  return 1;
}

void gotox(unsigned char x)
{
  x_pos = x;
	// gotoxy(x,wherey());
}

unsigned int wherex(void)
{
  return x_pos;
}

unsigned int wherey(void)
{
  return y_pos;
}

void gotoxy(unsigned int x, unsigned int y)
{
  x_pos = x;
  y_pos = y;
}

void putch(char c)
{
  cputc(c);
}

unsigned char doesclrscrafterexit(void) {
	return 1;
}

void chlinexy(unsigned char x, unsigned char y, unsigned char length) {
	// gotoxy(x, y);
  x_pos = x;
  y_pos = y;
  while(length--)
		cputc(CH_HLINE);
}

unsigned char revers(unsigned char onoff)
{

	return 0;
}

void clrscr(void)
{
  uint16_t vramaddr;

  if (is_alt_screen)
    vramaddr = 0x1c00;
  else
    vramaddr = 0x1800; //base address for name table in mode 1

  vdp_vfill(vramaddr,0,0x300);
}

#endif
