#include <iostream>

#include "cartpole_env.cpp"

constexpr int N = 100;
constexpr double rho = 0.1;

// Linear Model
class LinearModel{
  Vector param;
  public:
    LinearModel(Vector initial_param);
    ~LinearModel();
    int action(Vector obs);
};

LinearModel::LinearModel(Vector initial_param){
  param = initial_param;
}

LinearModel::~LinearModel(){
}

int LinearModel::action(Vector obs){
  double dot_obs_param = dot(obs,param);
  if(dot_obs_param > 0) return 1;
  else return -1;
}

// 標準正規分布もどき
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

// 報酬値の高かったパラメータ上位100ρ%の平均として次のパラメータを計算。
Vector get_next_param(Vector theta_with_noise, Vector reward_list){
  Vector r(4);
  int arg;
  int num_top = N * rho;
  r[0] = 0;
  r[1] = 0;
  r[2] = 0;
  r[3] = 0;
  for(int i=0; i<num_top; i++){
    arg = reward_list.argmax();
    reward_list[arg] = 0;
    for(int j=0; j<4; j++){
      r[j] += theta_with_noise[arg*4+j];
    }
  }
  return r * (1./num_top);
}

// パラメータを100個生成
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

// 報酬値を元にスコアを計算
int get_score(Vector &reward_list){
  int score = 0;
  for(int index=0;index<100;index++){
    if(reward_list[index] == 500) score++;
  }
  return score;
}

// 元の関数
int main() {
  Vector param(4);
  Vector theta_with_noise(4*N);
  bool finish_flag = false;
  int counter = 0;
  Vector obs(4);
  Vector param_temp(4);
  Vector reward_list(N);

  // 初期パラメータ
  for(int i; i<4; i++){
    param[i] = random_randn();
  }

  while(1){ // 収束するまで
    counter++;

    // 元パラメータを元に，Θ_iを生成
    theta_with_noise = get_next_param_100(param);

    // Θ_iごとに以下を回す。
    for (int episode = 1; episode <= N; ++episode) {
      double reward_sum = 0;
      CartPoleEnv env;

      // Agent
      for(int k=0; k<4; k++){
        param_temp[k] = theta_with_noise[(episode-1)*4+k];
      }
      LinearModel lm(param_temp);

      env.step(lm.action(env.obs)); // 最初の一歩

      for (int step = 0; step < 500 ; ++step) {
        reward_sum += env.reward; // 報酬を追加
        env.step(lm.action(env.obs)); // 次の一歩
        if (env.done_flag) break;
      }
      reward_list[episode-1] = reward_sum;
    }

    // スコア更新
    int score = get_score(reward_list);

    // パラメータの更新
    param = get_next_param(theta_with_noise,reward_list);

    // ログ出力
    std::cerr << "====================================================" << std::endl;
    std::cerr << "Step : " << counter << std::endl;
    std::cerr << "parameters : ";
    for(int i=0; i<4; i++){
      std::cerr << param[i] << " ";
    }
    std::cerr << std::endl;
          std::cerr << "score : " << score << std::endl;
    // 終了判定
    if(score >= 95){
      std::cerr << "====================================================" << std::endl;
      std::cerr << "Agent has just finished learning." << std::endl;
      std::cerr << "final parameters : "
      for(int i=0; i<4; i++){
        std::cerr << param[i] << " ";
      }
      std::cerr << std::endl;
      std::cerr << "final score : " << score << std::endl;
      std::cout << "q" << std::endl; // 終了メッセージを出力
      break;
    }
  }
}
