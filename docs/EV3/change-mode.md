# Arduinoのモードを変更する
モードごとの内容[参照](https://docs.google.com/spreadsheets/d/1WJhSWleOLEynmB5vheJFunxQu6BkRgz2Rvdan5Di-zE/edit?usp=sharing)

## 確認
返ってくる8バイトの内1バイト目は命令の2バイト目(センサーのモード番号)になっている。それが変更されたかを確認し、されていなかった場合は再度変更する。