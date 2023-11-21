#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL2Nbn15xIT"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "-yGvVDI3SQ2E1M3mIWs6CQdA4IJL9sAg"

#include <SerialRelay.h>
#include "ESP8266_Lib.h"
#include "BlynkSimpleShieldEsp8266.h"

char auth[] = "-yGvVDI3SQ2E1M3mIWs6CQdA4IJL9sAg";
char ssid[] = "TP-Link_FD2C";
char pass[] = "gustavoaranda";

SerialRelay relays(4, 5, 1); //(data, clk, numero de modulos)

#include "SoftwareSerial.h"
SoftwareSerial EspSerial(10, 11);  // RX, TX
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    relays.SetRelay(1, SERIAL_RELAY_ON, 1);  // liga o relé 01
    Serial.println("Relé 01 ligado");
  } else {
    relays.SetRelay(1, SERIAL_RELAY_OFF, 1);  // desliga o relé 01
    Serial.println("Relé 01 desligado");
  }
}

BLYNK_WRITE(V2) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    relays.SetRelay(2, SERIAL_RELAY_ON, 1);  // liga o relé 02
  } else {
    relays.SetRelay(2, SERIAL_RELAY_OFF, 1);  // desliga o relé 02
  }
}


// BLYNK_WRITE(V1) {
//   int energia = param.asInt();  // Obtém o valor do slider (0 a 100)

//   // Limita a energia entre 0 e 100
//   energia = constrain(energia, 0, 100);
  
//   if (energia > 0) {
//     relays.SetRelay(3, SERIAL_RELAY_ON, 1);  // Liga o relé 03
//     Serial.print("Fita de LED ligada. Energia: ");
//     Serial.println(energia);
//   } else {
//     relays.SetRelay(3, SERIAL_RELAY_OFF, 1);  // Desliga o relé 03
//     Serial.println("Fita de LED desligada");
//   }
// }

#define ledPin 4

BLYNK_WRITE(V1) {
  int sliderValue = param.asInt();  // Obtém o valor do slider (0 a 100)

  // Mapeia o valor do slider para um intervalo de 0 a 255 (PWM)
  int intensidadeLuz = map(sliderValue, 0, 100, 0, 255);
  
  if (intensidadeLuz > 0) {
    relays.SetRelay(3, SERIAL_RELAY_ON, 1);  // Liga o relé 03
    analogWrite(ledPin, intensidadeLuz);  // Define a intensidade da luz
    Serial.print("LED ligado. Intensidade: ");
    Serial.println(intensidadeLuz);
  } else {
    relays.SetRelay(3, SERIAL_RELAY_OFF, 1);  // Desliga o relé 03
    analogWrite(ledPin, 0);  // Desliga o LED
    Serial.println("LED desligado");
  }
}


void setup() {
  Serial.begin(9600);
  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
}

void loop() {
  Blynk.run();
}