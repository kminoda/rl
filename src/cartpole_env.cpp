#include <iostream>
#include <stdio.h>
#include <random>
#include <string>

#include <cmath>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "matrix.cpp"

class CartPoleEnv{

  int step_counter;

  public:
    Vector obs;
    bool done_flag;
    int reward;
    CartPoleEnv();
    ~CartPoleEnv();
    void reset();
    int obs_dim(){return 4;};
    void step(const int &action);
    void get_obs(Vector &obs, bool&done);
};

CartPoleEnv::CartPoleEnv(){
  reset();
  done_flag = false;
  step_counter = 0;
}

CartPoleEnv::~CartPoleEnv(){
}

void CartPoleEnv::reset(){
  Vector r(4);
  std::cout << "r" << std::endl;
  get_obs(r, done_flag);
  obs = r;
}

void CartPoleEnv::get_obs(Vector &obs, bool&done){
  std::string stat;
  std::cin >> stat;
  if (stat == "obs") {
    for (int i = 0; i < 4; ++i) std::cin >> obs[i];
    done_flag = false;
  } else if (stat == "done") {
    done_flag = true;
  }
}

void CartPoleEnv::step(const int &action){
  step_counter++;
  std::cout << "s " << action << std::endl;
  get_obs(obs, done_flag);
  reward = 1;
}
