#include "ConveyorBelt.hpp"
#include "Reflex_Agent.cpp"
#include <string>
#include <iostream>

using namespace std;

void print_system_output(int item1, int item2, )

int main(){
	string input_file;
	Reflex_Agent quality_checker;
	int item1, item2;
	
	
	cout << "Input file must be in same directory as application file" << endl;
	cout << "Input conveyor belt test file directory: ";
	cin >> input_file;
	
	ConveyorBelt main_belt(input_file.c_str());
	
	while(quality_checker.action != "STOP"){
		item1 = main_belt.get_item_quality(0);
		item2 = main_belt.get_item_quality(1);
		
		quality_checker.feed_percepts(item1, item2);
		
		if(quality_checker.action.compare("ADVANCE") == 0){
			main_belt.step_belt();
		} else if(quality_checker.action.compare("PICK UP") == 0){
			main_belt.pick_item();
		}
	}
}