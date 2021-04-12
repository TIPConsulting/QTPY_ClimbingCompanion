# QTPY Climbing Companion

Signaling device for climbers to communicate when voice commands or hand signs are not feasible.  This is a discreet helmet augmentation that adds simple radio signaling to your existing helmet.  Climbing Companion uses small touch sensors and vibrators to send left hand or right hand signals.  These can be combined to communicate arbitrary commands to your partner.  The nRF24+ radio module can reach up 100m, so you'll never have to worry about signalling again on long routes.

![Component Layout](https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/ComputeCapsule/Capsule%20Layout.png?raw=true)

## Inspiration

Climbing Companion is inspired by own experiences climbing across Colorado.  Its common to find yourself climbing near loud rivers or busy roads where its difficult for belayers and climbers to hear each other.  Furthermore, many routes are shaped such that partners can't see each other after the first 40ft of climbing.  When these obstacles intersect, belayers are forced to make critical safety decisions based on intuition.  Many climbers have died due to such communication failures.

Climbing Companion provides a stable platform for partners to signal each other when primary methods are unreliable.  Some climbers elect to carry 2-way hand radios, but these can be bulky and present a new safety risk if they are dropped or they could injure the climber during a fall.  Climbing Companion opts for a more streamlined approach than conventional radios.  By only supporting a small set of signaling features, we are able to squeeze our hardware into a tiny package and integrate it directly into a helmet.  This means that the device is also right where it needs to be - it won't shift around, it won't fall off a harness, and it won't get in your way.

The goal is not to replace all voice commands or hand signals, but rather supplement them during safety critical operations like setting anchors or cleaning routes.  The following image shows a scenario in which Climbing Companion would be ideal - the belayer is not visible and a fast river drowns out any voice commands.  Our radio module would allow the climber to signal when he sets his anchor or needs a rest.

<img src="https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/Climber.jpg?raw=true" alt="Test Rig" width="400px">


## Hardware

- 2x [QT Py Microcontroller](https://www.adafruit.com/product/4600)
- 2x [RF24 Radio Modules](https://www.amazon.com/Makerfire-Arduino-NRF24L01-Wireless-Transceiver/dp/B00O9O868G)
- 2x 150mAH Lipo Battery
- 2x Slide Switch
- 4x [Vibrator Disc](https://www.amazon.com/tatoko-12000RPM-Wired-Phone-Vibration/dp/B07L5V5GYG/)
- 4x Touch Sensor / Conductive Strips

![Component Explosion](https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/ComputeCapsule/Redux%20Explosion.gif?raw=true)

