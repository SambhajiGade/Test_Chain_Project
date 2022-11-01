#include <iostream>
#include <string>
#include <time.h>
#include "sha256.h"
#include <fstream>
#include <limits>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;

string timestamp();

//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//

struct Block
{
	string data;
	string prev_hashKey;
	string hashKey;
	int BlockNum;
	Block *next;
	Block *prev;
	long long nonce;
};

//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//

class chain
{
public:
	Block *GenesisBlock = NULL;

	void insert(string data)
	{
		data += " ";
		data += timestamp();
		data += " ";
		int length = data.length();
		Block *NewBlock = new Block;
		Block *pntr = GenesisBlock;
		Block *previous_ptr = GenesisBlock;

		if (GenesisBlock == NULL)
		{

			NewBlock->hashKey = sha256(data);
			string temp;
			if (!(NewBlock->hashKey[0] == '0' && NewBlock->hashKey[1] == '0' && NewBlock->hashKey[2] == '0' && NewBlock->hashKey[3] == '0' && NewBlock->hashKey[4] == '0'))
			{
				temp = data;
				NewBlock->nonce += 1;

				std::string s = std::to_string(NewBlock->nonce);

				temp += s;
				std::cout << endl
						  << "\tdata = " << temp << "\n";

				NewBlock->hashKey = sha256(temp);
			}
			std::cout << "\n\tnonce = " << NewBlock->nonce << '\n';
			NewBlock->prev_hashKey = "0000000000000000000000000000000000000000000000000000000000000000";
			NewBlock->data = data;
			NewBlock->BlockNum = 1;
			NewBlock->next = NULL;
			std::cout << "\n\tBlock NO = " << NewBlock->BlockNum << endl
					  << endl;
			GenesisBlock = NewBlock;
		}

		else
		{
			int counter = 0;
			while (pntr != NULL)
			{
				previous_ptr = pntr;
				pntr = pntr->next;
				counter++;
			}
			previous_ptr->next = NewBlock;
			NewBlock->hashKey = sha256(data);
			string temp;
			if (!(NewBlock->hashKey[0] == '0' && NewBlock->hashKey[1] == '0' && NewBlock->hashKey[2] == '0' && NewBlock->hashKey[3] == '0' && NewBlock->hashKey[4] == '0'))
			{
				temp = data;
				NewBlock->nonce += 1;

				std::string s = std::to_string(NewBlock->nonce);
				temp += s;
				std::cout << "\n\tdata = " << temp << '\n';
				NewBlock->hashKey = sha256(temp);
			}
			std::cout << "\n\tnonce = " << NewBlock->nonce << '\n';
			NewBlock->prev_hashKey = previous_ptr->hashKey;

			NewBlock->prev = previous_ptr;
			NewBlock->data = data;
			NewBlock->BlockNum = counter + 1;

			std::cout << endl
					  << "\tBlock NO = " << NewBlock->BlockNum << endl
					  << "\n";
			NewBlock->next = NULL;
		}
	}

	//------------------------------------------------------------------------------------------------------//
	//------------------------------------------------------------------------------------------------------//

	void print()
	{
		Block *curr = GenesisBlock;
		if (curr == NULL)
		{
			cout << endl
				 << "\n\t-------------------------------------" << endl;
			std::cout << "Nothing to print" << '\n';
			cout << "\t-------------------------------------" << endl;
		}
		else
		{

			cout << endl
				 << "\n\t-------------------------------------" << endl;
			cout << "\tBlockNum:  " << curr->BlockNum << endl;
			cout << "\tData:  " << curr->data << endl;
			cout << "\tHash Key:  " << curr->hashKey << endl;
			cout << "\tPrevious Hash Key:  " << curr->prev_hashKey << endl;
			cout << "\tNonce :" << curr->nonce << endl;
			cout << "\t-------------------------------------" << endl;
			if (curr->next != NULL)
			{

				do
				{
					curr = curr->next;

					cout << endl
						 << "\n\t-------------------------------------" << endl;
					cout << "\tBlockNum:  " << curr->BlockNum
						 << endl;
					cout << "\tData:  " << curr->data << endl;
					cout << "\tHash Key:  " << curr->hashKey << endl;
					cout << "\tPrevious Hash Key:  " << curr->prev_hashKey << endl;
					cout << "\tNonce :" << curr->nonce << endl;
					cout << "\t-------------------------------------" << endl;
				} while (curr->next != NULL);
			}
		}
	}

	//------------------------------------------------------------------------------------------------------//
	//------------------------------------------------------------------------------------------------------//

	void printBlock(int num)
	{
		Block *curr = GenesisBlock;
		if (curr == NULL)
		{
			cout << endl
				 << "\n\t-------------------------------------" << endl;
			std::cout << "Nothing to print" << '\n';
			cout << "\t-------------------------------------" << endl;
		}
		else
		{

			for (size_t i = 1; i < num; i++)
			{
				curr = curr->next;
			}
			cout << endl
				 << "\n\t-------------------------------------" << endl;
			cout << "\tBlockNum:  " << curr->BlockNum << endl
				 << endl;
			cout << "\tData:  " << curr->data << endl;
			cout << "\tHash Key:  " << curr->hashKey << endl;
			cout << "\tPrevious Hash Key:  " << curr->prev_hashKey << endl;
			cout << "\tNonce :" << curr->nonce << endl;
			cout << "\t-------------------------------------" << endl
				 << endl;
		}
	}

	//------------------------------------------------------------------------------------------------//
	//------------------------------------------------------------------------------------------------//

	void writetofile()
	{
		Block *curr = GenesisBlock;

		ofstream SamG("SamG.txt");

		if (curr == NULL)
		{
			SamG << endl
				 << "\t-------------------------------------" << endl;
			SamG << "\t\tNothing to print" << '\n';
			SamG << "\t-------------------------------------" << endl;

			cout << "\n\t\tFirst give some data" << endl;
		}
		else
		{

			string alldata;

			//	ofstream SamG("SamG.txt");

			SamG << "\t--------------------------------------\n\n";
			SamG << "\tBlockNum:  " << curr->BlockNum << endl;
			SamG << "\n\tData:  " + curr->data;
			SamG << "\n\tHash Key:  " + curr->hashKey;
			SamG << "\n\n\tPrevious Hash Key:  " + curr->prev_hashKey;
			SamG << "\n\n\tNonce :" << curr->nonce << endl;
			SamG << "\n\t-------------------------------------\n\n";

			if (curr->next != NULL)
			{

				do
				{
					curr = curr->next;

					SamG << "\t-----------------------------------------\n\n";
					SamG << "\tBlockNum:  " << curr->BlockNum << endl;
					SamG << "\n\tData:  " + curr->data;
					SamG << "\n\tHash Key:  " + curr->hashKey;
					SamG << "\n\n\tPrevious Hash Key:  " + curr->prev_hashKey;
					SamG << "\n\n\tNonce :" << curr->nonce << endl;
					SamG << "\n\t---------------------------------------\n\n";
				} while (curr->next != NULL);
			}

			//	SamG.close();

			cout << endl
				 << "\tData is successfully added" << endl;
		}

		SamG.close();
	}

	//--------------------------------------------------------------------------------//
	//--------------------------------------------------------------------------------//

	void readFromFile()
	{
		string SamT;

		ifstream SamG("SamG.txt");

		while (getline(SamG, SamT))
		{

			cout << endl
				 << SamT;
		}

		SamG.close();
	}

	//------------------------------------------------------------------------------------------------------//
	//------------------------------------------------------------------------------------------------------//

	int validity(int no)
	{
		Block *ptr = GenesisBlock;
		int n = 0;
		while (ptr != NULL)
		{
			n++;
			ptr = ptr->next;
		}

		if (n >= no)
		{

			return 1;
		}
		return 0;
	}

	//------------------------------------------------------------------------------------------------------//
	//------------------------------------------------------------------------------------------------------//

	string EncreptPass(string pass)
	{
		string sampass = sha256(pass);

		// cout << endl
		// 	 << "\t" + sampass << endl
		// 	 << endl;

		return sampass;
	}

	//------------------------------------------------------------------------------------------------------//
	//------------------------------------------------------------------------------------------------------//

	int authentication(string user, string pass)
	{
		string u, p;
		int chance_u = 3;
		int chance_p = 3;

		//   cout<<endl<<chance_u<<endl;
		//   cout<<" "+chance_p;

		string dumy = EncreptPass(pass);
		cout << "\n\tPass :-  " + pass << "\n"
			 << " \tEncrepted Pass: ";
		cout << "\t" + dumy << endl
			 << endl;

		cout << endl
			 << "\n\t   Welcome please enter your username and password." << endl
			 << endl;

		while (chance_u)
		{
			cout << "\n\t\tUsername >> ";
			cin >> u;
			if (u == user)
			{
				chance_u = 0;

				while (chance_p)
				{
					cout << "\n\t\tPassword >> ";
					cin >> p;

					if (p == EncreptPass(pass))
					{
						chance_p = 0;
						return 1;
					}
					else
					{
						chance_p--;
						cout << "\n\tYou have loss 1 chance to enter correct passowrd" << endl;
					}
				}
			}
			else
			{

				chance_u--;
				cout << "\n\t  You have loss 1 chance to enter correct username" << endl;
			}
		}

		return 0;
	}
};

//---------------------------------------------------------------//
//---------------------------------------------------------------//

string timestamp()
{
	time_t now = time(0);
	char *dt = ctime(&now);
	return dt;
}

//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//

int main()
{

	chain sam;

	int var, x;
	string data;

	int j = 0;
	int h, num1, passd;

	string user = "admin";
	int sg, last;
	string pass = "Sambhaji_Gade@2k22";

	passd = sam.authentication(user, pass);

	if (passd)
	{

		cout << "\n\n\t\t-------------------------------------" << endl;
		cout << "\t\t-------------------------------------" << endl;
		cout << "\t\t-------------------------------------" << endl;
		cout << "\t\t------- WELCOME TO TESTCHAIN --------" << endl;
		cout << "\t\t-------------------------------------" << endl;
		cout << "\t\t-------------------------------------" << endl;
		cout << "\t\t-------------------------------------" << endl
			 << endl;

		while (true)
		{
			string ptr;
			cout << endl
				 << "\n\t---------------------------------------------------" << endl
				 << endl;
			cout << "\t\t-- Press 1 for Insert the data -- \n";
			cout << "\t\t-- Press 2 for print the data -- \n";
			cout << "\t\t-- Press 3 for write to file --" << endl;
			cout << "\t\t-- Press 4 for see perticular block data --\n";
			cout << "\t\t-- Press 5 for print data from file --\n";
			cout << "\t\t-- Press 6 for exit --\n\n";
			cout << "\t------------------------------------------------------" << endl
				 << endl;

			cout << "\t\tSelection: ";
			cin >> h;
			switch (h)
			{
			case 1:

				cin.ignore();
				cout << endl
					 << "\t\tInsert Data: ";

				getline(cin, ptr);

				sam.insert(ptr);

				// if (j == 1)
				// {
				// 	cout << "\tData is successfully added" << endl
				// 		 << endl;
				// }
				// else
				// {
				// 	cout << "\tfailed" << endl;
				// }
				break;

			case 2:
				sam.print();
				break;

			case 3:
				sam.writetofile();
				break;

			case 4:
				cout << "\n\t\tEnter block number : ";
				cin >> num1;
				sg = sam.validity(num1);
				if (sg)
				{
					sam.printBlock(num1);
				}
				else
				{
					cout << "\n\tThe given no of block is not present in TestChain." << endl;
				}
				break;

			case 5:
				sam.readFromFile();
				break;

			case 6:
				goto SamGade;

			default:
				cout << "\tThat is an invalid entry, please try again." << endl;

				break;
			}

			cout << endl;
		}
	}

	else
	{
		cout << endl
			 << "\n\t\tyou are not authorized user" << endl;

		cout << endl
			 << "\n\t\tpress 0 for exit : ";
		cin >> last;
		if (last == 0)
		{
			exit;
		}
	SamGade:;
	}
}