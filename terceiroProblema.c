/*
    Ana Carolina Fainelo de Oliveira 
    28/10/2019
    
    Program that finds the longgest Fibonacci Like Sequence in an array.
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

#define NOT_FOUND -1
#define FOUND 1

#define VISITED     1
#define NON_VISITED 0

//-----------------------------------------------------------------------------------------------------------------------
void swap(int a, int b, int* array){
    int auxiliar;
    auxiliar = array[a];
    array[a] = array[b];
    array[b] = auxiliar;
}

//-----------------------------------------------------------------------------------------------------------------------
/*this sorting algorithm was choosen considering that the complexity of the biggestFibonacciSequence() is bigger than 
the sorting complexity  O(n^2) */
void insertionSort(int size, int* array){
    int i, j;
    for(i = 1; i < size; i++){
        j = i;
        while(j > 0 && array[j]<array[j-1]){
            swap(j, j-1, array);
            j--;
        }
    }

}

//-----------------------------------------------------------------------------------------------------------------------
int binarySearch(int numberToFind, int size, int* array, int* postion){  
    
    int start = 0, end = size-1, middle;
    
    while(end >= start){

        //middle position between start point and end point
        middle = (int)( (end+start)/2 );

        //if I find the number :)
        if(array[middle] == numberToFind){
            *postion = middle;
            return FOUND;
        }
        //change limits of search
        if(numberToFind < array[middle]) 
            end = middle-1;
        else
            start = middle+1;   
    }
    //if it gets to this line of the code, the number was not found
    return NOT_FOUND; 

}
//-----------------------------------------------------------------------------------------------------------------------
/*CONSIDERING REPEATED VALUES IN THE ARRAY...
    if i found a number but it was already visited, I go through the array in both directions looking for a 
    neighbor with the same value that hasn't been visited yet*/
int repeatedNonVisitedValues(int size, int* array, int* pos, int* visitedPositions){
    int initialPos = *pos;
    //looking backward in the array
    while(*pos-1 >= 0) {
        *pos -= 1;
        if(array[*pos] == array[initialPos] && visitedPositions[*pos] == VISITED) return FOUND;
        
    }
    //looking forward in the array 
    *pos = initialPos;
    while(*pos+1 < size) {
        *pos += 1;
        if(array[*pos] == array[initialPos] && visitedPositions[*pos] == VISITED) return FOUND;
        
    }
    return NOT_FOUND;
}

//CALCULATE SIZE OF FIBONACCI LIKE SUBSEQUENCE-------------------------------------------------------------------------
/* generating elements of the fibonacci like sequence based on f0 and f1, and keep doing it while the 
    generated numbers have its corresponding values in the array*/
int sizeOfFibLikeSubseq(int f0, int f1, int size, int* array){
    int i, nextF, pos = -1, sizeOfFibSeq = 2;
    char status = FOUND;
    int* visitedPositions;

    //initializing vesited vector as NON VISITED
    visitedPositions = (int*) calloc(size, sizeof(int));

    for(i = 2; i < size && status == FOUND; i++){
        //calculating next fibonacci in sequence
        nextF = f1+f0;
        f0 = f1;
        f1 = nextF;

        //looking for that number in the array
        status = binarySearch(nextF, size, array, &pos);

         
        if(status == FOUND) {
            //if the number was found in the array and hasn't been considered in the fibonnaci like sequence yet
            if(visitedPositions[pos] == NON_VISITED) {
                visitedPositions[pos] = VISITED;
                sizeOfFibSeq++; 
            }
            //if the number was found in the array but has already been considered in the fibonnaci like sequence
            else if (repeatedNonVisitedValues(size, array, &pos, visitedPositions) == FOUND){
                visitedPositions[pos] = VISITED;
                sizeOfFibSeq++; 
            }
            //All positions with this value in the array were already considered in the fibonacci like sequence
            else status = NOT_FOUND;
        } 

    }

    free(visitedPositions);
    return (sizeOfFibSeq == 2)? 0 : sizeOfFibSeq;
}

//-----------------------------------------------------------------------------------------------------------------------
int biggestFibonacciSequence(int size, int* array){

    int i, j, f0, f1;
    int biggestFibSeq = 0, calculatedSize;
    
    //making every possible choice of the first two numbers of the sequence:
    for(i = 0; i < size; i++){
        //combinating array[i] with the numbers before it in the array
        for(j = 0; j < i; j++){
            f0 = array[i]; 
            f1 = array[j];
            calculatedSize = sizeOfFibLikeSubseq(f0, f1, size, array);
            if (calculatedSize > biggestFibSeq) biggestFibSeq = calculatedSize;   
        }
        //combinating array[i] with the numbers after it in the array
        for(j = i+1; j < size; j++){
            f0 = array[i]; 
            f1 = array[j];
            calculatedSize = sizeOfFibLikeSubseq(f0, f1, size, array);
            if (calculatedSize > biggestFibSeq) biggestFibSeq = calculatedSize;  
        }
    }

    return biggestFibSeq;
}

//-----------------------------------------------------------------------------------------------------------------------
int main(){
    int i, size;
    int* array;
    int biggestFibSeq;
    char trash;

    //getting input: size of the array
    scanf("%d", &size);


    //creating vector with sizeOfArray positions
    array = (int*) malloc(size*sizeof(int));

    for(i = 0; i < size; i++){
        scanf("%d", &array[i]);
    }

    insertionSort(size, array); //ordering array
    biggestFibSeq = biggestFibonacciSequence(size, array);
    printf("%d\n", biggestFibSeq);

    free(array);
}
