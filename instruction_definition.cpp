//1st instruction
void MOV(char op1,char op2)
{
    if(!check_register(op1)){
        cout<<op1<<" is invalid register"<<endl;
        exit(1);
    }
    if(!check_register(op2)){
        cout<<op2<<" is invalid register"<<endl;
        exit(1);
    }
	if(op1!='M' && op2!='M')
	{
		registers[op1]=registers[op2];
	}
	else  //if it is memory
	{
		int address=registers['H']*256+registers['L'];
		if(op1=='M')
		{
			memory[dectohex(address)]=registers[op2];
		}
		else
		{
			registers[op1]=memory[dectohex(address)];
		}
	}
}

//2nd instruction
void MVI(string op,string value)
{
    if(!check_register(op))
    {
        cout<<op<<" is invalid register"<<endl;
        exit(1);
    }
	registers[op]=hextodec(value);
}

//3rd instruction
void LXI(string op,string value)
{
	string value_H;
	value_H = value.substr(0,2);
	string value_L;
	value_L = value.substr(2,2);
	registers['H']=hextodec(value_H);
	registers['L']=hextodec(value_L);
}



//4th instruction
void LDA(string address)
{
	registers['A']=memory[address];
}


//5th instruction
void STA(string address)
{
	memory[address]=registers['A'];
}


//6th instruction
void LHLD(string address)
{
	int tmp=hextodec(address);
    registers['H']=memory[address];
    registers['L']=memory[dectohex(tmp+1)];
}


//7th instruction
void SHLD(string address)
{
	int tmp=hextodec(address);
	memory[address]=registers['L'];
	memory[dectohex(tmp+1)]=registers['H'];
}

//8th instruction
void STAX(string op)
{
	string h;
	int d;
	switch(op)
		{
			case 'B':
                    h=dectohex(registers['B'])+dectohex(registers['C']);
                    d=hextodec(h);
                    memory[h]=registers['A'];
                    break;
			case 'D':
                    h=dectohex(registers['D'])+dectohex(registers['E']);
                    d=hextodec(h);
                    memory[h]=registers['A'];
                    break;
			case 'H':
                    h=dectohex(registers['H'])+dectohex(registers['L']);
                    d=hextodec(h);
                    memory[h]=registers['A'];
                    break;
            default:cout<<op<<" is invalid"<<endl;
                    break;
        }
}


//9th instruction
void XCHG()
{
	int tmp;
	tmp=registers['D'];
	registers['D']=registers['H'];
	registers['H']=tmp;
	tmp=registers['E'];
	registers['E']=registers['L'];
	registers['L']=tmp;
}

//10th instruction
void ADD(string op)
{
    if(!check_register(s1)){
        cout<<"invalid register"<<endl;
        exit(1);
    }
	if(op=='M')
    {
        string str = dectohex(registers['L']);
		string address=dectohex(registers['H'])+((str.size()==1)?("0"+str):str);
		registers['A']+=memory[address];
	}
	else
		registers['A']+=registers[op];

    changes_flag();
}

//11th instruction
void ADI(string val)
{
	registers['A']+=hextodec(value);
	changes_flag();
}

//12th instruction
void SUB(string op)
{
	if(op=='M')
    {
		string str = dectohex(registers['L']);
		string address=dectohex(registers['H'])+((str.size()==1)?("0"+str):str);
		registers['A']-=memory[address];
	}
	else
		registers['A']-=registers[op];

    changes_flag();
}


//13th instruction
void INR(string op)
{
	registers[op]++;
	if(registers[op]>255)
    {
		registers[op]%=256;
	}
	check_carry();
	check_sign(op);
	check_zero(op);
	check_parity(op);
	check_auxilary(op);
}


//14th instruction
void DCR(string op)
{
	registers[op]--;
	if(registers[op]<0)
    {
		registers[op]+=256;
	}
	check_carry();
	check_sign(op);
	check_zero(op);
	check_parity(op);
	check_auxilary(op);
}


//15th instruction
void INX(string op)
{
	if(op=='B')
    {
        if(registers['C']==127)
        {
			registers['C']=0;
			if(registers['B']==127)
				registers['B']=0;
		}
		else
			registers['C']++;
	}
	else if(op=='D')
	{
		if(registers['E']==127)
		{
			registers['E']=0;
			if(registers['D']==127)
				registers['D']=0;
		}
		else
			registers['E']++;
	}
	else if(op=='H')
	{
		if(registers['L']==127)
		{
			registers['L']=0;
			if(registers['H']==127)
				registers['H']=0;
		}
		else
			registers['L']++;
	}
}

//16th instruction
void DCX(string op)
{
	if(op=='B')
    {
		if(registers['C']==-128)
		{
			registers['C']=0;
			if(registers['B']==-128)
				registers['B']=0;
		}
		else
			registers['C']--;
	}
	else if(op=='D')
	{
		if(registers['E']==-128)
		{
			registers['E']=0;
			if(registers['D']==-128)
				registers['D']=0;
		}
		else
			registers['E']--;
	}
	else if(op=='H')
	{
		if(registers['L']==-128)
		{
			registers['L']=0;
			if(registers['H']==-128)
				registers['H']=0;
		}
		else
			registers['L']--;
	}
}

//17th instruction
void DAD(string op)
{
	int carry,sum;
	switch(op)
	{
		case 'B':
                sum=registers['C']+registers['L'];
                registers['L']=sum%256;
                carry=sum/256;
                sum=registers['B']+registers['H']+carry;
                registers['H']=sum%256;
                flag['c']=sum/256;
                break;
		case 'D':
                sum=registers['E']+registers['L'];
                registers['L']=sum%256;
                carry=sum/256;
                sum=registers['D']+registers['H']+carry;
                registers['H']=sum%256;
                flag['c']=sum/256;
                break;
		case 'H':
                sum=registers['L']+registers['L'];
                registers['L']=sum%256;
                carry=sum/256;
                sum=registers['H']+registers['H']+carry;
                registers['H']=sum%256;
                flag['c']=sum/256;
                break;
	}
}


//18th instruction
void SUI(string value)
{
	registers['A']-=hextodec(value);
	changes_flag();
}


//19th instruction
void CMA()
{
	registers['A']=255-registers['A'];
}

//20th instruction
void CMP(string op) //comparing register with accumulator
{
    if(op=='M')
    {
        string address = dectohex(registers['H']*256+registers['L']);
        if(registers['A']>memory[address])//if memory is used
        {
            flag['c']=0;
            flag['z']=0;
        }
        else
        {
            if(registers['A']==memory[address])
            {
                flag['z']=1;	//only zero flag get affected
            }
            else
            {
                flag['c']=1;	//if register content is greater then accumulator carry set
            }
        }
    }
    else
    {
        if(registers['A']>registers[operand])
        {
            flag['c']=0; //carry and zero flag get affected
            flag['z']=0;
        }
        else
        {
            if(registers['A']==registers[operand])
            {
                flag['z']=1;	//only zero flag get affected
            }
            else
            {
                flag['c']=1;	//if register content is greater then accumulator carry set
            }
        }
    }
}

//21st instruction
void JMP(string address)
{
	program_counter=address;
	pc = hextodec(program_counter);
}

//22nd instruction
void JC(string address)
{
	transform(address.begin(), address.end(), address.begin(), ::tolower);
	if(flag['c']==1)
    {
		program_counter=address;
		pc = hextodec(program_counter);
	}
	else
	{
		pc += 3;
		program_counter = dectohex(pc);
	}
}

//23th instruction
void JNC(string address)
{
	transform(address.begin(), address.end(), address.begin(), ::tolower);
	if(flag['c']==0)
    {
		program_counter=address;
		pc = hextodec(program_counter);
	}
	else
    {
		pc += 3;
		program_counter = dectohex(pc);
	}
}


//24th instruction
void JZ(string address)
{
	transform(address.begin(), address.end(), address.begin(), ::tolower);
	if(flag['z']==1)
    {
		program_counter=address;
		pc = hextodec(program_counter);
	}
	else
    {
		pc += 3;
		program_counter = dectohex(pc);
	}
}

//25th instruction
void JNZ(string address)
{
	transform(address.begin(), address.end(), address.begin(), ::tolower);
	if(flag['z']==0)
    {
		program_counter=address;
		pc = hextodec(program_counter);
	}
	else
    {
		pc += 3;
		program_counter = dectohex(pc);
	}
}

//26th instruction
void SET(string mem,string value)
{
	memory[mem]=hextodec(value);
}



void changes_flag()
{
    check_carry();
	check_sign();
	check_zero();
	check_parity();
	check_auxilary();
}




/*for(int i=0000;i<hextodec(ffff);i++)
{
    memory[dectohex(i)]=0;
}*/
