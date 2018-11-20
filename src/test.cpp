#include<iostream>
#include<stdio.h>
#include <random>
using namespace std;

#include "matrix.cpp"

class EasyEnv{
  Vector prev_obs;
  int finish_flag;

  public:
    EasyEnv();
    ~EasyEnv();
    Vector reset();
    int obs_dim(){return 1;};
    double step(const int action);
};

EasyEnv::EasyEnv(){
  prev_obs = reset();
  finish_flag = 0;
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

hogehoge EasyEnv::step(const int &action){
  finish_flag++;


}
