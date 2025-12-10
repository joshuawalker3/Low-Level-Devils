#ifndef _SEVEN_SEGMENT_H_
#define _SEVEN_SEGMENT_H_

class SevenSegment {

public:
    SevenSegment(int pin1, int pin2, int pin4, int pin5,
                 int pin6, int pin7, int pin9, int pin10);

    void start();
    void flashOne(int led);
    void flashAll();
    void ledOn(int led);
    void ledOff(int led);
    void display_0();
    void display_1();
    void display_2();
    void display_3();
    void display_4();
    void display_5();
    void display_6();
    void display_7();
    void display_8();
    void display_9();
    void display_a();
    void display_b();
    void display_c();
    void display_d();
    void display_e();
    void display_f();
    void display_g();
    void display_h();
    void display_j();
    void display_l();
    void display_n();
    void display_o();
    void display_p();
    void display_r();
    void display_s();
    void display_u();

private:
    int led_a;
    int led_b;
    int led_c;
    int led_d;
    int led_e;
    int led_f;
    int led_g;
    int led_dp;

};

#endif //_SEVEN_SEGMENT_H_
