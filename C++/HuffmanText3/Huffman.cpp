#include"Huffman.h"
int HuffmanTree(Huffmantree& pHT, int* w, int n) {
	//��ʼ��Huffman��
	for (int i = 0; i < n * 2; i++)
		pHT[i] = { 0,0,0,0 };
	for (int i = 0; i < n; i++) {
		pHT[i + 1].weight = w[i];
	}
	//�������Ŷ�����
	for (int i = n; i < n * 2; i++) {
		//�ҳ�����
		pHT[i + 1].lchild = Select(pHT, i);
		pHT[i + 1].weight += pHT[Select(pHT, i)].weight;
		pHT[Select(pHT, i)].parent = i + 1;
		//�ҳ��Һ���
		pHT[i + 1].rchild = Select(pHT, i);
		pHT[i + 1].weight += pHT[Select(pHT, i)].weight;
		pHT[Select(pHT, i)].parent = i + 1;
	}
	return 0;
}

int Select(Huffmantree pHT, int nSize) {
	int minValue = 0x7FFFFFFF; //��Сֵ
	int min = 0;//Ԫ�����

	//�ҵ���СȨֵ��Ԫ�����
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
	char cd[256] = { '\0' };//��¼����·��
	int cdlen = 0;// ��¼��ǰ·������
	for (int i = 1; i < 512; i++) {
		pHT[i].weight = 0;//����Huffman��ʱ�������ڵ��״̬���
	}
	int p = 511;//���ڵ�
	while (p != 0) {
		if (pHT[p].weight == 0) {//����
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0) {
				p = pHT[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (pHT[p].rchild == 0) //�Ǽ�Ҷ�ӽڵ���ַ��ı���
			{
				pHC[p] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(pHC[p], cd);//���Ʊ���
			}
		}
		else if (pHT[p].weight == 1) {//����
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0)//�ҽڵ�ΪҶ�ӽڵ�
			{
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else//�˻ظ��ڵ㣬���볤�ȼ�һ
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
	if (pHT[root].lchild)//��������
	{
		TestHuffmanCode(pHT[root].lchild, pHT, pHC);
	}
	if (pHT[root].rchild)//�����Һ���
	{
		TestHuffmanCode(pHT[root].rchild, pHT, pHC);
	}
}