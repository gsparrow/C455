// vim: nu expandtab shiftwidth=2 softtabstop=2 foldmethod=marker
/*
 *  Created by Hang Dinh on 4/13/2016.
 *      The purpose of this assignment is to perform empirical analysis of sorting algorithms
 */

#include <iostream>
#include <string.h>
#include <chrono>
#include <limits>
#include <random>
using namespace std;

const int N=100000; //maximal data size
unsigned long long comparisons=0; //the number of comparisons

/**************************** function prototypes ******************************/

//Menu for the user inputs
//This menu returns the length of the array.
int menu(int my_array[]);

//displays information on program options
void display_help();

int Hoare_partition(int a[], int first, int last);
void quicksort (int a[], int first, int last);

//Interchanges the values of v1 and v2.
void swapValues(int& v1, int& v2);

//sorts the numbers in a[0...(n-1)].
void badsort(int a[], int n);


/****************************** main function  ********************************/

int main(int argc, char* argv[]) 
{
  bool verbose=false;
  const int my_array_beginning =0;
        int my_array_end       =0;
        int my_array[N]        ={0};
        int qsort_array[N]     ={0};
  if (argc>1)
  {
    if (strcmp(argv[1],"--verbose")==0 || strcmp(argv[1],"-v")==0)
    {
      verbose=true;
    }
    else
    {
      display_help();
      return 0;
    }
  }
  try
  {
    my_array_end=menu(my_array);
    for (int i=0; i<my_array_end; i++)
    {
      qsort_array[i]=my_array[i];
    }
    if (verbose)
    {
      std::cout << "The array is as follows" << std::endl;
      for (int i=0; i<my_array_end; i++)
      {
        std::cout << my_array[i] << " ";
      }
    }
    std::cout << std::endl;
    comparisons=0;
    auto time_begin = std::chrono::high_resolution_clock::now();
    //I need to subtract 1 from the end of the array, or quicksort adds an extra element;
    quicksort (qsort_array, my_array_beginning, my_array_end-1);
    auto time_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_total_in_ms = time_end - time_begin;
    std::cout << "This quicksort took " << time_total_in_ms.count() << " milliseconds to run." << std::endl;
    std::cout << "The effect of the sort is " << comparisons << " comparison operations." << std::endl;
    if (verbose)
    {
      for (int i=my_array_beginning; i<my_array_end; i++)
      {
        std::cout << qsort_array[i] << " ";
      }
    }
    comparisons=0;
    time_begin = std::chrono::high_resolution_clock::now();
    badsort(my_array, my_array_end);
    time_end = std::chrono::high_resolution_clock::now();
    time_total_in_ms = time_end - time_begin;
    std::cout << "This badsort took " << time_total_in_ms.count() << " milliseconds to run." << std::endl;
    std::cout << "The effect of the sort is " << comparisons << " comparison operations." << std::endl;
    if (verbose)
    {
      for (int i=my_array_beginning; i<my_array_end; i++)
      {
        std::cout << my_array[i] << " ";
      }
    }
  }
  catch (int error_number) //{{{
  {
    if (error_number==1)
    {
      std::cout << std::endl << "The Length of the array was invalid. It must be greater than 0" << std::endl;
    }
    if (error_number==2)
    {
      std::cout << std::endl << "The Length of the array was invalid. It must be less than " << N << std::endl;
    }
    if (error_number==3)
    {
      std::cout << std::endl << "You entered something other than y or n when asked if you wanted to input the array manually." << std::endl;
    }
    if (error_number==4)
    {
      std::cout << std::endl << "You entered something something other than a number into the array." << std::endl;
    }
    else
    {
      std::cout << std::endl << "An unexpected error has occured." << std::endl;
    }
  } //}}}
  return 0;
}




/****************************** function definitions  ********************************/
int menu(int my_array[])
{
  int length=0;
  char manual=0;
  std::cout << "Enter the length of the array to be sorted: ";
  std::cin  >> length;
  if (length < 1)
  {
    throw 1;
  }
  else if (length > N)
  {
    throw 2;
  }
  int my_int_array[length];
  std::cout << "Do you want to manually enter the values for the input array? (y/n): ";
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get(manual);
  if (manual =='n' || manual=='N')
  {
    //"Randomly" generate the array for debugging purposes{{{
    //auto my_seed=42;
    //std::mt19937 my_engine(my_seed); 
    //}}}
    //Randomly generate the array {{{
    std::random_device my_seed;
    std::mt19937 my_engine(my_seed()); 
    //}}}
    std::uniform_int_distribution<int> my_distribution(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    for (int i=0; i<length; i++)
    {
      my_array[i]=my_distribution(my_engine);
    }
  }
  else if (manual =='y' || manual=='Y')
  {
    //Enter the array manually.
    std::cout << "Please input the array manually." << std::endl;
    for (int i=0; i<length; i++)
    {
      if(!(std::cin >> my_array[i]))
        throw 4;
    }
  }
  else
  {
    throw 3;
  }
  return length;
}

void display_help()
{
  std::cout << "The options for this program are as follows." << std::endl;
  std::cout << "-v or --verbose: put the program in verbose mode and output all arrays" << std::endl;
}

int Hoare_partition(int a[], int first, int last) //{{{
{
  int pivot=a[first];
  int i = first - 1,  j = last+1; 
  while (true)  
  {
    //comparisons++;
    do
    {
      comparisons++;
      ++i;                  
    }
    while (a[i] < pivot); 
    do
    {
      comparisons++;
      --j;                  
    }
    while (a[j] > pivot);
    //comparisons++;
    if (i<j) 
    {
      swapValues (a[i], a[j]);
    }
    else
      return j;  
  }
} //}}}

void quicksort (int a[], int first, int last) //{{{
{
  //comparisons++;
  if (last <= first)      //base case; 
    return;         //arrays of length<=1 are sorted        
  int p=Hoare_partition(a, first, last); 
  quicksort (a, first, p);  
  quicksort (a, p+1, last);   
} //}}}


void swapValues(int& v1, int& v2) //{{{
{
  int temp;
  temp = v1;
  v1 = v2;
  v2 = temp;
} //}}}

void badsort(int a[], int n) //{{{
{
  int i=0;
  while(i<n-1)
  {
    comparisons++;
    if(a[i]>a[i+1])
    {
      swap(a[i], a[i+1]);
      i=0;    //Note that i is being reset!
      continue;
    }
    i++;
  }
} //}}}
