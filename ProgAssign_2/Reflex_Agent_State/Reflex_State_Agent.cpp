#include "Reflex_State_Agent.h"

Reflex_State_Agent::Reflex_State_Agent(){
	slot_1_state = 0;
	slot_2_state = 0;
	picked_item_state = 0;
	agent_action = "Init";
}

Reflex_State_Agent::~Reflex_State_Agent(){ }

string Reflex_State_Agent::compute_action(int belta_current, int belta_next,
                     int beltb_current, int beltb_next, int current_power){
		//At end of both belts or Have no power
	if((belta_current == -1 && beltb_current == -1) || current_power == 0){
		agent_action = "STOP";
	}else{
		if(picked_item_state == 0){
			//find worst visible product on blets
			int percepts[4] = {belta_current, belta_next, beltb_current, beltb_next};
			int worst = belta_current, worst_index = 0, i;
			
			//cout << "\n\n\n";
			
			for(i = 0; i < 4; i ++){
				
				//cout << "\nWorst: " << worst << "Percepts[" << i << "]: " << percepts[i];
				
				
				if (worst < percepts[i]){
					worst = percepts[i];
					worst_index = i;
				}
			}
			
			//cout << "\n\n\n";

			if(worst > slot_1_state || worst > slot_2_state){
				if(worst_index == 0){
					//worst is at belta_current
					agent_action = "Pick Up A";
					picked_item_state = worst;
				} else if(worst_index == 2){
					//worst is at beltb_current
					agent_action = "Pick Up B";
					picked_item_state = worst;
				} else if(worst_index == 1){
					//worst is at belta_next
					agent_action = "Advance A";
				}else{
					//worst is at beltb_next
					agent_action = "Advance B";
				}
			}else{
				/*
					The worst visible product for either belt is less than what
					is in slot 1 or slot 2
				*/
				if(percepts[0] == 0){
					//belta_current is empty
					agent_action = "Advance A";
				}else{
					//beltb_current is empty
					agent_action = "Advance B";
				}
			}
		}else{

			/*
				Choose smallest slotted item
				-Fill first open slot
				-If no open slots, drop smallest slot
			*/
			if(slot_1_state == 0){
				agent_action = "Fill 1";
				
				slot_1_state = picked_item_state;
				picked_item_state = 0;
			}else if(slot_2_state == 0){
				agent_action = "Fill 2";
				
				slot_2_state = picked_item_state;
				picked_item_state = 0;
			}else{
				if(slot_1_state < slot_2_state){
					agent_action = "Drop 1";
					slot_1_state = 0;
				}else{
					agent_action = "Drop 2";
					slot_2_state = 0;
				}
			}

		}
	}
	
	print_agent_state(belta_current, belta_next, beltb_current, beltb_next, current_power);

	return agent_action;
}

void Reflex_State_Agent::print_agent_state(int belta_current, int belta_next,
                     int beltb_current, int beltb_next, int current_power){
	cout << "Agent State: " << endl;
	cout << "\t--Percepts: " << belta_current << " " << belta_next 
			<< " " << beltb_current << " " << beltb_next << " " << current_power << endl;
	cout << "\t--Slots:" << endl
				<< "\t\t1) " << slot_1_state << endl
				<< "\t\t2) " << slot_2_state << endl
	<< "\t--Picked Item: " << picked_item_state << endl;
}










