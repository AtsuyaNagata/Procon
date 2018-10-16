#include"Sequence/Objects/DynamicObject.h"
#include"Image.h"
#include"GameLib/Framework.h"
using namespace GameLib;

DynamicObject::DynamicObject()
	: mPlayer(true),
	mClick(false),
	mMoved(false),
	mX(0),
	mY(0),
	mOldX(0),
	mOldY(0),
	mImg(0),
	massSize(0)
{
	mImg = new Image("Data/image/changed.dds");
}

DynamicObject::~DynamicObject() {
	SAFE_DELETE(mImg);
}

void DynamicObject::draw() {
	int spX = 0;
	int spY = 1;
	if (mClick == true) {
		//spX = 1;
		spY -= 1;
	}
	if (mPlayer == true) {
		mImg->draw(mX * massSize + spX, mY * massSize + spY, 0, 0, 16, 16);
	}
	else {
		mImg->draw(mX * massSize + spX, mY * massSize + spY, 16, 0, 16, 16);
	}
}

void DynamicObject::set(int x, int y, bool player, int size) {
	mX = x;
	mY = y;
	mPlayer = player;
	massSize = size;
}

void DynamicObject::set(int x, int y) {
	mX = x;
	mY = y;
}

void DynamicObject::setOld(int x, int y) {
	mOldX = x;
	mOldY = y;
}

void DynamicObject::operator=(const DynamicObject &other) {
	mPlayer = other.mPlayer;  //プレイヤーか敵か

	mX = other.mX;  //x座標(アナログな値ではない)
	mY = other.mY;  //察して
	mOldX = other.mOldX;  //一つ手前にあったx座標
	mOldY = other.mOldY;  //察せよ

	massSize = other.massSize;  //マスの大きさ

	mClick = other.mClick;
	mMoved = other.mMoved;

	mImg = 0;   //画像データを読み込むクラスのポインタ 使う予定はないので0にしておく
}