#include <stdlib.h>

typedef struct sprite {
    int x;
    int y;
    int size;
    int width;
    char* img;
    struct sprite* next;
} sprite;

sprite* newSprite(int x,int y,int size,int width,char* img){
    sprite*a=malloc(sizeof(sprite));
    if(a!=NULL){
        a->x=x;
        a->y=y;
        a->size=size;
        a->width=width;
        a->img=img;
        a->next=NULL;
    }
    return a;
}
void addSprite(sprite* a,int x,int y,int size,int width,char* img){
    if(a->next==NULL && a->img==NULL){
        a->x;
        a->y;
        a->size=size;
        a->width=width;
        a->img=img;
        return;
    }
    while(a->next!=NULL){
        a=a->next;
    }
    a->next=newSprite(x,y,size,width,img);
}
