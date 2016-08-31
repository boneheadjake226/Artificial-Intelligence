#include <string>

class Reflex_Agent {
	private:
		char *action;
	public:
		Reflex_Agent();
		void feed_percepts(int item1, int item2);
		char * get_action();
};