WS2822S
============
シリアルフルカラーLED WS2822Sを制御するためのArduino用ライブラリです。
このライブラリはATmega328Pを搭載したArduino用です。
> examples  ----------WS2822Sを使用したサンプルスケッチ
 + LED_bar_10  ------- WS2822Sを10個光らせるサンプルスケッチ
 + addresss_write ------- WS2822Sにアドレスを書き込むサンプルスケッチ
 
> Ws2822s.cpp

> Ws2822s.h

> keywords.txt

*動作確認 Arduino Uno

使い方
=============
初期設定
> 
+ 最初に使用するピンの番号を指定します。
+ サンプルスケッチでは色信号を出すピンを13番、アドレスを書き込むピンを12番としました。
+ 制御するWS2822Sの数を指定します。サンプルスケッチでは10個です。
+ 　　　例：  Ws2822s  LED(13, 12, 10);
+ すでにアドレス設定済みのWS2822Sを制御する場合。アドレス書き込みピンは使用する必要はありません。
+ 　　　例：　Ws2822s  LED(13,10);

アドレス書き込み
> 
+ WS2822Sのアドレスは3ずつ増やす必要があるため、先頭のLEDがアドレス1番なら次は4番、続けて7、10、13、16となります。
+ このライブラリではアドレスの割り当てを単純化して先頭から0、1、2、3、4と割り当てられるようにしてあります。
+ 　　　例： LED.setAddress(0,9); ---- これで先頭から0～9番のアドレスを順番に書き込みます。

色データ送信
>
+ 最初の初期化時にWS2822Sの数で指定しただけの配列が作成されます。
+ その配列に光らせる色を指定します。
+ 　　　例：　LED.setColor(address,R,G,B);
+ 次に色の情報を送信します。
+ 　　　例：  LED.send(); ---- 用意した色のデータを全て送信します。
+ 注意点：　WS2822Sは1秒以内に新しい色のデータを書き続ける必要があります。定期的にsend()を実行して色のデータを送信してください。

