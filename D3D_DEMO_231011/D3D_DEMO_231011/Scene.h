#pragma once

enum SCENENAME {
	NONE,//何もない

	TITLE,//タイトル

	STAGESELECT,//ステージセレクト

	STAGE,//ステージ

	RESULT,//リザルト

};

enum STAGEINFO {
	STAGE1_1 = 0,
	STAGE1_2 = 1,
	STAGE1_3 = 2,

	STAGE2_1 = 3,
	STAGE2_2 = 4,
	STAGE2_3 = 5,

	STAGE3_1 = 6,
	STAGE3_2 = 7,
	STAGE3_3 = 8,

	STAGE_IDLE = 99,
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
	SCENENAME m_newScene;


	STAGEINFO m_stage;
	RESULTINFO m_result;

public:

	Scene(void);
	
	void SetScene(SCENENAME _scene) { m_scene = _scene; };
	SCENENAME GetScene() { return m_scene; };

	void SetNextScene(SCENENAME _next) { m_nextScene = _next; };
	SCENENAME GetNextScene() { return m_nextScene; };

	void SetNewScene(SCENENAME _new) { m_newScene = _new; };
	SCENENAME GetNewScene() { return m_newScene; };

	void SetStage(STAGEINFO _stage) { m_stage = _stage; };
	STAGEINFO GetStage() { return m_stage; };
	//次のステージを取得
	STAGEINFO GetNextStage();

	void SetResult(RESULTINFO _result) { m_result = _result; };
	RESULTINFO GetResult() { return m_result; };


};

