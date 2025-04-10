#include<bits/stdc++.h>
#include<time.h>

using namespace std;

# include "iGraphics.h"
#pragma comment(lib, "winmm.lib")

#define screenwidth 1000
#define screenheight 600

int mposx,mposy;

int x=50,y=250,flg=1;
int obsx1=200,obsx2=400,obsx3=600,obsx4=800,obsx5=1000,obsx6=1200,obsy1=0,obsy2=450,obsy3=0,obsy4=450,obsy5=0,obsy6=450;
int obs_height=193;
int r=255,g=255,b=255;

char bc[10][20]={"bc\\t.bmp","bc\\bg.bmp","bc\\2.bmp","bc\\3.bmp","bc\\4.bmp","bc\\5.bmp","bc\\6.bmp","bc\\7.bmp","bc\\8.bmp","bc\\9.bmp"};
char bird[8][20]={"bird\\1.bmp","bird\\2.bmp","bird\\3.bmp","bird\\4.bmp","bird\\5.bmp","bird\\6.bmp","bird\\7.bmp","bird\\8.bmp"};
char bird2[8][20]={"bird2\\1.bmp","bird2\\2.bmp","bird2\\3.bmp","bird2\\4.bmp","bird2\\5.bmp","bird2\\6.bmp","bird2\\7.bmp","bird2\\8.bmp"};
char obstacles[2][20]={"obstacle\\1.bmp","obstacle\\2.bmp"};
char home[4][30]={"homepage\\start.bmp","homepage\\settings.bmp","homepage\\more.bmp","homepage\\exit.bmp"};
char obstacles_med[10][100]={"obstacle\\3.bmp","obstacle\\10.bmp","obstacle\\4.bmp","obstacle\\5.bmp","obstacle\\6.bmp","obstacle\\7.bmp","obstacle\\8.bmp","obstacle\\9.bmp"};
char obstacles_hard[10][100]={"obstacle\\21.bmp","obstacle\\22.bmp","obstacle\\23.bmp","obstacle\\24.bmp","obstacle\\25.bmp"};
int oidx1=0,oidx2=1;
int play=0,settings=0,more=0,ext=0,gameover=0,homepage=1;
int birdidx=0;
int bcindex=9;
int green=1;
int red=0;
int birdcolour=0;
int levelpage=0;
int level=1;
int leveldeep=0;
int easy=1,medium=0,hard=0;
int mediumscore=0;
int mediumhighscore;
int hardscore=0;
int hardhighscore;
int obs_height1=342,obs_height3=200,obs_height5=302,obs_height7=250;
int obsx7,obsx8,obsy7,obsy8;
float neg=10;
int hardobsh1=320,hardobsh2=169,hardobsh3=259,hardobsh4=226;
int calculation=0;
int rnd[50]={0};
char name[100];
int name_idx=0;
int howtoplay=0,aboutme=0;
int colordeep=0;
int sound=0,sounddeep=0;
int music=1;
int removenaam=0;

/*void drawHomepage();
void drawEasypage();
void drawGameoverPage();
void collision();
void easyScore();
void easyNewHighScore();*/
int easyhighscore=0;
int easyscore=0;
int easyscr[8];
int mediumscr[6];
int hardscr[6];
int len=0;
char str[100];
bool newScore=true;
int change_called=0;
char copystr[100];
int seeleaderboard=0;
int once=0;
int ldrbrd=0;
int gameoversound=0;
int outofgameover=0;
int savescore=0;
int saved=0;

void removename(){
    while(name_idx>=0) name[name_idx]='\0',name_idx--;
    name_idx=0;
}

void soundcontroller(){
    if(!play && !gameover && music) PlaySound("homepage.wav", NULL, SND_LOOP | SND_ASYNC);
    outofgameover=0;
}

struct Hscore{
    char naam[100];
    int score;
}easyhscore[6],mediumhscore[6],hardhscore[6];

void sort(struct Hscore hscore[],int size){
    for(int i=0;i<size-1;i++){
        int max=hscore[i].score;
        int maxidx=i;
        for(int j=i+1;j<size;j++){
            if(max<hscore[j].score){
                max=hscore[j].score;
                maxidx=j;
            }
        }
        int t=hscore[i].score;
        char temp[100];
        strcpy(temp,hscore[i].naam);
        hscore[i].score=max;
        strcpy(hscore[i].naam,hscore[maxidx].naam);
        hscore[maxidx].score=t;
        strcpy(hscore[maxidx].naam,temp);
    }
}

/*void sort(int a[]){
    for(int i=0;i<5;i++){
        int min=a[i],minidx=i;
        for(int j=i+1;j<6;j++){
            if(min>a[j]){
                min=a[j];
                minidx=j;
            }
        }
        int temp=a[i];
        a[i]=min;
        a[minidx]=temp;
    }
    return;
}*/

void SaveScore(){
    if(easy && once){
        FILE *fp=fopen("easyscore.txt","r+");
        strcpy(easyhscore[5].naam,name);
        easyhscore[5].score=easyscore;
        fseek(fp,0,SEEK_SET);
        for(int i=0;i<5;i++){
            fscanf(fp,"%s %d ",copystr,&easyhscore[i].score);
            strcpy(easyhscore[i].naam,copystr);
            //fscanf(fp,"%d",&easyhscore[i].score);
        }
        sort(easyhscore,6);
        fseek(fp,0,SEEK_SET);
        for(int j=0;j<5;j++){
            fprintf(fp,"%s %d\n",easyhscore[j].naam,easyhscore[j].score);
        }
        fclose(fp);
        once = 0;
    }
    if(medium && once){
        FILE *fpm=fopen("mediumscore.txt","r+");
        strcpy(mediumhscore[5].naam,name);
        mediumhscore[5].score=mediumscore;
        fseek(fpm,0,SEEK_SET);
        for(int i=0;i<5;i++){
            fscanf(fpm,"%s %d ",copystr,&mediumhscore[i].score);
            strcpy(mediumhscore[i].naam,copystr);
            //fscanf(fp,"%d",&easyhscore[i].score);
        }
        sort(mediumhscore,6);
        fseek(fpm,0,SEEK_SET);
        for(int j=0;j<5;j++){
            fprintf(fpm,"%s %d\n",mediumhscore[j].naam,mediumhscore[j].score);
        }
        fclose(fpm);
        once = 0;
    }
    if(hard && once){
        FILE *fph=fopen("hardscore.txt","r+");
        strcpy(hardhscore[5].naam,name);
        hardhscore[5].score=hardscore;
        fseek(fph,0,SEEK_SET);
        for(int i=0;i<5;i++){
            fscanf(fph,"%s %d ",copystr,&hardhscore[i].score);
            strcpy(hardhscore[i].naam,copystr);
            //fscanf(fp,"%d",&easyhscore[i].score);
        }
        sort(hardhscore,6);
        fseek(fph,0,SEEK_SET);
        for(int j=0;j<5;j++){
            fprintf(fph,"%s %d\n",hardhscore[j].naam,hardhscore[j].score);
        }
        fclose(fph);
        once = 0;
    }
}

void drawMorePage(){
    iShowBMP(0,0,"bc\\more.bmp");
    iShowBMP2(200,100,"bc\\more_button.bmp",0);
    iSetColor(000,0,100);
    iText(248,322,"How to play ?",GLUT_BITMAP_HELVETICA_18);
    iText(230,255,"See Leaderboard",GLUT_BITMAP_HELVETICA_18);
    iText(260,193,"About me",GLUT_BITMAP_HELVETICA_18);
    iText(280,133,"Back",GLUT_BITMAP_HELVETICA_18);
}

void drawLeaderboardPage(){
    iShowBMP(0,0,"bc\\leaderboard.bmp");
    iShowBMP2(750,100,"bc\\back.bmp",0);
    iText(772,128,"Back to home",GLUT_BITMAP_HELVETICA_18);
    if(easy && once){
        FILE *fp=fopen("easyscore.txt","r+");
        strcpy(easyhscore[5].naam,name);
        easyhscore[5].score=easyscore;
        fseek(fp,0,SEEK_SET);
        for(int i=0;i<5;i++){
            fscanf(fp,"%s %d ",copystr,&easyhscore[i].score);
            strcpy(easyhscore[i].naam,copystr);
            //fscanf(fp,"%d",&easyhscore[i].score);
        }
        sort(easyhscore,6);
        fseek(fp,0,SEEK_SET);
        for(int j=0;j<5;j++){
            fprintf(fp,"%s %d\n",easyhscore[j].naam,easyhscore[j].score);
        }
        fclose(fp);
        once = 0;
    }
    if(easy){
        FILE *fp=fopen("easyscore.txt","r+");
        fseek(fp,0,SEEK_SET);
        iText(425,480,"Easy Leaderboard",GLUT_BITMAP_HELVETICA_18);
        iFilledRectangle(380,470,230,3);
        for(int i=0;i<5;i++){
            fscanf(fp,"%s",copystr);
            strcat(copystr," : ");
            int kichuekta;
            fscanf(fp,"%d",&kichuekta);
            sprintf(str,"%d",kichuekta);
            strcat(copystr,str);
            iSetColor(0,0,0);
            char merit[10];
            merit[0]=i+1+'0';
            merit[1]='-';
            merit[2]='>';
            merit[3]='\0';
            iText(400,430-i*40,merit,GLUT_BITMAP_HELVETICA_18);
            iText(435,430-i*40,copystr,GLUT_BITMAP_HELVETICA_18);
        }
        fclose(fp);
    }
    if(medium && once){
        FILE *fpm=fopen("mediumscore.txt","r+");
        strcpy(mediumhscore[5].naam,name);
        mediumhscore[5].score=mediumscore;
        fseek(fpm,0,SEEK_SET);
        for(int i=0;i<5;i++){
            fscanf(fpm,"%s %d ",copystr,&mediumhscore[i].score);
            strcpy(mediumhscore[i].naam,copystr);
            //fscanf(fp,"%d",&easyhscore[i].score);
        }
        sort(mediumhscore,6);
        fseek(fpm,0,SEEK_SET);
        for(int j=0;j<5;j++){
            fprintf(fpm,"%s %d\n",mediumhscore[j].naam,mediumhscore[j].score);
        }
        fclose(fpm);
        removename();
        once = 0;
    }
    if(medium){
        FILE *fpm=fopen("mediumscore.txt","r+");
        iText(415,480,"Medium Leaderboard",GLUT_BITMAP_HELVETICA_18);
        iFilledRectangle(380,470,230,3);
        fseek(fpm,0,SEEK_SET);
        for(int i=0;i<5;i++){
            fscanf(fpm,"%s",copystr);
            strcat(copystr," : ");
            int kichuekta;
            fscanf(fpm,"%d",&kichuekta);
            sprintf(str,"%d",kichuekta);
            strcat(copystr,str);
            iSetColor(0,0,0);
            char merit[10];
            merit[0]=i+1+'0';
            merit[1]='-';
            merit[2]='>';
            merit[3]='\0';
            iText(400,430-i*40,merit,GLUT_BITMAP_HELVETICA_18);
            iText(435,430-i*40,copystr,GLUT_BITMAP_HELVETICA_18);
        }
        fclose(fpm);
    }
    if(hard && once){
        FILE *fph=fopen("hardscore.txt","r+");
        strcpy(hardhscore[5].naam,name);
        hardhscore[5].score=hardscore;
        fseek(fph,0,SEEK_SET);
        for(int i=0;i<5;i++){
            fscanf(fph,"%s %d ",copystr,&hardhscore[i].score);
            strcpy(hardhscore[i].naam,copystr);
            //fscanf(fp,"%d",&easyhscore[i].score);
        }
        sort(hardhscore,6);
        fseek(fph,0,SEEK_SET);
        for(int j=0;j<5;j++){
            fprintf(fph,"%s %d\n",hardhscore[j].naam,hardhscore[j].score);
        }
        fclose(fph);
        once = 0;
    }
    if(hard){
        FILE *fph=fopen("hardscore.txt","r+");
        iText(425,480,"Hard Leaderboard",GLUT_BITMAP_HELVETICA_18);
        iFilledRectangle(380,470,230,3);
        fseek(fph,0,SEEK_SET);
        for(int i=0;i<5;i++){
            fscanf(fph,"%s",copystr);
            strcat(copystr," : ");
            int kichuekta;
            fscanf(fph,"%d",&kichuekta);
            sprintf(str,"%d",kichuekta);
            strcat(copystr,str);
            iSetColor(0,0,0);
            char merit[10];
            merit[0]=i+1+'0';
            merit[1]='-';
            merit[2]='>';
            merit[3]='\0';
            iText(400,430-i*40,merit,GLUT_BITMAP_HELVETICA_18);
            iText(435,430-i*40,copystr,GLUT_BITMAP_HELVETICA_18);
        }
        fclose(fph);
    }
    removenaam=1;
}

void easyScore(){
    FILE *fp=fopen("easyscore.txt","r+");
    sprintf(str,"Your score : %d",easyscore);
    iText(350,200,str, GLUT_BITMAP_HELVETICA_18);
    iText(350,100,"See Leaderboard",GLUT_BITMAP_HELVETICA_18);
    strcpy(easyhscore[5].naam,name);
    easyhscore[5].score=easyscore;
    fseek(fp,0,SEEK_SET);
    for(int i=0;i<5;i++){
        fscanf(fp,"%s",copystr);
        strcpy(easyhscore[i].naam,copystr);
        fscanf(fp,"%d",&easyhscore[i].score);
    }
    sort(easyhscore,6);
    /*if(calculation){
        fseek(fp,0,SEEK_SET);
        for(int j=1;j<6;j++){
            fprintf(fp,"%s %d ",easyhscore[j].naam,easyhscore[j].score);
        }
    }*/
    calculation=0;
    easyhighscore=easyhscore[0].score;
    if(easyhighscore<easyscore) easyhighscore=easyscore;
    sprintf(str,"High score : %d",easyhighscore);
    iText(350,170,str, GLUT_BITMAP_HELVETICA_18);
    fclose(fp);
}

void mediumScore(){
    FILE *fpm=fopen("mediumscore.txt","r+");
    sprintf(str,"Your score : %d",mediumscore);
    iText(350,200,str, GLUT_BITMAP_HELVETICA_18);
    iText(350,100,"See Leaderboard",GLUT_BITMAP_HELVETICA_18);
    strcpy(mediumhscore[5].naam,name);
    mediumhscore[5].score=mediumscore;
    fseek(fpm,0,SEEK_SET);
    for(int i=0;i<5;i++){
        fscanf(fpm,"%s",copystr);
        strcpy(mediumhscore[i].naam,copystr);
        fscanf(fpm,"%d",&mediumhscore[i].score);
    }
    sort(mediumhscore,6);
    /*if(calculation){
        fseek(fp,0,SEEK_SET);
        for(int j=1;j<6;j++){
            fprintf(fp,"%s %d ",easyhscore[j].naam,easyhscore[j].score);
        }
    }*/
    calculation=0;
    mediumhighscore=mediumhscore[0].score;
    if(mediumhighscore<mediumscore) mediumhighscore=mediumscore;
    sprintf(str,"High score : %d",mediumhighscore);
    iText(350,170,str, GLUT_BITMAP_HELVETICA_18);
    fclose(fpm);
}

void hardScorePage(){
    FILE *fph=fopen("hardscore.txt","r+");
    sprintf(str,"Your score : %d",hardscore);
    iText(350,200,str, GLUT_BITMAP_HELVETICA_18);
    iText(350,100,"See Leaderboard",GLUT_BITMAP_HELVETICA_18);
    strcpy(hardhscore[5].naam,name);
    hardhscore[5].score=hardscore;
    fseek(fph,0,SEEK_SET);
    for(int i=0;i<5;i++){
        fscanf(fph,"%s",copystr);
        strcpy(hardhscore[i].naam,copystr);
        fscanf(fph,"%d",&hardhscore[i].score);
    }
    sort(hardhscore,6);
    /*if(calculation){
        fseek(fp,0,SEEK_SET);
        for(int j=1;j<6;j++){
            fprintf(fp,"%s %d ",easyhscore[j].naam,easyhscore[j].score);
        }
    }*/
    calculation=0;
    hardhighscore=hardhscore[0].score;
    if(hardhighscore<hardscore) hardhighscore=hardscore;
    sprintf(str,"High score : %d",hardhighscore);
    iText(350,170,str, GLUT_BITMAP_HELVETICA_18);
    fclose(fph);
}

void drawDeepLevelPage(){
    iShowBMP(0,0,"settings\\leveltogame.bmp");
    iShowBMP2(750,100,"settings\\colour.bmp",0);
    iText(765,130,"Play now",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(765,200,"Go to Menu",GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawLevelPage(){
    iShowBMP(0,0,"settings\\levelbg.bmp");
    iShowBMP2(200,280,"settings\\levelwrite.bmp",0);
    iSetColor(0,0,0);
    iText(250,320,"Select Level ",GLUT_BITMAP_TIMES_ROMAN_24);
    iShowBMP2(150,100,"settings\\level1.bmp",0);
}

void drawSettingsPage(){
    iClear();
    iShowBMP(0,0,"settings\\bg.bmp");
    iShowBMP2(500,50,"settings\\main.bmp",0);
    iText(680,418, "Level", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(680,110, "Back", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(680,320,"Sound", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(680,210,"Bird Colour", GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawBirdColourPage(){
    iShowBMP(0,0,"settings\\colourhome.bmp");
    iShowBMP2(400,400,"settings\\clr.bmp",0);
    iShowBMP2(630,250,"settings\\colour.bmp",0);
    iSetColor(200,100,200);
    iText(650,280,"Red", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(650,350,"Green", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(470,470,"Select Bird Colour", GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawColordeepPage(){
    iShowBMP(0,0,"bc\\deepcolor.bmp");
    iShowBMP2(380,250,"bc\\dpclr.bmp",0);
    iSetColor(50,50,50);
    iText(400,340,"Play now",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(400,270,"Go to home",GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawSoundPage(){
    iShowBMP(0,0,"bc\\sound.bmp");
    iShowBMP2(630,150,"settings\\colour.bmp",0);
    iSetColor(200,100,200);
    iText(650,180,"Music Off", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(650,250,"Music On", GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawSounddeepPage(){
    iShowBMP(0,0,"bc\\sounddeep.bmp");
    iShowBMP2(380,250,"bc\\dpclr.bmp",0);
    iSetColor(50,50,50);
    iText(400,340,"Play now",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(400,270,"Go to home",GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawHomepage(){
    iShowBMP(0,0,"homepage\\home2.bmp");
    iShowBMP2(285,450,"homepage\\flpy.bmp",0);
    iShowBMP2(100,325,home[0],0);
    iShowBMP2(100,250,home[1],0);
    iShowBMP2(100,175,home[2],0);
    iShowBMP2(100,100,home[3],0);
    iSetColor(255,255,255);
    iText(700,100, "By Fajrin Anjum Thuja", GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawEasypage(){
    iShowBMP(0,0,"bc\\15.bmp");
    
    if(flg){
        if(green) iShowBMP2(x,y,bird[7],0);
        else iShowBMP2(x,y,bird2[7],0);
        obsx1=400,obsx2=600,obsx3=800,obsx4=1000,obsx5=1200,obsx6=1400,obsy1=150,obsy2=450,obsy3=150,obsy4=450,obsy5=150,obsy6=450;
        for(int i=0;i<50;i++){
            rnd[i]=20*i;
        }
        if(music){
            PlaySound(0,0,0);
            PlaySound("play.wav", NULL, SND_LOOP | SND_ASYNC);
        }
        removename();
        easyscore=0;
    }
    else{
        if(green) iShowBMP2(x,y,bird[birdidx],0);
        else iShowBMP2(x,y,bird2[birdidx],0);
    }
        iShowBMP2(obsx1,obsy1,obstacles[oidx1],0);
        iShowBMP2(obsx2,obsy2,obstacles[oidx2],0);
        iShowBMP2(obsx3,obsy3,obstacles[oidx1],0);
        iShowBMP2(obsx4,obsy4,obstacles[oidx2],0);
        iShowBMP2(obsx5,obsy5,obstacles[oidx1],0);
        iShowBMP2(obsx6,obsy6,obstacles[oidx2],0);
        for(int i=0;i<50;i++){
            iShowBMP(rnd[i],0,"bc\\rend.bmp");
        }
        //iShowBMP2(0,0,"bc\\floor.bmp",255);
        sprintf(str,"Score : %d",easyscore);
        if(play) iText(10,570,str, GLUT_BITMAP_HELVETICA_18);
}

void drawMediumPage(){
    iShowBMP(0,0,"bc\\10.bmp");
    if(flg){
        obsx1=350;
        obsx2=500;
        obsx3=650;
        obsx4=800;
        obsx5=950;
        obsx6=1100;
        obsx7=1250;
        obsx8=1400;
        obsy1=0;
        obsy3=0;
        obsy5=0;
        obsy7=0;
        srand(NULL);
        obsy2=400+rand()%100;
        obsy4=400+rand()%100;
        obsy6=400+rand()%50;
        obsy8=400+rand()%70;
        if(green) iShowBMP2(x,y,bird[7],0);
        else iShowBMP2(x,y,bird2[7],0);
        if(music){
            PlaySound(0,0,0);
            PlaySound("play.wav", NULL, SND_LOOP | SND_ASYNC);
        }
        mediumscore=0;
        removename();
    }
    else{
        if(green) iShowBMP2(x,y,bird[birdidx],0);
        else iShowBMP2(x,y,bird2[birdidx],0);
    }
        iShowBMP2(obsx1,obsy1,obstacles_med[0],0);
        iShowBMP2(obsx2,obsy2,obstacles_med[7],0);
        iShowBMP2(obsx3,obsy3,obstacles_med[1],0);
        iShowBMP2(obsx4,obsy4,obstacles_med[7],0);
        iShowBMP2(obsx5,obsy5,obstacles_med[2],0);
        iShowBMP2(obsx6,obsy6,obstacles_med[7],0);
        iShowBMP2(obsx7,obsy7,obstacles_med[3],0);
        iShowBMP2(obsx8,obsy8,obstacles_med[7],0);
        sprintf(str,"Score : %d",mediumscore);
        if(play) iText(10,570,str, GLUT_BITMAP_HELVETICA_18);
}

void drawHardPage(){
    iShowBMP(0,0,"bc\\12.bmp");
    if(flg){
        obsx1=200;
        obsx2=350;
        obsx3=500;
        obsx4=650;
        obsx5=800;
        obsx6=950;
        obsx7=1100;
        obsx8=1250;
        obsy1=0;
        obsy3=0;
        obsy5=0;
        obsy7=0;
        srand(NULL);
        obsy2=400+rand()%100;
        obsy4=350+rand()%100;
        obsy6=350+rand()%50;
        obsy8=350+rand()%70;
        if(green) iShowBMP2(x,y,bird[7],0);
        else iShowBMP2(x,y,bird2[7],0);
        if(music){
            PlaySound(0,0,0);
            PlaySound("play.wav", NULL, SND_LOOP | SND_ASYNC);
        }
        hardscore=0;
        removename();
    }
    else{
        if(green) iShowBMP2(x,y,bird[birdidx],0);
        else iShowBMP2(x,y,bird2[birdidx],0);
    }
        iShowBMP2(obsx1,obsy1,obstacles_hard[0],0);
        iShowBMP2(obsx2,obsy2,obstacles_hard[4],0);
        iShowBMP2(obsx3,obsy3,obstacles_hard[1],0);
        iShowBMP2(obsx4,obsy4,obstacles_hard[4],0);
        iShowBMP2(obsx5,obsy5,obstacles_hard[2],0);
        iShowBMP2(obsx6,obsy6,obstacles_hard[4],0);
        iShowBMP2(obsx7,obsy7,obstacles_hard[3],0);
        iShowBMP2(obsx8,obsy8,obstacles_hard[4],0);
        sprintf(str,"Score : %d",hardscore);
        if(play) iText(10,570,str, GLUT_BITMAP_HELVETICA_18);
}

void drawGameoverPage(){
    if(music){
        //PlaySound(0,0,0);
        if(gameoversound) PlaySound("gameover.wav", NULL, SND_LOOP | SND_ASYNC);
    }
    iShowBMP(0,0,"game_over\\bg.bmp");
    iShowBMP2(430,400,"game_over\\dead.bmp",0);
    /*iShowBMP2(430,190,"game_over\\menu.bmp",0);
    iShowBMP2(430,120,"game_over\\restart.bmp",0);
    iShowBMP2(430,50,"game_over\\exit.bmp",0);*/
    iShowBMP2(300,10,"game_over\\new.bmp",0);
    iText(480,30,"Exit",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(613,125,"Restart",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(618,195, "Menu" , GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255,255,255);
    iFilledRectangle(250,240,500,40);
    iSetColor(0,0,0);
    iText(260,250,"Enter your name : ",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(450,250,name,GLUT_BITMAP_TIMES_ROMAN_24);
    iText(350,135,"Save your score",GLUT_BITMAP_HELVETICA_18);
    gameoversound=0;
}

void drawSavescorePage(){
    iShowBMP(0,0,"bc\\saved.bmp");
    iShowBMP2(750,100,"settings\\colour.bmp",0);
    iText(765,130,"Restart",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(765,200,"Go to Menu",GLUT_BITMAP_TIMES_ROMAN_24);
}

/*void drawObstacles()
{
	iShowBMP2(x1, y1, "obstacle\\1.bmp", 0);
	iShowBMP2(x2, y2, "obstacle\\2.bmp", 0);
	iShowBMP2(x3, y3, "obstacle\\1.bmp", 0);
	iShowBMP2(x4, y4, "obstacle\\2.bmp", 0);
	iShowBMP2(x5, y5, "obstacle\\1.bmp", 0);
	iShowBMP2(x6, y6, "obstacle\\2.bmp", 0);
}*/

void drawHowtoplayPage(){
    iShowBMP(0,0,"bc\\howtoplay.bmp");
    iShowBMP2(800,100,"bc\\back.bmp",0);
    iSetColor(0,0,0);
    iText(850,125,"Back",GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(250,250,250);
    iText(380,500,"About My Flappy Bird",GLUT_BITMAP_TIMES_ROMAN_24);
    iFilledRectangle(340,480,300,3);
    iText(100,400,"Tap carefully to raise the bird up and navigate through the gaps in the green pipes without crashing.",GLUT_BITMAP_HELVETICA_18);
    iText(100,370,"For overtaking every obstacles, your score will be updated. Score will be incremented accoding to level",GLUT_BITMAP_HELVETICA_18);
    iText(100,340,"For easy level, score will be incremented by 1 for each obstcales. For medium, score will be incremeted",GLUT_BITMAP_HELVETICA_18);
    iText(100,310,"by 2 and for hard,score will be incremented by 3 for each obstacles",GLUT_BITMAP_HELVETICA_18);
    iText(100,270,"How to fly the bird : ",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(200,230,"1) Press left mouse button",GLUT_BITMAP_HELVETICA_18);
    iText(200,200,"2) Press space bar",GLUT_BITMAP_HELVETICA_18);
    iText(200,170,"3) Press up button",GLUT_BITMAP_HELVETICA_18);

}

void drawLdrbrdPage(){
    iShowBMP(0,0,"bc\\ldrbrd.bmp");
    iShowBMP2(380,200,"bc\\more_button.bmp",0);
    iText(410,420,"Hard Leaderboard",GLUT_BITMAP_HELVETICA_18);
    iText(395,355,"Medium Leaderboard",GLUT_BITMAP_HELVETICA_18);
    iText(410,292,"Easy Leaderboard",GLUT_BITMAP_HELVETICA_18);
    iText(460,227,"Back",GLUT_BITMAP_HELVETICA_18);
}

void drawAboutmePage(){
    iShowBMP(0,0,"bc\\aboutme.bmp");
    iShowBMP2(800,100,"bc\\back.bmp",0);
    iText(850,125,"Back",GLUT_BITMAP_TIMES_ROMAN_24);
    iShowBMP2(100,270,"bc\\thuja.bmp",0);
    iText(80,210,"Hey... I am Fajrin Anjum Thuja. I am a student of computer science and engineering at Bangladesh ",GLUT_BITMAP_HELVETICA_18);
    iText(80,180,"University of Engineering and Technology. This is my level 1 term 1 project and also my first project.",GLUT_BITMAP_HELVETICA_18);
    iText(80,150,"Hope you enjoy the game.",GLUT_BITMAP_HELVETICA_18);
}

/*void playmusichome(char *musichome){
    if(homepage && music){
            PlaySound(musichome, NULL, SND_LOOP | SND_ASYNC);
    }
    else PlaySound(0,0,0);
}*/

void iDraw(){
    //code
    iClear();
    if(homepage){
        drawHomepage();
    }
    if(play){
        if(easy) drawEasypage();
        if(medium){
            drawMediumPage();
        }
        if(hard) drawHardPage();
    }
    if(settings) drawSettingsPage();
    if(gameover && !levelpage && !leveldeep){
        drawGameoverPage();
        if(easy) easyScore();
        if(medium) mediumScore();
        if(hard) hardScorePage();
    }
    if(howtoplay) drawHowtoplayPage();
    if(aboutme) drawAboutmePage();
    if(more) drawMorePage();
    if(seeleaderboard) drawLeaderboardPage();
    if(ldrbrd) drawLdrbrdPage();
    if(levelpage) drawLevelPage();
    if(sound) drawSoundPage();
    if(sounddeep) drawSounddeepPage();
    if(birdcolour) drawBirdColourPage();
    if(leveldeep) drawDeepLevelPage();
    if(colordeep) drawColordeepPage();
    if(outofgameover){
        //removename();
        soundcontroller();
    }
    if(removenaam){
        removename();
        removenaam=0;
    }
    if(savescore){
        SaveScore();
        drawSavescorePage();
    }
    
    //drawObstacles();
}

void iMouseMove(int mx,int my){
    //code
}

void iMouse(int button,int state,int mx,int my){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(play) y+=100;
        if(play) flg=0;
        if(play) gameover=0;
    }  
    if(mx>=100 && mx<=250 && my>=325 && my<=375 && homepage) play=1,homepage=0;
    else if(mx>=100 && mx<=250 && my>=250 && my<=300 && homepage) settings=1,homepage=0;
    else if(mx>=100 && mx<=250 && my>=175 && my<=225 && homepage) more=1,homepage=0;
    else if(mx>=100 && mx<=250 && my>=100 && my<=150 && homepage) exit(0);
    else if(mx>=600 && mx<=950 && my>=90 && my<= 150 && settings) settings=0,homepage=1;
    else if(mx>=600 && mx<=950 && my>=200 && my<= 260 && settings) birdcolour=1,settings=0;
    else if(mx>=600 && mx<=950 && my>=400 && my<= 450 && settings) levelpage=1,play=0,flg=1,settings=0;
    else if(mx>=600 && mx<=950 && my>=310 && my<= 370 && settings) settings=0,sound=1;
    if(mx>=180 && mx<=350 && my>=100 && my<=260 && levelpage){
        leveldeep=1;
        easy=1;
        medium=0;
        hard=0;
        levelpage=0;
    }
    if(mx>=420 && mx<=580 && my>=100 && my<=260 && levelpage){
        leveldeep=1;
        medium=1;
        play=0;
        flg=1;
        easy=0;
        hard=0;
        levelpage=0;
    }
    if(mx>=600 && mx<=750 && my>=100 && my<=260 && levelpage){
        leveldeep=1;
        gameover=0;
        levelpage=0;
        easy=0;
        medium=0;
        hard=1;
    }
    if(mx>=750 && mx<= 850 && my>=180 && my<=250 && leveldeep){
        leveldeep=0;
        gameover=0;
        flg=1;
        play=0;
        homepage=1;
    }
    if(mx>=750 && mx<= 850 && my>=100 && my<=170 && leveldeep){
        leveldeep=0;
        gameover=0;
        flg=1;
        play=1;
    }
    if(gameover){
        if(mx>=610 && mx<=700 && my>=165 && my<=230){
            play=0;
            gameover=0;
            homepage=1;
            easyscore=0;
            mediumscore=0;
            outofgameover=1;
        }
        if(mx>=610 && mx<=680 && my>=70 && my<=150) homepage=0,gameover=0,play=1,easyscore=0,mediumscore=0,hardscore=0,outofgameover=1;
        if(mx>=300 && mx<=500 && my>=90 && my<=120) gameover=0,seeleaderboard=1,once=1,outofgameover=1;
        if(mx>=300 && mx<=500 && my>=130 && my<=160) savescore=1,once=1,gameover=0,outofgameover=1;
        if(mx>=300 && mx<=700 && my>=20 && my<=70) exit(0);
    }
    if(more){
        if(mx>=200 && mx<=450 && my>=300 && my<=350) more=0,howtoplay=1;
        if(mx>=200 && mx<=450 && my>=230 && my<=280) more=0, ldrbrd=1;
        if(mx>=230 && mx<=450 && my>=180 && my<=230) more=0, aboutme=1;
        if(mx>=200 && mx<=450 && my>=120 && my<=160) more=0, homepage=1;
    }
    if(mx>=800 && mx<=950 && my>=110 && my<=150 && aboutme) more=1,aboutme=0;
    if(mx>=800 && mx<=950 && my>=110 && my<=150 && howtoplay) more=1,howtoplay=0;
    if(ldrbrd){
        if(mx>=390 && mx<=530 && my>=400 && my<=450) easy=0,medium=0,hard=1,ldrbrd=0,seeleaderboard=1;
        if(mx>=390 && mx<=530 && my>=340 && my<=380) easy=0,medium=1,hard=0,ldrbrd=0,seeleaderboard=1;
        if(mx>=390 && mx<=530 && my>=280 && my<=320) easy=1,medium=0,hard=0,ldrbrd=0,seeleaderboard=1;
        if(mx>=390 && mx<=530 && my>=210 && my<=270) easy=1,medium=0,hard=0,more=1,ldrbrd=0;
    }
    if(birdcolour){
        if(mx>=600 && mx<=750 && my>=330 && my<=380) colordeep=1,birdcolour=0,green=1,red=0;
        if(mx>=600 && mx<=750 && my>=250 && my<=310) colordeep=1,birdcolour=0,green=0,red=1;
    }
    if(colordeep){
        if(mx>=380 && mx<=600 && my>=320 && my<=380) colordeep=0,play=1;
        if(mx>=380 && mx<=600 && my>=250 && my<=300) colordeep=0,homepage=1;
    }
    if(sound){
        if(mx>=600 && mx<=750 && my>=230 && my<=280){
            sounddeep=1,music=1,sound=0;
            if(!play) PlaySound("homepage.wav", NULL, SND_LOOP | SND_ASYNC);
            if(play){
                PlaySound(0,0,0);
                PlaySound("play.wav", NULL, SND_LOOP | SND_ASYNC);
            }
        }
        if(mx>=600 && mx<=750 && my>=150 && my<=210){
            sounddeep=1,music=0,sound=0;
            PlaySound(0,0,0);
        }
    }
    if(sounddeep){
        if(mx>=380 && mx<=600 && my>=320 && my<=380) sounddeep=0,play=1;
        if(mx>=380 && mx<=600 && my>=250 && my<=300) sounddeep=0,homepage=1;
    }
    if(seeleaderboard){
        if(mx>=750 && mx<=900 && my>=110 && my<=140) easy=1,medium=0,hard=0,homepage=1,seeleaderboard=0,gameover=0;
    }
    if(savescore){
        if(mx>=750 && mx<= 850 && my>=100 && my<=170) savescore=0,play=1;
        if(mx>=750 && mx<= 850 && my>=180 && my<=250) savescore=0,homepage=1;
    }
}

void iKeyboard(unsigned char key){
    if(key==' ' && play){
        y+=100;
        flg=0;
    }
    if(gameover){
        if(key=='\r') name[name_idx]='\0';
        else if(key=='\b'){
            if(name_idx<0) name_idx=0;
            else{
                name[name_idx]='\0';
                name_idx--;
            }
        }
        else{
            name[name_idx]=key;
            name_idx++;
        }
    }
}

void iSpecialKeyboard(unsigned char key){
    if (key == GLUT_KEY_UP) y+=100;
}

void collision(){
    if(easy){
        if(y<=obsy1+obs_height && obsx1<=50+81 && obsx1+83>=50) gameover=1,flg=1,play=0,calculation=1,removename(),gameoversound=1;
        if(y<=obsy3+obs_height && obsx3<=50+81 && obsx3+83>=50) gameover=1,flg=1,play=0,calculation=1,removename(),gameoversound=1;
        if(y<=obsy5+obs_height && obsx5<=50+81 && obsx5+83>=50) gameover=1,flg=1,play=0,calculation=1,removename(),gameoversound=1;
        if(y>=obsy2-10 && obsx2<=50+81 && obsx2+83>=50) gameover=1,flg=1,play=0,calculation=1,removename(),gameoversound=1;
        if(y>=obsy4-10 && obsx4<=50+81 && obsx4+83>=50) gameover=1,flg=1,play=0,calculation=1,removename(),gameoversound=1;
        if(y>=obsy6-10 && obsx6<=50+81 && obsx6+83>=50) gameover=1,flg=1,play=0,calculation=1,removename(),gameoversound=1;
        if(y>600 || y<150) gameover=1,y=250,flg=1,play=0,removename(),gameoversound=1;
        if(gameover){
            y=250;
            obsx1=200;
            obsx2=400;
            obsx3=600;
            obsx4=800;
            obsx5=1000;
            obsx6=1200;
            obsy1=150;
            obsy2=400;
            obsy3=150;
            obsy4=400;
            obsy5=150;
            obsy6=400;
        }
    }
    if(medium){
        if(y<=obsy1+obs_height1 && obsx1<=50+81 && obsx1+81>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
        if(y<=obsy3+obs_height3 && obsx3<=50+81 && obsx3+81>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
        if(y<=obsy5+obs_height5 && obsx5<=50+81 && obsx5+81>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
        if(y<=obsy7+obs_height7 && obsx7<=50+81 && obsx7+81>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
        if(y>=obsy2-10 && obsx2<=50+81 && obsx2+81>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
        if(y>=obsy4-10 && obsx4<=50+81 && obsx4+81>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
        if(y>=obsy6-10 && obsx6<=50+81 && obsx6+81>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
        if(y>=obsy8-10 && obsx8<=50+81 && obsx8+81>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
        if(y>600 || y<0) gameover=1,y=250,flg=1,play=0,gameoversound=1;
        if(gameover){
            if(easy){
                y=250;
                obsx1=200;
                obsx2=400;
                obsx3=600;
                obsx4=800;
                obsx5=1000;
                obsx6=1200;
                obsy1=0;
                obsy2=400;
                obsy3=0;
                obsy4=400;
                obsy5=0;
                obsy6=400;
            }
            if(medium){
                y=250;neg=10;
                obsx1=200;
                obsx2=350;
                obsx3=500;
                obsx4=650;
                obsx5=800;
                obsx6=950;
                obsx7=1100;
                obsx8=1250;
                srand(0);
                obsy2=400+rand()%100;
                obsy4=350+rand()%100;
                obsy6=350+rand()%50;
                obsy8=380+rand()%70;
            }
        }
    }
        if(hard){
            if(y<=obsy1+hardobsh1 && obsx1<=50+80 && obsx1+80>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
            if(y<=obsy3+hardobsh2 && obsx3<=50+80 && obsx3+80>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
            if(y<=obsy5+hardobsh3 && obsx5<=50+80 && obsx5+80>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
            if(y<=obsy7+hardobsh4 && obsx7<=50+80 && obsx7+80>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
            if(y>=obsy2-10 && obsx2<=50+80 && obsx2+80>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
            if(y>=obsy4-10 && obsx4<=50+80 && obsx4+80>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
            if(y>=obsy6-10 && obsx6<=50+80 && obsx6+80>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
            if(y>=obsy8-10 && obsx8<=50+80 && obsx8+80>=50) gameover=1,flg=1,play=0,calculation=1,gameoversound=1;
            if(y>600 || y<0) gameover=1,y=250,flg=1,play=0,gameoversound=1;
            if(gameover){
                y=250;neg=10;
                obsx1=200;
                obsx2=350;
                obsx3=500;
                obsx4=650;
                obsx5=800;
                obsx6=950;
                obsx7=1100;
                obsx8=1250;
                srand(0);
                obsy2=400+rand()%100;
                obsy4=250+rand()%100;
                obsy6=350+rand()%50;
                obsy8=380+rand()%70;
            }
        }
}
    
void change(){
    if(easy){
        if(!flg && !gameover && play) y-=20;
        birdidx++;
        if(birdidx>7) birdidx=0;
        if(!flg){
            obsx1-=10;
            obsx2-=10;
            obsx3-=10;
            obsx4-=10;
            obsx5-=10;
            obsx6-=10;
        }

        for(int i=0;i<50;i++){
            rnd[i]-=10;
            if(rnd[i]<0) rnd[i]=980;
        }

        collision();

        if(obsx1<0) obsx1=1200,easyscore++;
        if(obsx2<0) obsx2=1200,easyscore++;
        if(obsx3<0) obsx3=1200,easyscore++;
        if(obsx4<0) obsx4=1200,easyscore++;
        if(obsx5<0) obsx5=1200,easyscore++;
        if(obsx6<0) obsx6=1200,easyscore++;
    }
    if(medium){
        if(!flg && !gameover && play) y-=20;
        birdidx++;
        if(birdidx>7) birdidx=0;
        if(!flg){
            obsx1-=neg;
            obsx2-=neg;
            obsx3-=neg;
            obsx4-=neg;
            obsx5-=neg;
            obsx6-=neg;
            obsx7-=neg;
            obsx8-=neg;
        }

        collision();

        if(obsx1<0) obsx1=1250,mediumscore+=2;
        if(obsx2<0) obsx2=1250,mediumscore+=2;
        if(obsx3<0) obsx3=1250,mediumscore+=2;
        if(obsx4<0) obsx4=1250,mediumscore+=2;
        if(obsx5<0) obsx5=1250,mediumscore+=2;
        if(obsx6<0) obsx6=1250,mediumscore+=2;
        if(obsx7<0) obsx7=1250,mediumscore+=2;
        if(obsx8<0) obsx8=1250,mediumscore+=2;
        
        while(neg<15) neg+=0.0005;
    }
    if(hard){
        if(!flg && !gameover && play) y-=20;
        birdidx++;
        if(birdidx>7) birdidx=0;
        if(!flg){
            obsx1-=neg;
            obsx2-=neg;
            obsx3-=neg;
            obsx4-=neg;
            obsx5-=neg;
            obsx6-=neg;
            obsx7-=neg;
            obsx8-=neg;
        }

        collision();

        if(obsx1<0) obsx1=1250,hardscore+=3;
        if(obsx2<0) obsx2=1250,hardscore+=3;
        if(obsx3<0) obsx3=1250,hardscore+=3;
        if(obsx4<0) obsx4=1250,hardscore+=3;
        if(obsx5<0) obsx5=1250,hardscore+=3;
        if(obsx6<0) obsx6=1250,hardscore+=3;
        if(obsx7<0) obsx7=1250,hardscore+=3;
        if(obsx8<0) obsx8=1250,hardscore+=3;
        
        while(neg<15) neg+=0.002;
    }
}

int main(){
    int x=50;
    iSetTimer(x,change);
    if(music){
        PlaySound("homepage.wav", NULL, SND_LOOP | SND_ASYNC);
    }
    else PlaySound(0,0,0);
    iInitialize(screenwidth,screenheight,"Thuja's Flappy Bird");
    
}