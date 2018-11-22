# 倒立振子の強化学習

## コマンド
以下の順にコマンドを実行
```bash
g++ -std=c++11 ./src/agent.cpp -o agent.out
```

```bash
g++ -std=c++11 ./cartpole.cc -o cartpole.out
```

```bash
./cartpole.cc ./agent.out
```

## ファイルについて
### cartpole.cc
- 標準入力でaction（ここでは1or-1）を受け取り、それに対する観測値を返す。
- 環境をリセット
- 倒立振子の角度が傾きすぎたらアウト

### src/agent.cpp
強化学習するやつ。Linear Modelを使用。
