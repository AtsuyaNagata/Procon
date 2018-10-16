#include "Salgorithm.h"
#include "Sequence/Objects/DynamicObject.h"
#include "Sequence/Objects/StaticObject.h"
#include "GameLib/Framework.h"
#include <random>
using namespace Sequence;
using namespace GameLib;

//StaticObjectのコピーコンストラクタはいじってある
Algorithm::Algorithm(Array2D<StaticObject> StObj, DynamicObject *DyObj, int maxX, int maxY)
	:
	mPointingX(0),
	mPointingY(0),
	mMaxX(maxX),
	mMaxY(maxY),
	mMaximumValue(2),
	mFinished(false)
{
	mStaticObject.setSize(maxX, maxY);
	for (int i = 0; i < maxX; ++i) {
		for (int j = 0; j < maxY; ++j) {
			mStaticObject(i, j) = StObj(i, j);
			//GameLib::cout << "StaticCall: " << mStaticObject(i, j).getPanel() << GameLib::endl;
		}
	}

	mDynamicObject = new DynamicObject[4];
	DynamicObject *tempDyObj = DyObj;
	for (int i = 0; i < 4; ++i) {
		mDynamicObject[i] = tempDyObj[i];
		//GameLib::cout << "tempCall: " << tempDyObj[i].getMoved() << GameLib::endl;
	}
	mPointingX = new int[mMaximumValue];
	mPointingY = new int[mMaximumValue];

	//仮に初期化してる
	for (int i = 0; i < mMaximumValue; ++i) {
		mPointingX[i] = 0;
		mPointingY[i] = 0;
	}
}

void Algorithm::CleanObject(Array2D<StaticObject> &StObj, DynamicObject *DyObj) {
	for (int i = 0; i < mMaxY; ++i) {
		for (int j = 0; j < mMaxX; ++j) {
			mStaticObject(j, i) = StObj(j, i);
		}
	}

	setPlayerSquared();

	for (int i = 0; i < 4; ++i) {
		mDynamicObject[i] = DyObj[i];
	}
}

void Algorithm::CleanPanel(Array2D<StaticObject> &StObj) {
	for (int i = 0; i < mMaxX; ++i) {
		for (int j = 0; j < mMaxY; ++j) {
			mStaticObject(i, j).setPanel(StObj(i, j).getPanel());
		}
	}
}

void Algorithm::cleanSquared() {
	for (int i = 0; i < mMaxY; ++i) {
		for (int j = 0; j < mMaxX; ++j) {
			mStaticObject(j, i).setSquared(false);
		}
	}
}

void Algorithm::setPlayerSquared() {

	for (int i = 0; i < mMaxY; ++i) {
		for (int j = 0; j < mMaxX; ++j) {
			mStaticObject(j, i).setSquared(true);
		}
	}

	for (int i = 0; i < mMaxX; ++i) {
		if (mStaticObject(i, 0).getPanel() == StaticObject::Panel::PANEL_BLUE) {
			SearchSquared(i, 0, 1);
		}
		else {
			SearchSquared(i, 0, 0);
		}
		if (mStaticObject(i, mMaxY - 1).getPanel() == StaticObject::Panel::PANEL_BLUE) {
			SearchSquared(i, mMaxY - 1, 1);
		}
		else {
			SearchSquared(i, mMaxY - 1, 0);
		}
	}

	for (int i = 0; i < mMaxY; ++i) {
		if (mStaticObject(0, i).getPanel() == StaticObject::Panel::PANEL_BLUE) {
			SearchSquared(0, i, 1);
		}
		else {
			SearchSquared(0, i, 0);
		}
		
		if (mStaticObject(mMaxX - 1, i).getPanel() == StaticObject::Panel::PANEL_BLUE) {
			SearchSquared(mMaxX - 1, i, 1);
		}
		else {
			SearchSquared(mMaxX - 1, i, 0);
		}
		
	}

	return;
}

void Algorithm::setEnemySquared() {

	for (int i = 0; i < mMaxY; ++i) {
		for (int j = 0; j < mMaxX; ++j) {
			mStaticObject(j, i).setSquared(true);
		}
	}

	for (int i = 0; i < mMaxX; ++i) {
		if (mStaticObject(i, 0).getPanel() == StaticObject::Panel::PANEL_RED) {
			SearchSquared(i, 0, 3);
		}
		else {
			SearchSquared(i, 0, 2);
		}
		if (mStaticObject(i, mMaxY - 1).getPanel() == StaticObject::Panel::PANEL_RED) {
			SearchSquared(i, mMaxY - 1, 3);
		}
		else {
			SearchSquared(i, mMaxY - 1, 2);
		}

		//GameLib::cout << i << " :" << mStaticObject(i, i).getSquared() << GameLib::endl;
	}

	for (int i = 0; i < mMaxY; ++i) {
		if (mStaticObject(0, i).getPanel() == StaticObject::Panel::PANEL_RED) {
			SearchSquared(0, i, 3);
		}
		else {
			SearchSquared(0, i, 2);
		}

		if (mStaticObject(mMaxX - 1, i).getPanel() == StaticObject::Panel::PANEL_RED) {
			SearchSquared(mMaxX - 1, i, 3);
		}
		else {
			SearchSquared(mMaxX - 1, i, 2);
		}
		//GameLib::cout << i << " :" << mStaticObject(i, i).getSquared() << GameLib::endl;
	}

	return;
}

//囲み判定を探す 再帰処理を行っている
//最初に全ての囲みフラグをtrueにしているが、探索していく内にfalseになっていく
//modeの値は、0,1はプレイヤーの処理、2,3は敵の処理で分けている
void Algorithm::SearchSquared(int x, int y, int mode) {
	mStaticObject(x, y).setSquared(false);
	if (mode == 0) {
		if (x + 1 < mMaxX) {
			if (mStaticObject(x + 1, y).getPanel() == StaticObject::Panel::PANEL_BLUE && mStaticObject(x + 1, y).getSquared() == true) {
				mode = 1;
				SearchSquared(x + 1, y, mode);
				mode = 0;
			}
			else if(mStaticObject(x + 1, y).getSquared() == true){
				SearchSquared(x + 1, y, mode);
			}
		}
		if (x - 1 >= 0) {
			if (mStaticObject(x - 1, y).getPanel() == StaticObject::Panel::PANEL_BLUE && mStaticObject(x - 1, y).getSquared() == true) {
				mode = 1;
				SearchSquared(x - 1, y, mode);
				mode = 0;
			}
			else if (mStaticObject(x - 1, y).getSquared() == true) {
				SearchSquared(x - 1, y, mode);
			}
		}
		if (y + 1 < mMaxY) {
			if (mStaticObject(x, y + 1).getPanel() == StaticObject::Panel::PANEL_BLUE && mStaticObject(x, y + 1).getSquared() == true) {
				mode = 1;
				SearchSquared(x, y + 1, mode);
				mode = 0;
			}
			else if (mStaticObject(x, y + 1).getSquared() == true) {
				SearchSquared(x, y + 1, mode);
			}
		}
		if (y - 1 >= 0) {
			if (mStaticObject(x, y - 1).getPanel() == StaticObject::Panel::PANEL_BLUE && mStaticObject(x, y - 1).getSquared() == true) {
				mode = 1;
				SearchSquared(x, y - 1, mode);
				mode = 0;
			}
			else if (mStaticObject(x, y - 1).getSquared() == true) {
				SearchSquared(x, y - 1, mode);
			}
		}
	}

	else if (mode == 1) {
		if (x + 1 < mMaxX) {
			if (mStaticObject(x + 1, y).getPanel() == StaticObject::Panel::PANEL_BLUE && mStaticObject(x + 1, y).getSquared() == true) {
				SearchSquared(x + 1, y, mode);
			}
		}
		if (x - 1 >= 0) {
			if (mStaticObject(x - 1, y).getPanel() == StaticObject::Panel::PANEL_BLUE && mStaticObject(x - 1, y).getSquared() == true) {
				SearchSquared(x - 1, y, mode);
			}
		}
		if (y + 1 < mMaxY) {
			if (mStaticObject(x, y + 1).getPanel() == StaticObject::Panel::PANEL_BLUE && mStaticObject(x, y + 1).getSquared() == true) {
				SearchSquared(x, y + 1, mode);
			}
		}
		if (y - 1 >= 0) {
			if (mStaticObject(x, y - 1).getPanel() == StaticObject::Panel::PANEL_BLUE && mStaticObject(x, y - 1).getSquared() == true) {
				SearchSquared(x, y - 1, mode);
			}
		}
	}

	else if (mode == 2) {
		if (x + 1 < mMaxX) {
			if (mStaticObject(x + 1, y).getPanel() == StaticObject::Panel::PANEL_RED && mStaticObject(x + 1, y).getSquared() == true) {
				mode = 3;
				SearchSquared(x + 1, y, mode);
				mode = 2;
			}
			else if (mStaticObject(x + 1, y).getSquared() == true) {
				SearchSquared(x + 1, y, mode);
			}
		}
		if (x - 1 >= 0) {
			if (mStaticObject(x - 1, y).getPanel() == StaticObject::Panel::PANEL_RED && mStaticObject(x - 1, y).getSquared() == true) {
				mode = 3;
				SearchSquared(x - 1, y, mode);
				mode = 2;
			}
			else if (mStaticObject(x - 1, y).getSquared() == true) {
				SearchSquared(x - 1, y, mode);
			}
		}
		if (y + 1 < mMaxY) {
			if (mStaticObject(x, y + 1).getPanel() == StaticObject::Panel::PANEL_RED && mStaticObject(x, y + 1).getSquared() == true) {
				mode = 3;
				SearchSquared(x, y + 1, mode);
				mode = 2;
			}
			else if (mStaticObject(x, y + 1).getSquared() == true) {
				SearchSquared(x, y + 1, mode);
			}
		}
		if (y - 1 >= 0) {
			if (mStaticObject(x, y - 1).getPanel() == StaticObject::Panel::PANEL_RED && mStaticObject(x, y - 1).getSquared() == true) {
				mode = 3;
				SearchSquared(x, y - 1, mode);
				mode = 2;
			}
			else if (mStaticObject(x, y - 1).getSquared() == true) {
				SearchSquared(x, y - 1, mode);
			}
		}
	}

	else if (mode == 3) {
		if (x + 1 < mMaxX) {
			if (mStaticObject(x + 1, y).getPanel() == StaticObject::Panel::PANEL_RED && mStaticObject(x + 1, y).getSquared() == true) {
				SearchSquared(x + 1, y, mode);
			}
		}
		if (x - 1 >= 0) {
			if (mStaticObject(x - 1, y).getPanel() == StaticObject::Panel::PANEL_RED && mStaticObject(x - 1, y).getSquared() == true) {
				SearchSquared(x - 1, y, mode);
			}
		}
		if (y + 1 < mMaxY) {
			if (mStaticObject(x, y + 1).getPanel() == StaticObject::Panel::PANEL_RED && mStaticObject(x, y + 1).getSquared() == true) {
				SearchSquared(x, y + 1, mode);
			}
		}
		if (y - 1 >= 0) {
			if (mStaticObject(x, y - 1).getPanel() == StaticObject::Panel::PANEL_RED && mStaticObject(x, y - 1).getSquared() == true) {
				SearchSquared(x, y - 1, mode);
			}
		}
	}

	return;
}

int Algorithm::getPlayerPoint() {
	int sum = 0;
	setPlayerSquared();
	for (int i = 0; i < mMaxX; ++i) {
		for (int j = 0; j < mMaxY; ++j) {
			if (mStaticObject(i, j).getPanel() == StaticObject::Panel::PANEL_BLUE) {
				sum += mStaticObject(i, j).getPoint();
			}
			if (mStaticObject(i, j).getSquared() == true) {
				sum += abs(mStaticObject(i, j).getPoint());
			}
		}
	}
	return sum;
}

int Algorithm::getEnemyPoint() {
	int sum = 0;
	setEnemySquared();
	for (int i = 0; i < mMaxX; ++i) {
		for (int j = 0; j < mMaxY; ++j) {
			if (mStaticObject(i, j).getPanel() == StaticObject::Panel::PANEL_RED) {
				sum += mStaticObject(i, j).getPoint();
			}
			if (mStaticObject(i, j).getSquared() == true) {
				sum += abs(mStaticObject(i, j).getPoint());
			}
		}
	}
	return sum;
}

//TODO
void Algorithm::not_Thinking_Salgorithm(int x, int y, int count, int loop, int playerNumber) {

	int mMX;
	int mMY;
	StaticObject::Panel *mfPane = new StaticObject::Panel[mMaxX * mMaxY];

	for (int i = 0; i < mMaxX * mMaxY; ++i) {
		mfPane[i] = mStaticObject(i % mMaxX, i / mMaxX).getPanel();
	}

	int max = 0, now = 0;

	for (int i = 0; i < loop; ++i) {
		switch (rand() % 3) {

		case 0:
			mMX = 0;
			break;
		case 1:
			if (x + 1 < mMaxX) {
				mMX = 1;
			}
			else {
				mMX = -1;
			}
			break;
		case 2:
			if (x - 1 >= 0) {
				mMX = -1;
			}
			else {
				mMX = 1;
			}
			break;
		}

		switch (rand() % 3) {

		case 0:
			mMY = 0;
			break;
		case 1:
			if (y + 1 < mMaxY) {
				mMY = 1;
			}
			else {
				mMY = -1;
			}
			break;
		case 2:
			if (y - 1 >= 0) {
				mMY = -1;
			}
			else {
				mMY = 1;
			}
			break;
		}
		if (mMX != 0 || mMX != 0) {
			now = randomMove(x + mMX, y + mMY, 0, count);
		}
		if (now > max) {
			max = now;
			mPointingX[playerNumber] = x + mMX;
			mPointingY[playerNumber] = y + mMY;
		}

		for (int i = 0; i < mMaxX * mMaxY; ++i) {
			mStaticObject(i % mMaxX, i / mMaxX).setPanel(mfPane[i]);
		}
	}

}


//TODO : 得点がおかしい
int Algorithm::randomMove(int x, int y, int bonus, int count) {
	if (count <= 0) {
		setPlayerSquared();
		int ans = getPlayerPoint() + bonus;
		//GameLib::cout << "ans :" << ans << GameLib::endl;
		cleanSquared();
		return ans;
	}

	mStaticObject(x, y).setPanel(StaticObject::Panel::PANEL_BLUE);

	int moveX = 0;
	int moveY = 0;

	switch (rand() % 3) {

	case 0:
		moveX = 0;
		break;
	case 1:
		if (x + 1 < mMaxX) {
			moveX = 1;
		}
		else {
			moveX = -1;
		}
		break;
	case 2:
		if (x - 1 >= 0) {
			moveX = -1;
		}
		else {
			moveX = 1;
		}
		break;
	}

	switch (rand() % 3) {

	case 0:
		moveY = 0;
		break;
	case 1:
		if (y + 1 < mMaxY) {
			moveY = 1;
		}
		else {
			moveY = -1;
		}
		break;
	case 2:
		if (y - 1 >= 0) {
			moveY = -1;
		}
		else {
			moveY = 1;
		}
		break;
	}

	if (mStaticObject(x + moveX, y + moveY).getPanel() != StaticObject::Panel::PANEL_BLUE) {
		if (mStaticObject(x + moveX, y + moveY).getPanel() == StaticObject::Panel::PANEL_NONE) {
			count -= 1;
		}
		else {
			count -= 2;
			bonus += mStaticObject(x + moveX, y + moveY).getPoint();
		}
		return randomMove(x + moveX, y + moveY, bonus, count);
	}
	else {
		count -= 1;
		return randomMove(x + moveX, y + moveY, bonus, count);
	}

	/*
	int countB = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (x + j < 0 || x + j >= mMaxX || y + i < 0 || y + i >= mMaxY) {
				//何もしない
			}
			else {
				if (i != 0 || j != 0) {
					countB++;
				}
			}
		}
	}

	//カウントがゼロになるのはおかしい
	
	if (countB == 0) {
		return -1;
	}

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (x + j < 0 || x + j >= mMaxX || y + i < 0 || y + i >= mMaxY) {
				//何もしない
			}
			else {
				if ((int)(rand()) % 2 == 1 || countB == 1) {
					count -= 1;
					return randomMove(x + j, y + i, bonus, count);
				}
				else {
					countB--;
				}
			}
		}
	}
	*/
}

int Algorithm::abs(int x) {
	return (x >= 0) ? x : x * -1;
}
