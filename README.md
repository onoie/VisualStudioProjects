# VisualStudioProjects


## VC2013(JP)
1. VC++.win32プロジェクト,ソリューションのディレクトリ作成:unckeck  
2. Windowsアプリケーション,空のプロジェクト  

### すべての構成
* 構成プロパティ.文字セット.マルチバイト文字セットを使用する
* 構成プロパティ.VC++ディレクトリ.インクルードディレクトリ:Dxlib.Dirctory
* 構成プロパティ.リンカー.全般.追加のライブラリディレクトリ.:Dxlib.Dirctory

### Release
* リンカー.詳細設定.安全な例外ハンドラーを含むイメージ:いいえ
* C/C++.コード生成.ランタイムライブラリ:マルチスレッド(/MIT)

### Debug
* C/C++.コード生成.ランタイムライブラリ:マルチスレッドデバッグ(/MTd)

##### main.cpp

```
#include <DxLib.h>
int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC ,int nC){
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1){
		return 1;
	}
	DrawBox(0, 0, 120, 120, 0x00FFF, TRUE);
	WaitKey();
	DxLib_End();
	return 0;
}
```