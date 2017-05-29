#include "Servo.h"            
#define NUM 4
#define FAST 0
#define SLOW 20
#define MODERATE 5

#define AU 0
#define SPR 1
#define SU 2
#define WIN 3

#define NEAR 0
#define FAR 1
// ----------- motor movement -----------//
Servo servos[NUM];
int sAngle[NUM];
int sState[NUM]; // 0 - STILL; 1 - UP; 2 - DOWN;

int irPin[NUM];
int irRead[NUM]; // 0 - Close; 1 - Far;

int aMax = 70;
int aReset = 5;
int aLow = 20;

int aStillMax = 70;
int aStillMin = 30;

int aWaveMax = 70;
int aWaveMin = 30;
int aWaveUnit = 10;

// ----------- interactivity -----------//
int detectNum;
int lastDetect;
bool wave;

void setup() 
{ 
  Serial.begin(9600);  
  for (int i = 0; i < NUM; i++)
  {
    servos[i].attach(i+4);  
    irPin[i] = 30+i;
    irRead[i] = digitalRead(irPin[i]);
    sState[i] = 0;
    
    sAngle[i] = aReset;
    servos[i].write(sAngle[i]);

    Serial.println(String(i) + " sensor read " + String(irRead[i]));
  }
  delay(1000);
} 

void loop()
{
  detectNum = 0;
  lastDetect = AU;
  
  for (int i= 0; i< NUM; i++)
  {
    irRead[i] = digitalRead(irPin[i]);
    if (irRead[i] == NEAR)
    {
      detectNum ++; 
      lastDetect = i;
      Serial.println("Near sensor is " + String(i));
    }
  }

  if (detectNum > 2)
  {
      //allFall(aLow, 0);

      allSuddenFall(aLow);
      wave = false;
  }
  else
  {
    if (detectNum > 1)
    {      
      if (wave == false)
      {
        Serial.println("ENTER first wave mode, detectNum is " + String(detectNum) + ". last is " + String(lastDetect));
        stillMode(AU, SLOW);      
      }
      Serial.println("ENTER wave mode" + String(sAngle[0]) + String(sAngle[1]) +String(sAngle[2]) +String(sAngle[3]));
      
      waveMode(MODERATE);    
      wave = true;
    }
    else if(detectNum == 1)
    {
      Serial.println("ENTER still mode - " + String(lastDetect));
      stillMode(lastDetect, SLOW);
      wave = false;
    }
    else
    {
      Serial.println("ENTER reset mode");
      allFall(aReset, SLOW);
      wave = false;
    }    
  }
}

void waveMode(int w)
{
  for (int i = 0; i < NUM; i ++)
  {
    if (sState[i] == 0){ 
      // STILL state

      // go up first
      sState[i] = 1;  
    }
    else if (sState[i] == 1)
    {
      // UP state
      if (sAngle[i] < aWaveMax)
      {   
         sAngle[i] = sAngle[i] + aWaveUnit; 
         servos[i].write(sAngle[i]);  
      }
      else
      {
        sState[i] = 2;
      }    
    }
    else if (sState[i] == 2)
    {
      // DOWN state

      if (sAngle[i] > aWaveMin)
      {
         sAngle[i] = sAngle[i] - aWaveUnit;  
         servos[i].write(sAngle[i]);     
      }
      else
      {
        sState[i] = 1;
      }      
    }

    else{
      sState[i] = 0;
    }
  }  
}

void allFall(int des, int w) 
{
  for (int i = 0; i < NUM; i ++)
  {
    if (sAngle[i] > des) 
    {
      sAngle[i]--;
      servos[i].write(sAngle[i]);
      delay(w);
    }
  }  
}

void allSuddenFall(int des) 
{
  for (int i = 0; i < NUM; i ++)
  {
    if (sAngle[i] > des) 
    {
      sAngle[i] = (sAngle[i]+des)/2;
      servos[i].write(sAngle[i]);
      delay(5);
    }
  }  
}

void allRise(int des, int w)
{  
  for (int i = 0; i < NUM; i ++)
  {
    if (sAngle[i] < des) 
    {
      sAngle[i]++;
      servos[i].write(sAngle[i]);
      delay(w);
    }
  }  
}

void stillMode(int index, int w)
{
  switch(index)
  {
    case AU: 
      stillAu(w);
      break;
    case SPR:
      stillSpr(w);
      break;
    case SU:
      stillSu(w);
      break;
    case WIN:
      stillWin(w);
      break;
  } 
}

void stillAu(int w)
{
  ServoMoveAlone(AU, aStillMin, w); 
  ServoMoveAlone(SPR, aStillMax, w); 
  ServoMoveAlone(SU, aStillMin, w); 
  ServoMoveAlone(WIN, aStillMax, w);   
}

void stillSpr(int w)
{
  ServoMoveAlone(SPR, aStillMin, w); 
  ServoMoveAlone(SU, aStillMax, w); 
  ServoMoveAlone(WIN, aStillMin, w); 
  ServoMoveAlone(AU, aStillMax, w);   
}

void stillSu(int w)
{
  ServoMoveAlone(SU, aStillMin, w); 
  ServoMoveAlone(WIN, aStillMax, w); 
  ServoMoveAlone(AU, aStillMin, w); 
  ServoMoveAlone(SPR, aStillMax, w);   
}

void stillWin(int w)
{
  ServoMoveAlone(WIN, aStillMin, w); 
  ServoMoveAlone(AU, aStillMax, w);  
  ServoMoveAlone(SPR, aStillMin, w); 
  ServoMoveAlone(SU, aStillMax, w);  
}

void ServoMoveAlone(int index, int des, int w){
    if (index > NUM || index < 0 || des > aMax || des < aReset)
    {
      return;
    }
    if (sAngle[index] < des)
    {
        for (int a = sAngle[index]; a <= des; a++)
        {
            servos[index].write(a);
            delay(w);
        }
        sAngle[index] = des;
        //Serial.println("single "+String(index)+ " UP: "+String(sAngle[index]));
      }
      else if (sAngle[index] > des) 
      {
         for (int a = sAngle[index]; a >= des; a--)
        {
            servos[index].write(a);
            delay(w);
        }
        sAngle[index] = des;     
      }
      
      //Serial.println("single "+String(index)+ " DOWN: "+String(sAngle[index]));
      sState[index] = 0;
}
