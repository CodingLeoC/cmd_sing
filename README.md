﻿(Japanese, UTF-8)

# cmd_sing by 片山博文MZ

## 概要

古いパソコン PC-8801 の N88-BASIC というプログラム言語の `CMD SING` 文を現代の Windows パソコンでエミュレート（再現）するプログラムです。

## 使い方

```txt
使い方: cmd_sing [オプション] 文字列

オプション:
  -D変数名=値            変数に代入。
  -save_wav 出力.wav     WAVファイルとして保存。
  -reset                 設定をリセット。
  -help                  このメッセージを表示する。
  -version               バージョン情報を表示する。

文字列変数は、{変数名} で展開できます。
```

## `CMD SING`文 (8801のみ) (タートル拡張) {#cmd_sing}

- 【機能】 音楽を演奏します。
- 【語源】 Command sing
- 【書式】 `CMD SING` *サブコマンド文字列*
- 【文例】 `CMD SING "CDE"`　⇒　ドレミを演奏
- 【説明】 *サブコマンド文字列*で指定されたメロディーを演奏します。*サブコマンド文字列*は、ミュージックサブコマンドを並べた文字列です。ミュージックサブコマンドには、テンポ、オクターブ、長さ、音符、休符などを指定できます。ミュージックサブコマンドは文字と引数で指定します。引数は数字か変数名で指定できます。たとえば、テンポを`120`にしたい場合は、次の２とおりの方法があります。

    CMD SING "T120"

    tempo=120:CMD SING "T(tempo)"

- ミュージックサブコマンドの文法は次のとおりです。

|記号                 |条件      |説明                                                                                                                                                          |
|:--------------------|:---------|:-------------------------------------------------------------------------------------------------------------------------------------------------------------|
|`Tn`                 |48≦n≦255|  テンポを設定します。1分間に演奏する４分音符の数をnで指定します。                                                                                            |
|`On`                 |3≦n≦6   |  オクターブを設定します。                                                                                                                                    |
|`Ln`                 |1≦n≦32  |  音符・休符の長さの既定値を設定します。全音符の場合はn＝1、四分音符の場合はn＝4となります。                                                                  |
|`R[n][.]`            |1≦n≦32  |  休符を演奏します。nの値で長さを指定します。`.`は符点を表します。                                                                                            |
|`C`～`B[+/-][n][.]`  |1≦n≦32  |  音符を演奏します。nの値で長さを指定します。`.`は符点を表します。`+/-`でシャープかフラットを指定できます。`CDEFGAB`はそれぞれドレミファソラシに対応します。  |
|`Xn`                 |n＝0,1    |  [テキスト画面](#text_screen)の表示を制御します。0で[テキスト画面](#text_screen)を消し、`1`で表示します。                                                    |
|`RPj[...]`           |1≦j≦255 |  `[` `]`の中身を`j`回繰り返します。入れ子は8レベルまでです。                                                                                                 |

- 【注意】 `CMD SING`文はタートル拡張命令であり、8801のみで使用できます(無制限モードを除く)。`CMD SING`を使用する前に`BLOAD "@exst*v2"`か`BLOAD "@exst"`を実行する必要があります(無制限モードを除く)。古い機種では[テキスト画面](#text_screen)を消さずに演奏すると、聞きづらくなりますので、[テキスト画面](#text_screen)を`X0`か[`CMD TEXT OFF`](#cmd_text_on_off)で表示を切り替えることをおすすめします。255文字を越える長さの文字列を指定すると、`String too long`エラーが発生します(無制限モードを除く)。

## 注意

- `X` サブコマンドには対応しておりません。

## 使用許諾

- 本ソフトウェアの使用においては、LICENSE.txtに記載されている「fmgon ライセンス」の使用条件に従ってください。

## 連絡先

- 片山博文MZ <katayama.hirofumi.mz@gmail.com>
