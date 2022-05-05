#include <bits/stdc++.h>
#include "sdlsetting.h"
//#include "game.h"
using namespace std;
SDL_Window* window;
SDL_Renderer* renderer;
string img[4][4];
int tmp[4][4] = {};
string tmparray[16];
string GetPath(int x,int y)
{
   int x0=547,y0=97,x1=1015,y1=765;
   int col = (x-x0)*4/(x1-x0);
   int row = (y-y0)*4/(y1-y0);
   return img[row][col];

}
void GetEvent(SDL_Event e,int &a,int &b){
    while (true) {
        // Đợi 10 mili giây
        SDL_Delay(10);

        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặpd
        if ( SDL_WaitEvent(&e) == 0) continue;

        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (e.type == SDL_QUIT) break;

        // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;

        // Nếu chuột (mouse) được nhấn (xuống)
        if (e.type == SDL_MOUSEBUTTONDOWN) {
             if(e.button.x<547||e.button.x>1015||e.button.y<97||e.button.y>765) continue;
             else
             {
             a=e.button.x;
             b=e.button.y;
             break;
            }
     }
}
}
void GetLoca(int &x,int &y)
{
   int x0=547,y0=97,x1=1015,y1=765;
    x = (x-x0)*4/(x1-x0);
    y = (y-y0)*4/(y1-y0);
}
void loadpath()
{
    int k=1;
    int n=0;
    for(int i=0;i<16;i++)
    {
        tmparray[i]="images\\" + to_string(k) + ".png";
        if(k<8)k++;
        else
        {
            k=1;
        }
    }
    random_shuffle(begin(tmparray),end(tmparray));
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            img[i][j]=tmparray[n];
            n++;
        }
    }
}
void showgame()
{
    initSDL(window, renderer);
    SDL_Texture *background =loadTexture("images/background.png", renderer);
    SDL_RenderCopy(renderer,background,NULL,NULL);               //Khoi tao background
    SDL_RenderPresent(renderer);
    int x =547,y=97;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            Display_hide(x,y,renderer);
            x+=117;
        }
        y+=167;
        x=547;
    }
    loadpath();
}
void rungame()
{
    SDL_Event e;
    int check=0;
    while(check<8){
        int a,b,c,d;
        while (true)
        {
            GetEvent(e,a,b);
        GetLoca(a,b);
            if(tmp[b][a]==0)
        {
            tmp[b][a]=1;
        Display_img(a*117+547,97+b*167,img[b][a],renderer);
        break;
        }
        }
        while(true){
        GetEvent(e,c,d);
        GetLoca(c,d);
        if(tmp[d][c]==0){
              tmp[d][c]=1;
              Display_img(c*117+547,97+d*167,img[d][c],renderer);
              break;
        }
        }
        SDL_Delay(1000);
        if(img[b][a]==img[d][c]){
            check++;
        }
        else {
              Display_hide(c*117+547,97+d*167,renderer);
              Display_hide(a*117+547,97+b*167,renderer);
              tmp[b][a]=0;
              tmp[d][c]=0;
        }
    }
    cout<<"You Win";
}
int main (int argc, char* argv[]){
showgame();
rungame();
waitUntilKeyPressed();
quitSDL(window, renderer);
    return 0;

}
