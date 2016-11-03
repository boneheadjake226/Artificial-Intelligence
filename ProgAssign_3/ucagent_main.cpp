#include "UCAgent.h"
#include <iostream>
#include <string>

using namespace std;



int main(int argc, char *argv[]){
	string start_side = argv[1];
	string goal_side;
	if(argc > 2){
		goal_side = argv[2];
	}else{
		goal_side = "";
	}
	bool init_vars[5];
	
	cout << "Program Started with: " << start_side << " " << goal_side <<endl;
	
	for(int i = 0; i < NUM_OF_BOTS + 1; i++){
		if(i < start_side.size()){
			switch (start_side.at(i)){
				case 'A' :
					init_vars[0] = false;
					break;
				case 'B' :
					init_vars[1] = false;
					break;
				case 'C' :
					init_vars[2] = false;
					break;
				case 'D' :
					init_vars[3] = false;
					break;
				case 'P' :
					init_vars[0] = false;
					break;
			}
		}
		
		if(i < goal_side.size()){
			switch (goal_side.at(i)){
				case 'A' :
					init_vars[0] = true;
					break;
				case 'B' :
					init_vars[1] = true;
					break;
				case 'C' :
					init_vars[2] = true;
					break;
				case 'D' :
					init_vars[3] = true;
					break;
				case 'P' :
					init_vars[0] = true;
					break;
			}
		}
	}
	
	State init(0, 0, init_vars);
	
	cout << init_vars[0] << " " << init_vars[1] << " " << init_vars[2] << endl;
	
	cout << "State initialized" << endl;
	
	UCAgent agent(&init);
	
	cout << "Agent initialized" <<endl;
	
	string * optimal_path = agent.find_optimal_path();
	cout << "Optimal path commands from agent:" << endl;
	for(int i = 0; i < optimal_path->size(); i++){
		cout << optimal_path[i] << endl;
	}
	
	return 0;
}