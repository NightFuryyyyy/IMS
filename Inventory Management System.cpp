using namespace std;
#include<iostream>
#include<vector>

std::string intToString(int n)
{
	std::string str;
	do
	{
		str = char('0' + n % 10) + str;
		n /= 10;
	}
	while(n > 0);
	return str;
}

int findInVector(const std::vector<std::string>& vect,const std::string& str)
{
	for(int i = 0; i < vect.size(); i++)
	{
		if(vect[i] == str)
		{
			return i;
		}
	}
	return vect.size();
}

int menu(std::string title, std::vector<std::string> vect)
{
	std::string CHOICE;
	int choice = 0, width = title.length() + 2, no_width = intToString(vect.size()).length();
	for(int i = 0; i < vect.size(); i++)
	{
		if(vect[i].length() + no_width + 4 > width)
		{
			width = vect[i].length() + no_width + 4;
		}
	}
	std::cout << "+" << std::string(width, '-') << "+\n"
			  << "| " << title << std::string(width - title.length() - 1, ' ') << "|\n"
			  << "+" << std::string(width, '-') << "+\n";
	for(int i = 1; i <= vect.size(); i++)
	{
		std::cout << "| " << std::string(no_width - intToString(i).length(), ' ') << i << ". " << vect[i - 1] << std::string(width - (no_width + vect[i - 1].length() + 3), ' ') << "|\n";
	}
	std::cout << "+" << std::string(width, '-') << "+\n\nChoice: ";
	std::cin >> CHOICE;
	for(int i = 0; i < CHOICE.length(); i++)
	{
		if(isdigit(CHOICE[i]))
		{
			choice = choice * 10 + CHOICE[i] - '0';
		}
		else
		{
			return 0;
		}
	}
	return choice;
}

std::string lower(std::string str)
{
	for(int i = 0; i < str.length(); i++)
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}
	return str;
}

class inventory
{
    string product, company;
	public:
	int quantity;
    inventory(string product, string company, int quantity)
    {
        this -> product = product;
        this -> company = company;
        this -> quantity = quantity;
    }
    inventory operator+=(int n)
    {
        quantity += n;
        return *this;
    }
	void display()
	{
		cout << "\nProduct: " << product << endl
			 << "Company: " << company << endl
	 		 << "Quantity: " << quantity << "\n\n";
	}
	friend int findItem(vector<inventory> &item, int mode);
};

int findItem(vector<inventory> &item, int mode)
{
	
	vector<string> vec;
	int n, quantity;
	string p, c;
	if(mode == 1 || mode == 2) quantity = 0;
	if(mode == 2) vec.push_back("NEW");
	for(int i = 0; i < item.size(); i++)
	{
		if(findInVector(vec, item[i].product) == vec.size())
		{
			vec.push_back(item[i].product);
		}
	}
	vec.push_back("EXIT");
	do
	{
		cout << endl;
		n = menu("Product", vec);
	}
	while(n < 1 || n > vec.size());
	if(vec[n - 1] == "NEW")
	{
		cout << "\nNew Product: ";
		cin.ignore();
		getline(cin, p);
	}
	else if(n == vec.size())
	{
		cout << endl;
		return -1;
	}
	else
	{
		p = vec[n - 1];
	}
	vec.clear();
	if(mode == 2) vec.push_back("NEW");
	for(int i = 0; i < item.size(); i++)
	{
		if(lower(item[i].product) == lower(p) && item[i].quantity >= quantity)
		{
			vec.push_back(item[i].company);
		}
	}
	vec.push_back("EXIT");
	do
	{
		cout << endl;
		n = menu("Company", vec);
	}
	while(n < 1 || n > vec.size());
	if(vec[n - 1] == "NEW")
	{
		cout << "\nNew Company: ";
		cin.ignore();
		getline(cin, c);
	}
	else if(n == vec.size())
	{
		cout << endl;
		return -1;
	}
	else
	{
		c = vec[n - 1];
	}
	for(int i = 0; i < item.size(); i++)
	{
		if(lower(item[i].product) == lower(p) && lower(item[i].company) == lower(c))
		{
			return i;
		}
	}
	item.push_back(inventory(p, c, 0));
	return item.size() - 1;
}

int main()
{
	int c, q, o;
	vector<string> MM;
	MM.push_back("SHOW STOCK");
	MM.push_back("PURCHASED");
	MM.push_back("SOLD");
	MM.push_back("EXIT");
	inventory I[] = 
	{
		inventory("TV", "Samsung", 100),
		inventory("TV", "Sony", 250),
		inventory("TV", "LG", 180),
		inventory("TV", "Toshiba", 130),
		inventory("TV", "Panasonic", 140),
		inventory("Laptop", "HP", 300),
		inventory("Laptop", "Apple", 200),
		inventory("Laptop", "Dell", 280),
		inventory("Laptop", "Lenovo", 270),
		inventory("Laptop", "Acer", 220),
		inventory("Phone", "Samsung", 500),
		inventory("Phone", "Apple", 400),
		inventory("Phone", "Google", 300),
		inventory("Phone", "OnePlus", 350),
		inventory("Phone", "Xiaomi", 450),
		inventory("Tablet", "Microsoft", 150),
		inventory("Tablet", "Amazon", 100),
		inventory("Tablet", "Apple", 200),
		inventory("Tablet", "Samsung", 170),
		inventory("Tablet", "Lenovo", 90),
		inventory("Watch", "Garmin", 90),
		inventory("Watch", "Apple", 110),
		inventory("Watch", "Fitbit", 130),
		inventory("Watch", "Samsung", 85),
		inventory("Watch", "Huawei", 95),
		inventory("Camera", "Canon", 75),
		inventory("Camera", "Nikon", 85),
		inventory("Camera", "Sony", 90),
		inventory("Camera", "Panasonic", 80),
		inventory("Camera", "Olympus", 60)
	};
	vector<inventory> item(I, I + sizeof(I) / sizeof(inventory));
	while(1)
    {
		c = menu("Main Menu", MM);
    	switch(c)
    	{
    		case 1:
    			o = findItem(item, c);
				if(o == -1) break;
				item[o].display();
				break;
			case 2:
    			o = findItem(item, c);
				if(o == -1) break;
				item[o].display();
				do
    			{
    				cout << "Quantity Purchased: ";
					cin >> q;
				}
				while(q < 0);
				item[o] += q;                          
				cout << "New Quantity: " << item[o].quantity << "\n\n";
				break;
			case 3:
    			o = findItem(item, c);
				if(o == -1) break;
				item[o].display();
				do
				{
					cout << "Quantity Sold: ";
					cin >> q;
				}
				while(q < 0 || q > item[o].quantity);
				item[o] += 0 - q;                          
				cout << "New Quantity: " << item[o].quantity << "\n\n";
				break;
			case 4:
				return 0;
			default:
				cout << endl;
				break;
		}
	}
}