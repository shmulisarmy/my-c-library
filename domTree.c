#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "/Users/Shmuli/my-c-library/colors.c"




typedef struct Element Element;


Element* elementpointers[1000];
int ElementPointerCount = 0;


struct Element{
    char tagName[10];
    char className[10];
    Element* parent;
    Element* children[10];
    int childListMutex;
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


void appendChild(Element* parent, Element* child){
    while (parent->childListMutex){
        usleep(1000);
    }
    parent->childListMutex = 1;
    parent->children[parent->currentChildCount] = child;
    parent->currentChildCount++;
    parent->childListMutex = 0;
    child->parent = parent;
}


void displayElement(Element* elP, int depth){
    for (int i = 0; i < depth; i++){
        printf("\t");
    }
    printf("<%s%s%s class='%s'>\n", blue, elP->tagName, white, elP->className);
    for (int i = 0; i < elP->currentChildCount; i++){
        displayElement(elP->children[i], depth+1);
    }
    for (int i = 0; i < depth; i++){
        printf("\t");
    }
    printf("</%s%s%s>\n", blue, elP->tagName, white);
}



int main(){
    Element* e1 = elementConstructor("div", "class1");
    Element* e2 = elementConstructor("div", "class2");
    Element* e3 = elementConstructor("div", "class3");
    Element* e4 = elementConstructor("div", "class4");
    Element* e5 = elementConstructor("div", "class5");
    Element* e6 = elementConstructor("div", "class6");
    Element* e7 = elementConstructor("div", "class7");
    Element* e8 = elementConstructor("div", "class8");
    Element* e9 = elementConstructor("div", "class9");
    Element* e10 = elementConstructor("div", "class10");
    appendChild(e1, e2);
    appendChild(e2, e3);
    appendChild(e3, e4);
    appendChild(e4, e5);
    appendChild(e5, e6);
    appendChild(e6, e7);
    appendChild(e7, e8);
    appendChild(e8, e9);
    appendChild(e9, e10);

    displayElement(e1, 0);
    return 0;

}