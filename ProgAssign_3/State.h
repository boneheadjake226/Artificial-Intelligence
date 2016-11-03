#include <iostream>

using namespace std;

const int NUM_OF_BOTS = 4;


class State{
	private:
		bool state_values[NUM_OF_BOTS + 1];
		int depth;
		State *parent;
	public:
		int path_cost;
		State(int state_depth, int cost, bool state_values[]);
		~State();
		bool* get_state_values();
		int get_path_cost();
		int get_depth();
		State* get_parent_state();
		void set_parent(State *new_parent);
		void print_state_data();
};


class Compare_Cost{
	public:	
		bool operator() ( State state_1, State state_2){
			return state_1.path_cost > state_2.path_cost;
		}
};