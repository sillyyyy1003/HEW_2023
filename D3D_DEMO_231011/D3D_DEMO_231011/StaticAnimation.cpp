#include "StaticAnimation.h"

StaticAnimation::StaticAnimation(int splitX, int splitY) :Animation(splitX, splitY)
{
<<<<<<< .merge_file_FEkagb
=======
	int num = splitX * splitY;

	//�A�j���V���̔z��
	for (int i = 0; i < num; i++) {
		animeTable.push_back(i);
	}

	//�z��̍Ō�
	animeTable.push_back(-1);


>>>>>>> .merge_file_6O7OTj
}

void StaticAnimation::Update(void)
{
<<<<<<< .merge_file_FEkagb
=======
	int animeID = animeTable[(int)m_animeCounter];

	if (isPlaying)
	{
		// �A�j���[�V�����̃J�E���^�[��i�߂�
		m_animeCounter += m_animeSpeed;

		//���[�v����ꍇ
		if (isLoop) {

			if (animeTable[(int)m_animeCounter] == -1) {
				m_animeCounter = 0.0f;
			}

		}//���[�v���Ȃ��ꍇ
		else {

			if (animeTable[(int)m_animeCounter] == -1) {
				m_animeCounter = 0.0f;
				isPlaying = false;
			}

		}
	}
	
	SetFrameX(animeID % m_split.x);
>>>>>>> .merge_file_6O7OTj
	Animation::Update();
}
