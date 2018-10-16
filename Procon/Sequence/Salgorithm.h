#ifndef SEQUENCE_ALGORITHM_H_
#define SEQUENCE_ALGORITHM_H_

#include"Array2D.h"

class StaticObject;
class DynamicObject;

namespace Sequence {
	class Algorithm {
	public:

		Algorithm(Array2D<StaticObject> StObj, DynamicObject *DyObj, int maxX, int maxY);

		 //オブジェクトを現在の盤面に戻す
		void CleanObject(Array2D<StaticObject> &StObj, DynamicObject *DyObj);

		void CleanPanel(Array2D<StaticObject> &StObj);


		//囲まれたかどうかを確認する関数群
		void cleanSquared();
		void setPlayerSquared();
		void setEnemySquared();
		void SearchSquared(int x, int y, int mode);

		//自軍の得点計算
		int getPlayerPoint();

		//敵軍の得点計算
		int getEnemyPoint();

		//サルゴリズム
		void not_Thinking_Salgorithm(int x, int y, int count, int loop, int playerNumber);
		int randomMove(int x, int y, int bonus, int count);


		int abs(int x);
		
		int getPointX(int p) const { 
			if (p >= 0 && p < mMaximumValue) 
				return mPointingX[p]; 
			else 
				return -1; 
		}
		int getPointY(int p) const {
			if (p >= 0 && p < mMaximumValue)
				return mPointingY[p];
			else
				return -1;
		}

		bool getFinished() { return mFinished; }
		void setFinished(bool f) { mFinished = f; }

	private:
		Array2D<StaticObject> mStaticObject;  //静的(動かない)オブジェクト
		DynamicObject *mDynamicObject; //動的(めっちゃ動く)オブジェクト

		int *mPointingX;  //サルゴリズムの末に叩き出した、次に行くべき点(X座標)
		int *mPointingY;  //サルゴリズムの末に叩き出した、次に行くべき点(Y座標)

		const int mMaxX;
		const int mMaxY;

		bool mFinished;

		int mMaximumValue;
	};
}
#endif