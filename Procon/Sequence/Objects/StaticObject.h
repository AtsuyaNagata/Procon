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
		mPoint = p; //�|�C���g�̓���
	}

	void operator=(const StaticObject &other);

	Panel getPanel() { return mPanel; }
	int getPoint() { return mPoint; }
	bool getSquared() { return mSquared; }

private:
	int mPoint;  //�|�C���g
	bool mSquared;  //�͂܂�Ă��邩�ǂ���
	bool mArgorithmFlag;
	bool mArgorithmFlag_S;
	Panel mPanel;
	const Image* mImg;

	//���W
	int mX;
	int mY;
};

#endif