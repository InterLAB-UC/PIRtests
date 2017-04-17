// trabajando con un sensor PIR para detectar movimiento, usa un
// buzzer a modo de alarma.
// traducido de: http://blog.makezine.com/projects/pir-sensor-arduino-alarm/

 
int ledPin = 13;                // el pin para el LED
int inputPin = 2;               // el pin de entrada para el sensor PIR (digital el pin)
int pirState = LOW;             // asumimos que no hay movimiento detectado
int val = 0;                    // una variable para leer el estatus del pin
int pinSpeaker = 10;            // bocina en un PWM pin (digital 9, 10 u 11)

void setup() {
  pinMode(ledPin, OUTPUT);      // declaramos el LED como salida
  pinMode(inputPin, INPUT);     // declaramos el sensor como entrada
  pinMode(pinSpeaker, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  val = digitalRead(inputPin);  // leemos el valor de entrada
  if (val == HIGH) {            // checamos si la entrada esta en HIGH
    digitalWrite(ledPin, HIGH);  // se prende el led
    playTone(500, 260);
    delay(150);

    
    if (pirState == LOW) {
      // encendemos
      Serial.println("Motion detected!");
      // solo queremos el cambio de salida, no de estado
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW); // se apaga el LED 
      playTone(0, 0);
      delay(300);    
      if (pirState == HIGH){
      // apagamos
      Serial.println("Motion ended!");
      // solo queremos el cambio de salida, no de estado
      pirState = LOW;
    }
  }
}
// duración en mSecs, frecuencia en hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

