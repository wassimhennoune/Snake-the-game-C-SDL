#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include<time.h>
int main ( int argc, char** argv )
{
 SDL_Surface *ecran = NULL , *imst=NULL/*tete*/,*imst2=NULL/*corp*/ ,*scorebare=NULL,*imst3=NULL/*q*/;
 FILE *f_score=NULL;
 SDL_Rect position[500];
 SDL_Rect pos,pos_score ;
 SDL_Event event ;
 int continuer=1 , d=2 , tail=0 ,i , eat=1 , k=0,score=0,delay=100;
 pos_score.x=0;
 pos_score.y=600;
 f_score=fopen("score.txt", "a+");
 SDL_Init(SDL_INIT_VIDEO);
 ecran = SDL_SetVideoMode(750, 660, 32, SDL_HWSURFACE );
 scorebare=SDL_LoadBMP("scorebare.bmp");

 SDL_WM_SetCaption("snake", NULL);
 //initialisation
position[tail].x=(rand()%50)*15 ;
position[tail].y=(rand()%40)*15 ;

for (i=(tail-1);i>=0;i--)
{
    position[i].x=position[i+1].x+15 ;
    position[i].y=0 ;
}

 while (continuer)
  {
    srand (k);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
    SDL_BlitSurface(scorebare,NULL,ecran,&pos_score);
    SDL_PollEvent(&event) ;
     switch (event.type)
     {
           case SDL_KEYDOWN :
           switch (event.key.keysym.sym )
            {
              case SDLK_UP :
              if ((d!=1)&&(d!=3))
              {
                d=1 ;
              }
              break ;

              case SDLK_DOWN :
              if ((d!=1)&&(d!=3))
              {
                d=3 ;
              }
              break ;

             case SDLK_RIGHT :
              if ((d!=2)&&(d!=4))
              {
                  d=2 ;
              }
              break ;

             case SDLK_LEFT :
              if ((d!=2)&&(d!=4))
              {
                  d=4 ;
              }
              break;
            }
         break ;

       case SDL_QUIT :
        continuer=0 ;
     }

     switch(d)
     {
         case 1 :imst = SDL_LoadBMP("head_up.bmp");imst3 = SDL_LoadBMP("q_up.bmp");break;
         case 2 :imst = SDL_LoadBMP("head_right.bmp");imst3=SDL_LoadBMP("q_right.bmp");break;
         case 3 :imst = SDL_LoadBMP("head_down.bmp");imst3 = SDL_LoadBMP("q_down.bmp");break;
         case 4 :imst = SDL_LoadBMP("head_left.bmp");imst3 = SDL_LoadBMP("q_left.bmp");break;
     }

                 imst2 = SDL_LoadBMP("a.bmp");
   SDL_SetColorKey (imst,SDL_SRCCOLORKEY,SDL_MapRGB(imst->format,255,255,255));
   if (eat)
    {
    pos.x=  (rand()%50)*15;
    pos.y=  (rand()%40)*15;
    eat=0 ;
    }
    //repositionnement
    if (position[0].y<0)        position[0].y=580 ;
    if (position[0].y>585)      position[0].y=0 ;
    if (position[0].x>735)      position[0].x=0 ;
    if (position[0].x<0)         position[0].x=735 ;
    //affichege
    SDL_BlitSurface(imst2, NULL, ecran, &pos );
    SDL_BlitSurface(imst, NULL, ecran, &position[0] );
    for (i=1;i<tail;i++)
     {
       SDL_BlitSurface(imst2, NULL, ecran, &position[i] );
     }
     SDL_BlitSurface(imst3, NULL, ecran, &position[tail] );
      SDL_Flip(ecran);
      //eat
     if ((pos.x>=position[0].x-10)&&(pos.x<=position[0].x+10)&&(pos.y>=position[0].y-10)&&(pos.y<=position[0].y+10))
     {
       tail++ ;
       eat=1 ;
     }

     for (i=tail;i>=1;i--)
     {
       position[i]=position[i-1] ;
     }
     if (d==2)
     {
      position[0].x=position[0].x+15 ;
     }
     if (d==4)
     {
      position[0].x=position[0].x-15 ;
     }
     if (d==1)
     {
      position[0].y=position[0].y-15 ;
     }
     if (d==3)
     {
      position[0].y=position[0].y+15 ;
     }

     SDL_Delay(delay) ;
     k=k+3 ;
     //GAME OVER
     for(i=1;i<=tail;i++){if((position[0].x==position[i].x)&&(position[0].y==position[i].y))continuer=0;}
  }
SDL_Quit();
return EXIT_SUCCESS;
}
