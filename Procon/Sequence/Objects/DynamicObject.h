#ifndef DYNAMIC_OBJECT_H_
#define DYNAMIC_OBJECT_H_

class Image;

class DynamicObject {
public:
	DynamicObject();
	~DynamicObject();

	void draw();

	void set(int x, int y, bool player, int size);
	void set(int x, int y);
	void setOld(int x, int y);
	void operator=(const DynamicObject &other);

	void changeClick() { (mClick == true) ? mClick = false : mClick = true;}  //�N���b�N�t���O�𔽓]������
	void changeMoved() { (mMoved == true) ? mMoved = false : mMoved = true; }  //���[�u�t���O�𔽓]������

	int getX() const { return mX; }
	int getY() const { return mY; }
	int getOldX() const { return mOldX; }
	int getOldY() const { return mOldY; }
	bool getClick() const { return mClick; }
	bool getMoved() const { return mMoved; }
	bool getPlayer() const { return mPlayer; }

private:
	bool mPlayer;  //�v���C���[���G��

	int mX;  //x���W(�A�i���O�Ȓl�ł͂Ȃ�)
	int mY;  //�@����
	int mOldX;  //���O�ɂ�����x���W
	int mOldY;  //�@����

	int massSize;  //�}�X�̑傫��

	bool mClick;
	bool mMoved;

	Image* mImg;   //�摜�f�[�^��ǂݍ��ރN���X
};

#endif