#include "Huffman.h"
#include <iostream>
#include <string>
#include <vector>

void getcode(vector<pair<char, string>>* codeorder, string* tmp, Node* root)
{
    if (root->LeftChild == nullptr && root->RightChild == nullptr) //����Ҷ�ӽڵ�
    {
        pair<char, string> t;
        t.first = root->key;
        t.second = *tmp;
        codeorder->push_back(t);
        tmp->pop_back();
        return;
    }
    if (root->LeftChild)  //������������tmp+='0'
    {
        *tmp += "0";
        getcode(codeorder, tmp, root->LeftChild);
    }if (root->RightChild)  //������������tmp+='1'
    {
        *tmp += "1";
        getcode(codeorder, tmp, root->RightChild);
    }
    if (tmp->length())
        tmp->pop_back();//��㷵�ص�ʱ��һ��Ҫɾ������һ���ַ�
}
void StructuralCoding(vector<pair<char, string>>* codeorder, Node* root) //��������ı��뼯�Լ����������ĸ��ڵ�
{
    string tmp;
    getcode(codeorder, &tmp, root);
}