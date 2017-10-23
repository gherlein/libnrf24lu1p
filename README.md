# libnrf24lu1p #

This library allows USB-driven use of the Nordic Semi NRF24LU1+
chipset from linux user space.  This work is heavily derived from the
excellent work done by Ron Pedde's [libcrazyradio](https://github.com/rpedde/libcrazyradio).

This library is intended to continue to support the Crazyflie2 as well
as to support other modes of radio operation.  Other projects that we
aim compatability with include:

* [nRF24 Library](https://github.com/nRF24)
* [NRF24 Sniffer](https://github.com/Yveaux/NRF24_Sniffer)
* [Cheerson CX-10A Quadcopter](https://www.amazon.com/dp/B00WQX7WMI/_encoding=UTF8?coliid=I11LFTLXRCE300&colid=2WORUWOFT4693)
* Home Automation and IoT network sensor networks

The existing libcrazyradio is awesome, but I desired to extend it to
support many modes of operation in addition to the Bitcraze model. 

## Hardware ##

The only product I currently know of that uses this chip in this mode
is the [Bitcraze CrazyRadio
PA](https://www.bitcraze.io/crazyradio-pa).

The NRF24LU1+ natively supports USB and has an internal 8051-compatible core that makes it
highly adaptable for many uses.  The CrazyRadio
[firmware](https://github.com/bitcraze/crazyradio-firmware) implements
a specific profile that supports connection to the [Crazyflie2
Quadcopter](https://www.bitcraze.io/crazyflie-2/).

## Building ##

To build the library you need the standard GNU autotools/autoconf
suite.  Currently it is tested on linux only.

````bash
./autogen.sh
./configure
make
sudo make install
````
If you need to clean up and recompile, you can return to the vanilla
github repo state by 

````bash
./wipe-clean
````

## Test Programs ##

There are two test programs:  rx-test and tx-test.  They should be
built automatically with a make but not installed. On the receiver side:

````bash
src/tx-test/tx-test 
````

On the transmit side:

````bash
src/rx-test/rx-test 
rx-test: version 0.1
Found device: Crazyradio PA USB Dongle
Serial: 45BCC85B98
Firmware Version: 99.55
received 9 bytes of data: packet 0
received 9 bytes of data: packet 1
received 9 bytes of data: packet 2
received 9 bytes of data: packet 3
received 9 bytes of data: packet 4
received 9 bytes of data: packet 5
````

If you desire to run both devices from one linux system, you can
append the radio number on the command line:

````bash
src/tx-test/tx-test 0
````

and 

````bash
src/rx-test/rx-test 1 
````

## Credits ##

Bitcraze deserves huge kudos for releasing the CrazyRadio PA.  Ron
Pedde deserves all the credit for creating libcrazyradio from which
this is derived.  

## License ##

This software retains the GPLv3 license from libcrazyradio.




