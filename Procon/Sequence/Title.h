#ifndef SEQUENCE_TITLE_H_
#define SEQUENCE_TITLE_H_

class Image;
namespace Sequence {
	class Parent;

	class Title {
	public:
		Title();
		~Title();
		void update(Parent* parent);

	private:
		Image *mImage; //�^�C�g���̉��
	};
}

#endif