#include<iostream>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<Windows.h>
#include<string>
#include<string.h>


using namespace ::std;

class Shop
{

	struct Cloth     //the structure that holds cloth properties and will be the node of linked list
	{
		int cloth_id;
		char cloth_type[30];
		bool cloth_availability;
		char cloth_colour[30];
		int cloth_quantity;
		string cloth_size;
		float cloth_price;
		char cloth_description[100];
		Cloth *next;
		Cloth *previous;
	};

	Cloth *HeadNode;
	static int ID;              //we use static int for ID and order ID so they dont get reset and then repeated 
	static int Order_ID;

	class Cart                  //class that holds order properties and will be the node of a linked list
	{
		struct Item            //the structure that holds ordered items properties and will be the node of a linked list
		{
			int item_id;
			char item_type[30];
			char item_colour[30];
			int item_quantity;
			string item_size;
			float item_price;

			Item *next;
			Item *previous;

		};

		struct buyer        //structure for buyer details that will be stored in orders linked list as a data member of cart node
		{
			char buyer_name[30];
			char buyer_address[100];
			int buyer_no;
		}b1;

		double payment;

	public:

		Item *Item_HeadNode;
		double bill;
		char delivery;      //the delivery char will be used as boolean later in the code with a yes(y) or no(n) option
		int order_id;
		Cart *next;
		Cart *previous;

		Cart()            //default constructor
		{
			Item_HeadNode = 0;
			bill = 0;
			payment = 0;
			delivery = '?';
		}

		void add_item(Cloth *c1)        //function to add new node to items linked list
		{
			Item *temp_ptr = Item_HeadNode;
			Item *i1 = new Item;

			if (c1->cloth_quantity != 0)          //code to copy cloth details from shop to item variables for the cart
			{
				i1->item_id = c1->cloth_id;
				i1->item_price = c1->cloth_price;
				i1->item_size = c1->cloth_size;

				cout << "\n\nPlease Enter The Quantity You Want To Order. If You Want To Cancel, Then Enter '0': ";
				cin >> i1->item_quantity;


				if (i1->item_quantity > c1->cloth_quantity)
				{
					do
					{
						cout << "\nThe Quantity You Desire Is Not Available. Enter Within Range Or Enter '0' To Cancel Order";
						cin >> i1->item_quantity;

					} while (i1->item_quantity != 0 && i1->item_quantity > c1->cloth_quantity);
				}

				if (i1->item_quantity == 0) return;

			}

			if (i1->item_quantity == 0) return;

			c1->cloth_quantity = c1->cloth_quantity - i1->item_quantity;

			if (Item_HeadNode == 0)        //code to add node to linked list
			{
				Item_HeadNode = i1;
				i1->next = NULL;
				i1->previous = NULL;
				return;
			}

			while (temp_ptr->next != NULL)
				temp_ptr = temp_ptr->next;

			temp_ptr->next = i1;
			i1->next = NULL;
			i1->previous = temp_ptr;

			return;
		}

		void disp_cart()   //function to display our list in a tabular form
		{
			cout << "|---------------------------------------------------------------------------|\n";
			cout << "|-----------------------------Your Present Cart-----------------------------|\n";
			cout << "|---------------------------------------------------------------------------|\n";

			Item *temp_ptr = Item_HeadNode;
			cout << "\n ----------------------------------------------------------------------------";
			cout << "\n Item (type-colour-size)";
			cout << setw(20) << "Delivery";
			cout << setw(15) << "Quantity";
			cout << setw(15) << "Price(per)";
			cout << "\n ----------------------------------------------------------------------------";

			while (temp_ptr != NULL)
			{
				cout << endl << " " << temp_ptr->item_type << "-" << temp_ptr->item_colour << "-"<<temp_ptr->item_size;
				cout << "                         ";
				if (delivery == 'y')cout << "yes";
				else cout << "no";
				cout << setw(15) << temp_ptr->item_quantity << "              ";
				cout << temp_ptr->item_price;
				temp_ptr = temp_ptr->next;
			}

			cout << "\n ----------------------------------------------------------------------------\n";
			cout << "                                                               Total Bill: " << bill;
			cout << "\n                                                              Amount Paid: " << payment;
			cout << "\n                                                          Amount Returned: " << payment - bill << "\n";

			if (delivery == 'y')
			{
				cout << "Delivery: Yes(50RM Charge)\n";
				cout << "Delivery Details:\n";
				cout << "Buyer Name: " << b1.buyer_name;
				cout << "\nBuyer Address: " << b1.buyer_address;
				cout << "\nBuyer Contact: " << b1.buyer_no;
			}

			else if (delivery == 'n') cout << "Delivery: No";

		}

		void bill_count()  //fucntion to add up prices of items in the items linked list
		{
			bill = 0;
			Item *temp_ptr = Item_HeadNode;
			while (temp_ptr != NULL)
			{
				bill = bill + (temp_ptr->item_price*temp_ptr->item_quantity);
				temp_ptr = temp_ptr->next;
			}

		}

		void checkout_input()     //checkout function
		{


			order_id = Order_ID;

			do
			{
				cout << "\nDo You Require Delivery (50RM Additionl Cost)? (y/n)";
				delivery = _getch();

			} while (delivery != 'y'&&delivery != 'n');

			if (delivery == 'y')
			{
				bill = bill + 50;

				cout << "\n\nEnter Buyer Name (Must End With A '.'): ";
				cin.ignore();
				cin.getline(b1.buyer_name, 30, '.');
				cout << "\nEnter Buyer Address (Must End With A '.'): ";
				cin.ignore();
				cin.getline(b1.buyer_address, 100, '.');
				cout << "\nEnter Buyer Contact Number: ";
				cin.ignore();
				cin >> b1.buyer_no;
				cout << endl;
			}

			while (true)
			{
				cout << "\nEnter Bill Payment (Total Bill is " << bill << "):";
				cin >> payment;

				if (payment < bill) continue;
				else break;
			}
		}

		void change_buyer_details()  //function to update buyer details
		{
			if (delivery == 'n')
			{
				cout << "\n\nYou Cannot Modify The Buyer Details In A Non Delivery Order.\n";
				system("pause");
				return;
			}

			int choice;
			while (true)
			{
				cout << "\n\n 1.Modify Name\n";
				cout << " 2.Modify Address\n";
				cout << " 3.Modify Contact Number\n";
				cout << " 4.Exit";
				cout << " choice: ";
				cin >> choice;

				if (choice == 1)
				{
					cout << "\nEnter Name (Must End With A '.'): ";
					cin.ignore();
					cin.getline(b1.buyer_name, 30, '.');
				}

				if (choice == 2)
				{
					cout << "\nEnter Address (Must End With A '.'): ";
					cin.ignore();
					cin.getline(b1.buyer_address, 100, '.');
				}

				if (choice == 3)
				{
					cout << "\nEnter Phone Number:";
					cin >> b1.buyer_no;
				}

				if (choice == 4) break;

			}

			return;
		}

		void disp_order()           //function to disp whole order in a single line (shows order id, delivery status and bill)
		{
			cout << endl << order_id << setw(25);

			if (delivery == 'y') cout << setw(30) << "Yes";
			else cout << setw(25) << "No";
			cout << setw(18) << bill;
			cout << endl << "------------------------------------------------" << endl;
		}

	};

	Cart *Cart_HeadNode;

public:

	Cart *cart1;

	void insert_order(Cart *s1)  //function used to add a node to the orders linked list 
	{
		Cart *cart = new Cart;
		*cart = *s1;
		Cart *temp_ptr = Cart_HeadNode;
		Order_ID++;

		if (Cart_HeadNode == 0)
		{
			Cart_HeadNode = cart;
			cart->next = NULL;
			cart->previous = NULL;
			return;
		}

		while (temp_ptr->next != NULL)
			temp_ptr = temp_ptr->next;

		temp_ptr->next = cart;
		cart->next = NULL;
		cart->previous = temp_ptr;

		return;
	}

	void remove_order(Cart *s1)  //function to delete an order node from orders linked list
	{
		Cart *temp_ptr = s1;

		if (temp_ptr == Cart_HeadNode && temp_ptr->next == NULL)
		{
			Cart_HeadNode = 0;
			delete temp_ptr;
			return;
		}

		if (temp_ptr == Cart_HeadNode)
		{
			Cart_HeadNode = temp_ptr->next;
			temp_ptr->next->previous = NULL;
			delete temp_ptr;
			return;
		}

		if (temp_ptr->next == NULL)
		{
			temp_ptr->previous->next = NULL;
			delete temp_ptr;
			return;
		}

		temp_ptr->next->previous = temp_ptr->previous;
		temp_ptr->previous->next = temp_ptr->next;
		delete temp_ptr;
		return;
	}

	void disp_order(Cart *s1)  //function to display whole order in detail and give further options of deleting and updating
	{                          //this function uses recursion to allow user to move back and forth along the orders linked list
		system("cls");
		cout << "\n-------------------" << "|Order ID: " << s1->order_id << "|---------------------\n\n";

		s1->disp_cart();

		cout << "\n\nUse (Right/Left) Arrow Keys To Maneuver Through Orders And The (Down) Arrow Key To Return.\n";
		cout << "Use (Up) Arrow Key Update Delivery Info.\n";
		cout << "Use 'd' Key To Delete Current Order History.";

		int action;
		do
		{
			action = _getch();

		} while (action != 75 && action != 77 && action != 72 && action != 80 && action != 100);

		if (action == 75 && s1->previous == NULL) disp_order(s1);
		if (action == 75) disp_order(s1->previous);
		if (action == 77 && s1->next == NULL) disp_order(s1);
		if (action == 77 && s1->next != NULL) disp_order(s1->next);
		if (action == 72) { s1->change_buyer_details(); disp_order(s1); }
		if (action == 100) { remove_order(s1); system("cls"); cout << "\n Order Deleted\n"; Sleep(500); cout << " -----------------"; Sleep(500); return; }
		if (action == 80) return;

	}

	void cloth_input(Cloth *c1)  //function to input a new cloth
	{
		string flag;

		cout << "************************************************\n";
		cout << "Enter Cloth's Type (Must End With A '.' ): ";
		cin.ignore();
		cin.getline(c1->cloth_type, 29, '.');

		cout << "Enter Cloth's Colour (Must End With A '.' ): ";
		cin.ignore();
		cin.getline(c1->cloth_colour, 29, '.');

		cout << "Enter Cloth's Description (Must End With A '.' ): ";
		cin.ignore();
		cin.getline(c1->cloth_description, 99, '.');

		cout << "Enter Cloth's Quantity: ";
		cin >> c1->cloth_quantity;

		if (c1->cloth_quantity > 0) c1->cloth_availability = 1;
		else c1->cloth_availability = 0;

		do
		{
			cout << "Enter Cloth's Size ('s', 'm', 'l', 'xl' ): ";
			cin >> c1->cloth_size;

		} while (c1->cloth_size != "s"&&c1->cloth_size != "m"&&c1->cloth_size != "l"&&c1->cloth_size != "xl");


		cout << "Enter Cloth's Price: ";
		cin >> c1->cloth_price;

		c1->cloth_id = ID;

		cout << endl;
	}

	Shop()  //default constructor
	{
		HeadNode = 0;
		Cart_HeadNode = 0;
		cart1 = new Cart;
	}

	void finput()   //funtion to read input clothes from a file
	{
		ifstream fin;
		Cloth *c2 = new Cloth;
		Cloth *temp_ptr;
		Cloth *max_temp;


		fin.open("clothes.txt");
		while (!fin.eof())
		{

			c2 = new Cloth;

			fin >> c2->cloth_id;
			fin.ignore();
			fin.getline(c2->cloth_type, 30, '7');
			fin.ignore();
			fin.getline(c2->cloth_colour, 30, '7');
			fin.ignore();
			fin.getline(c2->cloth_description, 100, '7');
			fin >> c2->cloth_quantity;
			fin >> c2->cloth_price;
			fin >> c2->cloth_size;

			// after storing the data from the file into our cloth structure we now insert the data into our linked list by calling the insert fucntion
			insert_cloth(c2);

		}

		temp_ptr = HeadNode;
		max_temp = HeadNode;

		while (temp_ptr != NULL)
		{
			if ((temp_ptr->cloth_id) > (max_temp->cloth_id))
			{
				max_temp = temp_ptr;
			}

			temp_ptr = temp_ptr->next;
		}

		ID = max_temp->cloth_id;
	}

	void foutput()   //function to output clothes to a file
	{
		ofstream fout;
		Cloth *temp_ptr = HeadNode;

		fout.open("clothes.txt");

		while (temp_ptr != NULL)
		{
			fout << endl << temp_ptr->cloth_id << endl;
			fout << temp_ptr->cloth_type << 7 << endl;
			fout << temp_ptr->cloth_colour << 7 << endl;
			fout << temp_ptr->cloth_description << 7 << endl;
			fout << temp_ptr->cloth_quantity << endl;
			fout << temp_ptr->cloth_price << endl;
			fout << temp_ptr->cloth_size;

			temp_ptr = temp_ptr->next;
		}
	}


	void insert_cloth()    //function to input data into the node and then add it to the linked list
	{
		Cloth *c1 = new Cloth;
		Cloth *temp_ptr = HeadNode;
		ID++;

		if (HeadNode == 0)
		{
			HeadNode = c1;
			cloth_input(c1);
			c1->next = NULL;
			c1->previous = NULL;
			return;
		}

		while (temp_ptr->next != NULL)
			temp_ptr = temp_ptr->next;


		temp_ptr->next = c1;
		cloth_input(c1);
		c1->next = NULL;
		c1->previous = temp_ptr;

		return;

	}

	void insert_cloth(Cloth *c1)  //function used to add a node to the linked list if it already carries data
	{
		Cloth *temp_ptr = HeadNode;
		ID++;

		if (HeadNode == 0)
		{
			HeadNode = c1;
			c1->next = NULL;
			c1->previous = NULL;
			return;
		}

		while (temp_ptr->next != NULL)
			temp_ptr = temp_ptr->next;

		temp_ptr->next = c1;
		c1->next = NULL;
		c1->previous = temp_ptr;

		return;
	}

	int get_length()    //function to give size of linked list
	{
		int len = 0;
		Cloth *temp_ptr = HeadNode;

		while (temp_ptr != NULL)
		{
			len++;
			temp_ptr = temp_ptr->next;
		}

		return len;
	}

	int get_order_length()    //function to give size of linked list
	{
		int len = 0;
		Cart *temp_ptr = Cart_HeadNode;

		while (temp_ptr != NULL)
		{
			len++;
			temp_ptr = temp_ptr->next;
		}

		return len;
	}

	void sort()     //function to sort the clothes linked list according to increasing price
	{
		Cloth *temp_ptr;
		Cloth *temp_ptr2;
		Cloth *temp=new Cloth;
		int length = get_length();
		for (int i = 0; i < length - 1; i++)
		{
			temp_ptr = HeadNode;
			temp_ptr2 = temp_ptr->next;

			for (int j = 0; j < length - 1; j++)
			{

				if (temp_ptr->cloth_price > temp_ptr2->cloth_price)
				{
					if (temp_ptr == HeadNode)    //relinking the linked list after a sort step
					{
						HeadNode = temp_ptr2;
						temp_ptr->next = temp_ptr2->next;
						temp_ptr->previous = temp_ptr2;

						if (temp_ptr2->next != NULL)
							temp_ptr2->next->previous = temp_ptr;

						temp_ptr2->next = temp_ptr;
						temp_ptr2->previous = NULL;
					}

					else
					{
						temp_ptr->next = temp_ptr2->next;       //relinking the linked list after a sort step

						if (temp_ptr2->next != NULL)
							temp_ptr2->next->previous = temp_ptr;

						temp_ptr->previous->next = temp_ptr2;
						temp_ptr2->previous = temp_ptr->previous;
						temp_ptr->previous = temp_ptr2;

						temp_ptr2->next = temp_ptr;
						temp->next = temp_ptr2;
					}

					temp = temp_ptr2;            //reassignment to the temp pointers if sort happens
					temp_ptr2 = temp_ptr->next;
				}

				else
				{
					temp = temp_ptr;            //reassignment to the temp pointers if sort dose not happen
					temp_ptr = temp_ptr2;
					temp_ptr2 = temp_ptr2->next;
				}
			}
		}
	}

	void sort_orders()     //function to sort the orders linked list according delivery status and then increasing price
	{
		Cart *temp_ptr;
		Cart *temp_ptr2;
		Cart *temp= new Cart;
		int length = get_order_length();
		for (int i = 0; i < length - 1; i++)
		{
			temp_ptr = Cart_HeadNode;
			temp_ptr2 = temp_ptr->next;

			for (int j = 0; j < length - 1; j++)
			{

				if ((temp_ptr->bill > temp_ptr2->bill) || (temp_ptr->delivery == 'n'&&temp_ptr2->delivery == 'y'))
				{
					if (temp_ptr == Cart_HeadNode)    //relinking the linked list after a sort step
					{
						Cart_HeadNode = temp_ptr2;
						temp_ptr->next = temp_ptr2->next;
						temp_ptr->previous = temp_ptr2;

						if (temp_ptr2->next != NULL)
							temp_ptr2->next->previous = temp_ptr;

						temp_ptr2->next = temp_ptr;
						temp_ptr2->previous = NULL;
					}

					else
					{
						temp_ptr->next = temp_ptr2->next;       //relinking the linked list after a sort step

						if (temp_ptr2->next != NULL)
							temp_ptr2->next->previous = temp_ptr;

						temp_ptr->previous->next = temp_ptr2;
						temp_ptr2->previous = temp_ptr->previous;
						temp_ptr->previous = temp_ptr2;

						temp_ptr2->next = temp_ptr;
						temp->next = temp_ptr2;
					}

					temp = temp_ptr2;            //reassignment to the temp pointers if sort happens
					temp_ptr2 = temp_ptr->next;
				}

				else
				{
					temp = temp_ptr;            //reassignment to the temp pointers if sort dose not happen
					temp_ptr = temp_ptr2;
					temp_ptr2 = temp_ptr2->next;
				}
			}
		}
	}


	void search()  //function to search
	{
		Cloth *temp_ptr = HeadNode;
		char type[30];
		bool found = 0;


		cout << "\nEnter The Cloth Type To Search For: ";
		cin >> type;

		cout << "Cloth ID";
		cout << setw(20) << "Cloth Type";
		cout << setw(15) << "Quantity";
		cout << setw(15) << "Price";
		cout << "\n-----------------------------------------------------------";

		while (temp_ptr != NULL)
		{
			if (!strcmp(temp_ptr->cloth_type, type))
			{

				found = 1;
				cout << endl << temp_ptr->cloth_id << setw(25);
				cout << temp_ptr->cloth_type << setw(30);
				cout << setw(15) << temp_ptr->cloth_quantity << "              ";
				cout << temp_ptr->cloth_price;
			}

			temp_ptr = temp_ptr->next;

		}

		if (temp_ptr == NULL && found == 0)
		{
			cout << endl << "Invalid Cloth Type";
		}

	}

	void select()  //function to select a node and call disp_cloth() function for clothes linked list
	{
		Cloth *temp_ptr = HeadNode;
		int search_id;
		bool found = 0;


		cout << "\n\nEnter Cloth ID For Further Description And Options: ";
		cin >> search_id;

		while (temp_ptr != NULL)
		{
			if (temp_ptr->cloth_id == search_id)
				break;

			temp_ptr = temp_ptr->next;

		}

		if (temp_ptr == NULL)
		{
			cout << endl << "Invalid Cloth ID";
		}

		else disp_cloth(temp_ptr);


	}

	void select_order()  //function to select a node and call disp_order() function for orders linked list
	{
		Cart *temp_ptr = Cart_HeadNode;
		int search_id;

		cout << "\nEnter Order ID For Further Description And Options: ";
		cin >> search_id;

		while (temp_ptr != NULL)
		{
			if (temp_ptr->order_id == search_id)
				break;

			temp_ptr = temp_ptr->next;
		}

		if (temp_ptr == NULL)
		{
			cout << endl << "Invalid Order ID";
		}

		else
		{
			disp_order(temp_ptr);
		}
	}


	void disp_list()   //function to display clothes linked list in a tabular form
	{
		Cloth *temp_ptr = HeadNode;

		cout << "Cloth ID";
		cout << setw(20) << "Cloth Type";
		cout << setw(15) << "Quantity";
		cout << setw(17) << "Price(RM)";
		cout << "\n-----------------------------------------------------------";

		while (temp_ptr != NULL)
		{
			cout << endl << temp_ptr->cloth_id << setw(25);
			cout << temp_ptr->cloth_type << setw(30);
			cout << setw(15) << temp_ptr->cloth_quantity << "              ";
			cout << temp_ptr->cloth_price;
			temp_ptr = temp_ptr->next;

		}

		select();

	}

	void disp_order_list()   //function to display orders linked list in a tabular form
	{

		Cart *temp_ptr = Cart_HeadNode;

		cout << "Order ID";
		cout << setw(20) << "Delivery";
		cout << setw(15) << "Bill";
		cout << "\n-----------------------------------------------";

		while (temp_ptr != NULL)
		{
			temp_ptr->disp_order();
			temp_ptr = temp_ptr->next;
		}

		select_order();
	}

	void disp_cloth(Cloth *c1) //function to disp a single cloth node in detail
	{                          //the function uses recursion to move move back and forth in the clothes linked list
		system("cls");
		Cart *cart = cart1;

		cout << "\n-------------------" << "|Cloth ID: " << c1->cloth_id << "|---------------------";
		cout << endl << "Cloth Type: " << c1->cloth_type;
		cout << endl << "Cloth Colour: " << c1->cloth_colour;
		cout << endl << "Description: " << c1->cloth_description;
		cout << endl << "Quantity: " << c1->cloth_quantity;
		cout << endl << "Price: " << c1->cloth_price;
		cout << endl << "Size: " << c1->cloth_size;
		cout << "\n-----------------------------------------------------";

		cout << "\nUse (Right/Left) Arrow Keys To Maneuver Through Clothes And (Down) Arrow Key To Return.\n";
		cout << "Use (Up) Arrow Key To Add Item To Cart.";

		int action;
		do
		{
			//action=_getch();
			action = _getch();
		} while (action != 75 && action != 77 && action != 72 && action != 80);

		if (action == 75 && c1->previous == NULL) disp_cloth(c1);
		if (action == 75) disp_cloth(c1->previous);
		if (action == 77 && c1->next == NULL) disp_cloth(c1);
		if (action == 77) disp_cloth(c1->next);
		if (action == 72) { cart->add_item(c1); disp_cloth(c1); }
		if (action == 80) return;
	}

	void checkout()  //fucntion that calls several other functions required for checkout
	{
		Cart *cart = cart1;

		if (cart->Item_HeadNode == 0)
		{
			cout << "Cart Is Empty.\n";
			system("pause");
			return;
		}

		cart->bill_count();
		cart->disp_cart();
		cart1->checkout_input();
		insert_order(cart1);
		cart1 = new Cart;
		system("cls");
		cout << "\n Database Updated\n"; Sleep(500); cout << " -----------------"; Sleep(500);
	}

	void view_cart() //fucntion to disp items in cart before the checkout
	{
		Cart *cart = cart1;
		cart->bill_count();
		cart->disp_cart();
		cout << endl;
	}

	void menu()  //menu function   
	{
		int choice1;
		int choice2;
		finput();

		cout << "\n\n\n\n\t\t\t\t\t----------------------------------------\n";
		cout << "\t\t\t\t\tGreetings To DressMe Clothing Martketplace\n";
		cout << "\t\t\t\t\t----------------------------------------\n";
		cout << "\t\t\t\t\t\t    Loading.";
		Sleep(300);
		cout << ".";
		Sleep(300);
		cout << ".";
		Sleep(300);
		cout << ".";
		Sleep(300);
		cout << ".";
		Sleep(300);

		while (true)
		{
			choice1 = 0;
			choice2 = 0;

			system("cls");
			cout << " DressMe Clothing Martketplace\n";
			cout << " --------------------------\n\n";
			cout << " 1.Shop Menu\n";
			cout << " 2.Customer Service Menu\n";
			cout << " 3.Exit\n\n";
			cout << " Option: ";
			cin >> choice1;


			if (choice1 == 1)
			{
				do
				{
					system("cls");
					cout << " DressMe Clothing Martketplace (Shop)\n";
					cout << " --------------------------\n\n";
					cout << " 1.Display Cloth Lists\n";
					cout << " 2.Search\n";
					cout << " 3.View Cart\n";
					cout << " 4.Checkout Order\n";
					cout << " 11.Exit\n\n";
					cout << " Option: ";
					cin >> choice2;

					switch (choice2)
					{
					case 1: system("cls");
						sort();
						disp_list();
						break;

					case 2:  system("cls");
						search(); cout << endl << endl;
						system("PAUSE");
						break;

					case 3: system("cls");
						view_cart();
						system("pause");
						break;

					case 4: system("cls");
						checkout();
						choice2 = 11;
						break;
					}

				} while (choice2 != 11);
			}


			else if (choice1 == 2)
			{
				do
				{
					system("cls");
					cout << " DressMe Clothing Martketplace (Customer Service)\n";
					cout << " --------------------------\n\n";
					cout << " 1.View Orders\n";
					cout << " 2.Enter cloth To Shop\n";
					cout << " 11.Exit\n\n";
					cout << " Option: ";
					cin >> choice2;

					switch (choice2)
					{
					    case 1: system("cls");
						        sort_orders();
						        disp_order_list();
						        break;

					    case 2: system("cls");
						        insert_cloth();
						        system("cls");
						        foutput();
						        cout << "\n Database Updated\n"; Sleep(500); cout << " -----------------"; Sleep(500);
						        break;
					}

				} while (choice2 != 11);
			}

			else if (choice1 == 3)
				break;
		}
	}

};

int Shop::ID = 0;
int Shop::Order_ID = 1;

int main()
{
	Shop d1;
	d1.menu();

	return 0;
}
