#include <iostream>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 100	//������������
struct goods	//��Ʒ�ṹ��
{
	int sign;	//��Ʒ���
	int w;	//��Ʒ����
	int p;	//��Ʒ��ֵ
}a[N];
bool m(goods a,goods b)
{
	return (a.p/a.w)>(b.p/b.w);
}
int max(int a,int b)
{
	return a<b?b:a;
}
int n,C,bestP=0,cp=0,cw=0;
int X[N],cx[N];
/*���������0/1��������*/
int Force(int i)
{
	if(i>n-1){
		if(bestP<cp&&cw+a[i].w<=C){
			for (int k=0;k<n;k++)	X[k]=cx[k];//�洢����·��
			bestP=cp;
		}
		return bestP;
	}
	cw=cw+a[i].w;
	cp=cp+a[i].p;
	cx[i]=1;	//װ�뱳��
	Force(i+1);
	cw=cw-a[i].w;
	cp=cp-a[i].p;
	cx[i]=0;	//��װ�뱳��
	Force(i+1);
	return bestP;
}
int KnapSack1(int n,goods a[],int C,int x[])
{
	Force(0);
	return bestP;
}
/*��̬�滮�����0/1��������*/
int KnapSack2(int n,goods a[],int C,int x[])
{
    int j;
	int V[N][10*N];
	for(int i=0;i<=n;i++)	//��ʼ����0��
		V[i][0]=0;
	for(int j=0;j<=C;j++)	//��ʼ����0��
		V[0][j]=0;
	for(int i=1;i<=n;i++)		//�����i�У����е�i�ε���
		for(int j=1;j<=C;j++)
			if(j<a[i-1].w)
				V[i][j]=V[i-1][j];
			else
				V[i][j]=max(V[i-1][j],V[i-1][j-a[i-1].w]+a[i-1].p);
			j=C;	//��װ�뱳������Ʒ
			for (int i=n;i>0;i--)
			{
				if (V[i][j]>V[i-1][j]){
					x[i-1]=1;
					j=j-a[i-1].w;
				}
				else	x[i-1]=0;
			}
			return V[n][C];	//���ر���ȡ�õ�����ֵ
}
/*���ݷ����0/1��������*/
int BackTrack(int i)
{
	if(i>n-1){
		if(bestP<cp){
			for (int k=0;k<n;k++)	X[k]=cx[k];//�洢����·��
			bestP=cp;
		}
		return bestP;
	}
	if(cw+a[i].w<=C){	//����������
		cw=cw+a[i].w;
		cp=cp+a[i].p;
		cx[a[i].sign]=1;	//װ�뱳��
		BackTrack(i+1);
		cw=cw-a[i].w;
		cp=cp-a[i].p;	//���ݣ�����������
	}
	cx[a[i].sign]=0;	//��װ�뱳��
	BackTrack(i+1);
	return bestP;
}
int KnapSack3(int n,goods a[],int C,int x[])
{
	for(int i=0;i<n;i++)
	{
		x[i]=0;
		a[i].sign=i;
	}
	sort(a,a+n,m);//������Ʒ����λ������ֵ��������
	BackTrack(0);
	return bestP;
}
/*��֧�޽編���0/1��������*/
struct KNAPNODE	//״̬�ṹ��
{
	bool s1[N]; //��ǰ��������
	int k;		//�������
	int b;	//��ֵ�Ͻ�
	int w;	//��������
	int p;	//�����ֵ
};
struct HEAP	//��Ԫ�ؽṹ��
{
	KNAPNODE *p;//�������
	int b;        //��ָ�����Ͻ�
};
//����������Ԫ��
void swap(HEAP &a, HEAP &b)
{
	HEAP temp = a;
	a = b;
	b = temp;
}
//����Ԫ������
void mov_up(HEAP H[], int i)
{
	bool done = false;
	if(i!=1){
		while(!done && i!=1){
			if(H[i].b>H[i/2].b){
				swap(H[i], H[i/2]);
			}else{
				done = true;
			}
			i = i/2;
		}
	}
}
//����Ԫ������
void mov_down(HEAP H[], int n, int i)
{
	bool done = false;
	if((2*i)<=n){
		while(!done && ((i = 2*i) <= n)){
			if(i+1<=n && H[i+1].b > H[i].b){
				i++;
			}
			if(H[i/2].b<H[i].b){
				swap(H[i/2], H[i]);
			}else{
				done = true;
			}
		}
	}
}
//�����в�����
void insert(HEAP H[], HEAP x, int &n)
{
	n++;
	H[n] = x;
	mov_up(H,n);
}
//ɾ�����н��
void del(HEAP H[], int &n, int i)
{
	HEAP x, y;
	x = H[i]; y = H[n];
	n --;
	if(i<=n){
		H[i] = y;
		if(y.b>=x.b){
			mov_up(H,i);
		}else{
			mov_down(H, n, i);
		}
	}
}
//��öѶ�Ԫ�ز�ɾ��
HEAP del_top(HEAP H[], int &n)
{
	HEAP x = H[1];
	del(H, n, 1);
	return x;
}
//�����֧�ڵ���Ͻ�
void bound( KNAPNODE* node, int M, goods a[], int n)
{
	int i = node->k;
	float w = node->w;
	float p = node->p;
	if(node->w>M){    //  ����������������������
		node->b = 0;    //  �Ͻ���Ϊ0
	}else{
		while((w+a[i].w<=M)&&(i<n)){
			w += a[i].w;   // ���㱳����װ������
			p += a[i++].p;  //    ���㱳����װ���ֵ
		}
		if(i<n){
			node->b = p + (M - w)*a[i].p/a[i].w;
		}else{
			node -> b = p;
		}
	}
}
//�÷�֧�޽編ʵ��0/1��������
int KnapSack4(int n,goods a[],int C, int X[])
{
	int i, k = 0;      // ����Ԫ�ظ����ļ�������ʼ��Ϊ0
	int v;
	KNAPNODE *xnode, *ynode, *znode;
	HEAP x, y, z, *heap;
	heap = new HEAP[n*n];         // ����ѵĴ洢�ռ�
	for( i=0; i<n; i++){
		a[i].sign=i;        //��¼����ĳ�ʼ���
	}
	sort(a,a+n,m);              // �����尴�ռ�ֵ����������
	xnode = new KNAPNODE;         // �������׽��
	for( i=0; i<n; i++){            //  ��ʼ�����
		xnode->s1[i] = false;
	}
	xnode->k = xnode->w = xnode->p = 0;
	while(xnode->k<n) {
		ynode = new KNAPNODE;      // �������y
		*ynode = *xnode;          //���x�����ݸ��Ƶ����y
		ynode->s1[ynode->k] = true;     //   װ���k������
		ynode->w += a[ynode->k].w;     //   ���������������ۼ�
		ynode->p += a[ynode->k].p;     //   �����������ֵ�ۼ�
		ynode->k ++;                //  �������++
		bound(ynode, C, a, n);  //       ������y���Ͻ�
		y.b = ynode->b;
		y.p = ynode;
		insert(heap, y, k);        //���y���Ͻ��ֵ�������
		znode = new KNAPNODE;      // �������z
		*znode = *xnode;           //���x�����ݸ��Ƶ����z
		znode->k++;                         //   �������++
		bound(znode, C, a, n);  //����ڵ�z���Ͻ�
		z.b = znode->b;
		z.p = znode;
		insert(heap, z, k);      //���z���Ͻ��ֵ�������
		delete xnode;
		x = del_top(heap, k);    //��öѶ�Ԫ����Ϊ�µĸ��׽��
		xnode = x.p;
	}
	v = xnode->p;
	for( i=0; i<n; i++){      //ȡװ�뱳��������������ǰ�����
		if(xnode->s1[i]){
			X[a[i].sign] =1 ;
		}else{
			X[a[i].sign] = 0;
		}
	}
	delete xnode;
	delete heap;
	return v;              //���ر���������ļ�ֵ
}
/*���������㷨��������*/
int main()
{
	goods b[N];
	printf("��Ʒ����n: ");
	scanf("%d",&n);	//������Ʒ����
	printf("��������C: ");
	scanf("%d",&C);	//���뱳������
	for (int i=0;i<n;i++)	//������Ʒi������w�����ֵv
	{
		printf("��Ʒ%d������w[%d]�����ֵv[%d]:  ",i+1,i+1,i+1);
		scanf("%d%d",&a[i].w,&a[i].p);
		b[i]=a[i];
	}
	int sum1=KnapSack1(n,a,C,X);//������������0/1��������
	printf("���������0/1��������:\nX=[ ");
	for(int i=0;i<n;i++)
		cout<<X[i]<<" ";//�������X[n]����
	printf("]	װ���ܼ�ֵ%d\n",sum1);
	bestP=0,cp=0,cw=0;//�ָ���ʼ��
	int sum2=KnapSack2(n,a,C,X);//���ö�̬�滮����0/1��������
	printf("��̬�滮�����0/1��������:\nX=[ ");
	for(int i=0;i<n;i++)
		cout<<X[i]<<" ";//�������X[n]����
	printf("]	װ���ܼ�ֵ%d\n",sum2);
	for (int i=0;i<n;i++)
	{
		a[i]=b[i];
	}//�ָ�a[N]˳��
	int sum3=KnapSack3(n,a,C,X);//���û��ݷ���0/1��������
	printf("���ݷ����0/1��������:\nX=[ ");
	for(int i=0;i<n;i++)
		cout<<X[i]<<" ";//�������X[n]����
	printf("]	װ���ܼ�ֵ%d\n",sum3);
	for (int i=0;i<n;i++)
	{
		a[i]=b[i];
	}//�ָ�a[N]˳��
	int sum4=KnapSack4(n,a,C,X);//���÷�֧�޽編��0/1��������
	printf("��֧�޽編���0/1��������:\nX=[ ");
	for(int i=0;i<n;i++)
		cout<<X[i]<<" ";//�������X[n]����
	printf("]	װ���ܼ�ֵ%d\n",sum4);
	return 0;
}
