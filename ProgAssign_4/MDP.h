/*
* Marcovian Decision Process Class
* MDP.h
*/
#include <vector>
#include <map>
#include <string>
#include <stringstream>
#include <fstream>
#include <stdlib.h>
#include <iostream>

// int = next_state_id, 
// float = probability of getting to that state
typedef pair<int, float> next_state;

typedef struct State{
  int reward;
  // char = action_id (S, G, B)
  // actions = all possible result states for taking action_id
  //            plus their probabilities
  std::map< char, std::vector<next_state> > actions
}

public class MDP{
  
  private:

  public:
    MDP(string state_file_name, string trans_file_name);
    ~MDP();
    std::map<int, State> states;
    float gamma;
    float error_value;
}