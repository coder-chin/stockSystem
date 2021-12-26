// ͷ�ļ�, �궨��, �������� 

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "struct.h"
using namespace std;

#define INF 0x3f3f3f3f
#define N 60
#define SIZE 200
#define HASHLENGTH 97

// ���ߺ��� 
int hashFun(string str);       //��ϣ����
double hashASL(vector<StockInfo>, vector<hashList>); //���ϣ��ASL 
double bstASL(BinTree, vector<StockInfo>); //�����������ASL 
bool kmp(string s, string t);  //KMP
string format(int number);     //��ʽ�����
bool cmp(const fundPortfolio t1, const fundPortfolio t2);         //�ȽϺ��� 
bool cmpByScores(const fundPortfolio t1, const fundPortfolio t2); //�ȽϺ��� 
int find(int x);               //find���� 

// �������
void showSearchMenu();                    //չʾ��ѯ���ܲ˵� 
void showAnalyseMenu();                   //չʾ�������ܲ˵� 

// ���幦��ʵ�� 
void readStockInfo();                     //���ļ���������Ϣ 
void createHashTable();                   //������ϣ��
void searchBaseInfo();                    //���ڹ�ϣ���� 
void searchWebsite();                     //����KMP������ַ
void searchByBST();	                      //���ڶ�����������ѯ
void createBST(BinTree&, vector<StockInfo>);                 //��������������
void insertBST(BinTree&, int, vector<StockInfo>);            //��������������ڵ� 
BinTree searchBST(BinTree T, string key,double&); //����ָ����Ʊ����
void searchByLinkList();                  //���ڵ�����Ĺ�Ʊ�۸���Ϣ��ѯ
dataLink getLinkByDate(string date);      //�������ڻ�ȡ����
void analyseByInsertSort();               //ͨ���������������з���
void sortByOpeningPrice(dataLink);        //ͨ�����̼����� 
void sortByClosingPrice(dataLink);        //���̼����� 
void sortByChangePercent(dataLink);       //�ǵ������� 
void analyseByQuickSort();                //ͨ�����Ž��з���
void quickSort(vector<StockInfo>&, int, int); //���� 
int partition(vector<StockInfo>& industry, int low, int high);
void analyseBySelectionSort();            //���ڼ�ѡ������Ĺ�Ʊ�۸����
void analyseByFloyd();                    //����Floyd�Ĺ�Ʊ����Լ���
void analyseByPrim();                     //����Prim��С�������Ĺ�Ʊ����ɸѡ
void analyseByBigraph();                  //���ڶ���ͼ�Ĺ�Ʊ����ɸѡ
void deleteBST(){}                        //���ڶ����������Ĺ�Ʊ������Ϣɾ��
void anylyseByKruskal();                  //����Kruskal��С�������Ĺ�Ʊ����ɸѡ
void MST();                               //��С������-����ķ��
int find(int x);                          //���鼯���� 
