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
	mPlayer = other.mPlayer;  //�v���C���[���G��

	mX = other.mX;  //x���W(�A�i���O�Ȓl�ł͂Ȃ�)
	mY = other.mY;  //�@����
	mOldX = other.mOldX;  //���O�ɂ�����x���W
	mOldY = other.mOldY;  //�@����

	massSize = other.massSize;  //�}�X�̑傫��

	mClick = other.mClick;
	mMoved = other.mMoved;

	mImg = 0;   //�摜�f�[�^��ǂݍ��ރN���X�̃|�C���^ �g���\��͂Ȃ��̂�0�ɂ��Ă���
}