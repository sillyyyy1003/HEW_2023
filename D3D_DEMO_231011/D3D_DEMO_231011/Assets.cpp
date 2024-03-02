#include "Assets.h"
#include <locale.h>
#include "UiManager.h"

ID3D11ShaderResourceView* Assets::debugFont;

Assets::Assets()
{
    //===========ここからでテクスチャファイルを追加=============//
    //要注意!! 「L」いりません
    debugFont = LoadTexture("assets/img/ASCIILib.png");

    //test
    //title
    uiTitleBg = LoadTexture("assets/img/title/00_title.png");

    //TUTORIAL
    uiTutorialAnimation[INTRODUCE] = LoadTexture("assets/img/tutorial/01_switch.png");
    uiTutorial[INTRODUCE] = LoadTexture("assets/img/tutorial/02_forward.png");
    uiTutorialAnimation[MOVE1] = LoadTexture("assets/img/tutorial/03_switch.png");
    uiTutorial[MOVE1] = LoadTexture("assets/img/tutorial/04_skill1.png");
    uiTutorialAnimation[MOVE2] = LoadTexture("assets/img/tutorial/05_switch.png");
    uiTutorial[MOVE2] = LoadTexture("assets/img/tutorial/06_skill2.png");
    uiTutorialAnimation[MOVE3] = LoadTexture("assets/img/tutorial/07_switch.png");
    uiTutorial[MOVE3] = LoadTexture("assets/img/tutorial/08_skill3.png");
    uiTutorialAnimation[MOVE4] = LoadTexture("assets/img/tutorial/09_switch.png");
    uiTutorial[MOVE4] = LoadTexture("assets/img/tutorial/10_skill4.png");
    uiTutorialAnimation[SIZECHANGE] = LoadTexture("assets/img/tutorial/11_switch.png");
    uiTutorial[SIZECHANGE] = LoadTexture("assets/img/tutorial/12_skill5.png");
    uiTutorialAnimation[COMBINITION] = LoadTexture("assets/img/tutorial/13_switch.png");
    uiTutorial[COMBINITION] = LoadTexture("assets/img/tutorial/14_skill6.png");
    uiTutorialAnimation[END] = LoadTexture("assets/img/tutorial/15_switch.png");
    uiTutorial[END] = LoadTexture("assets/img/tutorial/16_start.png");

    //select
    uiSelectBg = LoadTexture("assets/img/ui/select/Select_bg.png");
    uiSelectCursor = LoadTexture("assets/img/ui/select/hane.png");
    uiSelectStage[0] = LoadTexture("assets/img/ui/select/stage1.png");
    uiSelectStage[1] = LoadTexture("assets/img/ui/select/stage2.png");
    uiSelectStage[2] = LoadTexture("assets/img/ui/select/stage3.png");
    uiSelectChapter[0] = LoadTexture("assets/img/ui/select/chapter1.png");
    uiSelectChapter[1] = LoadTexture("assets/img/ui/select/chapter2.png");
    uiSelectChapter[2] = LoadTexture("assets/img/ui/select/chapter3.png");

    selectMask = LoadTexture("assets/img/ui/select/stage_select_left_mask.png");
    chapterMask= LoadTexture("assets/img/ui/select/stage_select_right_mask.png");
    uiClear= LoadTexture("assets/img/ui/select/clear.png");

    stageMask = LoadTexture("assets/img/bg_mask.png");
    controlPanel = LoadTexture("assets/img/ui/controlPanel.png");
    resultMask = LoadTexture("assets/img/result_mask.png");
    
    //stage hint
    stageHint[0] = LoadTexture("assets/img/stage1/1_1_hint.png");
    stageHint[1] = LoadTexture("assets/img/stage1/1_2_hint.png");
    stageHint[2] = LoadTexture("assets/img/stage1/1_3_hint.png");
    stageShapeHint[0] = LoadTexture("assets/img/stage1/1_1_ingame_hint.png");
    stageShapeHint[1] = LoadTexture("assets/img/stage1/1_2_ingame_hint.png");
    stageShapeHint[2] = LoadTexture("assets/img/stage1/1_3_ingame_hint.png");
    stageHintBg = LoadTexture("assets/img/ui/bg_shadow.png");

    stageTutorial[0]= LoadTexture("assets/img/stage1/hint_direction_animation.png");
    stageTutorial[1] = LoadTexture("assets/img/stage1/hint_space_animation.png");
    stageTutorial[2] = LoadTexture("assets/img/stage1/hint_h_animation.png");


    //stage1_1
    stageBg1_1 = LoadTexture("assets/img/stage1/1_1_bgA.png");
    coconut = LoadTexture("assets/img/stage1/coconut.png");
    coconutShadow = LoadTexture("assets/img/stage1/coconut_s.png");
    lamp = LoadTexture("assets/img/stage1/lamp.png");
    lampShadow = LoadTexture("assets/img/stage1/lamp_s.png");
    housePlate = LoadTexture("assets/img/stage1/housePlate.png");
    housePlateShadow = LoadTexture("assets/img/stage1/housePlate_s.png");

    //stage1_2
    stageBg1_2 = LoadTexture("assets/img/stage1/1_2_bgA.png");
    lamp_1_2 =  LoadTexture("assets/img/stage1/1_2_lamp.png");
    lamp_1_2Shadow = LoadTexture("assets/img/stage1/1_2_lamp_shadow.png");
    iphone = LoadTexture("assets/img/stage1/1_2_iphone.png");
    iphoneShadow = LoadTexture("assets/img/stage1/1_2_iphone_shadow.png");
    triangleBlock = LoadTexture("assets/img/stage1/1_2_bulidingblock.png");
    triangleBlockShadow = LoadTexture("assets/img/stage1/1_2_buldingblock_shadow.png");

    //Result Comic
    //1-1
    resultComic1_1_1 = LoadTexture("assets/img/clear/1_1_1.png");
    resultComic1_1_2 = LoadTexture("assets/img/clear/1_1_2.png");
    resultComic1_1_3 = LoadTexture("assets/img/clear/1_1_3.png");
    //1-2
    resultComic1_2_1 = LoadTexture("assets/img/clear/1_2_1.png");
    resultComic1_2_2 = LoadTexture("assets/img/clear/1_2_2.png");
    resultComic1_2_3 = LoadTexture("assets/img/clear/1_2_3.png");

    resultComic1_3_1 = LoadTexture("assets/img/clear/1_3_1.png");
    resultComic1_3_2 = LoadTexture("assets/img/clear/1_3_2.png");
    resultComic1_3_3 = LoadTexture("assets/img/clear/1_3_3.png");

    //stage1_3
    //stage3Bg = LoadTexture("assets/stage1/1_3_BG.png");
    stageBg1_3 = LoadTexture("assets/img/stage1/1_3_bgA.png");
    sandwich = LoadTexture("assets/img/stage1/1_3_sandwich.png");
    sandwichShadow = LoadTexture("assets/img/stage1/1_3_sandwich_shadow.png");
    busket = LoadTexture("assets/img/stage1/1_3_busket.png");
    busketShadow = LoadTexture("assets/img/stage1/1_3_bucket_shadow.png");
    newspaper = LoadTexture("assets/img/stage1/1_3_newspaper.png");
    newspaperShadow = LoadTexture("assets/img/stage1/1_3_newspaper_shadow.png");
    picnicbasket = LoadTexture("assets/img/stage1/1_3_picnicbasket.png");
    picnicbasketShadow = LoadTexture("assets/img/stage1/1_3_pinicbasket_shadow.png");

    //result
    resultBg = LoadTexture("assets/img/result/result＿BG.png");
    Button_again = LoadTexture("assets/img/result/result_button_again.png");
    Button_next = LoadTexture("assets/img/result/result_button_next.png");
    Button_return = LoadTexture("assets/img/result/result_button_return.png");
    result = LoadTexture("assets/img/result/result_result.png");
    Result_score = LoadTexture("assets/img/result/result_score.png");
    Result_stepcount = LoadTexture("assets/img/result/result_stepcount.png");
    Result_num = LoadTexture("assets/img/result/result_suuji.png");
    star = LoadTexture("assets/img/result/Star_shadow.png");
    starShadow = LoadTexture("assets/img/result/Star.png");
    Button_skip = LoadTexture("assets/img/result/result_skip_botton.png");


    //pause
    uiPauseBg = LoadTexture("assets/img/ui/pauseBg.png");

    uiPauseButton[0]= LoadTexture("assets/img/ui/resume.png");
    uiPauseButton[1] = LoadTexture("assets/img/ui/restart.png");
    uiPauseButton[2] = LoadTexture("assets/img/ui/select.png");
    uiPauseButton[3] = LoadTexture("assets/img/ui/sound.png");

    uiResume = LoadTexture("assets/img/ui/resume.png");
    uiRestart = LoadTexture("assets/img/ui/restart.png");
    uiSelect= LoadTexture("assets/img/ui/select.png");
    uiSound = LoadTexture("assets/img/ui/sound.png");


    //sound
    uiSoundBg = LoadTexture("assets/img/ui/soundBg.png");//サウンド背景
    uiSoundOp_BGM = LoadTexture("assets/img/ui/pause_note.png");
    uiSoundCursor = LoadTexture("assets/img/ui/pause_select.png");

    fade = LoadTexture("assets/img/ui/fade.png");

    //effect
    effect1 = LoadTexture("assets/img/Effect/cursor.png");
    uiArrow = LoadTexture("assets/img/ui/direction_animation.png");

    comingSoon = LoadTexture("assets/img/stage1/comingsoon_1.png");
    comingSoonLoop = LoadTexture("assets/img/stage1/comingsoon_loop.png");


}

Assets::~Assets()
{

    // 図形

    //タイトル用のリソース
    SAFE_RELEASE(uiTitleBg);


    //ステージセレクト用
    SAFE_RELEASE(uiSelectBg);
    SAFE_RELEASE(uiSelectCursor);

    for (int i = 0; i < 3; i++) {
        SAFE_RELEASE(uiSelectStage[i]);
        SAFE_RELEASE(uiSelectChapter[i]);
        SAFE_RELEASE(stageHint[i]);
        SAFE_RELEASE(stageShapeHint[i]);
        SAFE_RELEASE(stageTutorial[i]);

    }
    SAFE_RELEASE(selectMask);
    SAFE_RELEASE(chapterMask);

    //UI用
    SAFE_RELEASE(stageMask);
    SAFE_RELEASE(controlPanel);
    SAFE_RELEASE(resultMask);

    //clear
    SAFE_RELEASE(uiClear);
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
    SAFE_RELEASE(stageBg1_3);

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

    for (int i = 0; i < 4; i++) {
        SAFE_RELEASE(uiPauseButton[i]);
    }

    for (int i = 0; i < 8; i++) {
        SAFE_RELEASE(uiTutorial[i]);
        SAFE_RELEASE(uiTutorialAnimation[i]);
    }


    //サウンド画面用
    SAFE_RELEASE(uiSoundBg);//サウンド背景
    SAFE_RELEASE(uiSoundOp_BGM);//サウンド調節
    SAFE_RELEASE(uiSoundCursor);


    SAFE_RELEASE(fade);

    //エフェクト用
    SAFE_RELEASE(effect1);
    SAFE_RELEASE(uiArrow);

    SAFE_RELEASE(comingSoon);
    SAFE_RELEASE(comingSoonLoop);
    

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