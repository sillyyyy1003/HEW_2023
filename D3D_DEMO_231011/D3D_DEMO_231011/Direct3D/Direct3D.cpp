#include "Direct3D.h"
#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"
#include <atltypes.h>		// CRect���g�����߂̃w�b�_�[�t�@�C��
#include "../Sprite.h"

// ���C�u�����̃����N�ݒ�
#pragma comment (lib, "d3d11.lib")

//----------------------------//
// �O���[�o���ϐ���`
//----------------------------//
static D3D_DATA* g_pD3D;        //DirectX�̋@�\���܂߂��\����
static UINT g_ScreenWidth;      //��ʂ̕�
static UINT g_ScreenHeight;     //��ʂ̍���
ID3D11Buffer* g_ConstantBuffer; //�萔�o�b�t�@�p�ϐ�


D3D_DATA* GetD3D_DATA(void) { return g_pD3D; }

ID3D11Device* GetD3D_Device(void){ return g_pD3D->Device; }

ID3D11DeviceContext* GetD3D_Context(void){ return g_pD3D->Context; }

ID3D11BlendState* GetBlendAlpha(void){ return g_pD3D->BlendAlpha; }

ID3D11BlendState* GetBlendAdd(void){ return g_pD3D->BlendAdd;}




void DirectXInit(HWND hWnd)
{
    //�������m��
    g_pD3D = (D3D_DATA*)malloc(sizeof(D3D_DATA));

    ZeroMemory(g_pD3D, sizeof(D3D_DATA));

    //�f�o�C�X�쐬�֐����Ăяo��
    D3D_CreateDevice(hWnd);

    //�[�x�o�b�t�@�쐬�֐����Ăяo��
    D3D_CreateDepthStencil();

    //�����_�[�^�[�Q�b�g�쐬�֐����Ăяo��
    D3D_CreateRenderTarget();

    //�V�F�[�_�[�쐬�֐����Ăяo��
    D3D_CreateShader();

    //�r���[�|�[�g�ݒ�֐����Ăяo��
    D3D_SetViewPort();

    //�T���v���[�쐬�֐����Ăяo��
    D3D_CreateSampler();

    //�萔�o�b�t�@�쐬�֐����Ăяo��
    D3D_CreateBuffer();

    //�u�����h�X�e�[�g�쐬�֐����Ăяo��
    D3D_CreateBlendState();

}


BOOL D3D_CreateDevice(HWND hwnd)
{
	//HRESULT�^�E�E�EWindows�v���O�����Ŋ֐����s�̐���/���s���󂯎��
    HRESULT  hr;


    UINT flags = 0;

    CRect                rect;
    //�E�C���h�E�̃N���C�A���g�̈�i���ۂɕ`��ł���͈́j�̃T�C�Y���擾
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

    // �f�o�C�X�ƃX���b�v�`�F�C���𓯎��ɍ쐬����֐��̌Ăяo��
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

    if (FAILED(hr)) // ��̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N
    {
        return FALSE;
        //�G���[�\��
        MessageBoxA(NULL,"�f�o�C�X�쐬���s", "�G���[",MB_OK | MB_ICONERROR);
    }

}

BOOL D3D_CreateRenderTarget(void)
{
    HRESULT hr;
    ID3D11Texture2D* pBackBuffer;

    //�o�b�t�@���擾
    hr = g_pD3D->SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);


    if (FAILED(hr))
    {
        //�擾���s�����ꍇ
        return FALSE;
        //�G���[�\��
        MessageBoxA(NULL, "�o�b�t�@�擾���s", "�G���[", MB_OK | MB_ICONERROR);
    }
    else
    {
        // �����_�[�^�[�Q�b�g���쐬����֐����Ăяo��
        hr = g_pD3D->Device->CreateRenderTargetView(pBackBuffer, NULL, &g_pD3D->RenderTarget);
        pBackBuffer->Release();

        if (FAILED(hr)) {
            return FALSE;
            //�G���[�\��
            MessageBoxA(NULL, "�����_�[�^�[�Q�b�g�쐬���s", "�G���[", MB_OK | MB_ICONERROR);
        }
    }

}

BOOL D3D_CreateDepthStencil(void)
{
    HRESULT hr;

    // �[�x�X�e���V���o�b�t�@���쐬
    // ���[�x�o�b�t�@�iZ�o�b�t�@�j�����s�𔻒肵�đO��֌W�𐳂����`��ł���

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
        //�G���[�\��
        return FALSE;
        MessageBoxA(NULL, "CreateTexture2d Fail", "�G���[", MB_OK | MB_ICONERROR);
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
            //�G���[�\��
            MessageBoxA(NULL, "�[�x�X�e���V���o�b�t�@�쐬���s", "�G���[", MB_OK | MB_ICONERROR);
        }
    }   
}


BOOL D3D_CreateShader(void)
{
    HRESULT hr;
    //���_�V�F�[�_�[�쐬
    hr = g_pD3D->Device->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &(g_pD3D->VertexShader));
    if (FAILED(hr))
    {
        return FALSE;
        //�G���[�\��
        MessageBoxA(NULL, "���_�V�F�[�_�[�쐬���s", "�G���[", MB_OK | MB_ICONERROR);
    }
    else
    {
        //�s�N�Z���V�F�[�_�[�쐬
        hr = g_pD3D->Device->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &(g_pD3D->PixelShader));

        if (FAILED(hr)) {
            return FALSE;
            //�G���[�\��
            MessageBoxA(NULL, "�s�N�Z���V�F�[�_�[�쐬���s", "�G���[", MB_OK | MB_ICONERROR);
        }
        else {
            //���_�P������ɂǂ�ȃf�[�^���܂܂�邩��Direct3D�ɋ�����
            D3D11_INPUT_ELEMENT_DESC vertexDesc[]
            {
                // �ʒu���W������Ƃ������Ƃ�`����
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA, 0 },

                // UV���W������Ƃ������Ƃ�`����
                { "TEX",    0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                
                //�ǉ���񂱂��Ɂ�
            };

            //�C���v�b�g���C�A�E�g�쐬
            hr = g_pD3D->Device->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), g_vs_main, sizeof(g_vs_main), &(g_pD3D->InputLayout));
            if (FAILED(hr))
            {
                return FALSE;
                //�G���[�\��
                MessageBoxA(NULL, "�C���v�b�g���C�A�E�g�쐬���s", "�G���[", MB_OK | MB_ICONERROR);
            }

        }
    }
   

}

void D3D_SetViewPort(void)
{
   
   //��ʕ����ȂǂɎg���A�`��̈�̎w��̂���
   g_pD3D->Viewport.TopLeftX = 0;
   g_pD3D->Viewport.TopLeftY = 0;
   g_pD3D->Viewport.Width = g_ScreenWidth;
   g_pD3D->Viewport.Height = g_ScreenHeight;
   g_pD3D->Viewport.MinDepth = 0.0f;
   g_pD3D->Viewport.MaxDepth = 1.0f;
}

BOOL D3D_CreateSampler(void)
{
    //�e�N�X�`���g��k�����̃A���S���Y��
    HRESULT hr;

    D3D11_SAMPLER_DESC smpDesc;

    ::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
    // �K�p�����t�B���^�[�i�A���S���Y���j�̎��
    smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    hr =g_pD3D->Device->CreateSamplerState(&smpDesc, &(g_pD3D->Sampler));
    if (FAILED(hr)) {
        return FALSE;
        //�G���[�\��
        MessageBoxA(NULL, "�T���v���[�쐬���s", "�G���[", MB_OK | MB_ICONERROR);
    }
}

BOOL D3D_CreateBuffer(void)
{
    HRESULT hr;

    D3D11_BUFFER_DESC cbDesc;
    cbDesc.ByteWidth = sizeof(CONSTBUFFER);// ��������萔�o�b�t�@�̃T�C�Y
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// �萔�o�b�t�@�쐬���w��
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;

    hr = g_pD3D->Device->CreateBuffer(&cbDesc, NULL, &g_ConstantBuffer);

    if (FAILED(hr)) {
        return FALSE;
        //�G���[�\��
        MessageBoxA(NULL, "�萔�o�b�t�@�쐬���s", "�G���[", MB_OK | MB_ICONERROR);
    }
    
}

BOOL D3D_CreateBlendState(void)
{
    HRESULT hr;
    // �����ߏ�������Z�������\�ɂ���F�̍������@
    //���Z�������G�t�F�N�g�ȂǂɎg�p����F�����邭�Ȃ鍇�����@
    D3D11_BLEND_DESC BlendState;
    ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
    BlendState.AlphaToCoverageEnable = FALSE;
    BlendState.IndependentBlendEnable = FALSE;
    BlendState.RenderTarget[0].BlendEnable = TRUE;
    BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;//�w�i�F�ɂ������킹��W��(����)
    BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    
    //���ߏ����̐ݒ�����
    hr = g_pD3D->Device->CreateBlendState(&BlendState, &(g_pD3D->BlendAlpha));
    if (FAILED(hr)) {
        return FALSE;
        //�G���[�\��
        MessageBoxA(NULL, "BlendStateAlpha Failed", "�G���[", MB_OK | MB_ICONERROR);
    }


    //���Z�����̐ݒ�����
    BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;//�w�i�F�ɂ������킹��W��(���Z)
    hr = g_pD3D->Device->CreateBlendState(&BlendState, &(g_pD3D->BlendAdd));
    if (FAILED(hr)) {
        return FALSE;
        //�G���[�\��
        MessageBoxA(NULL, "BlendStateAddictive Failed", "�G���[", MB_OK | MB_ICONERROR);
    }
    
    //�u�����h�X�e�[�g�̐ݒ�
    g_pD3D->Context->OMSetBlendState(g_pD3D->BlendAlpha, NULL, 0xffffffff);

}

void D3D_ClearScreen(void)
{
    // ��ʓh��Ԃ��F
    float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //red,green,blue,alpha

    // �`���̃L�����o�X�Ǝg�p����[�x�o�b�t�@���w�肷��
    GetD3D_Context()->OMSetRenderTargets(1, &GetD3D_DATA()->RenderTarget, GetD3D_DATA()->DepthStencilView);
    // �`���L�����o�X��h��Ԃ�
    GetD3D_Context()->ClearRenderTargetView(GetD3D_DATA()->RenderTarget, clearColor);
    // �[�x�o�b�t�@�����Z�b�g����
    GetD3D_Context()->ClearDepthStencilView(GetD3D_DATA()->DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    UINT strides = sizeof(VERTEX);
    UINT offsets = 0;
    GetD3D_Context()->IASetInputLayout(GetD3D_DATA()->InputLayout);


    GetD3D_Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    GetD3D_Context()->VSSetShader(GetD3D_DATA()->VertexShader, NULL, 0);
    GetD3D_Context()->RSSetViewports(1, &GetD3D_DATA()->Viewport);
    GetD3D_Context()->PSSetShader(GetD3D_DATA()->PixelShader, NULL, 0);

    // �s�N�Z���V�F�[�_�[�ɃT���v���[��n��
    GetD3D_Context()->PSSetSamplers(0, 1, &GetD3D_DATA()->Sampler);

    // �萔�o�b�t�@�𒸓_�V�F�[�_�[�ɃZ�b�g����
    GetD3D_Context()->VSSetConstantBuffers(0, 1, &g_ConstantBuffer);
    //�萔�o�b�t�@���s�N�Z���V�F�[�_�[�ɂɃZ�b�g����
    GetD3D_Context()->PSSetConstantBuffers(0, 1, &g_ConstantBuffer);


}

void D3D_Release(void)
{
	//POINTER�����������
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




	//malloc�֐��Ŋm�ۂ��������������
	if (g_pD3D != NULL)
	{
		free(g_pD3D); //malloc�Ŋm�ۂ������������������֐�
		g_pD3D = NULL;
	}

}


