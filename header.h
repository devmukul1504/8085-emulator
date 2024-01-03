#include<iostream>
#include<string>
#include<string.h>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int pc;

string program_counter,starting_address;
map<string,int> commands;
map<string,int> inst_size;
map<string,string>M;
map<string,int> memory;
map<char,int> registers;
map<char,int> flag;

//int get_index(string);
//void MOV(string,string);
//vector<string> memoryLocationsUsed;


/*for(int i=0;i<=(hextodec(ffff);i++)
{
    mm=i;
    string address=dectohex(mm);
    memory[address]=0;
}*/

