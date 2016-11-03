//UCAgent.cpp

#include "UCAgent.h"
#include <windows.h>

//Constructor
//@param init_state: Starting state for uniform cost agent
UCAgent::UCAgent(State *init_state){
	curr_state = init_state;
	nodes_expanded = 0;
}

UCAgent::~UCAgent() {	}

//Expands a single state and places them in the priority queue
void UCAgent::expand_state(State *state_to_expand){
	/*
		Create child states
		-Generate true false values
		-increment depth
		-calculate path cost
		-initialize
		-push to priority queue
	*/
	bool * curr_state_vals = state_to_expand->get_state_values();
	bool pack_side = curr_state_vals[NUM_OF_BOTS];
	
	for(int i = 0; i < NUM_OF_BOTS; i++){
		if(curr_state_vals[i] == pack_side){
			for(int j = i; j < NUM_OF_BOTS; j++){
				if(curr_state_vals[i] == curr_state_vals[j]){
					State *new_state;
					int path_cost = state_to_expand->get_path_cost();
					int depth = state_to_expand->get_depth() + 1;
					bool new_state_vals[NUM_OF_BOTS + 1];
					
					//set state values
					for(int k = 0; k < NUM_OF_BOTS + 1; k++){
						new_state_vals[k] = curr_state_vals[k];
					}
					new_state_vals[i] = !new_state_vals[i];
					if(i != j){
						new_state_vals[j] = !new_state_vals[j];
					}
					
					
					new_state_vals[NUM_OF_BOTS] = !new_state_vals[NUM_OF_BOTS];
										
					//Calculate path cost
					int robot = j;
					switch (robot){
						case bot_a :
							path_cost += BOT_A_SPEED;
							break;
						case bot_b :
							path_cost += BOT_B_SPEED;
							break;
						case bot_c :
							path_cost += BOT_C_SPEED;
							break;
						case bot_d :
							path_cost += BOT_D_SPEED;
							break;
					}
					
					new_state = new State(depth, path_cost, new_state_vals);
					new_state->set_parent(state_to_expand);
					
					p_queue.push(*new_state);
					/*
					cout << "---state values pack: " << curr_state_vals[4] << endl;
					cout << "---Pack Side: " << pack_side <<endl;
					cout << "---Parent path cost: " << state_to_expand->path_cost << endl;
					
					new_state->print_state_data();
					*/
					Sleep(300);
				}
			}
		}
	}
	
	// print meta data
}

//Finds the optimal path from initial state to goal state
string * UCAgent::find_optimal_path(){
	nodes_expanded ++;
	
	//Expand Current Node
	expand_state(curr_state);
	
	//Pop next best node
	*curr_state = p_queue.top();
	

	
	p_queue.pop();
	//Expand and pop till goal state is reached
	while(!check_goal_state(curr_state->get_state_values())){
		cout << "---Expanding Popped State---"<< endl;
		curr_state->print_state_data();
		cout << "----------------------------" << endl;
		
		expand_state(curr_state);
		nodes_expanded ++;
		
		cout << "---Expanded State---"<< endl;
		curr_state->print_state_data();
		cout << "----------------------------" << endl;
		
		*curr_state = p_queue.top();
		p_queue.pop();
	}
	
	cout << "Finished path finding" << endl;
	//return optimal path cost
	deque<State> path = trace_path_to_init();
	
	cout << "Finished path trace" << endl;
	
	return get_commands(path);
}

//Checks values of a state for equality to the goal state
bool UCAgent::check_goal_state(bool state_vals[]){
	for(int i = 0; i < NUM_OF_BOTS + 1; i++){
		if(!state_vals[i]){
			cout << "Not Goal State" << endl;
			return false;
		}
	}
	
	cout << "Goal State Reached!!!!"<<endl;
	for(int i = 0; i < 100; i++){
		cout << ">" << endl;
	}
	Sleep(500);
	return true;
}

/*
	Creates a deque<string> representing the path from initial state
	to goal state.
	
	-changes value of curr_state to initial state of UCAgent
*/
deque<State> UCAgent::trace_path_to_init(){
	deque<State> path;
	path.push_front(*curr_state);
	
	while(curr_state->get_depth() != 0){
		curr_state = curr_state->get_parent_state();
		path.push_front(*curr_state);
	}
	
	return path;
}

string * UCAgent::get_commands(deque<State> path){
	string *commands = new string[path.size()];
	int i = 0;
	while(path.size() > 0){
		int bot_1 = -1;
		int bot_2 = -1;
		bool side;
		bool parent_state[NUM_OF_BOTS+1] = {path.front().get_state_values()};
		path.pop_front();
		bool child_state[NUM_OF_BOTS+1] = {path.front().get_state_values()};
		path.pop_front();
		//power pack side change
		side = child_state[NUM_OF_BOTS];
		string command = "Move robot(s) ";
		
		for(int k = 0; k < NUM_OF_BOTS; k++){
			if(parent_state[k] != child_state[k]){
				switch(k){
					case 0 :
						command.append("A ");
						break;
					case 1 :
						command.append("B ");
						break;
					case 2 :
						command.append("C ");
						break;
					case 3 :
						command.append("D ");
						break;
				}
			}
		}
		
		if(side){
			command.append(" to the goal side\n");
		} else{
			command.append(" to the starting side\n");
		}
		
		commands[i] = command;
		
		i++;
	}
	
	
	return commands;
}

















