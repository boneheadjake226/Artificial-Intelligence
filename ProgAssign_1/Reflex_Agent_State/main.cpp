#include "Conveyor_Belt.h"
#include <string>
#include <iostream>

using namespace std;

string reflex_agent(int belta_current, int belta_next,
                     int beltb_current, int beltb_next, current_power);

int slot_1 = 0, slot_2 = 0, picked_item = 0;

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

string reflex_agent(int belta_current, int belta_next,
                     int beltb_current, int beltb_next, int current_power){

    string action;

    if(picked_item == 0){
        //find worst visible product
        int percepts[4] = {belta_current, belta_next, beltb_current, beltb_next};
        int worst = belta_current;
        int worst_index = 0;
        for_each(int i = 0; i < 4; i ++){
            if (worst < percepts[i]){
                worst = percepts[i];
                worst_index = i;
            }
        }

        if(worst > slot_1 || worst > slot 2){
            if(worst_index == 0){
                //worst is at belta_current
                action = "Pick UP A";
                picked_item = worst;
            } else if(worst_index == 2){
                //worst is at beltb_current
                action = "Pick UP B";
                picked_item = worst;
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
        if(slot_1 == 0){
            action = "Fill 1";
            picked_item = 0;
        }else if(slot_2 == 0){
            action = "Fill 2";
            picked_item = 0;
        }else{
            if(slot_1 < slot_2){
                action = "Drop 1";
                slot_1 = 0;
            }else{
                action = "Drop 2";
                slot_2 = 0;
            }
        }

    }

}
