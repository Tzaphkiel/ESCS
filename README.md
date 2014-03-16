# ESCS

Electronic Source CodeS

This repository will be used mainly by me to host and track my Arduino, RPI and PIC MCU code as well as other electronics MCU projects.

It is not intended to be used (at the moment) by third parties and as such will have to be used at your own risk & peril !
I shall not be held responsible for whatever damage it may cause to your hardware or yourself.

Enjoy !

# Credits
The NRF24L01 libraries are based ont he work done on the folloging repositories:
- https://github.com/stanleyseow/RF24
- https://github.com/jonathongrigg/RF24

# Projects

## MorseMessagePlayer
This bit of code is used to replay a MCU stored message through a relay. It is controlled by a PIC16F628A MCU.
It provides an automated way of triggering an old telegraph keyer.

It is to be used during a war representation by a person demonstrating an old war telegraph by the transmission of messages through the telegraph line. It could also simulate receiving a message.

This code loops through all the (UPPER-CASE only) letters and spaces. For each letter, looks up for the corresponding morse code and 'plays' it with appropriate delays.
NB: the delays are aproximations. They do not take into account the time it takes an instruction to execute. On top of this loose timing calculations, I'm using the internal 4Mhz oscillator to restrict the number of needed components.
