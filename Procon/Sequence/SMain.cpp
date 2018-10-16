#include"Sequence/SMain.h"
#include"Sequence/Objects/DynamicObject.h"
#include"Sequence/Objects/StaticObject.h"
#include"File.h"
#include"Image.h"
#include"Sequence/GrandParent.h"
#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Mouse.h"
#include "Salgorithm.h"

using namespace Sequence;
using namespace GameLib::Input;

Main::Main()
	: massSize(18),           //マスの大きさ
	maxX(0),
	maxY(0),
	mousePressed(false),
	moved(false),
	mDynamicObject(0),      //めっちゃ動くオブジェクトの初期化
	mFont(0),               //フォントの初期化
	PointingX(0),           //次に行くべき場所をポイントするための座標データの初期化
	PointingY(0)
{
	mMouse = new Mouse;
	mFont = new Image("Data/image/font.dds");
	mFont2 = new Image("Data/image/font2.dds");
	mBackGround = new Image("Data/image/changed.dds");
	File file("Data/stage/stage1.txt");              //ステージ読み込み

	int charaPoint = 0;
	charaPoint += charaToInteger(&file.data()[charaPoint], &maxX);
	charaPoint += charaToInteger(&file.data()[charaPoint], &maxY);

	mStaticObject.setSize(maxX, maxY);    //ステージの大きさ
	mDynamicObject = new DynamicObject[4];

	//StaticObjectの初期化
	int point = 0;
	for (int i = 0; i < maxX; ++i) {
		for (int j = 0; j < maxY; ++j) {
			if (charaToInteger(&file.data()[charaPoint], &point) != 1) {
				mStaticObject(i, j).set(i * massSize, j * massSize, StaticObject::Panel::PANEL_NONE);
				mStaticObject(i, j) = point;
				mStaticObject(i, j).draw();
				drawString(i * massSize, j * massSize, mStaticObject(i, j).getPoint());
			}
			else {
				j -= 1;
			}
			charaPoint += charaToInteger(&file.data()[charaPoint], &point);
		}
	}

	int x = 0, y = 0;
	//ダイナミックオブジェクトの初期化
	for (int i = 0; i < 2; ++i) {
		charaPoint += charaToInteger(&file.data()[charaPoint], &x);
		charaPoint += charaToInteger(&file.data()[charaPoint], &y);
		x--;        //座標の開始地点を0に調整する。
		y--;        //上と同じ
		mDynamicObject[i].set(x, y, true, massSize);
		mStaticObject(x, y).setPanel(StaticObject::Panel::PANEL_BLUE);
		mStaticObject(x, y).draw();
		mDynamicObject[i].draw();

		mDynamicObject[i + 2].set(maxX - 1 - x, y, false, massSize);  //maxサイズは1大きいので1引く
		mStaticObject(maxX - 1 - x, y).setPanel(StaticObject::Panel::PANEL_RED);
		mStaticObject(maxX - 1 - x, y).draw();
		mDynamicObject[i + 2].draw();
	}

	//アルゴリズムの生成と動作確認
	mAlgorithm = new Algorithm(mStaticObject, mDynamicObject, maxX, maxY);

	mAlgorithm->CleanObject(mStaticObject, mDynamicObject);
	
	mAlgorithm->not_Thinking_Salgorithm(mDynamicObject[0].getX(), mDynamicObject[0].getY(), 4, 5000, 0);
	mAlgorithm->not_Thinking_Salgorithm(mDynamicObject[1].getX(), mDynamicObject[1].getY(), 4, 5000, 1);
	drawMark(mAlgorithm->getPointX(0), mAlgorithm->getPointY(0));
	drawMark(mAlgorithm->getPointX(1), mAlgorithm->getPointY(1));
	

	//得点横のキャラクターの描画
	mBackGround->draw(250, 10, 48, 0, 16, 16);
	mBackGround->draw(250, 10, 0, 0, 16, 16);
	//同上(敵キャラ)
	mBackGround->draw(250, 30, 48, 0, 16, 16);
	mBackGround->draw(250, 30, 16, 0, 16, 16);
}

Main::~Main() {
}

void Main::update(Parent* parent) {
	if (mousePressed == false) {  //マウスが「押されていたか」を判定

		if (mMouse->isOn(Mouse::BUTTON_LEFT) || mMouse->isOn(Mouse::BUTTON_RIGHT) || mMouse->isOn(Mouse::BUTTON_MIDDLE)) {  //マウスが「押されている」かを判定

			if (0 < mMouse->x() && 0 < mMouse->y() && mMouse->x() < maxX * massSize && mMouse->y() < maxY * massSize) {  //アクセス違反検知(大事)

				whereMass(mMouse->x(), mMouse->y());  //マスの場所を確定する

				if (mMouse->isOn(Mouse::BUTTON_LEFT)) {  //左クリックされていたら
					if (mStaticObject(massX, massY).getPanel() == StaticObject::Panel::PANEL_BLUE) {  //元々青色だったら
						mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_NONE);
					}
					else {
						mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_BLUE);
					}
					mStaticObject(massX, massY).draw();
					drawString(massX * massSize, massY * massSize, mStaticObject(massX, massY).getPoint());
				}

				if (mMouse->isOn(Mouse::BUTTON_RIGHT)) {
					if (mStaticObject(massX, massY).getPanel() == StaticObject::Panel::PANEL_RED) {
						mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_NONE);
					}
					else {
						mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_RED);
					}
					mStaticObject(massX, massY).draw();
					drawString(massX * massSize, massY * massSize, mStaticObject(massX, massY).getPoint());
				}

				//プレイヤーor敵の選択
				if (mMouse->isOn(Mouse::BUTTON_MIDDLE)) {
					for (int i = 0; i < 4; ++i) {
						if (mDynamicObject[i].getClick() == true) {  //もし動的オブジェクトがクリックされている状態であれば
							//値のセット
							mDynamicObject[i].changeMoved();
							mAlgorithm->setFinished(false);
							mDynamicObject[i].set(massX, massY);
							//描画
							mStaticObject(mDynamicObject[i].getOldX(), mDynamicObject[i].getOldY()).draw();
							drawString(mDynamicObject[i].getOldX() * massSize, mDynamicObject[i].getOldY() * massSize, mStaticObject(mDynamicObject[i].getOldX(), mDynamicObject[i].getOldY()).getPoint());
							if (mDynamicObject[i].getPlayer() == true) {  //プレイヤーだったら
								mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_BLUE);
							}
							else {  //敵だったら
								mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_RED);
							}
							mStaticObject(massX, massY).draw();
							//文字は出力しない
						}
					}

					//changeClick()は上のコードと兼用
					for (int i = 0; i < 4; ++i) {
						if (mDynamicObject[i].getX() == massX && mDynamicObject[i].getY() == massY) {  //もしクリック先にダイナミックオブジェクトがあったら
							mDynamicObject[i].changeClick();
							mDynamicObject[i].setOld(massX, massY);
						}
						else {
							//何もしない
						}
					}
				}
				
				mousePressed = true;  //押したな？
				for (int i = 0; i < 4; ++i) {
					mDynamicObject[i].draw();
				}

				//アルゴリズムクラスのデータをクリーンする
				mAlgorithm->CleanObject(mStaticObject, mDynamicObject);
				//クリーンした後得点描画を行う(アルゴリズムクラス用の得点計算を流用してるため)
				drawPoint(mAlgorithm->getPlayerPoint(), mAlgorithm->getEnemyPoint());
			}
		}
	}

	else if(!(mMouse->isOn(Mouse::BUTTON_LEFT) || mMouse->isOn(Mouse::BUTTON_RIGHT) || mMouse->isOn(Mouse::BUTTON_MIDDLE))){
		mousePressed = false;  //押さなかったのか...俺以外の奴と...
		for (int i = 0; i < 2; ++i) {
			if (mDynamicObject[i].getMoved() == true) {
				if (mAlgorithm->getFinished() == false) {
					//アルゴリズムクラスのデータを今の盤面データにする
					mAlgorithm->CleanObject(mStaticObject, mDynamicObject);
					//描画をきれいにしてポイントを変える
					MarkClean(mAlgorithm->getPointX(i), mAlgorithm->getPointY(i));
					//アルゴリズムの開始
					mAlgorithm->not_Thinking_Salgorithm(mDynamicObject[i].getX(), mDynamicObject[i].getY(), 4, 5000, i);
					mAlgorithm->setFinished(true);
				}

				//フラグのクリーン
				mDynamicObject[i].changeMoved();
				//初期描画
				mStaticObject(mAlgorithm->getPointX(i), mAlgorithm->getPointY(i)).draw();
				//もし動的オブジェクトの移動先がポイント点とかぶったら
				if(mAlgorithm->getPointX(i) == mDynamicObject[i].getX() && mAlgorithm->getPointY(i) == mDynamicObject[i].getY())
					mDynamicObject[i].draw();
				//かぶらなかったら
				else
					drawString(mAlgorithm->getPointX(i) * massSize, mAlgorithm->getPointY(i) * massSize, mStaticObject(mAlgorithm->getPointX(i), mAlgorithm->getPointY(i)).getPoint());
				
				//値の変更
				//mAlgorithm->getLargestNumber(i);
				//変更後描画
				drawMark(mAlgorithm->getPointX(i), mAlgorithm->getPointY(i));
			}
		}
	}
}

void Main::whereMass(int x, int y) {    //座標マス変換
	massX = x / massSize;
	massY = y / massSize;
}

void Main::drawString(int x, int y, int point) {
	char text[2];
	int j = 0;
	
	if (point < 0) {
		mFont->draw(x, y, 15 * 8, 3 * 16, 8, 16);
		point *= -1;
	}

	for (int i = 0; i < 2; ++i) {
		text[i] = 48;
	}

	for (int i = point % 100; i >= 1; i /= 10) {
		if (i == 1) {
			text[j] = 49;
			break;
		}
		text[j] = (i % 10) + 48;
		++j;
	}

	for (int i = 0; i < sizeof(text); ++i) {
		mFont->draw(x + ((1 - i) * 8), y, ((text[i] - 32) % 16) * 8, ((text[i] - 32) / 16) * 16, 8, 16);
	}
}

int Main::charaToInteger(char const * c, int *point) {
	bool minus = false;
	*point = 0;

	//もし開幕これだったら1だけ返して終了
	if (c[0] == ' ' || c[0] == ':') {
		return 1;
	}

	for (int i = 0; i < 3; ++i) {
		if (c[i] == '-') {  //マイナスがあるかの判別
			minus = true;
		}
		else {
			if (c[i + 1] == ' ' || c[i + 1] == ':') {  //もしこの記号があれば終了処理
				*point += c[i] - 48;
				if (minus) {
					*point *= -1;
				}
				return i + 2;
			}
			else {
				*point += 10 * (c[i] - 48);
			}
		}
	}
	return 3;
}

void Main::drawMark(int PointingX, int PointingY) {
	mFont2->draw(PointingX * massSize - 2, PointingY * massSize, 8 * 11, 16 * 3, 8, 16);  //青色「[」を表示
	mFont2->draw(PointingX * massSize + 10, PointingY * massSize, 8 * 13, 16 * 3, 8, 16);  //青色「]」を表示
}

void Main::MarkClean(int x, int y)
{
	mStaticObject(x, y).draw();
	for (int i = 0; i < 2; ++i) {
		if (mDynamicObject[i].getX() == x && mDynamicObject[i].getY() == y) {

			mDynamicObject[i].draw();
			return;
		}
	}
	drawString(x * massSize, y * massSize, mStaticObject(x, y).getPoint());
}

void Main::drawPoint(int Ppoint, int Epoint) 
{
	/*自軍のポイント*/
	mBackGround->draw(270, 10, 48, 0, 10, 16);         //符号のクリーン
	if (Ppoint < 0) {
		Ppoint *= -1;
		mFont2->draw(270, 10, 8 * 13, 0, 8, 16);       //マイナス符号の描画
	}
	else {
		mFont2->draw(270, 10, 8 * 11, 0, 8, 16);       //プラス符号の描画
	}
	int digits = Ppoint / 100;
	mBackGround->draw(280, 10, 48, 0, 10, 16);         //3桁目のクリーン
	mFont2->draw(280, 10, 8 * digits, 16 * 1, 8, 16);  //3桁目の数を表示

	digits = Ppoint % 100;
	digits = digits / 10;
	mBackGround->draw(290, 10, 48, 0, 10, 16);         //2桁目のクリーン
	mFont2->draw(290, 10, 8 * digits, 16 * 1, 8, 16);  //2桁目の数を表示

	digits = Ppoint % 10;
	mBackGround->draw(300, 10, 48, 0, 10, 16);         //1桁目のクリーン
	mFont2->draw(300, 10, 8 * digits, 16 * 1, 8, 16);  //1桁目の数を表示

	/*相手軍のポイント*/
	mBackGround->draw(270, 30, 48, 0, 10, 16);         //符号のクリーン
	if (Epoint < 0) {
		Epoint *= -1;
		mFont2->draw(270, 30, 8 * 13, 0, 8, 16);       //マイナス符号の描画
	}
	else {
		mFont2->draw(270, 30, 8 * 11, 0, 8, 16);       //プラス符号の描画
	}
	digits = Epoint / 100;
	mBackGround->draw(280, 30, 48, 0, 10, 16);         //3桁目のクリーン
	mFont2->draw(280, 30, 8 * digits, 16 * 1, 8, 16);  //3桁目の数を表示

	digits = Epoint % 100;
	digits = digits / 10;
	mBackGround->draw(290, 30, 48, 0, 10, 16);         //2桁目のクリーン
	mFont2->draw(290, 30, 8 * digits, 16 * 1, 8, 16);  //2桁目の数を表示

	digits = Epoint % 10;
	mBackGround->draw(300, 30, 48, 0, 10, 16);         //1桁目のクリーン
	mFont2->draw(300, 30, 8 * digits, 16 * 1, 8, 16);  //1桁目の数を表示
}