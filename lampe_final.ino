
int f = 1;
unsigned long startTime[4] = {0, 0, 0, 0 };
unsigned long t1[4] = {157000*f,77000*f,100000*f,3000*f};
unsigned long t2[4]=  {357000,127000,200000,5000};
unsigned long t3[4] = {407000,227000,300000,7000};
unsigned long t4[4] = {457000,257000,351000,10000};

int led[4] = {3,5,6,9} ;     // the PWM pin the LED is attached to
int x= 0;// serilaprint to watch
int del = 100; //delay

float minlevel1[4] = {3,20,30,25};
float brightness[4] = {3,20,30,25};    // how bright the LED is
float fadeAmountUP[4] = {((255-brightness[0])/(t1[0]/del)),((255-brightness[1])/(t1[1]/del)),((255-brightness[2])/(t1[2]/del)),((255-brightness[3])/(t1[3]/del))};    // how many points to fade the LED by
float fadeAmountDOWN[4] = {((255-minlevel1[0])/((t3[0]-t2[0])/del)),((255-minlevel1[1])/((t3[1]-t2[1])/del)),((255-minlevel1[2])/((t3[2]-t2[2])/del)),((255-minlevel1[3])/((t3[3]-t2[3])/del))};    // how many points to fade the LED by

//       t1              t2                               t1'          t2' ...         
//        ________________                                .____________
//       .                  .                           .
//     .                       .                      .
//   .                            .  t3          t4 .
// .                                ._____________.
//                                    
//.................................................................................



void setup()
{  
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); 
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  Serial.println("OK");
}

void loop()
{

for (int i=0; i<4; i++) {
   unsigned long loopTime[4] = {millis() - startTime[0],millis() - startTime[1],millis() - startTime[2],millis() - startTime[3]}; //Calculate the time since last time the cycle was completed

 if ((loopTime[i] <= t1[i]) && (brightness[i] < 255)) //Check if the time is less than 1000 millis, and if so, run loop 1
 {
  brightness[i] = brightness[i]  + fadeAmountUP[i];
  Serial.print("led "); 
  Serial.print(x);   
  Serial.print("="); 
  Serial.println(brightness[x]);
  analogWrite(led[i], brightness[i]);



 }


 else if (loopTime[i] > t1[i] && loopTime[i] <= t2[i]) //If time is over 1000 millis and less than/or 2000 millis, run loop 2
 {
  brightness[i] = 255;
  Serial.print("led "); 
  Serial.print(x);   
  Serial.print("="); 
  Serial.println(brightness[x]);  
  analogWrite(led[i], brightness[i]);


 }
 
  else if (((loopTime[i] > t2[i]) && (loopTime[i] <= t3[i])) && (brightness[i] >  minlevel1[i])) //If time is over 1000 millis and less than/or 2000 millis, run loop 2
 {
       brightness[i] = brightness[i]- fadeAmountDOWN[i];
        Serial.print("led "); 
  Serial.print(x);   
  Serial.print("="); 
       Serial.println(brightness[x]);
       analogWrite(led[i], brightness[i]);

 }
   else if ((loopTime[i] > t3[i]) && (loopTime[i] <= t4[i]) ) //If time is over  and less than/or 2000 millis, run loop 2
 {
       brightness[i] = minlevel1[i];
        Serial.print("led "); 
     Serial.print(x);   
     Serial.print("="); 
       Serial.println(brightness[x]);
       
       analogWrite(led[i], brightness[i]);

 }
 
 else if (loopTime[i] > t4[i]) //If time is over 2000 millis, set the startTime to millis so the loop time will be reset to zero
 {
   startTime[i] = millis();
}
}
delay(del);
}


