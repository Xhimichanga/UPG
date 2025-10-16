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

// Servos invertidos
bool servoInvertido[NUM_SERVOS] = {0, 1, 0, 1, 0, 1, 0, 1};

// ---------------- FUNCIONES ----------------

// Golpear nota con servos 360°
void tocarNota360(int nota, int duracion) {
  servos[nota].attach(pinesServos[nota]);

  int direccion = 0; // ajusta: <90 o >90 según dirección deseada
  if (servoInvertido[nota]) direccion = 180; // invertir si es necesario

  servos[nota].write(direccion); // iniciar golpe
  delay(150);                     // tiempo de golpe
  servos[nota].write(90);         // detener
  delay(duracion - 150);

  servos[nota].detach();
}

// Mover todos los servos a reposo (detenidos)
void moverServosInicio() {
  Serial.println("Reiniciando servos a posición de reposo...");
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(pinesServos[i]);
    servos[i].write(90); // detener servo
    delay(200);
    servos[i].detach();
  }
  Serial.println("Servos en reposo.");
}

// Función para mover solo el servo del pin 9
void moverServoPin9(int angulo) {
  int indice = -1;
  for (int i = 0; i < NUM_SERVOS; i++) {
    if (pinesServos[i] == 9) {
      indice = i;
      break;
    }
  }

  if (indice == -1) return;

  servos[indice].attach(pinesServos[indice]);
  // Para 360°, 90 = detener, <90/ >90 = dirección
  int valor = angulo;
  if (servoInvertido[indice]) valor = 180 - angulo;
  servos[indice].write(valor);
  delay(500);
  servos[indice].write(90); // detener
  servos[indice].detach();

  Serial.print("Servo pin 9 movido a: ");
  Serial.println(valor);
}

// ---------------- CANCIONES ----------------
void pruebaServos() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    for (int j = 0; j < 2; j++) {
      tocarNota360(i, 300);
    }
    delay(400);
  }
}

void elAusente() {
  tocarNota360(MI, 400);
  tocarNota360(FA, 300);
  tocarNota360(SOL, 300);
  tocarNota360(MI, 500);

  tocarNota360(MI, 300);
  tocarNota360(RE, 300);
  tocarNota360(DO, 600);
  delay(300);

  tocarNota360(RE, 350);
  tocarNota360(MI, 350);
  tocarNota360(FA, 400);
  tocarNota360(SOL, 450);

  tocarNota360(FA, 400);
  tocarNota360(MI, 400);
  tocarNota360(RE, 400);
  tocarNota360(DO, 800);
  delay(2000);
}

void noSeHablaDeBruno() {
  tocarNota360(MI, 400);
  tocarNota360(RE, 350);
  tocarNota360(DO, 550);
  tocarNota360(DO, 300);
  tocarNota360(RE, 350);
  tocarNota360(MI, 500);
  tocarNota360(RE, 350);
  tocarNota360(DO, 800);
  delay(400);
  tocarNota360(SOL, 500);
  tocarNota360(FA, 450);
  tocarNota360(MI, 550);
  tocarNota360(RE, 400);
  tocarNota360(DO, 900);
  delay(2000);
}

void laRebelion() {
  tocarNota360(SOL, 400);
  tocarNota360(SOL, 300);
  tocarNota360(LA, 300);
  tocarNota360(SOL, 400);
  tocarNota360(FA, 350);
  tocarNota360(MI, 350);
  tocarNota360(RE, 600);
  delay(300);
  tocarNota360(RE, 350);
  tocarNota360(MI, 350);
  tocarNota360(FA, 350);
  tocarNota360(SOL, 400);
  tocarNota360(MI, 450);
  tocarNota360(RE, 400);
  tocarNota360(DO, 800);
  delay(2000);
}

void estrellita() {
  tocarNota360(DO, 400);
  tocarNota360(DO, 400);
  tocarNota360(SOL, 400);
  tocarNota360(SOL, 400);
  tocarNota360(LA, 400);
  tocarNota360(LA, 400);
  tocarNota360(SOL, 800);
  delay(200);
  tocarNota360(FA, 400);
  tocarNota360(FA, 400);
  tocarNota360(MI, 400);
  tocarNota360(MI, 400);
  tocarNota360(RE, 400);
  tocarNota360(RE, 400);
  tocarNota360(DO, 800);
  delay(300);
  tocarNota360(SOL, 400);
  tocarNota360(SOL, 400);
  tocarNota360(FA, 400);
  tocarNota360(FA, 400);
  tocarNota360(MI, 400);
  tocarNota360(MI, 400);
  tocarNota360(RE, 800);
  delay(300);
  tocarNota360(SOL, 400);
  tocarNota360(SOL, 400);
  tocarNota360(FA, 400);
  tocarNota360(FA, 400);
  tocarNota360(MI, 400);
  tocarNota360(MI, 400);
  tocarNota360(RE, 800);
  delay(2000);
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_SERVOS; i++) {
    pinMode(pinesServos[i], OUTPUT);
    digitalWrite(pinesServos[i], LOW);
  }

  delay(1500);
  moverServosInicio();

  Serial.println("Xilófono listo. Escribe un número:");
  Serial.println("0 = Prueba Servos");
  Serial.println("1 = El Ausente");
  Serial.println("2 = No se Habla de Bruno");
  Serial.println("3 = La Rebelión");
  Serial.println("4 = Estrellita");
  Serial.println("9 = Reestablecer servos a reposo");
  Serial.println("S9 <0-180> = Mover servo pin 9 (360°)");
}

// ---------------- LOOP ----------------
void loop() {
  if (Serial.available() > 0) {
    String comando = Serial.readString();
    comando.trim();

    if (comando.startsWith("S9")) {
      int espacio = comando.indexOf(' ');
      if (espacio > 0) {
        int angulo = comando.substring(espacio + 1).toInt();
        if (angulo >= 0 && angulo <= 180) moverServoPin9(angulo);
        else Serial.println("Error: ángulo fuera de rango (0-180)");
      } else {
        Serial.println("Formato incorrecto. Usar: S9 <angulo>");
      }
    } else {
      int opcion = comando.toInt();
      if (opcion == 0) pruebaServos();
      else if (opcion == 1) elAusente();
      else if (opcion == 2) noSeHablaDeBruno();
      else if (opcion == 3) laRebelion();
      else if (opcion == 4) estrellita();
      else if (opcion == 9) moverServosInicio();
    }

    Serial.println("Listo. Esperando nueva opción...");
  }
}
