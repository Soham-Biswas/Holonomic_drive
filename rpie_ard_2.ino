
float second_rpm = 0;
float third_rpm = 0;


const int pwm_motor_2 = 3 ;  //initializing pin 2 as pwm
const int in_a_2 = 4 ;
const int in_b_2 = 5 ;


const int pwm_motor_3 = 6 ;  //initializing pin 2 as pwm
const int in_a_3 = 7 ;
const int in_b_3 = 8 ;


void setup() {

  pinMode(pwm_motor_2,OUTPUT) ;    //we have to set PWM pin as output
  pinMode(in_a_2,OUTPUT) ;  //Logic pins are also set as output
  pinMode(in_b_2,OUTPUT) ;

  pinMode(pwm_motor_3,OUTPUT) ;    //we have to set PWM pin as output
  pinMode(in_a_3,OUTPUT) ;  //Logic pins are also set as output
  pinMode(in_b_3,OUTPUT) ;

  
  Serial.begin(115200);  // start serial communication at 9600 baud


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
      for(int i=0; i<StringCount; i++)
      {
        Serial.print(i);
        Serial.println(strs[i]);
      }
      second_rpm =strs[1].toFloat() *300;
      third_rpm = strs[2].toFloat() *300;

      Serial.print("Second");
      Serial.println(second_rpm);
      Serial.print("Third");
      Serial.println(third_rpm);
      
      if (second_rpm > 300)
      {
        second_rpm = 300;
      }

      if (second_rpm < -300)
      {
        second_rpm = -300;
      }
      
      
      if (third_rpm > 300)
      {
        third_rpm = 300;
      }
 
      if (third_rpm < -300)
      {
        third_rpm = -300;
      }
      
   
   
  if (second_rpm>0)
  {
    digitalWrite(in_a_2,HIGH) ;
    digitalWrite(in_b_2,LOW) ;    
  }
  else
  {
    digitalWrite(in_a_2,LOW) ;
    digitalWrite(in_b_2,HIGH) ;      
  }
  
  if (third_rpm>0)
  {
    digitalWrite(in_a_3,HIGH) ;
    digitalWrite(in_b_3,LOW) ;
  }
  else
  {
    digitalWrite(in_a_3,LOW) ;
    digitalWrite(in_b_3,HIGH) ;  
  }
   }
   
  second_rpm = abs(second_rpm);
  third_rpm = abs(third_rpm);

  Serial.println(third_rpm);

  int pwm_2 = map(second_rpm, 0, 300, 0 ,255);
  int pwm_3 = map(third_rpm, 0, 300, 0 ,255);
  
  analogWrite(pwm_motor_2,pwm_2) ;
  analogWrite(pwm_motor_3,pwm_3) ;
//
//  String statement2 = "PWM2 value:-";
//  statement2.concat(pwm_2);
  String statement3 = " PWM3 value:-";
  statement3.concat(pwm_3);
//  Serial.println(statement2);
  Serial.println(statement3);
 delay(1000);
}
