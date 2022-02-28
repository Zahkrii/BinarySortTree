#ifndef BINARYSORTTREE_H
#define BINARYSORTTREE_H

// ��������Ľڵ�
typedef struct BSTNode
{
    int data;                        // ������
    struct BSTNode *lchild, *rchild; // ����ָ����
} node;

// �洢�������������ڵ�
typedef struct BST
{
    node *root; // �������������ڵ�ָ��
} BST;

// �ڽӱ�ڵ�
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *next;
} arcNode;

// �ڽӱ�
typedef struct AdjGraph
{
    arcNode *nodes[11];
    int size; // ͷ�ڵ����
} adjGraph;

// ����������ݲ����
extern void generateData(int *empty, int dataCount, int MaxData);
// ��ʼ������������
extern void initBinarySortTree(BST *bst, int *data, int dataCount);
// �������������Ԫ��
extern void insert(node **t, int value);
// �ݹ�ʵ�ֶ����������������
extern void sort_mid(node *t);
// ѡ���������
extern void sort(BST *bst, char type);

// ʵ���
// �����������ڵ�
extern node *copyNode(node *root);
// ����������
extern BST copyTree(BST *bst);
// �ݹ���ҽڵ�
extern node *searchNode(node *t, int key);
// �ݹ�����Сֵ�ڵ�
extern node *findMin(node *t);
// �ݹ���Ҳ�ɾ���ڵ�
extern node *findAndDeleteNode(node *t, int key);
// ɾ���ڵ�
extern BST deleteNode(BST *t, int key);

// ����ת��������
extern arcNode *convertR(node *t);
// ����ת��������
extern arcNode *convertL(node *t);
// ת��ת��������Ϊ�ڽӱ�洢�ṹ
extern adjGraph convert(node *t);
// �ж��Ƿ���ʹ��ýڵ�
extern int isVisited(node *t);

// ��ʾ�ڽӱ�ڵ�
extern void showArcNode(arcNode *t);
// ��ʾ�ڽӱ�
extern void showAdjGraph(adjGraph graph);
// ��������ڵ�
extern int sortNode(arcNode *t, int cnt);
// ��������
extern void topologicalSort(adjGraph graph);

#endif