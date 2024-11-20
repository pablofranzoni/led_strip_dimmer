// Configuración de pines
const int pwmPin = 0;       // Pin de salida PWM (pines compatibles en el ATtiny85 son 0 y 1)
const int buttonPin = 1;    // Pin de entrada para el pulsador
const int debounceDelay = 50;  // Tiempo de anti-rebote en milisegundos

int pwmValue = 0;           
int step = 51;              
bool buttonState = HIGH;     
bool lastButtonState = HIGH; 
unsigned long lastDebounceTime = 0; 

void setup() {
  pinMode(pwmPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  
  analogWrite(pwmPin, pwmValue);     
}

void loop() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        pwmValue += step;
        
        if (pwmValue > 255) {
          pwmValue = 0;
        }
        
        analogWrite(pwmPin, pwmValue);
      }
    }
  }

  lastButtonState = reading;
}
