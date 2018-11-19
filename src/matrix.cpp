#include <iostream>
#include <cmath>

#include "vector.cpp"

class Matrix{

  int row;
  int column;

  double** p_top;

  public:
    Matrix(int i=1,int j=1);
    Matrix(const Matrix &cp);

    ~Matrix();

    int row_size(){return(row);}
    int column_size(){return(column);}

    void change_size(int i,int j);
    void print();
    double* &operator[](int i){return(p_top[i]);}
    Matrix operator=(const Matrix &a);
    Matrix operator+(const Matrix &a);
    Matrix operator-(const Matrix &a);
    Matrix operator*(const Matrix &a);
    friend Matrix operator*(const Matrix &a, double b);
    friend Matrix operator*(double b, const Matrix &a);

    friend Vector operator*(const Matrix &a, Vector b);

    void unit_matrix();
    Matrix transpose();
};


Matrix::Matrix(int i,int j)
{
  if(i<1 || j<1){
    std::cerr << "err Matrix::Matrix" << std::endl;
    exit(1);
  }

  row = i ;
  column = j;

  p_top = new double*[row+1];
  *p_top = new double[row*column+1];
  for(int k=0;k<row;k++){
    *(p_top+k) = *p_top + (k*column);
  }
  for(int k1=0;k1<row;k1++){
    for(int k2=0;k2<column;k2++){
      p_top[k1][k2] = 0;
    }
  }
}


Matrix::Matrix(const Matrix &cp){
  row = cp.row;
  column = cp.column;

  p_top = new double*[row+1];
  *p_top = new double[row*column+1];
  for(int k=0; k<row; k++){
    *(p_top+k) = *p_top + (k*column);
  }

  for(int k1=0; k1<row; k1++){
    for(int k2=0; k2<column; k2++){
      p_top[k1][k2] = cp.p_top[k1][k2];
    }
  }
}


Matrix::~Matrix(){
  delete [] *p_top;
  delete [] p_top;
}

void Matrix::change_size(int i,int j){
  if(i<1 || j<1){
    std::cerr << "err Matrix::change_size" << std::endl;
    exit(1);
  }
  delete [] *p_top;
  delete [] p_top;

  row = i;
  column = j;

  p_top = new double*[row+1];
  *p_top = new double[row*column+1];

  for(int k=0; k<row; k++){
    *(p_top+k) = *p_top + (k*column);
  }

  for(int k1=0; k1<row; k1++){
    for(int k2=0; k2<column; k2++){
      p_top[k1][k2] = 0;
    }
  }
}


void Matrix::print(){
  printf("[");
  for(int i=0; i<row; i++){
    if(i!=0){printf("\n");}
    printf("[");
    for(int j=0; j<column; j++){
      printf("%f",p_top[i][j]);
      printf(" ");
    }
    printf("]");
  }
  printf("]\n");
}

Matrix Matrix::operator=(const Matrix &a){
  if(row != a.row || column!=a.column){
    change_size(a.row,a.column);
  }

  for(int i=0; i<row; i++){
    for(int j=0; j<column; j++){
      p_top[i][j] = a.p_top[i][j];
    }
  }
  return(*this);
}



Matrix Matrix::operator+(const Matrix &a){
  if(row != a.row || column != a.column){
    std::cerr << "err Matrix::operator+" << std::endl;
    std::cerr << " not equal matrix size" << std::endl;
    exit(0);
  }
  Matrix r(row,column);
  for(int i=0; i<row; i++){
    for(int j=0; j<column; j++){
      r.p_top[i][j] = p_top[i][j] + a.p_top[i][j];
    }
  }
  return(r);
}

Matrix Matrix::operator-(const Matrix &a){
  if(row != a.row || column != a.column){
    std::cerr << "err Matrix::operator-" << std::endl;
    std::cerr << " not equal matrix size" << std::endl;
  }

  Matrix r(row,column);
  for(int i=0; i<row; i++){
    for(int j=0; j<column; j++){
      r.p_top[i][j] = p_top[i][j] - a.p_top[i][j];
    }
  }
  return(r);
}


Matrix Matrix::operator*(const Matrix &a){
  if(column != a.row){
    std::cerr << "err Matrix::operator*" << std::endl;
    std::cerr << " not equal matrix size" << std::endl;
    exit(0);
  }

  Matrix r(row, a.column);
  for(int i=0;i<row; i++){
    for(int j=0;j<a.column; j++){
      for(int k=0; k<column; k++){
        r.p_top[i][j] += p_top[i][k] * a.p_top[k][j];
      }
    }
  }
  return(r);
}


Matrix operator*(const Matrix &a, double b)
{
  Matrix r(a.row, a.column);
  for(int i=0; i<a.row; i++){
    for(int j=0; j<a.column; j++){
      r[i][j] = b * a.p_top[i][j];
    }
  }
  return(r);
}

Matrix operator*(double b, const Matrix &a)
{
  Matrix r(a.row, a.column);
  for(int i=0; i<a.row; i++){
    for(int j=0; j<a.column; j++){
      r[i][j] = b * a.p_top[i][j];
    }
  }
  return(r);
}

Vector operator*(const Matrix &a, Vector b)
{
  if(a.column != b.size()){
    std::cerr << "err operator*" << std::endl;
    std::cerr << " size of matrix and vector do not match" << std::endl;
    exit(0);
  }
  Vector r(a.row);
  for(int i=0; i<a.row; i++){
    for(int j=0; j<a.column; j++){
      r[i] =  r[i] + a.p_top[i][j] * b[j];
    }
  }
  return(r);
}



void Matrix::unit_matrix()
{
  if(row != column){
    std::cerr <<"err in Matrix::unit_matrix()" << std::endl;
    exit(0);
  }

  int n = row;
  double** a = p_top;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      a[i][j] = 0;
      if(i == j) a[i][j] = 1;
    }
  }

}

Matrix Matrix::transpose()
{
  Matrix t(column, row);
  double** a = p_top;

  for(int i=0; i<row; i++){
    for(int j=0; j<column; j++){
      t[j][i] = a[i][j];
    }
  }
  return(t);
}
