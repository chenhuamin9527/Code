#include "Huffman.h"
#include <iostream>
#include <string>
#include <vector>

void getcode(vector<pair<char, string>>* codeorder, string* tmp, Node* root)
{
    if (root->LeftChild == nullptr && root->RightChild == nullptr) //遇到叶子节点
    {
        pair<char, string> t;
        t.first = root->key;
        t.second = *tmp;
        codeorder->push_back(t);
        tmp->pop_back();
        return;
    }
    if (root->LeftChild)  //若左子树，则tmp+='0'
    {
        *tmp += "0";
        getcode(codeorder, tmp, root->LeftChild);
    }if (root->RightChild)  //若右子树，则tmp+='1'
    {
        *tmp += "1";
        getcode(codeorder, tmp, root->RightChild);
    }
    if (tmp->length())
        tmp->pop_back();//逐层返回的时候一定要删掉最后的一个字符
}
void StructuralCoding(vector<pair<char, string>>* codeorder, Node* root) //传入待填充的编码集以及哈弗曼树的根节点
{
    string tmp;
    getcode(codeorder, &tmp, root);
}