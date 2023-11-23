#pragma once
#include "Sprite.h"

class ShadowObject
{
public:
	//----------------------------//
	// •Ï”
	//----------------------------//
	
	Sprite* m_obj;

	bool isActive = false;

	
	
	
public:
	//Constructor
	ShadowObject(void);

	//‰e‚Ìƒ‚ƒfƒ‹ì¬
	void CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//
	void Update(void);

	BOOL CheckShadow(void);

	//•`‰æŠÖ”
	void Draw(void);

	~ShadowObject(void);

};

