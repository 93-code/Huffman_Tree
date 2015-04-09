#ifndef _HEAD_H_ 
#define _HEAD_H_ 

#define N 5

typedef struct hnode 
{
    char c;
    int weight;
    char code[256];
    struct hnode *lchild;
    struct hnode *rchild;
}htree_t;

typedef htree_t * DATATYPE;

//链表节点的类型
typedef struct node 
{
    DATATYPE data;
    struct node *next;
}LinkNode;

///////////////////////////////////////////////////////////////////
typedef struct 
{
    LinkNode *front;
    LinkNode *rear;
}LinkQueue;

extern LinkQueue *create_linkqueue();
extern int is_empty_linkqueue(LinkQueue *q);
extern int enter_linkqueue(LinkQueue *q,DATATYPE data);
extern DATATYPE delete_linkqueue(LinkQueue *q);
#endif 
