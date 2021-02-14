
//Window size
#define WINDOW_W  800  //ウィンドウの幅
#define WINDOW_H  300  //ウィンドウの高さ

//Num of keys
#define NUM_WHITE_KEYS   7 //白鍵の数
#define NUM_BLACK_KEYS   5 //黒鍵の数
#define W_W_KEY   80	   //白鍵：1鍵分の幅
#define H_W_KEY   250	   //白鍵：1鍵分の高さ
#define W_B_KEY   50	   //黒鍵：1鍵分の幅
#define H_B_KEY   150      //黒鍵：1鍵分の高さ


//Coordinate keys
#define START_X_W_KEY   (WINDOW_W - (W_W_KEY * NUM_WHITE_KEYS) - 25)  //白鍵：1鍵目を描画するx座標
#define START_Y_W_KEY   ((WINDOW_H - H_W_KEY) / 2)					  //白鍵：1鍵目を描画するy座標
#define START_X_B_KEY   (START_X_W_KEY + W_W_KEY - (W_B_KEY / 2))	  //黒鍵：1鍵目を描画するx座標
#define START_Y_B_KEY   START_Y_W_KEY								  //黒鍵：1鍵目を描画するy座標

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

//プロトタイプ宣言
bool isIntersectBlackKeys(Rect* allKeys);    //マウスの座標が黒鍵と重なっているか判定

bool isKeyWhite(int keyIndex);    //鍵盤を描画時に白鍵か黒鍵かを判断する関数
