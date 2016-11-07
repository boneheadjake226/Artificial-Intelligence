/*
  Value Iterator Implementation
*/

#include "MDP.h"
#include <iostream>

using namespace std;

map<int, State> value_iteration(MDP, int);
pair<char, float> max_action_util(State,   map<int, float>, float);
string state_policy(State);

int main(int argc, char *argv[]) {
  float greatest_util_diff;
  int debug = 0;
  if(argc == 3){
    istringstream is(argv[3]);
    is >> debug;
  }
  
  MDP mdp(argv[1], argv[2]);
  
  if(debug){
    cout << "MDP initialized with command line args" << endl;
  }
  
  map<int, State> result = value_iteration(mdp, debug);
  
  if(debug){
    cout << "Value iteration complete" << endl;
  }
  
  
}

map<int, State> value_iteration(MDP mdp, int debug){
    // U
  map<int, float> prev_utils;
  
  // Iterator type for states map
  typedef map<int, State>::iterator it_type;
  do{
    greatest_util_diff = 0.0;
    // U = U'
    for(it_type state = mdp.states.begin(); state != mdp.states.end(); state++){
      prev_utils[state.key()] = state.second.utility;
    }
    
    for(it_type state = mdp.states.begin(); state != mdp.states.end(); state++){
      state.utility = state.reward + (mdp.gamma * max_action_util(state, pre_utils).second)
      
      if( (state.utility - prev_utils[state.key()]) > greatest_util_diff){
        greatest_util_diff = (state.utility - prev_utils[state.key()]);
      }
    }
    
  }while( greatest_util_diff <= (mdp.error_value(1-mdp.gamma) / mdp.gamma) );
  
}


pair<char, float> max_action_util(State state, map<int, float> prev_utils){
  float max_action_util= 0.0;
  char action_code;
  
  map<int, float>::iterator action;
  for(action = state.actions.begin(); action != state.actions.end(); action++){
    float action_util = 0;
    
    // Compute expected utility for current action
    for(int i = 0; i < action->second().size(); i++){
      float prob_nxt_state = action->second[i].second;
      float nxt_state_id = action->second[i].first;
      action_util += prev_utils[nxt_state_id] * prob_nxt_state;
    }
    
    if(action_util > max_action_util){
      max_action_util = action_util;
      action_code = action->first;
    }
    
  }
  
  pair<char, float> max_action(action_code, max_action_util);
  return max_action;
}

string state_policy(State state, map<int, State> states){
  //TODO: use max action instead
}












