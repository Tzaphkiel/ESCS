# ESCS

Electronic Source CodeS

This repository will be used mainly by me to host and track my Arduino, RPI and PIC MCU code and various electronics MCU projects.

It is not intended to be used (at the moment) by third parties and as such will have to be used at your own risk & peril !
I shall not be hels responsible for whatever damage it may cause to your hardware or yourself.


The NRF24L01 libraries are based ont he work done on the folloging repositories:
- https://github.com/stanleyseow/RF24
- https://github.com/jonathongrigg/RF24

Enjoy !

## MorseDemoTicker.c
This bit of code is used to have a relay controlled by a PIC MCU and thus provide an automated way of triggering the old telegraph key.

Such a device could then have a pre-recorded sentence and replay it in a loop thus demoing the keyer, sounder and transmission of messages through the line. It could hence simulate receiving a message for example.

This code loops through all the (UPPER-CASE) letters and spaces and for each, looks up the corresponding morse code and 'plays' it with appropriate delays.
NB: the delays are aproximate since the time to make api calls are not taken into account and we are anyway using the internal oscillator.
