#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap * map = (TreeMap *)malloc(sizeof(TreeMap));
  if(map == NULL)return NULL;
  map->root = NULL;
  map->current = NULL;
  map->lower_than = lower_than;
  return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if(tree == NULL)return;
  if(tree->root == NULL) //si el arbol esta vacio, el nuevonodo se convertira en la raiz
  {
    tree->root = createTreeNode(key,value);
    return;
  }
  TreeNode *currentAUX = tree->root; //nodo actual
  while(currentAUX != NULL)
    {
      if(is_equal(tree,key,currentAUX->pair->key))return; 
      //PARA INSERTAR A LA IZQUIERDA
      if(tree->lower_than(key,currentAUX->pair->key)) //si la clave es menor que el current, se va a la izq
      {
        if(currentAUX->left == NULL) //si no hay nodo a la izq se crea uno y se asigna como hijo
        {
          TreeNode *newNodo = createTreeNode(key,value);
          newNodo->parent = currentAUX;
          currentAUX->left = newNodo;
          tree->current = newNodo; //actualiza nodo
          return;
        }
        if(currentAUX->left != NULL)currentAUX = currentAUX->left;
      }//PA INSERTAR A LA DERECHA  
      if(tree->lower_than(currentAUX->pair->key,key))
      {
        if(currentAUX->right == NULL)
        {
          TreeNode *newNodo = createTreeNode(key,value);
          newNodo->parent = currentAUX;
          currentAUX->right = newNodo;
          tree->current = newNodo; //actualiza nodo
          return;
        }
        if(currentAUX->right != NULL) currentAUX = currentAUX->right; //si hay nodo derecho, avanza a la derecha
      }
    }
  

}

TreeNode * minimum(TreeNode * nodo){
    if(nodo == NULL)return NULL;
    while(nodo->left != NULL)
      {
        if(nodo->left == NULL)break;
        nodo = nodo->left;
      }
    return nodo;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  //caso 1: nodo sin hijos
  if(node->left == NULL && node->right == NULL)
  {
    if(node->parent == NULL)
      tree->root = NULL;
    else
    {
      if(node->parent->left == node)
        node->parent->left = NULL;
      else  
        node->parent->right = NULL;
    }
  }
  
  

}
//5.- Implemente la función void removeNode(TreeMap * tree, TreeNode* node). Esta función elimina el nodo node del árbol tree. Recuerde que para eliminar un node existen 3 casos: Nodo sin hijos: Se anula el puntero del padre que apuntaba al nodo Nodo con un hijo: El padre del nodo pasa a ser padre de su hijo Nodo con dos hijos: Descienda al hijo derecho y obtenga el menor nodo del subárbol (con la función minimum). Reemplace los datos (key,value) de node con los del nodo "minimum". Elimine el nodo minimum (para hacerlo puede usar la misma función removeNode).
void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current = tree->root;
  while(tree->current != NULL)
  {
    if(is_equal(tree, tree->current->pair->key, key)) 
      return tree->current->pair;
    if(tree->lower_than(key, tree->current->pair->key) == 1)
      tree->current = tree->current->left;//si es menor va a la izquierda
    else tree->current = tree->current->right; //sino va a la derecha
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
