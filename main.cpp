#include <Novice.h>
#include "Play.h"
#include "Title.h"

const char kWindowTitle[] = "GC1A_03_オノセ_ユウカ_フルスイング";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWide, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Scene scene = TITLE;

	Play* play = new Play;
	Title* title = new Title;	
	int audioHandle1 = Novice::LoadAudio("./images/stage.mp3");
	int playHandle1 = -1;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (!Novice::IsPlayingAudio(playHandle1)) {
			playHandle1 = Novice::PlayAudio(audioHandle1, false, 0.5f);
		}

		switch (scene) {
			case TITLE:
				title->Update(keys);
				title->Draw();
				if (title->GetIsNextScene() == true) {
					scene = PLAY;
					title->Initialization();
				}
				break;

			case PLAY:
				play->Update(keys, preKeys);
				play->Draw();
				if (play->GetIsNextScene() == true) {
					scene = play->GetNextScene();
					play->Initialization();
				}
				break;

		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete play;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
