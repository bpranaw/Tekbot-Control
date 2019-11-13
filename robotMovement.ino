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
    Constants(Integers)
Purpose:
    Stores the digital pin numbers corresponding to the motor connections
    motor1 and motor2 represent the bidirectional movement of 2 motors in parallel
      (each motor value only controls 1 direction)
    motor3 and motor4 work the same but for different motors
 */

    const int motor1 = 6; 
    const int motor2 = 7; 
    
    const int motor3 = 8;
    const int motor4 = 9;

/*
Variable Names:
    leftTouchSensor, rightTouchSensor
Variable Type:
    Character
Purpose:
    Stores the analog pin numbers corresponding to the left and right front touch sensors
 */
    const char leftTouchSensor = "A6";
    const char rightTouchSensor = "A5";
    
/*
Variable Names: 
    sonicTrigger, sonicEcho, duration, cm, inches
Variable Types: 
    int, long
Purpose: 
    Stores the digital pin number that corresponds to the ultrasonic distance sensor's trigger and echo pins
 */
    const int sonicTrigger = 4;
    const int sonicEcho = 5;
    long duration, cm, inches;
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
          PWM_Pin, motor1, motor2, motor3, motor4, leftTouchSensor, rightTouchSensor, sonicTrigger, sonicEcho
      Functions Used:
          pinMode()
        Inputs:
            PWM_Pin, motor1, motor2, motor3, motor4, OUTPUT, leftTouchSensor, rightTouchSenspr, sonicTrigger, sonicEcho
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
             
             pinMode(leftTouchSensor,INPUT);
             pinMode(rightTouchSensor,INPUT);

             pinMode(sonicTrigger,OUTPUT);
             pinMode(sonicEcho,INPUT);
             delay(10000);
      
      
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
        delay(250);
        navigateMaze();
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
         digitalWrite(motor3,LOW);
         digitalWrite(motor4,HIGH);
     
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
         digitalWrite(motor1,HIGH);
         digitalWrite(motor2,LOW);
        
         //Left Side Motor
         digitalWrite(motor3,HIGH);
         digitalWrite(motor4,LOW);
     
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
         digitalWrite(motor3,LOW);
         digitalWrite(motor4,HIGH);
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
         digitalWrite(motor3,HIGH);
         digitalWrite(motor4,LOW);
    }


/*
Function Name:
    isTouchSensorPressed
Return Type: 
    Boolean
Inputs:
    Char(leftTouchSensor or rightTouchSensor)
Outputs:
    Boolean: False(Unpressed) or True(Pressed)
Purpose:
    Converts the value of the specific touch sensor inputted and returns a boolean to indicate whether it is pressed
 */

    bool isTouchSensorPressed(char sensor)
    {
        if(sensor == leftTouchSensor)
        {
             if(analogRead(sensor) == LOW)
             {
                 return true;
             }
             else
             {
                 return false;
             }
        }
        else if(sensor == rightTouchSensor)
        {
             if(analogRead(sensor) == LOW)
             {
                 return true;
             }
             else
             {
                 return false;
             }
          
        }
        else
        {
             Serial.println();
             Serial.print("The input is not a touch sensor");
        }
    }

/*
Function Name:
    howFarIsWall
Return Type: 
    double
Inputs:
    Int (sonicTrigger, sonicEcho)
Outputs:
    Distance(long)
Purpose:
    Operates the ultrasonic sensor by sending out pulses and using math and the time it taks to recieve the pulse to determine the distance
 */
    double howFarIsWall( int trigger, int echo)
    {
      //(CODE ADAPTED FROM RUI SANTOS)
      
        /*
            The ultrasonic sensor operates on HIGH pulses of 10+ microseconds
            so it is important to send a short LOW ping to get clean HIGH pings
         */
         
        digitalWrite(trigger, LOW);
        delayMicroseconds(5);
        
        digitalWrite(trigger, HIGH);
        delayMicroseconds(10);
        
        digitalWrite(trigger, LOW);

        //This sends a pulse and the duration is the time it takes for the echo to come back
        duration = pulseIn(echo, HIGH);

        // Convert the time into a distance
        cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
        inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135

        //Prints the distance from the wall into the serial
        Serial.print("Distance from a wall:");
        Serial.println();
        Serial.print(inches);
        Serial.print("in, ");
        Serial.print(cm);
        Serial.print("cm");
        Serial.println();

        return cm;
    }
/*
Function Name:
    navigateMaze
Return Type: 
    void
Inputs:
    None
Outputs:
    None
Purpose:
    Navigates a maze autonomously
 */
    int rate = 10; //The real rate is 20 but this is for accuracy purposes.
    const int timeFor180Degree = 1500; //The estimated time it takes for the robot to rotate 180 degrees in milliseconds
    const int timeFor90Degree = 800;  //The estimated time it takes for the robot to rotate 90 degrees in miliseconds
    void navigateMaze()
    {
        
        int wallDistance = howFarIsWall(sonicTrigger,sonicEcho);
        delay(250);
        while( wallDistance > 8)
        {
          delay(250);
          moveForward();
          delay(wallDistance*rate);
          moveStop();
          delay(250);
          wallDistance = howFarIsWall(sonicTrigger,sonicEcho);
        }

        moveStop();
        delay(500);
        rotateLeft();
        delay(timeFor90Degree);
        moveStop();

        if(howFarIsWall(sonicTrigger,sonicEcho) < 15)
        {
            delay(500);
            rotateRight();
            delay(timeFor180Degree);
            moveStop();
        }       
    }
