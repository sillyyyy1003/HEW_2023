#include "Assets.h"
#include <locale.h>

ID3D11ShaderResourceView* Assets::debugFont;

Assets::Assets()
{
    //===========ここからでテクスチャファイルを追加=============//
    //要注意!! 「L」いりません
    debugFont = LoadTexture("assets/img/ASCIILib.png");

    //test
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
    stageBg1_1 = LoadTexture("assets/stage1/stage1_1Bg.png");
    coconut = LoadTexture("assets/stage1/coconut.png");
    coconutShadow = LoadTexture("assets/stage1/coconut_s.png");
    lamp = LoadTexture("assets/stage1/lamp.png");
    lampShadow = LoadTexture("assets/stage1/lamp_s.png");
    housePlate = LoadTexture("assets/stage1/housePlate.png");
    housePlateShadow = LoadTexture("assets/stage1/housePlate_s.png");

    //stage1_2
    stageBg1_2 = LoadTexture("assets/stage1/1-2Bg.png");

    lamp_1_2 =  LoadTexture("assets/stage1/1_2_lamp.png");
    lamp_1_2Shadow = LoadTexture("assets/stage1/1_2_lamp_shadow.png");
    iphone = LoadTexture("assets/stage1/1_2_iphone.png");
    iphoneShadow = LoadTexture("assets/stage1/1_2_iphone_shadow.png");
    triangleBlock = LoadTexture("assets/stage1/1_2_bulidingblock.png");
    triangleBlockShadow = LoadTexture("assets/stage1/1_2_buldingblock_shadow.png");

    //Result Comic
    //1-1
    resultComic1_1_1 = LoadTexture("assets/clear/1_1_1.png");
    resultComic1_1_2 = LoadTexture("assets/clear/1_1_2.png");
    resultComic1_1_3 = LoadTexture("assets/clear/1_1_3.png");
    //1-2
    resultComic1_2_1 = LoadTexture("assets/clear/1_2_1.png");
    resultComic1_2_2 = LoadTexture("assets/clear/1_2_2.png");
    resultComic1_1_3 = LoadTexture("assets/clear/1_2_3.png");

      //stage1_3
    stage3Bg = LoadTexture("assets/stage1/1_3_BG.png");
    sandwich = LoadTexture("assets/stage1/1_3_sandwich.png");
    sandwichShadow = LoadTexture("assets/stage1/1_3_sandwich_shadow.png");
    busket = LoadTexture("assets/stage1/1_3_busket.png");
    busketShadow = LoadTexture("assets/stage1/1_3_bucket_shadow.png");
    newspaper = LoadTexture("assets/stage1/1_3_newspaper.png");
    newspaperShadow = LoadTexture("assets/stage1/1_3_newspaper_shadow.png");
    picnicbasket = LoadTexture("assets/stage1/1_3_picnicbasket.png");
    picnicbasketShadow = LoadTexture("assets/stage1/1_3_pinicbasket_shadow.png");

    //pause
    uiPauseBg = LoadTexture("assets/ui/pauseBg.png");
    uiResume = LoadTexture("assets/ui/resume.png");
    uiRestart = LoadTexture("assets/ui/restart.png");
    uiSelect= LoadTexture("assets/ui/select.png");
    uiSound = LoadTexture("assets/ui/sound.png");

    //sound
    uiSoundBg = LoadTexture("assets/ui/soundBg.png");//サウンド背景
    uiMusic = LoadTexture("assets/ui/pause_music.png");
    uiSE = LoadTexture("assets/ui/pause_se.png");
    uiSoundOp_BGM = LoadTexture("assets/ui/pause_note.png");

    fade = LoadTexture("assets/fade.png");

    //effect
    effect1 = LoadTexture("assets/Effect/effect4.png");


}

Assets::~Assets()
{

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
    SAFE_RELEASE(stageBg1_1);

    SAFE_RELEASE(coconut);
    SAFE_RELEASE(coconutShadow);
    SAFE_RELEASE(lamp);
    SAFE_RELEASE(lampShadow);
    SAFE_RELEASE(housePlate);
    SAFE_RELEASE(housePlateShadow);

    //1-2
    SAFE_RELEASE(stageBg1_2);
    SAFE_RELEASE(lamp_1_2);
    SAFE_RELEASE(lamp_1_2Shadow);
    SAFE_RELEASE(iphone);
    SAFE_RELEASE(iphoneShadow);
    SAFE_RELEASE(triangleBlock);
    SAFE_RELEASE(triangleBlockShadow);

    //Result Comic
    //1-1
    SAFE_RELEASE(resultComic1_1_1);
    SAFE_RELEASE(resultComic1_1_2);
    SAFE_RELEASE(resultComic1_1_3);
    //1-2
    SAFE_RELEASE(resultComic1_2_1);
    SAFE_RELEASE(resultComic1_2_2);
    SAFE_RELEASE(resultComic1_1_3);    //stage1-2用リソース

    //stage1-3用リソース
    SAFE_RELEASE(stage3Bg);

    SAFE_RELEASE(sandwich);
    SAFE_RELEASE(sandwichShadow);
    SAFE_RELEASE(busket);
    SAFE_RELEASE(busketShadow);
    SAFE_RELEASE(newspaper);
    SAFE_RELEASE(newspaperShadow);
    SAFE_RELEASE(picnicbasket);
    SAFE_RELEASE(picnicbasketShadow);

    //ポーズ画面用
    SAFE_RELEASE(uiPauseBg);
    SAFE_RELEASE(uiResume);
    SAFE_RELEASE(uiRestart);

    SAFE_RELEASE(uiSelect);
    SAFE_RELEASE(uiSound);

    //サウンド画面用
    SAFE_RELEASE(uiSoundBg);//サウンド背景
    SAFE_RELEASE(uiSoundOp_BGM);//サウンド調節
    SAFE_RELEASE(uiMusic);	//サウンド音楽文字表示
    SAFE_RELEASE(uiSE);		//サウントSE文字表示


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


