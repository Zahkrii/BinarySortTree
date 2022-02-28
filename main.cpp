#include <iostream>
#include "binarySortTree.h"
#include "formatter.h"

using namespace std;

// 查找数据
void search(BST bst, BST newBST);
// 删除数据
void del(BST newBST);
// 转换为邻接表存储
void convertAdjGraph(BST bst);

int main()
{
    int dataCount;
    int maxData;
    BST bst;

    initialize();
    while (1)
    {
        cout << "输入 Data Count: ";
        cin >> dataCount;
        if (dataCount < 10 || dataCount > 20)
        {
            cout << "Data Count 必须在 [10, 20] 之间！" << endl;
        }
        else
            break;
    }
    while (1)
    {
        cout << "输入 Max Data: ";
        cin >> maxData;
        if (maxData < 50 || maxData > 100)
        {
            cout << "Max Data 必须在 [50, 100] 之间！" << endl;
        }
        else
            break;
    }

    breakLine();

    int *data = new int[dataCount];

    // 生成随机数据并输出
    generateData(data, dataCount, maxData);
    // 初始化二叉排序树
    initBinarySortTree(&bst, data, dataCount);

    sort(&bst, 'm');

    breakLine();

    //拷贝二叉树
    BST newBST = copyTree(&bst);
    cout << "拷贝二叉树成功，进行中序遍历" << endl;
    sort(&newBST, 'm');

    int flag = 0;
    while (1)
    {
        showMenu();
        char key;
        cin >> key;
        breakLine();
        switch (key)
        {
        case 's':
            search(bst, newBST);
            break;
        case 'd':
            del(newBST);
            break;
        case 'c':
            if (flag == -1)
            {
                cout << "不能重复转换，请查阅历史记录！" << endl;
                break;
            }
            flag = -1;
            convertAdjGraph(bst);
            break;
        case 'e':
            flag = 1;
            cout << "程序退出..." << endl;
            break;
        default:
            break;
        }
        if (flag == 1)
            break;
    }
    breakLine();
    system("pause");
    return 0;
}

// 查找数据
void search(BST bst, BST newBST)
{
    char treeIndex;
    char *strKey = new char[4];
    node *result;
    while (1)
    {
        cout << "输入希望查找的二叉树( 1 或 2 ): ";
        cin >> treeIndex;
        if (treeIndex != '1' && treeIndex != '2')
        {
            cout << "仅接受 1 或 2 的输入！" << endl;
        }
        else
            break;
    }

    if (treeIndex == '1')
    {
        cout << "对源二叉树进行查找，输入希望查找的数据：";
        cin >> strKey;
        result = searchNode((&bst)->root, atoi(strKey));
    }
    else if (treeIndex == '2')
    {
        cout << "对二叉树副本进行查找，输入希望查找的数据：";
        cin >> strKey;
        result = searchNode((&newBST)->root, atoi(strKey));
    }
    cout << "搜索中..." << endl;
    if (result != NULL)
    {
        cout << "查找成功，数据所在地址：" << result << endl;
    }
    else
    {
        cout << "查找失败，未找到相符数据！" << endl;
    }
}

// 删除数据
void del(BST newBST)
{
    char *strKey = new char[4];

    cout << "输入将要从二叉树副本删除的数据：";
    cin >> strKey;
    newBST = deleteNode(&newBST, atoi(strKey));
}

// 转换为邻接表存储
void convertAdjGraph(BST bst)
{
    adjGraph graph = convert((&bst)->root);
    showAdjGraph(graph);
    //sort(&bst, 'f');
    topologicalSort(graph);
}