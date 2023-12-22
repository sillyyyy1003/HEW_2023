#pragma once


class GameObject;
class TestObject;
class Object;
class CanvasUI;
class StaticObject;

class Game
{
private:
	enum GAMESCENE
	{
		TITLE,		//タイトル
		STAGE1,		//ゲームシーン
		RESULT,		//リザルトシーン
	};

	GAMESCENE m_gameScene = TITLE;

	//const double M_PI = 3.14159265358979323846;
private:

	GameObject* testTree;

private:
	//コンストラクタ&デストラクタ
	Game() {};
	~Game();

public:
	//唯一のインスタンスを返す関数
	static Game* Get();

	//初期化を行う関数
	void Init();

	//ゲーム本体
	void GameUpdate(void);
	void TitleUpdate(void);
	void StageUpdate(void);
	void ResultUpdate(void);

	//描画
	void GameDraw(void);
	void TitleDraw(void);
	void StageDraw(void);
	void ResultDraw(void);

	// �����蔻��
	// �~�Ɖ~���m�̓����蔻��
	int CircleHit(BOUNDING_CIRCLE bc1, BOUNDING_CIRCLE bc2);

	// �l�p�`�Ɖ~�̓����蔻��
	int SqureandCircle(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj);
	// �l�p�`�Ɖ~�̓����蔻���Ɏg���֐�
	bool CheckHit(const BOX& t_box, const BOUNDING_CIRCLE bc1);

	// �l�p�`���m�̓����蔻��
	int SqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	// �I�u�W�F�N�g���m�����̂������֐�
	void CombineObjects(int HitNum, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj2);

	void CombineTriangleObjects(int HitNum, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	// �㉺���E�ŕʂ̓����蔻�����Ƃ邽�߂̊֐�
	int SideCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2);

	int SqureCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	bool CheckSqureHit(const BOX& t_box, const BOX& t_box2);

	SQUREBOX Squre(BOUNDING_CIRCLE circle2, TestObject* testObj);

	std::vector<Vector2> SetTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2);

	std::vector<Vector2> SetSqureWithTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2, float width);

	SQURE SetCircleWithTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2, float width);

	// �_���O�p�`���ɂ��邩�ǂ����𔻒肷���֐�
	bool isPointInTriangle(Point A, Point B, Point C, Point P);

	int CheckTriangleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	int CheckTriangleAndCircleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	int CheckTriangleAndSqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	bool TriangleAndCircleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	bool TriangleAndSqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	bool TriangleHit(TestObject* testObj, TestObject* testObj2);

	void InitialPolygonSAT(BOUNDING_CIRCLE circle1, TestObject* testObj, float rotation);

	std::vector<Vector2> InitialPolygonSATvertices(BOUNDING_CIRCLE circle1, std::vector<Vector2> vertices, float rotation);

	//�@���ׂĂ̓����蔻�����Ǘ�����
	void TestCollision();

	//�V�[�����ݒ肷��
	void SetGameScene(GAMESCENE scene);

	DirectX::XMFLOAT3 p_center; // ���S�_�̍��W
};

