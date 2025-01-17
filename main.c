#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <pthread.h>
#include "sprite.c"

#define W_WIDTH 648
#define W_HEIGHT 480

char* gDino="000000000000000001111000000011101100000011111100000011110000000011111100000011111100000001110000000001110000000011111100100111110000111111100000011111100000001111000000000101000000";
char* gCactus="110000001101100011011010111110100001101000011110000110000001100000011000";

void* myInp(void* a);

Display* d;
Window win;
bool qPress=false;

int main(){
    d=XOpenDisplay(NULL);
    if(d==NULL){
        printf("[error] cannot connect to X");
    }

    int screen=DefaultScreen(d);
    int width=DisplayWidth(d,screen)/2;
    int height=DisplayHeight(d,screen)/2;

    XFlush(d);
    win=XCreateSimpleWindow(d,RootWindow(d,screen),0,0,W_WIDTH,W_HEIGHT,5,BlackPixel(d,screen),WhitePixel(d,screen));
    XMapWindow(d,win);
    XSelectInput(d,win,KeyPress);
    XSync(d,0);
    XGCValues uwu;

    sprite* list=newSprite(25,W_HEIGHT-140,5,12,gDino);
    addSprite(list,540,W_HEIGHT-140+5*16-9*5,5,8,gCactus);
    addSprite(list,230,W_HEIGHT-140+5*16-9*5,5,8,gCactus);
    addSprite(list,720,W_HEIGHT-140+5*16-9*5,5,8,gCactus);



    uwu.cap_style = CapButt;
    uwu.join_style = JoinBevel;
    GC gc=XCreateGC(d,win,GCCapStyle|GCJoinStyle,&uwu);

    XSetForeground(d,gc,WhitePixel(d,RootWindow(d,screen)));
    XSetBackground(d,gc,BlackPixel(d,RootWindow(d,screen)));

    pthread_t input;
    pthread_create(&input,NULL,myInp,NULL);
    int mode=0;
    while(1){
        sprite* a=list;
        sprite* pre;
        bool prev=false;
        XFillRectangle(d,win,gc,0,W_HEIGHT-140+5*16,1280,1);
        while(a!=NULL){
            if(prev){
                prev=false;
                pre=list;
            }
            int lines=strlen(a->img)/a->width;
            for(int i=0;i<lines;i++){
                for(int j=0;j<a->width;j++){
                    if(a->img[a->width*i+j]=='1')
                        XFillRectangle(d,win,gc,a->x+a->size*j,a->y+a->size*i,a->size,a->size);
                }
            }
            if(!strcmp(gCactus,a->img)){
                a->x-=3;
                if(a->x==0||a->x==-1||a->x==-2)
                    addSprite(list,680+rand()%120,W_HEIGHT-140+5*16-9*5,5,8,gCactus);
                if(a->x<-720){
                    pre->next=a->next;
                    free(a);
                    a=pre;

                }
            }
            if(a==list)
                prev=true;
            a=a->next;
        }
        if(qPress){
            qPress=false;
            if(mode==0)
                mode=1;
        }
        if(mode==1){
            list->y-=5;
            if(list->y<W_HEIGHT-140-130)
                mode=2;
        }
        else if(mode==2){
            list->y+=5;
            if(list->y>W_HEIGHT-140)
                mode=0;
        }
        XSync(d,0);
        usleep((1000*1000)/60);
        XClearWindow(d,win);
    }
    XCloseDisplay(d);
    return 0;
}

void* myInp(void* a){
    XEvent e;
    while(1){
        XNextEvent(d,&e);
        qPress=true;
        printf("KEYPRESS\n");
    }
    return NULL;
}