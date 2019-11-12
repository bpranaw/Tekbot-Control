/*
Variable Names: 
    PWM_Pin, PWM_Speed
Variable Type: 
    Integers
Purpose: 
    Stores the pin number that corresponds to the Pulse Width Modulation(PWM) pin on the Arduino
    Also controles the frequency of the PWM  
 */
    int PWM_Pin = 3; //needs to be this pin for pwm
    int PWM_Speed = 130; 

/*
Variable Names:
    motor1, motor2, motor3, motor4
Variable Type:
    Integers
Purpose:
    Stores the digital pin numbers corresponding to the motor connections
    motor1 and motor2 represent the bidirectional movement of 2 motors in parallel
      (each motor value only controls 1 direction)
    motor3 and motor4 work the same but for different motors
 */

    int motor1 = 6; 
    int motor2 = 7; 
    
    int motor3 = 8;
    int motor4 = 9;

/*
Function Name:
    setup
Return Type: 
    void
Inputs:
    None
Outputs:
    None
Purpose:
    A function that runs upon intialization of the Arduino
    Houses the code that initalizes the pin setup of the motors and PWM
 */
    void setup() 
    {
      /*
      Variables involved:
          PWM_Pin, motor1, motor2, motor3, motor4
      Functions Used:
          pinMode()
        Inputs:
            PWM_Pin, motor1, motor2, motor3, motor4, OUTPUT
        Outputs:
            None
      Purpose:
          Initialize the pins and configure them as either inputs or outputs
       */
             pinMode(PWM_Pin,OUTPUT);
             pinMode(motor1,OUTPUT);
             pinMode(motor2,OUTPUT);
             pinMode(motor3,OUTPUT);
             pinMode(motor4,OUTPUT);
      
      
      
      /*
      Variables Used:
          PWM_Pin, motor1, motor2, motor3, motor4
      Functions Used:
          digitalWrite()
        Inputs:
              PWM_Pin, PWM_Speed, motor1, motor2, motor3, motor4, HIGH
        Outputs:
              None
      Purpose:
          Sets the frequency of the PWM and stops the motors
       */
           digitalWrite(PWM_Pin,PWM_Speed);
           digitalWrite(motor1,HIGH);
           digitalWrite(motor2,HIGH);
           digitalWrite(motor3,HIGH);
           digitalWrite(motor4,HIGH);
      
      
      /*
      Functions Used:
          begin()
        Input:
          (a number)
        Output:
          None
      Purpose:
          Initializes the Serial communication and sets the tempo at which signals will be sent          
       */
          Serial.begin(9600);
    }

/*
Function Name:
    loop
Return Type: 
    void
Inputs:
    None
Outputs:
    None
Purpose:
    A function that continually loops as long as the Arduino is active
    Contains the functions that allow the Tekbot to move autonomously
 */

    void loop() 
    {
        delay(2000);
        
        digitalWrite(motor1,LOW);
        digitalWrite(motor2,HIGH);
        digitalWrite(motor3,LOW);
        digitalWrite(motor4,HIGH);
        
        
        delay(4000);
        
        moveStop();
        
        while(1){}
    }

/*
Function Name:
    moveForward
Return Type: 
    void
Inputs:
    None
Outputs:
    None
Purpose:
    Turns on motors in a specific way to move the Tekbot in the "Forward" direction
 */
    void moveForward()
    {
         //Right Side Motor
         digitalWrite(motor1,HIGH);
         digitalWrite(motor2,LOW);

         //Left Side Motor
         digitalWrite(motor3,HIGH);
         digitalWrite(motor4,LOW);
     
    }


/*
Function Name:
    moveBackward
Return Type: 
    void
Inputs:
    None
Outputs:
    None
Purpose:
    Turns the motors on to move the Tekbot in the "backwards" direction
 */
    void moveBackward()
    {
         //Right Side Motor
         digitalWrite(motor1,LOW);
         digitalWrite(motor2,HIGH);
        
         //Left Side Motor
         digitalWrite(motor3,LOW);
         digitalWrite(motor4,HIGH);
     
    }

/*
Function Name:
    moveStop
Return Type: 
    void
Inputs:
    None
Outputs:
    None
Purpose:
    To stop all the motors
 */
      void moveStop()
      {
           digitalWrite(motor1,HIGH);
           digitalWrite(motor2,HIGH);
           digitalWrite(motor3,HIGH);
           digitalWrite(motor4,HIGH);
      }


/*
Function Name:
    rotateRight
Return Type: 
    void
Inputs:
    None
Outputs:
    None
Purpose:
    Turns on the motors specific way to rotate the Tekbot to the "right" side
 */
    void rotateRight()
    {
         //Right Side Motor
         digitalWrite(motor1,LOW);
         digitalWrite(motor2,HIGH);

         //Left Side Motor
         digitalWrite(motor3,HIGH);
         digitalWrite(motor4,LOW);
    }

/*
Function Name:
    rotateLeft
Return Type: 
    void
Inputs:
    None
Outputs:
    None
Purpose:
    Turns on the motors specific way to rotate the Tekbot to the "left" side
 */
    void rotateLeft()
    {
         //Right Side Motor
         digitalWrite(motor1,HIGH);
         digitalWrite(motor2,LOW);

         //Left Side Motor
         digitalWrite(motor3,LOW);
         digitalWrite(motor4,HIGH);
    }
