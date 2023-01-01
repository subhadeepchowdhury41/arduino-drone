#include "Wire.h"
#include <MPU6050_light.h>
#include <SPI.h>
#include <Servo.h>

#define MIN_PULSE 1000
#define MAX_PULSE 2000

#define px 0.5
// #define px 0
#define ix 0
// #define ix 0
#define dx 0.5
// #define dx 5
#define py 1
// #define py 0
#define iy 0
// #define iy 0
// #define dy 5
#define dy 0.4
#define pz 0
#define dz 0

#define thres 1000
#define pid_thres 200
#define pid_p_i_thres 30
#define pid_r_i_thres 30
#define pid_p_d_thres 200
#define pid_r_d_thres 200

#define safety_pin 7
#define on_input 2
#define status_pin 4

volatile int index = 0;
volatile bool receivedone;
char buff[50];

bool on = false;
bool safe = false;

const int v1 = A0;
const int v2 = A1;
const int v3 = A2;
const int v4 = A3;

Servo s1, s2, s3, s4;

unsigned long previousTime = 0;
double currentTime = 0;
double elapsedTime = 0;
double pid_timer = 0;
int timer1 = 0;

float acc_x, acc_y, acc_z;
float gyro_x, gyro_y, gyro_z;

float acc_angle_x, acc_angle_y, acc_angle_z;
float gyro_angle_x, gyro_angle_y, gyro_angle_z;

float acc_error_x, acc_error_y, acc_error_z;
float gyro_error_x, gyro_error_y, gyro_error_z;
int c = 0;

volatile int req_th = 47;
volatile int req_p = 49;
volatile int req_r = 49;
volatile int req_y = 49;

double pid_pitch = 0;
double pitch = 0;
double prev_pitch = 0;

double pid_roll = 0;
double pid_pitch_i = 0;
double pid_pitch_d = 0;
double roll = 0;
double pid_roll_i = 0;
double pid_roll_d = 0;
double prev_roll = 0;

double pid_yaw = 0;
double yaw = 0;
double prev_yaw = 0;

bool isData = false;
int length = 0;
int d_index = 0;

int t1, t2, t3, t4;

void esc_callibration() {
  Serial.println("Sending MAX Pulse");
  s1.writeMicroseconds(MIN_PULSE);
  s2.writeMicroseconds(MIN_PULSE);
  s3.writeMicroseconds(MIN_PULSE);
  s4.writeMicroseconds(MIN_PULSE);

  delay(5000);

  Serial.println("Sending MIN Pulse");
  s1.writeMicroseconds(MIN_PULSE);
  s2.writeMicroseconds(MIN_PULSE);
  s3.writeMicroseconds(MIN_PULSE);
  s4.writeMicroseconds(MIN_PULSE);

}

void imu_begin() {
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  int status = Wire.endTransmission();
  delay(100);
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}
}

void calculate_imu_error() {
  while (c < 200) {
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 6, true);

    acc_x = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    acc_y = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    acc_z = (Wire.read() << 8 | Wire.read()) / 16384.0 ;

    acc_error_x = acc_error_x + ((atan((acc_y) / sqrt(pow((acc_x), 2) + pow((acc_z), 2))) * 180 / PI));
    acc_error_y = acc_error_y + ((atan(-1 * (acc_x) / sqrt(pow((acc_y), 2) + pow((acc_z), 2))) * 180 / PI));

    c++;
  }

  acc_error_x = acc_error_x / 200;
  acc_error_y = acc_error_y / 200;
  c = 0;

  while (c < 200) {
    Wire.beginTransmission(0x68);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 6, true);

    gyro_x = Wire.read() << 8 | Wire.read();
    gyro_y = Wire.read() << 8 | Wire.read();
    gyro_z = Wire.read() << 8 | Wire.read();
    
    gyro_error_x = gyro_error_x + (gyro_x / 131.0);
    gyro_error_y = gyro_error_y + (gyro_y / 131.0);
    gyro_error_z = gyro_error_z + (gyro_z / 131.0);

    c++;
  }

  gyro_error_x = gyro_error_x / 200;
  gyro_error_y = gyro_error_y / 200;
  gyro_error_z = gyro_error_z / 200;

  Serial.print("AccErrorX: ");
  Serial.println(acc_error_x);
  Serial.print("AccErrorY: ");
  Serial.println(acc_error_y);
  Serial.print("GyroErrorX: ");
  Serial.println(gyro_error_x);
  Serial.print("GyroErrorY: ");
  Serial.println(gyro_error_y);
  Serial.print("GyroErrorZ: ");
  Serial.println(gyro_error_z);
}

void update_imu_data() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);

  acc_x = acc_x*0.98 + 0.02*(Wire.read() << 8 | Wire.read()) / 16384.0;
  acc_y = acc_y*0.98 + 0.02*(Wire.read() << 8 | Wire.read()) / 16384.0;
  acc_z = acc_z*0.98 + 0.02*(Wire.read() << 8 | Wire.read()) / 16384.0;
  
  acc_angle_x = 0.92*acc_angle_x + 0.08* ((atan(acc_y / sqrt(pow(acc_x, 2) + pow(acc_z, 2))) * 180 / PI) - acc_error_x);
  acc_angle_y = 0.92*acc_angle_y + 0.08* ((atan(-1 * acc_x / sqrt(pow(acc_y, 2) + pow(acc_z, 2))) * 180 / PI) - acc_error_y);

  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);

  gyro_x = 0.97 * gyro_x + (float(Wire.read() << 8 | Wire.read()) / 131.0 - gyro_error_x) * 0.03;
  gyro_y = 0.97 * gyro_y + (float(Wire.read() << 8 | Wire.read()) / 131.0 - gyro_error_y) * 0.03;
  gyro_z = 0.97 * gyro_z + (float(Wire.read() << 8 | Wire.read()) / 131.0 - gyro_error_z) * 0.03;

  elapsedTime = (millis() - currentTime) / 1000;
  currentTime = millis();

  gyro_angle_x = gyro_angle_x + gyro_x * elapsedTime;
  gyro_angle_y = gyro_angle_y + gyro_y * elapsedTime;
  yaw =  yaw + gyro_z * elapsedTime;

  // Serial.print(elapsedTime);
  // Serial.println(" ");

  // pitch = 0.996 * gyro_angle_x + 0.004 * acc_angle_x;
  // roll = 0.996 * gyro_angle_y + 0.004 * acc_angle_y;

  pitch = 0.96 * gyro_angle_x + 0.04 * acc_angle_x;
  roll = 0.96 * gyro_angle_y + 0.04 * acc_angle_y;

  gyro_angle_x = pitch;
  gyro_angle_y = roll;

  // Serial.print(pitch);
  // Serial.print(" ");
  // Serial.print(roll );
  // Serial.print(" ");
  // Serial.println(yaw);
}

void setup() {
  Serial.begin(9600);

  pinMode(on_input, INPUT);
  pinMode(safety_pin, INPUT);
  pinMode(status_pin, OUTPUT);
  // pinMode(v1, INPUT);
  // pinMode(v2, INPUT);
  // pinMode(v3, INPUT);
  // pinMode(v4, INPUT);
  
  s1.attach(3, MIN_PULSE, MAX_PULSE);
  s2.attach(9, MIN_PULSE, MAX_PULSE);
  s3.attach(5, MIN_PULSE, MAX_PULSE);
  s4.attach(6, MIN_PULSE, MAX_PULSE);

  esc_callibration();

  // while (!on) {
  //   on = digitalRead(on_input);
  // }

  Wire.begin();
  delay(500);
  imu_begin();
  delay(500);
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  calculate_imu_error();
  Serial.println("Done!\n");

  SPCR |= bit(SPE);
  pinMode(MISO, OUTPUT);
  SPI.attachInterrupt();
  receivedone = false;

  prev_pitch = 0;
  prev_roll = 0;
  prev_yaw = 0;

  pid_timer = millis();
}

void loop() {
  // timer1 = millis();

  on = digitalRead(on_input);
  safe = digitalRead(safety_pin);

  // float volt1 = analogRead(v1);
  // float volt2 = analogRead(v2);
  // float volt3 = analogRead(v3);
  // float volt4 = analogRead(v4);

  // Serial.print(volt1); Serial.print(" ");
  // Serial.print(volt2); Serial.print(" ");
  // Serial.print(volt3); Serial.print(" ");
  // Serial.print(volt4); Serial.println(" ");
  
  if (receivedone) {
    buff[index] = 0;
    String s = String(buff);
    // Serial.println(s);
    for (int i = 0; i < s.length(); i++) {
      if (s.charAt(i) == ',') {
        length++;
      }
    }

    if (length == 3 && s.charAt(0) == '<' && s.charAt(s.length()-1) == '>') {
      int l = 0;
      for (int i = 0; i < s.length(); i++) {
      if (s.charAt(i) == '<') {
        isData = true;
      } else if (s.charAt(i) == '>') {
        int d = s.substring(i - l, i).toInt();
        req_y = req_y - d > 30 || req_y - d < - 30 ? req_y : d;
        // req_y = s.substring(i - l, i).toInt();
        isData = false;
        l = 0;
        d_index = 0;
        receivedone = true;
      } else if (isData) {
        if (s.charAt(i) == ',') {
          int d = s.substring(i - l, i).toInt();
          switch (d_index) {
            case 0:
              req_th = req_th - d > 30 || req_th - d < - 30 ? req_th : d;
              // req_th = s.substring(i - l, i).toInt();
              break;
            case 1:
              req_p = req_p - d > 30 || req_p - d < - 30 ? req_p : d;
              // req_p = s.substring(i - l, i).toInt();
              break;
            case 2:
              req_r = req_r - d > 30 || req_r - d < - 30 ? req_r : d;
              // req_r = s.substring(i - l, i).toInt();
              break;
          }
          l = 0;
          d_index++;
        } else {
          l++;
        }
      }
    }}

    // Serial.print(req_th);
    // Serial.print(" ");
    // Serial.print(req_p);
    // Serial.print(" ");
    // Serial.print(req_r);
    // Serial.print(" ");
    // Serial.print(req_y);
    // Serial.println("");
  
    length = 0;
    index = 0;
    receivedone = false;
  }
  
  update_imu_data();

  // Serial.print(gyro_x); Serial.println(" ");

  float now = millis();

  // Serial.print((pitch - prev_pitch) * 1000 / (now - pid_timer)); Serial.println("");

  pid_pitch = px * (pitch - map(req_p, 0, 98, - 30,  30));
  pid_pitch_d =  (dx * (pitch - prev_pitch) * 1000) / (now - pid_timer);
  pid_pitch_i += ix * (pitch - map(req_p, 0, 98, - 30,  30)) * (now - pid_timer);

  pid_roll = py * (roll - map(req_r, 0, 98, - 30,  30));
  pid_roll_d = (dy * (roll - prev_roll) * 1000) / (now - pid_timer);
  pid_roll_i += iy * (roll - map(req_r, 0, 98, - 30,  30)) * (now - pid_timer);

  pid_timer = now;

  pid_yaw = pz * (yaw - map(req_y, 0, 98, - 30,  30));
  // pid_yaw += (dz * (gyro_z) / (now - pid_timer));
  // pid_yaw_i = i * (yaw - prev_yaw) * (now - pid_timer);

  prev_pitch = pitch;
  prev_roll = roll;
  
  pid_pitch_d = pid_pitch_d > pid_p_d_thres ? pid_p_d_thres : pid_pitch_d;
  pid_roll_d = pid_roll_d > pid_r_d_thres ? pid_r_d_thres : pid_roll_d;
  pid_pitch_d = pid_pitch_d < - pid_p_d_thres ? - pid_p_d_thres : pid_pitch_d;
  pid_roll_d = pid_roll_d < - pid_r_d_thres ? - pid_r_d_thres : pid_roll_d;
  
  // pid_pitch_i = pid_pitch_i > pid_p_i_thres ? pid_p_i_thres : pid_pitch_i;
  // pid_roll_i = pid_roll_i > pid_r_i_thres ? pid_r_i_thres : pid_roll_i;
  // pid_pitch_i = pid_pitch_i < - pid_p_i_thres ? - pid_p_i_thres : pid_pitch_i;
  // pid_roll_i = pid_roll_i < - pid_r_i_thres ? - pid_r_i_thres : pid_roll_i;

  pid_pitch += pid_pitch_i + pid_pitch_d;
  pid_roll += pid_roll_i + pid_roll_d;

  t1 = t1 > pid_thres ? pid_thres : t1;
  t1 = t1 < -pid_thres ? -pid_thres : t1;

  t2 = t2 > pid_thres ? pid_thres : t2;
  t2 = t2 < -pid_thres ? -pid_thres : t2;

  t3 = t3 > pid_thres ? pid_thres : t3;
  t3 = t3 < -pid_thres ? -pid_thres : t3;

  t4 = t4 > pid_thres ? pid_thres : t4;
  t4 = t4 < -pid_thres ? -pid_thres : t4;

  t1 = map(req_th, 49, 98, 1000, 1700) + pid_pitch - pid_roll + pid_yaw;
  t2 = map(req_th, 49, 98, 1000, 1700) + pid_pitch + pid_roll - pid_yaw;
  t3 = map(req_th, 49, 98, 1000, 1700) - pid_pitch - pid_roll + pid_yaw;
  t4 = map(req_th, 49, 98, 1000, 1700) - pid_pitch + pid_roll - pid_yaw;

  t1 = t1 > 1900 ? 1900 : t1;
  t2 = t2 > 1900 ? 1900 : t2;
  t3 = t3 > 1900 ? 1900 : t3;
  t4 = t4 > 1900 ? 1900 : t4;

  t1 = on && safe ? t1 : 900;
  t2 = on && safe ? t2 : 900;
  t3 = on && safe ? t3 : 900;
  t4 = on && safe ? t4 : 900;

  s1.writeMicroseconds(t1 < thres ? thres : t1);
  // s1.writeMicroseconds(1000);

  s2.writeMicroseconds(t2 < thres ? thres : t2);
  // s2.writeMicroseconds(1000);

  s3.writeMicroseconds(t3 < thres ? thres : t3);
  // s3.writeMicroseconds(1300);

  s4.writeMicroseconds(t4 < thres ? thres : t4);
  // s4.writeMicroseconds(1000);

  // Serial.print(t1); Serial.print(" ");
  // Serial.print(t2); Serial.print(" ");
  // Serial.print(t3); Serial.print(" ");
  // Serial.print(t4); Serial.println(" ");


  // if (millis() - timer1 >= 10) {
    // Serial.print(" ");
    // Serial.println(millis() - timer1);
  //   timer1 = millis();

  // while(millis() - timer1 < 10) {}
  // }
}

ISR (SPI_STC_vect) {
  uint8_t oldsrg = SREG;
  char c = SPDR;

  if (index < sizeof buff) {
    buff[index++] = c;
    if (c == '>') {
      receivedone = true;
    }
  }
  SREG = oldsrg;
}