#include"Sequence/Title.h"
#include"Sequence/GrandParent.h"
#include"Image.h"
#include"Gamelib/Framework.h"
#include"Gamelib/Input/Manager.h"
#include"Gamelib/Input/Mouse.h"
using namespace Sequence;
using namespace GameLib::Input;

Title::Title() : mImage(0){
	mImage = new Image("Data/image/dummy.dds");
}

Title::~Title() {}

//ƒ}ƒEƒX‘€ì‚É’§í‚·‚é
void Title::update(Parent* parent) {
	if (Manager::instance().mouse().isOn( Mouse::BUTTON_LEFT )) {
		parent->changeSequence(Parent::NEXT_MAIN);
		//GameLib::Framework::instance().drawDebugString(0, 0, "ÆÓÂ¸Ý");
	}

	mImage->draw();
	//GameLib::Framework::instance().drawDebugString(0, 0, "ÆÓÂ¸Ý");
}