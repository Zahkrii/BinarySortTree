#include <iostream>
#include "binarySortTree.h"
#include "formatter.h"

using namespace std;

// ��������
void search(BST bst, BST newBST);
// ɾ������
void del(BST newBST);
// ת��Ϊ�ڽӱ�洢
void convertAdjGraph(BST bst);

int main()
{
    int dataCount;
    int maxData;
    BST bst;

    initialize();
    while (1)
    {
        cout << "���� Data Count: ";
        cin >> dataCount;
        if (dataCount < 10 || dataCount > 20)
        {
            cout << "Data Count ������ [10, 20] ֮�䣡" << endl;
        }
        else
            break;
    }
    while (1)
    {
        cout << "���� Max Data: ";
        cin >> maxData;
        if (maxData < 50 || maxData > 100)
        {
            cout << "Max Data ������ [50, 100] ֮�䣡" << endl;
        }
        else
            break;
    }

    breakLine();

    int *data = new int[dataCount];

    // ����������ݲ����
    generateData(data, dataCount, maxData);
    // ��ʼ������������
    initBinarySortTree(&bst, data, dataCount);

    sort(&bst, 'm');

    breakLine();

    //����������
    BST newBST = copyTree(&bst);
    cout << "�����������ɹ��������������" << endl;
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
                cout << "�����ظ�ת�����������ʷ��¼��" << endl;
                break;
            }
            flag = -1;
            convertAdjGraph(bst);
            break;
        case 'e':
            flag = 1;
            cout << "�����˳�..." << endl;
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

// ��������
void search(BST bst, BST newBST)
{
    char treeIndex;
    char *strKey = new char[4];
    node *result;
    while (1)
    {
        cout << "����ϣ�����ҵĶ�����( 1 �� 2 ): ";
        cin >> treeIndex;
        if (treeIndex != '1' && treeIndex != '2')
        {
            cout << "������ 1 �� 2 �����룡" << endl;
        }
        else
            break;
    }

    if (treeIndex == '1')
    {
        cout << "��Դ���������в��ң�����ϣ�����ҵ����ݣ�";
        cin >> strKey;
        result = searchNode((&bst)->root, atoi(strKey));
    }
    else if (treeIndex == '2')
    {
        cout << "�Զ������������в��ң�����ϣ�����ҵ����ݣ�";
        cin >> strKey;
        result = searchNode((&newBST)->root, atoi(strKey));
    }
    cout << "������..." << endl;
    if (result != NULL)
    {
        cout << "���ҳɹ����������ڵ�ַ��" << result << endl;
    }
    else
    {
        cout << "����ʧ�ܣ�δ�ҵ�������ݣ�" << endl;
    }
}

// ɾ������
void del(BST newBST)
{
    char *strKey = new char[4];

    cout << "���뽫Ҫ�Ӷ���������ɾ�������ݣ�";
    cin >> strKey;
    newBST = deleteNode(&newBST, atoi(strKey));
}

// ת��Ϊ�ڽӱ�洢
void convertAdjGraph(BST bst)
{
    adjGraph graph = convert((&bst)->root);
    showAdjGraph(graph);
    //sort(&bst, 'f');
    topologicalSort(graph);
}