/*
 * Client test for implementation and header files of Dictionary ADT
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

int main(){
   Dictionary first;
   char* printOut;
  
   A = newDictionary();
   insert(first, "10","apple");
   insert(first, "9","banana");
   insert(first, "8","cat");
   insert(first, "7","dog");
   insert(first, "6","elephant");
   insert(first, "5","fig");
   insert(first, "4","giraffe");
   insert(first, "3","hexagon");
   insert(first, "2","isotope");
   insert(first, "1","january");

   insert(A, "1","july");

   printOut = DictionaryToString(first);
   printf("%s\n", printOut);
   printf("size(first) = %d\n", size(first));
   free(printOut);

   //lookup key in Dictionary first
   printf("lookup: %d\n", lookup(first, "3");
   printf("lookup: %d\n", lookup(first, "8");

   //lookup key not in Dictionary first
   printf("lookup: %d\n", lookup(A, "1")
   printf("lookup: %d\n", lookup(first, "key");

   delete(first, "10");
   delete(first, "8");
   delete(first, "6");

   // print out the Dictionary
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);

   printf("size(first) = %d\n", size(first));

   makeEmpty(first);
   makeEmpty(second);

   str = DictionaryToString(first);
   printf("%s\n", printOut);
   printf("size(first) = %d\n", size(first));
   
   free(printOut);
  
   freeDictionary(&first);

   return EXIT_SUCCESS;
}
