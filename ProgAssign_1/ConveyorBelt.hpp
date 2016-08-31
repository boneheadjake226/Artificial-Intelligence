#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Conveyor_Belt{
	private:
		vector<int> queue;
	public:
		Conveyor_Belt(char *in_file);
		Conveyor_Belt();
		~Conveyor_Belt();
		void initialize(istream &in_file)
		void step_belt();
		void pick_item();
		int get_item_quality(int index);
};