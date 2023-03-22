#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_,PRINT_FUNC priFunc_){
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	(pArr->pElemArr) = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = priFunc_;
	return pArr;
}

void DeleteAdptArray(PAdptArray pArr){
	// return if pArr null
	if (pArr == NULL)
		return;
	
	// for all the array delete with delfunc and free the element
	for(int i = 0; i < pArr->ArrSize; ++i)
	{
		if(pArr->pElemArr[i]!=NULL){
			pArr->delFunc((pArr->pElemArr)[i]);
		}
	}
	free(pArr->pElemArr);
	free(pArr);

}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem){
    PElement* newpElemArr;
	// return fail if pArr null
	if (pArr == NULL)
		return FAIL;
	// return fail if idx < 0 null
	if (idx < 0)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		// Extend Array
		newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement));
		if (newpElemArr == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem
	if((pArr->pElemArr[idx])!=NULL){
		pArr->delFunc((pArr->pElemArr)[idx]);
	}

	// copy with the copyfunc
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx){
	// return null if idx<0 null
	if(idx < 0){
		return NULL;
	}
	// return null if pArr null
	if(pArr == NULL){
		return NULL;
	}
	// return null if idx bigger from size of arr
	if(pArr->ArrSize -1 < idx){
		return NULL;
	}
	// return null if index idx=null
	if(pArr->pElemArr[idx] == NULL){
		return NULL;
	}
	// copy the element
	PElement copyOfElement = pArr->copyFunc(pArr->pElemArr[idx]);
	return copyOfElement;
}

int GetAdptArraySize(PAdptArray pArr){
	// return -1 if pArr null
	if(pArr == NULL){
		return -1;
	} 

	// return the size of arr
	return pArr->ArrSize;
}
void PrintDB(PAdptArray pArr){
	// return if pArr null
	if(pArr == NULL){
		return;
	}

	// for all the array print with printfunc
	for(int i = 0; i < pArr->ArrSize; i++){
		if(pArr->pElemArr[i] != NULL){
			pArr->printFunc(pArr->pElemArr[i]);
		}
	}
}

