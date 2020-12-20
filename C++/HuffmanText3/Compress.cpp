#include"Compress.h"
#include"Huffman.h"

int Compress(const char* pFilename) {
	int weight[256] = { 0 };
	FILE* in = fopen(pFilename, "rb");
	int ch;
	while ((ch = getc(in)) != EOF) {
		weight[ch]++;
	}
	fclose(in);

	HTNode* pHT = (HTNode*)malloc(512 * sizeof(HTNode));
	HuffmanCode pHC = (char**)malloc(257 * sizeof(char*));
	HuffmanTree(pHT, weight, 256);
	HuffmanCoding(pHC, pHT);

	//���㻺������С
	int nSize = 0;
	for (int i = 0; i < 256; i++) {
		nSize += weight[i] * strlen(pHC[i + 1]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;

	//��Դ�ļ����б���ѹ��
	char* pBuffer = NULL;
	Encode(pFilename, pHC, pBuffer, nSize);
	return 0;
}

int Str2byte(const char* pBinStr) {
	char b = 0x00;
	for (int i = 0; i < 8; i++) {
		b = b << 1;
		if (pBinStr[i] == '1') {
			b = b | 0x01;
		}
	}
	return b;
}

int strlen2(char* x) {
	int i = 0;
	while (x[i] == '0' || x[i] == '1') {
		i++;
	}
	return i;
}

int Encode(const char* pFilename, const HuffmanCode pHC, char* pBuffer, const int nSize) {
	//���ٻ�����
	FILE* in = fopen(pFilename, "rb");
	pBuffer = (char*)malloc(nSize * sizeof(char));
	if (!pBuffer) {
		cerr << "���ٻ�����ʧ��" << endl;
		return 0;
	}
	char cd[SIZE] = { 0 };//������
	int pos = 0;//������ָ��
	int ch;
	//ɨ���ļ�������Huffman�����������ѹ����ѹ������ݴ浽��������
	while ((ch = fgetc(in)) != EOF)
	{
		strcat(cd, pHC[ch + 1]);

		//ѹ������
		while (strlen2(cd) >= 8) {
			//��ȡ�ַ�����ߵ�8���ַ���������ֽ�
			pBuffer[pos++] = Str2byte(cd);
			//�ַ�����������
			for (int i = 0; i < SIZE - 8; i++) {
				cd[i] = cd[8 + i];
			}

		}
	}
	if (strlen(cd) > 0) {
		pBuffer[pos++] = Str2byte(cd);
	}
	fclose(in);
	HEAD sHead;
	InitHead(pFilename, sHead);
	WriteFile(pFilename, sHead, pBuffer, nSize);
}

int InitHead(const char* pFilename, HEAD& sHead) {
	//��ʼ���ļ�ͷ
	strcpy(sHead.type, "HUF");//�ļ�����
	sHead.length = 0;//Դ�ļ�����
	for (int i = 0; i < SIZE; i++) {
		sHead.weight[i] = 0;//Ȩֵ
	}
	//�Զ���������ʽ���ļ�
	FILE* in = fopen(pFilename, "rb");
	int ch;
	while ((ch = getc(in)) != EOF) {
		sHead.weight[ch]++;
		sHead.length++;
	}
	fclose(in);
	in = NULL;
	return 0;
}

int WriteFile(const char* pFilename, const HEAD sHead, const BUFFER pBuffer, const int nSize) {
	//�����ļ���
	char filename[SIZE] = { 0 };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");

	//�Զ���������ʽ���ļ�
	FILE* out = fopen(filename, "wb");

	//д�ļ�ͷ
	fwrite(&sHead, sizeof(HEAD), 1, out);

	//дѹ����ı���
	fwrite(pBuffer, sizeof(char), nSize, out);

	//�ر��ļ����ͷ��ļ�ָ��
	fclose(out);
	out = NULL;
	cout << sHead.length << " �ֽ�" << endl;
	cout << "����ѹ���ļ��� " << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	cout << len << " �ֽ�" << endl;
	cout << "ѹ�����ʣ� " << len * 1.0 / (sHead.length * 1.0) * 100 << "%" << endl;
	return len;
}

