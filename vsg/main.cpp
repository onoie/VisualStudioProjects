#include <DxLib.h>

//�O���[�o���ϐ�
//���Ԍv���p�ϐ�
int g_lasttime = 0;		//���O�̌v������
float g_frametime = 0;	//1���[�v�ɂ�����������
int g_timerstart;		//�^�C�}�[�p�ϐ�
enum GameState{			//�Q�[�����
	GAME_TITLE, GAME_MAIN,
	GAME_CLEAR, GAME_OVER
};
GameState g_gamestate = GAME_TITLE;
int g_gametitleimg;			//�^�C�g���C���[�W
int g_heroimg;				//�摜
float g_hx = 0, g_hy = 0;	//���W
//�{�^��
BOOL g_akey_prev;			//���O��A�{�^���̏��
//�t�H���g
int g_middlefont;			//���T�C�Y�t�H���g�n���h��
int g_largefont;			//��T�C�Y�t�H���g�n���h��

//�֐��v���g�^�C�v�錾
void DrawGameTitle();
void DrawGameMain();
void DrawGameClear();
void DrawGameOver();
BOOL IsAKeyTrigger(int key);

int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC, int nC){
	//�E�B���h�E���[�h�ɂ���
	ChangeWindowMode(TRUE);
	//�E�B���h�E�T�C�Y��ύX����
	SetGraphMode(800, 600, 32);
	//DX���C�u����������
	if (DxLib_Init() == -1) return -1;

	//�摜��ǂݍ���
	g_gametitleimg = LoadGraph("media\\smp1_title.png");
	g_heroimg = LoadGraph("media\\smp1_chara01.png");
	g_middlefont = CreateFontToHandle("���C���I", 42, -1, DX_FONTTYPE_ANTIALIASING);
	g_largefont = CreateFontToHandle("���C���I", 90, -1, DX_FONTTYPE_ANTIALIASING);

	SetDrawScreen(DX_SCREEN_BACK);
	g_lasttime = GetNowCount() & INT_MAX;	//���ݎ����̋L�^
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		//1���[�v�ɂ����������Ԃ��v��
		int curtime = GetNowCount();
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;

		ClearDrawScreen();
		//��ʕ`��֐��ɐ؂�ւ�
		switch (g_gamestate)
		{
		case GAME_TITLE:
			DrawGameTitle();
			break;
		case GAME_MAIN:
			DrawGameMain();
			break;
		case GAME_CLEAR:
			DrawGameClear();
			break;
		case GAME_OVER:
			DrawGameOver();
			break;
		default:
			break;
		}
		ScreenFlip();
	}

	//�ҋ@
	WaitKey();
	//DX���C�u�����̏I������
	DxLib_End();
	return 0;
}

//�^�C�g����ʕ`��
void DrawGameTitle(){
	DrawBox(0, 0, 800, 600, GetColor(255, 255, 255), TRUE);
	DrawGraph(0, 0, g_gametitleimg, TRUE);
	//�e�L�X�g�\��
	DrawStringToHandle(100, 400, "Z�L�[�ŃQ�[���X�^�[�g",
		GetColor(255, 0, 255), g_middlefont);
	DrawStringToHandle(100, 460, "�J�[�\���L�[�ŏ㉺���E�Ɉړ�",
		GetColor(0, 0, 0), g_middlefont);
	//�L�[���`�F�b�N���ĉ�ʂ�؂�ւ�
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (IsAKeyTrigger(key) == TRUE) g_gamestate = GAME_MAIN;
}
//�Q�[���{�ҕ`��
void DrawGameMain(){
	//���L�����ړ�
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	float mv = 80.0f * g_frametime; //�ړ��ʌv�Z
	if (key & PAD_INPUT_UP)		g_hy -= mv;
	if (key & PAD_INPUT_DOWN)	g_hy += mv;
	if (key & PAD_INPUT_LEFT)	g_hx -= mv;
	if (key & PAD_INPUT_RIGHT)	g_hx += mv;
	DrawGraph(g_hx, g_hy, g_heroimg, TRUE);
	//Z�L�[���`�F�b�N���ĉ�ʂ�؂�ւ�
	if (IsAKeyTrigger(key) == TRUE) {
		g_gamestate = GAME_OVER;
		g_timerstart = g_lasttime;	//�^�C�}�[�Z�b�g
	}
}
//�Q�[���N���A��ʕ`��
void DrawGameClear(){

}
//�Q�[���I�[�o�[��ʕ`��
void DrawGameOver(){
	//�e�L�X�g�\��
	DrawStringToHandle(100, 200, "�Q�[���I�[�o�[",
		GetColor(255, 0, 0), g_largefont);
	//5�b�o������^�C�g����ʂ�
	if (g_lasttime - g_timerstart > 5000) g_gamestate = GAME_TITLE;
}

//�L�[�g���K�[����
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