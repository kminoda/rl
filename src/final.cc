#include <iostream>
#include <vector>

#include "linear_model.cpp"


int N = 100;

void get_observation(Vector &obs, bool&done) {
  std::string stat;
  std::cin >> stat;
  if (stat == "obs") {
    //obs.resize(4);
    for (int i = 0; i < 4; ++i) std::cin >> obs[i];
    done = false;
  } else if (stat == "done") {
    done = true;
  }
}

double random_randn(){
  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> score(-1.0,1.0);
  double aa = 0;
  for(int i=0; i<3; i++){
    aa += score(mt);
  }
  return aa/3.0;
}

Vector get_next_param(Vector theta_with_noise, Vector reward_list){
  Vector r(4);
  int arg;
  int num_top = 10;
  r[0] = 0;
  r[1] = 0;
  r[2] = 0;
  r[3] = 0;
  for(int i=0; i<num_top; i++){
    arg = reward_list.argmax();
    cerr << reward_list[arg] << " ";
    reward_list[arg] = 0;
    for(int j=0; j<4; j++){
      r[j] += theta_with_noise[arg*4+j];
    }
  }
  cerr << endl;
  return r * (1./num_top);
}

int get_action(Vector obs, Vector param){
  double dot_obs_param = dot(obs,param);
  if(dot_obs_param > 0) return 1;
  else return -1;
}


Vector get_next_param_100(Vector param){
  Vector theta_with_noise(4*N);
  for(int i=0; i<N; i++){
    for(int j=0; j<4; j++){
      theta_with_noise[i*4+j] = 0;
      theta_with_noise[i*4+j] = param[j] + random_randn();
    }
  }
  return theta_with_noise;
}

int episode_100() {
  cerr << random_randn() << endl;
  Vector param(4);
  for(int i; i<4; i++){
    param[i] = random_randn();
  }

  Vector theta_with_noise(4*N);
  bool finish_flag = true;
  int counter = 0;
  Vector obs(4);
  Vector param_temp(4);

  while(finish_flag){ // 収束するまで
    counter++;
    std::cerr << "==================================" << std::endl;
    std::cerr << "Step : " << counter << std::endl;

    theta_with_noise = get_next_param_100(param);

    Vector reward_list(N);
    for (int episode = 1; episode <= N; ++episode) {
      std::cout << "r" << std::endl;
      bool done;

      for(int k=0; k<4; k++){
        param_temp[k] = theta_with_noise[(episode-1)*4+k];
      }

      int action = get_action(obs,param_temp);
      //std::cout << "s " << action << std::endl;

      //get_observation(obs, done); //ここがおかしいっぽい
      std::string stat;
      std::cin >> stat;
      if (stat == "obs") {
        for (int i = 0; i < 4; ++i) std::cin >> obs[i];
        done = false;
      } else if (stat == "done") {
        done = true;
      }

      //LinearModel model(param_temp); // LinearModelのインスタンス作成

      double reward_sum = 0;
      for (int step = 0; step < 500 ; ++step) {
        reward_sum += 1;

        int action = get_action(obs,param_temp);

        //int action = model.action(obs);
        std::cout << "s " << action << std::endl;
        //get_observation(obs, done);
        std::string stat;
        std::cin >> stat;
        if (stat == "obs") {
          for (int i = 0; i < 4; ++i) std::cin >> obs[i];
          done = false;
        } else if (stat == "done") {
          done = true;
        }

        if (done) break;
      }
      reward_list[episode-1] = reward_sum;
    }

    // パラメータの更新
    param = get_next_param(theta_with_noise,reward_list);

    // ログ出力
    std::cerr << "Reward average : " << reward_list.mean() << std::endl;
    std::cerr << "parameters : ";
    for(int i=0; i<4; i++){
      std::cerr << param[i] << " ";
    }
    std::cerr << "\n" ;

    // 収束したら終了フラグを立てる
    if(reward_list.mean() > 400) finish_flag = false;
  }
  std::cout << "q" << std::endl;
  return 0;
}


int main(){
  episode_100();
}
