#include "Direct3D.h"
#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"
#include <atltypes.h>		// CRectを使うためのヘッダーファイル
#include "../Sprite.h"

// ライブラリのリンク設定
#pragma comment (lib, "d3d11.lib")

//----------------------------//
// グローバル変数定義
//----------------------------//
static D3D_DATA* g_pD3D;        //DirectXの機能を含めた構造体
static UINT g_ScreenWidth;      //画面の幅
static UINT g_ScreenHeight;     //画面の高さ
ID3D11Buffer* g_ConstantBuffer; //定数バッファ用変数


D3D_DATA* GetD3D_DATA(void) { return g_pD3D; }

ID3D11Device* GetD3D_Device(void){ return g_pD3D->Device; }

ID3D11DeviceContext* GetD3D_Context(void){ return g_pD3D->Context; }

ID3D11BlendState* GetBlendAlpha(void){ return g_pD3D->BlendAlpha; }

ID3D11BlendState* GetBlendAdd(void){ return g_pD3D->BlendAdd;}

void SetBlendState(ID3D11BlendState* _blendState)
{
     GetD3D_Context()->OMSetBlendState(_blendState,NULL, 0xffffffff);
}




void DirectXInit(HWND hWnd)
{
    //メモリ確保
    g_pD3D = (D3D_DATA*)malloc(sizeof(D3D_DATA));

    ZeroMemory(g_pD3D, sizeof(D3D_DATA));

    //デバイス作成関数を呼び出す
    D3D_CreateDevice(hWnd);

    //深度バッファ作成関数を呼び出す
    D3D_CreateDepthStencil();

    //レンダーターゲット作成関数を呼び出す
    D3D_CreateRenderTarget();

    //シェーダー作成関数を呼び出す
    D3D_CreateShader();

    //ビューポート設定関数を呼び出す
    D3D_SetViewPort();

    //サンプラー作成関数を呼び出す
    D3D_CreateSampler();

    //定数バッファ作成関数を呼び出す
    D3D_CreateBuffer();

    //ブレンドステート作成関数を呼び出す
    D3D_CreateBlendState();

}


BOOL D3D_CreateDevice(HWND hwnd)
{
	//HRESULT型・・・Windowsプログラムで関数実行の成功/失敗を受け取る
    HRESULT  hr;


    UINT flags = 0;

    CRect                rect;
    //ウインドウのクライアント領域（実際に描画できる範囲）のサイズを取得
    GetClientRect(hwnd, &rect);
    g_ScreenWidth  = rect.Width();
    g_ScreenHeight = rect.Height();

    D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL level;    

    DXGI_SWAP_CHAIN_DESC scDesc;
    ZeroMemory(&scDesc, sizeof(scDesc));

    scDesc.BufferCount = 1;
    scDesc.BufferDesc.Width = rect.Width();
    scDesc.BufferDesc.Height = rect.Height();
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.OutputWindow = hwnd;
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;
    scDesc.Windowed = TRUE;

    // デバイスとスワップチェインを同時に作成する関数の呼び出し
    hr = D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        flags,
        pLevels,
        1,
        D3D11_SDK_VERSION,
        &scDesc,
        &(g_pD3D->SwapChain),
        &(g_pD3D->Device),
        &level,
        &(g_pD3D->Context));

    if (FAILED(hr)) // 上の関数呼び出しが失敗してないかifでチェック
    {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL,"デバイス作成失敗", "エラー",MB_OK | MB_ICONERROR);
    }

}

BOOL D3D_CreateRenderTarget(void)
{
    HRESULT hr;
    ID3D11Texture2D* pBackBuffer;

    //バッファを取得
    hr = g_pD3D->SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);


    if (FAILED(hr))
    {
        //取得失敗した場合
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "バッファ取得失敗", "エラー", MB_OK | MB_ICONERROR);
    }
    else
    {
        // レンダーターゲットを作成する関数を呼び出す
        hr = g_pD3D->Device->CreateRenderTargetView(pBackBuffer, NULL, &g_pD3D->RenderTarget);
        pBackBuffer->Release();

        if (FAILED(hr)) {
            return FALSE;
            //エラー表示
            MessageBoxA(NULL, "レンダーターゲット作成失敗", "エラー", MB_OK | MB_ICONERROR);
        }
    }

}

BOOL D3D_CreateDepthStencil(void)
{
    HRESULT hr;

    // 深度ステンシルバッファを作成
    // ※深度バッファ（Zバッファ）→奥行を判定して前後関係を正しく描画できる

    D3D11_TEXTURE2D_DESC txDesc;
    ZeroMemory(&txDesc, sizeof(txDesc));
    txDesc.Width = g_ScreenWidth;
    txDesc.Height = g_ScreenHeight;
    txDesc.MipLevels = 1;
    txDesc.ArraySize = 1;
    txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    txDesc.SampleDesc.Count = 1;
    txDesc.SampleDesc.Quality = 0;
    txDesc.Usage = D3D11_USAGE_DEFAULT;
    txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    txDesc.CPUAccessFlags = 0;
    txDesc.MiscFlags = 0;
    hr = g_pD3D->Device->CreateTexture2D(&txDesc, NULL, &(g_pD3D->DepthStencilTexture));
    
    if (FAILED(hr)) 
    {   
        //エラー表示
        return FALSE;
        MessageBoxA(NULL, "CreateTexture2d Fail", "エラー", MB_OK | MB_ICONERROR);
    }
    else 
    {

        D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
        ZeroMemory(&dsDesc, sizeof(dsDesc));
        dsDesc.Format = txDesc.Format;
        dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        dsDesc.Texture2D.MipSlice = 0;
        hr = g_pD3D->Device->CreateDepthStencilView(g_pD3D->DepthStencilTexture, &dsDesc, &g_pD3D->DepthStencilView);
        if (FAILED(hr))
        {
            return FALSE;
            //エラー表示
            MessageBoxA(NULL, "深度ステンシルバッファ作成失敗", "エラー", MB_OK | MB_ICONERROR);
        }
    }   
}


BOOL D3D_CreateShader(void)
{
    HRESULT hr;
    //頂点シェーダー作成
    hr = g_pD3D->Device->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &(g_pD3D->VertexShader));
    if (FAILED(hr))
    {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "頂点シェーダー作成失敗", "エラー", MB_OK | MB_ICONERROR);
    }
    else
    {
        //ピクセルシェーダー作成
        hr = g_pD3D->Device->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &(g_pD3D->PixelShader));

        if (FAILED(hr)) {
            return FALSE;
            //エラー表示
            MessageBoxA(NULL, "ピクセルシェーダー作成失敗", "エラー", MB_OK | MB_ICONERROR);
        }
        else {
            //頂点１つあたりにどんなデータが含まれるかをDirect3Dに教える
            D3D11_INPUT_ELEMENT_DESC vertexDesc[]
            {
                // 位置座標があるということを伝える
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA, 0 },

                // UV座標があるということを伝える
                { "TEX",    0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                
                //追加情報ここに↓
            };

            //インプットレイアウト作成
            hr = g_pD3D->Device->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), g_vs_main, sizeof(g_vs_main), &(g_pD3D->InputLayout));
            if (FAILED(hr))
            {
                return FALSE;
                //エラー表示
                MessageBoxA(NULL, "インプットレイアウト作成失敗", "エラー", MB_OK | MB_ICONERROR);
            }

        }
    }
   

}

void D3D_SetViewPort(void)
{
   
   //画面分割などに使う、描画領域の指定のこと
   g_pD3D->Viewport.TopLeftX = 0;
   g_pD3D->Viewport.TopLeftY = 0;
   g_pD3D->Viewport.Width = g_ScreenWidth;
   g_pD3D->Viewport.Height = g_ScreenHeight;
   g_pD3D->Viewport.MinDepth = 0.0f;
   g_pD3D->Viewport.MaxDepth = 1.0f;
}

BOOL D3D_CreateSampler(void)
{
    //テクスチャ拡大縮小時のアルゴリズム
    HRESULT hr;

    D3D11_SAMPLER_DESC smpDesc;

    ::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
    // 適用されるフィルター（アルゴリズム）の種類
    smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    hr =g_pD3D->Device->CreateSamplerState(&smpDesc, &(g_pD3D->Sampler));
    if (FAILED(hr)) {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "サンプラー作成失敗", "エラー", MB_OK | MB_ICONERROR);
    }
}

BOOL D3D_CreateBuffer(void)
{
    HRESULT hr;

    D3D11_BUFFER_DESC cbDesc;
    cbDesc.ByteWidth = sizeof(CONSTBUFFER);// 今から作る定数バッファのサイズ
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// 定数バッファ作成を指定
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;

    hr = g_pD3D->Device->CreateBuffer(&cbDesc, NULL, &g_ConstantBuffer);

    if (FAILED(hr)) {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "定数バッファ作成失敗", "エラー", MB_OK | MB_ICONERROR);
    }
    
}

BOOL D3D_CreateBlendState(void)
{
    HRESULT hr;
    // →透過処理や加算合成を可能にする色の合成方法
    //加算合成→エフェクトなどに使用する色が明るくなる合成方法
    D3D11_BLEND_DESC BlendState;
    ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
    BlendState.AlphaToCoverageEnable = FALSE;
    BlendState.IndependentBlendEnable = FALSE;
    BlendState.RenderTarget[0].BlendEnable = TRUE;
    BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;//背景色にかけ合わせる係数(透過)
    BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    
    //透過処理の設定を作る
    hr = g_pD3D->Device->CreateBlendState(&BlendState, &(g_pD3D->BlendAlpha));
    if (FAILED(hr)) {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "BlendStateAlpha Failed", "エラー", MB_OK | MB_ICONERROR);
    }


    //加算合成の設定を作る
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;//背景色にかけあわせる係数(加算)
    hr = g_pD3D->Device->CreateBlendState(&BlendState, &(g_pD3D->BlendAdd));
    if (FAILED(hr)) {
        return FALSE;
        //エラー表示
        MessageBoxA(NULL, "BlendStateAddictive Failed", "エラー", MB_OK | MB_ICONERROR);
    }
    
    //ブレンドステートの設定
    g_pD3D->Context->OMSetBlendState(g_pD3D->BlendAlpha, NULL, 0xffffffff);

}

void D3D_ClearScreen(void)
{
    // 画面塗りつぶし色
    float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //red,green,blue,alpha

    // 描画先のキャンバスと使用する深度バッファを指定する
    GetD3D_Context()->OMSetRenderTargets(1, &GetD3D_DATA()->RenderTarget, GetD3D_DATA()->DepthStencilView);
    // 描画先キャンバスを塗りつぶす
    GetD3D_Context()->ClearRenderTargetView(GetD3D_DATA()->RenderTarget, clearColor);
    // 深度バッファをリセットする
    GetD3D_Context()->ClearDepthStencilView(GetD3D_DATA()->DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    UINT strides = sizeof(VERTEX);
    UINT offsets = 0;
    GetD3D_Context()->IASetInputLayout(GetD3D_DATA()->InputLayout);


    GetD3D_Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    GetD3D_Context()->VSSetShader(GetD3D_DATA()->VertexShader, NULL, 0);
    GetD3D_Context()->RSSetViewports(1, &GetD3D_DATA()->Viewport);
    GetD3D_Context()->PSSetShader(GetD3D_DATA()->PixelShader, NULL, 0);

    // ピクセルシェーダーにサンプラーを渡す
    GetD3D_Context()->PSSetSamplers(0, 1, &GetD3D_DATA()->Sampler);

    // 定数バッファを頂点シェーダーにセットする
    GetD3D_Context()->VSSetConstantBuffers(0, 1, &g_ConstantBuffer);
    //定数バッファをピクセルシェーダーににセットする
    GetD3D_Context()->PSSetConstantBuffers(0, 1, &g_ConstantBuffer);


}

void D3D_Release(void)
{
	//POINTERメモリを解放
    SAFE_RELEASE(g_pD3D->Device);
    SAFE_RELEASE(g_pD3D->Context);
    SAFE_RELEASE(g_pD3D->SwapChain);
    SAFE_RELEASE(g_pD3D->RenderTarget);
    SAFE_RELEASE(g_pD3D->DepthStencilView);
    SAFE_RELEASE(g_pD3D->DepthStencilTexture);
    SAFE_RELEASE(g_pD3D->InputLayout);
    SAFE_RELEASE(g_pD3D->VertexShader);
    SAFE_RELEASE(g_pD3D->PixelShader);
    //SAFE_RELEASE(g_pD3D->Viewport);
    SAFE_RELEASE(g_pD3D->BlendAlpha);
    SAFE_RELEASE(g_pD3D->BlendAdd);
    SAFE_RELEASE(g_pD3D->Sampler);




	//malloc関数で確保したメモリを解放
	if (g_pD3D != NULL)
	{
		free(g_pD3D); //mallocで確保したメモリを解放する関数
		g_pD3D = NULL;
	}

}


