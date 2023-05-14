#include <Servo.h>

// The limits of rotation we can obtain from servo
#define MAX_DEGREE 160
#define MIN_DEGREE 20
#define TOLERANCE 2

// Pin definition
// For servo (must be PWM)
#define PIN_AXIS_A 9
#define PIN_AXIS_B 10

// For LDR
#define PIN_A A1
#define PIN_B A3
#define PIN_C A4
#define PIN_D A2

// Global variables
Servo servo_axis_a;
int voltage_a = 0;
int voltage_b = 0;
int voltage_c = 0;
int voltage_d = 0;
int position = 30;
int ad = 0;
int ab = 0;
int bc = 0;
int cd = 0;

int axis_a_current_position;
int axis_b_current_position;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_AXIS_A, OUTPUT);
  pinMode(PIN_AXIS_B, OUTPUT);
  
  servo_axis_a.attach(PIN_AXIS_A);
  delay(500);
}

void loop() {
  voltage_a = analogRead(PIN_A);
  voltage_b = analogRead(PIN_B);
  voltage_c = analogRead(PIN_C);
  voltage_d = analogRead(PIN_D);

  ad = (voltage_a + voltage_d)/2;
  ab = (voltage_a + voltage_b)/2;
  bc = (voltage_b + voltage_c)/2;
  cd = (voltage_c + voltage_d)/2;

  axis_a_current_position = servo_axis_a.read();
  axis_b_current_position = servo_axis_b.read();

  // First axis
  
  if ( ad > bc + TOLERANCE && axis_a_current_position > MIN_DEGREE) {
    servo_axis_a.write(axis_a_current_position -1);
  } else if(bc > ad + TOLERANCE && axis_a_current_position < MAX_DEGREE) {
    servo_axis_a.write(axis_a_current_position + 1);
  }

  // Second axis

  if ( ab > cd + TOLERANCE && axis_b_current_position > MIN_DEGREE) {
    servo_axis_a.write(axis_b_current_position -1);
  } else if(cd > ab + TOLERANCE && axis_b_current_position < MAX_DEGREE) {
    servo_axis_a.write(axis_b_current_position + 1);
  }

  delay(100);
}
