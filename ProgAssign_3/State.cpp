//State.cpp
#include "State.h"

State::State(int state_depth, int cost, bool state_vals[]){
	
	for(int i = 0; i < NUM_OF_BOTS + 1; i++){
		state_values[i] = state_vals[i];
	}
	
	depth = state_depth;
	path_cost = cost;
	parent = 0;
}

State::~State() {}

bool* State::get_state_values(){
	bool *vals = new bool[5];
	
	for(int i = 0; i < NUM_OF_BOTS + 1; i++){
		vals[i] = state_values[i];
	}
	
	return vals;
}

int State::get_path_cost(){ return path_cost; }

int State::get_depth(){ return depth; }

State* State::get_parent_state() { return parent;};

void State::set_parent(State *new_parent){
	parent = new_parent;
}

void State::print_state_data(){
	cout << "\tState Data" << endl;
	cout << "-State: ";
	for(int i = 0; i < NUM_OF_BOTS + 1; i++){
		cout << state_values[i] << " ";
	}
	cout << endl;
	
	cout << "-Parent State: ";
	for(int i = 0; i < NUM_OF_BOTS + 1; i++){
		cout << parent->state_values[i] << " ";
	}
	cout <<endl;
	
	cout << "-Path Cost: " << path_cost << endl;
	cout << "-Depth: " << depth << endl;
}