#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

int calc_char_count(char *string,int count[])
{
    char *p;

    for(p = string; *p != '\0';p ++)
    {
        count[*p] ++;
    }

    return 0;
}

// 1 3 5
//  2
int insert_order_linkqueue(LinkQueue *lq,DATATYPE data)
{
    LinkNode *temp;
    LinkNode *q,*p;
    LinkNode *head = lq->front;

    q = head;
    p = head->next;

    while(p != NULL)
    {
        if(p->data->weight > data->weight)
            break;
        else{
            p = p->next;
            q = q->next;
        }
    }

    temp = (LinkNode *)malloc(sizeof(LinkNode));
    temp->data = data;

    temp->next = q->next;
    q->next    = temp;

    //更新q->rear值,找到尾部节点 
    for(p = head;p->next != NULL;p = p->next);

    lq->rear = p;

    return 0;
}

htree_t *malloc_hnode(char c,int w)
{
    htree_t *tree;

    tree = (htree_t *)malloc(sizeof(htree_t));
    memset(tree,0,sizeof(htree_t));
    tree->c = c;
    tree->weight = w;
    tree->lchild = tree->rchild = NULL;

    return tree;
}

LinkQueue *create_huffman_queue(int count[])
{
    int  i = 0;
    htree_t *tree;
    LinkQueue *q = create_linkqueue();

    for(i = 0;i < 256;i ++)
    {
        if(count[i] != 0){
            tree = malloc_hnode(i,count[i]);
            insert_order_linkqueue(q,tree);
        }
    }

    return q;
}

int is_onenode_linkqueue(LinkQueue *q)
{
    return q->front->next == q->rear ? 1 : 0;
}

htree_t *create_huffman_tree(LinkQueue *q)
{
    /*
     * 思路:
     * ltree = delete_queue(q);
     * rtree  = delete_queue(q);
     * 分配新节点空间,新节点权值是左和右权值相加之后,左右孩子ltree,rtee 
     * 新节点有序进队
     */
    htree_t *root;
    htree_t *ltree;
    htree_t *rtree;
    while (1)
    {
        ltree = delete_linkqueue(q);
        rtree = delete_linkqueue(q);

        root = malloc_hnode(0,(ltree->weight + rtree->weight));
        root->lchild = ltree; 
        root->rchild = rtree; 
        insert_order_linkqueue(q,root); 
        if (is_onenode_linkqueue(q)) 
            break; 
    } 
    return delete_linkqueue(q);

    //出队返回树根节点
}

char *gcode[256];

int Level_Tree(htree_t *root)
{
    DATATYPE tmp;
    LinkQueue *Tree_Lq = create_linkqueue();

    enter_linkqueue(Tree_Lq,root);

    while (!is_empty_linkqueue(Tree_Lq))
    {
        tmp = delete_linkqueue(Tree_Lq);
        
        if (tmp->lchild == NULL && tmp->rchild == NULL)
        {
            gcode[tmp->c] = tmp->code;
            printf("%c : %d : %s\n ",tmp->c,tmp->weight,tmp->code);
        }

        if (tmp->lchild != NULL)
        {
            strcpy(tmp->lchild->code,tmp->code);
            strcat(tmp->lchild->code,"0");
            enter_linkqueue(Tree_Lq,tmp->lchild);
        }

        if (tmp->rchild != NULL)
        {
            strcpy(tmp->rchild->code,tmp->code);
            strcat(tmp->rchild->code,"1");
            enter_linkqueue(Tree_Lq,tmp->rchild);
        }
    }
    return 0;
}

int compress_string(char *buf,char *cbuf)
{
    char *p;
    for(p = buf; *p != '\0'; p++) 
    {
        strcat(cbuf,gcode[*p]);
    }
    return 0;
}

int decompress_string(htree_t *root,char *cbuf)
{
    htree_t *p;
    char *q = cbuf;
    while (*q != '\0')
    {
        p = root;
        while (p->lchild != NULL && p->rchild != NULL)
        {
            if (*q == '0')
            {
                p = p->lchild; 
            }
            else
            {
                p = p->rchild;
            }
            q++;
        }
        printf("%c",p->c);
    }
}

int main(int argc, const char *argv[])
{
    char buf[1024];
    int  count[256] = {0};
    char cbuf[1024] = {0};
    LinkQueue *q;
    htree_t *root;

    /*printf("Input string : ");*/
    scanf("%s",buf);
    /*gets(buf);*/

    calc_char_count(buf,count);

    q = create_huffman_queue(count);

    root = create_huffman_tree(q);

    Level_Tree(root);
    printf("\n");

    compress_string(buf,cbuf);
    printf("compress_string :\n%s\n",cbuf);

    printf("=================\n");
    decompress_string(root,cbuf);
    printf("\n=================\n");
    return 0;

}
