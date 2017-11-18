#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define INITSIZE 100        //线性表储存结构初始分配分量
#define ENLARGE 10          //线性表储存结构分配增量

typedef int Status;
typedef int ElemType;

typedef struct
{
    ElemType *elem;     //线性表基址
    int length;         //线性表长度
    int listsize;       //当前分配的容量
}SqList;

Status InitList(SqList *L)
{
    //构造一个空的线性表
    L->elem = (ElemType*)malloc(INITSIZE * sizeof(ElemType));
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = INITSIZE;
    return OK;
}

Status DestroyList(SqList *L)
{
    //销毁线性表L
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    return OK;
}

Status ClearList(SqList *L)
{
    //将L重置为空表
    free(L->elem);
    L->elem = (ElemType*)malloc(INITSIZE * sizeof(ElemType));
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = INITSIZE;
    return OK;
}

Status EmptyList(SqList *L)
{
    //判断L是否为空表
    if(!L->elem) exit(INFEASIBLE);
    if(L->length == 0) return TRUE;
    else return FALSE;
}

Status ListLength(SqList *L)
{
    //返回线性表L中的元素个数
    return L->length;
}

Status GetElem(SqList *L,int i)
{
    //用e返回线性表L中的第i个值
    ElemType *p = L->elem;
    if(i >= 1 && i <= L->length){
        return *(p + i - 1);
    }
    else return ERROR;
}

Status LocateElem(SqList *L,ElemType e)
{
    //判断线性表中是否存在e
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
    //找线性表中cur_e的前驱
    if(i == 1)
        return ERROR;
    else{
        return L->elem[i - 2];
    }
}

Status NextElem(SqList *L,int i)
{
    //找线性表中cur_e的后继
    if(i == L->length)
        return ERROR;
    else{
        return L->elem[i];
    }
}

Status MallocAgain(SqList *L)
{
    //扩充线性表的储存空间
    ElemType *p;
    p = (ElemType*)realloc(L->elem,(L->listsize + ENLARGE) * sizeof(ElemType));
    if(!p) exit(OVERFLOW);
    L->elem = p;
    L->listsize += ENLARGE;
    printf("储存空间已扩充！");
    return OK;
}
Status ListInsert(SqList *L,int i,ElemType e)
{
    //在线性表第i个位置前插入e
    int k;
    ElemType *p;
    p = L->elem;
    if(L->length == INITSIZE){
        MallocAgain(&L);
    }
    if(i < 1 || i > L->length + 1){
        printf("插入位置不正确！");
        return ERROR;
    }
    if(i >= 1 && i <= L->length){       //非表尾插入的情况
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
    //删除线性表第i个元素
    ElemType *p;
    ElemType e = 0;
    p = L->elem;
    if(EmptyList(L)){
        printf("线性表为空，无法进行操作！");
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
    //遍历输出线性表元素
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
    printf("线性表长度：%d\n",len);
    printf("*****************************\n");

    printf("删除：%d\n",ListDelete(&L,1));
    len = ListLength(&L);
    for(int i = 1;i <= len;i++){
        printf("%d\n",GetElem(&L,i));
    }
    printf("线性表长度：%d\n",len);
    printf("*****************************\n");

    printf("第三个元素的前驱：%d\n",PriorElem(&L,3));
    printf("第三个元素的后继：%d\n",NextElem(&L,3));
    printf("*****************************\n");

    ListTraverse(&L);

    DestroyList(&L);

}
