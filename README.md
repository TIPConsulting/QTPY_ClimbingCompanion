# QTPY Climbing Companion

Signaling device for climbers to communicate when voice commands or hand signs are not feasible.  This is a discreet helmet augmentation that adds simple radio signaling to your existing helmet.  Climbing Companion uses small touch sensors and vibrators to send left hand or right hand signals.  These can be combined to communicate arbitrary commands to your partner.  The nRF24+ radio module can reach up 100m, so you'll never have to worry about signaling again on long routes.

![CommExample](https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/CommExample.JPG?raw=true)

## Inspiration

Climbing Companion is inspired by own experiences climbing across Colorado.  Its common to find yourself climbing near loud rivers or busy roads where its difficult for belayers and climbers to hear each other.  Furthermore, many routes are shaped such that partners can't see each other after the first 40ft of climbing.  When these obstacles intersect, belayers are forced to make critical safety decisions based on intuition.  Many climbers have died due to such communication failures.

Climbing Companion provides a stable platform for partners to signal each other when primary methods are unreliable.  Some climbers elect to carry 2-way hand radios, but these can be bulky and present a new safety risk if they are dropped or they could injure the climber during a fall.  Climbing Companion opts for a more streamlined approach than conventional radios.  By only supporting a small set of signaling features, we are able to squeeze our hardware into a tiny package and integrate it directly into a helmet.  This means that the device is also right where it needs to be - it won't shift around, it won't fall off a harness, and it won't get in your way.

The goal is not to replace all voice commands or hand signals, but rather supplement them during safety critical operations like setting anchors or cleaning routes.  The following image shows a scenario in which Climbing Companion would be ideal - the belayer is not visible and a fast river drowns out any voice commands.  Our radio module would allow the climber to signal when he sets his anchor or needs a rest.

<img src="https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/Climber0.jpg?raw=true" alt="Climber" width="400px">


## Hardware

- 2x [QT Py Microcontroller](https://www.adafruit.com/product/4600)
- 2x [RF24 Radio Modules](https://www.amazon.com/Makerfire-Arduino-NRF24L01-Wireless-Transceiver/dp/B00O9O868G)
- 2x 150mAH Lipo Battery
- 2x Slide Switch
- 4x [Vibrator Disc](https://www.amazon.com/tatoko-12000RPM-Wired-Phone-Vibration/dp/B07L5V5GYG/)
- 4x Touch Sensor / Conductive Strips

![Component Layout](https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/ComputeCapsule/Capsule%20Layout.png?raw=true)

## Design

From the very outset, we knew that Climbing Companion would have to prioritize form factor and energy use over features.  We chose small, low power components to meet the functional requirements and nothing more.  That allows us pack our device into a tiny case - its so small that it can fit it a helmet vent!  Small parts also means low weight; the compute capsule _weighs 24g_, that's less than a locking carabiner!  You won't even notice that it's there unless your partner is signaling to you.  And our long battery life means that your partner can signal all day long, no matter how early you hit the crag.

We designed and printed an enclosure for a hemlet we have on-hand, but similar cases could be made a varity of helmets, allowing Climbing Companion to seamlessly integrate with your existing gear.

![Capsule Render](https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/ComputeCapsule/Capsule%20Drawing.JPG?raw=true)

![Helmet Render](https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/Helmet_DesignRender.PNG?raw=true?raw=true)

## Build Process

![Component Explosion](https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/ComputeCapsule/Redux%20Explosion.gif?raw=true)

![Helmet Explosion](https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/Helmet_Explosion.gif?raw=true)

### Electronics

The electronics are not terribly difficult to assemble. Simply follow the standard nRF24+ wiring diagram to connect the RF module to the QT Py controller.  The connecting wires should be short so the devices can be compacted together in the case.  After connected the RF, attach leads to the QT Py for the vibrators and touch sensors.  These will need to be longer so they can extend outside of the case.  Finish off by adding a battery connector and power switch.

<img src="https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/WireDiagram.jpg?raw=true" alt="Wire Diagram" width="520px"> <img src="https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/NakedComponents%20(Medium).JPG?raw=true" alt="Electronics" width="400px">

### Compute Capsule

For the best integration possible, each compute capsule is designed to fit a specific helmet and vent.  It is critical to get a capsule that perfectly fits the helmet vent and provides enough room for the components.  It took half a dozen prototypes before we were satisfied with the fit and finish of our capsule.


### Compute Capsule Assembly

Once the components are soldered together and the case fit is perfected, the electronics will need to be inserted into the case.  We designed holes into the back of our capsule to allow vibrator and sensor wires to pass through unobtrusively.  We passed these wires through the shell first and used them to gently pull everything into place.  Only after this step should the final components be added.  If you were to add the vibrators and sensors too early, you would not be able to properly assemble the device.

1. 

<img src="https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/Capsule_Top%20(Medium).JPG?raw=true" alt="Compute Capsule Top" width="400px"> <img src="https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/Capsule_Front%20(Medium).JPG?raw=true" alt="Compute Capsule Front" width="400px">

2.
![Electronics Assembly](https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/AssembledComponents%20(Medium).jpg?raw=true)

### Helmet Integration

Now that the compute capsule is assembled, we can add integrate it into our helmet.  Align the compute capsule with the back of the helmet in the proper vent slot.  Insert the wires through the vent first and gently pull them from the inside as you guide the capsule into position.  Once fully seated, the compute capsule should wedge into position - the friction alone is enough to keep it in place.  Now route the touch pads and vibration modules to their respective locations and affix them using your preferred adhesive.


![Electronics Assembly](https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/Helmet_FinSide%20(Medium).jpg?raw=true)

<img src="https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/Helmet_FinBackOblR%20(Medium).jpg?raw=true" alt="Helmet Side" width="400px"> <img src="https://github.com/TIPConsulting/QTPY_ClimbingCompanion/blob/master/Documents/Helmet_FinBack%20(Medium).JPG?raw=true" alt="Helmet Back" width="400px">

## Final Testing

TODO

## Conclusions

TODO
