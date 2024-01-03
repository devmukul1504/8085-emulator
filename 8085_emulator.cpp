#include "function_definition.h"
#include  "function_definition.cpp"

void written_code();
void run_program();
void convert(string &s)
{
    for(int i=0;i<s.length();i++)
        s[i]=toupper(s[i]);
}

bool validityAddress(string data)
{
	bool flag;
	int l=data.length();
	if(l==4)
	{
		for(int i=0;i<l;i++)
			if(( data[i]>='0' && data[i]<='9')||( data[i]>='A' && data[i]<='F' ))
				flag = true;
			else
				flag = false;
		return flag;
	}
	else
		return false;
}




int main(int agrc,char*argv[])
{
    int tmp;
    char ch;
    set_instructions_size();
    cout<<"\n\t\tWelcome in 8085 emulator\n\n"<<endl;
    cout<<"Press 1 : if you use prewritten code"<<endl;
    cout<<"Press 2 : if you write program on terminal"<<endl;
    cout<<"Press 3 : exit"<<endl;
    cin>>tmp;
    if(tmp==1)//INPUT FROM FILE
    {
        string code;
        ifstream fin;
        /*if(argc==2)
        {
            fin.open(argv[1]);
        }
        else
        {*/
            do
            {
                cout<<"\nAvailable Codes:\n\n";
                cout<<"\nA:Swap contains of 2 memory location";
                cout<<"\nB:8 bit Addition";
                cout<<"\nC:16 bit Addition";
                cout<<"\nD:8 bit subraction";
                cin>>ch;
                switch(ch)
                {
                    case 'a':
                    case 'A':fin.open("swap data.txt");
                             break;
                    case 'b':
                    case 'B':fin.open("8 Bit Addition.txt");
                             break;
                    case 'c':
                    case 'C':fin.open("16 Bit Addition.txt");
                             break;
                    case 'd':
                    case 'D':fin.open("8 Bit subtraction.txt");
                             break;
                    case 'e':
                    case 'E':fin.open("8 Bit Array Find smallest.txt");
                             break;
                    case 'f':
                    case 'F':fin.open("8 Bit Array Find largest.txt");
                             break;
                    case 'g':
                    case 'G':fin.open("8 Bit Array Sort Ascending.txt");
                             break;
                    case 'h':
                    case 'H':fin.open("8 Bit Array Sort Descending.txt");
                             break;
                    default: cout<<"\nInvalid Input\n";
                }
            }while(!((ch>='A' && ch<='H') || (ch>='a' && ch<='h')));
        //}

    }
    switch(tmp)
    {
        case 1: //prewritten_code();
                break;
        case 2: written_code();
                break;
        case 3: cout<<"Thank you using for 8085 emultor"<<endl;
                break;
        default:cout<<"Invaild input"<<endl;
                break;
    }
    return 0;
}






void written_code()
{
    string code;
    int tmp1;
    cout<<"Enter starting address:\n";
    ofstream fout;
    fout.open("Code.txt",ios::out);
    cin.ignore();
    getline(cin,starting_address);
    if(!validityAddress(starting_address))
    {
        cout<<"The memory you entered either does not exist or is reserved by the system";
        cout<<"\n\t***Terminating Program\t\n";
        exit(1);
    }

    fout<<starting_address<<endl;
    program_counter = starting_address;
    do
    {
        cout<<program_counter<<": ";
        getline(cin,code);
        convert(code);
        M[program_counter] = code;
      //  fout<<program_counter<<":";
        fout<<code<<endl;
        pc = hextodec(program_counter);
        if(code.size()==3 || code.size()==4||code.size()==2)
        {
            pc += inst_size[code];
        }
        else
        {
            pc += inst_size[code.substr(0,get_index(code,' '))];
        }
        program_counter = dectohex(pc);
    }while(code!="HLT" && code!="EOF");
    fout.close();
    do
    {
        cout<<"\nDebugger:"<<endl;
        cout<<"Press 1: ON"<<endl;
        cout<<"Press 2:OFF"<<endl;
        cin>>tmp1;
        if(tmp1!=1 && tmp1!=2)
        {
            cout<<"\nInvalid Option! Try Again!\n";
        }
    }while(tmp1!=1 && tmp1!=2);
    if(tmp1==2){
        set_instructions();
        reset_flags();
        reset_registers();
        program_counter = starting_address;
        run_program();
    }
}

void run_program()
{
    map<string,string>::iterator p=M.begin();
    string s,s1,s2,tmp;
    string mycode;
    while(p!=M.end())
    {
        if(((p->second).size())>4)
        {
            mycode=(p->second);
            s=mycode.substr(0,get_index1(mycode,' '));
            tmp=mycode.substr(get_index1(mycode,' ')+1,' ');
            s1=tmp.substr(0,get_index1(tmp,' '));
            s2=tmp.substr(get_index1(tmp,' ')+1,' ');

        }
        else if(((p->second).size())==3 && ((p->second).size())==4)
        {
            mycode=(p->second);
            s=mycode.substr(0,get_index1(mycode,' '));

        }
        int size=check_operand(s);
        switch(size)
        {
            case -1:cout<<"*** ERROR: INVALID 8085 COMMAND. ***\nTerminating Program..."<<endl;		// ERROR STATEMENT
                    break;

            case 0: break;              // RETURN 0 for hlt

            case 1: char str[5];
                    char str1[5];
                    strcpy(str,s1.c_str());
                    strcpy(str1,s2.c_str());
                    MOV(str,str1);
                    break;

            case 2: MVI(s1,s2);
                    break;

            case 3: LXI(s1,s2);
                    break;

            case 4: LDA(s1);
                    break;

            case 5: STA(s1);
                    break;

            case 6: LHLD(s1);
                    break;

            case 7: SHLD(s1);
                    break;

            case 8: STAX(s1);
                    break;

            case 9: XCHG();
                    break;

            case 10:ADD(s1);
                    break;

            case 11:ADI(s1);
                    break;

            case 12:SUB(s1);
                    break;

            case 13:INR(s1);
                    break;

            case 14:DCR(s1);
                    break;

            case 15:INX(s1);
                    break;

            case 16:DCX(s1);
                    break;

            case 17:DAD(s1);
                    break;

            case 18:SUI(s1);
                    break;

            case 19:CMA(s1);
                    break;

            case 20:CMP(s1);
                    break;

            case 21:JMP(s1);
                    break;

            case 22:JC(s1);
                    break;

            case 23:JNC(s1);
                    break;

            case 24:JZ(s1);
                    break;

            case 25:JNZ(s1);
                    break;

            case 26:SET(s1,s2);
                    break;
        }
        p++;
    }
}




