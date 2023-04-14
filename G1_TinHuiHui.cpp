/*
	This is a C++ application to handle a community parcel locker system for the residents of Boulevard Service Apartment.
	This application can be used by couriers to deliver parcels, and residents to collect their parcel.
	Couriers can register parcels for delivery by entering residents' details.
	This application reads the residents' details from a text file containing the residents' unit number, name,
	contact number, and password, then generates a PIN code for the residents' parcel collection.
*/

#include <iostream> 
#include <iomanip>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cstring>
#include <string>
using namespace std;

#define UNIT_NUM_SIZE 5 
#define NAME_SIZE 30 
#define CONTACT_NUM_SIZE 15 
#define PASSWORD_SIZE 15 

typedef struct
{
	char unit_num[5];
	char name[30];
	char contact_num[15];
	char password[15];
} RESIDENT;

typedef struct
{
	string unit_num2;
	string pincode;
} PINCODELST;

// Function prototypes
void resident_page();
void resident_regis();
void parcel_regis();
void parcel_collect();

/*
	The main function displays the main menu of the application, then prompts the user, asking who they are to proceed.
	The user can choose whether they are a courier, a resident, or they can exit the application.
*/
int main(void)
{
	bool loop = true;
	while (loop)
	{
		system("CLS");
		char option;
		cout << "\t\t==================================================\n" << endl;
		cout << "\t\t            Boulevard Service Apartment           \n" << endl;
		cout << "\t\t==================================================\n" << endl;
		cout << "\t\t      Welcome to Boulevard Service Apartment " << endl;;
		cout << "\t\t          Community Parcel Locker System \n" << endl;
		cout << "\tWho are you? " << endl;
		cout << "\t1. Courier\t2. Resident\t3. Exit application\n" << endl;
		cout << "\tEnter option : ";
		cin >> option;

		if (option == '3')
		{
			cout << "\n\tThank you for using our application!";
			loop = false;
		}
		else
		{
			while (option != '1' && option != '2')
			{
				cout << "\tWrong option. Please try again.\n\tEnter option : ";
				cin >> option;
			}

			if (option == '1')
			{
				parcel_regis();
			}
			else
			{
				resident_page();
			}
			system("pause");
		}
	}
	return 0;
}

/*
	The resident_page function displays the resident page.
	The function prompts whether the user wants to register, collect their parcel, or exit the page.
*/
void resident_page()
{
	system("CLS");

	char resident_op;
	cout << "\tWelcome, resident\n" << endl;
	cout << "\tWhat can we do to help you?\n" << endl;
	cout << "\t1. Registration\n\t2. Parcel Collection\n\t3. Exit\n" << endl;
	cout << "\tEnter option : ";
	cin >> resident_op;

	while (resident_op != '1' && resident_op != '2' && resident_op != '3')
	{
		cout << "\tWrong option. Please try again.\n\tEnter option : ";
		cin >> resident_op;
	}

	/*
		Switch statement allows the user to make options in the resident page.
		When user inputs '1': resident_regis function is called for resident registration.
		When user inputs '2': parcel_collect function is called for parcel collection.
	*/
	switch (resident_op)
	{
	case '1':
		resident_regis();
		break;
	case '2':
		parcel_collect();
		break;
	default:
		cout << "\tPlease press 'Enter' to exit this page.\n";

	}
	system("pause");
	return;
}

/*
	The resident_regis function is to let users register for parcel collection.
	The function gets the users' unit number, name, contact number and password, then saves them into a text file.
*/
void resident_regis()
{
	system("cls");
	string contact_num;
	string password;
	string name;
	string unit_num;

	cout << "\t\t\t\tRegistration Page\t\t\n\n";

	cout << "\tEnter apartment unit number : ";
	cin >> unit_num;

	// If the length of unit number is more than 5 
	while (unit_num.length() > UNIT_NUM_SIZE)
	{ 
		cout << "\tInvalid apartment unit number! Please key in again...";
		cout << "\n\tEnter apartment unit number : ";
		cin >> unit_num;
	}

	cin.ignore(); // Ignores or clears one or more characters from the input buffer    
	cout << "\n\tEnter name                  : ";
	getline(cin, name);

	cout << "\n\tEnter contact number        : ";
	cin >> contact_num;

	// If the length of contact number is more than 15
	while (contact_num.length() > CONTACT_NUM_SIZE)
	{ 
		cout << "\tInvalid contact number! Please key in again...";
		cout << "\n\tEnter contact number        : ";
		cin >> contact_num;
	}

	cout << "\n\tEnter password (max 15)     : "; 
	cin >> password;

	// If the length of password is more than 15
	while (password.length() > PASSWORD_SIZE)
	{
		cout << "\tInvalid password. Password too long.Please key in again...";
		cout << "\n\tEnter password (max 15)     : ";
		cin >> password;
	}

	char select;
	cout << "\n\tDo you want to edit the information?"; // Lets the user choose if they want to edit the information or not 
	cout << "\n\tyes or no (Y or N): ";
	cin >> select;
	bool run = true;

	while (run) 
	{  // If the user does not input 'y' or 'n', the prompt keeps displaying until user types the correct option
		if (select == 'Y' || select == 'y')
		{
			run = false;
			continue;
		}
		if (select == 'N' || select == 'n')
		{
			run = false;
			continue;
		}
		cout << "\n\tInvalid\n\tEnter Y or N only: ";
		cin >> select;
	}

	while (true)
	{
		if (select == 'N' || select == 'n')
		{ //If the user inputs 'N', the system will break and goes to the register successfully message
			break;
		}
		if (select == 'Y' || select == 'y')
		{ //If the user inputs 'Y', the system will keep running 
			system("cls");
			cout << "\tPlease re-enter the information!";
			cout << "\n\tEnter apartment unit number : ";
			cin >> unit_num;
			cin.ignore();        // Ignore or clears one or more characters from the input buffer
			cout << "\n\tEnter name                  : ";
			getline(cin, name);
			cout << "\n\tEnter contact number        : ";
			cin >> contact_num;
			cout << "\n\tEnter password (max 15)     : ";
			cin >> password;
			break;
		}
	}

	ofstream f1("Resident_List.txt", ios::app);
	f1 << unit_num << "\n" << name << "\n" << contact_num << "\n" << password << "\n"; // Input information will be saved into text file

	system("cls");
	cout << "\n\tThank you";
	cout << "\n\tYour registration was successful! Your personal information is stated below.\n";
	cout << "\n\tApartment unit number : " << unit_num;
	cout << "\n\tName                  : " << name;
	cout << "\n\tContact number        : " << contact_num;
	cout << "\n\tPassword              : " << password;
	cout << "\n\tThank you for using Boulevard Service Apartment Community Parcel Locker System!";
	cout << "\n\tPlease press Enter to exit this page.";

	return;
}

/*
	The parcel_regis function is for couriers to register and deliver parcels.
	The function gets the unit number and checks with the text file to see whether it exists.
*/
void parcel_regis()
{
	system("CLS");
	string unit_num;
	char option;

	cout << "\tWelcome to the Parcel Registration Page!\n";

	do
	{
		cout << "\n\tPlease enter apartment unit number             : ";
		cin >> unit_num;

		ifstream in_file("Resident_List.txt");
		string unit_check;

		bool found = false;

		if (in_file)
		{
			while (in_file >> unit_check)
			{
				if (unit_check == unit_num)
				{
					// Lets courier know the unit number exists
					cout << "\n\t\tUNIT NUMBER EXISTS!";

					char choice;

					// Prompts confirmation of the parcel delivery
					cout << "\n\tConfirmation for parcel delivery to " << unit_num << " (Y/N) : ";
					cin >> choice;

					if (choice == 'Y' || choice == 'y')
					{
						// 6-digit PIN code generation with random numbers
						int pin_code, lower = 100000, upper = 999999;
						srand(time(NULL));
						int first_digit = ((rand() % 8) + 1) * 100000;
						pin_code = first_digit + ((rand() % (upper - lower + 1)) + lower);

						ofstream outfile;

						outfile.open("pin.txt", ios_base::app);
						outfile << unit_num << "\n" << pin_code << endl;
						outfile.close();

						cout << "\n\tParcel registration is SUCCESSFUL!\n";

						found = true;

						break;
					}
					else
					{
						break;
					}
				}
			}
			if (!found)
			{
				// Lets courier know parcel registration is unsuccessful
				cout << "\n\t\tUNIT NUMBER NOT FOUND!";
				cout << "\n\tParcel registration is NOT SUCCESSFUL!\n";
			}
			in_file.close();
		}
		// Asks courier if there is another parcel to deliver
		cout << "\n\tDo you have another parcel to deliver (Y/N)    : ";
		cin >> option;
	} while (option == 'y' || option == 'Y');
	cout << "\n\tThank you for using the Boulevard Service Apartment Community Parcel Locker System!\n";
}

/*
	The parcel_collect function allows residents to collect their parcels.
	The resident enters their unit number, password, then receives their PIN code.
*/
void parcel_collect()
{
	system("CLS");
	ifstream in_file("Resident_List.txt", ios::in);
	if (!in_file)
		cout << "Error opening file" << endl;
	else
	{
		RESIDENT residents[10000];
		int count = -1;

		in_file.getline(residents[++count].unit_num, UNIT_NUM_SIZE);

		while (in_file)
		{
			in_file.getline(residents[count].name, NAME_SIZE);
			in_file.getline(residents[count].contact_num, CONTACT_NUM_SIZE);
			in_file.getline(residents[count].password, PASSWORD_SIZE);
			in_file.getline(residents[++count].unit_num, UNIT_NUM_SIZE);
		}
		in_file.close();

		string unit_num_input, password_input;
		string name;
		char check;
		cout << "\tWelcome! Sir/Madam!\n" << endl;
		cout << "\tPlease enter your apartment unit number : ";
		cin >> unit_num_input;
		cout << "\tPlease enter your password              : ";
		cin >> password_input;

		bool loop = true;
		while (loop)
		{
			// Confirmation for correct data input
			cout << "\n\tYour entered apartment unit number : " << unit_num_input << endl;
			cout << "\tYour entered password		   : " << password_input << endl;
			cout << "\tPlease make sure your entered data are correct. (Y for Yes, N for no) : ";
			cin >> check;
			if (check == 'Y' || check == 'y')
				loop = false;
			else
			{
				if (check == 'N' || check == 'n') // Enter data again if previous entry is wrong
				{
					cout << "\n\tPlease enter your apartment unit number : ";
					cin >> unit_num_input;
					cout << "\tPlease enter your password              : ";
					cin >> password_input;
				}
				else
				{
					cout << "\n\tWrong option. Only Y, y, N, n are allowed. Please re-enter again." << endl;
					cout << "\tPlease make sure your entered data are correct. (Y for Yes, N for no)" << endl;
					cin >> check;
				}
			}
		}
		bool loop2 = true;
		while (loop2)
		{
			bool acc_exist = false;
			for (int i = 0; i <= count; i++)
			{
				if (residents[i].unit_num == unit_num_input)
				{
					acc_exist = true;
					if (residents[i].password == password_input)
					{
						ifstream in_file2("pin.txt", ios::in);
						if (!in_file2)
							cout << "\n\tError opening text file.\n";
						else
						{
							PINCODELST pincode[50];
							int index = -1;
							in_file2 >> pincode[++index].unit_num2;
							while (in_file2)
							{
								in_file2 >> pincode[index].pincode;
								in_file2 >> pincode[++index].unit_num2;
							}
							in_file2.close();

							bool found = false;
							for (int j = 0; j <= index; j++)
							{
								if (pincode[j].unit_num2 == unit_num_input)
								{
									// Prompts user that there is a parcel in their locker, with their PIN code.
									cout << "\n\tYou have a parcel in the locker. Please collect it as soon as possible.\n";
									cout << "\tYour one-time PIN code			: " << pincode[j].pincode << endl;
									cout << "\tYou are only allowed to view the pin code once.\n";
									cout << "\tPlease remember your pin code before you exit from this page.\n";
									cout << "\n\n";

									int indexs = j;
									for (int k = indexs; k < index - 1; k++)
									{
										pincode[k].unit_num2 = pincode[k + 1].unit_num2;
										pincode[k].pincode = pincode[k + 1].pincode;
									}

									ofstream out_file("pin.txt", ios_base::out);
									if (!out_file)
										cout << "Error opening output file.\n";
									else
									{
										for (int l = 0; l < index - 1; l++)
										{
											out_file << pincode[l].unit_num2 << endl;
											out_file << pincode[l].pincode << endl;
										}
									}
									out_file.close();
									found = true;
									break;
								}
							}
							if (found == false)
							{
								// Prompts user that there is no parcel in their locker.
								cout << "\n\tThe apartment unit number of " << unit_num_input << " don't have a parcel currently.\n\n";
							}
						}
					}
				}
			}
			if (acc_exist == false)
			{
				// Prompts user that they do not have an account.
				cout << "\n\tThe apartment unit number of " << unit_num_input << " don't have an account.\n";
				cout << "\tPlease register an account first.\n\n";
			}
			cout << "\tThank you for using Boulevard Service Apartment Community Parcel Locker System!" << endl;
			cout << "\tPlease press 'Enter' to exit this page.\n\n";
			loop2 = false;
		}
	}
	return;
}