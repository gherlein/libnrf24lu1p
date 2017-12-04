/*
 * Example receiver program
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
#include <string.h>

#include <nrf24lu1p.h>

#define VERSION "0.1"
#define MAX_NRF24_DEVICES 4
#define PRINT_PAYLOAD



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
    int lost=0;
    char serialnum[12];
    
    
    if(argc > 1) {
      strcpy(serialnum,argv[1]);
    }

    fprintf(stderr, "rx-test: version %s\n", VERSION);

    count=nrf24radio_init();

    printf("found %d devices\n",count);

    // set debug_level to 5 for lots of logs, to 0 for nothing
    debug_level = 0;
    nrf24radio_set_log_method(print_log_msg);

    if(count==0)
    {
      printf("No devices found\n");
      exit(-1);
    }

    for(int x=0;x<count;x++)
    {
      dev = nrf24radio_get(x);
      if(!dev) {
        fprintf(stderr, "could not open device: %s - skipping\n", nrf24radio_get_errorstr());
        continue;
      }
      printf("Found device: %s\n", dev->model);
      printf("Serial: [%s] \n", dev->serial);
      printf("Firmware Version: %g\n", dev->firmware);
      int n=strcmp(serialnum,dev->serial);
      if(n==0) {
        radio_id=x;
      }
      nrf24radio_close(dev);
      if(radio_id>=0) break;
    }
    printf("radio_id: %d\n",radio_id);
    fflush(stdout);
    
    if(count>1 && radio_id<0)
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
    
    printf("opened device [%s] in PRX mode\n",dev->serial);
    
    uint8_t addr[5]={0x01,0x01,0x01,0x01,0x01};
    uint8_t *address=addr;

    
    if(nrf24radio_set_channel(dev, 100) ||
       nrf24radio_set_data_rate(dev, DATA_RATE_250KBPS) ||
//       nrf24radio_set_data_rate(dev, DATA_RATE_1MBPS) ||
//       nrf24radio_set_data_rate(dev, DATA_RATE_2MBPS) ||
       nrf24radio_set_power(dev,POWER_M18DBM) ||
//       nrf24radio_set_power(dev,POWER_0DBM) ||
//       nrf24radio_set_address(dev, address) ||
       nrf24radio_set_mode(dev, MODE_PRX)) {
      fprintf(stderr, "error setting up radio: %s\n", nrf24radio_get_errorstr());
      exit(EXIT_FAILURE);
    }

    while(1);

    
    int val=0;
    while(1) {
        res = nrf24radio_read_packet(dev, buffer, 64, 0);
        if(res < 0) {
            fprintf(stderr, "error reading: %s\n", nrf24radio_get_errorstr());
            exit(EXIT_FAILURE);
        }
#ifdef PRINT_PAYLOAD
        printf("Payload:  [%s]\n",buffer);
#endif        
      
        int got=atoi(buffer);
        printf("expected %d - got %d\n",val,got);
        val=got;
        if(val!=got)
        {
          int l=got-val;
          lost+=l;
        }
        printf("lost %d packets so far\n",lost);

        memset(buffer,0x00,64);
        sprintf(buffer,"got %d",val);
        printf("writing [%s]\n",buffer);
        
        res=nrf24radio_write_packet(dev, buffer, strlen((char*)buffer) + 1, 1000);
        printf("res: %d\n",res);
        
        if(res < 0) {
            fprintf(stderr, "error writing: %s\n", nrf24radio_get_errorstr());
            exit(EXIT_FAILURE);
        }
    }
}
