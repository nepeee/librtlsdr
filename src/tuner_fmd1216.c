#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "rtlsdr_i2c.h"
#include "tuner_fmd1216.h" 


int fmd1216_init(struct fmd1216_state *priv) {
	priv->lastfreq = 0;
	priv->lastband = 0;
	
	return 0;
}

int fmd1216_set_freq(struct fmd1216_state *priv, uint32_t freq) {
	uint8_t band;
	uint16_t mod;

	freq = freq + FMD1216_IF_FREQ;

	mod = freq % 31250;
	freq = freq / 31250;
	if (mod>15625)
		freq = freq + 1;
	
	fprintf(stderr, "FREQ %d\n", freq);

	if (freq!=priv->lastfreq) {
		if (freq<5760) //18000000
			band = FMD1216_BB_BAND_LOW;
		else if (freq<15296) //47800000                         
			band = FMD1216_BB_BAND_MID;
		else
			band = FMD1216_BB_BAND_HIGH;

		if (band!=priv->lastband) {
			uint8_t data[4];
			data[0] = (freq >> 8) & 0xFF; //db1
			data[1] = freq & 0xFF; //db2
			data[2] = FMD1216_CB_DEF; //cb
			data[3] = band; //bb

			if (rtlsdr_i2c_write_fn(priv->rtl_dev, FMD1216_I2C_ADDR, data, 4) < 0)
				return -1;

			priv->lastband = band; 
		}
		else {
			uint8_t data[2];
			data[0] = (freq >> 8) & 0xFF; //db1
			data[1] = freq & 0xFF; //db2

			if (rtlsdr_i2c_write_fn(priv->rtl_dev, FMD1216_I2C_ADDR, data, 2) < 0)
				return -1;			
		}
		
		priv->lastfreq = freq;
	}

	return 0;
}
