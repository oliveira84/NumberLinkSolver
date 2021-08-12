#pragma once
#include "DLList.h"
#include "Node.h"
#include "HashTable.h"

class Search
{
    // lista de nodes para serem expandidas 
    DLList<Node*> open;
    // lista de nodes expandidas
    DLList<Node*> closed;
    // Para localizar duplicados de forma mais rapida, a chave � uma string, usar (node->toString).
    // IMPORTANTE: nao utilizar com DFS limitado, pode levar a que n�o se encontre uma solu��o.
    HashTable<Node*>* knownStates;

    int geracoes;
    int expancoes;
    bool withLoops;
    bool reconstructPath;
    int limit;    
    bool useHashTable;   
    Node* root;

public:
    Search(Node* root);
    void startSearch();
    ~Search();

    void updateNodeStatus(DLList<Node*>& successors, Node* parent);
    void printPath(Node* currentNode);
    void printStats(Node* node = nullptr);
    void initializeKnownStates(Node* rootCopy);

    bool dFS();
    bool bFS();

    void removeDuplicates(DLList<Node*>& successors);

    void clearLists();

};

