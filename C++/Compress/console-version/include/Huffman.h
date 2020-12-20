#ifndef HUFFMAN_H
#define HUFFMAN_H

#include<iostream>
#include<cstring>
#include<string>
using namespace std;
const int MaxSize=512;
struct Node
{
    int weight;
    int lchild,rchild,parent;
};

class Huffman
{
    public:
        Huffman(int a[],int n);
        //��ӡ��������
        void print();
        //�ⲿ���ù���������
        void compile();
        //��ȡ������Ϣ
        string getCode(int i);
        Node getNode(int i);
        virtual ~Huffman();

    protected:

    private:
        //��ʼ����������
        void inital();
        //ѡȡȨֵ��С���
        void SelectMin(int &i1,int &i2);
        //������������
        void HuffmanTree();
        //����������
        void compile(Node node,string s,int index);
        Node tree[MaxSize];
        //Ҷ�ӽ����
        int NodeSize;
        //�����Ӧ����
        string code[MaxSize];
};

#endif // HUFFMAN_H
