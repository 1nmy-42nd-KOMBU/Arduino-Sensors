
# ライントレースにEV3 Sensor Multiplexerは使えるのか

初めにMUX(EV3 Sensor Multiplexer)を介してカラーセンサーの反射光モードの値を取得し、通信が成功したかの情報とともにEV3で表示します。
これを10秒間繰り替えし、最後に実行された回数を表示します。
![image.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/2449798/a86a7046-6962-9e9d-4f73-b821ddefec65.png)
<img width="400" alt="ファイル名" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/2449798/ae2d0b8c-65d4-f6dd-24ff-b0fda8093031.png">

``594times``と表示されました。ですが、何回か試してみると回数が安定しません。また、実行中、通信に失敗したことを示すエラーが多かったのも気になります。

<img width="400" alt=".JPG" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/2449798/8d35ddf6-72f0-a3dd-7876-886a5dd01bc0.jpeg">

値の取得が要求に追い付いていないのではないかと思い0.1sの遅延を追加してみました。

![image.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/2449798/2d9fc2d2-3d07-d4b0-e5b6-47742f710e1a.png)
<img width="400" alt="ファイル名" src="https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/2449798/695654cf-9ff5-844d-f29f-98be416ffc6a.png">

結果、**70times**で安定しました。また通信にも成功しているようです。

また、遅延は0.005sだとエラーが出ませんが0.001sだとちょくちょくエラーが出ます。

---

次に、カラーセンサーを直接EV3に接続して同様の検証をします。
![image.png](https://qiita-image-store.s3.ap-northeast-1.amazonaws.com/0/2449798/ecd567ff-51cc-f818-61b5-7ab15db7ad98.png)
結果は**98times**。そこまで差がない?と思いましたが遅延0.1sは少し過剰すぎる気がしたので0.005sで再検証してみるとセンサーを直接接続した場合が**1250times**、MUXを使った場合が**205times**。大きく差が出ましたね。

元の実行時間から遅延分の時間を除いて、残りの時間を実行回数で割る(例:t(s)の間d(s)の遅延でc回実行の場合は$(t - c \times d) \div c $)と、遅延を除いてセンサーが1回値を得るのに使った周期が求められます。
MUXを使った場合は0.04s程度であるのに対して、センサーを直接EV3に接続した場合は0.002s～0.003sと10倍以上の差が出ました。
これをHzに直すとMUXを使った場合が約**25Hz**、センサーを直接EV3に接続した場合が**500～333Hz**前後となります。(仕様書上のサンプリングレートが1000Hz)

※この式でセンサーのサンプリングレートを正しく評価することはできませんが、あくまでも目安として使っています。また遅延を変えての試行回数も少ないです。

---

MUXを使うことでサンプリングレートが大きく下がることが確認できました。ライントレースは制御周期を1msでも早くしようとする世界なので、[ヤフー知恵袋](https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q14204940404)の通りメインのラインセンサーにMUXを使うことは控えるべきでしょう。
