
# include <Siv3D.hpp>

enum {
	NUM_WHITE_KEYS = 7,
	NUM_BLACK_KEYS = 5,
	NUM_ALL_KEYS = 12,
	WINDOW_W = 800,
	WINDOW_H = 600,
	W_KEY_W = 90,
	W_KEY_H = 250,
	B_KEY_W = 60,
	B_KEY_H = 150,
	KEY_START_X = (WINDOW_W - (W_KEY_W * NUM_WHITE_KEYS)) / 2,
	KEY_START_Y = (WINDOW_H - W_KEY_H) / 2,
};

bool JudgmentOverlapKey(Rect *blackKey);

void Main()
{
	Scene::SetBackground(Palette::Lightgrey);
	Window::Resize(WINDOW_W, WINDOW_H);
	constexpr Size WhiteKeySize((int32)W_KEY_W,(int32)W_KEY_H);
	constexpr Size BlackKeySize((int32)B_KEY_W, (int32)B_KEY_H);

	//ピアノの音
	const Audio pianoC(GMInstrument::Piano1, PianoKey::C4, 0.5s);
	


	Array<Audio> audioKey;
	for (int i = 0; i < NUM_ALL_KEYS; i++) {
		const Audio pianoC(GMInstrument::Piano1, PianoKey::C4 + i, 0.5s);
		audioKey << pianoC;
	}

	
	
	//白鍵と黒鍵の位置
	Array<Rect> whiteKey;
	for (int i = 0; i < NUM_WHITE_KEYS; i++) {
		whiteKey << Rectangle(KEY_START_X + i * WhiteKeySize.x, KEY_START_Y , WhiteKeySize);
	}

	Array<Rect> blackKey;
	for (int i = 0; i < NUM_BLACK_KEYS; i++) {
		if (i < 2) {
			blackKey << Rectangle((KEY_START_X + W_KEY_W - B_KEY_W / 2) + i * W_KEY_W, KEY_START_Y, BlackKeySize);
		}
		else {
		//	blackKey << Rectangle((KEY_START_X + W_KEY_W + B_KEY_W) + i * W_KEY_W, KEY_START_Y, BlackKeySize);
			blackKey << Rectangle((KEY_START_X + W_KEY_W - B_KEY_W / 2) + (i + 1) * W_KEY_W, KEY_START_Y, BlackKeySize);
		
		}

	}




	//白鍵と黒鍵の描画
	while (System::Update()) {
		for (const auto& whiteKey : whiteKey){
			whiteKey.draw().drawFrame(0, 3, Palette::Black);
		}

		int i = 0;
		for (int i = 0; i < NUM_BLACK_KEYS; i++) {
			//if (i != 2 ) {
				blackKey[i].draw(Palette::Black);
			//}
		}

		/*白鍵1つだけ音声を出す
		if (whiteKey[0].leftPressed()) {
			pianoC.play();
		}*/

		//白鍵の音を鳴らす

		if (!JudgmentOverlapKey(&blackKey[0])) {

			for (int i = 0; i < NUM_WHITE_KEYS; i++) {
				if (whiteKey[i].leftPressed()) {
					switch (i) {
					case 0:
						audioKey[0].play();
						break;
					case 1:
						audioKey[2].play();
						break;

					case 2:
						audioKey[4].play();
						break;
					case 3:
						audioKey[5].play();
						break;
					case 4:
						audioKey[7].play();
						break;
					case 5:
						audioKey[9].play();
						break;
					case 6:
						audioKey[11].play();
						break;
					}
				}
			}
		}

		//黒鍵の音を鳴らす
		for (int i = 0; i < NUM_BLACK_KEYS; i++) {
			if (blackKey[i].leftPressed()) {
				switch (i) {
				case 0:
					audioKey[1].play();
					break;
				case 1:
					audioKey[3].play();
					break;
				case 2:
					audioKey[6].play();
					break;
				case 3:
					audioKey[8].play();
					break;
				case 4:
					audioKey[10].play();
					break;
				}
			}
		}


	}

}

//全部の黒鍵とクリックした白鍵が重なってないか判定
bool JudgmentOverlapKey(Rect *blackKey)
{
	for (int i = 0; i < NUM_BLACK_KEYS; i++) {
		if ( (blackKey + i)->mouseOver()) {
			return true;
		}
	}
	return false;

}

