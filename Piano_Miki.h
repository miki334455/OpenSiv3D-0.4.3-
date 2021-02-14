
//Window size
#define WINDOW_W  800  //�E�B���h�E�̕�
#define WINDOW_H  300  //�E�B���h�E�̍���

//Num of keys
#define NUM_WHITE_KEYS   7 //�����̐�
#define NUM_BLACK_KEYS   5 //�����̐�
#define W_W_KEY   80	   //�����F1�����̕�
#define H_W_KEY   250	   //�����F1�����̍���
#define W_B_KEY   50	   //�����F1�����̕�
#define H_B_KEY   150      //�����F1�����̍���


//Coordinate keys
#define START_X_W_KEY   (WINDOW_W - (W_W_KEY * NUM_WHITE_KEYS) - 25)  //�����F1���ڂ�`�悷��x���W
#define START_Y_W_KEY   ((WINDOW_H - H_W_KEY) / 2)					  //�����F1���ڂ�`�悷��y���W
#define START_X_B_KEY   (START_X_W_KEY + W_W_KEY - (W_B_KEY / 2))	  //�����F1���ڂ�`�悷��x���W
#define START_Y_B_KEY   START_Y_W_KEY								  //�����F1���ڂ�`�悷��y���W

enum eKeys {
	KEY_C, KEY_Cs,
	KEY_D, KEY_Ds,
	KEY_E,
	KEY_F, KEY_Fs,
	KEY_G, KEY_Gs,
	KEY_A, KEY_As,
	KEY_B,
	NUM_ALL_KEYS
};

enum {
	PIANO,
	GUITAR,
	FLUTE,
	NUM_OF_SOUND
};

//�v���g�^�C�v�錾
bool isIntersectBlackKeys(Rect* allKeys);    //�}�E�X�̍��W�������Əd�Ȃ��Ă��邩����

bool isKeyWhite(int keyIndex);    //���Ղ�`�掞�ɔ������������𔻒f����֐�
