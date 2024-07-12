#include <stdio.h>
#include <stdlib.h>
#include "/Users/Shmuli/my-c-library/hashMap.c"

#define likely(x)  __builtin_expect(!!(x), 1)
#define unlikely(x)  __builtin_expect(!!(x), 0)
typedef struct graph graph;
typedef struct vertex vertex;

struct vertex{
    int id;
    char name[10];
    int connectedVertices[10];
    int connectedVerticesCount;
    int connectedVerticesMutex;
};

// directed graph
struct graph{
    vertex matrix[1000];
    int vertexCount;
    hashMap* userGraghLookupIds;
    int newVertexMutex;
};



int getNewVertexId(graph* g){
    g->newVertexMutex = 1;
    int id = g->vertexCount;
    g->vertexCount++;
    // the mutex only needs to be locked in order to reset the id, once the id is reseved the rest is up to this process
    g->newVertexMutex = 0;
    return id;
}

vertex* createVertex(int id, char name[10]){
    vertex* v = (vertex*)malloc(sizeof(vertex));
    v->id = id;
    strcpy(v->name, name);
    return v;
}

int addVertex(graph* g, char name[10]){
    while (unlikely(g->newVertexMutex == 1)){
        usleep(1000);
    }

    int id = getNewVertexId(g);

    g->matrix[id] = *createVertex(id, name);
    char charedId[5];
    sprintf(charedId, "%d", (id));
    hashMapSet(g->userGraghLookupIds, name, charedId);
    return id;
}


char* getVertexIdByName(graph* g, char name[10]){
    return hashMapGet(g->userGraghLookupIds, name);
}

void addconnectedVertex(graph* g, int vertexId, int connectedVertexId){
    while (unlikely(g->matrix[vertexId].connectedVerticesMutex == 1)){
        usleep(1000);
    }
    g->matrix[vertexId].connectedVerticesMutex = 1;

    g->matrix[vertexId].connectedVertices[g->matrix[vertexId].connectedVerticesCount] = connectedVertexId;
    g->matrix[vertexId].connectedVerticesCount++;

    g->matrix[vertexId].connectedVerticesMutex = 0;

}

graph* createGraph(){
    graph* g = (graph*)malloc(sizeof(graph));
    g->vertexCount = 0;
    g->newVertexMutex = 0;
    g->userGraghLookupIds = hashMapConstructor();
    return g;
}

vertex getVertexById(graph* g, int id){
    return g->matrix[id];
}

vertex** depthFirstSearch(graph* g, int startVertexId, int amount){
    int visited[amount];
    int visitedCount = 0;

    int que[amount];
    int queItemsUsed = 0;
    int queCount = 0;
    return NULL;
}



int main(){

    graph* g = createGraph();
    int shmulisId = addVertex(g, "jon");
    int berelId = addVertex(g, "bob");
    addconnectedVertex(g, shmulisId, berelId);
    addconnectedVertex(g, berelId, shmulisId);
    printf("%s\n", getVertexById(g, 0).name);
    printf("%s\n", getVertexIdByName(g, "jon"));
    return 0;
}
