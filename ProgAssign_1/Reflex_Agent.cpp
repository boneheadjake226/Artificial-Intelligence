#include "Reflex_Agent.hpp"

Reflex_Agent::Reflex_Agent(){
	action = "Init";
}
void feed_percepts(int item1, int item2){
	if(item1 == 0 ){
		if(item2 == 0){
			action = "STOP";
		} else{
			action = "ADVANCE";
		}
	}else if(item1 > item2){
		action = "PICK UP";
	}else {
		action = "ADVANCE";
	}
}
string get_action() {
	return action;
}