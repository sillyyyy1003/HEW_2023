#include "Assets.h"
#include <locale.h>

ID3D11ShaderResourceView* Assets::debugFont;

Assets::Assets()
{
    //===========ここからでテクスチャファイルを追加=============//
    //要注意!! 「L」いりません

    testObj = LoadTexture("assets/Tree.png");
    testShadow = LoadTexture("assets/treeshadow.png");

    testWallbg = LoadTexture("assets/wallbg.png");
    testGroundbg = LoadTexture("assets/groundbg.png");
    testChara01 = LoadTexture("assets/char01.png");

    testWall = LoadTexture("assets/img/Background.png");
    testGround = LoadTexture("assets/img/Ground.png");

    debugFont = LoadTexture("assets/img/ASCIILib.png");

}

Assets::~Assets()
{
   SAFE_RELEASE(testObj);
   SAFE_RELEASE(testShadow);

   SAFE_RELEASE(testWallbg);	
   SAFE_RELEASE(testGroundbg);	
   SAFE_RELEASE(testChara01);	

   SAFE_RELEASE(testWall);
   SAFE_RELEASE(testGround);

   SAFE_RELEASE(debugFont);
}

ID3D11ShaderResourceView* Assets::LoadTexture(const char* _fileName)
{
    //char*型からwchar_t*へ変換
    wchar_t wchar_fileName[256];
    //プログラムのロケール情報
    char* curLocale = setlocale(LC_ALL, "Japanese_Japan.932");
    //wchar_fileNameに内容装填
    //mbstowcs_s->マルチバイト文字のシーケンスを、対応するワイド文字のシーケンスに変換します
    mbstowcs_s(NULL, wchar_fileName, 256, _fileName, 255);

    HRESULT hr;
    ID3D11ShaderResourceView* outputSRV = nullptr;//(ShaderResourceView 着色器资源视图)

    hr = DirectX::CreateWICTextureFromFile(GetD3D_Device(), wchar_fileName, NULL, &outputSRV);

    if (FAILED(hr)) {
        //読み込みが失敗した場合
        //読み込み失敗のファイル名変換
        char outStr[128];
        wsprintfA(outStr, "%sを読み込み失敗", _fileName);
        //メッセージボックスで表示
        MessageBoxA(NULL, outStr, "エラー", MB_OK | MB_ICONERROR);

        return nullptr;
    }
    else {

        return outputSRV;
    }

}


