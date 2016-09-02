/*
	Hello world program
	Author: Jake Hill
	Class:	CSE 3521
	Instructor:	Jeremy Morris
	Meeting Time: Tue, Thur 8-9:20am
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
#include <string>

using namespace std;


int main(){
	priority_queue<int, std::vector<int>, std::greater<int> > min_heap;
	fstream test_file;
	string test_file_name;

	cout << "Test text file must be in the same directory as program and executable files" << endl;
	cout << "Enter test file name: ";
	cin >> test_file_name;
	test_file.open(test_file_name.c_str(), fstream::in);

	if(test_file.is_open()){

		//File opened test
		cout << "File opened successfully" << endl;

		string user_name;

		getline(test_file, user_name);
		cout << "Hello " << user_name << "!" <<  endl;

		string next_line;
		int next_num;
        test_file >> next_num;
		while(!test_file.eof()){
			min_heap.push(next_num);
			test_file >> next_num;
		}

		test_file.close();

		while(!min_heap.empty()){
			cout << min_heap.top() << endl;
			min_heap.pop();
		}
	} else{
		cout << endl << "Error: File was not opened properly";
	}

	return 0;
}
