/*
 *  Created by Hang Dinh on 4/13/2016.
 *	The purpose of this assignment is to perform empirical analysis of sorting algorithms
 */

#include <iostream>
#include <ctime>
using namespace std;

const int N=100000; //maximal data size

/**************************** function prototypes ******************************/

int Hoare_partition(int a[], int first, int last);
void quicksort (int a[], int first, int last);

//Interchanges the values of v1 and v2.
void swapValues(int& v1, int& v2);

//sorts the numbers in a[0...(n-1)].
void badsort(int a[], int n);


/****************************** main function  ********************************/

int main() 
{

	
	return 0;
}




/****************************** function definitions  ********************************/

int Hoare_partition(int a[], int first, int last)
{
	int pivot=a[first];
 	int i = first - 1,  j = last+1; 
 	while (true)  
	{
	  do
          ++i;                  
      while (a[i] < pivot); 
	  do
          --j;                  
      while (a[j] > pivot);
	  if (i<j) 
		    swap (a[i], a[j]);
	  else
		    return j;  
	} 
}

void quicksort (int a[], int first, int last)
{
   	if (last <= first) 	//base case; 
		return; 	//arrays of length<=1 are sorted	
	int p=Hoare_partition(a, first, last); 
	quicksort (a, first, p);  
    quicksort (a, p+1, last);   
}


void swapValues(int& v1, int& v2)
{
    int temp;
    temp = v1;
    v1 = v2;
    v2 = temp;
}

void badsort(int a[], int n)
{
	int i=0;
	while(i<n-1)
	{
		if(a[i]>a[i+1])
		{
			swap(a[i], a[i+1]);
			i=0;	//Note that i is being reset!
			continue;
		}
		i++;
	}
}