#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
#define MAX  20
typedef struct{
	float coef;
	int exp;
}PolyArray[MAX];
//���嵥����������
typedef struct pnode{
	float coef;
	int exp;
	struct pnode *next;
}PolyNode;
//�������ʽ����
void DispPoly(PolyNode *L){//����ҵ���ʽ
	PolyNode  *p = L->next;
	while (p != NULL){
		printf("%gX^%d", p->coef, p->exp);//��%g���ǲ����С�������û�������0 
		p = p->next;
		if (p != NULL) printf(" + ");
	}
	printf("\n");
}
//һԪ����ʽ�ı�ʾ
//����������ʽ����
PolyNode* CreateListR(PolyArray a, int n){//��������������ʼ���������ʼ�������ĵ�һ���ڵ��ǲ�������ֵ��
	PolyNode *s, *r, *L; int i;
	L = (PolyNode*)malloc(sizeof(PolyNode));//���ó�ʼ��ͷ������ǲ�������ֵ�ģ���Ȼ�����ʡȥ��if��head�����ֶ���
	L->next = NULL;//���Բ�Ҫ
	r = L;
	for (i = 0; i<n; i++){
		s = (PolyNode  *)malloc(sizeof (PolyNode));//�����µĽڵ�Ŀռ�
		s->coef = a[i].coef;
		s->exp = a[i].exp;
		s->next = NULL;//���Բ�Ҫ
		r->next = s;
		r = s;
	}
	r->next = NULL;
	return L;//����ͷ
}
//ԭ����ʽ��������
void Sort(PolyNode *head){//soft��������ȶϿ�����������ֳ������֣�һ��������ͷ���ģ�һ����ֻ����ֵ�ģ���Ȼ��ͨ������ֵ������ͷ���������������
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
//һԪ����ʽ�����
PolyNode* Add(PolyNode *ha, PolyNode *hb){
	PolyNode *hc;
	PolyNode*pa = ha->next, *pb = hb->next, *s, *tc;
	float c;
	hc = (PolyNode*)malloc(sizeof(PolyNode));
	tc = hc;
	while (pa != NULL && pb != NULL){//��������Ƚ����������ϲ��������Ԫ�ذ��մ�С�����ó����ӵ��µ�����֮�У�����������ͬ�����
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
	//�˴�����ȷ������ܹ�������ֻ��pa����ʣ�µĶ�ȡ��� 
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
//���������趨������
int main(){
	PolyNode *ha, *hb, *hc;
	PolyArray a = { { 1.2f, 0 }, { 2.5f, 1 }, { 3.2f, 3 }, { -2.5f, 5 } };
	PolyArray b = { { -1.2f, 0 }, { 2.5f, 1 }, { 3.2f, 3 }, { 2.5f, 5 }, { 5.4f, 10 } };
	ha = CreateListR(a, 4);
	hb = CreateListR(b, 5);
	printf("ԭ����ʽA ��"); DispPoly(ha);
	printf("ԭ����ʽ B ��"); DispPoly(hb);
	Sort(ha);
	Sort(hb);
	printf("�������ʽA ��"); DispPoly(ha);
	printf("�������ʽB ��"); DispPoly(hb);
	hc = Add(ha, hb);
	printf("����ʽ��ӣ�"); DispPoly(hc);
	system("pause");
}
