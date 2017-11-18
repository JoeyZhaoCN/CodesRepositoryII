#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define INITSIZE 100        //���Ա���ṹ��ʼ�������
#define ENLARGE 10          //���Ա���ṹ��������

typedef int Status;
typedef int ElemType;

typedef struct
{
    ElemType *elem;     //���Ա��ַ
    int length;         //���Ա���
    int listsize;       //��ǰ���������
}SqList;

Status InitList(SqList *L)
{
    //����һ���յ����Ա�
    L->elem = (ElemType*)malloc(INITSIZE * sizeof(ElemType));
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = INITSIZE;
    return OK;
}

Status DestroyList(SqList *L)
{
    //�������Ա�L
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    return OK;
}

Status ClearList(SqList *L)
{
    //��L����Ϊ�ձ�
    free(L->elem);
    L->elem = (ElemType*)malloc(INITSIZE * sizeof(ElemType));
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = INITSIZE;
    return OK;
}

Status EmptyList(SqList *L)
{
    //�ж�L�Ƿ�Ϊ�ձ�
    if(!L->elem) exit(INFEASIBLE);
    if(L->length == 0) return TRUE;
    else return FALSE;
}

Status ListLength(SqList *L)
{
    //�������Ա�L�е�Ԫ�ظ���
    return L->length;
}

Status GetElem(SqList *L,int i)
{
    //��e�������Ա�L�еĵ�i��ֵ
    ElemType *p = L->elem;
    if(i >= 1 && i <= L->length){
        return *(p + i - 1);
    }
    else return ERROR;
}

Status LocateElem(SqList *L,ElemType e)
{
    //�ж����Ա����Ƿ����e
    ElemType *p;
    p = L->elem;
    int i = 1;
    while(i <= L->length && *(p++) != e){
        i++;
    }
    if(i <= L->length) return i;
    else return ERROR;
}

Status PriorElem(SqList *L,int i)
{
    //�����Ա���cur_e��ǰ��
    if(i == 1)
        return ERROR;
    else{
        return L->elem[i - 2];
    }
}

Status NextElem(SqList *L,int i)
{
    //�����Ա���cur_e�ĺ��
    if(i == L->length)
        return ERROR;
    else{
        return L->elem[i];
    }
}

Status MallocAgain(SqList *L)
{
    //�������Ա�Ĵ���ռ�
    ElemType *p;
    p = (ElemType*)realloc(L->elem,(L->listsize + ENLARGE) * sizeof(ElemType));
    if(!p) exit(OVERFLOW);
    L->elem = p;
    L->listsize += ENLARGE;
    printf("����ռ������䣡");
    return OK;
}
Status ListInsert(SqList *L,int i,ElemType e)
{
    //�����Ա��i��λ��ǰ����e
    int k;
    ElemType *p;
    p = L->elem;
    if(L->length == INITSIZE){
        MallocAgain(&L);
    }
    if(i < 1 || i > L->length + 1){
        printf("����λ�ò���ȷ��");
        return ERROR;
    }
    if(i >= 1 && i <= L->length){       //�Ǳ�β��������
        if(L->length != 0){
            for(k = L->length - 1;k >= i - 1;k--){
                *(p + k + 1) = *(p + k);
            }
        }
    }
    *(p + i - 1) = e;
    L->length = L->length + 1;
    return OK;
}

Status ListDelete(SqList *L,int i)
{
    //ɾ�����Ա��i��Ԫ��
    ElemType *p;
    ElemType e = 0;
    p = L->elem;
    if(EmptyList(L)){
        printf("���Ա�Ϊ�գ��޷����в�����");
        return ERROR;
    }
    e = *(p + i - 1);
    for(int j = i - 1;j < L->length;j++){
        *(p + j) = *(p + j +1);
    }
    L->length--;
    return e;
}

Status ListTraverse(SqList *L)
{
    //����������Ա�Ԫ��
    ElemType e;
    for(int i = 1;i <= L->length;i++){
        printf("%d\n",GetElem(L,i));
    }
    return OK;
}
int main()
{
    SqList *L;
    ElemType e;
    int len;
    ElemType *cur_e;
    InitList(&L);
    ListInsert(&L,1,18);
    ListInsert(&L,1,17);
    ListInsert(&L,1,16);
    ListInsert(&L,1,15);
    ListInsert(&L,1,14);
    len = ListLength(&L);
    for(int i = 1;i <= len;i++){
        printf("%d\n",GetElem(&L,i));
    }
    printf("���Ա��ȣ�%d\n",len);
    printf("*****************************\n");

    printf("ɾ����%d\n",ListDelete(&L,1));
    len = ListLength(&L);
    for(int i = 1;i <= len;i++){
        printf("%d\n",GetElem(&L,i));
    }
    printf("���Ա��ȣ�%d\n",len);
    printf("*****************************\n");

    printf("������Ԫ�ص�ǰ����%d\n",PriorElem(&L,3));
    printf("������Ԫ�صĺ�̣�%d\n",NextElem(&L,3));
    printf("*****************************\n");

    ListTraverse(&L);

    DestroyList(&L);

}
