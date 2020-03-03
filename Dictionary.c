/* Isabella Man
 * CSE 15
 * 12/5/19
 * pa5
 * Dictionary.c
 * Dictionary ADT based on Hash Tables, or an array that stores set of (key, value) pairs, where key and value are strings
 * Evenly distributes probability of where each key is stored in a given size of a Hash Table
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include"Dictionary.h"

const int tableSize = 101; // choice of length can change

// Hash functions ---------------------
// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);
      if ( shift == 0 ) {
         return value;
      }
         return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
   unsigned int result = 0xBAE86554;
   while (*input) {
      result ^= *input++;
      result = rotate_left(result, 5);
   }
   return result;
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
   return pre_hash(key)%tableSize;
}


// Private Types and Functions ---------------------------------
// NodeObj type
typedef struct NodeObj{
   //int item;
   char* key;		// null terminated char array
   char* value;		// null terminated char array
   struct NodeObj* next;
} NodeObj;

// Node type
typedef NodeObj* Node;

// newNode()
// constructor for the Node type
Node newNode(char* k, char* v) {
   Node N = malloc(sizeof(NodeObj));
   //assert(N!=NULL);
   N->key = k;
   N->value = v;
   N->next = NULL;
   return N;
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if(pN != NULL && *pN != NULL){
      free(*pN);
      *pN = NULL;
   }
}

// freeAllNodes()
// uses recursion to free all the Nodes in list headed by H
void freeAllNodes(Node H){
   if(H != NULL){
      freeAllNodes(H->next);
      freeNode(&H);
   }
}

// DictionaryObj type
typedef struct DictionaryObj{
   //Node head;           // pointer to the first Node in list
   Node* table;         // pointer to an array of LinkedLists, table T
   int numPairs;        // number of key-value pairs in this Dictionary
} DictionaryObj;

// Helper function -----------------------------------------------------------
/*Node findKey(Dictionary D, char* k){
   Node T;
   if (D == NULL) {
      fprintf(stderr,
         "Dictionary Error: findKey() called on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   T = D->head;
   //int index = hash(k);
    
 
 for(int i = 0; i < D->numPairs; i++) {
      if ((T->key) == k) {
         T = T->next;
      }
   }
   return T;
}
*/

// Exported type --------------------------------------------------------------

// Dictionary
typedef struct DictionaryObj* Dictionary;

// Constructors-Destructors ---------------------------------------------------
// newDictionary()
// Constructor for the Dictionary ADT
Dictionary newDictionary(){
   Dictionary D = malloc(sizeof(DictionaryObj));
   //D->head = NULL;
   D->table = calloc(tableSize, sizeof(Node));	// set table to point to newly allocated heap memory
   D->numPairs = 0;
   return D;
}

// freeLinkedList()
// Destructor for the Dictionary ADT
void freeDictionary(Dictionary *pD){
   if(pD != NULL && *pD != NULL){
      makeEmpty(*pD);
      makeEmpty(pD);
      free(*pD);
      free(pD);
      *pD = NULL;
      pD = NULL;
   }
}


// ADT operations -------------------------------------------------------------

// size()
// Return the number of (key, value) pairs in Dictionary D.
int size(Dictionary D) {
   if(D == NULL){
      fprintf(stderr,
         "Dictionary Error: calling size() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return D->numPairs;
}

// lookup()
// If D contains a pair whose key matches argument k, then return the 
// corresponding value, otherwise return NULL.
char* lookup(Dictionary D, char* k) {
   if(D == NULL){
      fprintf(stderr,
         "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   Node T;
   /*for (int i = 0; i < tableSize; i++) {
      if (D->table[i] != NULL) {
         T = D->table[i];
         if (strcmp(T->key, k) == 0) {
               return T->value;
         }
         while (T->next != NULL) {
            if (strcmp(T->key, k) == 0) {
               return T->value;
            }
            T = T->next;
        }
      }
   }*/

   int index = hash(k);
   if(D->table[index] != NULL) {
      T = D->table[index];
      if (strcmp(T->key, k) == 0) {
         return T->value;
      }
      else {      
         while (T->next != NULL) {
            T = T->next;
            if (strcmp(T->key, k) == 0) {
               return T->value;
            }
            //T = T->next;
         }
      }
   }
   else {
      return NULL;
   }
}

// insert()
// Insert the pair (k,v) into D.
// Pre: lookup(D, k)==NULL (D does not contain a pair whose first member is k.)
void insert(Dictionary D, char* k, char* v){
   if(D == NULL){
      fprintf(stderr,
         "Dictionary Error: calling insert() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   int index = hash(k);
   //printf("test: %d\n", index);
   //place (k,v) at head of list T[h(k)]

   Node T;
   if (D->table[index] == NULL) {
      T = D->table[index];
      T = newNode(k, v);
      D->table[index] = T;
   }
   else {
      T = newNode(k, v);
      T->next = D->table[index];
      D->table[index] = T;

      //T = D->table[index];
      //T->next = newNode(k, v);
      //T = T->next; 
   }
   D->numPairs++;
}



// delete()
// Remove pair whose first member is the argument k from D.
// Pre: lookup(D,k)!=NULL (D contains a pair whose first member is k.)
void delete(Dictionary D, char* k){
   if(D == NULL){
      fprintf(stderr,
         "Dictionary Error: calling delete() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

  int index = hash(k);
  Node T = D->table[index];
  
  if(lookup(D, k) != NULL) {
     if (strcmp(T->key, k) == 0) {
        T = D->table[index];
        D->table[index] = T->next;
        T->next = NULL;
        freeNode(&T);
     }
     else {
        T = T->next;
     }
   }
   D->numPairs--;
}


// makeEmpty()
// Reset D to the empty state, the empty set of pairs
void makeEmpty(Dictionary D) {
   if(D == NULL){
      fprintf(stderr,
         "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   //Node T;
   for (int i = 0; i < tableSize; i++) {
      /*if (D->table[i] != NULL) {
         T = D->table[i];
         while (T->next != NULL) {
            freeNode(T);
            T = T->next;
         }*/
         freeAllNodes(D->table[i]);
         D->table[i] = NULL;
      //}
   }
   //free(&T);
   D->numPairs = 0;
}

// Other Operations -----------------------------------------------------------
int countChars(Dictionary D) {
   int count = 0;
   Node T;
   if (D != NULL) {
      for (int i = 0; i < tableSize; i++) {
         if (D->table[i] != NULL) {
            T = D->table[i];
            count += strlen(T->key) + strlen(T->value) + 2;
            while (T->next != NULL) {
               T = T->next;
               count += strlen(T->key) + strlen(T->value) + 2;
            }
         }
      }
   }

   return count;
}      

// DictionaryToString()
// Determines a text representation of the current state of Dictionary D. Each 
// (key, value) pair is represented as the chars in key, followed by a space,
// followed by the chars in value, followed by a newline '\n' char. The pairs 
// occur in alphabetical order by key. The function returns a pointer to a char 
// array, allocated from heap memory, containing the text representation 
// described above, followed by a terminating null '\0' char. It is the 
// responsibility of the calling function to free this memory.
char* DictionaryToString(Dictionary D) {
   char* str;
   if (D == NULL) {
      fprintf(stderr,
         "IntegerList Error: DictionaryToString() called on NULL IntegerList\n");
      exit(EXIT_FAILURE);
   }

   int count = countChars(D);
   //printf("countt: %d\n", count); 

   Node T;
   //str = malloc((D->numPairs*4) * sizeof(char*));
   str = malloc((count + 4) * sizeof(char));
   //str = calloc(count, sizeof(char));
 
   for (int i = 0; i < tableSize; i++) {
      if (D->table[i] != NULL) {
         T = D->table[i];
         char* key = T->key;
         char* value = T->value;
         strcat(str, key);
         strcat(str, " ");
         strcat(str, value);
         strcat(str, "\n");
         while (T->next != NULL) {
            T = T->next;
	    char* key = T->key;
            char* value = T->value;
            strcat(str, key);
            strcat(str, " ");
            strcat(str, value);
            strcat(str, "\n");
         }
      }
   }  
   //str[strlen(str)-1] = '\0';
   return str;
}
