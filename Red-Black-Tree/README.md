# Red-Black-Tree
### This project was given as a final assignment in the C part of the C\CPP Workshop course in the Computer Science program of Hebrew University. In this program, complex dynamic allocations, generic programming in C and a general implementation of a hard data structure were expected of the students. The program is divided into two separate parts. The first being the implementation of the data structure, and the second is a file implementing different Structs intended to exhibit the genericity of the Red-Black Tree.

## RBTree Implementation
In our implementation of the data structure we created an instance and defined the expected characteristics of the Red Black Tree by writing the following functions:
```c 
RBTree *newRBTree(CompareFunc compFunc, FreeFunc freeFunc)
```
A function that allocates an instance of a RBTree for a specific type, which accepts a pointer to a function which can can be used by the tree to perform comparisons on the nodes.
```c
void freeRBTree(RBTree **tree);
```
The function that frees the pointer to the RBTree. We note that the function accepts a pointer to a pointer, as passing an argument to a function in C sends a copy of the argument, and passing only a pointer would have resulted in freeing a copy to the pointer to the RBTree and not the wanted pointer.
```c
int insertToRBTree(RBTree *tree, void *data)
```
This function adds an item in accordance to the instance of the specific RbTree accepted as an argument, maintaing the balance of the tree (to have a constant complexity of O(logn)).
```c
int deleteFromRBTree(RBTree *tree, void *data)
```
The function that deletes a node from the RBTree.
```c
int RBTreeContains(const RBTree *tree, const void *data)
```
This function determines whether a node is in a tree or not.
Note that for the above three functions, functions implementing the rotation of nodes after insertation/deletion were written as per the RBTree algorithm.
In addition to the functions defining and creating the data structure, an additional function allowing added functionality was written:
```c
int forEachRBTree(const RBTree *tree, forEachFunc func, void *args)
```
This function activates a given function "forEachFunc" on each node of the tree.

## Structs of Data Types
In this part of the project, structs of two data types were created, followed by implementations of their comparison functions, and forEachFuncs as per the API of the generic RBTree:
1. Vector - This data type implements a vector over the column space. Functions written for this library include:
```c
int vectorCompare1By1(const void *a, const void *b)
```
A comparison function of the two vectors passed through (as void types since the tree is generic). The comparison is described in the doc string of the function.
```c
void freeVector(void *pVector)
```
The freeFunc of this data type as per API.
```c
Vector *findMaxNormVectorInTree(RBTree *tree)
```
This function uses the forEachFunc of the RBTree library and the helper function copyIfNormIsLarger (to be explained below) in order to find the maximum Norm of the RBTree.
```c
int copyIfNormIsLarger(const void *pVector, void *pMaxVector)
```
A function that copies to the pMaxVector pointer, a vector of a specific node if its norm is larger than the norm of the vector currently residing in said memory location.

2. String - As this data type already exists in C, only functions needed for the interface of the RBTree were added:
```c
int stringCompare(const void *a, const void *b)
```
The comparison function of the string data type,
```c
void freeString(void *s)
```
The free function for the string data type.
```c
int concatenate(const void *word, void *pConcatenated)
```
An example of a forEachFunc that iterates over an instance of a RBTree of the string data type and concatenates all its nodes.


