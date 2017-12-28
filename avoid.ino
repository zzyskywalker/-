// 左边Trig接Arduino板的Digital 4口，触发测距；Echo接Digital 3口，接收距离信号。
const int inputPin_1=3; // 定义左超声波信号接收接口
 const int outputPin_1=4; // 定义左超声波信号发出接口
// 右边Trig接Arduino板的Digital 6口，触发测距；Echo接Digital 5口，接收距离信号。
const int inputPin_2=5; // 定义右超声波信号接收接口
const int outputPin_2=6; // 定义右超声波信号发出接口
const int P1=2;//声控模块P0接D2
const int P2=7;//声控模块P1接D7
const int P3=12;//声控模块P2接D12
const int leftgo=9;
const int leftback=8;
const int rightgo=10;
const int rightback=11;
unsigned int dutyCycle;
void Auto()
{
  digitalWrite(outputPin_1, LOW); // 使发出发出超声波信号接口低电平2μs
  delayMicroseconds(2);
  digitalWrite(outputPin_1, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
  delayMicroseconds(10);
  digitalWrite(outputPin_1, LOW); // 保持发出超声波信号接口低电平
  int distance_1 = pulseIn(inputPin_1, HIGH); // 读出脉冲时间
  distance_1= distance_1/58; // 将脉冲时间转化为距离（单位：厘米）
   Serial.print("距离左");
  Serial.println(distance_1); //输出距离值 
  digitalWrite(outputPin_2, LOW); // 使发出发出超声波信号接口低电平2μs
  delayMicroseconds(2);
  digitalWrite(outputPin_2, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
  delayMicroseconds(10);
  digitalWrite(outputPin_2, LOW); // 保持发出超声波信号接口低电平
  int distance_2 = pulseIn(inputPin_2, HIGH); // 读出脉冲时间
  distance_2= distance_2/58; // 将脉冲时间转化为距离（单位：厘米）
  Serial.print("距离右");
  Serial.println(distance_2); //输出距离值 
  if (distance_2 <7&&distance_1 >7)
    Leftgo();
  else if(distance_2 >7&&distance_1 >7)
    Run();
  else if(distance_2 >7&&distance_1 <7)
    Rightgo();
  else
    Stop();
}
void Run()
{
  dutyCycle =50;
  analogWrite(leftgo,dutyCycle);  //产生PWM
  digitalWrite(rightback,LOW);
  analogWrite(rightgo,dutyCycle);
  analogWrite(leftback,LOW);
}
void Leftgo(int time)
{
  dutyCycle =50;
  analogWrite(rightgo,dutyCycle);  //产生PWM
  digitalWrite(rightback,LOW);
  digitalWrite(leftgo,LOW);
  analogWrite(leftback,LOW);
  delay(time);
}
void Leftgo()
{
    dutyCycle =50;
    analogWrite(rightgo,dutyCycle);  //产生PWM
    digitalWrite(rightback,LOW);
    digitalWrite(leftgo,LOW);
    analogWrite(leftback,LOW);
}
void Rightgo(int time)
{
  dutyCycle =50;
  analogWrite(leftgo,dutyCycle);  //产生PWM
  digitalWrite(rightback,LOW);
  digitalWrite(rightgo,LOW);
  digitalWrite(leftback,LOW);
  delay(time);
}
void Rightgo()
{
  dutyCycle =50;
  analogWrite(leftgo,dutyCycle);  //产生PWM
  digitalWrite(rightback,LOW);
  digitalWrite(rightgo,LOW);
  digitalWrite(leftback,LOW);
}
void Stop()
{
  digitalWrite(rightgo,LOW);
  digitalWrite(rightback,LOW);
  digitalWrite(leftgo,LOW);
  digitalWrite(leftback,LOW);
}
void Back()
{
  digitalWrite(rightgo,LOW);
  digitalWrite(rightback,HIGH);
  digitalWrite(leftgo,LOW);
  digitalWrite(leftback,HIGH);
  delay(1000);
}
void setup() 
{
  pinMode(leftgo,OUTPUT); // PIN 8 ( 无 PWM)
  pinMode(leftback,OUTPUT); // PIN 9 (PWM)
  pinMode(rightgo,OUTPUT);// PIN 10 (PWM) 
  pinMode(rightback,OUTPUT);// PIN 11 (PWM)
  pinMode(P1, INPUT);
  pinMode(P2, INPUT);
  pinMode(P3, INPUT);
  Serial.begin(9600);
  pinMode(inputPin_1, INPUT);
  pinMode(outputPin_1, OUTPUT);
  pinMode(inputPin_2, INPUT);
  pinMode(outputPin_2, OUTPUT);
}
void loop() 
{
  int a,b,c,CMD;
  a=digitalRead(P1);
  b=digitalRead(P2);
  c=digitalRead(P3);
  CMD=a*4+b*2+c;
  switch(CMD)
  {
    case 1://停止 001
    Stop();
    Serial.println(CMD);
    break;
    case 2://前进 010
    Run();
    Serial.println(CMD);
    break;
    case 3://后退 011
    {
    Back();
    while(1)
    {
      a=digitalRead(P1);
      b=digitalRead(P2);
      c=digitalRead(P3);
      CMD=a*4+b*2+c;
      Serial.println(CMD);
      if(CMD==3)
        Stop();
      else
        break;
      }
    }
    Serial.println(CMD);
    break;
    case 4://左转后直行 100
    {
    Leftgo(1400);
    while(1)
    { 
      a=digitalRead(P1);
      b=digitalRead(P2);
      c=digitalRead(P3);
      CMD=a*4+b*2+c;
      Serial.println(CMD);
      if(CMD==4)
        Run();
      else
        break;
    }
    break;
    }
    case 5://右转后直行 101
    {
    Rightgo(1400);
    while(1)
    {
      a=digitalRead(P1);
      b=digitalRead(P2);
      c=digitalRead(P3);
      CMD=a*4+b*2+c;
      Serial.println(CMD);
      if(CMD==5)
        Run();
      else
        break;
    }
    break;
  }
    case 6://避障模式 110
    while(1)
    {
      a=digitalRead(P1);
      b=digitalRead(P2);
      c=digitalRead(P3);
      CMD=a*4+b*2+c;
      Serial.println(CMD);
      if(CMD==6)
      Auto();
      else
        break;
    }
    break;
  case 7://退出避障并停止 111
    while(1)
    {
      a=digitalRead(P1);
      b=digitalRead(P2);
      c=digitalRead(P3);
      CMD=a*4+b*2+c;
      Serial.println(CMD);
      if(CMD==7)
      Auto();
      else
        break;
    }

    break;
  }
  }


