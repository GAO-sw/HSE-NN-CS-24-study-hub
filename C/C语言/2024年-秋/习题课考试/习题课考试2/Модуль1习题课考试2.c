#include <stdio.h>
#include <stdlib.h>

// task1

/* int getColumnSum(int** matrix, int n, int column){
  int sum = 0;
  for(int i = 0; i < n; i++){
    sum += matrix[i][column];
  }
  return sum;
}

void swapColumns(int** matrix, int n, int column1, int column2){
  for(int i = 0; i < n; i++){
    int temp = matrix[i][column1];
    matrix[i][column1] = matrix[i][column2];
    matrix[i][column2] = temp;
  }
}

int main(){
  int n;
  scanf("%d", &n);

  int** matrix = (int**)malloc(sizeof(int*) * n);

  for(int i = 0; i < n; i++){
    matrix[i] = (int*)malloc(sizeof(int) * n);
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      scanf("%d", &matrix[i][j]);
    }
  }

  int max_sum = getColumnSum(matrix, n, 0);
  int min_sum = max_sum;
  int max_column = 0;
  int min_column = 0;

  for(int i = 1; i < n; i++){
    int sum = getColumnSum(matrix, n, i);
    if(sum > max_sum){
      max_sum = sum;
      max_column = i;
    }
    else{
      min_sum = sum;
      min_column = i;
    }
  }

  swapColumns(matrix, n, max_column, min_column);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  for(int i = 0; i < n; i++){
    free(matrix[i]);
  }
  free(matrix);
  return 0;
} */

// task2

/* int get2Rowsproduct(int** matrix, int n, int row1, int row2){
  int product = 1;
  for(int i = 0; i < n; i++){
    product = matrix[row1][i] * matrix[row2][i];
  }
  return product;
}


int main(){
  int n;
  scanf("%d", &n);

  int** matrix = (int**)malloc(sizeof(int*) * n);

  for(int i = 0; i < n; i++){
    matrix[i] = (int*)malloc(sizeof(int) * n);
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      scanf("%d", &matrix[i][j]);
    }
  }

  int max_product = get2Rowsproduct(matrix, n, 0, 1);
  int maxrow1 = 0;
  int maxrow2 = 1;
  for(int i = 0; i < n; i++){
    for(int j = i + 1; j < n; j++){
      int product = get2Rowsproduct(matrix, n, i, j);
      if(product > max_product){
        max_product = product;
        maxrow1 = i;
        maxrow2 = j;
    }
  }
}
  printf("The rows we are loking for is:%dth and %dth\n", maxrow1 + 1, maxrow2 +
1);

  for(int i = 0; i < n; i++){
    free(matrix[i]);
  }
  free(matrix);
  return 0;
} */

// task3

void changeevenletter(char *string) {
  int count = 0;
  int k = 0;
  while (string[k] != '\0') {
    count++;
    k++;
  }

  for (int i = 0; string[i] != '\0'; i++) {
    if (i % 2 == 1) {
      if (string[i] >= 'a' && string[i] <= 'z') {
        string[i] = string[i] - 32;
      } else if (string[i] >= 'A' && string[i] <= 'Z') {
        string[i] = string[i] + 32;
      }
    }
  }
}

int main() {
  char string[20];
  printf("Please enter a string:\n");
  scanf("%s", string);
  changeevenletter(string);
  printf("%s", string);
}