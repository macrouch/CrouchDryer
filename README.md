# CrouchDryer
Particle Photon code to have a tweeting clothes dryer.

This project uses an accelerometer to detect if a clothes dryer is moving, and report when it stops, hopefully after the cycle has finished.

## Wiring
The power from the accelerometer is connected to A0.

The ground from the accelerometer is connected to A2.

The Z-Axis from the accelerometer is connected to A1.

## Notifications
I use an [IFTTT recipe](https://ifttt.com/recipes/255411-send-tweet-when-spark-core-sends-an-event) to watch for the published event and then send a tweet. Subscribe to mobile notifications to receive a text message (or use [this receipe](https://ifttt.com/recipes/319097-if-particle-event-is-published-then-send-me-an-sms) to just get a text message from IFTTT).
