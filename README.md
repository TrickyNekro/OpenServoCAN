# OpenServoCAN
by El. Provatos

<b>!!! Currently two versions of the Hardware exist, development is going to continue on version 2 !!!</b>

An alternative to the boring control boards inside standard size hobby servos!

As it is, the project is far from completion! I have the first boards already, but I do not
have the materials to populate them. I will most probably start a gofundme campaign for these
first stages of the project. So bear with me, this will be an on-going process!

It was a very long time I wanted to make a project like this
Most, for the more expensive ones, hobby servos offer no feed back.
You send them a signal and hope they will reach the targeted position.
This might be good enough for uses in the RC world, but not good enough 
at all for those building robots or anything of a kind that needs feedback.

And thus this project was born! Although I am aware that another OpenServo Project
exists, I wanted to put my own touch into the matter and I tried to do quite a few 
things better, at least compared to the first version (I have not reviewed the second).

- Hardware V1 Capabilities

1) Added CAN-Bus! Yes, that´s a good thing! It might complicate some things especially for beginners
but that´s on what most "unobtainium" servos work in the market. I have not yet decided the 
communications protocol, but I am leaning towards CANopen, suggestions are open!

2) Can support either a potentiometer or an encoder (quadrature or not) for positional control

3) Can operate from 5V - 15V safe zone, but most probably will not have a problem with a 4S LiPo.
Current limiting will be done by software so, if you want to break the DC motor inside or not is
totally up to you!

4) Beefed up MOSFETs with individual MOSFET drivers, just to be able to push that switching 
frequency to the right spot without worrying too much!

- Hardware V2 Capabilities ( added on top of the previous! )

1) Modular! Yes, Modular! There is a Power Board, a CPU / MCU board and a Sensor / Encoder Board.
All are connected on the same bus, through some nice 0,5mm pitch - 30 pin Amphenol connectors. 
That also means of course that everything can change, and the version in connected to the function
specific board and not the whole system. Bored of the microcontroller? Change the MCU board, need
higher voltage? Change the power board? Need more capabilities? If physically allowed, add more
boards! Etc. etc. etc.. 

2) This version uses a magnetic encoder from AMS! Have not tested it yet, but given that it works
well without much interference from the motor, it should be able to give both precision, speed and
universality to the adaptation of the design. And do not forget... bored of the encoder board? Need
something more simple? Design and change it with a potentiometer board! Easy Peasy!!! 

3) One of the main limitation of the previous version was the input voltage. 15V max? How boring! 
This version was aimed to work with 24V and pushing it to 30V should be no problem! Unfortunately
the 100% duty cycle capability is gone as well, but the more efficient all N-Channel MOSFET bridge
should be able to make up the difference! Even if it does not, this was the one big step in being
able to bridge the design to a higher operating voltage, given the much constrained space.

4) There is a digital power meter from Texas Instruments on-board, should offload the processor 
quite a bit! And has also some quite interesting interrupt capabilites that should come in handy.

5) MCU board now has, EEPROM, battery (or better Super-Cap) backed RTC, a temperature sensor and
an RGB LED! How can one live without RGB these days. In all seriousness though, the RTC and EEPROM
should be a good compination for logging data / events and or even be used to wake the device up,
or even be able to develop small scripts for the device to run autonomously. But that´s only a dream
for now, still capability is there!

6) Reverse polarity protection is still here! But I also added some small extras! Some "TVS - like"
suppressors here, some more distributed capacitance there. It should be less noisy and more stable.
Only time will tell as more and more code and testing is being done!

<b> Important 2/11/2020 Update! </b>
I have officially ended the fundraiser for this Project. True to my promise I would like to thank:
Juri Ludwig, Anonymous (from eevblog ;-) ), Vagelis Logaras and Andreas Efthymiadis for their contributions.
Their money have funded a couple mouser orders, the PCBs and some test servos. Which for me is more than
enough that anyone would do for an open project with an open completion date! I can only promise that I
will continue to deliver as much as real life allows me. Thank you! Let your names be immortalized here!



# Donations!

<b>No project on the internet would be great without donations! And Crypto is the future! </b>

In Elon Musk We Trust Dogecoin (DOGE) : DQTDoTPzMencAXoiDVByQjifk2DryYTUPZ <br>
For the old timers Bitcoin (BTC)      : bc1qxqq8dz8md20nyglan9hmk88s894f8h0ywm0fq3 <br>
For the Russian hackers Ethereum(ETH) : 0xAA05e9abD960005df318Ab82aE35A8c47e0096AB <br>
