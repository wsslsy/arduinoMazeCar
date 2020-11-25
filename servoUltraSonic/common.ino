// 该文件包含一些常用控制函数

/*
 * @函数名：void speedControl(int side, int dir)；
 * @参数：side 可选参数：LEFT / RIGHT
 *       dir  可选参数：FORWARD / BACK / STOP
 * @备注："MISTAKE"参数用来微调两个电机的速度，
 *        例子中右轮较慢，因此在给右轮赋值时多加了5，
 *        该数值应根据实际进行适当调节。
 */
#define MISTAKE 5
void speedControl(int side, int dir)
{
  int A, B;
  int s;
  if (LEFT == side)
  {
    A = carLeftA;
    B = carLeftB;
    s = SPEED;
  }
  else if (RIGHT == side)
  {
    A = carRightA;
    B = carRightB;
    s = SPEED + MISTAKE;
  }
  if (FORWARD == dir)
  {
    analogWrite(A, s);
    analogWrite(B, 0);
  }
  else if (BACK == dir)
  {
    analogWrite(A, 0);
    analogWrite(B, s);
  }
  else if (STOP == dir)
  {
    analogWrite(A, 0);
    analogWrite(B, 0);
  }
}
/*
 * @函数名：void turn(int dir)；
 * @参数：dir 可选参数：LEFT / RIGHT
 * @备注："TURN_TIME"参数用来调节单次转向的延时时间，
 *        已用于精确控制专项角度为90度，
 *        例子中使用450ms，需要根据实际进行微调。
 */
#define TURN_TIME 450
void turn(int dir)
{
  if (LEFT == dir)
  {
    speedControl(RIGHT, FORWARD);
    speedControl(LEFT, BACK);
    delay(TURN_TIME);
    brake();
  }
  else if (RIGHT == dir)
  {
    speedControl(LEFT, FORWARD);
    speedControl(RIGHT, BACK);
    delay(TURN_TIME);
    brake();
  }
  else
  {
    // do nothing
  }
}
/*
 * @函数名：brake()；
 * @参数：无
 * @备注：封装停车函数，便于调用。
 */
void brake()
{
  speedControl(LEFT, STOP);
  speedControl(RIGHT, STOP);
}
/*
 * @函数名：forward()；
 * @参数：无
 * @备注：封装前进函数，便于调用。
 */
void forward()
{
  speedControl(RIGHT, FORWARD);
  speedControl(LEFT, FORWARD);
}
/*
 * @函数名：backward()；
 * @参数：无
 * @备注：封装后退函数，便于调用，此项目中未用到。
 */
void backward()
{
  speedControl(RIGHT, BACK);
  speedControl(LEFT, BACK);
}
/*
 * @函数名：long controlServoAndGetDistance(int dir)；
 * @参数：dir  可选参数：FORWARD / LEFT / RIGHT
 * @返回值：长整形 测距均值
 * @备注："dir"参数给定后，会将舵机转至指定角度，
 *        例子中，舵机对中值为97，
 *        向左为180，向右为19，
 *        应根据实际情况进行微调。
 *        例子中，LEFT方向没有用到。
 */
long controlServoAndGetDistance(int dir)
{
  long disAvg = 999;
  if (FORWARD == dir)
  {
    servoUltraSonic.write(97);
  }
  else if (LEFT == dir)
  {
    servoUltraSonic.write(180);
  }
  else if (RIGHT == dir)
  {
    servoUltraSonic.write(19);
  }
  else
  {
    // do nothing
  }
  // 该延时的作用为，等待舵机转向完成。
  delay(500);
  // 调用SR04库的平均值采样方法。该方法每间隔25ms采样5次，去最大最小值，取平均值。
  disAvg = sr04.DistanceAvg(25, 5);
  return disAvg;
}
