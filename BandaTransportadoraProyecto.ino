#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

// Variables para ángulos de los servos de posición fija
const int ANGULO_INICIAL = 45;
const int ANGULO_FINAL = 0;

// Pines servos
const int PIN_SERVO_ROJO = 7;
const int PIN_SERVO_AZUL = 8;
const int PIN_SERVO_360 = 6; // Asignamos pin 6 para el servo 360°

Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_614MS,
  TCS34725_GAIN_1X
);

Servo servoRojo;
Servo servoAzul;
Servo servo360;

unsigned long prevMillis = 0;  // Para control de tiempo

void setup() {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado");
  } else {
    Serial.println("No se detectó el sensor. Verifica conexiones");
    while (1);
  }

  // Conectar servos
  servoRojo.attach(PIN_SERVO_ROJO);
  servoAzul.attach(PIN_SERVO_AZUL);
  servo360.attach(PIN_SERVO_360);

  // Posición inicial servos de posición fija
  servoRojo.write(ANGULO_INICIAL);
  servoAzul.write(ANGULO_INICIAL);

  // Iniciar servo 360° girando (90 = stop, >90 gira en una dirección, <90 gira en otra)
  // Para girar hacia adelante, usamos por ejemplo 180 (máxima velocidad)
  servo360.write(160);
}

void loop() {
  unsigned long currentMillis = millis();

  // El servo 360 gira constantemente, no hay que tocarlo aquí

  // Chequeo cada 1 segundo (1000 ms)
  if (currentMillis - prevMillis >= 1000) {
    prevMillis = currentMillis;

    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

    String colorDetectado = "Indefinido";

    // Clasificación de color dominante (cambia verde por azul)
    if (r > b && r > g) {
      colorDetectado = "ROJO";
      servoRojo.write(ANGULO_FINAL);  // Mover servo rojo a posición activada
      servoAzul.write(ANGULO_INICIAL); // Servo azul en reposo
    }
    else if (b > r && b > g) {
      colorDetectado = "AZUL";
      servoAzul.write(ANGULO_FINAL);  // Mover servo azul a posición activada
      servoRojo.write(ANGULO_INICIAL); // Servo rojo en reposo
    }
    else {
      colorDetectado = "OTRO";
      servoRojo.write(ANGULO_INICIAL);
      servoAzul.write(ANGULO_INICIAL);
    }

    // Solo imprimir si detecta rojo o azul
    if (colorDetectado == "ROJO" || colorDetectado == "AZUL") {
      uint16_t colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
      uint16_t lux = tcs.calculateLux(r, g, b);

      Serial.print("Color Temp: "); Serial.print(colorTemp); Serial.print(" K - ");
      Serial.print("Lux: "); Serial.print(lux); Serial.print(" - ");
      Serial.print("R: "); Serial.print(r); Serial.print(" ");
      Serial.print("G: "); Serial.print(g); Serial.print(" ");
      Serial.print("B: "); Serial.print(b); Serial.print(" ");
      Serial.print("C: "); Serial.print(c); Serial.print(" - ");

      Serial.print("Color detectado: ");
      Serial.println(colorDetectado);
    }
  }

  // Aquí el loop sigue sin delay para que el servo360 gire sin interrupciones
}
