#include<stdio.h>
#include<time.h>//time�õ���ͷ�ļ�
#include<stdlib.h>//�����srand�õ���ͷ�ļ�
#include<ctype.h>//toascii()�õ���ͷ�ļ�
#include<string.h>//��������ʱ�Ƚ��ַ����õ�ͷ�ļ�
#define HASH_LEN 50//��ϣ��ĳ���
#define P 47//С�ڹ�ϣ���ȵ�P
#define NAME_LEN 30//������ĳ���

typedef struct//������
{
    char *key;    //���ֵ�ƴ��
    int m;       //ƴ������Ӧ��ASCII��
}NAME;

typedef struct//��ϣ��
{
    char *key;   //���ֵ�ƴ��
    int m;      //ƴ������Ӧ��ASCII�ܺͣ����ؼ���
    int si;     //���ҳ���
}HASH;

NAME Name[HASH_LEN];        //ȫ�ֶ���������,��󳤶�Ϊ50
HASH Hash[HASH_LEN];        //ȫ�ֶ����ϣ����󳤶�Ϊ50
int d[30],i,j;    //ȫ�ֶ��������,ѭ���õ�i��j

void InitName()
{//������ĳ�ʼ��
    Name[0].key="lvsongxian";
    Name[1].key="yuanlei";
    Name[2].key="daiziwen";
    Name[3].key="chenyonghui";
    Name[4].key="zhangliang";
    Name[5].key="liubei";
    Name[6].key="sunshangxiang";
    Name[7].key="liyuanfang";
    Name[8].key="huge";
    Name[9].key="liuyifei";
    Name[10].key="anyixuan";
    Name[11].key="wangbaoqiang";
    Name[12].key="yangyiming";
    Name[13].key="hujing";
    Name[14].key="guowen";
    Name[15].key="xuyang";
    Name[16].key="lilu";
    Name[17].key="shenjinfeng";
    Name[18].key="xuhui";
    Name[19].key="huangjing";
    Name[20].key="guanyu";
    Name[21].key="chenlong";
    Name[22].key="huangliang";
    Name[23].key="liyan";
    Name[24].key="haojian";
    Name[25].key="zhangfei";
    Name[26].key="shuxiang";
    Name[27].key="sunyingjie";
    Name[28].key="wangbo";
    Name[29].key="zhaoqing";
for (i=0;i<NAME_LEN;i++)    //���ַ����ĸ����ַ�����Ӧ��ASCII����ӣ����õ�������Ϊ��ϣ��Ĺؼ���
{
    int s=0;
        char *p=Name[i].key;
    for (j=0;*(p+j)!='\0';j++)
        s+=toascii(*(p+j));
        Name[i].m=s;
}
}

void CreateHash()
{//������ϣ��
       for(i=0;i<HASH_LEN;i++) //��չ�ϣ��δ���˲��������������
       {
              Hash[i].key="\0";
              Hash[i].m =0;
              Hash[i].si=0;
       }
       for(i=0;i<NAME_LEN;i++)
       {
              int sum=1,j=0,t;
              int adr=(Name[i].m)%P;  //����������H(key)=key%P������ΪP=47
              if(Hash[adr].si==0)     //�������ͻ����������ֵ����ϣ��
              {
                     Hash[adr].m =Name[i].m;
                     Hash[adr].key=Name[i].key;
                     Hash[adr].si=1;
              }
              else                         //�����ͻ
              {
                  t=adr;        //����̽�ⷨ�����ͻ
                 for(;Hash[adr].si!=0&&adr<HASH_LEN;adr++)//�ӳ�ͻ��һ��λ�ÿ�ʼ̽��
                     {
                            sum=sum+1;//ÿ�β��ң����Ҵ���+1
                            if(adr==HASH_LEN-1)//����ҵ����һ����Ȼû��λ��
                            {
                                for(;Hash[adr].si!=0&&adr<t;adr++)//�ӵ�һ����ʼ̽��
                                 sum=sum+1;//ÿ�β��ң����Ҵ���+1
                                 if(adr==t) printf("��ϣ������\n");//����ҵ��ϴε�λ����Ȼû�У��������ϣ������
                            }
                     }
                     Hash[adr].m =Name[i].m;  //���������Ƹ���ϣ���Ӧ��λ����
                     Hash[adr].key=Name[i].key;
                     Hash[adr].si=sum;
              }
       }
}

void DisplayName()//��ʾ������
{
       printf("\n��ַ \t\t ���� \t\t �ؼ���\n");
       for (i=0;i<NAME_LEN;i++)
       printf("%2d %18s \t\t  %d  \n",i,Name[i].key,Name[i].m);
}

void DisplayHash()// ��ʾ��ϣ��
{
       float asl=0.0;
       printf("\n\n ��ַ \t\t ���� \t\t �ؼ��� \t ��������\n"); //��ʾ�ĸ�ʽ
       for (i=0;i<HASH_LEN;i++)
       {
              printf("%2d %18s \t\t  %d \t\t  %d\n",i,Hash[i].key,Hash[i].m,Hash[i].si);
              asl+=Hash[i].si;
       }
       asl/=NAME_LEN;//���ASL
       printf("\n\nƽ�����ҳ��ȣ�ASL(%d)=%f \n",NAME_LEN,asl);
}

void FindName()//����
{
    char name[20]={0};
    int s=0,sum=1,adr;
    printf("\n��������Ҫ���ҵ�������ƴ��:");
    scanf("%s",name);
    getchar();
    for (j=0;j<20;j++)//���������ƴ������Ӧ��ASCII��Ϊ�ؼ���
        s+=toascii(name[j]);
    adr=s%P;           //����������
    j=0;
    if(Hash[adr].m==s&&!strcmp(Hash[adr].key,name)) //��3����������жϣ���������ҽ��
        printf("\n����:%s   �ؼ���:%d   ��ַ:%d   ���ҳ���Ϊ: 1\n",Hash[adr].key,s,adr);
    else if (Hash[adr].m==0)
        printf("\nû����Ҫ���ҵ���!\n");
    else
       {
            while(1)
              {
                  adr=(adr+d[j++])%HASH_LEN;//α���̽����ɢ�з������ͻ
                  sum=sum+1;                //���Ҵ�����1
                  if(Hash[adr].m==0)
                     {
                        printf("\nû����Ҫ���ҵ���!\n");
                        break;
                     }
                     if(Hash[adr].m==s&&!strcmp(Hash[adr].key,name))
                     {
                        printf("\n����:%s   �ؼ���:%d   ��ַ:%d   ���ҳ���Ϊ:%d\n",Hash[adr].key,adr,s,sum);
                        break;
                     }
              }
       }
}

void view()//��������
{
     printf("=======================================================\n");
    printf("=                                                     =\n");
    printf("=                   ������ϣ��                        =\n");
    printf("=                                                     =\n");
    printf("=  A: ��ӡ������                 B: ��ӡ��ϣ��        =\n");
    printf("=                                                     =\n");
    printf("=  C: ����                       D: �˳�����          =\n");
    printf("=                                                     =\n");
    printf("=======================================================\n");
}

int main()//������
{
    char c;
    int a=1;
    srand((int)time(0));//�Ե�ǰʱ���Ӧ��intֵΪ���������㣬ÿ�����г���������㲻ͬ���Եõ���ͬ�����������
    for(i=0;i<30;i++)//������������α�������d[i]����1��50֮�䣩
        d[i]=1+(int)(HASH_LEN*rand()/(RAND_MAX+1.0));
    InitName();//���ó�ʼ����������
    CreateHash();//���ô�����ϣ����
    view();//���ý������溯��
    while(a)
    {
       printf("\n����ѡ��:");
       scanf("%c",&c);
       getchar();
       switch(c)//����ѡ������жϣ�ֱ��ѡ���˳�ʱ�ſ����˳�
       {
           case 'A':
           case 'a': DisplayName(); break;//��ӡ������
           case 'B':
           case 'b': DisplayHash(); break;//��ӡ��ϣ��
           case 'C':
           case 'c': FindName(); break;//���ò��Һ���
           case 'D':
           case 'd': a=0; break;//�˳�ѭ������ֹ����
           default: printf("\n��������ȷ��ѡ��!\n"); break;
       }
    }
    return 0;
}

