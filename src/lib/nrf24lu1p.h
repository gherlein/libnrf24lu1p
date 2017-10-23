/*
 * C library for Nordic nrf24lu1+ based boards
 *
 * shipping product example is the Bitcraze CrazyRadio PA
 * https://www.bitcraze.io/crazyradio-pa/
 * 
 * Copyright (C) 2017 Greg Herlein (gherlein@herlein.com)
 * 
 * Derived directly from librazyradio https://github.com/rpedde/libcrazyradio
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

#ifndef _NRF24LU1P_H_
#define _NRF24LU1P_H_

#include <stdint.h>

/* USB Vendor/Product IDs */
#define CRADIO_VID 0x1915
#define CRADIO_PID 0x7777

/* Dongle config requests
 * From https://wiki.bitcraze.io/doc:crazyradio:usb:index
 */
#define CONF_SET_RADIO_CHANNEL   0x01
#define CONF_SET_RADIO_ADDRESS   0x02
#define CONF_SET_DATA_RATE       0x03
#define CONF_SET_RADIO_POWER     0x04
#define CONF_SET_RADIO_ARD       0x05
#define CONF_SET_RADIO_ARC       0x06
#define CONF_ACK_ENABLE          0x10
#define CONF_SET_CONT_CARRIER    0x20
#define CONF_START_SCAN_CHANNELS 0x21
#define CONF_GET_SCAN_CHANNELS   0x21
#define CONF_SET_RADIO_MODE      0x22

#define AUTO_ACK_DISABLED        0x00
#define AUTO_ACK_ENABLED         0x01

#define DATA_RATE_250KBPS        0x00
#define DATA_RATE_1MBPS          0x01
#define DATA_RATE_2MBPS          0x02

#define POWER_M18DBM             0x00
#define POWER_M12DBM             0x01
#define POWER_M6DBM              0x02
#define POWER_0DBM               0x03

#define MODE_PTX                 0x00
#define MODE_PRX                 0x02

typedef struct nrf24radio_device_t {
    float firmware;
    char *serial;
    char *model;
    void *pusb_handle;
} nrf24radio_device_t;

typedef uint8_t *nrf24radio_address;

extern int nrf24radio_init(void);
extern nrf24radio_device_t *nrf24radio_get(int);
extern int nrf24radio_close(nrf24radio_device_t *);

extern void nrf24radio_set_log_method(void(*)(int, char*, va_list));
extern void nrf24radio_set_config_timeout(int timeout);
extern const char *nrf24radio_get_errorstr(void);

extern int nrf24radio_send_config(nrf24radio_device_t *prd, uint8_t request,uint16_t value, uint16_t index,unsigned char *data, uint16_t length);
extern int nrf24radio_set_channel(nrf24radio_device_t *prd, uint16_t channel);
extern int nrf24radio_set_address(nrf24radio_device_t *prd, nrf24radio_address address);
extern int nrf24radio_set_data_rate(nrf24radio_device_t *prd, uint16_t data_rate);
extern int nrf24radio_set_power(nrf24radio_device_t *prd, uint16_t power);
extern int nrf24radio_set_arc(nrf24radio_device_t *prd, uint16_t arc);
extern int nrf24radio_set_ard_time(nrf24radio_device_t *prd, int us);
extern int nrf24radio_set_ard_bytes(nrf24radio_device_t *prd, uint16_t bytes);
extern int nrf24radio_set_mode(nrf24radio_device_t *prd, uint16_t mode);


extern int nrf24radio_read_packet(nrf24radio_device_t *prd,
                              unsigned char *buffer,
                              int len, int timeout);

extern int nrf24radio_write_packet(nrf24radio_device_t *prd,
                               unsigned char *buffer,
                               int len, int timeout);


#endif /* _NRF24LU1P_H_ */
