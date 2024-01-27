#include "Assets.h"
#include <locale.h>

ID3D11ShaderResourceView* Assets::debugFont;

Assets::Assets()
{
    //===========ここからでテクスチャファイルを追加=============//
    //要注意!! 「L」いりません
    testPause= LoadTexture("assets/pause.png");
    debugFont = LoadTexture("assets/img/ASCIILib.png");

    uiTitle = LoadTexture("assets/title/uiTitle.png");
    uiTitleBg = LoadTexture("assets/title/titleBg.png");
    uiPressEnter = LoadTexture("assets/title/uiPressEnter.png");

    uiPauseBg = LoadTexture("assets/ui/pauseBg.png");
    uiResume = LoadTexture("assets/ui/resume.png");
    uiRestart = LoadTexture("assets/ui/restart.png");

    //test
    circle = LoadTexture("assets/Tree.png");
    shadow = LoadTexture("assets/treeshadow.png");

    //stage1_1
    stageBg = LoadTexture("assets/stage1/stage1_1Bg.png");
    coconut = LoadTexture("assets/stage1/coconut.png");
    coconutShadow = LoadTexture("assets/stage1/coconut_s.png");
    lamp = LoadTexture("assets/stage1/lamp.png");
    lampShadow = LoadTexture("assets/stage1/lamp_s.png");
    housePlate = LoadTexture("assets/stage1/housePlate.png");
    housePlateShadow = LoadTexture("assets/stage1/housePlate_s.png");




}

Assets::~Assets()
{
    //title
    SAFE_RELEASE(uiTitleBg);
    SAFE_RELEASE(uiTitle);
    SAFE_RELEASE(uiPressEnter);

    //stage1_1
    SAFE_RELEASE(stageBg);
    SAFE_RELEASE(coconut);
    SAFE_RELEASE(lamp);
    SAFE_RELEASE(housePlate);
    SAFE_RELEASE(coconutShadow);
    SAFE_RELEASE(lampShadow);
    SAFE_RELEASE(housePlateShadow);

    SAFE_RELEASE(circle);
    SAFE_RELEASE(shadow);
    //ui
   
    SAFE_RELEASE(uiPauseBg);
    SAFE_RELEASE(uiResume);
    SAFE_RELEASE(uiRestart);


    SAFE_RELEASE(testPause);
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


