#pragma once

enum SCENENAME {
	NONE,

	TITLE,

	STAGESELECT,

	STAGE,

	RESULT,

};

enum STAGEINFO {
	STAGE1_1,
	STAGE1_2,
	STAGE1_3,

	STAGE2_1,
	STAGE2_2,
	STAGE2_3,

	STAGE3_1,
	STAGE3_2,
	STAGE3_3,
};

enum RESULTINFO {

	RESULT1_1,
	RESULT1_2,
	RESULT1_3,

	RESULT2_1,
	RESULT2_2,
	RESULT2_3,

	RESULT3_1,
	RESULT3_2,
	RESULT3_3,
};

class Scene
{
private:

	SCENENAME m_scene;
	SCENENAME m_nextScene;

	STAGEINFO m_stage;
	RESULTINFO m_result;

public:

	Scene(void);
	
	void SetScene(SCENENAME _scene) { m_scene = _scene; };
	SCENENAME GetScene() { return m_scene; };

	void SetNextScene(SCENENAME _next) { m_nextScene = _next; };
	SCENENAME GetNexScene() { return m_nextScene; };

	void SetStage(STAGEINFO _stage) { m_stage = _stage; };
	STAGEINFO GetStage() { return m_stage; };

	void SetResult(RESULTINFO _result) { m_result = _result; };
	RESULTINFO GetResult() { return m_result; };

};

