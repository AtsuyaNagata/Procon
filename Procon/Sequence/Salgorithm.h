#ifndef SEQUENCE_ALGORITHM_H_
#define SEQUENCE_ALGORITHM_H_

#include"Array2D.h"

class StaticObject;
class DynamicObject;

namespace Sequence {
	class Algorithm {
	public:

		Algorithm(Array2D<StaticObject> StObj, DynamicObject *DyObj, int maxX, int maxY);

		 //�I�u�W�F�N�g�����݂̔Ֆʂɖ߂�
		void CleanObject(Array2D<StaticObject> &StObj, DynamicObject *DyObj);

		void CleanPanel(Array2D<StaticObject> &StObj);


		//�͂܂ꂽ���ǂ������m�F����֐��Q
		void cleanSquared();
		void setPlayerSquared();
		void setEnemySquared();
		void SearchSquared(int x, int y, int mode);

		//���R�̓��_�v�Z
		int getPlayerPoint();

		//�G�R�̓��_�v�Z
		int getEnemyPoint();

		//�T���S���Y��
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
		Array2D<StaticObject> mStaticObject;  //�ÓI(�����Ȃ�)�I�u�W�F�N�g
		DynamicObject *mDynamicObject; //���I(�߂����ᓮ��)�I�u�W�F�N�g

		int *mPointingX;  //�T���S���Y���̖��ɒ@���o�����A���ɍs���ׂ��_(X���W)
		int *mPointingY;  //�T���S���Y���̖��ɒ@���o�����A���ɍs���ׂ��_(Y���W)

		const int mMaxX;
		const int mMaxY;

		bool mFinished;

		int mMaximumValue;
	};
}
#endif