#pragma once
#include <vector>

enum DIR {
	
	UP,			//è„
	UPRIGHT,	//âEè„
	RIGHT,		//âE
	DOWNRIGHT,	//âEâ∫
	DOWN,		//â∫
	DOWNLEFT,	//ç∂â∫
	LEFT,		//ç∂
	UPLEFT,		//ç∂è„
	STILL = 99,		//ê√é~

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

