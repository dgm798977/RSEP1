#include <Arduino.h>
#include <nrf.h>
#include <nrf_gpio.h>

#define PWM_PIN  13
#define TOP_VALUE 200
int pinSensor = A0;
int value;
uint8_t PWMvalue;
static uint16_t pwm_value = TOP_VALUE / 2;

void set_duty_cycle(uint8_t percent) {
    if (percent > 100) percent = 100;
    pwm_value = (TOP_VALUE * percent) / 100;  
}

void setup() {
  // 1. Habilitar el módulo PWM0
  NRF_PWM0->ENABLE = 1;

  // 2. Configurar el modo de operación
  NRF_PWM0->MODE = PWM_MODE_UPDOWN_Up;  // Cuenta solo hacia arriba

  // 3. Configurar la frecuencia
  NRF_PWM0->PRESCALER = PWM_PRESCALER_PRESCALER_DIV_16; // 1 MHz / 16 = 62.5 kHz

  // 4. Definir el "TOP" del contador (periodo PWM)
  NRF_PWM0->COUNTERTOP = TOP_VALUE;  // Para 1 kHz: 62.5kHz / 1kHz = 62.5

  // 5. Configurar el pin de salida
  NRF_PWM0->PSEL.OUT[0] = PWM_PIN | (1 << 31);  // Conectar P0.13 al PWM0_CH0

  // 6. Configurar el duty cycle (SEQ[0].VALUES)
  static uint16_t pwm_values[1];  // Un solo valor en la secuencia
  

  NRF_PWM0->SEQ[0].PTR = (uint32_t)&pwm_value;
  NRF_PWM0->SEQ[0].CNT = 1;  // Usamos solo un valor en la secuencia
  NRF_PWM0->SEQ[0].REFRESH = 0;
  NRF_PWM0->SEQ[0].ENDDELAY = 0;

  // 7. Configurar el DECODER (modo individual)
  NRF_PWM0->DECODER = PWM_DECODER_LOAD_Individual;

  // 8. Iniciar el PWM en modo "loop"
  NRF_PWM0->LOOP = PWM_LOOP_CNT_Disabled;  // Repetición infinita
  NRF_PWM0->TASKS_SEQSTART[0] = 1;  // Iniciar PWM
}

void loop() {
  value = analogRead(pinSensor);
  PWMvalue = map(value, 0, 1023, 0, 100);
  Serial.print("Value on ADC is: ");
  Serial.println(value);
  Serial.print("Scalated value (%) on ADC is: ");
  Serial.println(PWMvalue);
  Serial.println();
  set_duty_cycle(PWMvalue);
  delay(2000);

}
