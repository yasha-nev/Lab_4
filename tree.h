#ifndef TREE_H
#define TREE_H

#include <fstream>
#include "list.h"

struct treeNode{
  int id;
  float value;
  List<treeNode *> kids;
  treeNode *parent;
};

struct task_struct{
  treeNode* node;
  float num_kids;
  float devide;
  float sum;
};

class Tree
{
public:
    Tree();
    ~Tree();
    treeNode *Head();
    void ReadFromFile(char *argv);
    void Add(int id, int value, List<treeNode *> list);
    void Print(treeNode *node);
    task_struct MaxTree(treeNode *node);
    task_struct MinTree(treeNode *node);

private:
    treeNode *head;
    treeNode *NodeSearch(treeNode *node, int id);
    void DeleteNode(treeNode *node);
    void PrintNode(treeNode *node, int column, int count);
    int SearcHeight(treeNode *node, int height);
};

#endif // TREE_H
