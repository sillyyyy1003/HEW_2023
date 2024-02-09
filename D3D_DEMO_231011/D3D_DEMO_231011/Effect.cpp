#include "Effect.h"
#include "Game.h"
#include "GameObject.h"

extern Camera* g_WorldCamera;

Effect::Effect(int num)
{   
    //ここでアニメーションパターンを変更
    m_frameNum = num;
    animeTable = new int[m_frameNum + 1];

    for (int i = 0; i < m_frameNum; i++) {
        animeTable[i] = i;
    }
  
}

void Effect::SetLoop(bool isLoop) 
{

    this->isLoop = isLoop;     
    
    //最後の位置フレームの処理
    if (isLoop) {

        animeTable[m_frameNum] = -1;
    }
    else {
        animeTable[m_frameNum] = -2;
    }
    
}



Effect::~Effect()
{
    delete[] animeTable;
}

void Effect::CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
    //カメラの使用を禁じる
    //isUseCamera = false;

    //モデル作成
    Sprite::CreateModel(texture, _width, _height, splitX, splitY);

    //アニメーションを配置
    m_anime = new Animation(splitX, splitY);

    m_camera = g_WorldCamera;
}

void Effect::Update()
{
    //int animeTable[29] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,-1 };

    // 表示させるコマIDを取得
    int animeID = animeTable[(int)m_anime->m_animeCounter];


    if (m_anime->isPlaying)
    {
        // アニメーションのカウンターを進める
        m_anime->m_animeCounter += m_anime->m_animeSpeed;

        //ループする場合
        if (animeTable[(int)m_anime->m_animeCounter] == -1)
        {
            m_anime->m_animeCounter = 0.0f;
        }

        //ループしない場合
        if (animeTable[(int)m_anime->m_animeCounter] == -2) {
            m_anime->isPlaying = false;
            m_anime->m_animeCounter = 0.0f;
            isActive = false;
        }

    }

    //表示させるコマのUVを計算
    m_anime->SetFrameX(animeID % m_split.x);

    //UV座標更新
    m_anime->Update();

    //位置を確定
    if (isTrace) {
    
    //
    DirectX::XMFLOAT3 tracePos = { 0,0,0 };
        
        //稼働中のオブジェクトを探す
        for (auto& element : Game::Get()->GetObjectList()) {

            if (element->GetActive()) {
             
                //位置を獲得
                tracePos = element->m_obj->m_sprite->m_pos;
                m_pos = tracePos;
         
                //y軸の位置をずらす
                m_pos.y += element->m_obj->GetExtents().y;
                //z軸の位置をずらす
                m_pos.z = tracePos.z - 0.1f;
                break;

            }

        }
        
    }



}

void Effect::Draw()
{
    if (Effect::isActive) {

        Sprite::Draw();
        
    }
  
}
