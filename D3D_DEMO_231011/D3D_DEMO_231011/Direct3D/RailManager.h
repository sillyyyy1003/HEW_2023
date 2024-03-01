#pragma once
#include <vector>

enum DIR {
	
	UP,			//��
	UPRIGHT,	//�E��
	RIGHT,		//�E
	DOWNRIGHT,	//�E��
	DOWN,		//��
	DOWNLEFT,	//����
	LEFT,		//��
	UPLEFT,		//����
	STILL = 99,		//�Î~

};

struct PointInfo {
	bool isVacant;
	bool isMoveable[8];
};


class RailManager
{
public:

	//std::vector<PointInfo> m_info[15];
	PointInfo m_info [15];

	//std::vector <RailPos> m_autoMove;

private:

	RailManager() {};

	~RailManager();


public:
	static RailManager* Get();

	void InitRail();

	void InitRailPos(void);

};

