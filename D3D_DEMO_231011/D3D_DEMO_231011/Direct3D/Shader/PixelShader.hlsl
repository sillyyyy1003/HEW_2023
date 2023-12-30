﻿// ピクセルシェーダー

// ピクセルの情報の構造体（受け取り用）
struct PS_IN
{
    // float4型　→　float型が４つの構造体
    float4 pos : SV_POSITION; // ピクセルの画面上の座標
    float2 tex : TEXCOORD;  // ピクセルに対応するテクスチャ座標
};

// グローバル変数の宣言
// ※シェーダーのグローバル変数は、C言語プログラムから渡された
// 　データを受け取るために使う。
Texture2D myTexture : register(t0); //テクスチャー
SamplerState mySampler : register(s0); //サンプラー

// ピクセルシェーダーのエントリポイント
float4 ps_main(PS_IN input) : SV_Target
{
    // Sample関数→テクスチャから指定したUVを元にピクセル色を取って来る
    float4 color = myTexture.Sample(mySampler, input.tex);    
    return color;
}