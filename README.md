Windows-command-line-tools
==========================

Small command line tools for Windows.

Windows のコマンドプロンプトで動作する小さなソフトウェアです。 コマンドプロンプトの使い方がわかる方専用です。

 - Compiled Binary files: <https://skydrive.live.com/redir?resid=FCAD8DC6EA8FBDDF!439>
 - Source files: <https://github.com/higedice/windows-command-line-tools>


sleepsec
--------

Windows XP のコマンドプロンプトに sleep がないので、"sleep.exe" というものが世にあるのをしりつつ自分で書いてみました。単位は秒のみ。世にあるものよりも機能が少ない！

sleep が欲しいと思ったのは、Windows 起動時に、複数のサーバー等チェックのための BAT ファイルを動かしているため。起動時には重い処理がたくさん動くので、それらが完了してから動かしたかったのです。VBS なら数行ですが、この目的だとログオン直後に VBS のインタプリタが動くのは目的に合っていないのではという理由でC言語で書き直してみました。

    Usage: sleepsec [Seconds] [Progress Charactor]


startbg
-------

Windows の起動時に、BATファイルでサーバーのチェックや必ず起動するプログラムの起動を行っています。ところが、これを時間差で行おうと自作した sleepsec と組み合わせても、アプリケーションの起動でバッチが止まってしまいます。

UNIX のシェルのように、最後にアンパサンド（&）を打つとバックグラウンドで実行してくれるわけでもないので、例によって、簡単な VBS でなくC言語で書いてみました。（"start" コマンドを使うと、アプリケーションが起動はするけれど、新しいコマンドプロンプトのウィンドウが開いちゃうんですよね）

    Usage: startbg [command] [options]
    
    This program runs another following Windows execute file in the background like an ampersand (&) is at the end of the command line on UNIX shells.
    
    The called process runs in the current directory.
    So that directory is *ROCKED* while the sub process is running.


rename_files.rb
-------------

コマンドプロンプトから一括で複数ファイルの名前を変更をします。正規表現が使えます。iPhone の写真をドロップボックス経由で PC に取り込んだ後に「写真 」で始まるファイル名を変更するときなどに役立ちます。

Ruby インタプリタが必要ですが、それを同梱した実行ファイルも配布しています。ただし、動作が遅くなります。

    Usage: ruby rename_files.rb PATTERN NEW_STRING <directorys>... <files>...

    This program *CANNOT* UNDO!

    Search for PATTERN in files and each one's name in target directorys and replace to NEW_STRING.
    PATTERN is an extended regular expression.

    Example: ruby rename_files.rb "foto of " "" . path/to/ "foto of 2013-07-12.jpg"


License
--------

The MIT License. 
Read [license.txt](license.txt) or [license,ja.txt](license,ja.txt)


by Higedice (ひげダイス)  2013
 - <http://d.hatena.ne.jp/higedice/> 
 - <http://twitter.com/higedice>

