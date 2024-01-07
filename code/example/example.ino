const int pwmPin[4] = {26,13,25,21};// 绑定IO 26对应1号位 13对应2号口  25对应3号位 21对应4号口
int resolution[4] = {8,8,8,8}; //频率的分辨率，这里不用修改
int ch[4] = {1, 6, 2, 3};// 舵机通道
int Freq = 108000 ; //喷雾片谐振频率
int freq[4] = {Freq, Freq, Freq, Freq};                                                                           

void setup() {

  Serial.begin(115200);

  ledcSetup(ch[0], freq[0], resolution[0]); // 设置舵机通道
  ledcSetup(ch[1], freq[1], resolution[1]);
  ledcSetup(ch[2], freq[2], resolution[2]);
  ledcSetup(ch[3], freq[3], resolution[3]);

  ledcAttachPin(pwmPin[0], ch[0]);  //将 LEDC 通道绑定到指定 IO 口上以实现输出
  ledcAttachPin(pwmPin[1], ch[1]);

  ledcAttachPin(pwmPin[2], ch[2]);

  ledcAttachPin(pwmPin[3], ch[3]);

  Serial.println("E-Scent Coach");

}

void loop() {
  
//逐渐增强效果
  for(int i = 1; i<35; i++){
    if(i<15){
      ledcWrite(ch[0], i);//1号口。喷雾片在0-128会逐渐加强，128之后会突然停止。
      ledcWrite(ch[2], i);//3号口
      delay(200);//在15之前喷雾不明显，延长喷雾时间
    }
    else if(i>=15&&i<25){
      ledcWrite(ch[0], i);
      ledcWrite(ch[2], i);
      delay(250);//延长喷雾时间
    }
    else{
      ledcWrite(ch[0], i);
      ledcWrite(ch[2], i);
      delay(100);//在25-35之间区别不大，缩短喷雾时间
    }

  }

}

void readSerial(){
    // ledcWrite(ch[0], 50);
    // delay(500);
  int data = 0;
  if (Serial.available()) {
  // 读取串口缓冲区中的下一个字符
  data = Serial.read();
  // 发送读取到的数据回计算机
  //Serial.write(data);
  }
  if(data == '1'){
  ledcWrite(ch[0], 25);
  ledcWrite(ch[2], 25);
  Serial.println(1);
  delay(500);
  }
  else if (data == '2'){
  ledcWrite(ch[0], 35);
  //ledcWrite(ch[2], 35);
  Serial.println(2);
  delay(500);
  }
  else if (data == '3'){
  ledcWrite(ch[0], 45);
  //ledcWrite(ch[2], 45);
  Serial.println(3);
  delay(500);
  }
  else if (data == '4'){
  ledcWrite(ch[0], 128);
  //ledcWrite(ch[2], 128);
  Serial.println(4);
  delay(500);
  }
  else if (data == '0'){
  ledcWrite(ch[0], 0);
  //ledcWrite(ch[2], 0);
  Serial.println(0);
  delay(500);
  }
}
