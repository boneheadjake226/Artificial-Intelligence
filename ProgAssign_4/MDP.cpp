#include "MDP.h"

using namespace std;

int toInt(string);
float toFloat(string);

MDP::MDP(std::string state_file_name, std::string trans_file_name){
  std::fstream state_file;
  std::fstream trans_file;
  
  gamma = GAMMA;
  error_value = ERROR;
  
  //Parse state file and initialize states to vector positions
  state_file.open(state_file_name.c_str(), std::fstream::in);
  if(!state_file){
    std::cout << "\nCould not open: " << state_file_name << endl;
    std::cout << "\nExit Status: -1" << endl;
    
    exit(-1);
  }
  
  //DEBUG
  cout << "Opened " << state_file_name << endl;
  
  std::string next_state;
  while(getline(state_file, next_state)){
    State new_state;
    std::stringstream ss(next_state);
    
    std::string curr_token;
    
    //DEBUG
    cout << "Gathering Tokens from: " << next_state << endl;
    
    vector<string> tokens;
    while(getline(ss, curr_token, ',')){
      tokens.push_back(curr_token);
    }
    
    new_state.reward = toFloat(tokens[3]);
    new_state.utility = 0.0;
    int state_id = toInt(tokens[0]);
    
    //Set actions for terminal states
    if(new_state.reward == 1 || new_state.reward == -1){
      vector<Next_State> next_states;
      next_states.push_back(Next_State(state_id, 0.0));
      new_state.actions['H'] = next_states;
    }
    
    states[state_id] = new_state;
  }
  
  state_file.close();
  
  //DEBUG
  cout << "Closed " << state_file_name << endl;
  
  //Parse transition file and initialize fields of each state
  trans_file.open(trans_file_name.c_str(), fstream::in);
  if(!trans_file){
    cout << "\nCould not open: " << trans_file_name << endl;
    cout << "\nExit Status: -1" << endl;
    
    exit(-1);
  }
  
  //DEBUG
  cout << "Opened " << trans_file_name << endl;
  
  std::string next_action;
  while(getline(trans_file, next_action)){
    std::stringstream ss(next_action);
    vector<string> tokens;
    std::string curr_token;
    
    //DEBUG
    cout << "Action: " << next_action << endl;
    
    //DEBUG
    cout << "Trans: Gathering Tokens" << endl;
    
    while(getline(ss, curr_token, ',')){
      tokens.push_back(curr_token);
    }
    
    //DEBUG
    cout << "Trans: Tokens Gathered" << endl;
    
    int state_id = toInt(tokens[0]);
    
    State *state_ptr = &(states[state_id]);
    char action_code = tokens[1].at(0);
    std::vector<Next_State> nxt_state_vec;
    for(int i = 2; i < tokens.size(); i += 2){
      std::string::size_type sz;
      int dest_state_id = toInt(tokens[i]);
      float dest_state_prop = toFloat(tokens[i+1]);
      Next_State nxt_state = pair<int, float>(dest_state_id, dest_state_prop);
      
      nxt_state_vec.push_back(nxt_state);
      
    }
    
    state_ptr->actions[action_code] = nxt_state_vec;
  }
  
  trans_file.close();
  
  //DEBUG
  cout << "Closed " << trans_file_name << endl;
  
}

MDP::~MDP(){
}

/*
  * Outputs a textual representation of an MDP object to the console
*/
void MDP::toString(){
  
  for(int i = 0; i < states.size(); i++){
    State curr_state = states[i+1];
    
    cout << "State[" << i+1 << "]:" << endl;
    cout << "\tReward: " << curr_state.reward << endl;
    cout << "\tUtility: " << curr_state.utility << endl;
    cout << "\tTransitions:" << endl;
    
    if(is_terminal_state(curr_state)){
      std::vector<Next_State> next_states = curr_state.actions['H'];
      for(int j = 0; j < next_states.size(); j++){
        cout << "\t\tAction[H]: ";
        cout << next_states[j].first << " => " << next_states[j].second << endl;
      }
    } else{
      cout << "\t\tAction[S]: ";
      std::vector<Next_State> next_states = curr_state.actions['S'];
      for(int j = 0; j < next_states.size(); j++){
        cout << next_states[j].first << " => " << next_states[j].second << ", ";
      }
      cout << endl << "\t\tAction[G]: ";
      next_states = curr_state.actions['G'];
      for(int j = 0; j < next_states.size(); j++){
        cout << next_states[j].first << " => " << next_states[j].second << ", ";
      }
      cout << endl << "\t\tAction[B]: ";
      next_states = curr_state.actions['B'];
      for(int j = 0; j < next_states.size(); j++){
        cout << next_states[j].first << " => " << next_states[j].second << ", ";
      }
      cout << endl;
    }
  }
}

bool MDP::is_terminal_state(State state){
  return (state.reward == 1 || state.reward == -1);
}

/*=============================================*/
/*===============   Utility Functions   ================*/

/*
  * Converts a string to its integer form
  * String s must be a valid integer format. Otherwise return value is
      undefined
  * returns integer form of string s.
*/
int toInt(string s){
  cout << "toInt in progress" << endl;
  
  std::istringstream istream(s);
  int result;
  istream >> result;
  
  return result;
}

/*
  * Converts a string to a floating point decimal form
  * String s must be a valid decimal format. Otherwise return value is
      undefined
  * returns floating point decimal form of string s.
*/
float toFloat(string s){
  cout << "toInt in progress" << endl;
  
  std::istringstream istream(s);
  float result;
  istream >> result;
  
  return result;
}












