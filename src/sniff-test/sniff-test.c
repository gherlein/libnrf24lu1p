/*
 * Example sniff program
 *
 * Copyright (C) 2016 Ron Pedde (ron@pedde.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <nrf24lu1p.h>

#define VERSION "0.1"
#define MAX_NRF24_DEVICES 4

int debug_level;

void print_log_msg(int level, char *format, va_list args) {
    if(level <= debug_level) {
        vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
    }
}

int main(int argc, char *argv[]) {
    nrf24radio_device_t *p;
    nrf24radio_device_t *dev;
    unsigned char buffer[64];
    int res;
    int radio_id = -1;
    int count=0;
    
    if(argc > 1) {
        radio_id = atoi(argv[1]);
    }

    fprintf(stderr, "rx-test: version %s\n", VERSION);

    count=nrf24radio_init();

    printf("found %d devices\n",count);

    debug_level = 5;
    nrf24radio_set_log_method(print_log_msg);

    if(count==0)
    {
      printf("No devices found\n");
      exit(-1);
    }

    if(count>1)
    {
      printf("What number device to use? ");
      int c=getchar();
      switch(c)
      {
        case 48:
          radio_id=0;
          break;
        case 49:
          radio_id=1;
          break;
        case 50:
          radio_id=2;
          break;
        case 51:
          radio_id=3;
          break;
      }
    }
    
    dev = nrf24radio_get(radio_id);
    if(!dev) {
        fprintf(stderr, "could not open device: %s\n", nrf24radio_get_errorstr());
        exit(EXIT_FAILURE);
    }

    uint8_t addr[5]={0x01,0x01,0xff,0xff,0xff};
    uint8_t *address=addr;
    
    if(nrf24radio_set_channel(dev, 100) ||
       nrf24radio_set_data_rate(dev, DATA_RATE_250KBPS) ||
       nrf24radio_set_power(dev,POWER_M12DBM) ||
       nrf24radio_set_shockburst(dev,0) ||
       nrf24radio_set_crc(dev,0) ||
       nrf24radio_set_address(dev, address) ||
       nrf24radio_set_mode(dev, MODE_PRX)) {
      fprintf(stderr, "error setting up radio: %s\n", nrf24radio_get_errorstr());
      exit(EXIT_FAILURE);
    }


    while(1) {
        res = nrf24radio_read_packet(dev, buffer, 64, 0);
        if(res < 0) {
            fprintf(stderr, "error reading: %s\n", nrf24radio_get_errorstr());
            exit(EXIT_FAILURE);
        }
        printf("received %d bytes of data: %s\n", res, buffer);
    }
}
