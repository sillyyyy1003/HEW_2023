#include "Assets.h"
#include <locale.h>


Assets::Assets()
{
    //===========ここからでテクスチャファイルを追加=============//
    //要注意!! 「L」いりません
    testchar01 = LoadTexture("assets/char01.png");
    testbg01 = LoadTexture("assets/testbg.png");

    testbgbox = LoadTexture("assets/testBox.png");
    testObj = LoadTexture("assets/testTex.png");
    testShadow = LoadTexture("assets/testShadow.png");



}

Assets::~Assets()
{
   SAFE_RELEASE(testchar01);
   SAFE_RELEASE(testbg01);

   SAFE_RELEASE(testbgbox);
   SAFE_RELEASE(testObj);
   SAFE_RELEASE(testShadow);

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


