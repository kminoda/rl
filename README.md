# Reinforcement Learning of The inverted pendulum

## How to Execute
execute the following command
```bash
$ g++ -std=c++11 ./src/agent.cpp -o agent.out
```

```bash
$ g++ -std=c++11 ./src/cartpole.cpp -o cartpole.out
```

```bash
$ ./cartpole.out ./agent.out
```

## About This File
### src/cartpole.cpp
- Receive "action" (1 or -1) by stdin, return the observed value.
- Reset the environment if the pendulum is too inclined.

### src/agent.cpp
Uses linear model


## Results
Learned parameters are as follow.
- 0.401331 1.9443 3.14837 2.74489 
- 0.318463 2.18408 3.05604 2.71976
