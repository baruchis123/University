#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Structs.h"

/**
 *
 * @param a
 * @param b
 * @return
 */
int stringCompare(const void *a, const void *b)
{
   const char * aString = (char *) a;
   const char * bString = (char*) b;
   return strcmp(aString, bString);
}

/**
 *
 * @param word
 * @param pConcatenated
 * @return
 */
int concatenate(const void *word, void *pConcatenated)
{
    const char* ent = "\n";
    strcat((char*) pConcatenated, (const char *) word);
    strcat((char*) pConcatenated, ent);
    return 1;
}

/**
 *
 * @param s
 */
void freeString(void *s)
{
    free(s);
    s = NULL;
}

/**
 *
 * @param a
 * @param b
 * @return
 */
int vectorCompare1By1(const void *a, const void *b)
{
    Vector *aVec = (Vector *) a;
    Vector *bVec = (Vector *) b;
    int min = 0;
    if (aVec->len >= bVec->len)
    {
        min = bVec->len;
    }
    else
    {
        min =  aVec->len;
    }
    int i = 0;
    for (i = 0; i < min; i++)
    {
        if (aVec->vector[i] < bVec->vector[i])
        {
            return -1;
        }
        else if (aVec->vector[i] > bVec->vector[i])
        {
            return 1;
        }
    }
    if (aVec->len == bVec->len)
    {
        return 0;
    }
    else if (min == aVec->len)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void freeVector(void *pVector)
{
    Vector * vec = (Vector*) pVector;
    if (vec->vector != NULL)
    {
        free(vec->vector);
    }
    free(pVector);
}

void copyVec(Vector *maxVec, Vector* pVec)
{
    maxVec->vector = (double*) realloc((void*)maxVec->vector, pVec->len*sizeof(double));
    for (int i = 0; i < pVec->len; i++)
    {
        maxVec->vector[i] = pVec->vector[i];
    }
    maxVec->len = pVec->len;
}

/**
 *
 * @param pVector
 * @param pMaxVector
 * @return
 */
int copyIfNormIsLarger(const void *pVector, void *pMaxVector)
{
    double pNorm = 0;
    double maxNorm = 0;
    Vector *pVec = (Vector*) pVector;
    Vector *maxVec = (Vector*) pMaxVector;
    if (pVec->vector != NULL)
    {
        for (int i = 0; i < pVec->len; i++)
        {
            pNorm += pVec->vector[i];
        }
    }
    else
    {
        return 0;
    }
    if (maxVec->vector != NULL)
    {
        for (int i = 0; i < maxVec->len; i++)
        {
            maxNorm += maxVec->vector[i];
        }
    }
    else
    {
        copyVec(maxVec, pVec);
        return 1;
    }
    if (sqrt((double) (abs((int) pNorm))) > sqrt((double) (abs((int) maxNorm))))
    {
        copyVec(maxVec, pVec);
    }
    return 1;
}

Vector *findMaxNormVectorInTree(RBTree *tree)// implement it in Structs.c You must use copyIfNormIsLarger in the implementation!
{
    Vector * maxNormVector = (Vector*) calloc(sizeof(Vector), 1);
    if (maxNormVector == NULL)
    {
        return 0;
    }
    forEachRBTree(tree, copyIfNormIsLarger, (void*) maxNormVector);
    return maxNormVector;
}


