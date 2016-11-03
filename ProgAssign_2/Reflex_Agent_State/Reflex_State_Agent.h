#include <string>
#include <iostream>

using namespace std;


class Reflex_State_Agent{
	private:
		int slot_1_state, slot_2_state, picked_item_state;
		string agent_action;
	public:
		Reflex_State_Agent();
		~Reflex_State_Agent();
		string compute_action(int belta_current, int belta_next,
                     int beltb_current, int beltb_next, int current_power);
		void print_agent_state(int belta_current, int belta_next, int beltb_current,
									int beltb_next, int current_power);
};