#include "Sprite.h"
#include "Camera.h"
#include "Assets.h"

extern Assets* g_Assets;

Sprite::Sprite(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	//縦横分割を設定
	m_split=(XMINT2(splitX, splitY));

	//モデル頂点データ作成
	const float left = -(_width / 2.0f); 
	const float right = _width / 2.0f;
	const float top = _height / 2.0f;;
	const float bottom = -(_height / 2.0f);
	const float z = 0.0f;

	//割った後のテクスチャ、一枚ずつの大きさ（幅、高）
	const float u = 1.0 / m_split.x;
	const float v = 1.0 / m_split.y;

	VERTEX vertexList[] = {

		//頂点が時計回りに三角形を形成する側がポリゴンの表になる
		{left,	top,	z,	0.0f,	0.0f},		//左上
		{right,	bottom,	z,	u,		v},			//右下
		{left,	bottom,	z,	0.0f,	v},			//左下
		
		{left,	top,	z,	0.0f,	0.0f},		//左上
		{right,	top,	z,	u,		0.0f},		//右上
		{right,	bottom,	z,	u,		v},			//右下

	};

	// 頂点バッファを作成する
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// 確保するバッファサイズを指定
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 頂点バッファ作成を指定
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// VRAMに送るデータを指定
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr=GetD3D_Device()->CreateBuffer(&bufferDesc, &subResourceData, &(m_modelData.vertexBuffer));

	if (FAILED(hr)) {
		throw hr;
		MessageBoxA(NULL, "頂点バッファの作成失敗！", "エラー発生", MB_OK | MB_ICONERROR);
	}

	//テクスチャを実装
	SetTexture(texture);
}



void Sprite::GenerateMatrix(CONSTBUFFER& cb)
{
	//平行投影の行列作成
	XMMATRIX matrixProj = XMMatrixOrthographicLH(RATIO_W, RATIO_H, 0.0f, 3.0f);
	XMMATRIX matrixView = m_camera->GetMatrixView();
	matrixProj = matrixView * matrixProj;
	
	//ワールド変換行列の作成
	//移動行列
	XMMATRIX matrixMove = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	//拡大縮小行列
	XMMATRIX matrixScale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	//回転行列
	XMMATRIX matrixRotateX = XMMatrixRotationX(XMConvertToRadians(m_rotation.x));
	XMMATRIX matrixRotateY = XMMatrixRotationY(XMConvertToRadians(m_rotation.y));
	XMMATRIX matrixRotateZ = XMMatrixRotationZ(XMConvertToRadians(m_rotation.z));
	XMMATRIX matrixRotate = matrixRotateX * matrixRotateY * matrixRotateZ;
	XMMATRIX matrixWorld = matrixScale * matrixRotate * matrixMove;

	//UVアニメーション行列作成
	m_anime->Update();
	XMMATRIX matrixTex = XMMatrixTranslation(m_anime->GetUVOffset().x, m_anime->GetUVOffset().y, 0.0f);

	cb.matrixProj = XMMatrixTranspose(matrixProj);
	cb.matrixTex = XMMatrixTranspose(matrixTex);
	cb.matrixWorld = XMMatrixTranspose(matrixWorld);
	//マテリアル色を定数バッファデータに代入
	cb.materialDiffuse = m_materialDiffuse;
}



void Sprite::Draw(void)
{
	UINT strides = sizeof(VERTEX);
	UINT offsets = 0;

	//行列作成
	CONSTBUFFER cb;
	GenerateMatrix(cb);

	//行列をシェーダーに渡す
	GetD3D_Context()->UpdateSubresource(g_ConstantBuffer, 0, NULL, &cb, 0, 0);

	//描画する頂点バッファ(モデル)を指定する
	GetD3D_Context()->IASetVertexBuffers(0, 1, &Material::m_modelData.vertexBuffer, &strides, &offsets);

	//ピクセルシェーダーにテクスチャを渡す
	GetD3D_Context()->PSSetShaderResources(0, 1, &Material::m_modelData.texture);

	//vertexCount:描画する頂点数
	GetD3D_Context()->Draw(6, 0);


}




