// Configuración de pines
const int pwmPin = 0;       // Pin de salida PWM (pines compatibles en el ATtiny85 son 0 y 1)
const int buttonPin = 1;    // Pin de entrada para el pulsador
const int debounceDelay = 50;  // Tiempo de anti-rebote en milisegundos

// Variables de estado
int pwmValue = 0;           // Valor de salida PWM (0 a 255)
int step = 51;              // Paso del PWM (20% de 255 ≈ 51)
bool buttonState = HIGH;     // Estado actual del botón (inicializado en HIGH)
bool lastButtonState = HIGH; // Último estado leído del botón
unsigned long lastDebounceTime = 0; // Última vez que se cambió el estado

void setup() {
  pinMode(pwmPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Activar resistencia de pull-up interna
  analogWrite(pwmPin, pwmValue);     // Inicializamos la salida PWM en 0%
}

void loop() {
  // Lectura del botón con eliminación de rebote
  bool reading = digitalRead(buttonPin);

  // Si el estado del botón cambió, reiniciamos el temporizador de rebote
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Si ha pasado el tiempo de rebote y el estado es estable
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Si el estado es diferente al último registrado
    if (reading != buttonState) {
      buttonState = reading;

      // Si el botón está presionado (ahora LOW debido al pull-up interno)
      if (buttonState == LOW) {
        // Incrementamos el valor PWM en 20%
        pwmValue += step;
        
        // Si el valor supera 255 (100%), volvemos a 0
        if (pwmValue > 255) {
          pwmValue = 0;
        }
        
        // Actualizamos la salida PWM
        analogWrite(pwmPin, pwmValue);
      }
    }
  }

  // Guardamos el estado actual del botón para la próxima lectura
  lastButtonState = reading;
}
