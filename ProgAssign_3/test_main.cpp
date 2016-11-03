#include "State.h"
#include <iostream>
#include <functional>
#include <vector>
#include <queue>

using namespace std;

int main(){
	State *curr_state;
	bool *state_values;	
	int i = 0;
	priority_queue<State, vector<State>, Compare_Cost> p_queue;
	
	bool init_vars[] = {false,false,false,false,false};
	State init(0,0,init_vars);
	
	p_queue.push(init);
	
	while(true){
		int depth;
		int path_cost;
		state_values =  new bool[5];
		cout << "---State " << i << endl;
		cout << "Enter depth: ";
		cin >> depth;
		cout << "Enter path cost: ";
		cin >> path_cost;
		cout << "Bot a: ";
		cin >> state_values[0];
		cout << "Bot b: ";
		cin >> state_values[1];
		cout << "Bot c: ";
		cin >> state_values[2];
		cout << "Bot d: ";
		cin >> state_values[3];
		cout << "Power Pack: ";
		cin >> state_values[4];
		
		curr_state = new State(depth, path_cost, state_values);
		curr_state->set_parent(&init);
		
		i++;
		
		cout << "State " << i << "\tdept: " << curr_state->get_depth()
				<< "\tpath cost: " << curr_state->get_path_cost() << endl
					<< "State Values: ";
		for(int j=0; j < 5; j++){
			cout << state_values[j] << " ";
		}
		cout << endl << endl;
		
		p_queue.push(*curr_state);
	}
	
	return 0;
}