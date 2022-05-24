//--------/*/    HEADERS   /*/--------//
                                     //
#include <windows.h>                //
#include <Wincrypt.h>              //
#include <fstream>                //
#include <stdlib.h>              //
#include <iostream>             //
#include <string>              //
                              //
                             //
using namespace std;        //
                           //
                          //
///////////////////////////




//--------------------/*/    CLASSES    /*/------------------------//|
                                                                   //|
class A_Chars                                                      //|
{                                                                  //|
 public:                                                           //|
  BYTE A_Char[1024];                                               //|
};                                                                 //|
                                                                   //|
//=================================================================//|
                                                                   //|
class MD_FIVE                                                      //|
 {                                                                 //|
  public:                                                          //|
         MD_FIVE();                                                //|
         ~MD_FIVE();                                               //|
         void CREATE(BYTE*);                                       //|
         void wList_Normal();                                      //|
         void Call_Create();                                       //|
         int Ta_Tudo_Certo(int);                                   //|
         void wList_Soft();                                        //|
         void Breaking_Normal();                                   //|
  private:                                                         //|
          friend DWORD WINAPI wList_Softhread(LPVOID);             //|
          friend DWORD WINAPI wList_Softhread2(LPVOID);            //|
          HANDLE *Threader;                                        //|
          DWORD *ThreadID;                                         //|
          string O_STRING;                                         //|
          HCRYPTPROV hProv;                                        //|
          DWORD cbHash;                                            //|
          HCRYPTHASH hHash;                                        //|
          CHAR HexDig[16];                                         //|
          fstream File__, File__2;                                 //|
          BYTE A_Char[95];                                         //|
          A_Chars A_Char2, A_Char3;                                //|
          unsigned short int x , y, yy;                            //|
 };                                                                //|
                                                                   //|
/*-----------------------------------------------------------------*/






MD_FIVE :: MD_FIVE()
{
 hProv = 0;
 cbHash = 16;
 hHash = 0;
 HexDig[0] = '0';
 HexDig[1] = '1';
 HexDig[2] = '2';
 HexDig[3] = '3';
 HexDig[4] = '4';
 HexDig[5] = '5';
 HexDig[6] = '6';
 HexDig[7] = '7';
 HexDig[8] = '8';
 HexDig[9] = '9';
 HexDig[10] = 'a';
 HexDig[11] = 'b';
 HexDig[12] = 'c';
 HexDig[13] = 'd';
 HexDig[14] = 'e';
 HexDig[15] = 'f';
 
 
  
 for (unsigned short int i = 32; i < 127; i++)
 {
  A_Char[i-32] = (char) i;
 }
}//construtor
  
MD_FIVE :: ~MD_FIVE()
{
 if (File__.is_open())
 {
  File__.close();
 } 
 File__2.open("HeaderFile", ios_base :: binary | ios_base :: out);
 File__2.write((char *) &x, sizeof(x));
 File__2.write((char *) &y, sizeof(y));
 File__2.write((char *) &A_Char3, sizeof(A_Char3));
 File__2.close();
 
} //destrutor
  
void MD_FIVE :: CREATE(BYTE *overRR)
{   

    
    CryptAcquireContext(&hProv,
                        NULL,
                        NULL,
                        PROV_RSA_FULL,
                        CRYPT_VERIFYCONTEXT); 
    
    
                    
    CryptCreateHash(hProv, 0x00008003, 0, 0, &hHash);
    
    
    O_STRING = (const char *)overRR;
    CryptHashData(hHash, overRR, O_STRING.size(), 0);
    CryptGetHashParam(hHash, HP_HASHVAL, overRR, &cbHash, 0);
    
    
    for (int i = 0; i < cbHash; i++)
        {               
            File__ << HexDig[overRR[i] >> 4]
                   << HexDig[overRR[i] & 0xf];         
        }
    File__ << " String:" << O_STRING << endl;

 
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    
 


} //CREATE

void MD_FIVE :: Call_Create()
{
  ZeroMemory(A_Char2.A_Char,sizeof(A_Char2.A_Char));
  cout << "Digite a string: ";
  cin >> A_Char2.A_Char;
  File__.open("HashGen.txt",  ios_base :: app | ios_base :: out);
  this->CREATE(A_Char2.A_Char);
  File__.close();
  File__.clear();
  ZeroMemory(A_Char2.A_Char,sizeof(A_Char2.A_Char));
} //Call create


void MD_FIVE :: wList_Normal()
{
 
  

 
  File__2.open("HeaderFile", ios_base :: binary | ios_base :: in);
  File__2.seekg(0, ios :: end);
  if(File__2.tellg() > 0)
  {
   File__2.seekg(0, ios :: beg);                  
   File__2.read((char *) &x, sizeof(x));
   File__2.read((char *) &y, sizeof(y));
   File__2.read((char *) &A_Char3, sizeof(A_Char3));
  }
  else
  {
   y = 0;
   yy = 0;
   x = 0;
    
  }    

  File__2.close();
  File__2.clear();
  
  
  

  File__.open("wList.txt",  ios_base :: app | ios_base :: out);
  if(y > 0)
  {
   yy = y;
   goto Ja_to_dentro;
  }
  while(1)
  {
   while (1)
   {
    A_Char2 = A_Char3;   
    A_Char2.A_Char[0] = A_Char[x - ((x/95)*95)];
     
    
    /*algoritmo de transi��o*/
    if((x%95 == 0) && (y > 0))
     {
      testa_novamente:
      if(A_Char2.A_Char[yy] == (BYTE) '~' && yy > 0)
       {                     
        A_Char2.A_Char[yy] = A_Char[0];
        yy--;
        goto testa_novamente;
       }
      else if (yy > 0)
      {
       A_Char2.A_Char[yy] = (int)A_Char2.A_Char[yy] + 1;
      }
      if (yy == 0)
       yy = y+1;
      else 
      yy = y;
     }   
   
    /*gera o hash*/
    A_Char3 = A_Char2;
    this->CREATE(A_Char2.A_Char);  
    ZeroMemory(A_Char2.A_Char,sizeof(A_Char2.A_Char));
    
    /*controle de loops*/
    x++;
    
    Ja_to_dentro:;
    if (A_Char3.A_Char[0] == (BYTE) '~' && y == 0)   
     break;  
    
    if ((y > 0) && this->Ta_Tudo_Certo(y))
     break;
   }//while(1)
   y++;
   yy = y;
   for (int cont = 0; cont <= y; cont++)
    A_Char3.A_Char[cont] = 32;
   A_Char3.A_Char[y] = 31; 
  }//while(coluna)
  
 File__.close();
 
} //gerador de normal wList


int MD_FIVE :: Ta_Tudo_Certo(int cont)
{
    for(int i = 0; i <= cont; i++)
     if(A_Char3.A_Char[i] < 126)
      return 0;

    return 1;  
} //verificador


void MD_FIVE :: wList_Soft()
{
 Threader = new HANDLE [sizeof(HANDLE) * 2];
 ThreadID = new DWORD [sizeof(DWORD) * 2];
 Threader[0] = CreateThread(0,0,wList_Softhread,(void *) this,0, &ThreadID[0]);
 Threader[1] = CreateThread(0,0,wList_Softhread2,(void *) this,0, &ThreadID[1]);
 
 WaitForMultipleObjects(2,Threader,1,INFINITE);
 
 TerminateThread(Threader[0],0);
 CloseHandle(Threader[0]);
 
 TerminateThread(Threader[1],0);
 CloseHandle(Threader[1]);

 
 delete [] Threader;
 delete [] ThreadID;
}



void MD_FIVE :: Breaking_Normal()
{
 string m_Hash;
 cout << "Digite o Hash: ";
 cin >> m_Hash;
 
 
 
}

/*-----
         Threads
                 ------*/
                 
                 
DWORD wList_Softhread(LPVOID valor)
{      
 MD_FIVE *another = (MD_FIVE *)valor;      
 MessageBox(0,"Testando","ST1",0x40);
 cout << another->HexDig[10];
 return 0;
}


DWORD wList_Softhread2(LPVOID valor)
{      
 MD_FIVE *another = (MD_FIVE *)valor;      
 MessageBox(0,"teste","ST2",0x40);
 cout << another->HexDig[11];
 return 0;
}