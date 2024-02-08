#include "Sprite.h"

class Effect :public Sprite {

private:
	//���[�v���邩�ǂ����H
	bool isLoop = false;

	//�t���[���̖���
	int m_frameNum = 0;

	int* animeTable;
	
	//�\�����邩�ǂ����H
	bool isActive = false;

public:

	Effect(int num);

	~Effect();

	void CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	void Update();
	
	void Draw() override;

	void SetActive(bool isActive) { this->isActive = isActive; };
	
	void SetLoop(bool isLoop);


};
