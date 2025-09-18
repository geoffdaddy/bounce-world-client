#include "double_buffer.h"
#include "playfield_clr.h"
#include <video/tms99x8.h>


uint8_t is_alt_screen;

void swap_buffer()
{
  is_alt_screen = !is_alt_screen;

}

void show_other_screen()
{
  if (is_alt_screen)
    vdp_set_reg(2,7); //1c00
  else
    vdp_set_reg(2,6); //1800
}

void playfield_clr()
{
  clrscr();
}
