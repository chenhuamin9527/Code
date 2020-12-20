#include"Huffman.h"

Huffman::Huffman(int a[],int n)
{
    //ctor
    NodeSize=n;
    inital();
    for(int i=0;i<n;i++)
        tree[i].weight=a[i];
}

Huffman::~Huffman()
{
    //dtor
}
Node Huffman::getNode(int i)
{
    return tree[i];
}
void Huffman::inital()
{
    for(int i=0;i<NodeSize;i++)
    {
        tree[i].lchild=-1;
        tree[i].rchild=-1;
        tree[i].parent=-1;
    }
    for(int i=NodeSize;i<2*NodeSize-1;i++)//����������㣬�ȳ�ʼ���������������н��
    {
        tree[i].lchild=-2;
        tree[i].rchild=-2;
        tree[i].parent=-2;
    }
}
void Huffman::SelectMin(int& i1,int& i2)
{
    int a=-1,b;//�ȸ�a,bһ�������±�
    for(int i=0;i<2*NodeSize-1;i++)
    {
        if(tree[i].parent==-1)
        {
            if(a==-1)a=i;
            else{
                b=i;
                break;
            }
        }
    }
    //��a��ʾ�Ľ��Ȩֵ��С.
    if(tree[a].weight>tree[b].weight)swap(a,b);

    for(int i=0;i<2*NodeSize-1;i++)
    {
        if(tree[i].parent==-1&&i!=a&&i!=b)
        {
            if(tree[i].weight<tree[a].weight)
            {
                b=a;
                a=i;
            }
            else if(tree[i].weight<tree[b].weight)
            {
                b=i;
            }
        }
    }
    i1=a;i2=b;
}
void Huffman::HuffmanTree()
{
    int i1,i2;
    for(int k=NodeSize;k<2*NodeSize-1;k++)
    {
        SelectMin(i1,i2);
        tree[k].weight=tree[i1].weight+tree[i2].weight;
        tree[k].lchild=i1;
        tree[k].rchild=i2;
        tree[i1].parent=tree[i2].parent=k;
        tree[k].parent=-1;//������㣬����parent
    }
}
void Huffman::print()
{
    for(int i=0;i<2*NodeSize-1;i++)
    {
        cout<<tree[i].weight<<" "<<tree[i].parent<<" "<<tree[i].lchild<<" "<<tree[i].rchild;
        cout<<endl;
    }
}
string Huffman::getCode(int i)
{
    return code[i];
}
void Huffman::compile()
{
    HuffmanTree();

//    print();

    compile(tree[2*NodeSize-2],"",2*NodeSize-2);
//    for(int i=0;i<NodeSize;i++)
//        cout<<code[i];
}
void Huffman::compile(Node node,string s,int index)
{
    if(node.lchild==-1)
    {
        code[index]=s;
        return;
    }
    else
    {
        compile(tree[node.lchild],s+"0",node.lchild);
        compile(tree[node.rchild],s+"1",node.rchild);
    }
}
