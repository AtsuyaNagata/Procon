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

	void changeClick() { (mClick == true) ? mClick = false : mClick = true;}  //クリックフラグを反転させる
	void changeMoved() { (mMoved == true) ? mMoved = false : mMoved = true; }  //ムーブフラグを反転させる

	int getX() const { return mX; }
	int getY() const { return mY; }
	int getOldX() const { return mOldX; }
	int getOldY() const { return mOldY; }
	bool getClick() const { return mClick; }
	bool getMoved() const { return mMoved; }
	bool getPlayer() const { return mPlayer; }

private:
	bool mPlayer;  //プレイヤーか敵か

	int mX;  //x座標(アナログな値ではない)
	int mY;  //察して
	int mOldX;  //一つ手前にあったx座標
	int mOldY;  //察せよ

	int massSize;  //マスの大きさ

	bool mClick;
	bool mMoved;

	Image* mImg;   //画像データを読み込むクラス
};

#endif