#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// ��Ʊ�ǵ����� 
typedef struct changeData {
	string stockCode;    //��Ʊ����
	string shortName;    //��Ʊ���� 
	string date;         //����
	string openingPrice; //���̼�
	string closingPrice; //���̼�
	string highestPrice; //��߼�
	string lowestPrice;  //��ͼ�
	string volume;       //�ɽ���
	string turnover;     //�ɽ����
	string turnoverRate; //������
	string FZDE; 		 //���Ƕ� 
	double changePercent;//���Ƿ�
	struct changeData* next;
} changeData, *dataLink;
// ��Ʊ 
typedef struct {
	string stockCode;      //��Ʊ���� 
	string shortName;	   //��Ʊ��� 
	string industryCode;   //��ҵ���� 
	string cate1;          //һ������ 
	string cate2;		   //�������� 
	string exchange;       //���н�����
	string fullName;	   //��˾ȫ�� 
	string date;      	   //�������� 
	string province;       //ʡ�� 
	string city;           //���� 
	string legalPerson;    //���� 
	string location;       //��ַ 
	string website;        //��ַ 
	string email;          //���� 
	string phone;          //�绰 
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

vector<hashList> hashTable(97);  //�����ϣ��
StockInfo stocks[200];   //�洢200֧��Ʊ�Ļ�����Ϣ�;����Ʊ��Ϣ 

// ���ߺ��� 
int hashFun(string str);       //��ϣ����
bool kmp(string s, string t);  //KMP
string format(int number);     //��ʽ����� 

// ������� 
void readStockBaseInfo(); //���ļ����浽������ 
void createHashTable();   //������ϣ��
void searchBaseInfo();   //���ڹ�ϣ���� 
void searchWebsite();    //����KMP������ַ
void searchByBST();	     //���ڶ�����������ѯ
void createBST(BinTree&); //��������������
void insertBST(BinTree&, int); //��������������ڵ� 
BinTree searchBST(BinTree T, string key); //����ָ����Ʊ����
void searchByLinkList();   //���ڵ�����Ĺ�Ʊ�۸���Ϣ��ѯ
dataLink getLinkByDate(string date); //�������ڻ�ȡ����
void analyseByInsertSort(); //ͨ���������������з���
void sortByOpeningPrice(dataLink); //ͨ�����̼����� 
void sortByClosingPrice(dataLink); //���̼����� 
void sortByChangePercent(dataLink); //�ǵ������� 
void analyseByQuickSort(); //ͨ�����Ž��з���
void quickSort(vector<StockInfo>&, int, int); //���� 
int partition(vector<StockInfo>& industry, int low, int high);
void analyseBySelectionSort();  //���ڼ�ѡ������Ĺ�Ʊ�۸����

int main()
{
	readStockBaseInfo();   //���ļ����������� 
	int choice;

	while(true) {
		cout << "=====================================================" << endl;
		cout << "=====   ��ӭʹ�ù�Ʊ��ѯ�����ϵͳ V1.0        =====" << endl;
		cout << "=====      ��������Ҫִ�еĲ���                =====" << endl;
		cout << "=====    1. ���ڹ�ϣ��Ĺ�Ʊ������Ϣ��ѯ       =====" << endl;
		cout << "=====    2. ����KMP�Ĺ�Ʊ��ַ��ѯ              =====" << endl;
		cout << "=====    3. ���ڶ����������Ĺ�Ʊ������Ϣ��ѯ   =====" << endl;
		cout << "=====    4. ���ڵ�����Ĺ�Ʊ�۸���Ϣ��ѯ       =====" << endl;
		cout << "=====    5. ����ֱ�Ӳ�������Ĺ�Ʊ�۸����     =====" << endl;
		cout << "=====    6. ���ڿ�������Ĺ�Ʊ�۸����         =====" << endl;
		cout << "=====    7. ���ڼ�ѡ������Ĺ�Ʊ�۸����     =====" << endl;
		cout << "=====    8. ����Floyd�Ĺ�Ʊ����Լ���          =====" << endl;
		cout << "=====    9. ����Prim��С�������Ĺ�Ʊ����ɸѡ   =====" << endl;
		cout << "=====    10.���ڶ���ͼ�Ĺ�Ʊ����ɸѡ           =====" << endl;
		cout << "=====    11.����Kruskal��С�������Ĺ�Ʊ����ɸѡ=====" << endl;
		cout << "=====    12.���ڶ����������Ĺ�Ʊ������Ϣɾ��   =====" << endl;
		cout << "====================================================" << endl;
		
		cout << "��������Ҫ���еĲ���: ";
		cin >> choice;
		switch(choice) {
			case 1:
				searchBaseInfo();
				break;
			case 2:
				searchWebsite();
				break;
			case 3:
				searchByBST();
				break;
			case 4:
				searchByLinkList();
				break;
			case 5:
				analyseByInsertSort();
				break;
			case 6:
				analyseByQuickSort();
				break;
			case 7:
				analyseBySelectionSort();
				break;
			case 8:
				 
		}
	}
	return 0;
}
// ��ϣ���� 
int hashFun(string str) {
	int length = str.length();
	int sum = 0;
	
	for(int i = 0; i < length; i++) {
		sum += str[i];
	}
	
	return sum % 97;
}
// �����ַ�������� 
int encode(string str) {
	int length = str.length();
	int sum = 0;
	
	for(int i = 0; i < length; i++) {
		sum += str[i];
	}
	
	return sum;
}
// KMP
bool kmp(string s, string t) {
	int m = t.length();
        int n = s.length();
        s = '0' + s;
        t = '0' + t;

        vector<int> next(m+1, 0);
        next[0] = -1;  //��ʼnext[0]==-1  next[1] = 0

        int j = 2, i = next[1];   //j���α꣬���������ƶ�  i�ǳ���Ϊj���ַ���ƥ��ǰ��ƥ�����󳤶� ʼ�յ���next[j]

        while(j <= m) {
            while(i!=-1 && t[i+1]!=t[j])  i = next[i];  //ƥ�䲻����һֱ����, ֱ��iΪ0

            if(i==-1) i = 0, j++;  //i���˵�0�Ļ���i=next[0]=-1, iҪ�ָ���0��j��������ɨ��

            else {    //next[j] = t[i+1]
                next[j] = i+1;
                i = next[j];
                j++;
            }
        }

        i = 1, j = 1;

        while(i<=n && j<=m) {
            while(j>=1 && t[j]!=s[i])  j = next[j-1]+1;  //��ƥ��Ļ��Ӵ��α���ƣ������α겻��

            if(!j) j = 1, i++;
            else i++, j++;
        }

        if(j<m) return false;  //jû�ߵ����˵��i�����ˣ�jû���� Ϊƥ��ɹ�

        else return true;
}
//��ʽ����� 
string format(int number) {
	string ret;
	if(number < 10) {
		ret = "0" + to_string(number);
	} else {
		ret = to_string(number);
	}
	
	return ret;
}
// ¼���Ʊ������Ϣ 
void readStockBaseInfo() {
 	ifstream in("��Ʊ������Ϣ����/A�ɹ�˾���.csv");   //��ȡ�ļ� 
 	string row;
 	getline(in, row); 			//��һ���Թ�
 	int i = 0;      			//��Ʊ������Ϣ�����±�
 	string path1 = "��Ʊ�ǵ�����/";
 	string path2 = ".txt";
 	string fullPath;
 	
 	while(getline(in, row)) {
	 //�ַ������Զ��ŷָ��
	 stringstream ss(row);  
	 string str;  //�൱��һ���м仺��
	 vector<string> lineArray;
	 
	 while(getline(ss, str, ',')) lineArray.push_back(str);
	 
	 stocks[i].stockCode = lineArray[0];
	 stocks[i].shortName = lineArray[1];
	 stocks[i].industryCode = lineArray[2];
	 stocks[i].cate1 = lineArray[3];
	 stocks[i].cate2 = lineArray[4];
	 stocks[i].exchange = lineArray[5];
	 stocks[i].fullName = lineArray[6];
	 stocks[i].date = lineArray[7];
	 stocks[i].province = lineArray[8];
	 stocks[i].city = lineArray[9];
	 stocks[i].legalPerson = lineArray[10];
	 stocks[i].location = lineArray[11];
	 stocks[i].website = lineArray[12];
	 stocks[i].email = lineArray[13];
	 stocks[i].phone = lineArray[14];
	 stocks[i].majorBusiness = lineArray[15];
	 stocks[i].businessScope = lineArray[16];
	 
	 fullPath = path1 + lineArray[0] + path2;  //�����ļ�·��
	
	 ifstream fp(fullPath);
	 string line;
	
	 getline(fp, line);  //������һ��
	 getline(fp, line);  //��ʽ��ȡ
	 
	 vector<string> arr;
	 istringstream s(line);
	 while(getline(s, str, ' '))  arr.push_back(str);
	 
	 stocks[i].recentInfo[0] = arr[1];
	 stocks[i].recentInfo[1] = arr[2];
	 stocks[i].recentInfo[2] = arr[8];
	 
	 stocks[i].detail = new changeData;
	 dataLink head = stocks[i].detail;
	 
	 head->date = arr[0];
	 head->openingPrice = arr[1];
	 head->closingPrice = arr[2];
	 head->highestPrice = arr[3];
	 head->lowestPrice = arr[4];
	 head->volume = arr[5];
	 head->turnover = arr[6];
	 head->turnoverRate = arr[7];
	 head->FZDE = arr[8];
	 head->changePercent = stod(arr[9], 0);
	 head->next = NULL;
	 
	 //��ȡtxt�ļ���ÿһ�ж���Ҫ¼�룬�Ⲩ�վ����Ӳ���
	while(getline(fp, line)) {
		vector<string> arr;
		istringstream s(line);
	 	while(getline(s, str, ' '))  arr.push_back(str);
	 	
	 	dataLink node = new changeData;
	 	node->date = arr[0];
		node->openingPrice = arr[1];
		node->closingPrice = arr[2];
		node->highestPrice = arr[3];
		node->lowestPrice = arr[4];
		node->volume = arr[5];
		node->turnover = arr[6];
		node->turnoverRate = arr[7];
		node->FZDE = arr[8];
		node->changePercent = stod(arr[9], 0);
		node->next = NULL;
		
		head->next = node;
		head = head->next;
	}
	i++;
	}
	for(int i = 0; i < 200; i++) {
		stocks[i].score = 0;
	}
	ifstream infile("��Ʊ������Ϣ����/60֧��Ʊ��Ϣ2.csv");
	string scope;
	
	getline(infile, scope);
	getline(infile, scope);

	while(getline(infile, scope)) {
		stringstream ss(scope);
		string str;
	
		vector<string> arr;
		while(getline(ss, str, ',')) arr.push_back(str);

		for(int i = 0; i < 200; i++) {
			if(stocks[i].stockCode == arr[1]) {
				stocks[i].score = stod(arr[2], 0);
				break;
			}
		}
	} //stocks[200]����������������
	
	for(int i = 0; i < 200; i++) {
		dataLink head = stocks[i].detail;
		double maxChangePercent = head->changePercent;
		string date;
		while(head) {
			if(maxChangePercent < head->changePercent) {
				maxChangePercent = head->changePercent;
				date = head->date;
			}
			head = head->next;
		}
		stocks[i].maxChangePercent = maxChangePercent;
		stocks[i].date = date;
	}
}
// ������ϣ�� 
void createHashTable() {
	for(int i = 0; i < 200; i++) {
		string str = stocks[i].stockCode;   //��ϣ�������Ĵ��� 
		int index = hashFun(str);
		
		cout << index << str << endl;
		
		if(!hashTable[index]->next) {  //������ 
			hashList insertNode = new hashNode;
			
			insertNode->node.stockCode = stocks[i].stockCode;
			insertNode->node.shortName = stocks[i].shortName;
			insertNode->node.industryCode = stocks[i].industryCode;
			insertNode->node.cate1 = stocks[i].cate1;
			insertNode->node.cate2 = stocks[i].cate2;
			insertNode->node.exchange = stocks[i].exchange;
			insertNode->node.fullName = stocks[i].fullName;
			insertNode->node.date = stocks[i].date;
			insertNode->node.province = stocks[i].province;
			insertNode->node.city = stocks[i].city;
			insertNode->node.legalPerson = stocks[i].legalPerson;
			insertNode->node.location = stocks[i].location;
			insertNode->node.website = stocks[i].website;
			insertNode->node.email = stocks[i].email;
			insertNode->node.phone = stocks[i].phone;
			insertNode->node.majorBusiness = stocks[i].majorBusiness;
			insertNode->node.businessScope = stocks[i].businessScope;
			
			insertNode->next = NULL;
			
			hashTable[index]->next = insertNode;
		} 
		else {
			// ���ڣ�����  ͷ�巨
			hashList head = hashTable[index]->next;   // ��Ҫ���� 
			hashList insertNode = new hashNode;

			insertNode->node.stockCode = stocks[i].stockCode;
			insertNode->node.shortName = stocks[i].shortName;
			insertNode->node.industryCode = stocks[i].industryCode;
			insertNode->node.cate1 = stocks[i].cate1;
			insertNode->node.cate2 = stocks[i].cate2;
			insertNode->node.exchange = stocks[i].exchange;
			insertNode->node.fullName = stocks[i].fullName;
			insertNode->node.date = stocks[i].date;
			insertNode->node.province = stocks[i].province;
			insertNode->node.city = stocks[i].city;
			insertNode->node.legalPerson = stocks[i].legalPerson;
			insertNode->node.location = stocks[i].location;
			insertNode->node.website = stocks[i].website;
			insertNode->node.email = stocks[i].email;
			insertNode->node.phone = stocks[i].phone;
			insertNode->node.majorBusiness = stocks[i].majorBusiness;
			insertNode->node.businessScope = stocks[i].businessScope;
			
			insertNode->next = head;
			hashTable[index]->next = insertNode;
		}
	}
}
// ��ϣ���һ�����Ϣ
void searchBaseInfo() {
	//��ʼ����ϣ��
	for(int i = 0; i < 97; i++) {
		hashTable[i] = new hashNode;  //����ǵ�new  �ɹ����������� 
		hashTable[i]->next = NULL;  
	}
	
	createHashTable();
	cout << hashTable[31]->node.shortName << 123;
	
	string number;
	int flag = 1;
	
	cout << "��������Ҫ��ѯ�Ĺ�Ʊ���루���磺cn_600519����";
	
	while(cin>>number && flag) {
		cout << number << endl;
		int index = hashFun(number);
		
		if(hashTable[index]->next == NULL) {
			cout << "�����ڸù�Ʊ�����������룡";
			cout << "��������Ҫ��ѯ�Ĺ�Ʊ���루���磺cn_600519����";
		} 
		else {
			hashList stockNode = hashTable[index]->next;
			while(stockNode) {
				if(stockNode->node.stockCode == number) {
					cout << "���ҳɹ���" << endl;
					cout << "��Ʊ���ƣ�" << stockNode->node.shortName << endl;
					cout << "��Ʊ���룺" << stockNode->node.stockCode << endl;
					cout << "һ����ҵ��" << stockNode->node.cate1 << endl;
					cout << "������ҵ��" << stockNode->node.cate2 << endl;
					cout << "��Ӫҵ��" << stockNode->node.majorBusiness << endl;
					flag = 0;
					break;
				}
				stockNode = stockNode->next;
			}
		}
	}
} 
// KMP��ַ����
void searchWebsite() {
	cout << "��������ַ�ؼ���: ";
	string keywords;
	cin >> keywords;
	int flag = 1;
	
	for(int i = 0; i < 200; i++) {
		if(kmp(stocks[i].website, keywords)) {
			cout << stocks[i].shortName << " " << stocks[i].stockCode << endl;
			flag = 0;
			break;
		}
	}
}
// ���ڶ�����������ѯ 
void searchByBST() {
	// https://www.cnblogs.com/linfangnan/p/12958068.html
	BinTree T = NULL;
	createBST(T);
	// ������ϣ�
	string toSearch;
	cout << "������Ҫ��ѯ�Ĺ�Ʊ���룺";
	cin >> toSearch;
	BinTree node = searchBST(T, toSearch);
	cout << "���һ�չ�Ʊ��Ϣ���£�" << endl; 
	cout << "���̼� " << node->data.recentInfo[0] << endl;
	cout << "���̼� " << node->data.recentInfo[1] << endl;
	cout << "�ǵ��� " << node->data.recentInfo[2] << endl;
}
// ����BST
void createBST(BinTree &T) {
	for(int i = 0; i < 200; i++) {
		insertBST(T, i);  // i�ǵڼ���
	}
}
// ����ڵ� 
void insertBST(BinTree& root, int i) {
	if(!root) {  // Ҷ�ӽ�� 
		root = new TNode;
		root->data = stocks[i];
		root->left = NULL;
		root->right = NULL;
	}
	else {
		if(stocks[i].stockCode < root->data.stockCode) {
			insertBST(root->left, i);
		} else if(stocks[i].stockCode > root->data.stockCode) {
			insertBST(root->right, i);
		}
	}
}
// ���ݹ�Ʊ�����ڶ���������������
BinTree searchBST(BinTree T, string key) {
	if(T == NULL || key == T->data.stockCode)
       return T;
    else if(key < T->data.stockCode)      //�ݹ��������������
       return searchBST(T->left, key);
    else                                 //�ݹ��������������
       return searchBST(T->right, key);
}
// ���ڵ�����Ĺ�Ʊ�۸���Ϣ��ѯ 
void searchByLinkList() {
	cout << "������Ҫ��ѯ�����ڣ�";
	string date;
	cin >> date;  
	//¼��ɹ�����������
	 
	dataLink link = getLinkByDate(date);
	
	cout << "��Ʊ����" << "       " << "��Ʊ����" << "      " << "���̼�" << "      " << "���̼�" << "      " << "�ǵ���" << endl;
	link = link->next;
	while(link) {
		cout << link->stockCode << "      ";
		cout << link->shortName << "      ";
		cout << link->openingPrice << "      ";
		cout << link->closingPrice << "      ";
		cout << link->changePercent << endl;
		link = link->next;
	}
	
}
// �������ڻ�ȡ���й�Ʊ����Ĺ�Ʊ��Ϣ 
dataLink getLinkByDate(string date) {
	dataLink link = new changeData;
	dataLink p = link; //�α� 
	
	for(int i = 0; i < 200; i++) {
		dataLink head = stocks[i].detail; //�õ���Ԫ������� 
		while(head) {
			if(head->date == date) {
				dataLink node = new changeData;
				node->stockCode = stocks[i].stockCode;
				node->shortName = stocks[i].shortName;
				node->openingPrice = head->openingPrice;
				node->closingPrice = head->closingPrice;
				node->changePercent = head->changePercent;
				p->next = node;
				p = p->next;
				break;
			}
		}
	}
	
	return link;
}
// ����ֱ�Ӳ�����Ѫ�Ĺ�Ʊ�۸����
void analyseByInsertSort() {
	string date;
	cout << "�������ѯ���ڣ�"; 
	cin >> date;
	
	dataLink link = getLinkByDate(date);
	cout << "1. ���ݿ��̼�����" << endl;
	cout << "2. �������̼�����" << endl;
	cout << "3. �����ǵ�������" << endl;
	cout << "����������ʽ��";
	int option;
	cin >> option;
	switch(option) {
		case 1:
			sortByOpeningPrice(link);
			break;
		case 2:
			sortByClosingPrice(link);
			break;
		case 3:
			sortByChangePercent(link);
			break;
	}
}
// ���ݿ��̼�����
void sortByOpeningPrice(dataLink L) {
	//https://blog.csdn.net/vv_017/article/details/80502837
	dataLink p, pre, q;
	p = L->next->next;		// �ȱ�����L�ĵڶ���Ԫ�أ���Ϊ��һ��Ҫ��L���ֻ��һ��Ԫ�ص������  
	L->next->next = NULL;	// ��L���ֻ��һ��Ԫ�ص������
	// ��L�ĵڶ���Ԫ�ؿ�ʼ��������Lֱ����β 
	while(p != NULL){
		q = p->next;
		pre = L;	// ����pre������L��
		//https://blog.csdn.net/sinat_40872274/article/details/81367815
		while(pre->next !=NULL && stod(pre->next->openingPrice, 0) > stod(p->openingPrice, 0)) // ����pre��ָ��������L��ֱ���ҵ���p��Ľڵ� 
			pre = pre->next; 
		p->next = pre->next;
		pre->next = p;
		p = q;	
	}
	int index = 1;
	L = L->next;
	ofstream outfile("�۸���ǵ���������-���̼۽���.csv", ios::out);
	outfile << "���" << "," << "��Ʊ����" << "," << "��Ʊ����" << "," << "���̼�" << "," << "���̼�"
	<< "," << "�ǵ���" << endl;
	cout << "���" << "      "<< "��Ʊ����" << "       " << "��Ʊ����" << "      " << "���̼�" << "      " << "���̼�" << "      " << "�ǵ���" << endl;
	while(L) {
		cout << index << "      ";
	 	cout << L->stockCode << "      ";
		cout << L->shortName << "      ";
		cout << L->openingPrice << "      ";
		cout << L->closingPrice << "      ";
		cout << L->changePercent << endl;
		outfile << index << "," << L->stockCode << "," << L->shortName << "," << L->openingPrice << ","
		<< L->closingPrice << "," << L->changePercent << endl;
		L = L->next;
		index++;
	}
	outfile.close();
}
// �������̼�����
void sortByClosingPrice(dataLink L) {
	dataLink p, pre, q;
	p = L->next->next;		// �ȱ�����L�ĵڶ���Ԫ�أ���Ϊ��һ��Ҫ��L���ֻ��һ��Ԫ�ص������  
	L->next->next = NULL;	// ��L���ֻ��һ��Ԫ�ص������
	// ��L�ĵڶ���Ԫ�ؿ�ʼ��������Lֱ����β 
	while(p != NULL){
		q = p->next;
		pre = L;	// ����pre������L��
		while(pre->next !=NULL && stod(pre->next->closingPrice, 0) > stod(p->closingPrice, 0)) // ����pre��ָ��������L��ֱ���ҵ���p��Ľڵ� 
			pre = pre->next; 
		p->next = pre->next;
		pre->next = p;
		p = q;	
	}
	int index = 1;
	L = L->next;
	ofstream outfile("�۸���ǵ���������-���̼۽���.csv", ios::out);
	outfile << "���" << "," << "��Ʊ����" << "," << "��Ʊ����" << "," << "���̼�" << "," << "���̼�"
	<< "," << "�ǵ���" << endl;
	cout << "���" << "      "<< "��Ʊ����" << "       " << "��Ʊ����" << "      " << "���̼�" << "      " << "���̼�" << "      " << "�ǵ���" << endl;
	while(L) {
		cout << index << "      ";
	 	cout << L->stockCode << "      ";
		cout << L->shortName << "      ";
		cout << L->openingPrice << "      ";
		cout << L->closingPrice << "      ";
		cout << L->changePercent << endl;
		outfile << index << "," << L->stockCode << "," << L->shortName << "," << L->openingPrice << ","
		<< L->closingPrice << "," << L->changePercent << endl;
		L = L->next;
		index++;
	}
	outfile.close();
}
// �����ǵ�������
void sortByChangePercent(dataLink L) {
	dataLink p, pre, q;
	p = L->next->next;		// �ȱ�����L�ĵڶ���Ԫ�أ���Ϊ��һ��Ҫ��L���ֻ��һ��Ԫ�ص������  
	L->next->next = NULL;	// ��L���ֻ��һ��Ԫ�ص������
	// ��L�ĵڶ���Ԫ�ؿ�ʼ��������Lֱ����β 
	while(p != NULL){
		q = p->next;
		pre = L;	// ����pre������L��
		while(pre->next !=NULL && pre->next->changePercent > p->changePercent) // ����pre��ָ��������L��ֱ���ҵ���p��Ľڵ� 
			pre = pre->next; 
		p->next = pre->next;
		pre->next = p;
		p = q;	
	}
	int index = 1;
	L = L->next;
	ofstream outfile("�۸���ǵ���������-�ǵ�������.csv", ios::out);
	outfile << "���" << "," << "��Ʊ����" << "," << "��Ʊ����" << "," << "���̼�" << "," << "���̼�"
	<< "," << "�ǵ���" << endl;
	cout << "���" << "      "<< "��Ʊ����" << "       " << "��Ʊ����" << "      " << "���̼�" << "      " << "���̼�" << "      " << "�ǵ���" << endl;
	while(L) {
		cout << index << "      ";
	 	cout << L->stockCode << "      ";
		cout << L->shortName << "      ";
		cout << L->openingPrice << "      ";
		cout << L->closingPrice << "      ";
		cout << L->changePercent << endl;
		outfile << index << "," << L->stockCode << "," << L->shortName << "," << L->openingPrice << ","
		<< L->closingPrice << "," << L->changePercent << endl;
		L = L->next;
		index++;
	}
	outfile.close();
}
// ���ڿ�������Ĺ�Ʊ�۸����
void analyseByQuickSort() {
	
	string cate;
	cout << "������һ����ҵ��";
	cin >> cate;
	
	vector<StockInfo> industry;  //����ҵ�Ĺ�Ʊ
	industry.push_back(stocks[0]);
	
	for(int i = 0; i < 200; i++) {
		if(stocks[i].cate1 == cate && stocks[i].score > 0) {
			industry.push_back(stocks[i]);
		}
	}
	quickSort(industry, 1, industry.size()-1);
	int n = industry.size();
	for(int i = 1; i < n-1; i++) {
		cout << i << "   " << industry[i].stockCode << "   " << industry[i].shortName << 
		"   " << industry[i].maxChangePercent << "   " << industry[i].maxDate << endl;
	}
}
void quickSort(vector<StockInfo> &industry, int low, int high) {
	if(low < high) {
		int pivitloc = partition(industry, low, high);
		quickSort(industry, low, pivitloc-1);
		quickSort(industry, pivitloc+1, high);
	}
}
int partition(vector<StockInfo> &industry, int low, int high) {
	industry[0] = industry[low];   
	double pivotkey = industry[low].maxChangePercent;

    while(low < high)
	{ 
	   while(low < high && industry[high].maxChangePercent < pivotkey )  
	   	--high;
       industry[low] = industry[high];
       while (low < high && industry[low].maxChangePercent >= pivotkey )  
	   	++low;
       industry[high] = industry[low];
    }
    industry[low] = industry[0]; 
    return low;
}
// ���ڼ�ѡ������Ĺ�Ʊ�۸����
void analyseBySelectionSort() {
	ifstream in("��Ʊ������Ϣ����/60֧��Ʊ��Ϣ2.csv");
	string row;
	
	getline(in, row);
	getline(in, row);
	vector<vector<string>> arr1;

	while(getline(in, row)) {
		stringstream ss(row);
		string str;
	
		vector<string> arr;
		while(getline(ss, str, ',')) arr.push_back(str);
		arr1.push_back(arr);
	}  //�������ݷŵ� arr1 ���� 
	
	int num = arr1.size();
	for(int i = 0; i < num-1; i++) {
		int k = i;
		for(int j = i+1; j < num; j++) {
			if(stod(arr1[j][2]) > stod(arr1[k][2])) k = j;
		}
		if(k != i) swap(arr1[i], arr1[k]);
	}  //������������  OK��
	 
	vector<StockInfo> arr2;
	for(int i = 0; i < 200; i++) {
		if(stocks[i].score > 0)  arr2.push_back(stocks[i]);
	}
	
	int n = arr2.size();
	for(int i = 0; i < n-1; i++) {
		int k = i;
		for(int j = i+1; j < n; j++) {
			if( stod(arr2[j].recentInfo[1]) > stod(arr2[k].recentInfo[1]) ) k = j;
		}
		if(k != i) swap(arr2[i], arr2[k]);
	}  //�������̼�����  OK!
	
	cout << "���" << "   " << "��Ʊ����" << "   " << "��Ʊ����" << "   " << "����  " ;
	cout << "���" << "   " << "��Ʊ����" << "   " << "��Ʊ����" << "   " << "���̼�" << endl;
	
	ofstream scoreSort("��������.csv", ios::out);
	scoreSort << "���" << "," << "��Ʊ����" << "," << "��Ʊ����" << "," << "����" << endl;
	ofstream priceSort("���̼�����.csv", ios::out);
	priceSort << "���" << "," << "��Ʊ����" << "," << "��Ʊ����" << "," << "���̼�" << endl;
	
	for(int i = 0; i < 60; i++) { 
		cout << format(i+1) << "   " << arr1[i][0] << "   " << arr1[i][1] << "   " << arr1[i][2] << " |";
		cout << format(i+1) << "   " << arr2[i].stockCode << "   " << arr2[i].shortName << "   " << arr2[i].recentInfo[1] << endl;
		
		scoreSort << i+1 << "," << arr1[i][0] << "," << arr1[i][1] << "," << arr1[i][2] << endl;
		priceSort << i+1 << "," << arr2[i].stockCode << "," << arr2[i].shortName << "," << arr2[i].recentInfo[1] << endl;
	}

	scoreSort.close();
	priceSort.close();
}
// 















