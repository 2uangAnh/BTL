#include "sdlsetting.h"
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
SDL_Texture* loadTexture(string path,SDL_Renderer* renderer){
    SDL_Texture*newTexture=nullptr;
    SDL_Surface* loadedSurface=IMG_Load(path.c_str());
    if(loadedSurface==nullptr)
        cout<<"Unable to load image "<< path<<" SDL_Image Error "
            <<IMG_GetError()<<endl;

        else {
            newTexture =SDL_CreateTextureFromSurface( renderer, loadedSurface);
            if(loadedSurface==nullptr)
                cout<<" Unable to create texture from "<<path<<" SDL Error: "
                    <<SDL_GetError()<<endl;
                    SDL_FreeSurface(loadedSurface);

        }
        return newTexture;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
bool GameOver(int check){
    if(check==6) return true;
    else return false;
}
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer,
    const SDL_Rect& filled_rect, const bool leftMouse)
{
    // ?????t m??u v??? th??nh xanh lam (blue), xo?? m??n h??nh v??? m??u xanh lam.
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);   // blue
    SDL_RenderClear(renderer);

    // V??? h??nh ch??? nh???t v???i m??u tu??? thu???c n??t chu???t tr??i hay ph???i ???????c nh???n
    if (leftMouse)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    else
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   // green
    SDL_RenderFillRect(renderer, &filled_rect);

    // D??ng l???nh hi???n th??? (????a) h??nh ???? v??? ra m??nh h??nh
   //Khi th??ng th?????ng ch???y v???i m??i tr?????ng b??nh th?????ng ??? nh??
    SDL_RenderPresent(renderer);
   //Khi ch???y ??? m??y th???c h??nh WinXP ??? tr?????ng (m??y ???o)
   //SDL_UpdateWindowSurface(window);
}
void Display_hide(int x, int y,SDL_Renderer* renderer){
    SDL_Texture *img1 =loadTexture("images/backcard.png",renderer);
    SDL_Rect img1Rect ;
    SDL_QueryTexture (img1,NULL,NULL, &img1Rect.w,&img1Rect.h);
    img1Rect.x=x;
    img1Rect.y=y;
    SDL_RenderCopy(renderer,img1,NULL,&img1Rect);
    SDL_RenderPresent(renderer);
    }
void Display_img(int x, int y,string path,SDL_Renderer* renderer){
    SDL_Texture *img1 =loadTexture(path.c_str(),renderer);
    SDL_Rect img1Rect ;
    SDL_QueryTexture (img1,NULL,NULL, &img1Rect.w,&img1Rect.h);
    img1Rect.x=x;
    img1Rect.y=y;
    SDL_RenderCopy(renderer,img1,NULL,&img1Rect);
    SDL_RenderPresent(renderer);
}
