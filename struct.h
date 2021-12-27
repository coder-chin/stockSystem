// ���нṹ����Ϣ 

#include <string>
using namespace std;
// ��Ʊ�ǵ����� 
typedef struct changeData {
	string stockCode;    //��Ʊ����
	string shortName;    //��Ʊ���� 
	string date;         //����
	string openingPrice; //���̼�
	string closingPrice; //���̼�
	double changePercent;//���Ƿ�
	struct changeData* next;
} changeData, *dataLink;
// ��Ʊ��Ϣ 
typedef struct {
	string stockCode;      //��Ʊ���� 
	string shortName;	   //��Ʊ��� 
	string cate1;          //һ������ 
	string cate2;		   //�������� 
	string date;      	   //�������� 
	string website;        //��ַ 
	string majorBusiness;  //��Ӫҵ�� 
	string businessScope;  //��Ӫ��Χ
	string recentInfo[3];  //���һ�տ��̼ۡ����̼ۺ͵��Ƿ�
	dataLink detail;       //��Ʊ�ǵ����ݣ���Ԫ���
	double score;          //����
	double maxChangePercent; //����ǵ���
	string maxDate;        //����ǵ�����Ӧ������ 
} StockInfo;
// ��ϣ�ڵ� 
typedef struct _hashNode {
	StockInfo node;
	struct _hashNode *next;
} hashNode, *hashList;
// �������ڵ� 
typedef struct TreeNode {
	StockInfo data;
	TreeNode *left;
	TreeNode *right;
} TNode, *BinTree;
// �߽ṹ
struct edge {
	int v, w;
};
// �߽ṹ������Ҫ�ڽӱ� 
struct Edge {
	int u, v, w;
};
// MST�еı��Լ����������ߵĵ㣬��������� 
struct fundPortfolio {
	int fund1;
	int fund2;
	int weight;
	double scoreSum;
};
struct score {
	string name;
	double score;
};
