#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "/Users/Shmuli/my-c-library/linkedList.c"
#include <unistd.h>



typedef struct hashMap hashMap;
#define likely(x)  __builtin_expect(!!(x), 1)
#define unlikely(x)  __builtin_expect(!!(x), 0)
#define hashMapListSize 100


struct hashMap{
    linkedList* list_of_chains[hashMapListSize];
};



void* pointers[1000];
volatile int pointerCount = 0;
volatile int pointerListMutex = 0;

hashMap* hashMapConstructor(){
    hashMap* hmp = (hashMap*)malloc(sizeof(hashMap));
    while (likely(pointerListMutex)){
        usleep(1000);
    };
    pointerListMutex = 1;
    pointers[pointerCount] = hmp;
    pointerCount++;
    pointerListMutex = 0;
    assert(hmp);
    for (int i = 0; i < hashMapListSize; i++){
        hmp->list_of_chains[i] = NULL;
    }
    return hmp;
}


int hash(const char charPointer[]){
    int val = 0;
    for (int index = 0; charPointer[index] != '\0'; index++){
        val += (int)charPointer[index];
    }
    return val;
}


void hashMapSet(hashMap* hm, char key[10], char value[10]){
    unsigned int moddedHashValue = hash(key)%hashMapListSize;
    if (hm->list_of_chains[moddedHashValue] == NULL){
        hm->list_of_chains[moddedHashValue] = linkedListConstructor(key, value);
        return;
    }
    // the unlikely lets the cpu start preparing to handle the common case where the mutex is turned off
    while (unlikely(hm->list_of_chains[moddedHashValue]->mutex)){
        usleep(1000);
    }
    hm->list_of_chains[moddedHashValue]->mutex = 1;
    linkedListSet(hm->list_of_chains[moddedHashValue], key, value);
    hm->list_of_chains[moddedHashValue]->mutex = 0;
}


char* hashMapGet(hashMap* hm, char key[10]){
    unsigned int moddedHashValue = hash(key)%hashMapListSize;
    if (hm->list_of_chains[moddedHashValue] == NULL) return NULL;
    while (hm->list_of_chains[moddedHashValue]->mutex){
        usleep(1000);
    }
    return linkedListGet(hm->list_of_chains[moddedHashValue], key);
}



void hashMapMemClear(){
    linkedListMemClear();
    for (int i = 0; i < pointerCount; i++){
        free(pointers[i]);
    }
}


void hashMapSampleCode(){
    hashMap* hmp = hashMapConstructor();
    hashMapSet(hmp, "name", "shmuli");
    hashMapSet(hmp, "key2", "value2");
    hashMapSet(hmp, "key3", "value3");
    printf("%s\n", hashMapGet(hmp, "name"));
    printf("%s\n", hashMapGet(hmp, "key2"));
}
