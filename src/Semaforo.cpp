//Realizar una solucion programable de un semaforo que contiene tanto uno de los peatones como para vehiculos, con el detalle que el de peatones cuenta con un boton.
//para ponerlo en rojo luego de 5 segundos. tendran que hacer que el semaforo actue normlamente sincronizado a los dos y teniendo en cuenta el boton. 

#include <Arduino.h>
#define DELAY_AMARILLO 5000;
#define DELAY_VERDE_ROJO 10000;
volatile int apretado;
int pin1[3]={2,3,4};
int pin2=5;
int pin3[2]={6,7};
int tiempoPrevio = 0;
int tiempoDelay1 = DELAY_AMARILLO;
int tiempoDelay2 = DELAY_VERDE_ROJO;
int tiempoPrevio1= 0;
int tiempoPrevio2= 0;
int sem1[4][3]={
                {1,0,0},
                {1,1,0},
                {0,0,1},
                {0,1,0}
                };
int sem2[2][2]={
                 {0,1},
                 {1,0}
                };
  void ISR_Boton();
void setup() {
  for(int i=0; i<3; i++){
    pinMode (pin1[i], OUTPUT);
                        }
 pinMode (pin2, INPUT);
 attachInterrupt(digitalPinToInterrupt(pin2),ISR_Boton,RISING);
             }
void loop() {
  unsigned long int tiempoActual=millis();
  if(tiempoActual-tiempoPrevio1>=tiempoDelay1){
  for(int i=0; i<1; i++){
    for(int c=0; c<3; c++){
        digitalWrite(pin1[c], sem1[i][c]);
        tiempoPrevio1=tiempoActual;
                          }
                        }
  if(tiempoActual-tiempoPrevio2>=tiempoDelay2){
    for(int i=0; i<4; i++){
      for(int c=0; c<3; c++){
        digitalWrite(pin1[c], sem1[i][c]);
      }
    }
  }
    tiempoPrevio2=tiempoActual;
  }
  if(apretado){
    apretado=false;
    int EstadoSem = digitalRead(pin2);
    digitalWrite(pin2,!EstadoSem);
    for(int i=0; i<2; i++){
      for(int c=0; c<2; c++){
        digitalWrite(pin3[c], sem2[i][c]);
      }
    }
    }

}
void ISR_Boton(){
apretado=true;
}