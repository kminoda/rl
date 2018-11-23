#include <iostream>
#include <stdio.h>
#include <random>
#include <string>
using namespace std;

#include "matrix.cpp"
//#include "../cartpole.cc"

class EasyEnv{
  Vector prev_obs;
  int step_counter;
  bool finish_flag;

  public:
    EasyEnv();
    ~EasyEnv();
    Vector reset();
    int obs_dim(){return 1;};
    tuple<Vector, bool, double> step(const int &action);
};

EasyEnv::EasyEnv(){
  prev_obs = reset();
  finish_flag = false;
  step_counter = 0;
}

EasyEnv::~EasyEnv(){
}

Vector EasyEnv::reset(){
  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> score(-1.0,1.0);
  Vector r(obs_dim());
  for(int i=0; i<obs_dim(); i++){
    r[i] = score(mt);
  }
  return r;
}

tuple<Vector, bool, double>  EasyEnv::step(const int &action){
  Vector now_obs(obs_dim());
  double reward;

  step_counter++;
  if(step_counter == 10) finish_flag = true;

  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> score(-1.0,1.0);
  for(int i=0; i<obs_dim(); i++){
    now_obs[i] = score(mt);
  }

  for(int i=0; i<prev_obs.size(); i++){
    reward += prev_obs[i] * action;
  }

  prev_obs = now_obs;

  cout << "========== step " << step_counter << " ==========" << endl;
  cout << "action : " << action << endl;
  cout << "finished or not : " << finish_flag << endl;
  cout << "observation : " << now_obs[0] << endl;
  return forward_as_tuple(now_obs,finish_flag,reward);
}


int main(){
  EasyEnv env;
  env.reset();
  int x=1;
  int y=-1;
  // env.step(x);
  // env.step(x);
  // env.step(x);
  // env.step(x);
  // env.step(x);
  // env.step(y);
  // env.step(y);
  // env.step(y);
  // env.step(y);
  // env.step(x);
  // env.step(x);
  // env.step(x);

}
