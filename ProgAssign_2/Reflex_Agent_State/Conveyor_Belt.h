#ifndef CONVEYORBELT_H_INCLUDED
#define CONVEYORBELT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <deque>
#include <string>

using namespace std;

class Conveyor_Belt{
	private:
		deque<int> belt;
		int power;
		int item_held;
		int fill_1;
		int fill_2;
	public:
		Conveyor_Belt(string in_file);
		~Conveyor_Belt();
		void initialize(fstream &in_file);
		void step_belt();
		void pick_item();
		void drop_item(int slot);
		void fill_slot(int slot);
		int get_item_quality(int index);
};


#endif // CONVEYORBELT_H_INCLUDED
