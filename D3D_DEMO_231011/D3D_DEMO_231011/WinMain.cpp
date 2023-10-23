#undef UNICODE  //Unicode�ł͂Ȃ��A�}���`�o�C�g�������g��
#include <Windows.h>
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "TrackCamera.h"
#include "Game.h"

#define CLASS_NAME		"HEW_DEMO"		//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"GAME_TITLE"	//�E�B���h�E�̖��O

#define SCREEN_WIDTH (1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)	// �E�C���h�E�̍���


//----------------------------//
// �O���[�o���ϐ���`
//----------------------------//
Assets* g_Assets;

Camera* g_WorldCamera;

Game* g_Game;


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �G���g���|�C���g����ԍŏ��Ɏ��s�����֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	//�E�C���h�E�N���X�̖��O��ύX
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd;
	hWnd = CreateWindowEx(0,// �g���E�B���h�E�X�^�C��
		CLASS_NAME,// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,// �E�B���h�E�̍���x���W 
		SCREEN_WIDTH,// �E�B���h�E�̕�
		SCREEN_HEIGHT,// �E�B���h�E�̍���
		NULL,// �e�E�B���h�E�̃n���h��
		NULL,// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,// �C���X�^���X�n���h��
		NULL);// �E�B���h�E�쐬�f�[�^

	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	ShowWindow(hWnd, nCmdShow);

	// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
	UpdateWindow(hWnd);

	// �Q�[�����[�v�ɓ���O��
	//----------------------------//
	// DirectX�̏���������
	//----------------------------//
	DirectXInit(hWnd);

	//�A�Z�b�g�̏�����
	g_Assets = new Assets();

	//g_WorldCamera = new TrackCamera();
	g_WorldCamera = new Camera();

	//----------------------------//
	// 	�Q�[���N���X�̏���������
	//----------------------------//
	g_Game = new Game();

	MSG msg;

	// �Q�[�����[�v
	for (;;)
	{
		BOOL isAnyMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (isAnyMessage)// �������b�Z�[�W�����邩����
		{
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{


			//----------------------------//
			// 	�Q�[�����[�v 
			//----------------------------//
			g_WorldCamera->Update();

			g_Game->Update();

			g_Game->Draw();

		}
	} 

	//----------------------------//
	// �Q�[���N���X�̏I������
	//----------------------------//


	//�A�Z�b�g�������
	delete g_Assets;

	delete g_WorldCamera;

	delete g_Game;

	//Direct3D�������
	D3D_Release();

	//----------------------------//
	// �E�B���h�E�Y�̏I������
	//----------------------------//

	UnregisterClass(CLASS_NAME, hInstance);

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
	case WM_DESTROY:		//�E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);	//�A�v���I��
		break;

	case WM_CLOSE:			//���{�^���������ꂽ��
		DestroyWindow(hWnd);//
		break;

	case WM_LBUTTONDOWN:	// ���N���b�N���ꂽ��
		
		break;

	case WM_RBUTTONDOWN:	// �E�N���b�N���ꂽ��
		
		break;

	case WM_MOUSEMOVE:		// �}�E�X�J�[�\������������
		
		break;

	case WM_KEYDOWN:		// �L�[�������ꂽ��
		
		break;

	case WM_KEYUP:			// �L�[�������ꂽ��

		break;

	default:				// ���case�ȊO�̏ꍇ�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;

	}

	return 0;
}