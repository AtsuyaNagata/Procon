#ifndef GRAND_PARENT_H_
#define GRAND_PARENT_H_

namespace Sequence {

	class Title;
	class Main;
	class Menu;

	class Parent {

	public:
		//シーケンスの状態
		enum NextSequence {
			NEXT_TITLE,
			NEXT_MAIN,
			NEXT_MENU,

			NEXT_NONE
		};

		void update();
		void changeSequence(NextSequence);

		static Parent* instance();
		static void create();
		static void destroy();

	private:
		Parent();
		~Parent();

		NextSequence mNextSequence;

		Title* mTitle;
		Main* mMain;
		//Menu* mMenu;

		static Parent* mParentInstance;
	};
}
#endif