# include <Siv3D.hpp>
# include "Piano_Miki.h"

void Main()
{
	//ウィンドウ：背景色、サイズ変更
	Scene::SetBackground(Palette::Palevioletred);
	Window::Resize(WINDOW_W, WINDOW_H);


	Array<Rect> allKeys;

	//Array<Audio> soundPiano, soundGuiter, soundFlute;



	Array<Audio> soundObject[NUM_OF_SOUND];

	const Array<String> options = { U"Piano", U"Guiter", U"Flute" };

	//スライダーのラベル
	const Font font(20);
	const String sliderText = U"Vol.";
	constexpr Point posSlider(25, 230);
	const Rect sliderLabelRect = font(sliderText).region(posSlider);

	//スライダー初期値
	double volume = 0.8;

	//ボタン初期値
	size_t radioIndex = 0;


    //白鍵・黒鍵の座標
	allKeys << Rect(START_X_W_KEY + (W_W_KEY * 0), START_Y_W_KEY, W_W_KEY, H_W_KEY);          //C
	allKeys << Rect(START_X_B_KEY + (W_W_KEY * 0), START_Y_B_KEY, W_B_KEY, H_B_KEY);          //C#
	allKeys << Rect(START_X_W_KEY + (W_W_KEY * 1), START_Y_W_KEY, W_W_KEY, H_W_KEY);          //D
	allKeys << Rect(START_X_B_KEY + (W_W_KEY * 1), START_Y_B_KEY, W_B_KEY, H_B_KEY);          //D#
	allKeys << Rect(START_X_W_KEY + (W_W_KEY * 2), START_Y_W_KEY, W_W_KEY, H_W_KEY);          //E
	allKeys << Rect(START_X_W_KEY + (W_W_KEY * 3), START_Y_W_KEY, W_W_KEY, H_W_KEY);          //F
	allKeys << Rect(START_X_B_KEY + W_W_KEY + W_W_KEY * 2, START_Y_B_KEY, W_B_KEY, H_B_KEY);  //F#
	allKeys << Rect(START_X_W_KEY + (W_W_KEY * 4), START_Y_W_KEY, W_W_KEY, H_W_KEY);          //G
	allKeys << Rect(START_X_B_KEY + W_W_KEY + W_W_KEY * 3, START_Y_B_KEY, W_B_KEY, H_B_KEY);  //G#
	allKeys << Rect(START_X_W_KEY + (W_W_KEY * 5), START_Y_W_KEY, W_W_KEY, H_W_KEY);          //A
	allKeys << Rect(START_X_B_KEY + W_W_KEY + W_W_KEY * 4, START_Y_B_KEY, W_B_KEY, H_B_KEY);  //A#
	allKeys << Rect(START_X_W_KEY + (W_W_KEY * 6), START_Y_W_KEY, W_W_KEY, H_W_KEY);          //B


//ピアノ、ギター、フルートの音色を用意する。
	for (int toneIndex = 0; toneIndex < NUM_OF_SOUND; toneIndex++) {
		for (int keyIndex = 0; keyIndex < NUM_ALL_KEYS; keyIndex++) {
			if (toneIndex == PIANO) {
				soundObject[PIANO] << Audio(GMInstrument::Piano1, PianoKey::C4 + keyIndex, 0.5s);
			}
			else if (toneIndex == GUITAR) {

				soundObject[GUITAR] << Audio(GMInstrument::NylonGuitar, PianoKey::C4 + keyIndex, 0.5s);
			}
			else {
				soundObject[FLUTE] << Audio(GMInstrument::Flute, PianoKey::C4 + keyIndex, 0.5s);
			}
		}

	}



	while (System::Update()) {


		//白鍵・黒鍵の描画
		for (int i = 0; i < NUM_ALL_KEYS; i++) {
			if (isKeyWhite(i)) {
				allKeys[i].draw(Palette::White).drawFrame(0, 3, Palette::Black);
			}			
		}

		for (int i = 0; i < NUM_ALL_KEYS; i++) {
			if (!isKeyWhite(i)) {
				allKeys[i].draw(Palette::Black).drawFrame(0, 3, Palette::Black);
			}
		}

		//Volumeスライダーの描画
		sliderLabelRect.draw(Palette::White);
		font(sliderText).draw(posSlider, Palette::Black);

		//音色切り替えのラジオボタンを描画
		if (SimpleGUI::RadioButtons(radioIndex, options, Vec2(80, 25))) {

		}


		if (SimpleGUI::VerticalSlider(volume, 0.0, 1.0, Vec2(25, 25), 200)) {
			// 音量を設定 (0.0 - 1.0)
			for (int toneIndex = 0; toneIndex < NUM_OF_SOUND; toneIndex++) {
				for (int keyIndex = 0; keyIndex < NUM_ALL_KEYS; keyIndex++) {
					soundObject[toneIndex][keyIndex].setVolume(volume);
				}
			}
		}

		//ピアノの音を鳴らす
		//マウスの現在の座標が、白鍵と重なっている時に白鍵を鳴らす。
		//しかし、マウスの現在の座標が、黒鍵とも重なっていた時には、白鍵を鳴らさない。


			for (int toneIndex = 0; toneIndex < NUM_OF_SOUND; toneIndex++) {
				if (radioIndex == toneIndex) {
					for (int i = 0; i < NUM_ALL_KEYS; i++) {
						if (allKeys[i].leftPressed()) {
							if (isKeyWhite(i)) {
								bool aIntersect = isIntersectBlackKeys(&allKeys[0]);
								if (!aIntersect) {
									soundObject[radioIndex][i].play();

								}
							}
							else {
								soundObject[radioIndex][i].play();
							}
						}
					}
				}
			}


	}//while
}//main


//鍵盤を描画時に白鍵か黒鍵かを判断する関数
//引数：鍵盤の座標が格納されている順番  戻り値：true(白鍵の場合)　false(黒鍵の場合)
bool isKeyWhite(int keyIndex){

	switch (keyIndex) {
		case KEY_Cs:
		case KEY_Ds:
		case KEY_Fs:
		case KEY_Gs:
		case KEY_As:
			return false;
			break;
	}
	return true;


}

//黒鍵とマウスポインタが重なっているか判断する関数。
//引数：黒鍵オブジェクトのポインタ　戻り値：true(黒鍵とマウスポインタが重なっている場合) または false(黒鍵とマウスポインタが重なっていない場合)
bool isIntersectBlackKeys(Rect* allKeys)
{
	for (int i = 0; i < NUM_ALL_KEYS; i++) {
		if (!isKeyWhite(i)) {
			if ((allKeys + i)->mouseOver()) {
				return true;
			}
		}
	}

	return false;
}




