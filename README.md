# FAV Library

慶應義塾大学が富士ゼロックス株式会社と共同で研究開発している3Dプリンタ向けデータフォーマット「FAV」を使用するためのライブラリです。

FAVフォーマットの詳細については、富士ゼロックスのウェブサイト[3Dデータフォーマット「FAV（ファブ）」](https://www.fujixerox.co.jp/company/technical/communication/3d/fav.html)をご覧ください。

## 環境構築

### 必要環境

[Xercesc (XML parser)](https://xerces.apache.org/)

### Windows 環境での注意点 (FavLibrary.Win.sln を使用する場合)

NuGet 経由でも「xercesc」を取得できますが、Windows や VisualStudio のバージョンが異なると、要求される xercesc バージョンも異なり、不整合が起きる場合があります。
そのため、上記 URL からお使いの環境に適する xercesc バージョンを取得のうえ、ビルド・配置・プロジェクト設定を行ってください。

## 使用方法

詳細な解説は`FAV_Library_Usage.pdf`をご覧ください。

### FavLibrary の include

お使いの環境の構成に合わせて、`Fav.h`を include します。
FavLibrary は namespace FavLibrary で定義されているため、using 宣言をしてください。

```cpp
#include "YourEnvironment/FavLibrary/Fav.h"
using namespace FavLibrary;
```

### FAVファイルの読み書き

1. 正しいFAVファイルのパスを指定します
2. 書き出し先のFAVファイルパスを指定します

```cpp
Fav fav;
fav.read("path/to/file.fav");  // 1
fav.write("destination/file/path.fav", FavLibrary::Compression::base64);  // 2
```

1番では読み込むFAVファイルパスを指定します。読み込み時に、FAVファイルフォーマットのスキーマによってバリデーションが行われます。

2番では書き込むFAVファイルパスと、圧縮方法を指定します。FAVファイル内の`voxel_map.layer, color_map.layer`のみ指定の方法で圧縮されます。それ以外は圧縮されません。

[Example](FavLibrary/buildTest/testDLL.cpp)

### FAVファイルの新規作成

```cpp
#include <iostream>
#include "Fav.h"

using namespace FavLibrary;

// ボクセルデータ
int voxelSource[4][4][4] = {
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 1, 1, 0},
    },
    {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 1, 1, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    }
};


int main(int argc, const char * argv[]) {

    Fav fav;

    // Metadataの保存
    fav.setMetadataId("2019-11-18");
    fav.setMetadataAuthor("Takumi Moriya");
    fav.setMetadataTitle("Sample data");
    fav.setMetadataLicense("MIT");
    fav.setMetadataNote("This file is created by testWriter.cpp");

    // FAVデータで使用する Geometry (geometry1) を定義し、fav の palette に geometry1 を登録
    Geometry geometry1 = Geometry(1, "geometry1");
    geometry1.setScale(1, 1, 1);
    geometry1.setShape(GeometryShape::cube);
    fav.palette.addGeometry(geometry1);

    // FAVデータで使用する Material (material1) を定義し、fav の palette に material1 を登録
    Material material1 = Material(1, "material1");
    material1.addMaterialName("soft_mat1");
    material1.addIsoStandard("ISO 1043-1:2006 ABS");
    fav.palette.addMaterial(material1);

    // 三次元形状の構成要素となる Voxel (voxel1) を定義し、fav に voxel1 を登録
    Voxel voxel1 = Voxel(1, "voxel1");
    voxel1.addMaterialInfo(material1.getId(), 1.0);
    voxel1.setGeometryInfo(GeometryInfo(geometry1.getId()));
    fav.addVoxel(voxel1);

    // 三次元形状を構成する Voxel を配置するための Grid (grid1) を定義
    Grid grid1 = Grid();
    grid1.setUnit(1, 1, 1);
    grid1.setOrigin(0, 0, 0);
    grid1.setDimension(4, 4, 4);

    // Voxelで構成される三次元形状の実態となる Structure クラスのインスタンス (structure1) を生成し、初期化
    Structure structure1 = Structure();
    structure1.setBitPerVoxel(BitPerVoxel::Bit8);
    structure1.setGridPointer(&grid1);
    structure1.initVoxelMap();

    // ボクセルに色を指定したい場合、色の記述方法 (ColorMode) を指定して ColorMap を初期化
    structure1.initColorMap(ColorMode::RGB);

    for (int z = 0; z < grid1.getDimensionZ(); z++) {
        for (int y = 0; y < grid1.getDimensionY(); y++) {
            for (int x = 0; x < grid1.getDimensionX(); x++) {
                if (voxelSource[z][y][x] != 0) {
                    // 現在の Grid 位置にボクセルを配置する際には、fav に登録済みの Voxel の ID を指定
                    structure1.setVoxel(x, y, z, voxel1.getId());

                    // 配置したボクセルに色を指定したい場合
                    // ボクセルを配置したのと同じ Grid 位置に、先に指定した色の記述方法(ColorMode)に従って色を指定
                    ColorRGB rgb = ColorRGB(1, 1, 1);
                    structure1.setColor(x, y, z, rgb);
                } else {
                    // 現在の Grid 位置にボクセルが存在しない場合には、0を指定
                    structure1.setVoxel(x, y, z, 0);
                }
            }
        }
    }

    // 実際のFAVデータを表す Object のインスタンス (object1) を生成し、
    // Voxelを配置する Grid (grid1) と、実際に Voxel を配置した Structure (structure1) を登録
    Object object1 = Object(1, "object1");
    object1.grid = grid1;
    object1.structure = structure1;
    fav.addObject(object1);

    // fav書き出し
    // fav.write("sample.fav", CompressionMode::base64);
    fav.write("sample.fav", CompressionMode::none);
    return 0;
}
```

[Example](FavLibrary/buildTest/testWriter.cpp)

## 開発環境

Docker仮想環境の起動

```shell
$ cd docker
$ docker build ./ -t fav-project  # イメージのビルド
$ ./docker_run.sh fav-project  # 起動
```

ビルド（仮想環境にログインしてからビルドする）

```shell
$ cd /usr/local/fav/FavLibrary/buildLib
$ mkdir build
$ cd build
$ cmake ..
$ make
```

テスト実行（こちらも仮想環境にログインしてから）

```shell
$ cd /usr/local/fav/FavLibrary/buildTest
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./a.out  # 読み書き
$ ./reader  # 読み込み
$ ./writer  # 書き込み
```
