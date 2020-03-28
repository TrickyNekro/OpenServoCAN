# OpenServoCAN
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

1) Added CAN-Bus! Yes, that´s a good thing! It might complicate some things especially for beginners
but that´s on what most "unobtainium" servos work in the market. I have not yet decided the 
communications protocol, but I am leaning towards CANopen, suggestions are open!

2) Can support either a potentiometer or an encoder (quadrature or not) for positional control

3) Can operate from 5V - 15V safe zone, but most probably will not have a problem with a 4S LiPo.
Current limiting will be done by software so, if you want to break the DC motor inside or not is
totally up to you!

4) Beefed up MOSFETs with individual MOSFET drivers, just to be able to push that switching 
frequency to the right spot without worrying too much!
