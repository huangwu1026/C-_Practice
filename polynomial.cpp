#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#define MAX  20
typedef struct{
	float coef;
	int exp;
}PolyArray[MAX];
//定义单链表结点类型
typedef struct pnode{
	float coef;
	int exp;
	struct pnode *next;
}PolyNode;
//输出多项式链表
void DispPoly(PolyNode *L){//输出我的算式
	PolyNode  *p = L->next;
	while (p != NULL){
		printf("%gX^%d", p->coef, p->exp);//在%g中是不输出小数点后面没有意义的0 
		p = p->next;
		if (p != NULL) printf(" + ");
	}
	printf("\n");
}
//一元多项式的表示
//（建立多项式链表）
PolyNode* CreateListR(PolyArray a, int n){//根据你给的数组初始化，这个初始化出来的第一个节点是不储存数值的
	PolyNode *s, *r, *L; int i;
	L = (PolyNode*)malloc(sizeof(PolyNode));//设置初始化头，这个是不储存数值的，当然这个就省去了if（head）这种东西
	L->next = NULL;//可以不要
	r = L;
	for (i = 0; i<n; i++){
		s = (PolyNode  *)malloc(sizeof (PolyNode));//开辟新的节点的空间
		s->coef = a[i].coef;
		s->exp = a[i].exp;
		s->next = NULL;//可以不要
		r->next = s;
		r = s;
	}
	r->next = NULL;
	return L;//返回头
}
//原多项式链表排序
void Sort(PolyNode *head){//soft这个就是先断开链表，将链表分成两部分（一边是连接头结点的，一边是只有数值的），然后通过把数值插入有头结点的链表，完成排序
	PolyNode  *p = head->next, *q, *r;
	if (p != NULL){
		r = p->next;
		p->next = NULL;
		p = r;
		while (p != NULL){
			r = p->next;
			q = head;
			while (q->next != NULL && q->next->exp >p->exp)
				q = q->next;
			p->next = q->next;
			q->next = p;
			p = r;
		}
	}
}
//一元多项式的相加
PolyNode* Add(PolyNode *ha, PolyNode *hb){
	PolyNode *hc;
	PolyNode*pa = ha->next, *pb = hb->next, *s, *tc;
	float c;
	hc = (PolyNode*)malloc(sizeof(PolyNode));
	tc = hc;
	while (pa != NULL && pb != NULL){//这个就是先将两个即将合并的链表的元素按照大小依次拿出连接到新的链表之中，或者遇到相同的相加
		if (pa->exp > pb->exp){
			s = (PolyNode*)malloc(sizeof(PolyNode));
			s->exp = pa->exp; s->coef = pa->coef;
			s->next = NULL;
			tc->next = s; tc = s;
			pa = pa->next;
		}
		else if (pa->exp < pb->exp){
			s = (PolyNode *)malloc(sizeof(PolyNode));
			s->exp = pb->exp; s->coef = pb->coef;
			s->next = NULL;
			tc->next = s;
			tc = s;
			pb = pb->next;
		}
		else {
			c = pa->coef + pb->coef;
			if (c){
				s = (PolyNode *)malloc(sizeof(PolyNode));
				s->exp = pa->exp; s->coef = c;
				s->next = NULL;
				tc->next = s; tc = s;
			}
			pa = pa->next;
			pb = pb->next;
		}
	}
	//此处就是确保最后能够可以能只用pa来把剩下的读取完毕 
	if (pb != NULL) pa = pb;
	while (pa != NULL){
		s = (PolyNode*)malloc(sizeof(PolyNode));
		s->exp = pa->exp; s->coef = pa->coef;
		s->next = NULL;
		tc->next = s; tc = s;
		pa = pa->next;
	}
	tc->next = NULL;
	return hc;
}
//主函数的设定及调用
int main(){
	PolyNode *ha, *hb, *hc;
	PolyArray a = { { 1.2f, 0 }, { 2.5f, 1 }, { 3.2f, 3 }, { -2.5f, 5 } };
	PolyArray b = { { -1.2f, 0 }, { 2.5f, 1 }, { 3.2f, 3 }, { 2.5f, 5 }, { 5.4f, 10 } };
	ha = CreateListR(a, 4);
	hb = CreateListR(b, 5);
	printf("原多项式A ："); DispPoly(ha);
	printf("原多项式 B ："); DispPoly(hb);
	Sort(ha);
	Sort(hb);
	printf("有序多项式A ："); DispPoly(ha);
	printf("有序多项式B ："); DispPoly(hb);
	hc = Add(ha, hb);
	printf("多项式相加："); DispPoly(hc);
	system("pause");
}
