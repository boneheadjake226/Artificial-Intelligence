#include "Conveyor_Belt.h"
#include <string>
#include <iostream>

using namespace std;

string reflex_agent(int belta_current, int belta_next,
                     int beltb_current, int beltb_next, current_power);

//Reflex Agent state variables
int slot_1_state = 0, slot_2_state = 0, picked_item_state = 0;

int main(){
	string belta_file_name;
	string beltb_file_name
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
		blet_b_next = belt_b.get_item_quality(1);
		
		//Send Percepts to Reflex Agent
		r_agent_action = reflex_agent(belt_a_current, belt_a_next, belt_b_current,
										belt_b_next, current_power);
		
		//Output of agent's input, internal state, and output action
		cout << "Input Perception: " << belt_a_current << " " << belt_a_next 
				<< " " << belt_b_current << " " << belt_b_next << " " << current_power << endl;
		cout << "Agent State: " << endl;
		cout << "\t--Percepts: " << belt_a_current << " " << belt_a_next 
				<< " " << belt_b_current << " " << belt_b_next << " " << current_power << endl;
		cout << "\t--Slots:"
		cout << "\t\t1) " << slot_1_state << endl;
		cout << "\t\t2) " << slot_2_state << endl;
		cout << "\t--Picked Item: " << picked_item_state << endl;
		cout << "Output Action: " << r_agent_action << endl << endl;
		
		//Test Harness action taking proccess
		if(r_agent_action.compare("Advance A"){
			belt_a.step_belt();
		}else if(r_agent_action.compare("Advance B")){
			belt_b.step_belt();
		}else if(r_agent_action.compare("Pick Up A")){
			belt_a.pick_item();
		}else if(r_agent_action.compare("Pick Up B")){
			belt_b.pick_item();
		}else if(r_agent_action.compare("Fill 1")){
			slot_1 = picked_item;
			picked_item = 0;
		}else if(r_agent_action.compare("Fill 2")){
			slot_2 = picked_item;
			picked_item = 0;
		}else if(r_agent_action.compare("Drop 1")){
			slot_1 = 0;
		}else if(r_agent_action.compare("Drop 2")){
			slot_2 = 0;
		}
		
		if(current_power != 0) {current_power--;}
	}
}

string reflex_agent(int belta_current, int belta_next,
                     int beltb_current, int beltb_next, int current_power){

    string action;
	
	//At end of both belts or Have no power
	if((belta_current == -1 && beltb_current == -1) || current_power == 0){
		action = "STOP";
	}else{
		if(picked_item_state == 0){
			//find worst visible product on blets
			int percepts[4] = {belta_current, belta_next, beltb_current, beltb_next};
			int worst = belta_current;
			int worst_index = 0;
			for_each(int i = 0; i < 4; i ++){
				if (worst < percepts[i]){
					worst = percepts[i];
					worst_index = i;
				}
			}

			if(worst > slot_1_state || worst > slot 2){
				if(worst_index == 0){
					//worst is at belta_current
					action = "Pick Up A";
					picked_item_state = worst;
				} else if(worst_index == 2){
					//worst is at beltb_current
					action = "Pick Up B";
					picked_item_state = worst;
				} else if(worst_index == 1){
					//worst is at belta_next
					action = "Advance A";
				}else{
					//worst is at beltb_next
					action = "Advance B";
				}
			}
		}else{

			/*
				Choose smallest slotted item
				-Fill first open slot
				-If no open slots, drop smallest slot
			*/
			if(slot_1_state == 0){
				action = "Fill 1";
				picked_item_state = 0;
			}else if(slot_2_state == 0){
				action = "Fill 2";
				picked_item_state = 0;
			}else{
				if(slot_1_state < slot_2_state){
					action = "Drop 1";
					slot_1_state = 0;
				}else{
					action = "Drop 2";
					slot_2_state = 0;
				}
			}

		}
	}

	return action;
}
