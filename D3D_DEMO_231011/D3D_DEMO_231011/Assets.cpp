#include "Assets.h"
#include <locale.h>

ID3D11ShaderResourceView* Assets::debugFont;

Assets::Assets()
{
    //===========ここからでテクスチャファイルを追加=============//
    //要注意!! 「L」いりません
    debugFont = LoadTexture("assets/img/ASCIILib.png");

    //test
    //circle = LoadTexture("assets/Tree.png");
    tree = LoadTexture("assets/Tree.png");
    shadow = LoadTexture("assets/treeshadow.png");

    //title
    uiTitle = LoadTexture("assets/title/uiTitle.png");
    uiTitleBg = LoadTexture("assets/title/titleBg.png");
    uiPressEnter = LoadTexture("assets/title/uiPressEnter.png");

    //select
    uiSelectBg = LoadTexture("assets/ui/select/selectbg.png");
    uiStageSelect = LoadTexture("assets/ui/select/stageselect.png");
    uiSelectCursor = LoadTexture("assets/ui/select/hane.png");
    uiSelectStage1 = LoadTexture("assets/ui/select/stage1.png");
    uiSelectStage2 = LoadTexture("assets/ui/select/stage2.png");
    uiSelectStage3 = LoadTexture("assets/ui/select/stage3.png");
    uiSelectChapter1 = LoadTexture("assets/ui/select/chapter1.png");
    uiSelectChapter2 = LoadTexture("assets/ui/select/chapter2.png");
    uiSelectChapter3 = LoadTexture("assets/ui/select/chapter3.png");
    uiClear= LoadTexture("assets/ui/select/clear.png");

    //stage1_1
    stageBg = LoadTexture("assets/stage1/stage1_1Bg.png");
    coconut = LoadTexture("assets/stage1/coconut.png");
    coconutShadow = LoadTexture("assets/stage1/coconut_s.png");
    lamp = LoadTexture("assets/stage1/lamp.png");
    lampShadow = LoadTexture("assets/stage1/lamp_s.png");
    housePlate = LoadTexture("assets/stage1/housePlate.png");
    housePlateShadow = LoadTexture("assets/stage1/housePlate_s.png");

    //pause
    uiPauseBg = LoadTexture("assets/ui/pauseBg.png");
    uiResume = LoadTexture("assets/ui/resume.png");
    uiRestart = LoadTexture("assets/ui/restart.png");
    uiSelect= LoadTexture("assets/ui/select.png");
    uiSound = LoadTexture("assets/ui/sound.png");

    //sound
    uiSoundBg = LoadTexture("assets/ui/soundBg.png");//サウンド背景
    uiSoundOp_BGM = LoadTexture("assets/Tree.png");
    uiSoundOp_SE = LoadTexture("assets/Tree.png");

    fade = LoadTexture("assets/fade.png");

    //effect
    effect1 = LoadTexture("assets/Effect/effect2.png");


}

Assets::~Assets()
{
    //title

    SAFE_RELEASE(tree);
    SAFE_RELEASE(shadow);

    // 図形

    //タイトル用のリソース
    SAFE_RELEASE(uiTitleBg);
    SAFE_RELEASE(uiTitle);
    SAFE_RELEASE(uiPressEnter);

    //ステージセレクト用
    SAFE_RELEASE(uiSelectBg);
    SAFE_RELEASE(uiStageSelect);

    SAFE_RELEASE(uiSelectCursor);
    SAFE_RELEASE(uiSelectStage1);
    SAFE_RELEASE(uiSelectStage2);
    SAFE_RELEASE(uiSelectStage3);

    SAFE_RELEASE(uiSelectChapter1);
    SAFE_RELEASE(uiSelectChapter2);
    SAFE_RELEASE(uiSelectChapter3);

    SAFE_RELEASE(uiClear);


    //stage1-1用リソース
    SAFE_RELEASE(stageBg);

    SAFE_RELEASE(coconut);
    SAFE_RELEASE(coconutShadow);
    SAFE_RELEASE(lamp);
    SAFE_RELEASE(lampShadow);
    SAFE_RELEASE(housePlate);
    SAFE_RELEASE(housePlateShadow);



    //ポーズ画面用
    SAFE_RELEASE(uiPauseBg);
    SAFE_RELEASE(uiResume);
    SAFE_RELEASE(uiRestart);

    SAFE_RELEASE(uiSelect);
    SAFE_RELEASE(uiSound);

    //サウンド画面用
    SAFE_RELEASE(uiSoundBg);//サウンド背景
    SAFE_RELEASE(uiSoundOp_BGM);//サウンド調節
    SAFE_RELEASE(uiSoundOp_SE);//サウンド調節


    SAFE_RELEASE(fade);

    //エフェクト用
    SAFE_RELEASE(effect1);

    //デバッグ用
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


