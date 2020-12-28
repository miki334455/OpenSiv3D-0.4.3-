# include <Siv3D.hpp>

enum eCoordinate{
	//Window Size
	WINDOW_W = 800,
	WINDOW_H = 300,

	//Keys
	NUM_WHITE_KEYS = 7,
	NUM_BLACK_KEYS = 5,
	NUM_ALL_KEYS = 12,
	W_W_KEY = 80,
	H_W_KEY = 250,
	W_B_KEY = 50,
	H_B_KEY = 150,
	//START_X_W_KEY = (WINDOW_W - (W_W_KEY * NUM_WHITE_KEYS)) / 2,
	START_X_W_KEY = WINDOW_W - W_W_KEY * NUM_WHITE_KEYS - 25,
	START_Y_W_KEY = (WINDOW_H - H_W_KEY) / 2,	
	START_X_B_KEY = START_X_W_KEY + (W_W_KEY - W_B_KEY / 2),
	START_Y_B_KEY = START_Y_W_KEY,
};

enum eKeys{
	KEY_C,	KEY_Cs,
	KEY_D,	KEY_Ds,
	KEY_E,
	KEY_F,	KEY_Fs,
	KEY_G,	KEY_Gs,
	KEY_A,	KEY_As,
	KEY_B,
};

//プロトタイプ宣言
bool isIntersectBlackKeys(Rect* blackKeys );

void Main()
{
	Scene::SetBackground(Palette::Palevioletred);
	Window::Resize(WINDOW_W, WINDOW_H);

	Array<Rect> whiteKeys, blackKeys;
	Array<Audio> soundPiano,soundGuiter,soundFlute;

	const Array<String> options = { U"Piano", U"Guiter", U"Flute" };

    //スライダーのラベル
	const Font font(20);
	const String sliderText = U"Vol.";
	constexpr Point posSlider(25, 230);
	const Rect sliderRabelRect = font(sliderText).region(posSlider);


	//スライダー初期値
	double volume = 0.8;
	
	//ボタン初期値
	size_t radioIndex = 0;


	//白鍵の座標
	for (int i = 0; i < NUM_WHITE_KEYS; i++) {
		whiteKeys << Rect(START_X_W_KEY + (W_W_KEY * i), START_Y_W_KEY, W_W_KEY, H_W_KEY);
	}

	//黒鍵の座標
	for (int i = 0; i < NUM_BLACK_KEYS; i++) {
		if (i >= 2) {
			blackKeys << Rect(START_X_B_KEY + W_W_KEY + W_W_KEY * i, START_Y_B_KEY, W_B_KEY, H_B_KEY);
		}
		else {
			blackKeys << Rect(START_X_B_KEY + (W_W_KEY * i), START_Y_B_KEY, W_B_KEY, H_B_KEY);
		}

	}

	//ピアノの音色
	for (int i = 0; i < NUM_ALL_KEYS; i++) {
		soundPiano << Audio(GMInstrument::Piano1, PianoKey::C4 + i, 0.5s);
	}

	//ギターの音色
	for (int i = 0; i < NUM_ALL_KEYS; i++) {
		soundGuiter << Audio(GMInstrument::NylonGuitar, PianoKey::C4 + i, 0.5s);
	}

	//フルートの音色
	for (int i = 0; i < NUM_ALL_KEYS; i++) {
		soundFlute << Audio(GMInstrument::Flute, PianoKey::C4 + i, 0.5s);
	}

	while (System::Update()) {

		//白鍵の描画
		for (int i = 0; i < NUM_WHITE_KEYS; i++) {
			whiteKeys[i].draw(Palette::White).drawFrame(0, 3, Palette::Black);
		}

		//黒鍵の描画
		for (int i = 0; i < NUM_BLACK_KEYS; i++) {
			blackKeys[i].draw(Palette::Black).drawFrame(0, 3, Palette::Black);
		}

		//Volumeスライダーの描画
		sliderRabelRect.draw(Palette::White);
		font(sliderText).draw(posSlider, Palette::Black);

		if(SimpleGUI::VerticalSlider(volume, 0.0, 1.0, Vec2(25, 25), 200)){
			// 音量を設定 (0.0 - 1.0)
			for (int i = 0; i < NUM_ALL_KEYS; i++) {
				soundPiano[i].setVolume(volume);
				soundGuiter[i].setVolume(volume);
				soundFlute[i].setVolume(volume);
			}
		}


		
		//ピアノの音を鳴らす
		//マウスの現在の座標が、白鍵と重なっている時に白鍵を鳴らす。
		//しかし、マウスの現在の座標が、黒鍵とも重なっていた時には、白鍵を鳴らさない。
		if (radioIndex == 0)	{
			for (int i = 0; i < NUM_WHITE_KEYS; i++) {
				if (whiteKeys[i].leftPressed()) {
					bool aIntersect = isIntersectBlackKeys(&blackKeys[0]);
					if (!aIntersect) {
						switch (i) {
						case 0:		soundPiano[KEY_C].play();	break;
						case 1:		soundPiano[KEY_D].play();	break;
						case 2:		soundPiano[KEY_E].play();	break;
						case 3:		soundPiano[KEY_F].play();	break;
						case 4:		soundPiano[KEY_G].play();	break;
						case 5:		soundPiano[KEY_A].play();	break;
						case 6:		soundPiano[KEY_B].play();	break;
						default:								break;
						}
					}
				}
			}

			for (int i = 0; i < NUM_BLACK_KEYS; i++) {
				if (blackKeys[i].leftPressed()) {
					switch (i) {
					case 0:		soundPiano[KEY_Cs].play();	break;
					case 1:		soundPiano[KEY_Ds].play();	break;
					case 2:		soundPiano[KEY_Fs].play();	break;
					case 3:		soundPiano[KEY_Gs].play();	break;
					case 4:		soundPiano[KEY_As].play();	break;
					}
				}
			}

		}

		//ギターの音を鳴らす
		//マウスの現在の座標が、白鍵と重なっている時に白鍵を鳴らす。
		//しかし、マウスの現在の座標が、黒鍵とも重なっていた時には、白鍵を鳴らさない。
		if (radioIndex == 1){
			for (int i = 0; i < NUM_WHITE_KEYS; i++) {
				if (whiteKeys[i].leftPressed()) {
					bool aIntersect = isIntersectBlackKeys(&blackKeys[0]);
					if (!aIntersect) {
						switch (i) {
						case 0:		soundGuiter[KEY_C].play();	break;
						case 1:		soundGuiter[KEY_D].play();	break;
						case 2:		soundGuiter[KEY_E].play();	break;
						case 3:		soundGuiter[KEY_F].play();	break;
						case 4:		soundGuiter[KEY_G].play();	break;
						case 5:		soundGuiter[KEY_A].play();	break;
						case 6:		soundGuiter[KEY_B].play();	break;
						default:								break;
						}
					}
				}
			}

			for (int i = 0; i < NUM_BLACK_KEYS; i++) {
				if (blackKeys[i].leftPressed()) {
					switch (i) {
					case 0:		soundGuiter[KEY_Cs].play();	break;
					case 1:		soundGuiter[KEY_Ds].play();	break;
					case 2:		soundGuiter[KEY_Fs].play();	break;
					case 3:		soundGuiter[KEY_Gs].play();	break;
					case 4:		soundGuiter[KEY_As].play();	break;
					}
				}
			}

		}
	
		//フルートの音を鳴らす
		//マウスの現在の座標が、白鍵と重なっている時に白鍵を鳴らす。
		//しかし、マウスの現在の座標が、黒鍵とも重なっていた時には、白鍵を鳴らさない。
		if (radioIndex == 2) {
			for (int i = 0; i < NUM_WHITE_KEYS; i++) {
				if (whiteKeys[i].leftPressed()) {
					bool aIntersect = isIntersectBlackKeys(&blackKeys[0]);
					if (!aIntersect) {
						switch (i) {
						case 0:		soundFlute[KEY_C].play();	break;
						case 1:		soundFlute[KEY_D].play();	break;
						case 2:		soundFlute[KEY_E].play();	break;
						case 3:		soundFlute[KEY_F].play();	break;
						case 4:		soundFlute[KEY_G].play();	break;
						case 5:		soundFlute[KEY_A].play();	break;
						case 6:		soundFlute[KEY_B].play();	break;
						default:								break;
						}
					}
				}
			}

			for (int i = 0; i < NUM_BLACK_KEYS; i++) {
				if (blackKeys[i].leftPressed()) {
					switch (i) {
					case 0:		soundFlute[KEY_Cs].play();	break;
					case 1:		soundFlute[KEY_Ds].play();	break;
					case 2:		soundFlute[KEY_Fs].play();	break;
					case 3:		soundFlute[KEY_Gs].play();	break;
					case 4:		soundFlute[KEY_As].play();	break;
					}
				}
			}

		}
		if (SimpleGUI::RadioButtons(radioIndex, options, Vec2(80, 25))) {

			
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	




		

	}//while
}



//return:	マウスの座標が、黒鍵と重なっていればtrue
bool isIntersectBlackKeys(Rect* blackKeys)
{
	for (int i = 0; i < NUM_BLACK_KEYS; i++) {
		if ((blackKeys + i)->mouseOver()){
			return true;
		}
	}
	return false;
}

