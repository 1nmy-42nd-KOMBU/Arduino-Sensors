#include <Wire.h>

#define BNO055 0x28 //9軸センサ　IICアドレス

volatile int RET_MSG;
volatile int DIR;
volatile int GYRO;
volatile int PITCH;
volatile int ROLL;

void setup()
{
  Serial.begin(9600);

  Wire.begin(); //I2C通信開始
  Wire.beginTransmission(BNO055);
  Wire.write(0x3B); //register設定
  Wire.write(0x00);
  RET_MSG = Wire.endTransmission(); // データの送信と終了処理
  if (RET_MSG == 0) {} else {
    Serial.print("ERROR NO.="); //通信出来ない
    Serial.println(RET_MSG);
}

  Wire.beginTransmission(BNO055);
  Wire.write(0x41); //register設定
  Wire.write(0x21);
  Wire.write(0x04);
  RET_MSG = Wire.endTransmission(); // データの送信と終了処理
  if (RET_MSG == 0) {} else {
    Serial.print("ERROR NO.="); //通信出来ない
    Serial.println(RET_MSG);
  }

  Wire.beginTransmission(BNO055);
  Wire.write(0x3D); //register設定
  Wire.write(0x0C);
  RET_MSG = Wire.endTransmission(); // データの送信と終了処理
  if (RET_MSG == 0) {} else {
    Serial.print("ERROR NO.="); //通信出来ない
    Serial.println(RET_MSG);
  }
}

void loop()
{

  GYRO = getGYRO(0);
  Serial.print(GYRO);
  Serial.print("\t");

  PITCH = getPITCH(0);
  Serial.print(PITCH);
  Serial.print("\t");

  ROLL = getROLL(0);
  Serial.println(ROLL);
  delay(1000);

}

unsigned int getDIR(unsigned char) //ヘッドアップ角度を読み込み。
{
  typedef union { //受信データ用共用体
    unsigned int W;
    struct {
    unsigned char L;
    unsigned char H;
    };
  } U_UINT;
  U_UINT data; // 受信データ
  int reg; //レジスターアドレス
  reg = 0x1A; // Register 0x1A:dir(EUL_DATA_X LSB-MSB)
  Wire.beginTransmission(BNO055); //通信開始
  Wire.write(reg); //register
  Wire.endTransmission(); //通信終了

  Wire.requestFrom(BNO055, 2);
  if (Wire.available() > 1) {
    data.L = Wire.read(); //１バイト分のデータの読み込み
    data.H = Wire.read(); //次の１バイト分のデータを読み込み
  }
  data.W = data.W / 16;
  return (data.W);
}

unsigned int getROLL(unsigned char) //ロール角度を読み込み。
{
  typedef union { //受信データ用共用体
    unsigned int W;
    struct {
    unsigned char L;
    unsigned char H;
    };
  } U_UINT;
  U_UINT data; // 受信データ
  int reg; //レジスターアドレス
  reg = 0x1C; // Register 0x1C:ROLL(EUL_DATA_Y LSB-MSB)
  Wire.beginTransmission(BNO055); //通信開始
  Wire.write(reg); //register
  Wire.endTransmission(); //通信終了

  Wire.requestFrom(BNO055, 2);
  if (Wire.available() > 1) {
    data.L = Wire.read(); //１バイト分のデータの読み込み
    data.H = Wire.read(); //次の１バイト分のデータを読み込み
  }
  return (data.W);
}

unsigned int getPITCH(unsigned char) //ピッチ角度を読み込み。
{
    typedef union { //受信データ用共用体
    unsigned int W;
    struct {
    unsigned char L;
    unsigned char H;
    };
  } U_UINT;
  U_UINT data; // 受信データ
  int reg; //レジスターアドレス
  reg = 0x1E; // Register 0x1E:PITCH(LSB-MSB)
  Wire.beginTransmission(BNO055); //通信開始
  Wire.write(reg); //register
  Wire.endTransmission(); //通信終了

  Wire.requestFrom(BNO055, 2);
  if (Wire.available() > 1) {
    data.L = Wire.read(); //１バイト分のデータの読み込み
    data.H = Wire.read(); //次の１バイト分のデータを読み込み
  }
  return (data.W);
}
