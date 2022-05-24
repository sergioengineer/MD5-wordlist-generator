#include "hashmd5.h"

/*|-Variaveis-|*/
 MD_FIVE mFive;            //obj MD_FIVE declarado em hashmd5.h
 unsigned short int resp; //Resposta do usu�rio ao set de op��es




/****  Prot�tipos
                  ****/
void Show_Credits();




  //-----------------------------------------------------//
 //------------------MAIN-BEGIN-------------------------//
//-----------------------------------------------------//


int  WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance,
                                  LPSTR lpszArgument, int nFunsterStil)
{

 while(1)
 {


  /*----->T�tulo/referencias e etc*/
  SetConsoleTitle("*-----HashCracker------*");
  cout << "*********************\n";
  cout << "*     SERGIO C.     *\n";
  cout << "*********************\n\n\n";



 /*------>Set de op��es*/
  cout << "1- Criar hash \n" //ready
       << "2- \\HeavyMode\n"
       << "3- \\SoftMode\n" //almost
       << "4- \\NormalMode\n"
       << "5- Generate word list \\HeavyMode\n"
       << "6- Generate word list \\SoftMode\n"
       << "7- Generate word list \\NormalMode \n" //ready
       << "9- Sair\n";

  cin >> resp;

  switch(resp)
  {
   case 1:
            mFive.Call_Create();
            break;
   case 3:
            break;
   case 4:
            break;
   case 5:

            break;
   case 6:
            mFive.wList_Soft();
            break;
   case 7:
            mFive.wList_Normal();
            break;
   case 9:
            Show_Credits();
            goto fim_do_programa;
            break;


  }



  system("cls");
 }


fim_do_programa:;

}

  //-----------------------------------------------------//
 //------------------MAIN-END---------------------------//
//-----------------------------------------------------//






void Show_Credits()
{
     system("cls");
     cout << "Hohohoho";


     system("pause > nul");

}
