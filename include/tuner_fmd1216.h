/*
 * Philips FMD1216 driver
 *
 * Copyright (C) 2013 Mauro Carvalho Chehab <mchehab@redhat.com>
 * Copyright (C) 2013 Steve Markgraf <steve@steve-m.de>
 *
 * This driver is a heavily modified version of the driver found in the
 * Linux kernel:
 * http://git.linuxtv.org/linux-2.6.git/history/HEAD:/drivers/media/tuners/r820t.c
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FMD1216_H
#define FMD1216_H

#define FMD1216_I2C_ADDR 0xC2

#define FMD1216_BB_BAND_LOW 0x01 //P2P1P0=001
#define FMD1216_BB_BAND_MID 0x02 //P2P1P0=010
#define FMD1216_BB_BAND_HIGH 0x04 //P2P1P0=100
#define FMD1216_CB_DEF 0xB0 // CP=0, T2T1T0=110, RSARSB=00, OS=0 - 125khz tune

#define FMD1216_IF_FREQ 36000000 //36MHz

struct fmd1216_state {
	uint16_t lastfreq;
	uint8_t lastband;
	void *rtl_dev;
};

int fmd1216_init(struct fmd1216_state *priv);
int fmd1216_set_freq(struct fmd1216_state *priv, uint32_t freq);

#endif
