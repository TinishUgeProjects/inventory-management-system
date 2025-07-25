
// Include Libraries
#include "Arduino.h"
#include "DCMotor.h"
#include "DHT.h"
#include "HX711.h"
#include "RFID.h"
#include "Servo.h"


// Pin Definitions
#define DCMOTOR_PIN_COIL1	5
#define DHT_PIN_DATA	2
#define SCALE_PIN_DAT	4
#define SCALE_PIN_CLK	3
#define RFID_PIN_RST	6
#define RFID_PIN_SDA	10
#define SERVO9G_PIN_SIG	7



// Global variables and defines
const int servo9gRestPosition   = 20;  //Starting position
const int servo9gTargetPosition = 150; //Position when event is detected
// object initialization
DCMotor dcMotor(DCMOTOR_PIN_COIL1);
DHT dht(DHT_PIN_DATA);
HX711 scale(SCALE_PIN_DAT, SCALE_PIN_CLK);
#define calibration_factor 2280 //This value is obtained using the SparkFun_HX711_Calibration sketch https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide?_ga=2.77038550.2126325781.1526891300-303225217.1493631967
RFID rfid(RFID_PIN_SDA,RFID_PIN_RST);
Servo servo9g;


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    dht.begin();
    scale.set_scale(calibration_factor); 
    scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
    //initialize RFID module
    rfid.init();
    servo9g.attach(SERVO9G_PIN_SIG);
    servo9g.write(servo9gRestPosition);
    delay(100);
    servo9g.detach();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // DC Motor - Hobby Motor Gear - Test Code
    // The DC motor will turn on and off for 4000ms (4 sec)
    dcMotor.on(200);                        // 1. turns on
    delay(4000);                             // 2. waits 4000 milliseconds (4 sec). change the value in the brackets (4000) for a longer or shorter delay.
    dcMotor.off();                       // 3. turns off
    delay(4000);                             // 4. waits 4000 milliseconds (4 sec). change the value in the brackets (4000) for a longer or shorter delay.

    }
    else if(menuOption == '2') {
    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    float dhtHumidity = dht.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
    float dhtTempC = dht.readTempC();
    Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
    Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '3') {
    // SparkFun HX711 - Load Cell Amplifier - Test Code
    float scaleUnits = scale.get_units(); //scale.get_units() returns a float
    Serial.print(scaleUnits); //You can change this to lbs but you'll need to refactor the calibration_factor
    Serial.println(" Kg"); //You can change this to lbs but you'll need to refactor the calibration_factor
    }
    else if(menuOption == '4') {
    // RFID Card Reader - RC522 - Test Code
    //Read RFID tag if present
    String rfidtag = rfid.readTag();
    //print the tag to serial monitor if one was discovered
    rfid.printTag(rfidtag);

    }
    else if(menuOption == '5') {
    // 9G Micro Servo - Test Code
    // The servo will rotate to target position and back to resting position with an interval of 500 milliseconds (0.5 seconds) 
    servo9g.attach(SERVO9G_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servo9g.write(servo9gTargetPosition);  // 2. turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
    delay(500);                              // 3. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servo9g.write(servo9gRestPosition);    // 4. turns servo back to rest position. Modify initial position by modifying the 'ServoRestPosition' definition above.
    delay(500);                              // 5. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servo9g.detach();                    // 6. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DC Motor - Hobby Motor Gear"));
    Serial.println(F("(2) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(3) SparkFun HX711 - Load Cell Amplifier"));
    Serial.println(F("(4) RFID Card Reader - RC522"));
    Serial.println(F("(5) 9G Micro Servo"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing DC Motor - Hobby Motor Gear"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing SparkFun HX711 - Load Cell Amplifier"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing RFID Card Reader - RC522"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing 9G Micro Servo"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
