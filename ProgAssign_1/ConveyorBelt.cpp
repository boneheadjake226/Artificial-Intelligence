#include "ConveyorBelt.hpp"

ConveyorBelt::ConveyorBelt(char *in_file){
	istream input_file;
	input_file.open(in_file);
	
	if(!input_file){
		cerr("Unable to open file");
		exit(1);
	}
	
	this.initialize(input_file);
	in_file.close();
}

ConveyorBelt::ConveyorBelt(){
	this.initialize(cin);
}

void ConveyorBelt::initialize(istream &in_file){
	int next_item;
	while(in_file >> next_item){
		this.queue.push_back(next_item);
	}
}

void ConveyorBelt::step_belt(){
	queue.pop_front();
	queue.push_back(0);
}

void ConveyorBelt::pick_item(){
	queue.pop();
	queue.push_front(0);
}

int get_item_quality(int index){
	return queue.at(index);
}