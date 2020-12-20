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

	//计算缓冲区大小
	int nSize = 0;
	for (int i = 0; i < 256; i++) {
		nSize += weight[i] * strlen(pHC[i + 1]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;

	//对源文件进行编码压缩
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
	//开辟缓冲区
	FILE* in = fopen(pFilename, "rb");
	pBuffer = (char*)malloc(nSize * sizeof(char));
	if (!pBuffer) {
		cerr << "开辟缓冲区失败" << endl;
		return 0;
	}
	char cd[SIZE] = { 0 };//工作区
	int pos = 0;//缓冲区指针
	int ch;
	//扫描文件，根据Huffman编码表对其进行压缩，压缩结果暂存到缓冲区中
	while ((ch = fgetc(in)) != EOF)
	{
		strcat(cd, pHC[ch + 1]);

		//压缩编码
		while (strlen2(cd) >= 8) {
			//截取字符串左边的8个字符，编码成字节
			pBuffer[pos++] = Str2byte(cd);
			//字符串整体左移
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
	//初始化文件头
	strcpy(sHead.type, "HUF");//文件类型
	sHead.length = 0;//源文件长度
	for (int i = 0; i < SIZE; i++) {
		sHead.weight[i] = 0;//权值
	}
	//以二进制流形式打开文件
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
	//生成文件名
	char filename[SIZE] = { 0 };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");

	//以二进制流形式打开文件
	FILE* out = fopen(filename, "wb");

	//写文件头
	fwrite(&sHead, sizeof(HEAD), 1, out);

	//写压缩后的编码
	fwrite(pBuffer, sizeof(char), nSize, out);

	//关闭文件，释放文件指针
	fclose(out);
	out = NULL;
	cout << sHead.length << " 字节" << endl;
	cout << "生成压缩文件： " << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	cout << len << " 字节" << endl;
	cout << "压缩比率： " << len * 1.0 / (sHead.length * 1.0) * 100 << "%" << endl;
	return len;
}

