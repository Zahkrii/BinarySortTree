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

// ����������ݲ����
void generateData(int *empty, int dataCount, int maxData)
{
    srand((unsigned)time(NULL));
    cout << "���� [0, " << maxData << ") ��Χ�ڳ���Ϊ " << dataCount << " ��������У�" << endl;
    for (int i = 0; i < dataCount; i++)
    {
        *(empty + i) = rand() % maxData;
        cout << *(empty + i) << " ";
    }
    cout << endl;
}

// ��ʼ������������
void initBinarySortTree(BST *bst, int *data, int dataCount)
{
    bst->root = NULL;
    for (int i = 0; i < dataCount; i++)
    {
        insert(&(bst->root), *(data + i));
    }
    cout << "����������д�������������...�ɹ�" << endl;
}

// �������������Ԫ��
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
    // ������ȵ�������ԣ������ɽڵ�
}

// �ݹ�ʵ�ֶ����������������
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

// �ݹ�ʵ�ֶ���������ǰ�����
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

// ѡ���������
void sort(BST *bst, char type)
{
    switch (type)
    {
    case 'm': // �������
        cout << "������������" << endl;
        sort_mid(bst->root);
        cout << endl;
        break;
    case 'f': // ǰ�����
        cout << "ǰ����������" << endl;
        sort_front(bst->root);
        cout << endl;
        break;

    default:
        break;
    }
}

// ʵ���
// �����������ڵ�
node *copyNode(node *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    node *newRoot = (node *)malloc(sizeof(node));

    newRoot->lchild = copyNode(root->lchild); //����������
    newRoot->rchild = copyNode(root->rchild); //����������
    newRoot->data = root->data;               //�������ڵ�����
    return newRoot;
}

// ����������
BST copyTree(BST *bst)
{
    BST newTree;
    (&newTree)->root = copyNode(bst->root);
    return newTree;
}

// �ݹ���ҽڵ�
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

// �ݹ�����Сֵ�ڵ�
node *findMin(node *t)
{
    node *tmp = t;
    if (tmp->lchild)
        return findMin(tmp->lchild);
    return tmp;
}

// �ݹ���Ҳ�ɾ���ڵ�
node *findAndDeleteNode(node *t, int key)
{
    node *tmp = NULL;
    if (!t) // ���δ�ҵ�������NULL
        return NULL;
    else if (key < t->data)
        t->lchild = findAndDeleteNode(t->lchild, key);
    else if (key > t->data)
        t->rchild = findAndDeleteNode(t->rchild, key);
    else // ����ҵ���ɾ���Ľڵ�
    {
        if (t->lchild && t->rchild) // ��ɾ���Ľڵ��������ӽ��
        {
            tmp = findMin(t->rchild);
            t->data = tmp->data;
            t->rchild = findAndDeleteNode(t->rchild, t->data);
        }
        else // ��ɾ���ڵ�ֻ��һ���ӽڵ����û���ӽڵ�
        {
            if (!t->lchild) // ��ڵ�Ϊ�գ����ҽڵ�������ӽڵ�
                t = t->rchild;
            else if (!t->rchild) // �ҽڵ�Ϊ�գ�����ڵ�������ӽ��
                t = t->lchild;
        }
    }
    return t;
}

// ɾ���ڵ�
BST deleteNode(BST *t, int key)
{
    node *tmp = searchNode(t->root, key);

    if (tmp == NULL)
    {
        cout << "δ�ҵ���Ҫɾ���Ľڵ㣡" << endl;
        return *t;
    }
    else
    {
        tmp = findAndDeleteNode(t->root, key);
        cout << "ɾ���ɹ���������������" << endl;
        sort_mid(tmp);
        cout << endl;
        BST deleted;
        (&deleted)->root = tmp;
        return deleted;
    }
}

// ����ת��������
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

// ����ת��������
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

// �ж��Ƿ���ʹ��ýڵ�
int isVisited(node *t)
{
    for (int i = 0; i <= cnt; i++)
    {
        if (t->data == visited[i])
            return 1; // true
    }
    return 0; // false
}

// ת��ת��������Ϊ�ڽӱ�洢�ṹ
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
    cout << "ת��Դ������Ϊ�ڽӱ�洢�ṹ�ɹ���" << endl;
    return graph;
}

// ��ʾ�ڽӱ�ڵ�
void showArcNode(arcNode *t)
{
    if (t == NULL)
        return;
    cout << t->adjvex << ' ';
    showArcNode(t->next);
}

// ��ʾ�ڽӱ�
void showAdjGraph(adjGraph graph)
{
    cout << "ת��������£�" << endl;
    for (int i = 0; i < graph.size; i++)
    {
        cout << graph.nodes[i]->adjvex << " -> ";
        showArcNode(graph.nodes[i]->next);
        cout << endl;
    }
}

// ��������ڵ�
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

// ��������
void topologicalSort(adjGraph graph)
{
    int flag = 0;
    cntTmp = 0;
    cout << "������������" << endl;
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