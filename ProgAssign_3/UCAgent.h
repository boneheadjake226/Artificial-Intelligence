#include "State.h"
#include <queue>
#include <vector>
#include <functional>
#include <deque>
#include <iostream>
#include <string>

using namespace std;

const int BOT_A_SPEED = 1;
const int BOT_B_SPEED = 2;
const int BOT_C_SPEED = 5;
const int BOT_D_SPEED = 10;

enum robots {bot_a = 0, bot_b = 1, bot_c = 2, bot_d = 3};

class UCAgent{
	private:
		State *curr_state;
		int nodes_expanded;
		priority_queue<State, vector<State>, Compare_Cost> p_queue;
		bool check_goal_state(bool state_vals[]);
		deque<State> trace_path_to_init();
		void expand_state(State *state_to_expand);
		string * get_commands(deque<State>);
	public:
		UCAgent(State*);
		~UCAgent();
		string * find_optimal_path();
};