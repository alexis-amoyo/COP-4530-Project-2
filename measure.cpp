#include <iostream>
#include <string>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include "List.h"

using namespace std;
using namespace cop4530;

#define REPEATS 5

int main(int argc, char ** argv){

   List<int> nums[REPEATS];
   List<int> list;
   int size = 0;

   int cnt = 100;
   int range = cnt / 3;

   /*cout << "You have entered " << argc
         << " arguments:" << "\n";
  
    for (int i = 1; i < argc; ++i)
        cout << argv[i] << "\n";*/

   if(argc == 2){
      cnt = atoi(argv[1]);
      range = cnt / 3;
      //cout << cnt << endl;
   }

   for (int j = 0; j < REPEATS; j++) {
      /* initialize a random seed;
       * generate a random number between 1 and range.  */
      srand (time(NULL));
      for (int i = 0; i < cnt; i++) {
         int item = rand() % range + 1;
         nums[j].push_back(item);
         //cout << nums[j] << endl;
      }
   }

   /*
   for(int i = 0; i < size; i++){
      cout << nums[i] << endl;
   }
   */

   auto r_start = chrono::steady_clock::now();
   for (int i = 0; i < REPEATS; i++) {
      nums[i].reverse();
   }

   auto r_end = chrono::steady_clock::now();
   int usec = chrono::duration_cast<chrono::microseconds>(r_end - r_start).count();
   cout << "reverse " <<cnt<<"-item list: " << usec/REPEATS<<" usec"<<endl;


   for (int i = 0; i < REPEATS; i++) {
      nums[i].deduplicate();
   }

   r_end = chrono::steady_clock::now();
   usec = chrono::duration_cast<chrono::microseconds>(r_end - r_start).count();
   cout << "deduplicate " <<cnt<<"-item list: " << usec/REPEATS<<" usec"<<endl;

   //test 1 - size = 10
   /*size = 10;
   for(int i = 0; i < size; i++){
      int temp = rand() % range + 1;
      //cout << temp << endl;
      list.push_back(temp);
   }*/

   //test 2 - size = 50
   /*size = 50;
   for(int i = 0; i < size; i++){
      int temp = rand() % range + 1;
      //cout << temp << endl;
      list.push_back(temp);
   }*/
   
   
   //test 3 - size = 250
   size = 250;
   for(int i = 0; i < size; i++){
      int temp = rand() % range + 1;
      //cout << temp << endl;
      list.push_back(temp);
   }
   

   //int test = 0;
   for (int i = 0; i < REPEATS; i++) {
      nums[i].findSlice(list);
      //cout << test << endl;
   }
   //cout << test << endl;

   r_end = chrono::steady_clock::now();
   usec = chrono::duration_cast<chrono::microseconds>(r_end - r_start).count();
   cout << "findSlice " <<cnt<<"-item list: " << usec/REPEATS<<" usec"<<endl;
}