#include "Sprite.h"
#include <vector>

class Effect :public Sprite {

private:
	//ループするかどうか？
	bool isLoop = false;

	//フレームの枚数
	int m_frameNum = 0;

	std::vector<int> animeTable;

	//表示するかどうか？
	bool isActive = false;

	//オブジェクトに付くかどうか
	bool isTrace = false;


public:

	Effect(int num);

	~Effect();

	void CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	void Update();

	void Draw() override;

	void SetActive(bool isActive) { this->isActive = isActive; };

	void SetLoop(bool isLoop);

	void SetTrace(bool isTrace) { this->isTrace = isTrace; };


};
