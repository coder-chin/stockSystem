#include "general.h"

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
// Ȩֵ�������
bool cmp(const fundPortfolio t1, const fundPortfolio t2) {
	if(t1.weight < t2.weight) return true;
	return false;
} 
// ������ 
bool cmpByScores(const fundPortfolio t1, const fundPortfolio t2) {
	if(t1.scoreSum > t2.scoreSum) return true;
	return false;
} 
// ���鼯����
int find(int x) {
	return x = p[x] ? x : p[x] = find(p[x]);
} 
