#include"Gamelib/Framework.h"
#include"Sequence/GrandParent.h"
using namespace GameLib;

namespace GameLib{
	void Framework::update(){
		if (!Sequence::Parent::instance()) {
			Sequence::Parent::create();
			setFrameRate(60);
		}
		Sequence::Parent::instance()->update();
		sleep(1);
	}
}
