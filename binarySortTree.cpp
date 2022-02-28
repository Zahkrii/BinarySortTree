#include <iostream>
#include <cstdlib>
#include <ctime>
#include "binarySortTree.h"

using namespace std;

int visited[20];
int cnt;

node *tmpR[20];
int cntR;
node *tmpL[20];
int cntL;

arcNode *tmpGraph[11];

int tmp[20];
int cntTmp = 0;

// 生成随机数据并输出
void generateData(int *empty, int dataCount, int maxData)
{
    srand((unsigned)time(NULL));
    cout << "生成 [0, " << maxData << ") 范围内长度为 " << dataCount << " 的随机数列：" << endl;
    for (int i = 0; i < dataCount; i++)
    {
        *(empty + i) = rand() % maxData;
        cout << *(empty + i) << " ";
    }
    cout << endl;
}

// 初始化二叉排序树
void initBinarySortTree(BST *bst, int *data, int dataCount)
{
    bst->root = NULL;
    for (int i = 0; i < dataCount; i++)
    {
        insert(&(bst->root), *(data + i));
    }
    cout << "根据随机数列创建二叉排序树...成功" << endl;
}

// 插入二叉排序树元素
void insert(node **t, int value)
{
    if (*t == NULL)
    {
        *t = (node *)malloc(sizeof(node));
        (*t)->data = value;
        (*t)->lchild = NULL;
        (*t)->rchild = NULL;
    }
    else if (value < (*t)->data)
    {
        insert(&((*t)->lchild), value);
    }
    else if (value > (*t)->data)
    {
        insert(&((*t)->rchild), value);
    }
    // 数据相等的情况忽略，不生成节点
}

// 递归实现二叉排序树中序遍历
void sort_mid(node *t)
{
    if (NULL == t)
    {
        return;
    }
    else
    {
        sort_mid(t->lchild);
        cout << t->data << " ";
        sort_mid(t->rchild);
    }
}

// 递归实现二叉排序树前序遍历
void sort_front(node *t)
{
    if (NULL == t)
    {
        return;
    }
    else
    {
        cout << t->data << " ";
        sort_front(t->lchild);
        sort_front(t->rchild);
    }
}

// 选择遍历方法
void sort(BST *bst, char type)
{
    switch (type)
    {
    case 'm': // 中序遍历
        cout << "中序遍历结果：" << endl;
        sort_mid(bst->root);
        cout << endl;
        break;
    case 'f': // 前序遍历
        cout << "前序遍历结果：" << endl;
        sort_front(bst->root);
        cout << endl;
        break;

    default:
        break;
    }
}

// 实验二
// 拷贝二叉树节点
node *copyNode(node *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    node *newRoot = (node *)malloc(sizeof(node));

    newRoot->lchild = copyNode(root->lchild); //拷贝左子树
    newRoot->rchild = copyNode(root->rchild); //拷贝右子树
    newRoot->data = root->data;               //拷贝根节点数据
    return newRoot;
}

// 拷贝二叉树
BST copyTree(BST *bst)
{
    BST newTree;
    (&newTree)->root = copyNode(bst->root);
    return newTree;
}

// 递归查找节点
node *searchNode(node *t, int key)
{
    if (t == NULL || t->data == key)
    {
        return t;
    }
    else
    {
        if (key < t->data)
        {
            searchNode(t->lchild, key);
        }
        else
        {
            searchNode(t->rchild, key);
        }
    }
}

// 递归找最小值节点
node *findMin(node *t)
{
    node *tmp = t;
    if (tmp->lchild)
        return findMin(tmp->lchild);
    return tmp;
}

// 递归查找并删除节点
node *findAndDeleteNode(node *t, int key)
{
    node *tmp = NULL;
    if (!t) // 如果未找到，返回NULL
        return NULL;
    else if (key < t->data)
        t->lchild = findAndDeleteNode(t->lchild, key);
    else if (key > t->data)
        t->rchild = findAndDeleteNode(t->rchild, key);
    else // 如果找到待删除的节点
    {
        if (t->lchild && t->rchild) // 待删除的节点有两个子结点
        {
            tmp = findMin(t->rchild);
            t->data = tmp->data;
            t->rchild = findAndDeleteNode(t->rchild, t->data);
        }
        else // 待删除节点只有一个子节点或者没有子节点
        {
            if (!t->lchild) // 左节点为空，有右节点或者无子节点
                t = t->rchild;
            else if (!t->rchild) // 右节点为空，有左节点或者无子结点
                t = t->lchild;
        }
    }
    return t;
}

// 删除节点
BST deleteNode(BST *t, int key)
{
    node *tmp = searchNode(t->root, key);

    if (tmp == NULL)
    {
        cout << "未找到需要删除的节点！" << endl;
        return *t;
    }
    else
    {
        tmp = findAndDeleteNode(t->root, key);
        cout << "删除成功！中序遍历结果：" << endl;
        sort_mid(tmp);
        cout << endl;
        BST deleted;
        (&deleted)->root = tmp;
        return deleted;
    }
}

// 查找转换右子树
arcNode *convertR(node *t)
{
    if (!t)
    {
        return NULL;
    }
    else
    {
        if (t->lchild && !isVisited(t))
        {
            cntL++;
            tmpL[cntL] = t;
        }
        arcNode *arc = new arcNode;
        arc->adjvex = t->data;
        visited[cnt] = t->data;
        cnt++;
        arc->next = convertR(t->rchild);
        return arc;
    }
}

// 查找转换左子树
arcNode *convertL(node *t)
{
    if (!t)
    {
        return NULL;
    }
    else
    {
        if (t->rchild && !isVisited(t))
        {
            cntR++;
            tmpR[cntR] = t;
        }
        arcNode *arc = new arcNode;
        arc->adjvex = t->data;
        visited[cnt] = t->data;
        cnt++;
        arc->next = convertL(t->lchild);
        return arc;
    }
}

// 判断是否访问过该节点
int isVisited(node *t)
{
    for (int i = 0; i <= cnt; i++)
    {
        if (t->data == visited[i])
            return 1; // true
    }
    return 0; // false
}

// 转换转换二叉树为邻接表存储结构
adjGraph convert(node *t)
{
    int len = 1;
    cntL = -1;
    cntR = -1;
    cnt = 0;
    tmpGraph[0] = convertL(t);
    if (!tmpGraph[0])
        tmpGraph[0] = convertR(t);
    while (1)
    {
        if (cntR != -1)
        {
            while (cntR + 1)
            {
                tmpGraph[len] = convertR(tmpR[cntR]);
                len++;
                cntR--;
            }
        }
        if (cntL != -1)
        {
            while (cntL + 1)
            {
                tmpGraph[len] = convertL(tmpL[cntL]);
                len++;
                cntL--;
            }
        }
        if (cntL == -1 && cntR == -1)
            break;
    }

    adjGraph graph;
    int count = 0;
    int k = 0;
    int j = 0;
    for (j = 0; j < len; j++)
    {
        if (tmpGraph[j]->next == NULL)
        {
            count++;
            continue;
        }

        graph.nodes[k] = (arcNode *)malloc(sizeof(arcNode));
        graph.nodes[k]->adjvex = tmpGraph[j]->adjvex;
        graph.nodes[k]->next = tmpGraph[j]->next;
        k++;
    }
    graph.size = len - count;
    cout << "转换源二叉树为邻接表存储结构成功！" << endl;
    return graph;
}

// 显示邻接表节点
void showArcNode(arcNode *t)
{
    if (t == NULL)
        return;
    cout << t->adjvex << ' ';
    showArcNode(t->next);
}

// 显示邻接表
void showAdjGraph(adjGraph graph)
{
    cout << "转换结果如下：" << endl;
    for (int i = 0; i < graph.size; i++)
    {
        cout << graph.nodes[i]->adjvex << " -> ";
        showArcNode(graph.nodes[i]->next);
        cout << endl;
    }
}

// 拓扑排序节点
int sortNode(arcNode *t, int cnt)
{
    arcNode *p;
    p = t;
    int flag = 0;
    while (1)
    {
        for (int j = 0; j < cnt; j++)
        {
            if (tmp[j] == p->adjvex)
                flag = 1;
        }
        if (!flag)
        {
            cout << p->adjvex << " ";
            tmp[cnt] = p->adjvex;
            cnt++;
        }
        if (p->next != NULL)
            p = p->next;
        else
            break;
    }
    return cnt;
}

// 拓扑排序
void topologicalSort(adjGraph graph)
{
    int flag = 0;
    cntTmp = 0;
    cout << "拓扑排序结果：" << endl;
    for (int i = 0; i < graph.size; i++)
    {
        for (int j = 0; j < cntTmp; j++)
        {
            if (tmp[j] == graph.nodes[i]->adjvex)
                flag = 1;
        }
        if (!flag)
        {
            cout << graph.nodes[i]->adjvex << " ";
            tmp[cntTmp] = graph.nodes[i]->adjvex;
            cntTmp++;
        }
        cntTmp = sortNode(graph.nodes[i]->next, cntTmp);
    }
    cout << endl;
}