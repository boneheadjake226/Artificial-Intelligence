#include "Conveyor_Belt.h"
#include "Reflex_State_Agent.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
	Reflex_State_Agent agent;
	string belta_file_name;
	string beltb_file_name;
	string r_agent_action;
	int belt_a_current, belt_a_next, belt_b_current,
			belt_b_next, slot_1 = 0, slot_2 = 0, picked_item = 0, current_power = 20;


	cout << "Input files must be in same directory as application file" << endl;
	cout << "Input conveyor belt_a test file directory: ";
	cin >> belta_file_name;
	cout << endl << "Input conveyor belt_b test file directory: ";
	cin >> beltb_file_name;

	Conveyor_Belt belt_a(belta_file_name);
	Conveyor_Belt belt_b(beltb_file_name);

	while(r_agent_action.compare("STOP") != 0){
		//Generate Percepts
		belt_a_current = belt_a.get_item_quality(0);
		belt_a_next = belt_a.get_item_quality(1);
		belt_b_current = belt_b.get_item_quality(0);
		belt_b_next = belt_b.get_item_quality(1);
		
		
		//Display percept inputs and send them to Reflex Agent
		cout << "Input Perception: " << belt_a_current << " " << belt_a_next 
				<< " " << belt_b_current << " " << belt_b_next << " " << current_power << endl;
		//Compute action and print agent's state		
		r_agent_action = agent.compute_action(belt_a_current, belt_a_next, belt_b_current,
										belt_b_next, current_power);
		//Output Action
		cout << "Output Action: " << r_agent_action << endl << endl;
		
		//Test Harness action taking proccess
		if(r_agent_action.compare("Advance A") == 0){
			//cout << "\nStepping belt a \n";
			belt_a.step_belt();
		}else if(r_agent_action.compare("Advance B") == 0){
			//cout << "\n Stepping belt b \n";
			belt_b.step_belt();
		}else if(r_agent_action.compare("Pick Up A") == 0){
			belt_a.pick_item();
		}else if(r_agent_action.compare("Pick Up B") == 0){
			belt_b.pick_item();
		}else if(r_agent_action.compare("Fill 1") == 0){
			slot_1 = picked_item;
			picked_item = 0;
		}else if(r_agent_action.compare("Fill 2") == 0){
			slot_2 = picked_item;
			picked_item = 0;
		}else if(r_agent_action.compare("Drop 1") == 0){
			slot_1 = 0;
		}else if(r_agent_action.compare("Drop 2") == 0){
			slot_2 = 0;
		}
		
		if(current_power != 0) {
			current_power--;
		}
	}
	return 0;
}
