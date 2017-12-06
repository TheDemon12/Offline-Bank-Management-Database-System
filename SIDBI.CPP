#include<fstream.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
void bg()
{
	int i;
	char a=221;
	for(i=1;i<=25;i++)
	{
		gotoxy(77,i);
		cout<<a<<a;
	}
	for(i=25;i>=1;i--)
	{
		gotoxy(1,i);
		cout<<a<<a;
	}

}
void tell_date()
{
	date d;
	int da,m,y;
	getdate(&d);
	gotoxy(55,3);
	cout<<"DATE : ";
	da=d.da_day;
	m=d.da_mon;
	y=d.da_year;
	cout<<da<<"."<<m<<"."<<y;
}
class account
{
	char name[40],add[250],acctype;
	long accno;
	long float openamt,bankamt;
	char phone[12];
	public:

	void open();
	void close();
	void add_mon();
	void withdraw();
	void receipt();
	void transfer();
	void no_of_acc();
	void info_of_acc();
	void bankmon();
	void deleteacc();
}a1;

void account :: withdraw()
{
	K:
	clrscr();
	bg();
	tell_date();
	gotoxy(20,5);
	int acno,money,m,k;
	gotoxy(10,8);
	cout<<"ENTER YOUR ACC NO. : ";
	cin>>acno;
	gotoxy(10,9);
	L:
	k=0;m=0;
	gotoxy(10,10);
	cout<<"ENTER AMOUNT OF MONEY TO BE WITHDRAWN : ";
	cin>>money;
	ifstream fin("bank.dat",ios::binary);
	while(fin.read((char *)&a1,sizeof(account)))
	{
		if(a1.accno==acno)
		{
			k++;
			if(a1.bankamt<money)
				m++;
		}
	}
	fin.close();
	if (k==0)
	{
		char ch;
		gotoxy(12,12);
		cout<<"YOUR ACCOUNT NOT FOUND ! ENTER AGAIN (Y/N) : ";
		cin>>ch;
		if(ch=='y'||ch=='Y')
			goto K;
	}
	else if (m==1)
	{
		char ch;
		gotoxy(12,12);
		cout<<"INSUFFICIENT BALANCE IN YOUR ACCOUNT ! ENTER AGAIN (Y/N)";
		cin>>ch;
		if(ch=='y'||ch=='Y')
		{	clrscr();
			bg();
			tell_date();
			goto L;
		}
	}
	else
	{
		ifstream fin("bank.dat",ios::binary);
		ofstream fout("temp.dat",ios::binary);
		while(fin.read((char *)&a1,sizeof(account)))
		{
			if(a1.accno==acno)
			{
				gotoxy(8,10);
				a1.bankamt-=money;
			}
			fout.write((char *)&a1,sizeof(account));
		}
		gotoxy(20,15);
		cout<<"SUCCESSFULLY DONE ! ";
		fin.close();
		fout.close();
		remove("bank.dat");
		rename("temp.dat","bank.dat");
	}
	gotoxy(44,20);
	cout<<"PRESS ANY KEY TO GO BACK ...";
	getch();
}
void account :: add_mon()
{
	J:
	clrscr();
	bg();
	tell_date();
	gotoxy(20,5);
	int acno,money,k=0;
	gotoxy(10,8);
	cout<<"ENTER YOUR ACC NO. : ";
	cin>>acno;
	gotoxy(10,9);
	cout<<"INPUT THE AMT. OF MONEY TO BE ADDED : ";
	cin>>money;
	ifstream fin("bank.dat",ios::binary);
	while(fin.read((char*)&a1,sizeof(account)))
	{
		if(a1.accno==acno)
			{
				k++;
			}
	}
	fin.close();
	if(k==0)
	{
		char ch;
		gotoxy(12,12);
		cout<<"YOUR ACCOUNT NOT FOUND ! ENTER AGAIN (Y/N) : ";
		cin>>ch;
		if(ch=='y'||ch=='Y')
			goto J;
	}
	else
	{
		ifstream fin("bank.dat",ios::binary);
		ofstream fout("temp.dat",ios::binary);
		while(fin.read((char *)&a1,sizeof(account)))
		{
			if(a1.accno==acno)
			{
				a1.bankamt+=money;
			}
			fout.write((char *)&a1,sizeof(account));
		}
		gotoxy(20,15);
		cout<<"SUCCESSFULLY DONE ! ";
		fin.close();
		fout.close();
		remove("bank.dat");
		rename("temp.dat","bank.dat");

	}
	gotoxy(44,20);
	cout<<"PRESS ANY KEY TO GO BACK ...";
	getch();
}


void account :: transfer()
{
	H:
	clrscr();
	bg();
	tell_date();
	gotoxy(20,5);
	int acno,acno2,k,money,l,m;
	gotoxy(10,8);
	cout<<"ENTER YOUR ACC NO. : ";
	cin>>acno;
	gotoxy(10,9);
	cout<<"ENTER ACC NO. OF THE PERSON IN WHICH YOU HAVE TO TRANSFER CASH : ";
	cin>>acno2;
	I:
	k=0;l=0;m=0;
	gotoxy(10,10);
	cout<<"ENTER AMOUNT OF MONEY TO BE TRANSFERRED : ";
	cin>>money;
	ifstream fin("bank.dat",ios::binary);
	while(fin.read((char *)&a1,sizeof(account)))
	{
		if(a1.accno==acno)
		{
			k++;
			if(a1.bankamt<money)
				m++;
		}
		else if (a1.accno==acno2)
		{
			l++;
		}
	}
	fin.close();
	if (k==0)
	{
		char ch;
		gotoxy(12,12);
		cout<<"YOUR ACCOUNT NOT FOUND ! ENTER AGAIN (Y/N) : ";
		cin>>ch;
		if(ch=='y'||ch=='Y')
			goto H;
	}
	else if (l==0)
	{
		char ch;
		gotoxy(12,12);
		cout<<"RECIEVER'S ACCOUNT NOT FOUND ! ENTER AGAIN (Y/N) : ";
		cin>>ch;
		if(ch=='y'||ch=='Y')
			goto H;
	}
	else if (m==1)
	{
		char ch;
		gotoxy(12,12);
		cout<<"INSUFFICIENT BALANCE IN YOUR ACCOUNT ! ENTER AGAIN (Y/N)";
		cin>>ch;
		if(ch=='y'||ch=='Y')
		{	clrscr();
			bg();
			tell_date();
			goto I;
		}
	}
	else
	{
		ifstream fin("bank.dat",ios::binary);
		ofstream fout("temp.dat",ios::binary);
		while(fin.read((char *)&a1,sizeof(account)))
		{
			if(a1.accno==acno)
			{
				gotoxy(8,10);
				a1.bankamt-=money;
			}
			if (a1.accno==acno2)
			{
				gotoxy(8,10);
				a1.bankamt+=money;
			}
			gotoxy(10,11);
			fout.write((char*)&a1,sizeof(account));
		}
		gotoxy(20,15);
		cout<<"SUCCESSFULLY DONE ! ";
		fin.close();
		fout.close();
		remove("bank.dat");
		rename("temp.dat","bank.dat");
	}
	gotoxy(44,20);
	cout<<"PRESS ANY KEY TO GO BACK ...";
	getch();
}
void account :: receipt()
{
	G:
	clrscr();
	bg();
	tell_date();
	gotoxy(20,5);
	int acno,k=0;
	gotoxy(20,8);
	cout<<"ENTER YOUR ACC NO. : ";
	cin>>acno;
	ifstream fin("bank.dat",ios::binary);
	while(fin.read((char *)&a1,sizeof(account)))
	{
		if(a1.accno==acno)
		{
			gotoxy(8,10);
			cout<<"______________________________________";
			gotoxy(24,11);
			cout<<"RECEIPT";
			gotoxy(8,13);
			cout<<"NAME : "<<a1.name;
			gotoxy(8,14);
			cout<<"ADDRESS : "<<a1.add;
			gotoxy(8,15);
			cout<<"PHONE NO : "<<a1.phone;
			gotoxy(8,16);
			cout<<"ACCOUNT BALANCE : "<<a1.bankamt;
			gotoxy(8,17);
			if(a1.acctype=='c'||a1.acctype=='C')
				cout<<"ACCOUNT TYPE : CURRENT ACCOUNT";
			else
				cout<<"ACCOUNT TYPE : SAVINGS ACCOUNT";
			gotoxy(8,18);
			cout<<"______________________________________";
			k++;
		}

	}
	fin.close();
	if(k==0)
		{
			char ch;
			gotoxy(20,10);
			cout<<"NO ACCOUNT FOUND ! ENTER AGAIN ? (Y/N) : ";
			cin>>ch;
				if(ch=='Y'||ch=='y')
					goto G;
		}
	gotoxy(44,20);
	cout<<"PRESS ANY KEY TO GO BACK ...";
	getch();
}

void account :: info_of_acc()
{
	clrscr();
	bg();
	tell_date();
	gotoxy(20,5);
	int acno,k=0;
	char ch;
	ifstream fin("bank.dat",ios::binary);
	while(fin.read((char *)&a1,sizeof(account)))
	{
			K:
			clrscr();
			bg();
			tell_date();
			gotoxy(8,5);
			cout<<"ACCOUNT NO. : "<<a1.accno;
			gotoxy(8,6);
			cout<<"NAME : "<<a1.name;
			gotoxy(8,7);
			cout<<"ADDRESS : "<<a1.add;
			gotoxy(8,8);
			cout<<"PHONE NO : "<<a1.phone;
			gotoxy(8,9);
			cout<<"ACCOUNT BALANCE : "<<a1.bankamt;
			gotoxy(8,10);
			if(a1.acctype=='c'||a1.acctype=='C')
				cout<<"ACCOUNT TYPE : CURRENT ACCOUNT";
			else
				cout<<"ACCOUNT TYPE : SAVINGS ACCOUNT";
			gotoxy(4,14);
			cout<<"PRESS G TO SEE PREVIOUS ACC.";
			gotoxy(50,14);
			cout<<"PRESS N TO SEE NEXT ACC.";
			gotoxy(24,16);
			cout<<"PRESS E TO GO BACK FROM THIS MENU";
			gotoxy(33,18);
			cout<<("CHOOSE ONE : ");
			cin>>ch;
				if(ch=='g'||ch=='G')
				{
					int i=-2*sizeof(account);
					fin.seekg(i,ios::cur);
				}
				else if (ch=='e'||ch=='E')
					break;
				else if (ch=='n'||ch=='N')
				{
					
				}
				else 
				{
					gotoxy(32,20);
					cout<<"INVALID OPTION!";
					delay(1000);
					goto K;
				}	
				if(fin.eof()==0)
				{
					gotoxy(30,20);
					cout<<"NO MORE RECORDS FOUND !";
				}	
				
	}
	fin.close();
	gotoxy(44,23);
	cout<<"PRESS ANY KEY TO GO BACK ...";
	getch();
}
char user_log_menu()
{
		clrscr();
		bg();
		tell_date();
		char i;
		gotoxy(37,8);
		cout<<"SIDBI";
		gotoxy(26,10);
		cout<<"1. CREATE A NEW ACCOUNT";
		gotoxy(26,11);
		cout<<"2. ADD MONEY TO YOUR ACCOUNT";
		gotoxy(26,12);
		cout<<"3. WITHDRAW MONEY FROM YOUR ACCOUNT";
		gotoxy(26,13);
		cout<<"4. TRANSFER MONEY TO ANOTHER ACCOUNT";
		gotoxy(26,14);
		cout<<"5. GET A RECEIPT";
		gotoxy(26,15);
		cout<<"6. GO BACK";
		gotoxy(26,16);
		cout<<"7. EXIT";
		gotoxy(26,18);
		cout<<"CHOOSE ONE : ";
		cin>>i;
		return i;
}
char master_log_menu()
{
		clrscr();
		bg();
		tell_date();
		char i;
		gotoxy(37,8);
		cout<<"SIDBI";
		gotoxy(26,10);
		cout<<"1. TOTAL NO. OF ACCOUNT HOLDERS";
		gotoxy(26,11);
		cout<<"2. SEE INFO OF EVERY ACCOUNT HOLDER";
		gotoxy(26,12);
		cout<<"3. TO SEE TOTAL AMT. OF MONEY IN THE BANK";
		gotoxy(26,13);
		cout<<"4. DELETE SOMEONE'S ACCOUNT";
		gotoxy(26,14);
		cout<<"5. GO BACK";
		gotoxy(26,15);
		cout<<"6. EXIT";
		gotoxy(26,17);
		cout<<"CHOOSE ONE : ";
		cin>>i;
		return i;
}
void aknw()
{
	clrscr();	//ACKNOWLGEDGEMENT
	tell_date();
	bg();
	gotoxy(5,5);
	cout<<"A USER FRIENDLY SOFTWARE FOR A BANK AS WELL AS FOR A USER WHICH HELPS";
	gotoxy(5,6);
	cout<<"THEM TO MAKE ACCOUNTS, SEE STATUS, DEPOSIT, WITHDRAW AND MUCH MORE !";
	gotoxy(5,7);
	cout<<"FOR BANKS, IT HELPS IN VIEWING STATUS OF ACCOUNTS IN THE BANK , NUMBER";
	gotoxy(5,8);
	cout<<"OF THE ACCOUNTS AND MORE !";
	gotoxy(30,10);
	cout<<"DEVELOPED BY : ";
	gotoxy(30,12);
	cout<<"KARTIK BHALLA";
	gotoxy(30,13);
	cout<<"IKSHIT BANSAL";
	gotoxy(44,20);
	cout<<"PRESS ANY KEY TO GO BACK ...";
	getch();
}

void account :: open()
{
	E:
	clrscr();
	int max=0;
	bg();
	tell_date();
	ifstream fin("bank.dat",ios::binary);
	while(fin.read((char *)&a1,sizeof(account)))
	{
		if(max<a1.accno)
		{
			max=a1.accno;
		}
	}
	fin.close();
	gotoxy(8,5);
	cout<<"ENTER THE NAME :";
	gets(name);
	gotoxy(8,6);
	cout<<"ENTER THE ADDRESS :";
	gets(add);
	gotoxy(8,7);
	cout<<"ENTER THE PHONE :";
	cin>>phone;
	gotoxy(8,8);
	cout<<"TYPE OF ACCOUNT - CURRENT OR SAVING? (C/S) : ";
	cin>>acctype;
	if(acctype=='S' || acctype=='C'||acctype=='s' || acctype=='c')
	{
		goto F;
	}
	else
	{
		gotoxy(26,18);
		cout<<"INVALID OPTION ! ";
		delay(1000);
		goto E;
	}

	F:
	gotoxy(25,12);
	cout<<"ENTER THE OPENING AMOUNT :";
	cin>>openamt;
	if(openamt<500)
	{
		gotoxy(25,14);
		cout<<"MINIMUM OPENING AMOUNT FOR ACC IS Rs. 500 ";
		gotoxy(25,15);
		cout<<"ENTER AGAIN ! ";
		delay(1000);
		gotoxy(25,16);
		goto F;
	}
	bankamt=openamt;
	accno=max+1;
	ofstream fout("bank.dat",ios::binary|ios::app); 
	fout.write((char *)&a1,sizeof(account));
	gotoxy(25,16);
	cout<<"YOUR ACCOUNT NUMBER IS : "<<accno;
	fout.close();
	gotoxy(44,20);
	cout<<"PRESS ANY KEY TO GO BACK..";
	getch();
}

void account :: bankmon()
{
	clrscr();
	bg();
	tell_date();
	int m=0;
	ifstream fin ("bank.dat",ios::binary);
	while(fin.read((char *)&a1,sizeof(account)))
	{
		m+=a1.bankamt;
	}
	fin.close();
	gotoxy(25,10);
	cout<<"TOTAL MONEY IN BANK : "<<m;
	gotoxy(44,20);
	cout<<"PRESS ANY KEY TO GO BACK ...";
	getch();
	
}

void account :: deleteacc()
{
	J:
	clrscr();
	bg();
	tell_date();
	int acno,money,k=0,l=0;
	char o;
	gotoxy(20,4);
	cout<<"ENTER ACC NO. TO BE DELETED : ";
	cin>>acno;
		
		ifstream fin("bank.dat",ios::binary);
		while(fin.read((char*)&a1,sizeof(account)))
		{
			if(a1.accno==acno)
			{
				gotoxy(8,10);
				cout<<"NAME : "<<a1.name;
				gotoxy(8,11);
				cout<<"ADDRESS : "<<a1.add;
				gotoxy(8,12);
				cout<<"PHONE NO : "<<a1.phone;
				gotoxy(8,13);
				cout<<"ACCOUNT BALANCE : "<<a1.bankamt;
				gotoxy(8,14);
				if(a1.acctype=='c'||a1.acctype=='C')
					cout<<"ACCOUNT TYPE : CURRENT ACCOUNT";
				else
					cout<<"ACCOUNT TYPE : SAVINGS ACCOUNT";
				k++;
				gotoxy(17,16);
				cout<<"YOU SURE TO DELETE THE ACCOUNT? (Y/N) : ";
				cin>>o;
				if (o=='y'||o=='Y')
					l++;
			}
		}
		fin.close();
		if(k==0)
		{
			char ch;
			gotoxy(17,12);
			cout<<"ACCOUNT NOT FOUND ! ENTER AGAIN (Y/N) : ";
			cin>>ch;
			if(ch=='y'||ch=='Y')
				goto J;
		}
		else if(l==0)
		{
			
		}
		else
		{
			ifstream fin("bank.dat",ios::binary);
			ofstream fout("temp.dat",ios::binary);
			while(fin.read((char *)&a1,sizeof(account)))
			{
				if(a1.accno==acno)
				{
					continue;
				}
				fout.write((char *)&a1,sizeof(account));
			}
			gotoxy(23,17);
			cout<<"SUCCESSFULLY DELETED ! ";
			fin.close();
			fout.close();
			remove("bank.dat");
			rename("temp.dat","bank.dat");

		}
	gotoxy(44,20);
	cout<<"PRESS ANY KEY TO GO BACK ...";
	getch();
}
void account :: no_of_acc()
{
	clrscr();
	bg();
	tell_date();
	int i=10,m=0;
	gotoxy(25,5);
	cout<<"ACCOUNT HOLDERS ARE : ";
	gotoxy(20,8);
	cout<<"ACC. No.";
	gotoxy(30,8);
	cout<<"NAME";
	ifstream fin ("bank.dat",ios::binary);
	while(fin.read((char *)&a1,sizeof(account)))
	{
		gotoxy(20,i);
		cout<<a1.accno;
		gotoxy(30,i);
		cout<<a1.name;
		i++;
		m++;
	}
	fin.close();
	gotoxy(12,i+4);
	cout<<"TOTAL NO. OF ACCOUNTS : "<<m;
	gotoxy(44,20);
	cout<<"PRESS ANY KEY TO GO BACK ...";
	getch();

}
void main()
{
	clrscr();
	bg();
	tell_date();
	gotoxy(18,10);
	cout<<"SMALL INDUSTRIES DEVELOPMENT BANK OF INDIA";
	gotoxy(44,20)                        ;
	cout<<"PRESS ANY KEY TO CONTINUE...";
	getch();
	char p;
	A:
	clrscr();
	tell_date();
	bg();
	gotoxy(16,10);
	cout<<"WELCOME TO SIDBI BANK! WE ARE THERE FOR YOU!";
	gotoxy(20,12);
	cout<<"1. ACKNOWLGEDGEMENT";
	gotoxy(20,13);
	cout<<"2. MENU";
	gotoxy(20,14);
	cout<<"3. EXIT";
	gotoxy(20,16);
	cout<<"CHOOSE ONE : ";
	cin>>p;
	if (p=='1')
	{
		aknw();
		goto A;
	}
	else if (p=='2')
	{
		//main menu
		B:
		clrscr();
		tell_date();
		bg();
		gotoxy(20,9);
		cout<<"SIDBI BANK! WE ARE HAPPY TO HELP YOU!";
		gotoxy(26,11);
		cout<<"1. USER LOGIN ";
		gotoxy(26,12);
		cout<<"2. MASTER LOGIN ";
		gotoxy(26,13);
		cout<<"3. GO BACK ";
		gotoxy(26,14);
		cout<<"4. EXIT ";
		gotoxy(26,16);
		cout<<"CHOOSE ONE : ";
		char i,m;
		cin>>i;
		if(i=='1')
		{
			D:
			m=user_log_menu();
			if (m=='1')
			{
				char ch;
				gotoxy(10,20);
				cout<<"WARNING! YOU WON'T BE ABLE TO EXIT DURING THE PROCESS! ";
				gotoxy(27,21);
				cout<<"PRESS Y TO CONTINUE : ";
				cin>>ch;
				if(ch=='y'||ch=='Y')
				{
					a1.open();
					goto D;
				}
				else
					goto D;
			}
			else if (m=='2')
			{
				char ch;
				gotoxy(10,20);
				cout<<"WARNING! YOU WON'T BE ABLE TO EXIT DURING THE PROCESS! ";
				gotoxy(27,21);
				cout<<"PRESS Y TO CONTINUE : ";
				cin>>ch;
				if(ch=='y'||ch=='Y')
				{
					a1.add_mon();
					goto D;
				}
				else
					goto D;
			}
			else if (m=='3')
			{
				char ch;
				gotoxy(10,20);
				cout<<"WARNING! YOU WON'T BE ABLE TO EXIT DURING THE PROCESS! ";
				gotoxy(27,21);
				cout<<"PRESS Y TO CONTINUE : ";
				cin>>ch;
				if(ch=='y'||ch=='Y')
				{
					a1.withdraw();
					goto D;
				}
				else
					goto D;
			}
			else if (m=='4')
			{
				char ch;
				gotoxy(10,20);
				cout<<"WARNING! YOU WON'T BE ABLE TO EXIT DURING THE PROCESS! ";
				gotoxy(27,21);
				cout<<"PRESS Y TO CONTINUE : ";
				cin>>ch;
				if(ch=='y'||ch=='Y')
				{
					a1.transfer();
					goto D;
				}
				else
					goto D;
			}
			else if (m=='5')
			{
				char ch;
				gotoxy(10,20);
				cout<<"WARNING! YOU WON'T BE ABLE TO EXIT DURING THE PROCESS! ";
				gotoxy(27,21);
				cout<<"PRESS Y TO CONTINUE : ";
				cin>>ch;
				if(ch=='y'||ch=='Y')
				{
					a1.receipt();
					goto D;
				}
				else
					goto D;
			}
			else if (m=='6')
			{
				goto B;
			}
			else if (m=='7')
			{
			gotoxy(44,20);
			cout<<"BYE BYE,CLOSING NOW ...";
			delay(1000);
			exit(0);
			}
			else
			{
				gotoxy(26,19);
				cout<<"INVALID OPTION ! ";
				delay(1000);
				goto D;
			}
		}
		else if(i=='2')
		{
			C:		//master_login
			clrscr();
			bg();
			tell_date();
			char pass[20];
			gotoxy(30,5);
			cout<<"ENTER PASSWORD : ";
			//gets(pass);
			for(int i=0;i<8;i++)
			{
				pass[i]=getch();
				cout<<"*";
			}
			pass[8]='\0';
			char oripass[20];
			strcpy(oripass,"dayanand");
			if (strcmpi(oripass,pass)==0)
			{
				gotoxy(35,7);
				cout<<"ACCESS GRANTED!";
				delay(500);
				M:			
				char m;
				m=master_log_menu();
				if (m=='1')
				{
					char ch;
					gotoxy(10,20);
					cout<<"WARNING! YOU WON'T BE ABLE TO EXIT DURING THE PROCESS! ";
					gotoxy(27,21);
					cout<<"PRESS Y TO CONTINUE : ";
					cin>>ch;
					if(ch=='y'||ch=='Y')
					{	
						a1.no_of_acc();
						goto M;
					}
					else 
						goto M;
				}
				else if(m=='2')
				{
					char ch;
					gotoxy(10,20);
					cout<<"WARNING! YOU WON'T BE ABLE TO EXIT DURING THE PROCESS! ";
					gotoxy(27,21);
					cout<<"PRESS Y TO CONTINUE : ";
					cin>>ch;
					if(ch=='y'||ch=='Y')
					{	
						a1.info_of_acc();
						goto M;
					}
					else 
						goto M;
				}
				else if(m=='3')
				{
					char ch;
					gotoxy(10,20);
					cout<<"WARNING! YOU WON'T BE ABLE TO EXIT DURING THE PROCESS! ";
					gotoxy(27,21);
					cout<<"PRESS Y TO CONTINUE : ";
					cin>>ch;
					if(ch=='y'||ch=='Y')
					{	
						a1.bankmon();
						goto M;
					}
					else 
						goto M;
				}
				else if(m=='4')
				{
					char ch;
					gotoxy(10,20);
					cout<<"WARNING! YOU WON'T BE ABLE TO EXIT DURING THE PROCESS! ";
					gotoxy(27,21);
					cout<<"PRESS Y TO CONTINUE : ";
					cin>>ch;
					if(ch=='y'||ch=='Y')
					{	
						a1.deleteacc();
						goto M;
					}
					else 
						goto M;
				}
				else if(m=='5')
					goto B;
				else if (m=='6')
				{
					gotoxy(44,20);
					cout<<"BYE BYE,CLOSING NOW ...";
					delay(1000);
					exit(0);
				}
				else
				{
					gotoxy(26,19);
					cout<<"INVALID OPTION ! ";
					delay(1000);
					goto M;
				}
			}
			else
			{
				gotoxy(35,7);
				cout<<"ACCESS DENIED!";
				char m;
				gotoxy(30,9);
				cout<<"ENTER AGAIN ? (Y/N) ";
				cin>>m;
				if(m=='y'||m=='Y')
					goto C;
				else
					goto B;
			}	
		}
		else if (i=='3')
			goto A;
		else if (i=='4')
		    {
			gotoxy(44,20);
			cout<<"BYE BYE,CLOSING NOW ...";
			delay(1000);
			exit(0);
		    }
		else
		{
			gotoxy(30,17);
			cout<<"INVALID OPTION ! ";
			delay(1000);
			goto B;
		}
	}
	else if (p=='3')
	{
		gotoxy(44,20);
		cout<<"BYE BYE,CLOSING NOW ...";
		delay(1000);
		exit(0);
	}
	else
	{
		gotoxy(24,17);
		cout<<"INVALID OPTION ! ";
		delay(1000);
		goto A;
	}
	getch();
}