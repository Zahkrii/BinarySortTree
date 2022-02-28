#ifndef BINARYSORTTREE_H
#define BINARYSORTTREE_H

// 二叉链表的节点
typedef struct BSTNode
{
    int data;                        // 数据域
    struct BSTNode *lchild, *rchild; // 左右指针域
} node;

// 存储二叉排序树根节点
typedef struct BST
{
    node *root; // 二叉排序树根节点指针
} BST;

// 邻接表节点
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *next;
} arcNode;

// 邻接表
typedef struct AdjGraph
{
    arcNode *nodes[11];
    int size; // 头节点个数
} adjGraph;

// 生成随机数据并输出
extern void generateData(int *empty, int dataCount, int MaxData);
// 初始化二叉排序树
extern void initBinarySortTree(BST *bst, int *data, int dataCount);
// 插入二叉排序树元素
extern void insert(node **t, int value);
// 递归实现二叉排序树中序遍历
extern void sort_mid(node *t);
// 选择遍历方法
extern void sort(BST *bst, char type);

// 实验二
// 拷贝二叉树节点
extern node *copyNode(node *root);
// 拷贝二叉树
extern BST copyTree(BST *bst);
// 递归查找节点
extern node *searchNode(node *t, int key);
// 递归找最小值节点
extern node *findMin(node *t);
// 递归查找并删除节点
extern node *findAndDeleteNode(node *t, int key);
// 删除节点
extern BST deleteNode(BST *t, int key);

// 查找转换右子树
extern arcNode *convertR(node *t);
// 查找转换左子树
extern arcNode *convertL(node *t);
// 转换转换二叉树为邻接表存储结构
extern adjGraph convert(node *t);
// 判断是否访问过该节点
extern int isVisited(node *t);

// 显示邻接表节点
extern void showArcNode(arcNode *t);
// 显示邻接表
extern void showAdjGraph(adjGraph graph);
// 拓扑排序节点
extern int sortNode(arcNode *t, int cnt);
// 拓扑排序
extern void topologicalSort(adjGraph graph);

#endif