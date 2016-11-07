/*
  Value Iterator Implementation
*/

#include "MDP.h"
#include <iostream>

using namespace std;

map<int, float> value_iteration(MDP);
pair<char, float> max_action_util(State, map<int, float>);
string state_policy(State);

int debug = 0;

int main(int argc, char *argv[]) {
  float greatest_util_diff;
  
  cout << "argc: " << argc << endl;
  if(argc == 4){
    istringstream is(argv[3]);
    is >> debug;
  }
  
  MDP mdp(argv[1], argv[2]);
  
  if(debug){
    cout << "MDP initialized with command line args" << endl;
  }
  
  map<int, float> result = value_iteration(mdp);
  
  if(debug){
    cout << "Value iteration complete" << endl;
  }
  
  if(debug){
    cout << "Outputting Policy" << endl << endl;
  }
  
  for(int i = 1; i <= result.size(); i++){
    
    cout << "State " << i << ": Utility = " << result[i];
    if(mdp.is_terminal_state(mdp.states[i])){
      cout << endl;
    }else{
      cout << " Policy = ";
      switch(max_action_util(mdp.states[i], result).first){
        case 'S' : cout << "Scarlet" << endl;
                   break;
        case 'G' : cout << "Gray" << endl;
                   break;
        case 'B' : cout << "Black" << endl;
                   break;
        default :  cout << "undeclared" << endl;
      }
    }
  }
}

map<int, float> value_iteration(MDP mdp){
  // U
  map<int, float> prev_utils;
  float greatest_util_diff;
  
  // Iterator type for states map
  typedef map<int, State>::iterator it_type;
  do{
    greatest_util_diff = 0.0;
    // U = U'
    for(it_type state = mdp.states.begin(); state != mdp.states.end(); state++){
      prev_utils[state->first] = state->second.utility;
    }
    
    for(it_type state = mdp.states.begin(); state != mdp.states.end(); state++){
      if(mdp.is_terminal_state(state->second)){ continue; }
      
      state->second.utility = state->second.reward + 
              (mdp.gamma * max_action_util(state->second, prev_utils).second);
      
      if( (state->second.utility - prev_utils[state->first]) > greatest_util_diff){
        greatest_util_diff = (state->second.utility - prev_utils[state->first]);
      }
    }
    
    if(debug){
      cout << endl;
      for(map<int, float>::iterator state = prev_utils.begin(); state != prev_utils.end(); state++){
        cout << "State[" << state->first << "] utility: " << state->second << endl;
      }
    }
    
  }while( !(greatest_util_diff <= (mdp.error_value * (1-mdp.gamma)) / mdp.gamma) );
  
  return prev_utils;
}

/*
  * Given a state, determines the action with the maximum expected utility
*/
pair<char, float> max_action_util(State state, map<int, float> prev_utils){
  float max_action_util = -1.0;
  char action_code;
  
  map<char, vector<Next_State> >::iterator action;
  for(action = state.actions.begin(); action != state.actions.end(); action++){
    float action_util = 0;
    
    // Compute expected utility for current action
    for(int i = 0; i < action->second.size(); i++){
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












