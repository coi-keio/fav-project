# fav-project

慶應義塾大学が富士ゼロックス株式会社と共同で研究開発している3Dプリンタ向けデータフォーマット「FAV」を使用するためのライブラリです。

FAVフォーマットの詳細については、富士ゼロックスのウェブサイトをご覧ください。

- [3Dデータフォーマット「FAV（ファブ）」](https://www.fujixerox.co.jp/company/technical/communication/3d/fav.html)

## 開発環境

Docker仮想環境の起動

```shell
$ cd docker
$ docker build ./ -t fav-project
$ ./docker_run.sh fav-project
```

ビルド（仮想環境にログインしてからビルドする）

```shell
$ cd /usr/local/fav/FavLibrary/buildLib
$ mkdir build
$ cd build
$ cmake ..
$ make
```

テスト

```shell
$ cd /usr/local/fav/FavLibrary/buildTest
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./a.out
```
