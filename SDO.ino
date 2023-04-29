// definimos constantes para los diferentes pines que usamos
const byte BOTON01 = A0;
const byte BOTON02 = A1;
const byte BOTON03 = A2;
const byte BOTON04 = A3;
const byte BOTON05 = A4;
const byte BOTON06 = 1;
const byte BOTON07 = 2;
const byte BOTON08 = 3;
const byte BOTON09 = 4;

const byte LED01 = 5;
const byte LED02 = 6;
const byte LED03 = 7;
const byte LED04 = 8;
const byte LED05 = 9;
const byte LED06 = 10;
const byte LED07 = 11;
const byte LED08 = 12;
const byte LED09 = 13;

const byte MAX_RONDAS = 255; // el nmero mximo de rondas ser de 255

const int VELOCIDAD_INICIAL = 1000; // velocidad inicial en milisegundos a la que se mostrar la secuencia

byte ronda = 0; //numero de ronda en la que vamos
byte secuencia[MAX_RONDAS + 1]; //array para alojar la secuencia que se va generando. El array empieza en el elemento 0 pero no lo usamos, empezamos en el 1 para hacer coincidir con el nmero de ronda
int velocidad = VELOCIDAD_INICIAL; // tiempo en milisegundos que permanecen encendidos los LEDs cuando muestra la secuencia a repetir

// Definimos notas musicales, duraciones y Variable tempo
#define NOTA_B3 246.94 // Si en 3 Octava
#define NOTA_C4 261.63 // Do en 4 Octava
#define NOTA_C4S 277.18 // Do # en 4 Octava
#define NOTA_D4 293.66 // Re en 4 Octava
#define NOTA_E4 329.63 // Mi en 4 Octava
#define NOTA_F4 349.23 // Fa en 4 Octava

#define T_NEGRA 1
#define T_BLANCA 2
#define T_REDONDA 4
#define T_CORCHEA 0.5
#define T_SEMICORCHEA 0.25
#define T_FUSA 0.125
#define T_SEMIFUSA 0.0625

int tempo = 150; // duracin de un pulso en milisegundos. Se usa para la duracin de las notas

// variables para el controlde rebotes / bouncing de los pulsadores. Cada uno de los 4 pulsadores tiene las suyas
long BOTONCHECK01 = 0; //momento en el que se produjo la seal anterior del boton
long BOTONCHECK02 = 0; 
long BOTONCHECK03 = 0; 
long BOTONCHECK04 = 0; 
long BOTONCHECK05 = 0; 
long BOTONCHECK06 = 0; 
long BOTONCHECK07 = 0; 
long BOTONCHECK08 = 0; 
long BOTONCHECK09 = 0; 
long rebote_retardo = 50; // tiempo en milisegundos transcurrido que si se supera entre dos seales del botn deja de considerarse un rebote

void setup() {
  // establecemos los pines de los botones en modo entrada
  pinMode(BOTON01, INPUT);
  pinMode(BOTON02, INPUT);
  pinMode(BOTON03, INPUT);
  pinMode(BOTON04, INPUT);
  pinMode(BOTON05, INPUT);
  pinMode(BOTON06, INPUT);
  pinMode(BOTON07, INPUT);
  pinMode(BOTON08, INPUT);
  pinMode(BOTON09, INPUT);
  // establecemos los pines de los LEDs en modo salida
  pinMode(LED01, OUTPUT);
  pinMode(LED02, OUTPUT);
  pinMode(LED03, OUTPUT);
  pinMode(LED04, OUTPUT);
  pinMode(LED05, OUTPUT);
  pinMode(LED06, OUTPUT);
  pinMode(LED07, OUTPUT);
  pinMode(LED08, OUTPUT);
  pinMode(LED09, OUTPUT);
  // establecemos el pin del buzzer/zumbador en modo salida
  // inicializamos las salidasa a LOW
  digitalWrite(LED01, LOW);
  digitalWrite(LED02, LOW);
  digitalWrite(LED03, LOW);
  digitalWrite(LED04, LOW);
  digitalWrite(LED05, LOW);
  digitalWrite(LED06, LOW);
  digitalWrite(LED07, LOW);
  digitalWrite(LED08, LOW);
  digitalWrite(LED09, LOW);

  //Serial.begin(9600);
}

void loop()
{
  if (ronda == 0) { // si la ronda es 0 es que aun no han pulsado el botn de inicio para empezar una partida nueva
    espera_pulsacion_inicio();
  }
  if (ronda == 1) { // si estamos en la primera ronda hacemos las seales de bienvenida
    flash_bienvenida();
  }
  genera_secuencia(); //generamos la secuencia con tantos elementos como el nmero de ronda en el que vamos
  lee_respuesta(); //leemos la respuesta del jugador
}


void espera_pulsacion_inicio() {
  // esperamos hasta que pulsen el boton de inico de nueva partida
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
  /* notas = array con las notas (frecuencias o notas pre-definidas)
     duracion = array con la duracin de cada nota del array notas[] son el factor multiplicador del tempo, es decir si queremos que dure un pulso de tempo, indicaremos 1 o T_NEGRA
     tempo = duracin de un pulso (una nota negra) en milisegundos
     nro_notas = numero de notas que compone el array notas[]
   */
  int x = 0;
  for (x = 0; x < nro_notas; x++) {
    //falta aqui funcion tone() en version de 9 leds 9 botones
    delay(duracion[x] * tempo * 1.30);
  }
}

void reproduce_nota_led(byte led, int tiempo){
  int nota[] ={NOTA_C4, NOTA_D4, NOTA_E4, NOTA_F4};
  //falta aqui funcion tone() en version de 9 leds 9 botones
  delay(tiempo); // hacemos delay para que el led permanezca encendido mientras suena la nota
}

void tema_inicio() {
  // meloda que suena al inicio de las partidas
  int notas[] = {NOTA_B3, NOTA_B3,  NOTA_B3, NOTA_D4, NOTA_B3, NOTA_D4};
  int duracion[] = {T_NEGRA, T_NEGRA, T_NEGRA, T_BLANCA, T_NEGRA, T_REDONDA};
  //tempo = 150;
  // reproducimos la meloda
  reproduce_melodia (notas, duracion, 100, 6);
}

void tema_game_over (){
  //meloda que suena al perder la partida
  int notas[] = {NOTA_D4, NOTA_C4S, NOTA_C4, NOTA_B3};
  int duracion[] = {T_NEGRA, T_NEGRA, T_NEGRA, T_REDONDA};
  reproduce_melodia (notas, duracion, 300, 4);
}

void flash_bienvenida() {
  // Hacemos una secuencia de luces de inicio de partida
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
  // y Sunena la meloda de inicio
  tema_inicio();
  delay (1000);
}

void flash_respuesta_correcta() {
  // esperamos 1 segundo para continuar con la siguiente secuencia
  delay (1000);
}

void flash_respuesta_incorrecta() {
  // Suena la meloda game over con los 4 leds encendidos
  delay(500);
  for (byte x = LED01; x <= LED09; x++)
    {
      digitalWrite(x, HIGH);
    }  
  tema_game_over();
  for (byte x = LED09; x >= LED01; x--)
    {
      digitalWrite(x, LOW);
    }
  delay(1000);
}


void genera_secuencia() {
  // Generamos el sigeuinte elemento de la secuncia y la reproducimos
  randomSeed(analogRead(A5)); // generamos una semilla para generar el nmero aleatorio
  secuencia[ronda] = random(LED01, LED09); //generamos un numero aleatorio entre 2 y 5 que son lospines dondea estn los leds
  for (int x = 1; x <= ronda; x++) // reproducimos la secuencia
  {
    digitalWrite(secuencia[x], HIGH);
    reproduce_nota_led(secuencia[x], velocidad);
    //delay(velocidad); 
    digitalWrite(secuencia[x], LOW);
    delay(100 * velocidad / VELOCIDAD_INICIAL);
  }
}



void lee_respuesta() {
  // leemos las pulsaciones del jugador y vamos comprobando que la secuencia sea correcta
  boolean correcto = true;
  byte x = 1;
  byte pulsacion = 0;
  while (correcto and x <= ronda)
  { //vamos leyendo pulsacion a pulsacin y comprobando que la secuencia vaya siendo correcta
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
  

    if ((pulsacion == LED09 && (millis() - BOTONCHECK09) > rebote_retardo) || 
        (pulsacion == LED08 && (millis() - BOTONCHECK08) > rebote_retardo) ||
        (pulsacion == LED07 && (millis() - BOTONCHECK07) > rebote_retardo) ||
        (pulsacion == LED06 && (millis() - BOTONCHECK06) > rebote_retardo) ||
        (pulsacion == LED05 && (millis() - BOTONCHECK05) > rebote_retardo) ||
        (pulsacion == LED04 && (millis() - BOTONCHECK04) > rebote_retardo) ||
        (pulsacion == LED03 && (millis() - BOTONCHECK03) > rebote_retardo) || 
        (pulsacion == LED02 && (millis() - BOTONCHECK02) > rebote_retardo) || 
        (pulsacion == LED01 && (millis() - BOTONCHECK01) > rebote_retardo)){  
         // Solo entramos en caso de que se haya pulsado un boton y ya se haya soltado, 
         // para saber si se solt de verdad utilizamos las comparaciones de rebote para evitar falsas sueltas del botn
      if (pulsacion != secuencia[x]) { //si se ha fallado correcto = false y se sale del bucle
        correcto = false;
      }
      else { //si no se ha fallado se pasa al siguiente elemento de la secuencia
        x++;
        pulsacion = 0;
      }
    }
  } //fin while

  if (correcto == true) { //si correcto es que se ha acertado toda la secuencia
    delay(500);
    flash_respuesta_correcta();
    ronda++; //incrementamos una ronda
    if (velocidad >= 50) {
      velocidad = velocidad - 50; // incrementamos la velocidad de muestra de la secuencia (10 milisegundos ms rpida)
    }
  }
  else { //si correcto == false es que se ha fallado
    flash_respuesta_incorrecta();
    ronda = 0; //ponemos ronda a 0 para volver a esperar que inicien una nueva partida
    velocidad = VELOCIDAD_INICIAL;
    espera_pulsacion_inicio();
  }
}
