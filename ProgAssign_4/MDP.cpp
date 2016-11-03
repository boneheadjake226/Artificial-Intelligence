/*
* 
*/

#include "MDP.h"


MDP(string state_file_name, string trans_file_name){
  fstream state_file;
  fstream trans_file;
  
  
  //Parse state file and initialize states to vector positions
  state_file.open(state_file_name.c_str(), fstream::in);
  if(!state_file){
    cout << "\nCould not open: " << state_file_name << endl;
    cout << "\nExit Status: -1" << endl;
    
    exit(-1);
  }
  
  string next_state;
  while(state_file >> next_state){
    State new_state;
    stringstream ss(next_state);
    
    string curr_token;
    
    //debug message
    std::cout << curr_token << endl;
    
    vector<string> tokens;
    while(getline(ss, curr_token, ',')){
      tokens.push_back(curr_token);
    }
    new_state.reward = tokens[3];
    
    states[tokens[0]] = new_state;
  }
  
  state_file.close();
  
  //Parse transition file and initialize fields of each state
  trans_file.open(trans_file_name.c_str(), fstream::in);
  if(!trans_file){
    cout << "\nCould not open: " << trans_file_name << endl;
    cout << "\nExit Status: -1" << endl;
    
    exit(-1);
  }
  
  //TODO: Write parser for transition model
  //      Similar to states but storing actions

}











