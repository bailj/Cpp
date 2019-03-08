#include "GameBody.hpp"
using namespace std;

GameBody::GameBody(const string title,int width,int height,Uint32 flag,int delaytime):win(title,width,height,flag),error(false),gamequit(false),delaytime(delaytime){
	if(isSDL_Init == false)
		if(SDL_Init(SDL_INIT_EVERYTHING)==0)
			isSDL_Init=true;
	if((render = SDL_CreateRenderer(win.get(),-1,0))==nullptr)
		error=true;
	else
		globaleRenderer = render;
}

void GameBody::eventHandle(){
	while(SDL_PollEvent(&event)){
		if(event.type==SDL_QUIT){
			gamequit=true;
			SDL_Quit();
		}
	}
}

void GameBody::renderBegin(){
	SDL_SetRenderDrawColor(render,255,255,255,255);
	SDL_RenderClear(render);	
}

void GameBody::renderEnd(){
	SDL_RenderPresent(render);
}

void GameBody::delay(int millisec){
	SDL_Delay(millisec);
}

void GameBody::step(){
	renderBegin();
	eventHandle();
	update();
	renderEnd();
	delay(delaytime);
}

GameBody::~GameBody(){
	clean();
	SDL_DestroyRenderer(render);
	globaleRenderer = nullptr;
	if(isSDL_Init == true){
		SDL_Quit();	
		isSDL_Init=false;
	}
}
