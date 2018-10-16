#ifndef SEQUENCE_MAIN_H_
#define SEQUENCE_MAIN_H_

#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Mouse.h"

#include"Array2D.h"

class StaticObject;
class DynamicObject;
class Image;

namespace Sequence {
	class Parent;  //メインで使うオブジェクト
	class Algorithm;  //同じく

	class Main {

	public:
		Main();
		~Main();
		void update(Parent*);
		void whereMass(int x, int y);
		void drawString(int x, int y, int point);
		void MarkClean(int x, int y);
		void drawMark(int x, int y);
		int charaToInteger(char const * c, int *point);
		void drawPoint(int Ppoint, int Epoint);

	private:
		Array2D<StaticObject> mStaticObject;  //静的(動かない)オブジェクト
		DynamicObject *mDynamicObject; //動的(めっちゃ動く)オブジェクト

		Image* mFont;
		Image* mFont2;
		Image* mBackGround;

		GameLib::Input::Mouse* mMouse; //マウスの出力を受け取る

		int massX;  //マスの座標(X座標)<-マス目の値、アナログな値ではない。
		int massY;  //察して

		int PointingX;  //次に移動するべきマス
		int PointingY;

		int maxX;  //x座標の最大値
		int maxY;  //y座標の最大値

		bool mousePressed;  //マウスが押されていたかの判定
		bool moved; //動いたかどうかの判定

		const int massSize;  //マスの大きさ

		Algorithm *mAlgorithm;
	};
}

#endif