﻿#undef UNICODE  //Unicodeではなく、マルチバイト文字を使う
#include <Windows.h>
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "TrackCamera.h"
#include "Game.h"
#include "KBInput.h"

#define CLASS_NAME		"HEW_DEMO"		//ウインドウクラスの名前
#define WINDOW_NAME		"GAME_TITLE"	//ウィンドウの名前

#define SCREEN_WIDTH	(1280)	// ウインドウの幅
#define SCREEN_HEIGHT	(720)	// ウインドウの高さ

#define FPS_DATA		(60)


//----------------------------//
// グローバル変数定義
//----------------------------//
Assets* g_Assets;

Camera* g_WorldCamera;

Game* g_Game;

KBInput* g_KbInput = new KBInput();


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// エントリポイント＝一番最初に実行される関数
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
	//ウインドウクラスの名前を変更
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd;
	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,// ウィンドウスタイル
		CW_USEDEFAULT,// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,// ウィンドウの左上Ｙ座標 
		SCREEN_WIDTH,// ウィンドウの幅
		SCREEN_HEIGHT,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, nCmdShow);

	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);
	
	//----------------------------//
	// 	ゲームループに入る前に
	//----------------------------//

	// DirectXの初期化処理
	DirectXInit(hWnd);

	//アセットの初期化
	g_Assets = new Assets();

	//カメラの初期化
	g_WorldCamera = new TrackCamera();
	
	//ゲームクラスの初期化処理
	g_Game = new Game();

	//ブラッシュアップ頻度(fps処理)
	// FPS表示用変数
	int fpsCounter = 0;
	long long oldTick = GetTickCount64();//現在時間を保存
	long long nowTick = oldTick; // 現在時間取得用

	// FPS固定用変数
	LARGE_INTEGER liWork; // 関数から値を受け取る用
	long long frequency; // 計測精度
	// 計測精度を取得
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart; // １秒あたりの解像度が入る
	// １フレームあたりのカウント値を計算
	long long numCount_1frame = frequency / FPS_DATA; //FPSの値を変更する
	// 現在時間（単位：カウント）を取得
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;
	long long nowCount = oldCount;

	MSG msg;

	// ゲームループ
	for (;;)
	{
		BOOL isAnyMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (isAnyMessage)// 何かメッセージがあるか判定
		{
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			//現在時間を取得（単位：カウント）
			QueryPerformanceCounter(&liWork);
			nowCount = liWork.QuadPart; 

			//1/60秒経過したか？
			if (nowCount >= oldCount + numCount_1frame)
			{

				//----------------------------//
				// 	ゲームループ 
				//----------------------------//
				g_WorldCamera->Update();

				g_Game->GameUpdate();

				g_Game->GameDraw();

				g_KbInput->Update();

				//----------------------------//
				// 	FPSブラッシュアップ
				//----------------------------//
				fpsCounter++; // ゲームループ実行回数をカウント＋１
				oldCount = nowCount;
			}

			//現在時間取得
			nowTick = GetTickCount64(); 

			//１秒経過したか？
			if (nowTick >= oldTick + 1000)
			{
				fpsCounter = 0;
				oldTick = nowTick;
			}

		}
	} 

	//----------------------------//
	// ゲームクラスの終了処理
	//----------------------------//

	//アセット解放処理
	delete g_Assets;
	//カメラ解放処理
	delete g_WorldCamera;
	//ゲームの解放処理
	delete g_Game;
	//Direct3D解放処理
	D3D_Release();
	//入力解放処理
	delete g_KbInput;


	//----------------------------//
	// ウィンドウズの終了処理
	//----------------------------//

	UnregisterClass(CLASS_NAME, hInstance);

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg) 
	{
	case WM_DESTROY:		//ウィンドウ破棄のメッセージ
		PostQuitMessage(0);	//アプリ終了
		break;

	case WM_CLOSE:			//ｘボタンが押されたら
		DestroyWindow(hWnd);//
		break;

	case WM_LBUTTONDOWN:	// 左クリックされた時

		break;

	case WM_RBUTTONDOWN:	// 右クリックされた時
		
		break;

	case WM_MOUSEMOVE:		// マウスカーソルが動いた時
		
		break;

	case WM_KEYDOWN:		// キーが押された時
		g_KbInput->SetKeyDownState(wParam);
		break;

	case WM_KEYUP:			// キーが離された時
		g_KbInput->SetKeyUpState(wParam);
		break;

	default:				// 上のcase以外の場合の処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;

	}

	return 0;
}

