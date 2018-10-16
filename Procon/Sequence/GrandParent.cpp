#include"Gamelib/Framework.h"
#include"Sequence/GrandParent.h"
#include"Sequence/Title.h"
#include"Sequence/SMain.h"
using namespace Sequence;

Parent* Parent::mParentInstance = 0;

Parent::Parent() : 
mNextSequence( NEXT_NONE ),
mTitle(0),
mMain(0)
//mMenu(0)
{
	//�ŏ��Ƀ^�C�g�������(��R)
	mMain = new Main();
}

Parent::~Parent() {
	//��
	SAFE_DELETE(mTitle);
	SAFE_DELETE(mMain);
	//SAFE_DELETE(mMenu);
}

Parent* Parent::instance() {
	return mParentInstance;
}

void Parent::create() {
	ASSERT(!mParentInstance);
	mParentInstance = new Parent();
}

void Parent::update() {
	//�ǂ̃N���X�����s���邩�����߂�
	if (mTitle) {
		mTitle->update(this);
	}
	else if (mMain) {
		mMain->update(this);
	}/*
	else if (mMenu) {
		mMenu->update(this);
	}*/
	else {
		HALT("a ho ku sa"); //�����瓪��������
	}

	//���ꂼ��ւ̑J��
	switch (mNextSequence) {
	case NEXT_TITLE:
		if (!mTitle && mMain) {
			SAFE_DELETE(mMain);
			//SAFE_DELETE(mMenu);
			mTitle = new Title;
		}
		break;

	case NEXT_MAIN:
		if (!mMain && mTitle ) {
			SAFE_DELETE(mTitle);
			//SAFE_DELETE(mMenu);
			mMain = new Main;
		}
		break;
		/*
	case NEXT_MENU:
		if (!mMenu && (mTitle || mMain)) {
			SAFE_DELETE(mTitle);
			SAFE_DELETE(mMain);
			mMenu = new Menu;
		}
		break;
		*/
	}
	//����NEXT_NONE�ɂ��Ă���
	mNextSequence = NEXT_NONE;
}

void Parent::changeSequence(NextSequence next) {
	mNextSequence = next;
}
