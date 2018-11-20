// https://mementoo.info/archives/648

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
using namespace std;

class Vector{
  //private:
  //xdVec(){} これ？？
  double *p_top;
  int length;

  public:
    Vector(int i=1);
    Vector(const Vector &cp);

    ~Vector();

    int size(){return(length);}

    void change_size(int i);
    void print();
    double &operator[](int i){return(p_top[i]);}
    Vector operator=(const Vector &a);
    Vector operator+(const Vector &a);
    Vector operator-(const Vector &a);
    double operator*(const Vector &a);
    friend Vector operator*(const Vector& a, double b);
    friend Vector operator*(double b, const Vector& a);

    int argmax();
};

Vector::Vector(int i){
  length = i;
  if(length<1){
    cerr << "err Vector::Vector" << endl;
  }
  p_top = new double[length+1];
  for(int k=0; k<length; k++){
    p_top[k] = 0;
  }
}

    // なんか来れなくてもうまくいく。。。何者なんだ
Vector::Vector(const Vector &cp){
  length = cp.length;
  p_top = new double[length+1];
  for(int k=0; k<length; k++){
    p_top[k] = cp.p_top[k];
  }
}

Vector::~Vector(void){
  delete[] p_top;
}

void Vector::change_size(int i){
  if(i<1){
    cerr << "err Vector::change_size" << endl;
    exit(1);
  }
  delete [] p_top;
  length = i;

  p_top = new double[length+1];
  for(int k=0; k<length; k++){
    p_top[k] = 0;
  }
}

void Vector::print(void) {
  printf("[");
  for(int i=0;i<length;i++){
    cout << p_top[i] ;
    if(i<length-1){printf(" ");}
  }
  printf("]\n");
}

Vector Vector::operator=(const Vector &a){
  if(length != a.length){
    change_size(a.length);
  }
  for(int i=0; i<length; i++){
    p_top[i] = a.p_top[i];
  }
  return(*this);
}

Vector Vector::operator+(const Vector &a) {
  if(length!=a.length){
    cerr << "err Vector::operator+" << endl;
  }
  Vector r(length);
  for(int i=0;i<length;i++){
    r.p_top[i] = p_top[i] + a.p_top[i];
  }
  return(r);
}

Vector Vector::operator-(const Vector &a) {
  if(length!=a.length){
    cerr << "err Vector::operator-" << endl;
  }
  Vector r(length);
  for(int i=0;i<length;i++){
    r.p_top[i] = p_top[i] - a.p_top[i];
  }
  return(r);
}

double Vector::operator*(const Vector &a){
  if(length != a.length){
    std::cerr << "err Vector::operator*" << std::endl;
    std::cerr << " not equal vector size" << std::endl;
    exit(0);
  }

  double r = 0;
  for(int i=0;i<length; i++){
    r += p_top[i] * a.p_top[i];
  }
  return(r);
}

Vector operator*(const Vector &a, double b) {
  Vector r(a.length);
  for(int i=0;i<a.length;i++){
    r.p_top[i] = b * a.p_top[i];
  }
  return(r);
}

Vector operator*(double b,const Vector &a) {
  Vector r(a.length);
  for(int i=0;i<a.length;i++){
    r[i] = b * a.p_top[i];
  }
  return(r);
}

int Vector::argmax(void){
  int argmax = 0;
  for(int i=0; i<length; i++){
    if(p_top[argmax]<p_top[i]){
      argmax = i;
    }
  }
  return argmax;
}

Vector ReLU(Vector v1){
  int length = v1.size();
  Vector r(length);
  for(int i=0; i<length; i++){
    if(v1[i]>0){r[i]=v1[i];}
    else{r[i]=0;}
  }
  return(r);
}

double exp(double x){
  return pow(2.71828182846,x);
}

Vector Softmax(Vector v1){
  int length = v1.size();
  Vector r(length);
  double sum=0;
  for(int i=0; i<length; i++){
    sum += exp(v1[i]);
  }
  for(int i=0; i<length; i++){
    r[i] = exp(v1[i])/sum;
  }
  return(r);
}
