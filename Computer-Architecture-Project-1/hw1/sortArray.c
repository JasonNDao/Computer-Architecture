#include <stdio.h>
#include <stdlib.h>

void swap(int*first, int*second) 
{ 
    int temp =*first; 
   *first = *second; 
    *second= temp; 
} 
  
int partition (int *arr, int low, int high) 
{ 
    int pivot =arr[high];    
    int i = low - 1;  
  
    for (int j = low; j <= high- 1; j++) 
    { 
       
        if (arr[j] < pivot) 
        { 
            i++;    
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return i + 1; 
} 
  
void quicksort(int *arr, int low, int high) 
{ 
    if (low < high) 
    { 
        int sortedvalue = partition(arr, low, high); 
        quicksort(arr, low, sortedvalue - 1); 
        quicksort(arr, sortedvalue + 1, high); 
    } 
} 
int main(int argc, char*argv[])
{
    if (!fopen(argv[1],"r")){
        printf("error");
        return 0;
    }
    FILE *filepointer=fopen(argv[1],"r");
    int length;
    int odd=0;
    int even=0;
    fscanf(filepointer,"%d\n",&length);
    int big[length];
    for(int i=0;i<length;i++){
        fscanf(filepointer,"%d\t",&big[i]);
        if (big[i]%2==1 || big[i]%2==-1){
            odd++;
        }
        else{
            even++;
        }
    }
    int eveny[even];
    int oddy[odd];
    int oddindex=0;
    int evenindex=0;
    for (int i=0;i<length;i++){
        if (big[i]%2==1 || big[i]%2==-1){
            oddy[oddindex]=big[i];
            oddindex++;
        }
        else{
            eveny[evenindex]=big[i];
            evenindex++;
        }
    }
    quicksort(eveny,0,even-1);
    quicksort(oddy,0,odd-1);
    for(int k=0;k<even;k++){
        printf("%d\t",eveny[k]);
    }
    for(int j=odd-1;j>-1;j--){
        printf("%d\t",oddy[j]);
    }
    return 0;
}
