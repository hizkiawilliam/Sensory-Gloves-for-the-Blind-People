#define pingPin PA0 // Trigger Pin of Ultrasonic Sensor
#define echoPin PA1 // Echo Pin of Ultrasonic Sensor
#define buzzerPin PA11 // Echo Pin of Ultrasonic Sensor
#define vibratorPin PA13 // Echo Pin of Ultrasonic Sensor
#define LEDPin PA12 // Echo Pin of Ultrasonic Sensor

unsigned long startMillis = 0;
unsigned long previousMillis;
unsigned int interval_buzzer_on = 500;
unsigned int interval_buzzer_off = 5000;

int statusOutput = LOW;
int statusBuzzer = LOW;  
int statusVibrator = LOW; 

long duration, cm;

void setup()
{
    Serial.begin(9600); // Starting Serial Terminal
    pinMode(echoPin, INPUT);
    pinMode(pingPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(vibratorPin, OUTPUT);
    pinMode(LEDPin, OUTPUT);
}

void loop() 
{   
    digitalWrite(LEDPin, HIGH);
    getRange();
    if(cm > 50)
    {
        interval_buzzer_off = 2000;
        digitalWrite(vibratorPin, LOW); 
    }
    else if(cm > 25)
    {
        interval_buzzer_off = 500;
        digitalWrite(vibratorPin, LOW); 
    }
    else if(cm > 15)
    {
        interval_buzzer_off = 100;
        digitalWrite(vibratorPin, LOW); 
    }
    else if(cm <= 15)
    {
        interval_buzzer_off = 20;
         digitalWrite(vibratorPin, HIGH); 
    }
    
    previousMillis = millis();
 
    if((statusOutput == HIGH) && (previousMillis - startMillis >= interval_buzzer_on)) {
 
        statusOutput = LOW;                
        startMillis = previousMillis;          
        digitalWrite(LEDPin, statusOutput);
        digitalWrite(buzzerPin, statusOutput);

    } else if ((statusOutput == LOW) && (previousMillis - startMillis >= interval_buzzer_off)) {
    
        statusOutput = HIGH;                
        startMillis = previousMillis;         
        digitalWrite(LEDPin, statusOutput);
        digitalWrite(buzzerPin, statusOutput);
    } 
}

void getRange()
{
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);
    Serial.println(cm);
    delay(100);
}


long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29 / 2;
}
