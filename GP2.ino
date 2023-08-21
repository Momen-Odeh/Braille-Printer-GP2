#include <AccelStepper.h>
#include <LiquidCrystal.h>
#include <Servo.h>
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
AccelStepper stepper1(1,stepPin1,dirPin1); //Y-Coordinate +ve to paper feeder 
AccelStepper stepper2(1,stepPin2,dirPin2); //X-Xoordinate
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Servo s;
//

const int numSymbol = 46; // Number of letters in the alphabet
const int numRows = 3;     // Number of rows in each matrix
const int numCols = 2;     // Number of columns in each matrix
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

  // ... continue initializing matrices for other letters
}; // Array to store matrices
int x=0, y=0,symbolNum=0;

int getSymbolIndex(char c)
{
  if(c >= 'a' && c<='z')
  {
    return c-'a'; 
  }
  else if(c==' ')return 33;
  return 0; 
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
  delay(100);
  digitalWrite(Solenoid,HIGH);
}

void braillePrint(bool Symbol[][2])
{
  
  for(int i=0 ; i<2 ; i++)
  {
    for(int j=0; j<3;j++)
    {
      
      if(Symbol[i==1?2-j:j][i])
      {
        moveXY();
        knock();
        
      }
      if(j==2);
      else 
        i==1?y-=15:y+=15;
    }
    x+=15;
  }

  x+=30;
  symbolNum++;
  if(symbolNum == 14)
  {
    symbolNum=0;
    y+=100;
    moveXY();
    resetStepperMotorX(); 
  }
  
}

void rool1()
{
  if(analogRead(IR1)<200)
  {
    while(analogRead(IR3)>200)
    {
    Serial.println(analogRead(IR1));
    analogWrite(EN1,150);
    delay(200);
    analogWrite(EN1,0);
    delay(100);
    }
    for(int i=0 ; i<2;i++)
    {
    Serial.println(analogRead(IR1));
    analogWrite(EN1,130);
    delay(200);
    analogWrite(EN1,0);
    delay(100);
    }
  }
  else
  {
    Serial.println("No Paper");
  }
}

void rool2()
{
  Serial.print("Roller2====>");
  Serial.print(analogRead(IR3));
  while(analogRead(IR3)<200)
  {
    Serial.println(analogRead(IR3));
    analogWrite(EN2,255);
    delay(200);
    analogWrite(EN2,0);
    delay(200);
  }
}

void feader()
{
  if(analogRead(IR2)<200)
  {
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
    Serial.println("No Paper");
    Serial.println(analogRead(IR2));
    for(int i=0;i<5;i++)
    {
      runBuzer();
    }
  }
  
}

void runBuzer()
{
  digitalWrite(buzer,LOW);
  delay(500);
  digitalWrite(buzer,HIGH);
  delay(500);
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
void setup() {
  Serial.begin(9600);
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
  
//  digitalWrite(EnableStepper,HIGH);

  digitalWrite(Solenoid,HIGH);
  digitalWrite(buzer,HIGH);
  
  s.attach(servo);
  s.write(120);
  lcd.begin(20, 4);  // Initialize the LCD with 16 columns and 4 rows

  lcd.setCursor(0, 0);
  lcd.print("king.. Mohee Qwareeq");
  
  lcd.setCursor(0, 1);
  lcd.print("my name is momen ode");
  
  lcd.setCursor(0, 2);
  lcd.print("my name is  noor ald");
  
  lcd.setCursor(0, 3);
  lcd.print("sa ase oiuytrewqpopo");
  
  stepper1.setMaxSpeed(200);
  stepper1.setAcceleration(1200);
  stepper2.setMaxSpeed(200);
  stepper2.setAcceleration(1200);
  resetStepperMotorX();
  resetStepperMotorY();
  
  
  feader();
  delay(1000);
  rool1();
  delay(1000);
  
 
//  for(int i=0 ;i<20;i++)
//  {
//    knock(i*0,i*15);
//  }
//  stepper2.runToNewPosition(0);
  
//  knock(0,0);
//  knock(0,15);
//  knock(0,30);
//  knock(15,30);
//  knock(15,15);
//  knock(15,0);
bool c [3][2] ={
    {true, true},
    {true, true},
    {true, true}
  };
//  y+=300; 
//  moveXY();
//  braillePrint(SymbolMatrices[getSymbolIndex('m')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('o')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('h')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('e')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('e')]);
//  braillePrint(SymbolMatrices[getSymbolIndex(' ')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('q')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('w')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('a')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('r')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('e')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('q')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('q')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('q')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('a')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('r')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('e')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('q')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('q')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('q')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('a')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('r')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('e')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('q')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('q')]);
//  braillePrint(SymbolMatrices[getSymbolIndex('q')]);
  rool2();
  
  s.write(45);
}


void loop() {
  Serial.print("limitX=:");
  Serial.println(digitalRead(limitX));
  Serial.print("limitY=:");
  Serial.println(digitalRead(limitY));
  delay(1000);
}
