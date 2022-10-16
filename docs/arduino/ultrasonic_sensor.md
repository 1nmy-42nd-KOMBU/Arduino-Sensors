# ultrasonic_sensor
## 実行内容
引数で指示された超音波センサーの値(cm)をint型で返す

## 引数
`(char pingPort,char pingPin)`
* 第一引数 => ピン番号
* 第二引数 => ピン名

[参照](https://ht-deko.com/arduino/portregisters.html)

## ポート
D10とD9ポートのみ使用可能

## 周期
パルスが壁に当たって返ってくるまでの時間に依存する  
例: T=壁までの距離÷音の速さ×2+他の処理にかかる時間(1ms未満)

## 備考
パルス周りの処理を実行している間は`noInterrupts()`で割り込みを禁止している