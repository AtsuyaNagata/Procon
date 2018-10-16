#include"Sequence/SMain.h"
#include"Sequence/Objects/DynamicObject.h"
#include"Sequence/Objects/StaticObject.h"
#include"File.h"
#include"Image.h"
#include"Sequence/GrandParent.h"
#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Mouse.h"
#include "Salgorithm.h"

using namespace Sequence;
using namespace GameLib::Input;

Main::Main()
	: massSize(18),           //�}�X�̑傫��
	maxX(0),
	maxY(0),
	mousePressed(false),
	moved(false),
	mDynamicObject(0),      //�߂����ᓮ���I�u�W�F�N�g�̏�����
	mFont(0),               //�t�H���g�̏�����
	PointingX(0),           //���ɍs���ׂ��ꏊ���|�C���g���邽�߂̍��W�f�[�^�̏�����
	PointingY(0)
{
	mMouse = new Mouse;
	mFont = new Image("Data/image/font.dds");
	mFont2 = new Image("Data/image/font2.dds");
	mBackGround = new Image("Data/image/changed.dds");
	File file("Data/stage/stage1.txt");              //�X�e�[�W�ǂݍ���

	int charaPoint = 0;
	charaPoint += charaToInteger(&file.data()[charaPoint], &maxX);
	charaPoint += charaToInteger(&file.data()[charaPoint], &maxY);

	mStaticObject.setSize(maxX, maxY);    //�X�e�[�W�̑傫��
	mDynamicObject = new DynamicObject[4];

	//StaticObject�̏�����
	int point = 0;
	for (int i = 0; i < maxX; ++i) {
		for (int j = 0; j < maxY; ++j) {
			if (charaToInteger(&file.data()[charaPoint], &point) != 1) {
				mStaticObject(i, j).set(i * massSize, j * massSize, StaticObject::Panel::PANEL_NONE);
				mStaticObject(i, j) = point;
				mStaticObject(i, j).draw();
				drawString(i * massSize, j * massSize, mStaticObject(i, j).getPoint());
			}
			else {
				j -= 1;
			}
			charaPoint += charaToInteger(&file.data()[charaPoint], &point);
		}
	}

	int x = 0, y = 0;
	//�_�C�i�~�b�N�I�u�W�F�N�g�̏�����
	for (int i = 0; i < 2; ++i) {
		charaPoint += charaToInteger(&file.data()[charaPoint], &x);
		charaPoint += charaToInteger(&file.data()[charaPoint], &y);
		x--;        //���W�̊J�n�n�_��0�ɒ�������B
		y--;        //��Ɠ���
		mDynamicObject[i].set(x, y, true, massSize);
		mStaticObject(x, y).setPanel(StaticObject::Panel::PANEL_BLUE);
		mStaticObject(x, y).draw();
		mDynamicObject[i].draw();

		mDynamicObject[i + 2].set(maxX - 1 - x, y, false, massSize);  //max�T�C�Y��1�傫���̂�1����
		mStaticObject(maxX - 1 - x, y).setPanel(StaticObject::Panel::PANEL_RED);
		mStaticObject(maxX - 1 - x, y).draw();
		mDynamicObject[i + 2].draw();
	}

	//�A���S���Y���̐����Ɠ���m�F
	mAlgorithm = new Algorithm(mStaticObject, mDynamicObject, maxX, maxY);

	mAlgorithm->CleanObject(mStaticObject, mDynamicObject);
	
	mAlgorithm->not_Thinking_Salgorithm(mDynamicObject[0].getX(), mDynamicObject[0].getY(), 4, 5000, 0);
	mAlgorithm->not_Thinking_Salgorithm(mDynamicObject[1].getX(), mDynamicObject[1].getY(), 4, 5000, 1);
	drawMark(mAlgorithm->getPointX(0), mAlgorithm->getPointY(0));
	drawMark(mAlgorithm->getPointX(1), mAlgorithm->getPointY(1));
	

	//���_���̃L�����N�^�[�̕`��
	mBackGround->draw(250, 10, 48, 0, 16, 16);
	mBackGround->draw(250, 10, 0, 0, 16, 16);
	//����(�G�L����)
	mBackGround->draw(250, 30, 48, 0, 16, 16);
	mBackGround->draw(250, 30, 16, 0, 16, 16);
}

Main::~Main() {
}

void Main::update(Parent* parent) {
	if (mousePressed == false) {  //�}�E�X���u������Ă������v�𔻒�

		if (mMouse->isOn(Mouse::BUTTON_LEFT) || mMouse->isOn(Mouse::BUTTON_RIGHT) || mMouse->isOn(Mouse::BUTTON_MIDDLE)) {  //�}�E�X���u������Ă���v���𔻒�

			if (0 < mMouse->x() && 0 < mMouse->y() && mMouse->x() < maxX * massSize && mMouse->y() < maxY * massSize) {  //�A�N�Z�X�ᔽ���m(�厖)

				whereMass(mMouse->x(), mMouse->y());  //�}�X�̏ꏊ���m�肷��

				if (mMouse->isOn(Mouse::BUTTON_LEFT)) {  //���N���b�N����Ă�����
					if (mStaticObject(massX, massY).getPanel() == StaticObject::Panel::PANEL_BLUE) {  //���X�F��������
						mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_NONE);
					}
					else {
						mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_BLUE);
					}
					mStaticObject(massX, massY).draw();
					drawString(massX * massSize, massY * massSize, mStaticObject(massX, massY).getPoint());
				}

				if (mMouse->isOn(Mouse::BUTTON_RIGHT)) {
					if (mStaticObject(massX, massY).getPanel() == StaticObject::Panel::PANEL_RED) {
						mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_NONE);
					}
					else {
						mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_RED);
					}
					mStaticObject(massX, massY).draw();
					drawString(massX * massSize, massY * massSize, mStaticObject(massX, massY).getPoint());
				}

				//�v���C���[or�G�̑I��
				if (mMouse->isOn(Mouse::BUTTON_MIDDLE)) {
					for (int i = 0; i < 4; ++i) {
						if (mDynamicObject[i].getClick() == true) {  //�������I�I�u�W�F�N�g���N���b�N����Ă����Ԃł����
							//�l�̃Z�b�g
							mDynamicObject[i].changeMoved();
							mAlgorithm->setFinished(false);
							mDynamicObject[i].set(massX, massY);
							//�`��
							mStaticObject(mDynamicObject[i].getOldX(), mDynamicObject[i].getOldY()).draw();
							drawString(mDynamicObject[i].getOldX() * massSize, mDynamicObject[i].getOldY() * massSize, mStaticObject(mDynamicObject[i].getOldX(), mDynamicObject[i].getOldY()).getPoint());
							if (mDynamicObject[i].getPlayer() == true) {  //�v���C���[��������
								mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_BLUE);
							}
							else {  //�G��������
								mStaticObject(massX, massY).setPanel(StaticObject::Panel::PANEL_RED);
							}
							mStaticObject(massX, massY).draw();
							//�����͏o�͂��Ȃ�
						}
					}

					//changeClick()�͏�̃R�[�h�ƌ��p
					for (int i = 0; i < 4; ++i) {
						if (mDynamicObject[i].getX() == massX && mDynamicObject[i].getY() == massY) {  //�����N���b�N��Ƀ_�C�i�~�b�N�I�u�W�F�N�g����������
							mDynamicObject[i].changeClick();
							mDynamicObject[i].setOld(massX, massY);
						}
						else {
							//�������Ȃ�
						}
					}
				}
				
				mousePressed = true;  //�������ȁH
				for (int i = 0; i < 4; ++i) {
					mDynamicObject[i].draw();
				}

				//�A���S���Y���N���X�̃f�[�^���N���[������
				mAlgorithm->CleanObject(mStaticObject, mDynamicObject);
				//�N���[�������㓾�_�`����s��(�A���S���Y���N���X�p�̓��_�v�Z�𗬗p���Ă邽��)
				drawPoint(mAlgorithm->getPlayerPoint(), mAlgorithm->getEnemyPoint());
			}
		}
	}

	else if(!(mMouse->isOn(Mouse::BUTTON_LEFT) || mMouse->isOn(Mouse::BUTTON_RIGHT) || mMouse->isOn(Mouse::BUTTON_MIDDLE))){
		mousePressed = false;  //�����Ȃ������̂�...���ȊO�̓z��...
		for (int i = 0; i < 2; ++i) {
			if (mDynamicObject[i].getMoved() == true) {
				if (mAlgorithm->getFinished() == false) {
					//�A���S���Y���N���X�̃f�[�^�����̔Ֆʃf�[�^�ɂ���
					mAlgorithm->CleanObject(mStaticObject, mDynamicObject);
					//�`������ꂢ�ɂ��ă|�C���g��ς���
					MarkClean(mAlgorithm->getPointX(i), mAlgorithm->getPointY(i));
					//�A���S���Y���̊J�n
					mAlgorithm->not_Thinking_Salgorithm(mDynamicObject[i].getX(), mDynamicObject[i].getY(), 4, 5000, i);
					mAlgorithm->setFinished(true);
				}

				//�t���O�̃N���[��
				mDynamicObject[i].changeMoved();
				//�����`��
				mStaticObject(mAlgorithm->getPointX(i), mAlgorithm->getPointY(i)).draw();
				//�������I�I�u�W�F�N�g�̈ړ��悪�|�C���g�_�Ƃ��Ԃ�����
				if(mAlgorithm->getPointX(i) == mDynamicObject[i].getX() && mAlgorithm->getPointY(i) == mDynamicObject[i].getY())
					mDynamicObject[i].draw();
				//���Ԃ�Ȃ�������
				else
					drawString(mAlgorithm->getPointX(i) * massSize, mAlgorithm->getPointY(i) * massSize, mStaticObject(mAlgorithm->getPointX(i), mAlgorithm->getPointY(i)).getPoint());
				
				//�l�̕ύX
				//mAlgorithm->getLargestNumber(i);
				//�ύX��`��
				drawMark(mAlgorithm->getPointX(i), mAlgorithm->getPointY(i));
			}
		}
	}
}

void Main::whereMass(int x, int y) {    //���W�}�X�ϊ�
	massX = x / massSize;
	massY = y / massSize;
}

void Main::drawString(int x, int y, int point) {
	char text[2];
	int j = 0;
	
	if (point < 0) {
		mFont->draw(x, y, 15 * 8, 3 * 16, 8, 16);
		point *= -1;
	}

	for (int i = 0; i < 2; ++i) {
		text[i] = 48;
	}

	for (int i = point % 100; i >= 1; i /= 10) {
		if (i == 1) {
			text[j] = 49;
			break;
		}
		text[j] = (i % 10) + 48;
		++j;
	}

	for (int i = 0; i < sizeof(text); ++i) {
		mFont->draw(x + ((1 - i) * 8), y, ((text[i] - 32) % 16) * 8, ((text[i] - 32) / 16) * 16, 8, 16);
	}
}

int Main::charaToInteger(char const * c, int *point) {
	bool minus = false;
	*point = 0;

	//�����J�����ꂾ������1�����Ԃ��ďI��
	if (c[0] == ' ' || c[0] == ':') {
		return 1;
	}

	for (int i = 0; i < 3; ++i) {
		if (c[i] == '-') {  //�}�C�i�X�����邩�̔���
			minus = true;
		}
		else {
			if (c[i + 1] == ' ' || c[i + 1] == ':') {  //�������̋L��������ΏI������
				*point += c[i] - 48;
				if (minus) {
					*point *= -1;
				}
				return i + 2;
			}
			else {
				*point += 10 * (c[i] - 48);
			}
		}
	}
	return 3;
}

void Main::drawMark(int PointingX, int PointingY) {
	mFont2->draw(PointingX * massSize - 2, PointingY * massSize, 8 * 11, 16 * 3, 8, 16);  //�F�u[�v��\��
	mFont2->draw(PointingX * massSize + 10, PointingY * massSize, 8 * 13, 16 * 3, 8, 16);  //�F�u]�v��\��
}

void Main::MarkClean(int x, int y)
{
	mStaticObject(x, y).draw();
	for (int i = 0; i < 2; ++i) {
		if (mDynamicObject[i].getX() == x && mDynamicObject[i].getY() == y) {

			mDynamicObject[i].draw();
			return;
		}
	}
	drawString(x * massSize, y * massSize, mStaticObject(x, y).getPoint());
}

void Main::drawPoint(int Ppoint, int Epoint) 
{
	/*���R�̃|�C���g*/
	mBackGround->draw(270, 10, 48, 0, 10, 16);         //�����̃N���[��
	if (Ppoint < 0) {
		Ppoint *= -1;
		mFont2->draw(270, 10, 8 * 13, 0, 8, 16);       //�}�C�i�X�����̕`��
	}
	else {
		mFont2->draw(270, 10, 8 * 11, 0, 8, 16);       //�v���X�����̕`��
	}
	int digits = Ppoint / 100;
	mBackGround->draw(280, 10, 48, 0, 10, 16);         //3���ڂ̃N���[��
	mFont2->draw(280, 10, 8 * digits, 16 * 1, 8, 16);  //3���ڂ̐���\��

	digits = Ppoint % 100;
	digits = digits / 10;
	mBackGround->draw(290, 10, 48, 0, 10, 16);         //2���ڂ̃N���[��
	mFont2->draw(290, 10, 8 * digits, 16 * 1, 8, 16);  //2���ڂ̐���\��

	digits = Ppoint % 10;
	mBackGround->draw(300, 10, 48, 0, 10, 16);         //1���ڂ̃N���[��
	mFont2->draw(300, 10, 8 * digits, 16 * 1, 8, 16);  //1���ڂ̐���\��

	/*����R�̃|�C���g*/
	mBackGround->draw(270, 30, 48, 0, 10, 16);         //�����̃N���[��
	if (Epoint < 0) {
		Epoint *= -1;
		mFont2->draw(270, 30, 8 * 13, 0, 8, 16);       //�}�C�i�X�����̕`��
	}
	else {
		mFont2->draw(270, 30, 8 * 11, 0, 8, 16);       //�v���X�����̕`��
	}
	digits = Epoint / 100;
	mBackGround->draw(280, 30, 48, 0, 10, 16);         //3���ڂ̃N���[��
	mFont2->draw(280, 30, 8 * digits, 16 * 1, 8, 16);  //3���ڂ̐���\��

	digits = Epoint % 100;
	digits = digits / 10;
	mBackGround->draw(290, 30, 48, 0, 10, 16);         //2���ڂ̃N���[��
	mFont2->draw(290, 30, 8 * digits, 16 * 1, 8, 16);  //2���ڂ̐���\��

	digits = Epoint % 10;
	mBackGround->draw(300, 30, 48, 0, 10, 16);         //1���ڂ̃N���[��
	mFont2->draw(300, 30, 8 * digits, 16 * 1, 8, 16);  //1���ڂ̐���\��
}