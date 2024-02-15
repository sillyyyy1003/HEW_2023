#pragma once
#include"CanvasUI.h"

class Fade:public CanvasUI
{

public:
	Fade();
	~Fade();

	void Initialize();
	void Update();
	void Draw();

private:

	//ID3D11Device* m_device;
	//ID3D11DeviceContext* m_deviceContext;
	//ID3D11Buffer* m_vertexBuffer;
	//ID3D11VertexShader* m_vertexShader;
	//ID3D11PixelShader* m_pixelShader;
	//ID3D11InputLayout* m_inputLayout;

	//float m_currentFade;
	//float m_fadeDuration;

	//フェード状態
	enum FADE_STATE
	{
		NO_FADE,
		FADE_IN,
		FADE_OUT,
	};
	FADE_STATE fadeState = NO_FADE;




	

};

