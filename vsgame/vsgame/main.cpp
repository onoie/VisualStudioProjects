#include <DxLib.h>
int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC ,int nC){
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1){
		return 1;
	}
	//DrawBox(0, 0, 120, 120, 0x00FFF, TRUE);
	//WaitKey();
	//DxLib_End();
	
	//int ghandle = LoadGraph("media\\smp1_chara01.png");
	//DrawGraph(0, 0, ghandle, TRUE);
	//WaitKey();
	//DxLib_End();

	int ghandle = LoadGraph("media\\smp1_chara01.png");
	int x = 0,y=0;

	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		ClearDrawScreen();
		int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (key& PAD_INPUT_UP){ y -= 4; }
		if (key& PAD_INPUT_DOWN){ y += 4; }
		if (key& PAD_INPUT_LEFT){ x -= 4; }
		if (key& PAD_INPUT_RIGHT){ x += 4; }
		DrawGraph(x,y, ghandle, TRUE);
		ScreenFlip();
	}
	
	SetDrawScreen(DX_SCREEN_FRONT);
	ClearDrawScreen();
	DrawGraph(0, 0, ghandle, TRUE);
	ScreenFlip();

	WaitKey();

	DxLib_End();

	return 0;
}