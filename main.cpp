//============================================================================
// Author      : Wiktor Jurek
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <functional>
#include <fstream>
#include <math.h>       /* pow */
using namespace std;

int naiveStringMatching(string T, string p,int show=1)
{

    int textLenght = T.length();
    int patternLength = p.length();

    int counter=0;
    for(int i=0; i<=textLenght - patternLength; i++)
    {

        int index =0;

        while(p[index] == T[i + index] && index<patternLength)
        {

            index++;
            counter++;
            if(index == patternLength)
            {
            if(show==1){
                cout<<"Znaleziono wzorzec z przesunieciem "<<i<<endl;
            }
                counter-=1;
            }

        }
        counter++;

    }
    return counter;
}

int BoyerMoore(string T, string p, int show = 1)
{

    int textLenght = T.length();
    int patternLength = p.length();
    int counter=0;

    int lastTable[256];

    for(int k=0; k<256; k++)
    {
        lastTable[k] = -1;
    }
    for(int j =0; j<patternLength; j++)
    {
        lastTable[(int)p[j]] = j;
    }



    int i=0;
    while(i <= textLenght - patternLength )
    {

        bool increment = true;
        int index = patternLength - 1;
        while(index >= 0 && p[index] == T[i + index])
        {
            index--;
            counter++;
            increment = false;

        }

        if(index == -1 )
        {
            if(show==1){
                cout<<"Znaleziono wzorzec z przesunieciem "<<i<<endl;
            }
            i++;
        }
        else
        {
            //gdy nie występuje we wzoru przesuwamy za znak

            if(lastTable[(int)T[i + index]] == -1)
            {
                i = i +index +1;
            }
            //gdy występuje we wzorcu z lewej strony sprawdzanego elementu i przesuwamy na ten element
            else if(lastTable[(int)T[i + index]] < index)
            {
                i = i + index  - lastTable[(int)T[i + index]];
            }
            //gdy istnieje ale znakk we wzoru ale jest z prawej strony wzorca
            else
            {
                i++;
            }
        }

        if(increment)
        {

            counter++;
        }

    }
    return counter;
}
string textGenerator(int n){

    string temp ="";

    for(int i =0 ;i<n;i++){

        int character = rand() %95 + 32;
        temp = temp + (char)character;

    }
    return temp;
}


int main(int argc, char** argv)
{
    srand (time(NULL));
    cout<<"Wyszukiwanie wzorca w tekscie algorytm naiwny i Booyera Moore'a"<<endl;

    string text = "W ogolnym przekonaniu wiewiorki to istoty wprost urocze. Gdy skacza po drzewach, ludzie pokazuja je sobie palcami i pieja: - Ojej! Ale rozkoszna! - a ich glosy staja sie niezwykle przeslodzone i wznosza sie falsetem w gore. Pozwolcie jednak, ze wyjasnie tu od razu jedna rzecz: wiewiorki sa rozkoszne tylko wtedy, gdy sa na tyle male, ze mozna je rozdeptac. Kiedy czlowiek staje przed gigantyczna wiewiorka wielkosci betoniarki, jakos z miejsca przechodzi mu slabosc do tych stworzonek. Totez zeby wielkosci lodowki, wasy grubosci batogow, oczy jak opony od traktora gapiace sie na mnie niczym wulkaniczne banki tuszu chinskiego w zadnym razie mnie nie zaskoczyly - przerazilo mnie tylko, ze prawda okazaly sie moje najgorsze podejrzenia";
    cout<<endl<<text<<endl;
    string wzor = "W ogolnym";
    string wzor2 = " jedna";
    string wzor3 ="podejrzenia";
    cout<<endl<<endl;
    int temp = 0;
    cout<<"Test wzorzec na pierwszym miejscu tekstu "<<endl;
    temp = naiveStringMatching(text,wzor);
    cout<<"naiveStringMatching(text,"<<wzor<<") : "<< temp<<endl<<endl;
    temp = BoyerMoore(text,wzor);
    cout<<"BoyerMoore(text,"<<wzor<<") : "<< temp<<endl;

    cout<<endl;
    cout<<"Test wzorzec w dowolnym miejscu tekstu "<<endl;
    temp = naiveStringMatching(text,wzor2);
    cout<<"naiveStringMatching(text,"<<wzor2<<") : "<< temp<<endl<<endl;
    temp = BoyerMoore(text,wzor2);
    cout<<"BoyerMoore(text,"<<wzor2<<") : "<< temp<<endl;



    cout<<endl;
    cout<<"Test wzorzec na koncu tekstu "<<endl;
    temp = naiveStringMatching(text,wzor3);
    cout<<"naiveStringMatching(text,"<<wzor3<<") : "<< temp<<endl<<endl;
    temp = BoyerMoore(text,wzor3);
    cout<<"BoyerMoore(text,"<<wzor3<<") : "<< temp<<endl;

    cout<<endl<<"Porownanie algorytmow wyszukiwania wzorca w tekscie"<<endl;
    double avergaeNaive =0, averageBoyer =0;
    int trys = 5000;
    int textLength = 10000;
    for(int i=0;i<trys;i++){
        string textGenerated;
        textGenerated = textGenerator(textLength);
        int patternLength = rand() %100 + 1;
        int patternStartIndex = rand()%(textLength - patternLength);
        string pattern = "";
        pattern = textGenerated.substr(patternStartIndex,patternLength);
        avergaeNaive += naiveStringMatching(textGenerated,pattern,0);
        averageBoyer += BoyerMoore(textGenerated,pattern,0);
    }
    cout<<endl;
    cout<<"Srednia ilosc porownan dla algorytmu naiwnego : "<< (double)(avergaeNaive/(double)trys)<<endl;
    cout<<"Srednia ilosc porownan dla algorytmu Boyera : "<< (double)(averageBoyer/(double)trys)<<endl;
    return 0;
}




