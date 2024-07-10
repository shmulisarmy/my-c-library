#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>



typedef struct linkedList linkedList;




struct linkedList{
    char key[10];
    char value[10];
    linkedList* next;
    int mutex;
};

linkedList* linkedListPointers[1000];
int linkedListPointerCount = 0;


linkedList* linkedListConstructor(const char firstKey[10], const char firstValue[10]){
    linkedList* newLlp = (linkedList*)malloc(sizeof(linkedList));
    linkedListPointers[linkedListPointerCount] = newLlp;
    linkedListPointerCount++;
    assert(newLlp);
    newLlp->next = NULL;
    strcpy(newLlp->key, firstKey);
    strcpy(newLlp->value, firstValue);
    return newLlp;
}



void linkedListSet(linkedList* llp, const char key[10], const char value[10]){
    if (strlen(key) > 10) return;
    if (strlen(value) > 10) return;
    linkedList* lastParent = linkedListConstructor(key, value);
    while (llp){
        if (strcmp(llp->key, key) == 0){
            strcpy(llp->value, value);
            return;
        }
        lastParent = llp;
        llp = llp->next;
    }
    lastParent->next = linkedListConstructor(key, value);
}


char* linkedListGet(linkedList* llp, const char key[10]){
    // mallitios user might use the comparision to get other info too
    if (strlen(key) > 10) return NULL;
    while (llp){
        if (strcmp(llp->key, key) == 0){
            return llp->value;
        }
        llp = llp->next;
    }
    return NULL;

}




void linkedListMemClear(){
    for (int i = 0; i < linkedListPointerCount; i++){
        free(linkedListPointers[i]);
    }
}


void linkedListSampleCode(){
    linkedList* llp = linkedListConstructor("name", "shmuli");
    linkedListSet(llp, "last", "keller");
    printf("name: %s\n", linkedListGet(llp, "name"));
    printf("last: %s\n", linkedListGet(llp, "last"));
}
