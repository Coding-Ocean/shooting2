#include"libOne.h"
struct BULLET {
    float px, py, vx, vy, advSp=8, ang=0, angSp=0.05f;
    int hp = 0;
};
void gmain() {
    window(1920, 1080,full);
    rectMode(CENTER);
    int pImg = loadImage("assets\\player.png");
    int eImg = loadImage("assets\\enemy.png");
    int pbImg = loadImage("assets\\pBullet.png");
    int ebImg = loadImage("assets\\eBullet.png");
    struct BULLET p;
    p.px = width/2;
    p.py = height/2;
    p.advSp = 2;
    p.ang = 0;
    p.angSp = 0.05f;
    p.vx, p.vy;
    const int numPb = 24;
    struct BULLET pb[numPb];
    int pbTriggerCnt = 0;
    struct BULLET e;
    const int numEb = 24;
    struct BULLET eb[numEb];
    int ebTriggerCnt = 0;


    while (notQuit) {
        //player
        if (isPress(KEY_A))p.ang -= p.angSp;
        if (isPress(KEY_D))p.ang += p.angSp;
        p.vx = sin(p.ang);
        p.vy = -cos(p.ang);
        if (isPress(KEY_W)) {
            p.px += p.vx*p.advSp;
            p.py += p.vy*p.advSp;
        }
        if (isPress(KEY_S)) {
            p.px += -p.vx;
            p.py += -p.vy;
        }
        //enemy
        e.px = width/2 -sin(e.ang) * 420;
        e.py = height/2 -cos(e.ang) * 420;
        e.ang += 0.01f;
        //player bullets
        if (isPress(KEY_SPACE)) {
            if (++pbTriggerCnt % 10 == 1) {
                for (int i = 0; i < numPb; i++) {
                    if (pb[i].hp == 0) {
                        pb[i].hp = 1;
                        pb[i].px = p.px+p.vx*110;
                        pb[i].py = p.py+p.vy*110;
                        pb[i].vx = p.vx;
                        pb[i].vy = p.vy;
                        i = numPb;
                    }
                }
            }
        }
        else {
            pbTriggerCnt = 0;
        }
        for (int i = 0; i < numPb; i++) {
            if (pb[i].hp>0) {
                pb[i].px += pb[i].vx * pb[i].advSp;
                pb[i].py += pb[i].vy * pb[i].advSp;
                pb[i].ang += pb[i].angSp;
                if (pb[i].px<-30 || pb[i].px>width + 30 ||
                    pb[i].py<-30 || pb[i].py>height + 30) {
                    pb[i].hp = 0;
                }
            }
        }
        //enemy bullets
        if (++ebTriggerCnt % 60 == 1) {
            ebTriggerCnt = 1;
            for (int i = 0; i < numEb; i++) {
                if (eb[i].hp == 0) {
                    eb[i].hp = 1;
                    eb[i].px = e.px;
                    eb[i].py = e.py;
                    eb[i].vx = p.px - e.px;
                    eb[i].vy = p.py - e.py;
                    float l = sqrt(eb[i].vx * eb[i].vx + eb[i].vy * eb[i].vy);
                    eb[i].vx /= l;
                    eb[i].vy /= l;
                    i = numEb;
                }
            }
        }
        for (int i = 0; i < numEb; i++) {
            if (eb[i].hp > 0) {
                eb[i].px += eb[i].vx * eb[i].advSp;
                eb[i].py += eb[i].vy * eb[i].advSp;
                eb[i].ang += eb[i].angSp;
                if (eb[i].px<-30 || eb[i].px>width + 30 ||
                    eb[i].py<-30 || eb[i].py>height + 30) {
                    eb[i].hp = 0;
                }
            }
        }

        clear();
        for (int i = 0; i < numPb; i++) {
            if (pb[i].hp>0) {
                image(pbImg, pb[i].px, pb[i].py, pb[i].ang);
            }
        }
        for (int i = 0; i < numEb; i++) {
            if (eb[i].hp > 0) {
                image(ebImg, eb[i].px, eb[i].py);
            }
        }
        image(pImg, p.px, p.py, p.ang);
        image(eImg, e.px, e.py);
        
    }
}
