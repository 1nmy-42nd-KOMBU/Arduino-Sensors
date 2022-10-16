# loop
## 実行内容
一般的なC言語におけるmain()に近い立ち位置
EV3から{3,…}が送られていて、Bool型の変数`ready_sensor_values`がfalseのときにEV3に指定されたセンサーの値を読み込む  
1度実行されると`ready_sensor_values`がtrueに変更されるので2回続けて実行されることはない  
onRequest関数でEV3にセンサーの値を送信すると、`ready_sensor_values`が再びfalseに変更されセンサーの値を読み込む
onReceive関数で{3,…}を受け取った際にもfalseに変更される(最新の値を取得するため)

## ready_sensor_values
Bool型  
初期値: false  
センサーの値の更新が行われたかを示す  

## ややこしいことをする目的
onRequest関数とonReceive関数は割り込み処理であるためタイミングによっては誤作動を引き起こす可能性がある。
EV3がArduinoに値を要求する周期をArduinoでセンサーの値を処理する周期よりも長くすることで、確実に値を更新するようにしている。

## 周期
超音波センサーに依存する 最長で50ms前後