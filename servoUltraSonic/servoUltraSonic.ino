#include "Servo.h"
#include "SR04.h"
#include "setting.h"
      //调用库以及其他头文件
int carLeftA = 6;
int carLeftB = 11;
int carRightA = 5;
int carRightB = 3;
      //绑定电机引脚
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
Servo servoUltraSonic;
      //初始化超声波和舵机
void setup() {
  servoUltraSonic.attach(9);
      //绑定舵机引脚
  delay(1000);
      //延时，方便操作。
/*
 * 根据官方文档，使用analogWrite()函数的引脚，
 * 可以不使用pinMode()进行初始化，所以略去。
 */
}
void loop() {
  long forwardDistance = 0;
  long rightDistance = 0;
      //声明两个长整形变量，用于存储前方、右方的测距结果。
  forwardDistance = controlServoAndGetDistance(FORWARD);  
      //调用函数测量前方距离
  if(forwardDistance >= 25){
    forward();
      //如果前方距离大于25cm，继续向前走。
  }else{
    brake();
    rightDistance = controlServoAndGetDistance(RIGHT);
      //如果前方距离小于25cm，停车，测量右方距离。
    if(rightDistance >= 25){
      turn(RIGHT);
      //如果右方距离大于25cm，向右转。
    }else{
      turn(LEFT);
      //如果右方距离小于25cm，向左转。
    }
  }  
}


