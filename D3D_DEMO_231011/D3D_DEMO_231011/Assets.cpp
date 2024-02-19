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
    uiTitleBg = LoadTexture("assets/title/title_animation.png");
    uiPressSpace = LoadTexture("assets/title/title_pressspace_button.png");

    //select
    uiSelectBg = LoadTexture("assets/ui/select/Select_bg.png");
    uiSelectCursor = LoadTexture("assets/ui/select/hane.png");
    uiSelectStage1 = LoadTexture("assets/ui/select/stage1.png");
    uiSelectStage2 = LoadTexture("assets/ui/select/stage2.png");
    uiSelectStage3 = LoadTexture("assets/ui/select/stage3.png");
    uiSelectChapter1 = LoadTexture("assets/ui/select/chapter1.png");
    uiSelectChapter2 = LoadTexture("assets/ui/select/chapter2.png");
    uiSelectChapter3 = LoadTexture("assets/ui/select/chapter3.png");
    uiClear= LoadTexture("assets/ui/select/clear.png");

    stageMask = LoadTexture("assets/img/bg_mask.png");
    controlPanel = LoadTexture("assets/ui/controlPanel.png");
    resultMask = LoadTexture("assets/img/result_mask.png");
    
    //stage hint
    stageHint1_1 = LoadTexture("assets/hint/1_1_hint.png");
    stageHint1_2 = LoadTexture("assets/hint/1_2_hint.png");
    stageHint1_3 = LoadTexture("assets/hint/1_3_hint.png");
    stageHintBg = LoadTexture("assets/hint/bg_shadow.png");

    //stage1_1
    stageBg1_1 = LoadTexture("assets/stage1/1_1_BG.png");
    coconut = LoadTexture("assets/stage1/coconut.png");
    coconutShadow = LoadTexture("assets/stage1/coconut_s.png");
    lamp = LoadTexture("assets/stage1/lamp.png");
    lampShadow = LoadTexture("assets/stage1/lamp_s.png");
    housePlate = LoadTexture("assets/stage1/housePlate.png");
    housePlateShadow = LoadTexture("assets/stage1/housePlate_s.png");

    //stage1_2
    stageBg1_2 = LoadTexture("assets/stage1/1_2Bg.png");
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
    resultComic1_2_3 = LoadTexture("assets/clear/1_2_3.png");

    resultComic1_3_1 = LoadTexture("assets/clear/1_3_1.png");
    resultComic1_3_2 = LoadTexture("assets/clear/1_3_2.png");
    resultComic1_3_3 = LoadTexture("assets/clear/1_3_3.png");

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

    //result
    resultBg = LoadTexture("assets/result/result＿BG.png");
    Button_again = LoadTexture("assets/result/result_button_again.png");
    Button_next = LoadTexture("assets/result/result_button_next.png");
    Button_return = LoadTexture("assets/result/result_button_return.png");
    result = LoadTexture("assets/result/result_result.png");
    Result_score = LoadTexture("assets/result/result_score.png");
    Result_stepcount = LoadTexture("assets/result/result_stepcount.png");
    Result_num = LoadTexture("assets/result/result_suuji.png");
    star = LoadTexture("assets/result/Star_shadow.png");
    starShadow = LoadTexture("assets/result/Star.png");
    Button_skip = LoadTexture("assets/result/result_skip_botton.png");


    //pause
    uiPauseBg = LoadTexture("assets/ui/pauseBg.png");
    uiResume = LoadTexture("assets/ui/resume.png");
    uiRestart = LoadTexture("assets/ui/restart.png");
    uiSelect= LoadTexture("assets/ui/select.png");
    uiSound = LoadTexture("assets/ui/sound.png");
    uiPauseCursor= LoadTexture("assets/ui/select/hane.png");

    //sound
    uiSoundBg = LoadTexture("assets/ui/soundBg.png");//サウンド背景
    uiMusic = LoadTexture("assets/ui/pause_music.png");
    uiSE = LoadTexture("assets/ui/pause_se.png");
    uiSoundOp_BGM = LoadTexture("assets/ui/pause_note.png");

    fade = LoadTexture("assets/hint/fade.png");

    //effect
    effect1 = LoadTexture("assets/Effect/cursor.png");
    uiArrow = LoadTexture("assets/ui/direction_animation.png");


}

Assets::~Assets()
{

    // 図形

    //タイトル用のリソース
    SAFE_RELEASE(uiTitleBg);
 
    SAFE_RELEASE(uiPressSpace);

    //ステージセレクト用
    SAFE_RELEASE(uiSelectBg);


    SAFE_RELEASE(uiSelectCursor);
    SAFE_RELEASE(uiSelectStage1);
    SAFE_RELEASE(uiSelectStage2);
    SAFE_RELEASE(uiSelectStage3);

    SAFE_RELEASE(uiSelectChapter1);
    SAFE_RELEASE(uiSelectChapter2);
    SAFE_RELEASE(uiSelectChapter3);

    //UI用
    SAFE_RELEASE(stageMask);
    SAFE_RELEASE(controlPanel);
    SAFE_RELEASE(resultMask);

    //clear
    SAFE_RELEASE(uiClear);
    SAFE_RELEASE(stageHint1_1);
    SAFE_RELEASE(stageHint1_2);
    SAFE_RELEASE(stageHint1_3);
    SAFE_RELEASE(stageHintBg);    


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
    SAFE_RELEASE(resultComic1_2_3);    //stage1-2用リソース
    //1-3
    SAFE_RELEASE(resultComic1_3_1);
    SAFE_RELEASE(resultComic1_3_2);
    SAFE_RELEASE(resultComic1_3_3);    //stage1-2用リソース

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

    //result
    SAFE_RELEASE(resultBg);

    SAFE_RELEASE(Button_again);
    SAFE_RELEASE(Button_next);
    SAFE_RELEASE(Button_return);
    SAFE_RELEASE(result);
    SAFE_RELEASE(Result_score);
    SAFE_RELEASE(Result_stepcount);
    SAFE_RELEASE(Result_num);
    SAFE_RELEASE(star);
    SAFE_RELEASE(starShadow);
    SAFE_RELEASE(Button_skip);


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
    SAFE_RELEASE(uiArrow);

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


