# VisualStudioProjects


## VC2013(JP)
1. VC++.win32�v���W�F�N�g,�\�����[�V�����̃f�B���N�g���쐬:unckeck  
2. Windows�A�v���P�[�V����,��̃v���W�F�N�g  

### ���ׂĂ̍\��
* �\���v���p�e�B.�����Z�b�g.�}���`�o�C�g�����Z�b�g���g�p����
* �\���v���p�e�B.VC++�f�B���N�g��.�C���N���[�h�f�B���N�g��:Dxlib.Dirctory
* �\���v���p�e�B.�����J�[.�S��.�ǉ��̃��C�u�����f�B���N�g��.:Dxlib.Dirctory

### Release
* �����J�[.�ڍאݒ�.���S�ȗ�O�n���h���[���܂ރC���[�W:������
* C/C++.�R�[�h����.�����^�C�����C�u����:�}���`�X���b�h(/MIT)

### Debug
* C/C++.�R�[�h����.�����^�C�����C�u����:�}���`�X���b�h�f�o�b�O(/MTd)

##### main.cpp

```
#include <DxLib.h>
int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC ,int nC){
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1){
		return 1;
	}
	DrawBox(0, 0, 120, 120, 0x00FFF, TRUE);
	WaitKey();
	DxLib_End();
	return 0;
}
```