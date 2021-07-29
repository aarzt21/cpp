/*
 The following program is my homework assignment for my informatics course. It allows us to perform 
 1) vector x vector (i.e. inner product) 
 2) matrix x vector 
 3) matrix x matrix 
 computations 
*/


/*
Home work task: 
Write program that implements the multiplication of integer vectors and matrices using std::vector.
Program must support the following operations
1. Dot product of two vectors (i.e. the inner product)
2. Matrix vector product
3. Matrix product

Implement the following program structure:
1. Query for the two operands form the input: left operand first, then right operand
2. If no operations can be applied output error. This happens if left operand is vector
    and right operand is matrix - thus the dimensions don't match.
3. Output result of operation.

*/

#include<iostream>
#include<vector>
#include<string>
using matrix = std::vector<std::vector<int>>;
using vector = std::vector<int>;

//----------------------------- inner product case: v^t x v ----------------------------------

void fill_vec(vector& vec){
  for (unsigned int i = 0; i < vec.size(); ++i){
    std::cin >> vec[i];
  }
}


void inner_prod(vector& vec1, vector& vec2){ // use


  unsigned int n = vec1.size();
  vector res = vector(n,0); // init container

  for (unsigned int i = 0; i < n; ++i){
    res[i] = vec1[i]*vec2[i];
  }

  int sum = 0;
  for(unsigned int i = 0; i < n; ++i){
    sum = sum + res[i];
  }

  if (vec1.size() != vec2.size()) std::cout << "error";
  else std::cout << "s \n" << sum;
}


//----------------------------- matrix vector multiplication: M(nXp) x v(nX1) ----------------------------------

int inner_prod2(vector vec1, vector vec2){

    unsigned int n = vec1.size();
    vector res = vector(n,0); // init container

    for (unsigned int i = 0; i < n; ++i){
      res[i] = vec1[i]*vec2[i];
    }

    int sum = 0;
    for(unsigned int i = 0; i < n; ++i){
      sum = sum + res[i];
    }
    return sum;
}

void fill_mat(matrix& mat){
  unsigned int n = mat.size(); // rows
  unsigned int p = mat[0].size(); // cols (assuming each row as same length)

  for (unsigned int i = 0; i < n; ++i){
    for (unsigned int j = 0; j < p; ++j){
      std::cin >> mat[i][j];
    }
  ;}
}

void mat_vec_prod(matrix& mat, vector& vec){
  unsigned int n = mat.size();
  unsigned int p = mat[0].size();
  if(p != vec.size()) std::cout << "error";

  else{
    vector res = vector(n,0);
    for (unsigned int i = 0; i < n; ++i){
      res[i] = inner_prod2(mat[i], vec);
    }
    std::cout << "v " << res.size() << "\n";
    for(unsigned int i = 0; i < res.size(); ++i) std::cout << res[i] << " ";
  }

}


//----------------------------- matrix matrix multiplication: M(nXp) x M(nXp) ----------------------------------

vector col(matrix& mat, unsigned int idx){
  unsigned int n, p; n = mat.size(); p = mat[0].size();

  vector res = vector(n,0);
  if (idx > p) {
    std::cout << "Error: column index out of bound. Will return empty vector.";
    return res;}

  else{
    for (unsigned int i = 0; i < n; ++i){
      res[i] = mat[i][idx];
    }
    return res;
  }
}


void mat_mat_prod(matrix& mat1, matrix& mat2){
  unsigned int n1, n2, p1, p2;
  n1 = mat1.size(); n2 = mat2.size(); p1 = mat1[0].size(); p2 = mat2[0].size();
  if (p1 != n2) std::cout << "error";

  else {

    matrix res = matrix(n1,vector(p2,0)); // init empty results matrix
    for(unsigned int i = 0; i < n1; ++i){
      for(unsigned int j = 0; j < p2; ++j){
        res[i][j] = inner_prod2(mat1[i],col(mat2,j));
      }
    ;}

    //Print resulting matrix
    std::cout << "m " << res.size() << " " << res[0].size() << "\n";
    for (unsigned int i = 0; i < res.size(); ++i){
      for (unsigned int j = 0; j < res[0].size(); ++j){
        std::cout << res[i][j] << " ";
      }
      std::cout << "\n";
    }

  }

}



// ------------------------------ main program -----------------------------------------------------------------------


int main(){

  // First entry (vector case)
  char entry1;
  std::cin >> entry1;
  vector vec1;

  if (entry1 == 'v') {
    unsigned int n1; std::cin >> n1;
    vec1 = vector(n1,0);
    fill_vec(vec1);
  }
  // First entry (matrix case)
  matrix mat1;
  if (entry1 == 'm'){
    unsigned int n;
    unsigned int p;
    std::cin >> n >> p; //cols
    mat1 = matrix(n,vector(p,0));
    fill_mat(mat1);
  }


  // Second entry
  char entry2;
  std::cin >> entry2;
  vector vec2;

  if (entry2 == 'v') {
    unsigned int n2; std::cin >> n2;
    vec2 = vector(n2,0);
    fill_vec(vec2);
  }

  // Second entry (matrix)
  matrix mat2;
  if (entry2 == 'm'){
    unsigned int n2;
    unsigned int p2;
    std::cin >> n2 >> p2; //cols
    mat2 = matrix(n2,vector(p2,0));
    fill_mat(mat2);
  }


  //operations
  if (entry1 == 'v' && entry2 == 'v') inner_prod(vec1, vec2);
  if (entry1 == 'm' && entry2 == 'v') mat_vec_prod(mat1, vec2);
  if (entry1 == 'm' && entry2 == 'm') mat_mat_prod(mat1, mat2);
  if (entry1 == 'v' && entry2 == 'm') std::cout << "error" ;



  return 0;
}
