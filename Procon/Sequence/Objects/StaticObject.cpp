#include"Sequence/Objects/StaticObject.h"
#include"Image.h"
#include"GameLib/Framework.h"

StaticObject::StaticObject()
	:mPoint(0),
	mSquared(false),
	mArgorithmFlag(false),
	mArgorithmFlag_S(false),
	mPanel(PANEL_NONE),
	mX(0),
	mY(0),
	mImg(0) 
{
	mImg = new Image("Data/image/changed.dds");
}

StaticObject::StaticObject(const StaticObject& other) {
	mPoint = other.mPoint;  //ポイント
	mSquared = other.mSquared;  //囲まれているかどうか
	mPanel = other.mPanel;
	mImg = 0;  //new Image("Data/image/changed.dds");

	//座標
	mX = other.mX;
	mY = other.mY;
}

//壊す
StaticObject::~StaticObject() {
	SAFE_DELETE(mImg);
}

//描画
void StaticObject::draw() const {
	int Px, Py;
	//GameLib::cout << mPanel << GameLib::endl;
	switch (mPanel) {
	case PANEL_BLUE:
		Px = 0;
		Py = 32;
		break;
	case PANEL_RED:
		Px =16;
		Py = 32;
		break;
	case PANEL_NONE:
		Px = 32;
		Py = 32;
		break;

	}
	mImg->draw(mX, mY, Px, Py, 16, 16);
}

//値のセット
void StaticObject::set(int x, int y, Panel panel) {
	//座標修正
	mX = x;
	mY = y;
	mPanel = panel;
}

void StaticObject::setPanel(Panel panel) {
	mPanel = panel;
}

void StaticObject::operator=(const StaticObject &other) {
	mPoint = other.mPoint;  //ポイント
	//mSquared = other.mSquared;  //囲まれているかどうか
	mPanel = other.mPanel;
	mImg = 0;

	//座標
	mX = other.mX;
	mY = other.mY;
}