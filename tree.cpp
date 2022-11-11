#include "tree.h"

Tree::Tree()
{
    head = nullptr;
}

Tree::~Tree(){
    if (head){
        delete head;
    }
}

treeNode *Tree::Head()
{
    return head;
}

void Tree::ReadFromFile(char *path){
    std::fstream file;
    file.open(path, std::ios_base::in);
    if (!file.is_open()){
        return;
    }
    int count_sheet;
    file >> count_sheet;
    for (int i = 0; i < count_sheet; i++){
        int id_node, value, n;
        file >> id_node >> value >> n;
        List<treeNode *> list;

        for (int j = 0; j < n; j++){
            int kid_id;
            file >> kid_id;
            treeNode *node = new treeNode;
            node->id = kid_id;
            node->value = -1;
            list.Append(node);
        }
        Add(id_node, value, list);
    }
    file.close();
}

void Tree::Add(int id, int value, List<treeNode *> list)
{ 
    if (head == nullptr){
        head = new treeNode;
        head->id = id;
        head->value = value;
        head->kids = list;
    }
    else{
        treeNode *node;
        node = NodeSearch(head, id);;
        if (!node){
            return;
        }
        node->value = value;
        node->kids = list;
    }
}

treeNode *Tree::NodeSearch(treeNode *node, int id)
{
    if (!node){
        return node;
    }

    if (node->id == id){
        return node;
    }

    else{
        Node<treeNode *> *list_node = node->kids.Head();
        while(list_node != nullptr){
            treeNode *supTreeNode = NodeSearch(list_node->value, id);
            if (supTreeNode){
                return supTreeNode;
            }
            list_node = list_node->next;
        }
        return nullptr;
    }
}

void Tree::PrintNode(treeNode *node, int column, int cur_column){        //Ищем строчку и выводим ее
    if (cur_column == column){
        std::cout << "(";
    }
    if (cur_column > column){
        std::cout << node->id << "[" << node->value << "]" << " ";
    }

    if (cur_column <= column){
        Node<treeNode *> *sup = node->kids.Head();
        while (sup != nullptr){
            PrintNode(sup->value, column, cur_column + 1);
            sup = sup->next;
        }
    }

    if (cur_column == column){
        std::cout << ")";
    }
}

void Tree::Print(treeNode *node){
    if (!node)
        return;

    std::cout << node->id << "[" << node->value << "]" << "\n";

    int height = SearcHeight(node, 1);

    for (int i = 1; i < height;  i++){
        PrintNode(node, i, 1);
        std::cout << "\n";
    }
}

int Tree::SearcHeight(treeNode *node, int height){
    if (node->kids.Empty()){
        return height;
    }

    int max_height = 0;

    Node<treeNode *> *sup = node->kids.Head();
    while (sup != nullptr){
        int h = SearcHeight(sup->value, height + 1);
        max_height = (max_height >= h) ? max_height : h;
        sup = sup->next;
    }

    return max_height;
}


/*
 * struct task_struct{
 *  treeNode* node;
 *  int num_kids;
 *  float devide;
 *  int sum;
 *  };
*/


task_struct Tree::MaxTree(treeNode *node){
    task_struct max = {nullptr, 0, 0, 0};

    if (node->kids.Empty()){
        return {node, 1, static_cast<float>(node->value), node->value};
    }

    Node<treeNode *> *sup_node = node->kids.Head();
    while (sup_node != nullptr){
        task_struct sup_max = MaxTree(sup_node->value);

        //Получае данные с нижний уровней дерева
        max.num_kids += sup_max.num_kids;
        max.sum += sup_max.sum;

        //Сравниваем каждые новые данные с нынешними
        if (sup_max.devide > max.devide && sup_max.num_kids != 1){
            max.node = sup_max.node;
            max.devide = sup_max.devide;
        }

        sup_node = sup_node->next;
    }

    //Прибавляем текущий нод в колличество
    max.num_kids++;

     //Прибавляем вес текущего нода в сумму весов
    max.sum += node->value;

    //Сравниваем новые данные с текущими
    if (max.devide < max.sum / max.num_kids){
        max.devide = max.sum / max.num_kids;
        max.node = node;
    }
    return max;
}

task_struct Tree::MinTree(treeNode *node){
    task_struct min = {nullptr, 0, 0, 0};

    if (node->kids.Empty()){
        return {node, 1, static_cast<float>(node->value), node->value};
    }

    Node<treeNode *> *sup_node = node->kids.Head();
    while (sup_node != nullptr){

        task_struct sup_min = MinTree(sup_node->value);

        //Получае данные с нижний уровней дерева
        min.num_kids += sup_min.num_kids;
        min.sum += sup_min.sum;

        //Сравниваем каждые новые данные с нынешними
        if ((sup_min.devide < min.devide || min.devide == 0) && sup_min.num_kids != 1){
            min.node = sup_min.node;
            min.devide = sup_min.devide;
        }

        sup_node = sup_node->next;
    }

    //Прибавляем текущий нод в колличество
    min.num_kids++;
    //Прибавляем вес текущего нода в сумму весов
    min.sum += node->value;

    //Сравниваем новые данные с текущими
    if (min.devide > min.sum / min.num_kids || min.devide == 0){
        min.devide = min.sum / min.num_kids;
        min.node = node;
    }
    return min;
}


