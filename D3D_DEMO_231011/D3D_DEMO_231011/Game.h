#pragma once
#include "Object.h"



class Game
{
private:

	Object* testObject;


public:
	Game();

	void Update(void);

	~Game();

	void Draw();
};

