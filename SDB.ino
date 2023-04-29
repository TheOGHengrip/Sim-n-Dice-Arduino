//Botones
const byte BOTON01 = A0;
const byte BOTON02 = A1;
const byte BOTON03 = A2;
const byte BOTON04 = A3;
const byte BOTON05 = A4;
const byte BOTON06 = 1;
const byte BOTON07 = 2;
const byte BOTON08 = 3;
const byte BOTON09 = 4;

//LEDS
const byte LED01 = 5;
const byte LED02 = 6;
const byte LED03 = 7;
const byte LED04 = 8;
const byte LED05 = 9;
const byte LED06 = 10;
const byte LED07 = 11;
const byte LED08 = 12;
const byte LED09 = 13;

const int buzzer = 9; //Buzzer

const byte MAX_RONDAS = 10;//El maximo de rondas definido es 10

const int VELOCIDAD_INICIAL = 1000; //Velocidad de la secuencia de inicio

byte ronda = 0;
byte secuencia[MAX_RONDAS + 1];
int velocidad = VELOCIDAD_INICIAL; 

// Esta parte del código se elimina en la versión final debido a que no integramos el buzzer
#define NOTA_B3 246.94 
#define NOTA_C4 261.63 
#define NOTA_C4S 277.18 
#define NOTA_D4 293.66 
#define NOTA_E4 329.63 
#define NOTA_F4 349.23 
#define T_NEGRA 1
#define T_BLANCA 2
#define T_REDONDA 4
#define T_CORCHEA 0.5
#define T_SEMICORCHEA 0.25
#define T_FUSA 0.125
#define T_SEMIFUSA 0.0625
int tempo = 150; //Duración de las notas

// Control de los botones y su respectivo retraso
long BOTONCHECK01 = 0;
long BOTONCHECK02 = 0; 
long BOTONCHECK03 = 0; 
long BOTONCHECK04 = 0; 
long BOTONCHECK05 = 0; 
long BOTONCHECK06 = 0; 
long BOTONCHECK07 = 0; 
long BOTONCHECK08 = 0; 
long BOTONCHECK09 = 0; 
long rebote_retardo = 50;

void setup() {
  //Botones
  pinMode(BOTON01, INPUT);
  pinMode(BOTON02, INPUT);
  pinMode(BOTON03, INPUT);
  pinMode(BOTON04, INPUT);
  pinMode(BOTON05, INPUT);
  pinMode(BOTON06, INPUT);
  pinMode(BOTON07, INPUT);
  pinMode(BOTON08, INPUT);
  pinMode(BOTON09, INPUT);
  //Pines de LEDS
  pinMode(LED01, OUTPUT);
  pinMode(LED02, OUTPUT);
  pinMode(LED03, OUTPUT);
  pinMode(LED04, OUTPUT);
  pinMode(LED05, OUTPUT);
  pinMode(LED06, OUTPUT);
  pinMode(LED07, OUTPUT);
  pinMode(LED08, OUTPUT);
  pinMode(LED09, OUTPUT);
  //Buzzer
  pinMode(buzzer, OUTPUT);
  // LEDS se inician apagados
  digitalWrite(LED01, LOW);
  digitalWrite(LED02, LOW);
  digitalWrite(LED03, LOW);
  digitalWrite(LED04, LOW);
  digitalWrite(LED05, LOW);
  digitalWrite(LED06, LOW);
  digitalWrite(LED07, LOW);
  digitalWrite(LED08, LOW);
  digitalWrite(LED09, LOW);
}

void loop()
{
  if (ronda == 0) {
    espera_pulsacion_inicio();
  }
  if (ronda == 1) {
    flash_bienvenida();
  }
  genera_secuencia(); 
  lee_respuesta(); 
}


void espera_pulsacion_inicio() {
  //Modo espera
  while (ronda == 0) {
    digitalWrite(LED01, HIGH);
    digitalWrite(LED02, HIGH);
    digitalWrite(LED03, HIGH);
    digitalWrite(LED04, HIGH);
    digitalWrite(LED05, HIGH);
    digitalWrite(LED06, HIGH);
    digitalWrite(LED07, HIGH);
    digitalWrite(LED08, HIGH);
    digitalWrite(LED09, HIGH);
    if (digitalRead(BOTON01) == HIGH) {
      digitalWrite(LED01, LOW);
      digitalWrite(LED02, LOW);
      digitalWrite(LED03, LOW);
      digitalWrite(LED04, LOW);
      digitalWrite(LED05, LOW);
      digitalWrite(LED06, LOW);
      digitalWrite(LED07, LOW);
      digitalWrite(LED08, LOW);
      digitalWrite(LED09, LOW);
      delay(500);
      ronda = 1;
      delay(50);
    }
  }
}

void reproduce_melodia(int notas[], int duracion[], int tempo, int nro_notas) {
  int x = 0;
  for (x = 0; x < nro_notas; x++) {
    delay(duracion[x] * tempo * 1.30);
  }
}

void reproduce_nota_led(byte led, int tiempo){
  int nota[] ={NOTA_C4, NOTA_D4, NOTA_E4, NOTA_F4};
  delay(tiempo); // Delay para que suene el buzzer
}

void flash_bienvenida() {
  for (byte x = LED01; x <= LED09; x++)
  {
    digitalWrite(x, HIGH);
    delay(100);
  }
  for (byte x = LED09; x >= LED01; x--)
  {
    digitalWrite(x, LOW);
    delay(100);
  }
  for (byte y = 1; y <= 3; y++)
  {
    for (byte x = LED01; x <= LED09; x++)
    {
      digitalWrite(x, HIGH);
    }
    delay (333);
    for (byte x = LED09; x >= LED01; x--)
    {
      digitalWrite(x, LOW);
    }
  }
  delay (1000);
}

void flash_respuesta_correcta() {
  // Delay para mostrar la siguiente secuencia
  delay (1500);
}

void flash_respuesta_incorrecta() {
  delay(500);
  for (byte x = LED01; x <= LED09; x++)
    {
      digitalWrite(x, HIGH);
    }  
  for (byte x = LED09; x >= LED01; x--)
    {
      digitalWrite(x, LOW);
    }
  delay(1000);
}


void genera_secuencia() {
  randomSeed(analogRead(A5));
  secuencia[ronda] = random(LED01, LED09); //Toma un pin aleatorio de los que tenemos asignados
  for (int x = 1; x <= ronda; x++) 
  {
    digitalWrite(secuencia[x], HIGH);
    reproduce_nota_led(secuencia[x], velocidad);
    //delay(velocidad); 
    digitalWrite(secuencia[x], LOW);
    delay(100 * velocidad / VELOCIDAD_INICIAL);
  }
}



void lee_respuesta() {
  boolean correcto = true;
  byte x = 1;
  byte pulsacion = 0;
  while (correcto and x <= ronda)
  { //Se comprueba si la secuencia es correcta
    if (digitalRead(BOTON09) == HIGH) {
      digitalWrite(LED09, HIGH);
      reproduce_nota_led(LED09, 250);
      digitalWrite(LED09, LOW);
      pulsacion = LED09;
      BOTONCHECK09 = millis();
    }
    else if (digitalRead(BOTON08) == HIGH) {
      digitalWrite(LED08, HIGH);
      reproduce_nota_led(LED08, 250);
      digitalWrite(LED08, LOW);
      pulsacion = LED08;
      BOTONCHECK08 = millis();
    }
    else if (digitalRead(BOTON07) == HIGH) {
      digitalWrite(LED07, HIGH);
      reproduce_nota_led(LED07, 250);
      digitalWrite(LED07, LOW);
      pulsacion = LED07;
      BOTONCHECK07 = millis();
    }
    else if (digitalRead(BOTON06) == HIGH) {
      digitalWrite(LED06, HIGH);
      reproduce_nota_led(LED06, 250);
      digitalWrite(LED06, LOW);
      pulsacion = LED06;
      BOTONCHECK06 = millis();
    }
    else if (digitalRead(BOTON05) == HIGH) {
      digitalWrite(LED05, HIGH);
      reproduce_nota_led(LED05, 250);
      digitalWrite(LED05, LOW);
      pulsacion = LED05;
      BOTONCHECK05 = millis();
    }
    else if (digitalRead(BOTON04) == HIGH) {
      digitalWrite(LED04, HIGH);
      reproduce_nota_led(LED04, 250);
      digitalWrite(LED04, LOW);
      pulsacion = LED04;
      BOTONCHECK04 = millis();
    }
    else if (digitalRead(BOTON03) == HIGH) {
      digitalWrite(LED03, HIGH);
      reproduce_nota_led(LED03, 250);
      digitalWrite(LED03, LOW);
      pulsacion = LED03;
      BOTONCHECK03 = millis();
    }
    else if (digitalRead(BOTON02) == HIGH) {
      digitalWrite(LED02, HIGH);
      reproduce_nota_led(LED02, 250);
      digitalWrite(LED02, LOW);
      pulsacion = LED02;
      BOTONCHECK02 = millis();
    }
    else if (digitalRead(BOTON01) == HIGH) {
      digitalWrite(LED01, HIGH);
      reproduce_nota_led(LED01, 250);
      digitalWrite(LED01, LOW);
      pulsacion = LED01;
      BOTONCHECK01 = millis();
    }
    //Comprobamos si se ha soltado el botón
    if ((pulsacion == LED09 && (millis() - BOTONCHECK09) > rebote_retardo) || 
        (pulsacion == LED08 && (millis() - BOTONCHECK08) > rebote_retardo) ||
        (pulsacion == LED07 && (millis() - BOTONCHECK07) > rebote_retardo) ||
        (pulsacion == LED06 && (millis() - BOTONCHECK06) > rebote_retardo) ||
        (pulsacion == LED05 && (millis() - BOTONCHECK05) > rebote_retardo) ||
        (pulsacion == LED04 && (millis() - BOTONCHECK04) > rebote_retardo) ||
        (pulsacion == LED03 && (millis() - BOTONCHECK03) > rebote_retardo) || 
        (pulsacion == LED02 && (millis() - BOTONCHECK02) > rebote_retardo) || 
        (pulsacion == LED01 && (millis() - BOTONCHECK01) > rebote_retardo)){  
      if (pulsacion != secuencia[x]) { //Comprobamos si lo que ingresó el jugador es correcto
        correcto = false;
      }
      else {
        x++;
        pulsacion = 0;
      }
    }
  }

  if (correcto == true) { //Al final se comprueba si se ha acertado la ronda
    delay(500);
    flash_respuesta_correcta();
    ronda++; //Incrementamos una ronda
    if (velocidad >= 50) {
      velocidad = velocidad - 50; //Se reduce la velocidad del delay para mayor dificultad
    }
  }
  else {
    flash_respuesta_incorrecta();
    ronda = 0; //Esperamos a que se inicie nueva ronda y reiniciamos a la dificultad inicial
    velocidad = VELOCIDAD_INICIAL;
    espera_pulsacion_inicio();
  }
}
