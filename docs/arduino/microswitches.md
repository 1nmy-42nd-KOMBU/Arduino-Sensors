# microswitches
## 実行内容
2つのマイクロスイッチの状態(0or1)をbyte型のグローバル変数`microswitches_condition`を介して返す

## 引数
なし

## 返り値
`microswitches_condition`の2要素にはD12=>D11の順で結果が入っている

## ポート
D11とD12を使用

## 備考
レジスタを操作しているため高速化されている。  
onRequest関数内で使うことができるが、他センサーとの併用には注意