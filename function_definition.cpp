//Finding Index of a character in a String

int get_index1(string s, char c)
{
    for(int i=0;i<s.size();i++)
    {
        if(c==s[i])
        {
            return(i);
        }
    }
    return -1;
}





//Hexadecimal <--> Decimal Conversions

string dectohex(int n)
{
    stringstream ss;
    ss << hex << n;
    return ss.str();
}
int hextodec(string s)
{
    istringstream converter(s);
    int value;
    converter>>hex>>value;
    return value;
}



//String <--> Integer Conversions

/*int str_to_int(string str)
{
    int n;
    stringstream ss(str);
    ss>>n;
    return n;
}
string int_to_str(int n)
{
    stringstream ss;
    ss<<n;
    return ss.str();
}*/






//Decimal <--> Binary Conversions

/*string dectobin(int a)
{
	string str="";
	while(a>0)
	{
		str+=('0'+(a%2));
		a=a/2;
	}
	return str;
}
int bintodec(string str)
{
	int temp,i,a=0;
	for(i=0;i<str.size();i++)
	{
		a+=pow(2,i)*(str[i]-'0');
	}
	return a;
}*/


/*Checking for Valid Instruction which have operands

int insturction_Present(string s)
{
    if(s=="ADD"||s=="SUB"||s=="CMP"||s=="INR"||s=="DCR"||s=="LDA"||s=="STA"||s=="LHLD"||s=="SHLD"||s=="JMP"||s=="JC"||s=="JNC"||s=="JZ"||s=="JNZ"||s=="ADI"||s=="SUI"||s=="STAX"||s=="DAD"||s=="INX"||s=="DCX"||s=="MOV"||s=="LXI"||s=="MVI"||s=="SET")
    {
        return 1;
    }
    return 0;
}*/

bool check_register(string s)
{
    string a[] = {"A","B","C","D","E","H","L","M","a","b","c","d","e","h","l","m"};
    bool flag;
    for(int i=0;i<8;i++)
    {
        if(a[i] == s)
        {
            flag= true;
            return flag;
        }
    }
    flag=false;
    return flag;
}

//Reset all Flags
void reset_flags()
{
    flag['z'] = 0;
    flag['s'] = 0;
    flag['c'] = 0;
    flag['p'] = 0;
    flag['a'] = 0;
}

//Reset all Registers
void reset_registers()
{
    registers['A'] = 0;
    registers['B'] = 0;
    registers['C'] = 0;
    registers['D'] = 0;
    registers['E'] = 0;
    registers['H'] = 0;
    registers['L'] = 0;
}

//Setting size of instructions
void set_instructions_size()
{
    inst_size["MOV"] = 1;
    inst_size["XCHG"]= 1;
    inst_size["ADD"] = 1;
    inst_size["SUB"] = 1;
    inst_size["INR"] = 1;
    inst_size["DCR"] = 1;
    inst_size["INX"] = 1;
    inst_size["DCX"] = 1;
    inst_size["DAD"] = 1;
    inst_size["CMA"] = 1;
    inst_size["CMP"] = 1;
    inst_size["MVI"] = 2;
    inst_size["ADI"] = 2;
    inst_size["SUI"] = 2;
    inst_size["LXI"] = 3;
    inst_size["LDA"] = 3;
    inst_size["STA"] = 3;
    inst_size["LHLD"] = 3;
    inst_size["SHLD"] = 3;
    inst_size["STAX"] = 3;
    inst_size["JMP"]  = 3;
    inst_size["JC"]  =  3;
    inst_size["JNC"] =  3;
    inst_size["JZ"]  =  3;
    inst_size["JNZ"] =  3;
    inst_size["SET"] =  4;
}

//Setting addressing modes of instructions
void set_instructions()
{
    commands["XCHG"] = 0;
    commands["CMA"] = 0;
    commands["DAA"] = 0;
    commands["SUB"] = 1;
    commands["ADD"] = 1;
    commands["INR"] = 1;
    commands["DCR"] = 1;
    commands["CMP"] = 1;
    commands["LDA"] = 2;
    commands["STA"] = 2;
    commands["LHLD"] = 2;
    commands["SHLD"] = 2;
    commands["JMP"] = 2;
    commands["JC"] = 2;
    commands["JNC"] = 2;
    commands["JZ"] = 2;
    commands["JNZ"] = 2;
    commands["ADI"] = 3;
    commands["SUI"] = 3;
    commands["STAX"] = 4;
    commands["INX"] = 4;
    commands["DCX"] = 4;
    commands["DAD"] = 4;
    commands["MOV"] = 5;
    commands["MVI"] = 6;
    commands["LXI"] = 7;
    commands["SET"] = 8;
}

/*
//flags related functions.........
void check_flags_1(string op)
{
	if(registers[op]==0 || registers[op]==128 || registers[op]==-129)
    {
		flag['z']=1;
		registers[op]=0;
	}
	else
    {
		flag['z']=0;
	}
	//code for checking parity and auxilarry carry.............
}
void check_flags_2()
{							//to check flags for add,sub........
	if(registers['A']<0)
    {
		flag['s']=1;
		if(registers['A']<(-128))
		{
			flag['c']=1;		//if carry
			registers['A']=129-registers['A'];
		}
	}
	else
	{
		flag['s']=0;
		flag['c']=registers['A']/128;		//if carry
		registers['A']%=128;
	}
	if(registers['A']==0)
		flag['z']=1;
	else
		flag['z']=0;
	//code for checking auxilarry and parity flag..............
}

void check_carry(string op = 'A')
{
	if(registers[op]>255)
    {							//to check flags for add,sub........
		flag['c']=1;
		registers[op]%=256;
	}
	else if(registers[op]<0)
	{
		flag['c']=1;
		registers[op]+=256;
	}
	else
	{
		flag['c'] = 0;
	}
}

void check_sign(string op ='A')
{
	if(registers[op]>127)
    {
		flag['s']=1;
	}
	else
	{
		flag['s']=0;
	}
}

void check_zero(string op = 'A')
{
	if(registers[op]==0)
		flag['z'] = 1;
	else
		flag['z'] = 0;
}

void check_parity(string op = 'A'){
	int count=0;
	int a = registers[op];
	while(a)
	{
		a=a&(a-1);
		count++;
	}
	if(count%2==0)					//if number of 1 odd return 1 else return 0
		flag['p'] = 1;
	else
		flag['p'] = 0;
}
//void check_auxilary(string op = 'A')
//{

//}



void display()
{
    if(dp==0)
    {
        int i;
        ofstream code;
        code.open("outputFile.txt",ios::out);
        cout<<"Values in Registers:\n";
        code<<"Values in Registers:"<<endl;
        char ch;
        string s,f;
        for(ch='A';ch<='E';ch=ch+1)
        {
            s = dectohex(registers[ch]);
            transform(s.begin(), s.end(), s.begin(), ::toupper);
            f = ch;
            f = f+" : "+((s.size()==1)?("0"+s):s);
            cout<<f<<endl;
            code<<f<<endl;
        }

        s = dectohex(registers['H']);
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        f = "H : "+((s.size()==1)?("0"+s):s);
        cout<<f<<endl;
        code<<f<<endl;

        s = dectohex(registers['L']);
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        f = "L : "+((s.size()==1)?("0"+s):s);
        cout<<f<<endl;
        code<<f<<endl;

        cout<<"\nValues of Flags:\n";
        code<<"\nValues of Flags:"<<endl;
        f = "Z  : "+int_to_str(flag['z']);
        cout<<f<<endl;
        code<<f<<endl;
        f = "S  : "+int_to_str(flag['s']);
        cout<<f<<endl;
        code<<f<<endl;
        f = "C  : "+int_to_str(flag['c']);
        cout<<f<<endl;
        code<<f<<endl;
        f = "P  : "+int_to_str(flag['p']);
        cout<<f<<endl;
        code<<f<<endl;
        f = "AC : "+int_to_str(flag['a']);
        cout<<f<<endl;
        code<<f<<endl;

        cout<<"\nMemory Locations Used:"<<endl;
        code<<"\nMemory Locations Used:"<<endl;
        if(memoryLocationsUsed.size())
        {
            for(i=0;i<memoryLocationsUsed.size();i++)
            {
                s = dectohex(memory[memoryLocationsUsed[i]]);
                transform(s.begin(), s.end(), s.begin(), ::toupper);
                f=memoryLocationsUsed[i]+" : "+((s.size()==1)?("0"+s):s);
                cout<<f<<endl;
                code<<f<<endl;
            }
        }
        else
        {
            cout<<"None!"<<endl;
            code<<"None!"<<endl;
        }
        cout<<endl;
        code.close();
    }
}

*/











int check_operand(string ch)
{
    if(ch.compare("HLT")==0)
        return(0);
    else if(ch.compare("MOV")==0)
        return(1);
    else if(ch.compare("MVI")==0)
        return(2);
    else if(ch.compare("LXI")==0)
        return(3);
    else if(ch.compare("LDA")==0)
        return(4);
    else if(ch.compare("STA")==0)
        return(5);
    else if(ch.compare("LHLD")==0)
        return(6);
    else if(ch.compare("SHLD")==0)
        return(7);
    else if(ch.compare("STAX")==0)
        return(8);
    else if(ch.compare("XCHG")==0)
        return(9);
    else if(ch.compare("ADD")==0)
        return(10);
    else if(ch.compare("ADI")==0)
        return(11);
    else if(ch.compare("SUB")==0)
        return(12);
    else if(ch.compare("INR")==0)
        return(13);
    else if(ch.compare("DCR")==0)
        return(14);
    else if(ch.compare("INX")==0)
        return(15);
    else if(ch.compare("DCX")==0)
        return(16);
    else if(ch.compare("DAA")==0)
        return(17);
    else if(ch.compare("SUI")==0)
        return(18);
    else if(ch.compare("CMA")==0)
        return(19);
    else if(ch.compare("CMP")==0)
        return(20);
    else if(ch.compare("JMP")==0)
        return(21);
    else if(ch.compare("JC")==0)
        return(22);
    else if(ch.compare("JNC")==0)
        return(23);
    else if(ch.compare("JZ")==0)
        return(24);
    else if(ch.compare("JNZ")==0)
        return(25);
    else if(ch.compare("SET")==0)
        return(26);
    else
            return(-1);
}
