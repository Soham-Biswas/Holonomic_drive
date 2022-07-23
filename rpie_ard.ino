float first_rpm = 0;

const int pwm_motor_1 = 3 ;  //initializing pin 2 as pwm
const int in_1 = 4 ;
const int in_2 = 5 ;

void setup() {

  pinMode(pwm_motor_1,OUTPUT) ;    //we have to set PWM pin as output
  pinMode(in_1,OUTPUT) ;  //Logic pins are also set as output
  pinMode(in_2,OUTPUT) ;
  Serial.begin(9600);  // start serial communication at 9600 baud


}

void loop() 
{
   // Read and execute commands from serial port
   if (Serial.available())   
   { 
      String strs[10];
      int StringCount = 0;
      //String command = "1 2 3";
      String command = Serial.readString();  
      
      while (command.length() > 0)
      {
        int index = command.indexOf(' ');
        if (index == -1) // No space found
        {
          strs[StringCount++] = command;
          break;
        }
        else
        {
          strs[StringCount++] = command.substring(0, index);
          command = command.substring(index+1);
        }
      }
      first_rpm = strs[0].toFloat() *300;


      if (first_rpm > 300)
      {
        first_rpm = 300;
      }
      
      if (first_rpm < -300)
      {
        first_rpm = -300;
      }
      
    
   
  if (first_rpm>0)
  {
    digitalWrite(in_1,HIGH) ;
    digitalWrite(in_2,LOW) ;
//    Serial.println("Clock");
  }
  else
  {
    digitalWrite(in_1,LOW) ;
    digitalWrite(in_2,HIGH) ;
//    Serial.println("Anti-Clock");    
  }
   }
  first_rpm = abs(first_rpm);

   
  int pwm_1 = map(first_rpm, 0, 300, 0 ,255);

  analogWrite(pwm_motor_1,pwm_1) ;

//  String statement1 = "PWM1 value:-";
//  statement1.concat(pwm_1);
//  Serial.println(statement1);
 delay(1000);
}
