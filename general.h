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

vector<StockInfo> stocks(200);           //�洢200֧��Ʊ�Ļ�����Ϣ�;����Ʊ��Ϣ
vector<vector<edge>> e;                  //�ڽӱ� 
vector<int> d;                           //�ⲿ�㵽�ڲ������̾��� 
vector<int> vis;                         //�������
vector<vector<int>> graph(N+1, vector<int>(N+1, 0)); //60ֻ��Ʊ�ڽӾ��� 
vector<fundPortfolio> ret;               //��С���������еĻ������
vector<score> scores;                    //���ֺ�����
vector<int> p;                           //���鼯���� 
vector<int> G[SIZE];                     //ͼ
int color[SIZE];                         //����i����ɫ 1 �� -1

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
void deleteBSTNode();                     //ɾ�������������ڵ㹦�����
BinTree deleteBST(BinTree& BST, string str, BinTree& ret); //ɾ���ڵ� 
BinTree FindMin(BinTree BST);              //Ѱ����Сֵ
void printResult(BinTree);             //��ӡ�½ڵ㣬���ҽڵ���Ϣ
void showBestStocks(vector<int> arr1, vector<int> arr2); //չʾ����ͼ��ѹ�Ʊ��� 
bool solve(vector<int> v);             //����ͼ 
