#include "Conveyor_Belt.h"
#include <stdlib.h>

using namespace std;

Conveyor_Belt::Conveyor_Belt(string in_file){
	fstream input_file;
	input_file.open(in_file.c_str(), fstream::in);

	if(!input_file){
		cerr << "Unable to open file";
        exit(1);
	}

	this->initialize(input_file);
	input_file.close();
}

Conveyor_Belt::~Conveyor_Belt() { };

void Conveyor_Belt::initialize(fstream &in_file){
	int next_item;
	while(in_file >> next_item){
		belt.push_back(next_item);
	}
}

void Conveyor_Belt::step_belt(){
	belt.pop_front();
	belt.push_back(0);
}

void Conveyor_Belt::pick_item(){
    item_held = belt.front();
	belt.pop_front();
	belt.push_front(0);
}

void Conveyor_Belt::drop_item(int slot){
    if(slot == 1){
        slot_1 = 0;
    } else {
        slot_2 = 0;
    }
}
void Conveyor_Belt::fill_slot(int slot){
    if(slot == 1){
        slot_1 = item_held;
    } else {
        slot_2 = item_held;
    }
    item_held = 0;
}

int Conveyor_Belt::get_item_quality(int index){
	return belt.at(index);
}
