/*
  Q-State Value Iteration Implementation
*/

#include "MDP.h"
#include <iostream>

using namespace std;

typedef pair<int, char> SA_Pair; // State Action pair for Q-States

map< pair<int, char>, float> qvalue_iteration(MDP);
// pair<char, float> max_action_util(State, map<int, float>);
float qstate_expec_val(MDP, SA_Pair, map<SA_Pair, float>);
string state_policy(State);

int debug = 0;

// Iterator type for map containers
typedef map<int, State>::iterator state_it;
typedef map<char, vector<Next_State> >::iterator action_it;
typedef map< SA_Pair, float>::iterator qvalue_it;

int main(int argc, char *argv[]) {
  
  cout << "argc: " << argc << endl;
  if(argc == 4){
    istringstream is(argv[3]);
    is >> debug;
  }
  
  MDP mdp(argv[1], argv[2]);
  
  if(debug){
    mdp.toString();
    cout << "MDP initialized with command line args" << endl;
  }
  
  map<SA_Pair, float> result = qvalue_iteration(mdp);
  
  if(debug){
    cout << "Value iteration complete" << endl;
  }
  
  if(debug){
    cout << "Outputting Policy" << endl << endl;
  }
  
  cout << "----------------------" << endl;
  cout << "------ Results -------" << endl;
  for(qvalue_it qstate = result.begin(); qstate != result.end(); qstate++){
    cout << "Q-State (" << qstate->first.first << ", " << qstate->first.second 
              << ") Utility: " << qstate->second << endl;
  }
}
/*
  *returns a map of Q-states to Q-values
  *Q-state = pair<int, char> == SA_Pair
  *Q-value = float  => Q-state utility
*/
map< SA_Pair, float> qvalue_iteration(MDP mdp){
  map< SA_Pair, float> prev_qvals; // Q
  map< SA_Pair, float> qvals; // Q'
  float greatest_qval_diff;
  
  
  // Q = 0  Q' = 0
  for(state_it state = mdp.states.begin(); state != mdp.states.end(); state++){
    if(mdp.is_terminal_state(state->second)) continue;
    for(action_it action = state->second.actions.begin(); action != state->second.actions.end(); action++){
      
      SA_Pair qstate( state->first, action->first );
      
      prev_qvals[qstate] = 0.0;
      qvals[qstate] = 0.0;
    }
  }
  
  do{
    greatest_qval_diff = 0.0;
    // U = U'
    for(qvalue_it qstate = qvals.begin(); qstate != qvals.end(); qstate++){
      prev_qvals[qstate->first] = qstate->second;
    }
    
    for(state_it state = mdp.states.begin(); state != mdp.states.end(); state++){
      if(mdp.is_terminal_state(state->second)) continue;
      for(action_it action = state->second.actions.begin(); action != state->second.actions.end(); action++){
        SA_Pair qstate( state->first, action->first );
      
        qvals[qstate] = state->second.reward + 
                (mdp.gamma * qstate_expec_val( mdp, qstate, prev_qvals ));
        
        if( (qvals[qstate] - prev_qvals[qstate]) > greatest_qval_diff){
          greatest_qval_diff = (qvals[qstate] - prev_qvals[qstate]);
        }
      }
    }
    
    
    if(debug){
      cout << endl;
      for(qvalue_it qstate = prev_qvals.begin(); qstate != prev_qvals.end(); qstate++){
        cout << "Q-State(" << qstate->first.first << ", " << qstate->first.second 
                << ") utility: " << qstate->second << endl;
      }
    }
    
  }while( !(greatest_qval_diff <= (mdp.error_value * (1-mdp.gamma)) / mdp.gamma) );
  
  return prev_qvals;
}

/*
  * Given a State-Action pair (i.e. Q-State), returns the given Utility (i.e. Q-Value)
*/
float qstate_expec_val(MDP mdp, SA_Pair qstate, map<SA_Pair, float> prev_qvals){
  float qvalue = 0.0;
  
  vector<Next_State> next_states = mdp.states[qstate.first].actions[qstate.second];
  
  for(int i = 0; i < next_states.size(); i++){
    int next_state_id = next_states[i].first;
    float prob_next_state = next_states[i].second; // P(s' | s, a)
    
    // max Q(s',a')
    State next_state = mdp.states[next_state_id]; // To access the next state's actions
    float max_next_action;
    if(next_state.reward != 1){
      max_next_action = -1.0;
      for(action_it action = next_state.actions.begin(); action != next_state.actions.end(); action++){
        SA_Pair next_qstate(next_state_id, action->first);
        if(prev_qvals[next_qstate] > max_next_action){
          max_next_action = prev_qvals[next_qstate];
        }
      }
    } else{
      max_next_action = next_state.reward;
    }
    
    qvalue += prob_next_state * max_next_action;
  }
  
  return qvalue;
}













