#include "Conveyor_Belt.h"
#include <string>
#include <iostream>

using namespace std;

string reflex_agent(int percept1, int percept2);

int main(){
	string input_file;
	string r_agent_action;
	int item1, item2;


	cout << "Input file must be in same directory as application file" << endl;
	cout << "Input conveyor belt test file directory: ";
	cin >> input_file;

	Conveyor_Belt main_belt(input_file);

	while(r_agent_action.compare("STOP") != 0){
		item1 = main_belt.get_item_quality(0);
		item2 = main_belt.get_item_quality(1);

		r_agent_action = reflex_agent(item1, item2);

		cout << "Input Perception: " << item1 << " " << item2 << endl;
		cout << "Output Action: " << r_agent_action << endl;

		if(r_agent_action.compare("ADVANCE") == 0){
			main_belt.step_belt();
		} else if(r_agent_action.compare("PICK UP") == 0){
			main_belt.pick_item();
		}
	}
}

string reflex_agent(int percept1, int percept2){
    string action;
    if(percept1 <= 0 ){
		if(percept2 == -1 && percept1 == -1){
			action = "STOP";
		} else{
			action = "ADVANCE";
		}
	}else if(percept1 > percept2){
		action = "PICK UP";
	}else {
		action = "ADVANCE";
	}
	return action;
}
