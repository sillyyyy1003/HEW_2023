#include "Sprite.h"

Sprite::Sprite(ID3D11ShaderResourceView* texture, float _width, float _height, float splitX, float splitY)
{
	

	const float left = -(_width / 2.0f); 
	const float right = _width / 2.0f;
	const float top = _height / 2.0f;;
	const float bottom = -(_height / 2.0f);
	const float z = 0.0f;

	const float u = 1.0 / splitX;
	const float v = 1.0 / splitY;
	

	VERTEX vertexList[] = {

		//頂点が時計回りに三角形を形成する側がポリゴンの表になる
		{left,	top,	z,0.0f,	0.0f},		//左上
		{right,	bottom,	z,u,	v},			//右下
		{left,	bottom,	z,0.0f,	v},			//左下
		
		{left,	top,	z,0.0f,	0.0f},		//左上
		{right,	top,	z,u,	0.0f},		//右上
		{right,	bottom,	z,u,	v},			//右下

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

void Sprite::Draw(void)
{

}
