#include <DxLib.h>

//enum
enum GameState{
	GAME_TITLE, GAME_MAIN,
	GAME_CLEAR, GAME_OVER
};

//global
int g_timerstart;
int g_lasttime = 0;
float g_frametime = 0;
GameState g_gamestate = GAME_TITLE;
int g_gametitleimg;
int g_heroimg;
float g_hx = 0, g_hy = 0;
BOOL g_akey_prev;
int g_middlefont;
int g_largefont;
//prototype
void DrarGameTitle();
void DrarGameMain();
void DrarGameClear();
void DrarGameOver();
BOOL IsAKeyTrigger(int key);
//main
int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC ,int nC){
	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 32);
	if (DxLib_Init() == -1){
		return 1;
	}
	//load
	g_gametitleimg = LoadGraph("media\\smp1_title.png");
	g_heroimg = LoadGraph("media\\smp1_chara01.png");
	g_middlefont = CreateFontToHandle("メイリオ", 42,-1, DX_FONTTYPE_ANTIALIASING);
	g_largefont= CreateFontToHandle("メイリオ", 90, -1, DX_FONTTYPE_ANTIALIASING);
	SetDrawScreen(DX_SCREEN_BACK);
	g_lasttime = GetNowCount();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		int curtime = GetNowCount();
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;
		ClearDrawScreen();
		switch (g_gamestate){
			case GAME_TITLE:
				DrarGameTitle();
				break;
			case GAME_MAIN:
				DrarGameMain();
				break;
			case GAME_CLEAR:
				DrarGameClear();
				break;
			case GAME_OVER:
				DrarGameOver();
				break;
		}
		ScreenFlip();
	}
	WaitKey();
	DxLib_End();
	return 0;
}


//タイトル画面描画
void DrarGameTitle(){
	DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), TRUE);
	DrawGraph(0, 0, g_gametitleimg, TRUE);
	DrawStringToHandle(100, 400, "Zキーでゲームスタート",GetColor(255, 0, 255), g_middlefont);
	DrawStringToHandle(100, 460, "カーソルキーで上下左右に移動",GetColor(0, 0, 0), g_middlefont);

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (IsAKeyTrigger(key) == TRUE) {
		g_gamestate = GAME_MAIN;
	}
}
//ゲーム本編描画
void DrarGameMain(){
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	float mv = 80.0f * g_frametime;
	if (key& PAD_INPUT_UP){ g_hy -= mv; }
	if (key& PAD_INPUT_DOWN){ g_hy += mv; }
	if (key& PAD_INPUT_LEFT){ g_hx -= mv; }
	if (key& PAD_INPUT_RIGHT){ g_hx += mv; }
	DrawGraph(g_hx, g_hy, g_heroimg, TRUE);
	if (IsAKeyTrigger(key) == TRUE){
		g_gamestate = GAME_OVER;
		g_timerstart = g_lasttime;//timer
	}
	//forDebug
	clsDx();
	printfDx("%d:%f:%f", g_lasttime, g_frametime, mv);
}
//ゲームクリア画面描画
void DrarGameClear(){
}
//ゲームオーバー画面描画
void DrarGameOver(){
	DrawStringToHandle(100, 200, "ゲームオーバー",GetColor(255, 0, 0), g_largefont);
	if (g_lasttime - g_timerstart > 5000) { 
		g_gamestate = GAME_TITLE;
	}
}
//キートリガー処理
BOOL IsAKeyTrigger(int key){
	if (key & PAD_INPUT_A){
		if (g_akey_prev == FALSE){
			g_akey_prev = TRUE;
			return TRUE;
		}
	}
	else {
		g_akey_prev = FALSE;
	}
	return FALSE;
}