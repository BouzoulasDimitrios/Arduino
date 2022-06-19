# Arduino
This is a strain gauge measurement device. This device uses strain gauges in order to to measure strain. 

![1](https://github.com/BouzoulasDimitrios/Arduino/blob/main/pictures/placement.jpg)

The device has the inputs and as a result it can take 3 simoultanious readings.

The control of the device is being done using a phone application that connects to the device via bluetooth.

![2](https://github.com/BouzoulasDimitrios/Arduino/blob/main/pictures/screenshot_app.PNG)

The sensors that are used in this application are strain gage resistors. They have a default resistance of 120Ohm and a Gauge Factor of 2 ( GF = 2 ) and the device is 
built specifically for these sensors. The resistance of these sensors changes as they get streched and as a result we can use that change in resistance to measure the 
strain of a material.(https://www.youtube.com/watch?v=z603U-Am3AY)

 The device consists of 3 wheatstone bridges that each has 3 resistors that are 120Ohm each and have 0.1% tolerance (only resistors with tolerance <=0.1% are acceptable 
for these applications). In every wheatstone bridge the 4rth resistor is replaced by the stain gage sensor that is attached to the test sample or structure being tested. 
As a result if the device is measuring 3 sensors there will be 3 complete wheatstone bridges. What the wheatstone bridges do is that they allow us to measure the 
resistance changes in the stain gages.(https://www.youtube.com/watch?v=ZqAM_wQ35ow)

The change in the resistance of the sensor and as a result the change in the voltage difference in the wheatstone bridge is being passed though the HX711 signal 
amplifier, this is being done because the 'brains' of the device, the arduino uno is incapable of measuring very small changes in voltage.

After we recieve the voltage diffrence in the arduino using a simple math model that gives us the strain. After that the measurements are displayed om the phone of
the user.
 






