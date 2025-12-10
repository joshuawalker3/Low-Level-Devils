#include "SevenSegment.h"
#include "Arduino.h"


SevenSegment::SevenSegment(int pin1, int pin2, int pin4, int pin5,
                           int pin6, int pin7, int pin9, int pin10) {
    led_a = pin7;
    led_b = pin6;
    led_c = pin4;
    led_d = pin2;
    led_e = pin1;
    led_f = pin9;
    led_g = pin10;
    led_dp = pin5;
}

void SevenSegment::start() {
    flashOne(led_a);
    flashOne(led_b);
    flashOne(led_c);
    flashOne(led_d);
    flashOne(led_e);
    flashOne(led_f);
    flashOne(led_g);
    flashOne(led_dp);
    flashAll();
}

void SevenSegment::flashOne(int led) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
}

void SevenSegment::flashAll() {
    digitalWrite(this->led_a, HIGH);
    digitalWrite(this->led_b, HIGH);
    digitalWrite(this->led_c, HIGH);
    digitalWrite(this->led_d, HIGH);
    digitalWrite(this->led_e, HIGH);
    digitalWrite(this->led_f, HIGH);
    digitalWrite(this->led_g, HIGH);
    digitalWrite(this->led_dp, HIGH);
    delay(500);
    digitalWrite(this->led_a, LOW);
    digitalWrite(this->led_b, LOW);
    digitalWrite(this->led_c, LOW);
    digitalWrite(this->led_d, LOW);
    digitalWrite(this->led_e, LOW);
    digitalWrite(this->led_f, LOW);
    digitalWrite(this->led_g, LOW);
    digitalWrite(this->led_dp, LOW);
}

void SevenSegment::ledOn(int led) {
    digitalWrite(led, HIGH);
}

void SevenSegment::ledOff(int led) {
    digitalWrite(led, LOW);
}

void SevenSegment::display_0() {
    ledOn(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOff(led_g);
}
void SevenSegment::display_1() {
    ledOff(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOff(led_d);
    ledOff(led_e);
    ledOff(led_f);
    ledOff(led_g);
}

void SevenSegment::display_2() {
    ledOn(led_a);
    ledOn(led_b);
    ledOff(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOff(led_f);
    ledOn(led_g);
}

void SevenSegment::display_3() {
    ledOn(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOff(led_e);
    ledOff(led_f);
    ledOn(led_g);
}

void SevenSegment::display_4() {
    ledOff(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOff(led_d);
    ledOff(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_5() {
    ledOn(led_a);
    ledOff(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOff(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_6() {
    ledOn(led_a);
    ledOff(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_7() {
    ledOn(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOff(led_d);
    ledOff(led_e);
    ledOff(led_f);
    ledOff(led_g);
}

void SevenSegment::display_8() {
    ledOn(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_9() {
    ledOn(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOff(led_d);
    ledOff(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_a() {
    ledOn(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOff(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_b() {
    ledOff(led_a);
    ledOff(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_c() {
    ledOn(led_a);
    ledOff(led_b);
    ledOff(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOff(led_g);
}

void SevenSegment::display_d() {
    ledOff(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOff(led_f);
    ledOn(led_g);
}

void SevenSegment::display_e() {
    ledOn(led_a);
    ledOn(led_b);
    ledOff(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_f() {
    ledOn(led_a);
    ledOff(led_b);
    ledOff(led_c);
    ledOff(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_g() {
    ledOn(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOff(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_h() {
    ledOff(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOff(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_j() {
    ledOff(led_a);
    ledOn(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOff(led_f);
    ledOff(led_g);
}

void SevenSegment::display_l() {
    ledOff(led_a);
    ledOff(led_b);
    ledOff(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOff(led_g);
}

void SevenSegment::display_n() {
    ledOff(led_a);
    ledOff(led_b);
    ledOn(led_c);
    ledOff(led_d);
    ledOn(led_e);
    ledOff(led_f);
    ledOn(led_g);
}

void SevenSegment::display_o() {
    ledOff(led_a);
    ledOff(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOff(led_f);
    ledOn(led_g);
}

void SevenSegment::display_p() {
    ledOn(led_a);
    ledOn(led_b);
    ledOff(led_c);
    ledOff(led_d);
    ledOn(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_r() {
    ledOff(led_a);
    ledOff(led_b);
    ledOff(led_c);
    ledOff(led_d);
    ledOn(led_e);
    ledOff(led_f);
    ledOn(led_g);
}

void SevenSegment::display_s() {
    ledOn(led_a);
    ledOff(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOff(led_e);
    ledOn(led_f);
    ledOn(led_g);
}

void SevenSegment::display_u() {
    ledOff(led_a);
    ledOff(led_b);
    ledOn(led_c);
    ledOn(led_d);
    ledOn(led_e);
    ledOff(led_f);
    ledOff(led_g);
}