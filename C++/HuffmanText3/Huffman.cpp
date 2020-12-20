#include"Huffman.h"
int HuffmanTree(Huffmantree& pHT, int* w, int n) {
	//初始化Huffman树
	for (int i = 0; i < n * 2; i++)
		pHT[i] = { 0,0,0,0 };
	for (int i = 0; i < n; i++) {
		pHT[i + 1].weight = w[i];
	}
	//生成最优二叉树
	for (int i = n; i < n * 2; i++) {
		//找出左孩子
		pHT[i + 1].lchild = Select(pHT, i);
		pHT[i + 1].weight += pHT[Select(pHT, i)].weight;
		pHT[Select(pHT, i)].parent = i + 1;
		//找出右孩子
		pHT[i + 1].rchild = Select(pHT, i);
		pHT[i + 1].weight += pHT[Select(pHT, i)].weight;
		pHT[Select(pHT, i)].parent = i + 1;
	}
	return 0;
}

int Select(Huffmantree pHT, int nSize) {
	int minValue = 0x7FFFFFFF; //最小值
	int min = 0;//元素序号

	//找到最小权值的元素序号
	for (int i = 1; i <= nSize; i++) {
		if (pHT[i].parent == 0 && pHT[i].weight < minValue) {
			minValue = pHT[i].weight;
			min = i;
		}
	}

	return min;
}

void TestHuffmanTree(Huffmantree pHT) {
	for (int i = 1; i < 512; i++) {
		printf("pHT[%d] \t %d \t %d \t %d \t %d \n", i, pHT[i].weight, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
	}
}

int HuffmanCoding(HuffmanCode& pHC, Huffmantree& pHT) {
	char cd[256] = { '\0' };//记录访问路径
	int cdlen = 0;// 记录当前路径长度
	for (int i = 1; i < 512; i++) {
		pHT[i].weight = 0;//遍历Huffman树时用来作节点的状态标记
	}
	int p = 511;//根节点
	while (p != 0) {
		if (pHT[p].weight == 0) {//向左
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0) {
				p = pHT[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (pHT[p].rchild == 0) //登记叶子节点的字符的编码
			{
				pHC[p] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(pHC[p], cd);//复制编码
			}
		}
		else if (pHT[p].weight == 1) {//向右
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0)//右节点为叶子节点
			{
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else//退回父节点，编码长度减一
		{
			pHT[p].weight = 0;
			p = pHT[p].parent;
			--cdlen;
		}
	}
	return 0;
}

void TestHuffmanCode(int root, Huffmantree pHT, HuffmanCode pHC) {
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0) {
		printf("0x%02X %s\n", root - 1, pHC[root]);
	}
	if (pHT[root].lchild)//访问左孩子
	{
		TestHuffmanCode(pHT[root].lchild, pHT, pHC);
	}
	if (pHT[root].rchild)//访问右孩子
	{
		TestHuffmanCode(pHT[root].rchild, pHT, pHC);
	}
}