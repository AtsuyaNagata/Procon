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
	class Parent;  //���C���Ŏg���I�u�W�F�N�g
	class Algorithm;  //������

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
		Array2D<StaticObject> mStaticObject;  //�ÓI(�����Ȃ�)�I�u�W�F�N�g
		DynamicObject *mDynamicObject; //���I(�߂����ᓮ��)�I�u�W�F�N�g

		Image* mFont;
		Image* mFont2;
		Image* mBackGround;

		GameLib::Input::Mouse* mMouse; //�}�E�X�̏o�͂��󂯎��

		int massX;  //�}�X�̍��W(X���W)<-�}�X�ڂ̒l�A�A�i���O�Ȓl�ł͂Ȃ��B
		int massY;  //�@����

		int PointingX;  //���Ɉړ�����ׂ��}�X
		int PointingY;

		int maxX;  //x���W�̍ő�l
		int maxY;  //y���W�̍ő�l

		bool mousePressed;  //�}�E�X��������Ă������̔���
		bool moved; //���������ǂ����̔���

		const int massSize;  //�}�X�̑傫��

		Algorithm *mAlgorithm;
	};
}

#endif