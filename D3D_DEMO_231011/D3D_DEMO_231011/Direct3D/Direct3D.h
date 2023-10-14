#pragma once

#include <d3d11.h>		// DirectX11を使うためのヘッダーファイル
#include <DirectXMath.h>// DirextXの数学関連のヘッダーファイル
using namespace DirectX;


//マクロ解放
#define SAFE_RELEASE(p)      { if( NULL != p ) { p->Release(); p = NULL; } }

//x,yを表す構造体
struct FLOAT2 
{
	float x, y;
};

//定数バッファ用構造体
struct CONSTBUFFER 
{
	DirectX::XMMATRIX matrixTex;	//UV座標移動行列
	DirectX::XMMATRIX matrixProj;	//投影行列
	DirectX::XMMATRIX matrixWorld;	//ワールド変換行列
};

//Direct3D関連変数をまとめる構造体
struct D3D_DATA
{
	ID3D11Device*			Device;					//デバイス(设备)
	ID3D11DeviceContext*	Context;				//コンテキスト(设备上下文)
	IDXGISwapChain*			SwapChain;				//スワップチェイン(交换链)
	ID3D11RenderTargetView* RenderTarget;			//レンダーターゲット(RenderTargetView)
	ID3D11DepthStencilView* DepthStencilView;		//深度バッファ(深度缓冲)
	ID3D11Texture2D*		DepthStencilTexture;	//深度バッファ用テキスチャー
	ID3D11InputLayout*		InputLayout;			//インプットレイアウト(顶点数据馈送到图形管道)
	ID3D11VertexShader*		VertexShader;			//頂点シェーダー(顶点着色器)
	ID3D11PixelShader*		PixelShader;			//ピクセルシェーダー(像素着色器)
	D3D11_VIEWPORT			Viewport;				//ビューポート(视口)
	ID3D11BlendState*		BlendAlpha;				// アルファブレンディング用ブレンドステート(Alpha混合 透明效果)
	ID3D11BlendState*		BlendAdd;				//加算合成用ブレンドステート(加法混合 明亮效果)
	ID3D11SamplerState*		Sampler;				//ポイント補完用サンプラー(采样器)
};

//----------------------------//
// 関数のプロトタイプ宣言
//----------------------------//


/*
	@brief	DirectX初期化
	@param	<hWnd>:Window
	@return 
*/
void DirectXInit(HWND hWnd);

/*
	@brief	Device&SwapChain作成する
	@param	無し
	@return 失敗した時　エラー表示
*/
BOOL D3D_CreateDevice(HWND hwnd);

/*
	@brief	レンダーターゲットを作成する関数
	@param	無し
	@return 失敗した時　エラー表示
*/
BOOL D3D_CreateRenderTarget(void);

/*
	@brief	深度ステンシルバッファを作成する関数
	@param	無し
	@return 失敗した時　エラー表示
*/
BOOL D3D_CreateDepthStencil(void);

/*
	@brief　シェーダーのオブジェクトを作成する関数 
	@param	無し
	@return 失敗した時　エラー表示
	
*/
BOOL D3D_CreateShader(void);

/*
	@brief　ビューポートを作成する関数
	@param	無し
	@return 無し

*/
void D3D_SetViewPort(void);

/*
	@brief　サンプラー作成する関数
	@param	無し
	@return 失敗した時　エラー表示
*/

BOOL D3D_CreateSampler(void);


/*
	@brief　定数バッファ作成する関数
	@param	無し
	@return 失敗した時　エラー表示
*/
BOOL D3D_CreateBuffer(void);

/*
	@brief　ブレンドステート作成する関数
	@param	無し
	@return 失敗した時　エラー表示

BOOL D3D_CreateBlendState(void);

/*
	@brief	画面塗りつぶしと設定を行う関数
	@param	無し
	@return 無し
*/
void D3D_ClearScreen(void);


/*
	@brief	メモリ解放処理
	@param	無し
	@return 無し
*/
void D3D_Release(void);

/*
	@brief	g_pD3Dのゲッター
	@param	無し
	@return g_pD3D
*/
D3D_DATA* GetD3D_DATA(void);

/*
	@brief	g_pD3D->Deviceのゲッター
	@param	無し
	@return g_pD3D->Device
*/
ID3D11Device* GetD3D_Device(void);

/*
	@brief	g_pD3D->Contextのゲッター
	@param	無し
	@return g_pD3D->Context
*/
ID3D11DeviceContext* GetD3D_Context(void);



// グローバル変数のextern宣言
extern ID3D11Buffer* g_ConstantBuffer;
