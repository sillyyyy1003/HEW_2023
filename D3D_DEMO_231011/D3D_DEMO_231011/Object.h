#pragma once
#include "Sprite.h"

//ﾂオﾂブﾂジﾂェﾂクﾂトﾂ甘ｮﾂ墜�
class Object
{
public:
	//----------------------------//
	// ﾂ米篠青�
	//----------------------------//
	//ﾂ図ﾂ形ﾂ湘ｮﾂ頁�ﾂて堕案ｾﾂづｭﾂて卍づ�ﾂね伉づｩ
	Sprite* m_sprite;



public:
	
	/// <summary>
	/// ﾂコﾂδ督スﾂトﾂδ可クﾂタﾂ�ﾂ�ﾂ渉可甘ｺﾂ嫁･ﾂ行ﾂつ､
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="_width">width</param>
	/// <param name="_height">height</param>
	/// <param name="splitX"></param>
	/// <param name="splitY"></param>
	Object(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//ﾂアﾂニﾂδ�ﾂーﾂシﾂδ�ﾂδ督て堋更ﾂ新ﾂて堕行ﾂつ､
	virtual void Update(void);

	void Draw(void);
	
	// ﾂ米青付ﾂでｻﾂ渉按猟�
	~Object(void);
};

