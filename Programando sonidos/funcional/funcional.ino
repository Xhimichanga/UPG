#include <Servo.h>

const int NUM_SERVOS = 8;
int pinesServos[NUM_SERVOS] = {2, 3, 4, 5, 6, 9, 10, 11};
Servo servos[NUM_SERVOS];

// Definir notas
#define DO      0
#define RE      1
#define MI      2
#define FA      3
#define SOL     4
#define LA      5
#define SI      6
#define DO_ALTO 7

// Ángulos
//int angulosGolpe[NUM_SERVOS] = {60, 65, 65, 70, 75, 80, 80, 85};
int angulosGolpe[NUM_SERVOS] = {30, 50, 30, 30, 30, 30, 30, 30};

const int ANGULO_REPOSO = 10;

// Servos invertidos
//bool servoInvertido[NUM_SERVOS] = {false, true, false, true, false, true, false, true};
bool servoInvertido[NUM_SERVOS] = {0, 1, 0, 1, 0, 1, 0, 1};

// ---------------- FUNCIONES ----------------

void tocarNota(int nota, int duracion) {
  servos[nota].attach(pinesServos[nota]);  // conectar solo al usarlo

  int golpe = angulosGolpe[nota];
  int reposo = ANGULO_REPOSO;
  if (servoInvertido[nota]) {
    golpe = 180 - angulosGolpe[nota];
    reposo = 180 - ANGULO_REPOSO;
  }

  servos[nota].write(golpe);
  delay(150);
  servos[nota].write(reposo);
  delay(duracion - 150);

  servos[nota].detach();  // desconectar después de usar
}

void moverServosInicio() {
  // Todos los servos a posición 0 suave
  Serial.println("Reiniciando servos a posición 0°...");
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(pinesServos[i]);

    if (servoInvertido[i]) {
      servos[i].write(180);  // posición 0 equivalente en invertido
    } else {
      servos[i].write(0);
    }

    delay(200);
    servos[i].detach();
  }
  Serial.println("Servos colocados en 0°.");
}

// Canciones
void pruebaServos() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    for (int j = 0; j < 2; j++) {
      tocarNota(i, 300);
    }
    delay(400);
  }
}

void elAusente() {
  tocarNota(MI, 400);
  tocarNota(FA, 300);
  tocarNota(SOL, 300);
  tocarNota(MI, 500);

  tocarNota(MI, 300);
  tocarNota(RE, 300);
  tocarNota(DO, 600);
  delay(300);

  tocarNota(RE, 350);
  tocarNota(MI, 350);
  tocarNota(FA, 400);
  tocarNota(SOL, 450);

  tocarNota(FA, 400);
  tocarNota(MI, 400);
  tocarNota(RE, 400);
  tocarNota(DO, 800);
  delay(2000);
}

void noSeHablaDeBruno() {
  tocarNota(MI, 400);
  tocarNota(RE, 350);
  tocarNota(DO, 550);
  tocarNota(DO, 300);
  tocarNota(RE, 350);
  tocarNota(MI, 500);
  tocarNota(RE, 350);
  tocarNota(DO, 800);
  delay(400);
  tocarNota(SOL, 500);
  tocarNota(FA, 450);
  tocarNota(MI, 550);
  tocarNota(RE, 400);
  tocarNota(DO, 900);
  delay(2000);
}

void laRebelion() {
  tocarNota(SOL, 400);
  tocarNota(SOL, 300);
  tocarNota(LA, 300);
  tocarNota(SOL, 400);
  tocarNota(FA, 350);
  tocarNota(MI, 350);
  tocarNota(RE, 600);
  delay(300);
  tocarNota(RE, 350);
  tocarNota(MI, 350);
  tocarNota(FA, 350);
  tocarNota(SOL, 400);
  tocarNota(MI, 450);
  tocarNota(RE, 400);
  tocarNota(DO, 800);
  delay(2000);
}

void estrellita() {
  tocarNota(DO, 400);
  tocarNota(DO, 400);
  tocarNota(SOL, 400);
  tocarNota(SOL, 400);
  tocarNota(LA, 400);
  tocarNota(LA, 400);
  tocarNota(SOL, 800);
  delay(200);
  tocarNota(FA, 400);
  tocarNota(FA, 400);
  tocarNota(MI, 400);
  tocarNota(MI, 400);
  tocarNota(RE, 400);
  tocarNota(RE, 400);
  tocarNota(DO, 800);
  delay(300);
  tocarNota(SOL, 400);
  tocarNota(SOL, 400);
  tocarNota(FA, 400);
  tocarNota(FA, 400);
  tocarNota(MI, 400);
  tocarNota(MI, 400);
  tocarNota(RE, 800);
  delay(300);
  tocarNota(SOL, 400);
  tocarNota(SOL, 400);
  tocarNota(FA, 400);
  tocarNota(FA, 400);
  tocarNota(MI, 400);
  tocarNota(MI, 400);
  tocarNota(RE, 800);
  delay(2000);
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);

  // Mantener pines de señal en bajo hasta que se usen
  for (int i = 0; i < NUM_SERVOS; i++) {
    pinMode(pinesServos[i], OUTPUT);
    digitalWrite(pinesServos[i], LOW);
  }

  delay(1500);  // esperar estabilidad eléctrica
  moverServosInicio();  // llevar a posición 0

  Serial.println("Xilófono listo. Escribe un número:");
  Serial.println("0 = Prueba Servos");
  Serial.println("1 = El Ausente");
  Serial.println("2 = No se Habla de Bruno");
  Serial.println("3 = La Rebelión");
  Serial.println("4 = Estrellita");
  Serial.println("9 = Reestablecer servos a 0°");
}

// ---------------- LOOP ----------------
void loop() {
  if (Serial.available()) {
    int opcion = Serial.parseInt();

    if (opcion == 0) pruebaServos();
    else if (opcion == 1) elAusente();
    else if (opcion == 2) noSeHablaDeBruno();
    else if (opcion == 3) laRebelion();
    else if (opcion == 4) estrellita();
    else if (opcion == 9) moverServosInicio();  // nueva opción

    while (Serial.available()) Serial.read();
    Serial.println("Listo. Esperando nueva opción...");
  }
}
