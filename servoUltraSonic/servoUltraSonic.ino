// 调用库以及其他头文件
#include "Servo.h"
#include "SR04.h"
#include "setting.h"

// 绑定电机引脚
int carLeftA = 6;
int carLeftB = 11;
int carRightA = 5;
int carRightB = 3;

// 初始化超声波和舵机
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
Servo servoUltraSonic;

void setup()
{
  // 绑定舵机引脚
  servoUltraSonic.attach(9);
  // 延时，方便操作。
  delay(1000);
  /*
  * 根据官方文档，使用analogWrite()函数的引脚，
  * 可以不使用pinMode()进行初始化，所以略去。
  */
}
void loop()
{
  // 声明两个长整形变量，用于存储前方、右方的测距结果。
  long forwardDistance = 0;
  long rightDistance = 0;
  // 调用函数测量前方距离
  forwardDistance = controlServoAndGetDistance(FORWARD);
  if (forwardDistance >= 25)
  {
    // 如果前方距离大于25cm，继续向前走。
    forward();
  }
  else
  {
    // 如果前方距离小于25cm，停车，测量右方距离。
    brake();
    rightDistance = controlServoAndGetDistance(RIGHT);
    if (rightDistance >= 25)
    {
      // 如果右方距离大于25cm，向右转。
      turn(RIGHT);
    }
    else
    {
      // 如果右方距离小于25cm，向左转。
      turn(LEFT);
    }
  }
}
