#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Element Element;


Element* elementpointers[1000];
int ElementPointerCount = 0;


struct Element{
    char tagName[10];
    char className[10];
    Element* children[10];
    Element* parent;
    short currentChildCount;
};


Element* elementConstructor(char tagName[10], char className[10]){
    Element* elP = (Element*)malloc(sizeof(Element));
    assert(elP);
    strcpy(elP->tagName, tagName);
    strcpy(elP->className, className);
    elP->currentChildCount = 0;
    for (int i = 0; i < 10; i++) {
        elP->children[i] = NULL;

    }
    return elP;
}
