#include <AccelStepper.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#define servo 2
#define EN1 23
#define EN2 24
#define EN3 25
#define limitX 26
#define limitY 27
#define IR1 A1
#define IR2 A2
#define IR3 A0
#define Solenoid 22
#define EnableStepper 28
#define stepPin1 29
#define dirPin1 30
#define stepPin2 31
#define dirPin2 32
#define buzer 33
#define LCD_RS 34
#define LCD_EN 35
#define LCD_D4 36
#define LCD_D5 37
#define LCD_D6 38
#define LCD_D7 39
#define RXPin  10  // Serial Receive pin
#define TXPin  11  // Serial Transmit pin
AccelStepper stepper1(1,stepPin1,dirPin1); //Y-Coordinate +ve to paper feeder
AccelStepper stepper2(1,stepPin2,dirPin2); //X-Xoordinate
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Servo s;
SoftwareSerial WiFi_Data(RXPin, TXPin); // RX, TX
const int yAllign=50;
int byteSend;
const int numSymbol = 47; // Number of letters in the alphabet
const int numRows = 3;     // Number of rows in each matrix
const int numCols = 2;     // Number of columns in each matrix
int PrevPrint = false;
int printIndex = 0;
const int maxCharNumber = 154;
bool SymbolMatrices[numSymbol][numRows][numCols]= 
{
  // Matrix for 'A'
  {
    {true, false},
    {false, false},
    {false, false}
  },

  // Matrix for 'B'
  {
    {true, false},
    {true, false},
    {false, false}
  },
  
  // Matrix for 'C'
  {
    {true, true},
    {false, false},
    {false, false}
  },
  
  // Matrix for 'D'
  {
    {true, true},
    {false, true},
    {false, false}
  },
  
  // Matrix for 'E'
  {
    {true, false},
    {false, true},
    {false, false}
  },
  
  // Matrix for 'F'
  {
    {true, true},
    {true, false},
    {false, false}
  },
  
  // Matrix for 'G'
  {
    {true, true},
    {true, true},
    {false, false}
  },
  
  // Matrix for 'H'
  {
    {true, false},
    {true, true},
    {false, false}
  },
  
  // Matrix for 'I'
  {
    {false, true},
    {true, false},
    {false, false}
  },
  
  // Matrix for 'J'
  {
    {false, true},
    {true, true},
    {false, false}
  },
  
  // Matrix for 'K'
  {
    {true, false},
    {false, false},
    {true, false}
  },
  
  // Matrix for 'L'
  {
    {true, false},
    {true, false},
    {true, false}
  },
  
  // Matrix for 'M'
  {
    {true, true},
    {false, false},
    {true, false}
  },
  
  // Matrix for 'N'
  {
    {true, true},
    {false, true},
    {true, false}
  },
  
  // Matrix for 'O'
  {
    {true, false},
    {false, true},
    {true, false}
  },
  
  // Matrix for 'P'
  {
    {true, true},
    {true, false},
    {true, false}
  },
  
  // Matrix for 'Q'
  {
    {true, true},
    {true, true},
    {true, false}
  },
  
  // Matrix for 'R'
  {
    {true, false},
    {true, true},
    {true, false}
  },
  
  // Matrix for 'S'
  {
    {false, true},
    {true, false},
    {true, false}
  },
  // Matrix for 'T'
  {
    {false, true},
    {true, true},
    {true, false}
  },
  // Matrix for 'U'
  {
    {true, false},
    {false, false},
    {true, true}
  },
  
  // Matrix for 'V'
  {
    {true, false},
    {true, false},
    {true, true}
  },
  
  // Matrix for 'W'
  {
    {false, true},
    {true, true},
    {false, true}
  },
  
  // Matrix for 'X'
  {
    {true, true},
    {false, false},
    {true, true}
  },
  
  // Matrix for 'Y'
  {
    {true, true},
    {false, true},
    {true, true}
  },
  
  // Matrix for 'Z'
  {
    {true, false},
    {false, true},
    {true, true}
  },
  // Matrix for '.'
  {
    {false, false},
    {true, true},
    {false, true}
  },
  // Matrix for ','
  {
    {false, false},
    {true, false},
    {false, false}
  },
  // Matrix for '?'
  {
    {false, false},
    {true, false},
    {true, true}
  },
  // Matrix for '!'
  {
    {false, false},
    {true, true},
    {true, false}
  },
  // Matrix for '''
  {
    {false, false},
    {false, false},
    {true, false}
  },
  // Matrix for '-'
  {
    {false, false},
    {false, false},
    {true, true}
  },
  // Matrix for '#'
  {
    {false, true},
    {false, true},
    {true, true}
  },
   // Matrix for 'Space'
  {
    {false, false},
    {false, false},
    {false, false}
  },
  // Matrix for 'CAPITAL'
  {
    {false, false},
    {false, false},
    {false, true}
  },
  // Matrix for 'Number'
  {
    {false, true},
    {false, true},
    {true, true}
  },
  // Matrix for '0'
  {
    {false, true},
    {true, true},
    {false, false}
  },
  // Matrix for '1'
  {
    {true, false},
    {false, false},
    {false, false}
  },
  // Matrix for '2'
  {
    {true, false},
    {true, false},
    {false, false}
  },
  // Matrix for '3'
  {
    {true, true},
    {false, false},
    {false, false}
  },
  // Matrix for '4'
  {
    {true, true},
    {false, true},
    {false, false}
  },
  // Matrix for '5'
  {
    {true, false},
    {false, true},
    {false, false}
  },
  // Matrix for '6'
  {
    {true, true},
    {true, false},
    {false, false}
  },
  // Matrix for '7'
  {
    {true, true},
    {true, true},
    {false, false}
  },
  // Matrix for '8'
  {
    {true, false},
    {true, true},
    {false, false}
  },
  // Matrix for '9'
  {
    {false, true},
    {true, false},
    {false, false}
  },
  //Matrix for ';'
  {
    {false, false},
    {false, true},
    {false, true}
  },
  // ... continue initializing matrices for other letters
}; // Array to store matrices
int x=0, y=0,symbolNum=0;
bool startCaptal = false;
bool startNumber = false;
bool prevIsDigit = false;
int thereIsPaper=true;
int getSymbolIndex(char c)
{
  if(c >= 'a' && c<='z')
  {
    return c-'a'; 
  }
  else if(c >= 'A' && c <= 'Z')
  {
    return c-'A';
  }
  else if(c == '.')return 26;
  else if(c==',')return 27;
  else if(c=='?')return 28;
  else if(c=='!')return 29;
  else if(c=="'")return 30;
  else if(c=='-')return 31;
  else if(c=='#')return 31;
  else if(c==' ')return 33;//captal34 number35
  else if(c>='0' && c<='9')
  {
    return 36 + (c-'0');
  }
  else return 33;//any other char return ' '
}

void moveXY()
{
  digitalWrite(EnableStepper,HIGH);
  stepper1.runToNewPosition(x);
  delay(50);
  stepper2.runToNewPosition(y);
  delay(50);
  digitalWrite(EnableStepper,LOW);
}

void knock()
{
  digitalWrite(Solenoid,LOW);
  delay(12);
  digitalWrite(Solenoid,HIGH);
}

void printString(String text)
{      
  resetStepperMotorX();
  resetStepperMotorY();
  y+=yAllign;
  moveXY();
  runBuzer(1);
  feader();
  delay(400);
  roll1();
  if(analogRead(IR3)<200)
  {
    for(printIndex=0;printIndex<text.length();printIndex++)
    {
      lcd.setCursor(0, 0);
      lcd.print("  Braille  Printer  ");
      lcd.setCursor(0, 1);
      lcd.print("      GP2 2023      ");
      if(!thereIsPaper)break;
      if(startCaptal==false && text[printIndex]>='A'&&text[printIndex]<='Z')
      {
        if(printIndex>0 && text[printIndex-1] >= '0' && text[printIndex-1] <= '9' && startNumber) prevIsDigit=true;
        else if(printIndex+1 < text.length() && text[printIndex+1] >= 'A' && text[printIndex+1]<='Z')
        {
          braillePrint(SymbolMatrices[34]);
          braillePrint(SymbolMatrices[34]);
          startCaptal=true;
        }
        else
        {
          braillePrint(SymbolMatrices[34]);
        }
      }
      else if(startCaptal && !(text[printIndex]>='A'&&text[printIndex]<='Z')){
        braillePrint(SymbolMatrices[34]);
        braillePrint(SymbolMatrices[34]);
        startCaptal=false;
      }

      if(startNumber==false && text[printIndex] >= '0' && text[printIndex] <= '9'){
        braillePrint(SymbolMatrices[35]);
        startNumber = true;
      }
      else if(startNumber && !(text[printIndex] >= '0' && text[printIndex] <= '9')){
        if(text[printIndex]!=' '){
          braillePrint(SymbolMatrices[46]);//print ;
        }
        startNumber = false;
      }
      if(!prevIsDigit)
      {
        lcd.setCursor(0, 2);
        lcd.print("                    ");
        lcd.setCursor(0, 2);
        lcd.print("printing char: ");
        lcd.print(text[printIndex]);
        if(printIndex%20 ==0){
          lcd.setCursor(0, 3);
          lcd.print("                    ");
        }
        lcd.setCursor((printIndex%20), 3);
        lcd.print(text[printIndex]);

        braillePrint(SymbolMatrices[getSymbolIndex(text[printIndex])]);
      }
      else{
        prevIsDigit=false;
        printIndex--;
      }
    }
    if(thereIsPaper){
      roll2();
      runBuzer(2);
      symbolNum=0;
      resetStepperMotorX();
      resetStepperMotorY();
      y+=yAllign;
      moveXY();
      lcd.setCursor(0, 2);
      lcd.print("  Finish Printing   ");
      lcd.setCursor(0, 3);
      lcd.print("                    ");
    }
  }
}

void braillePrint(bool Symbol[][2])
{
  if(analogRead(IR3)<200){
    for(int i=0 ; i<2 ; i++)
    {
      for(int j=0; j<3;j++)
      {
        
        if(Symbol[i==1?2-j:j][i])
        {
          moveXY();
          knock();
          delay(20);
        }
        if(j==2);
        else 
          i==1?y-=15:y+=15;
      }
      x+=15;
    }

    x+=30;
    symbolNum++;
    if(symbolNum!=maxCharNumber && symbolNum%14 == 0)
    {
      y+=100;
      moveXY();
      resetStepperMotorX(); 
    }
    if(symbolNum==maxCharNumber)
    {
      roll2();
      symbolNum=0;
      resetStepperMotorX();
      resetStepperMotorY();
      y+=yAllign; 
      moveXY();
      feader();
      roll1();
    }
  }
  else{
      symbolNum=0;
      resetStepperMotorX();
      resetStepperMotorY();
      y+=yAllign;
      moveXY();
      feader();
      roll1();
  }
}

void roll1()
{
  if(analogRead(IR1)<200)
  {
    while(analogRead(IR3)>200)
    {
    Serial.println(analogRead(IR1));
    analogWrite(EN1,220);
    delay(200);
    analogWrite(EN1,0);
    delay(100);
    }
    for(int i=0 ; i<4;i++)
    {
    Serial.println(analogRead(IR1));
    analogWrite(EN1,220);
    delay(200);
    analogWrite(EN1,0);
    delay(100);
    }
    Serial.println(analogRead(IR1));
    analogWrite(EN2,200);
    delay(15);
    analogWrite(EN2,0);
    delay(1000);
  }
  else
  {
    Serial.println("No Paper");
  }
}

void roll2()
{
  Serial.print("Roller2====>");
  Serial.print(analogRead(IR3));
  int x=0;
  while(analogRead(IR3)<200)
  {
    x++;
    Serial.println(analogRead(IR3));
    analogWrite(EN2,200);
    delay(200);
    analogWrite(EN2,0);
    if((x%5)==0){
      for(int i=0 ; i<3;i++)
      {
        Serial.println(analogRead(IR1));
        analogWrite(EN1,200);
        delay(100);
        analogWrite(EN1,0);
        delay(300);
      }
    }
    if(x==15){
      runBuzer(2);
      lcd.setCursor(0, 2);
      lcd.print("roller2: paper stuck");
      lcd.setCursor(0, 3);
      lcd.print("                    ");
    }
    delay(200);
  }
}

void feader()
{
  if(analogRead(IR3)<200){
    roll2();
  }
  else if(analogRead(IR1)<200){
    roll1();
    roll2();
  }
  controlServo();
  if(analogRead(IR2)<200)
  {
    thereIsPaper=true;
    while(analogRead(IR1)>200)
    {
      Serial.println(analogRead(IR2));
        analogWrite(EN3,160);
        delay(10);
        analogWrite(EN3,0);
        delay(150);
    }
    for(int i=0 ; i<10;i++)
    {
        analogWrite(EN3,180);
        delay(10);
        analogWrite(EN3,0);
        delay(150);
    }
  }
  else
  {
    lcd.setCursor(0, 2);
    lcd.print("      No Paper      ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    Serial.println("No Paper");
    Serial.println(analogRead(IR2));
    runBuzer(3);
    thereIsPaper=false;
  }
}

void runBuzer(int beepingNum)
{
  for(int i=0;i<beepingNum;i++)
  {
    digitalWrite(buzer,LOW);
    delay(500);
    digitalWrite(buzer,HIGH);
    delay(500);
  }
}


void resetStepperMotorX()
{
  while (!digitalRead(limitX)) {  // Make the Stepper move CCW until the switch is activated  
    digitalWrite(EnableStepper,HIGH); 
    stepper1.moveTo(x);  // Set the position to move to
    x--;  // Decrease by 1 for next move if needed
    stepper1.run();  // Start moving the stepper
    Serial.println(digitalRead(limitX));
    delay(5);
  }
  digitalWrite(EnableStepper,LOW);
}

void resetStepperMotorY()
{
  
  while (!digitalRead(limitY)) {  // Make the Stepper move CCW until the switch is activated   
    digitalWrite(EnableStepper,HIGH);
    stepper2.moveTo(y);  // Set the position to move to
    y--;  // Decrease by 1 for next move if needed
    stepper2.run();  // Start moving the stepper
    delay(5);
  }
  digitalWrite(EnableStepper,LOW);
}

void controlServo(){
    s.attach(servo);
    if(analogRead(IR2) > 200){
      s.write(30);
    }else{
      s.write(110);
    }
}

void setup() {
  Serial.begin(9600);
  WiFi_Data.begin(9600);   // set the data rate
  delay(500);
  pinMode(EN1,OUTPUT); 
  pinMode(EN2,OUTPUT); 
  pinMode(EN3,OUTPUT);
  pinMode(limitX,INPUT);
  pinMode(limitY,INPUT);
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(Solenoid,OUTPUT);
  pinMode(EnableStepper,OUTPUT);
  pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
  pinMode(buzer,OUTPUT);
  pinMode(servo,OUTPUT);
  digitalWrite(Solenoid,HIGH);
  digitalWrite(buzer,HIGH);
  runBuzer(1);
  lcd.begin(20, 4);  // Initialize the LCD with 16 columns and 4 rows
  lcd.setCursor(0, 0);
  lcd.print("  Braille  Printer  ");
  lcd.setCursor(0, 1);
  lcd.print("      GP2 2023      ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  stepper1.setMaxSpeed(200);
  stepper1.setAcceleration(1200);
  stepper2.setMaxSpeed(200);
  stepper2.setAcceleration(1200);
  resetStepperMotorX();
  resetStepperMotorY();
  controlServo();
  lcd.setCursor(0, 2);
  lcd.print("start connecting ...");
  while(true){
    if (WiFi_Data.available()) {
      String incoming =  WiFi_Data.readString();
      if(strcmp(incoming.c_str(), "WiFi connected") == 0){
          lcd.setCursor(0, 2);
          lcd.print("   WiFi connected   ");
          Serial.print(incoming.c_str());
          break;
      }
    }
  }
  lcd.setCursor(0, 3);
  lcd.print("  Server connected  ");

  /*
  // printString("   Hello World   ");
  // feader();
  // delay(400);
  // roll1();
  // roll2();
  */
}


void loop() {
  controlServo();
  lcd.setCursor(0, 0);
  lcd.print("  Braille  Printer  ");
  lcd.setCursor(0, 1);
  lcd.print("      GP2 2023      ");
  if (WiFi_Data.available()) {
    String incoming =  WiFi_Data.readString();
    if(incoming!=NULL){
      String outgoing = "received";
      WiFi_Data.write(outgoing.c_str());

      printString(incoming.c_str());

      outgoing = "finished";
      WiFi_Data.write(outgoing.c_str());
    }else{
      String outgoing = "not received";
      WiFi_Data.write(outgoing.c_str());
    }
    Serial.print(incoming.c_str());
  }


}
