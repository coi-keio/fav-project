NuGetできるxercescの最新(安定版)は[xercesc.3.1.1]ですが，
Windows10環境では[xerces-c-3.1.4]を求められるため，手動
で入手し，./packagesに格納してください．

現在[FavLibrary.Win.vcxproj]では[xerces-c-3.1.4]をリンク
しているため，他のバージョンをリンクする場合はプロジェク
ト設定を変更してください．


実際の手順
1. xerces-c-3.1.4のソースコードを取得する
https://archive.apache.org/dist/xerces/c/3/sources/

2. xerces-c-3.1.4.zipを展開し，
./xerces-c-3.1.4/xerces-c-3.1.4/projects/Win32/VC14/xerces-all
内のプロジェクトをvisual studioで開く

3. x64, Debug/Releaseモードでコンパイルする

4. 生成されたフォルダ（xerces-c-3.1.4/xerces-c-3.1.4/Build)を
fav-project/FavLibrary/FavLibrary.Win/packages/xerces-c-3.1.4/
フォルダ内にコピーする

5. ./fav-project/FavLibrary/FavLibrary.Win/FavLibrary.Win.sln
ファイルをvisual studioで開いてコンパイルする
