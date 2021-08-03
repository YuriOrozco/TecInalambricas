#include <SoftwareSerial.h> //Librería que permite establecer comunicación serie en otros pins
//Aquí conectamos los pins RXD,TDX del módulo Bluetooth.
SoftwareSerial BT(11,10); //10 RX, 11 TX.

int Speed = 204; 
//Motor 1
int pinAIN1 = 2; //Direction
int pinAIN2 = 3; //Direction
int pinPWMA = 4; //Speed

//Motor 2
int pinBIN1 = 7; //Direction
int pinBIN2 = 6; //Direction
int pinPWMB = 5; //Speed

String cadena;
//Standby
int pinSTBY = 8;

//Constants to help remember the parameters
static boolean turnCW = 0;  //for motorDrive function
static boolean turnCCW = 1; //for motorDrive function
static boolean motor1 = 0;  //for motorDrive, motorStop, motorBrake functions
static boolean motor2 = 1;  //for motorDrive, motorStop, motorBrake functions

void setup()
{
 BT.begin(9600);
 Serial.begin(9600);
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinAIN2, OUTPUT);

  pinMode(pinPWMB, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);

  pinMode(pinSTBY, OUTPUT);
}
void loop()
{
 //Cuando haya datos disponibles
 if(BT.available())
 {
 char cadena2=BT.read(); //Guarda los datos carácter a carácter en la variable "dato"
 Serial.print(String(cadena2)); //Visualizamos el comando recibido en el Monitor Serial

// cadena=String(cadena2);
switch(cadena2){
       case 'F':
        motorDrive(motor1, turnCW, Speed);
        motorDrive(motor2, turnCW, Speed);
        break;

      case 'B':
        motorDrive(motor1, turnCCW, Speed);
        motorDrive(motor2, turnCCW, Speed);
        break;
      case 'L':
        motorDrive(motor2, turnCW, Speed);
        break;
      case 'R':
        motorDrive(motor1, turnCW, Speed);
        motorStop(motor2);
        break;
      case 'G':
        motorDrive(motor1, turnCW, 50);
        motorDrive(motor2, turnCW, Speed);
        break;
      case 'I':
        motorDrive(motor1, turnCW, Speed);
        motorDrive(motor2, turnCW, 50);
        break;
      case 'H':
        motorDrive(motor1, turnCCW, 50);
        motorDrive(motor2, turnCCW, Speed);
        break;
      case 'J':
         motorDrive(motor1, turnCCW, Speed);
        motorDrive(motor2, turnCCW, 50); 
        break;
       case 'S':
        motorStop(motor1);
        motorStop(motor2);
      break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
}

 BT.write("\r"); //Enviamos un retorno de carro de la app. La app ya crea una línea nueva
 }
}



void motorDrive(boolean motorNumber, boolean motorDirection, int motorSpeed)
{
  boolean pinIn1;  //Relates to AIN1 or BIN1 (depending on the motor number specified)
 
  if (motorDirection == turnCW)
    pinIn1 = HIGH;
  else
    pinIn1 = LOW;

//Select the motor to turn, and set the direction and the speed
  if(motorNumber == motor1)
  {
    digitalWrite(pinAIN1, pinIn1);
    digitalWrite(pinAIN2, !pinIn1);  //This is the opposite of the AIN1
    analogWrite(pinPWMA, motorSpeed);
  }
  else
  {
    digitalWrite(pinBIN1, pinIn1);
    digitalWrite(pinBIN2, !pinIn1);  //This is the opposite of the BIN1
    analogWrite(pinPWMB, motorSpeed);
  }

//Finally , make sure STBY is disabled - pull it HIGH
  digitalWrite(pinSTBY, HIGH);

}

void motorStop(boolean motorNumber)
{
  /*
  Detiene un motor especifico mandandole el numero del motor
  */
  if (motorNumber == motor1) {
    digitalWrite(pinAIN1, LOW);
    digitalWrite(pinAIN2, LOW);
  }
  else
  {
    digitalWrite(pinBIN1, LOW);
    digitalWrite(pinBIN2, LOW);
  } 
}


void motorsStandby()
{
  /*
  Pone los motores en standBy
  */
  digitalWrite(pinSTBY, LOW);
}
