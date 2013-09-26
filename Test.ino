/*  Will Keyser
 *  25 September, 2013
 *  
 *  Wild Thumper 6WD Chassis test
 *  for ATmega168 controller board
 */

#define LmotorA             3  // Left  motor H bridge, input A
#define LmotorB            11  // Left  motor H bridge, input B
#define RmotorA             5  // Right motor H bridge, input A
#define RmotorB             6  // Right motor H bridge, input B

const byte pot = 1;            // Trimpot for speed control

const int headlight = 12;      // My sketchy led headlamp

int reading;                   // Potentiometer value
  
int throt = 255;               // Throttle (0-255)


void setup()                   // Get set DDR for our pins!
{ 
  pinMode(LmotorA, OUTPUT);
  pinMode(LmotorB, OUTPUT);
  pinMode(RmotorA, OUTPUT);
  pinMode(RmotorB, OUTPUT);
  
  pinMode(headlight, OUTPUT);
  digitalWrite(headlight, HIGH);
  
     // Wait 5 seconds to let me plug in the battery
   delay(5000);
}

/*-------------------------------------- Let's Get to it! ---------------------------------------*/


void loop()
{
   reading = analogRead(pot);
   throt = map(reading, 0, 1024, 0, 255);
   
   // Rotate to the left, and then to the right, pausing after each slightly
   SpinLeft();
   delay(1000);
   SpinRight();
   delay(1000);
   
   // Stop
   AllOff();
   delay(3000);
   reading = analogRead(pot);
   throt = map(reading, 0, 1024, 0, 255);
   
   // Roll Forward, then backward, again pausing inbetween
   Forward();
   delay(1000);
   Backward();
   delay(1000);
   
   // Stop
   AllOff();
   delay(3000);
   reading = analogRead(pot);
   throt = map(reading, 0, 1024, 0, 255);
}


/* ----------------------------- SUBROUTINES GO HERE: ------------------------ */

// I should hope these are rather self-explanatory.  Especially with an understanding of H-Bridges. :)

void AllOff()
{
   analogWrite(LmotorA, 0);
   analogWrite(RmotorA, 0);
   analogWrite(LmotorB, 0);
   analogWrite(RmotorB, 0);
}

void SpinLeft()
{
   analogWrite(LmotorB, 0);
   analogWrite(RmotorB, 0);
   analogWrite(LmotorA, throt);
   analogWrite(RmotorA, throt);
}

void SpinRight()
{
   analogWrite(LmotorB, throt);
   analogWrite(RmotorB, throt);
   analogWrite(LmotorA, 0);
   analogWrite(RmotorA, 0);
}

void Right()
{
   analogWrite(LmotorB, 0);
   analogWrite(RmotorB, throt);
   analogWrite(LmotorA, 0);
   analogWrite(RmotorA, throt);
}

void Left()
{
   analogWrite(LmotorB, throt);
   analogWrite(RmotorB, 0);
   analogWrite(LmotorA, throt);
   analogWrite(RmotorA, 0);
}

void Forward()
{
   analogWrite(LmotorB, 0);
   analogWrite(RmotorB, throt);
   analogWrite(LmotorA, throt);
   analogWrite(RmotorA, 0);
}

void Backward()
{
   analogWrite(LmotorB, throt);
   analogWrite(RmotorB, 0);
   analogWrite(LmotorA, 0);
   analogWrite(RmotorA, throt);
}
