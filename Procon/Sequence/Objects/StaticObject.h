#ifndef STATIC_OBJECT_H_
#define STATIC_OBJECT_H_

class Image;

class StaticObject {
public:
	enum Panel {
		PANEL_NONE,
		PANEL_BLUE,
		PANEL_RED
	};

	StaticObject();
	StaticObject(const StaticObject& other);
	~StaticObject();

	void draw() const;
	void set(int x, int y, Panel);
	void setPanel(Panel);
	void setSquared(bool f) {
		mSquared = f;
	}

	void operator=(int p) {
		mPoint = p; //ポイントの入力
	}

	void operator=(const StaticObject &other);

	Panel getPanel() { return mPanel; }
	int getPoint() { return mPoint; }
	bool getSquared() { return mSquared; }

private:
	int mPoint;  //ポイント
	bool mSquared;  //囲まれているかどうか
	bool mArgorithmFlag;
	bool mArgorithmFlag_S;
	Panel mPanel;
	const Image* mImg;

	//座標
	int mX;
	int mY;
};

#endif