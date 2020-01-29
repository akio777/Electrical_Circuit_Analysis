#define Gpin D1
#define Rpin D2
#define Bpin D5

#define gpin D6
#define rpin D7
#define bpin D8

const int mic_unit = 512;

int mic_storage[mic_unit];
int INDEX = 0;
double total = 0;
double average = 0, UP=0, DOWN=0;

long TIME=0;

double R=0,G=0,B=0,r=0,g=0,b=0;

double wave = 0, brigthness=0;
int range = 0;

boolean Rfade=false,Gfade=false,Bfade=false,
rfade=false,gfade=false,bfade=false;
boolean isPLAY=false;
int counter=0;
int MODE=0,timer=0;

void setup() {
      
  Serial.begin(115200);
  
  pinMode(Gpin,OUTPUT);
  pinMode(Rpin,OUTPUT);
  pinMode(Bpin,OUTPUT);
  pinMode(gpin,OUTPUT);
  pinMode(rpin,OUTPUT);
  pinMode(bpin,OUTPUT);

  for(int i = 0 ; i<mic_unit ; i++){
    mic_storage[i]=0;
  }
  
}

void loop() {

  MICROPHONE();
  if(timer==0){TIME=millis();timer=1;}
  if(millis()-TIME>=3600000){timer=0;}
  if(timer==0)RGBrun1();
  else RGBrun2();
//  GRAPH();
  
}

void MICROPHONE(){

  wave = analogRead(A0);
  total = total - mic_storage[INDEX];
  mic_storage[INDEX] = analogRead(A0);
  total = total + mic_storage[INDEX];
  INDEX+=1;
  if(INDEX>=mic_unit){
    INDEX=0;
  }
  average = total/mic_unit;
  if(wave>average)UP=wave-average;
  else DOWN=average-wave;
  brigthness = map((UP+DOWN)/2,0,average,0,99);
  range = UP+DOWN;

}

void RGBrun1(){
  if(brigthness==0){
    if(counter<100)counter+=2;
  }
  else{
    if(counter>0)counter--;
  }
  if(counter>10){
    counter=0;
    isPLAY=false;
  }else isPLAY=true;



  if(isPLAY==false){
    if(R>5)R-=2.5;
    if(G>5)G-=2.5;
    if(B>5)B-=2.5;
    if(r>5)r-=2.5;
    if(g>5)g-=2.5;
    if(b>5)b-=2.5;
    
    if(R<5&&R>0)R=0;
    if(G<5&&G>0)G=0;
    if(B<5&&B>0)B=0;
    if(r<5&&r>0)r=0;
    if(g<5&&g>0)g=0;
    if(b<5&&b>0)b=0;
  }

if(isPLAY==true){
  if(range>0&&range<200){
    if(Bfade==false){
      B+=0.25;if(B>=255)Bfade=true;
//      if(G>0)G-=0.05;
//      if(B>0)B-=0.05;
    }
    if(rfade==false){
      r+=0.25;if(r>=255)rfade=true;
//      if(g>0)b-=0.05;
//      if(b>0)g-=0.05;
    }
  }else{
    if(Bfade==true){
      B-=0.25;if(B<=0)Bfade=false;
//      if(G<255)G+=0.05;
//      if(R<255)R+=0.05;
    }
    if(rfade==true){
      r-=0.25;if(r<=0)rfade=false;
//      if(g<255)g+=0.05;
//      if(b<255)b+=0.05;
    }
  }


  
  if(range>200&&range<400){
    if(Gfade==false){
      G+=0.25;if(G>=255)Gfade=true;
//      if(R>0)R-=0.05;
//      if(B>0)B-=0.05;
    }
    if(gfade==false){
      g+=0.25;if(g>=255)gfade=true;
//      if(r>0)r-=0.05;
//      if(b>0)b-=0.05;
    }
  }else{
    if(Gfade==true){
      G-=0.25;if(G<=0)Gfade=false;
//      if(R<255)R+=0.05;
//      if(B<255)B+=0.05;
    }
    if(gfade==true){
      g-=0.25;if(g<=0)gfade=false;
//      if(r<255)b+=0.05;
//      if(b<255)r+=0.05;
    }
  }

  
  if(range>400&&range<600){
    if(Rfade==false){
      R+=0.25;if(R>=255)Rfade=true;
//      if(G>0)G-=0.05;
//      if(B>0)B-=0.05;
    }
    if(bfade==false){
      b+=0.25;if(b>=255)bfade=true;
//      if(g>0)g-=0.05;
//      if(r>0)r-=0.05;
    }
  }else{
    if(Rfade==true){
      R-=0.25;if(R<=0)Rfade=false;
//      if(G<255)G+=0.05;
//      if(B<255)B+=0.05;
    }
    if(bfade==true){
      b-=0.25;if(b<=0)bfade=false;
//      if(g<255)g+=0.05;
//      if(r<255)r+=0.05;
    }
  }
}
  analogWrite(Rpin,(R*brigthness)/100);
  analogWrite(Gpin,(G*brigthness)/100);
  analogWrite(Bpin,(B*brigthness)/100);
  analogWrite(rpin,(r*brigthness)/100);
  analogWrite(gpin,(g*brigthness)/100);
  analogWrite(bpin,(b*brigthness)/100);

}


void RGBrun2(){
  if(brigthness==0){
    if(counter<100)counter+=2;
  }
  else{
    if(counter>0)counter--;
  }
  if(counter>10){
    counter=0;
    isPLAY=false;
  }else isPLAY=true;

  if(isPLAY==false){
    if(R>5)R-=2.5;
    if(G>5)G-=2.5;
    if(B>5)B-=2.5;
    if(r>5)r-=2.5;
    if(g>5)g-=2.5;
    if(b>5)b-=2.5;
    
    if(R<5&&R>0)R=0;
    if(G<5&&G>0)G=0;
    if(B<5&&B>0)B=0;
    if(r<5&&r>0)r=0;
    if(g<5&&g>0)g=0;
    if(b<5&&b>0)b=0;
  }

if(isPLAY==true){
  if(range>0&&range<200){
    if(Bfade==false){
      B+=0.25;if(B>=255)Bfade=true;
      if(G>0)G-=0.05;
      if(B>0)B-=0.05;
    }
    if(rfade==false){
      r+=0.25;if(r>=255)rfade=true;
      if(g>0)b-=0.05;
      if(b>0)g-=0.05;
    }
  }else{
    if(Bfade==true){
      B-=0.25;if(B<=0)Bfade=false;
      if(G<255)G+=0.05;
      if(R<255)R+=0.05;
    }
    if(rfade==true){
      r-=0.25;if(r<=0)rfade=false;
      if(g<255)g+=0.05;
      if(b<255)b+=0.05;
    }
  }

  if(range>200&&range<400){
    if(Gfade==false){
      G+=0.25;if(G>=255)Gfade=true;
      if(R>0)R-=0.05;
      if(B>0)B-=0.05;
    }
    if(gfade==false){
      g+=0.25;if(g>=255)gfade=true;
      if(r>0)r-=0.05;
      if(b>0)b-=0.05;
    }
  }else{
    if(Gfade==true){
      G-=0.25;if(G<=0)Gfade=false;
      if(R<255)R+=0.05;
      if(B<255)B+=0.05;
    }
    if(gfade==true){
      g-=0.25;if(g<=0)gfade=false;
      if(r<255)b+=0.05;
      if(b<255)r+=0.05;
    }
  }

  if(range>400&&range<600){
    if(Rfade==false){
      R+=0.25;if(R>=255)Rfade=true;
      if(G>0)G-=0.05;
      if(B>0)B-=0.05;
    }
    if(bfade==false){
      b+=0.25;if(b>=255)bfade=true;
      if(g>0)g-=0.05;
      if(r>0)r-=0.05;
    }
  }else{
    if(Rfade==true){
      R-=0.25;if(R<=0)Rfade=false;
      if(G<255)G+=0.05;
      if(B<255)B+=0.05;
    }
    if(bfade==true){
      b-=0.25;if(b<=0)bfade=false;
      if(g<255)g+=0.05;
      if(r<255)r+=0.05;
    }
  }
}
  
  analogWrite(Rpin,(R*brigthness)/100);
  analogWrite(Gpin,(G*brigthness)/100);
  analogWrite(Bpin,(B*brigthness)/100);
  analogWrite(rpin,(r*brigthness)/100);
  analogWrite(gpin,(g*brigthness)/100);
  analogWrite(bpin,(b*brigthness)/100);

}


void GRAPH(){
    Serial.print(" ");
  Serial.print(0);
  Serial.print(" ");
  Serial.print(100);
  Serial.print(" ");
  Serial.print(500);
  Serial.print(" ");
//  Serial.print(750);
//  Serial.print(" ");
//  Serial.print(1023);
//  Serial.print(" ");
//  Serial.print("AVG : ");
//  Serial.print(average);
//  Serial.print("  ");
//  Serial.print("WAVE : ");
//  Serial.print(wave);
//  Serial.print("  ");
//  Serial.print("UP : ");
//  Serial.print(UP);
//  Serial.print("  ");
//  Serial.print("DOWN : ");
//  Serial.print(DOWN);
  Serial.print("  ");
  Serial.print(brigthness);
  Serial.print("  ");
  Serial.print(range);

  Serial.println(" ");
}


double MAX(double a, double b){
  if(a>b)return a;
  else return b;
}
int MAX(int a, int b){
  if(a>b)return a;
  else return b;
}
double MIN(double a, double b){
  if(a<b)return a;
  else return b;
}

int delta(int a, int b){
  int temp = MAX(a,b)-MIN(a,b); 
  return temp;
}
double delta(double a, double b){
  double temp = MAX(a,b)-MIN(a,b); 
  return temp;
}
