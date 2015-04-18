 
#define trigPin1 8
#define echoPin1 9
#define led 13
#define soundConstant 28.72
#define distanceConstant 140
#define startGap 11
#define ballGap 6
#define upPin 0
#define enterPin 1
#include <LiquidCrystal.h>
int cmd, ballNo;
//long usedDistance;

LiquidCrystal lcd(7,6,5,4,3,2);  
//Effectively LiquidCrystal lcd(RS, Enable, D4, D5, D6, D7); 

void setup()
{ 
  Serial.begin(9600);
  pinMode(upPin, INPUT_PULLUP);
  pinMode(enterPin, INPUT_PULLUP);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(led, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("How many balls?");
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("# of players?");
  delay(500);
  int playerNo = readNo(4);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("# of balls?");
  delay(500);
  int ballNo = readNo(5);
  ballnumFunc(playerNo, ballNo);
}


int ballnumFunc (int pN, int bN)
{
  lcd.clear();
  int totals[pN];
  for (int j = 0; j < pN; j++)
  {
    totals[j ] = 0;
  }
  for(int i = 1; i <= bN; i++)
  {
    for (int j = 0; j < pN; j++)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Player #");
      lcd.print(j+1);
      lcd.setCursor(0,1);
      lcd.print("Ball #");
      lcd.print(i);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("3...");
      delay(1000);
      lcd.print("2...");
      delay(1000);
      lcd.print("1...");
      delay(1000);
      lcd.setCursor(0,1   );
      lcd.print("GO!");
      int c = ballFunc();
      totals[j] = totals[j] + c;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Score:");
      lcd.print(c);
      lcd.setCursor(0,1);
      lcd.print("Total:");
      lcd.print(totals[j]);
      
      delay(5000);
    }
  }
}

int ballFunc()
{
  long x;
  int z;
  do
  {
    x = distanceMeasure1(3);
  } while (x > 2* startGap+10*ballGap+8 ||  x == 0);
  z = pointFunc(x);
  return(z);
}
        
int readNo (int max)
{ 
  int Num = 1;
  lcd.setCursor(0, 1);
  lcd.print(Num);
  int upbuttonState = HIGH;
  int downbuttonState = HIGH;
  int lNum = Num;
  bool enterpinState;
  do
  {
    enterpinState = digitalRead(enterPin);
    upbuttonState = digitalRead(upPin);
    //downbuttonState = digitalRead(downPin);
    if(digitalRead(upPin) == LOW) 
    {
      //Serial.println("UP");
      Num = buttonFn(Num, 1);
    }
     /*
    if(digitalRead(downPin) == LOW) 
    {
      //Serial.println("DOWN");
      Num = buttonFn(Num, -1);
    }
    */
    if (Num == (max+1)) Num = 1;
    if (Num == 0) Num = max;
    if(lNum != Num)
    {
      lcd.setCursor(0, 1);
      lcd.print(Num);
    }
    lNum = Num;
  } while (enterpinState);
  return (Num);
}

long distanceMeasure1(int k)
{
  long i, j;
  digitalWrite(trigPin1, LOW);  
  delayMicroseconds(5); 
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5); 
  i = pulseIn(echoPin1, HIGH);
  j = ((i/2) / soundConstant);
  return j;
}

int pointFunc(int n)
{
  int m;
  if ((startGap <= n && n <= startGap+ballGap)||(startGap+9*ballGap+8 <= n && n <= startGap+10*ballGap+8)) 
  {    
    m = 2;
  } 
  else if ((startGap+ballGap+1 <= n && n <= startGap+2*ballGap+1)||(startGap+8*ballGap+7 <= n && n <= startGap+9*ballGap+7))  
  {
    m = 4;
  }
  else if ((startGap+2*ballGap+2 <= n && n <= startGap+3*ballGap+2)||(startGap+7*ballGap+6 <= n && n <= startGap+8*ballGap+6))  
  {
    m = 6;
  }
  else if ((startGap+3*ballGap+3 <= n && n <= startGap+4*ballGap+3)||(startGap+6*ballGap+5 <= n && n <= startGap+7*ballGap+5))  
  {
    m = 8;
  }
  else if (startGap + 4*ballGap + 4 <= n && n <= startGap + 6*ballGap + 4)  
  {
    m = 12;
  }
  else
  {
    m = 0;
  }
  return m;
}  

int buttonFn(int x, int y)
{
  x = x + y;
  delay(200);  
  return x;
}  
