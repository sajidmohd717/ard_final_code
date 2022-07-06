#define SENSORPIN_L 7
#define SENSORPIN_R 12

const int IN1 = 2, IN2 = 3, PWM = 1;
const int sensorDown = 6, sensorUp = 4, SensorPinL = 7, sensorPinR = 12;

int user_input = 0, position_state = 0, UP = 3, DOWN = 3; // a variable to read the encoder state

int sensorStateL = 2, sensorStateR = 2, sensorState = 2;

int x = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(sensorDown, INPUT);
  pinMode(sensorUp, INPUT);
  pinMode(SensorPinL, INPUT);
  pinMode(sensorPinR, INPUT);
}

void loop()
{
  if ( x == 0)
  {
    while (!Serial);
    Serial.println("Step 1: Introduce, Enter your input for caato arm:");
    x = 1;
  }


  if (Serial.available() == 1) {


    user_input = Serial.parseInt();

    Serial.print("Step 2: Input from user, user input is: ");
    Serial.println(user_input);

    if (user_input == 2) //move up
    {
      Serial.println("Step 3: Checking if condition for input, hello 2");
      messageUP();
    }
    else if (user_input == 1) //move down
    {
      Serial.print("Step 3: Checking if condition for input,hello 1");
      messageDown();
    }
    else if (user_input == 0)
    {
      messageBR();
    }
  }
}

void messageUP()
{
  check_sensors();
  Serial.print("Step 4: Enterned MessageUp function, Value for Up is");
  Serial.println(UP);
  check_sensors();
  if (UP)
    Motor_Forward(200);
}

void messageDown()
{
  check_sensors();
  Serial.println("Step 4: Enterned MessageUp function, Value for DOWN is");
  Serial.println(DOWN);
  if (DOWN)
    Motor_Backward(200);
}

void messageBR()
{
  check_sensors();
  Motor_Brake();
}

void Motor_Forward(int Speed) {
  while (1)
  {
    check_sensors();
    //Serial.println("Step 5: Motor forward function");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM, Speed);
    if (UP == 0)
    {
      Motor_Brake();
      x = 0;
      delay(100);
      check_bb();
      if (sensorState == 0) {
        Serial.println("Docked");
      }
      else {
        
        Serial.println("Not Docked");
        messageDown();
      }
      break;

    }
  }
}

void Motor_Backward(int Speed) {
  while (1)
  {
    check_sensors();
//    Serial.println("Motor backward function");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(PWM, Speed);
    if (DOWN == 0)
    {
      Motor_Brake();
      x = 0;
      break;
    }
  }

}

void Motor_Brake() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void check_sensors()
{
  UP = digitalRead(sensorUp);
  DOWN = digitalRead(sensorDown);
}

void check_bb()
{
  sensorStateL = digitalRead(SENSORPIN_L); //1 if not broken (not docked), 0 if broken (docked)
  sensorStateR = digitalRead(SENSORPIN_R); //1 if not broken (not docked), 0 if broken (docked)

  if (sensorStateL == 0 && sensorStateR == 0) { //docked
    sensorState = 0;
    //Serial.println("Docked");
  }
  else {
    sensorState = 1;
    //Serial.println("Not Docked");
  }
}
