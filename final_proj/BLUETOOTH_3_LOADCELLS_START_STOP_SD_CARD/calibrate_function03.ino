#include <SD.h>
//will be used in final 
long sample = 0 ;
long sample_temp;
int x;
int e1,e2,e3,e4;
//
long sample1 = 0; // Sample for calibrating
long count = 0; // Instant Reading value
//
long sample2=0; // Sample for calibrating
long count2=0; // Instant Reading value
//
long sample3=0; // Sample for calibrating
long count3=0; // Instant Reading value
//
unsigned long time_from_reading_start;
unsigned long general_time;
char Incoming_value = 0;
int memory_controller;
int readings_counter;
File myFile;
//
byte DT1=14;
byte SCK1=15;
byte DT2=16;
byte SCK2=17;
byte DT3=18;
byte SCK3=19;
//
//takes reading
unsigned long readrealcount(int x){
  if(x==1){
    SCK1=15;
    DT1=14;    
  }
  if(x==2){
    SCK1=SCK2;
    DT1=DT2; 
  }
  if(x==3){
    SCK1=SCK3;
    DT1=DT3; 
  }
   unsigned long Count;
   unsigned char i;
   pinMode(DT1, OUTPUT);
   digitalWrite(DT1,HIGH);
   digitalWrite(SCK1,LOW);
   Count=0;
   pinMode(DT1, INPUT);
   while(digitalRead(DT1));
   for (i=0;i<24;i++)
   {
   digitalWrite(SCK1,HIGH);
   Count=Count<<1;
   digitalWrite(SCK1,LOW);
   if(digitalRead(DT1))
   Count++;
   }
   digitalWrite(SCK1,HIGH);
   Count=Count^0x800000;
   digitalWrite(SCK1,LOW);
   return(Count);
}
//
void setup()
{
readings_counter = 0;//setting number of reading cycles to zero
Serial.begin(9600); // Serial port init
pinMode(10, OUTPUT);//SD card    
pinMode(15, OUTPUT); // Clock pin set up
pinMode(17, OUTPUT); // 
pinMode(19, OUTPUT); // 
//cheching if sd card works
//if (!SD.begin(10)) {
//    Serial.println("initialization failed!");
//    return;
//}
//
myFile = SD.open("test.txt", FILE_WRITE); // opnings sd file
//
if (myFile) { //checking that the file opened
  Serial.print("initialization of sd done");
  Serial.print("|");
  Serial.print("initialization of sd done");
  Serial.print("|");
  Serial.print("initialization of sd done");
  Serial.print("|");
} else {
  Serial.println("error opening test.txt");
  Serial.print("|");
  Serial.println("error opening test.txt");
  Serial.print("|");
  Serial.println("error opening test.txt");
  Serial.print("|");
}

//calibration
//the " " blank prints are and the "|" are needed for the app that takes the readings
Serial.print("calibrating 1"); 
Serial.println(" "); 
Serial.println(" "); 
Serial.print("|"); 
Serial.print("calibrating 2"); 
Serial.println(" "); 
Serial.println(" "); 
Serial.print("|"); 
Serial.print("calibrating 3"); 
Serial.println(" "); 
Serial.println(" "); 
Serial.print("|"); 
delay(2000);
Incoming_value = 0;   //this is set to 0 so it starts off without saving readings to the sd card 
sample1 = calibration(1);
sample2 = calibration(2);
//general_time = millis();
}
//***********************************************************************************************
void loop()
{
myFile = SD.open("test.txt", FILE_WRITE);

Serial.setTimeout(100); // skips the input if the user doesnt enter a value within x miliseconds

//caling a reading function for every gauge:
e1 = reading(1);
delay(1000);
e2 = reading(2);
delay(1000);

Incoming_value = Serial.parseInt; // reads input from phone


// the incoming value resets to zero after every loop because if the phone doesnt input anything it takes it as a zero
// so we save the value of the 
if(Incoming_value == 1) {             //initialize calibration sequence calibration
  memory_controller=1;         
  }  
else if(Incoming_value == 2){         //starts writing to sd card
  time_from_reading_start = millis(); //saves time of start to a value
  readings_counter+=1;                //adds 1 to the number of reading cycles
  memory_controller=2;                //we save the incoming value to a new value so it doesnt get a 0 in the next loop
  myFile.print("set of readings: ");  //writes to the sd card the num of readings
  myFile.println(readings_counter);
} else if(Incoming_value == 3){       //stops writing to sd
  memory_controller=3;
}
   
   
if(memory_controller == 2){                        //print readings to SD card

  general_time = millis()-time_from_reading_start; //time from the start of new set of readings
  myFile.print(general_time/1000);                 //sets the time to seconds from milliseconds
  myFile.print(" ");
  myFile.print(e1);
  myFile.print(" ");
  myFile.print(e2);
  myFile.print(" ");
  myFile.print(e2);
  myFile.print(" ");
  myFile.print(e2);
  myFile.println(" ");

}else if(memory_controller == 3){                  //stops printing readings

}else if(memory_controller == 1){                  //recalibration sequence
  
  Serial.print("calibrating 1");
  Serial.println(" ");
  Serial.println(" ");
  Serial.print("|");
  Serial.print("calibrating 2");
  Serial.println(" ");
  Serial.println(" ");
  Serial.print("|");
  Serial.print("calibrating 3");
  Serial.println(" ");
  Serial.println(" ");
  Serial.print("|");
  sample1 = calibration(1); 
  sample2 = calibration(2); 
  delay(2000);
  memory_controller = 3;

}
//printing phone
//print values of gauge 1
Serial.print("Measured microstrain 1:  ");
Serial.print(int(e1));
Serial.println(" ");
Serial.println(" ");
Serial.print("|");

//print values of gauge 2
Serial.print("Measured Strain 2:  ");
Serial.print(int(e2));
Serial.println(" ");
Serial.println(" ");
Serial.print("|");

//print values of gauge 3
Serial.print("third strain 3:  ");
Serial.print(int(e2));
Serial.println(" ");
Serial.println(" ");
Serial.print("|");
delay(100);

/*
//print values of gauge 4
Serial.print("third strain 4:  ");
Serial.print(int(e4));
Serial.println(" ");
Serial.println(" ");
Serial.print("|");
delay(100);
*/
myFile.close(); //close the SD card file
}


unsigned long reading(int x){           //function for taking a reading from the HX711
  if(x==1){sample_temp = sample1;
  }else if(x==2){sample_temp = sample2;}
  count = readrealcount(x); // reciveing the sensor value from the rutine 
  
  long val=(count-sample_temp); // error deleting 
  float vout=(val*0.43); // Vout calculating (in nVolts ) 1=0.43nV
  int e=(vout/3.77)*0.002; //microstrain 
  return e;
}

unsigned long calibration(int x){   //calibration function
  for(int i=0;i<100;i++)            // Start sampling for calibrating
    {
    count = readrealcount(x);       // Add sample values 
    sample+=count;
    }
  sample/=100;
  count = 0;
  return sample; 
  sample = 0;
}
