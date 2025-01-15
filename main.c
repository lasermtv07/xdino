#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include "sprite.c"

#define W_WIDTH 648
#define W_HEIGHT 480
int main(){
    Display* d=XOpenDisplay(NULL);
    if(d==NULL){
        printf("[error] cannot connect to X");
    }
    int screen=DefaultScreen(d);
    int width=DisplayWidth(d,screen)/2;
    int height=DisplayHeight(d,screen)/2;
    XFlush(d);
    Window win=XCreateSimpleWindow(d,RootWindow(d,screen),0,0,W_WIDTH,W_HEIGHT,5,BlackPixel(d,screen),WhitePixel(d,screen));
    XMapWindow(d,win);
    XSync(d,0);
    XGCValues uwu;
    sprite* list=newSprite(25,25,5,5,"011100111001110001000101011111");
    addSprite(list,150,150,15,9,"111111111100000001101000101100000001101111101100000001111111111");
    uwu.cap_style = CapButt;
    uwu.join_style = JoinBevel;
    GC gc=XCreateGC(d,win,GCCapStyle|GCJoinStyle,&uwu);
    XSetForeground(d,gc,WhitePixel(d,RootWindow(d,screen)));
    XSetBackground(d,gc,BlackPixel(d,RootWindow(d,screen)));

    while(1){
        sprite* a=list;
        while(a!=NULL){
            int lines=strlen(a->img)/a->width;
            for(int i=0;i<lines;i++){
                for(int j=0;j<a->width;j++){
                    if(a->img[a->width*i+j]=='1')
                        XFillRectangle(d,win,gc,a->x+a->width*j,a->y+a->width*i,a->width,a->width);
                }
            }
            a=a->next;
        }
        //XFillRectangle(d, win, gc, 60+i, 150, 50, 60);
        XSync(d,0);
        usleep((1000*1000)/60);
        XClearWindow(d,win);
    }
    XCloseDisplay(d);
}