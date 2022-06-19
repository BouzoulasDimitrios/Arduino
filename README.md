# Arduino

This is a strain gauge measurement device. This device uses strain gauges in order to to measure strain. 

![1](https://github.com/BouzoulasDimitrios/Arduino/blob/main/pictures/placement.jpg)

The device has the inputs and as a result, it can take 3 simultaneous readings.

The control of the device is being done using a phone application that connects to the device via Bluetooth.

![2](https://github.com/BouzoulasDimitrios/Arduino/blob/main/pictures/screenshot_app.PNG)

The sensors that are used in this application are strain gauge resistors. They have a default resistance of 120Ohm and a Gauge Factor of 2 ( GF = 2 ) and the device is 
built specifically for these sensors. The resistance of these sensors changes as they get stretched and as a result, we can use that change in resistance to measure 
the strain of the material.(https://www.youtube.com/watch?v=z603U-Am3AY)

The device consists of 3 Wheatstone bridges that each has 3 resistors that are 120Ohm each and have 0.1% tolerance (only resistors with tolerance <=0.1% are 
acceptable for these applications). In every Wheatstone bridge, the 4rth resistor is replaced by the strain gauge sensor that is attached to the test sample or 
structure being tested. As a result, if the device is measuring 3 sensors there will be 3 complete Wheatstone bridges. What the Wheatstone bridges do is that they 
allow us to measure the resistance changes in the strain gages. (https://www.youtube.com/watch?v=ZqAM_wQ35ow)

The change in the resistance of the sensor and as a result, the change in the voltage difference in the Wheatstone bridge is being passed through the HX711 signal 
amplifier, this is being done because the 'brains' of the device, the Arduino Uno is incapable of measuring very small changes in voltage.

After we receive the voltage difference in the Arduino using a simple mathematical model that gives us the strain. After that, the measurements are displayed on the 
phone of the user.

The user has 3 options while using the application. 

1) recalibrate: it recalibrates the device similar to a way you can set a kitchen scale to zero. ex: we can place a load on our structure and have the device measure from that point as the start.
2) start recording readings to start recording the measurements to the sd card that the device has.
3) stop recording readings to stop recording the measurements to the sd card.

the schematic of the device:

![3](https://github.com/BouzoulasDimitrios/Arduino/blob/main/pictures/schematic.PNG)

mit app inventor blocks: 

![4](https://github.com/BouzoulasDimitrios/Arduino/blob/main/pictures/3%20readings%20recalibrate%20button.PNG)

Connections:

![5](https://github.com/BouzoulasDimitrios/Arduino/blob/main/pictures/279670787_1705312476483181_8966646382633138351_n.jpg)

