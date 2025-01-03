#include <stdio.h>
#include <math.h>

//task 1
/* int main(){
    float arr[9];
    float x = -2.0f;
    for(int i = 0; i < 9; i++){
        arr[i] = -2.4f * pow(x,2) + 5.0f * x - 3.0f;
        x = x + 0.5f;
    }
    for(int i = 0; i < 9; i++){
        printf("%f ", arr[i]);
    }
    return 0;
} */
// task 2
/* int main(){
    int target = 0;
    scanf("%d", &target);
    int arr[target];
    int count = 0;
    for(int i = 2; i <= target; i++){
        int j;
        for(j = 2; j <= sqrt(i); j++){
            if(i % j == 0){
                break; 
            }
        }
        if(j > sqrt(i)){
            arr[count] = i;
            count++;
        }
    }
    for(int i = 0; i < count; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}
 */
// task3
/*
int main()
{
    int arr[10];
    int max = 0;
    int index = 0;
    int temp = 0;
    for(int i = 0; i < 10; i++){
        scanf("%d", &arr[i]);
    }
    for(int i = 0; i < 10; i++){
        if(arr[i] > max){
            max = arr[i];
            index = i;
        }
    }
    temp = arr[0];
    arr[0] = arr[index];
    arr[index] = temp;
    printf("%d", max);
    printf("\n");
    for(int i = 0; i < 10; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}*/
// task4
/*
int main(){
    int arr[15];
    float aver = 0;
    int sum = 0;
    float new_arr[15];
    for(int i = 0; i < 15; i++){
        scanf("%d", &arr[i]);
    }
    for(int i =0; i < 15; i++){
        sum += arr[i];
    }
    aver = (float) sum / 15;
    for(int i = 0; i < 15; i++){
        new_arr[i] = arr[i] - aver;
    }
    for(int i = 0; i < 15; i++){
        printf("%f ", new_arr[i]);
    }
    return 0;
}
*/



















