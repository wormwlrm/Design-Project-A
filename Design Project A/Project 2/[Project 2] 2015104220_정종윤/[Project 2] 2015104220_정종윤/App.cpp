#include "App.h"


App::App()
{
	loadUserFiles(); // User ���� �ε�
	loadRouterFiles(); // Router ���� �ε�
	loadMailCenterIdFiles(); // MailCenterId ���� �ε�
	md.setDBPointers(&users, &mailCenters, router); // md�� ��� ������ App�� ��� ������ �ʱ�ȭ
}

App::~App()
{
}

void App::run()
{
	cout << "��������������������������������������" << endl;
	cout << "��������������������������������������" << endl;
	cout << "������ ���� ��۰��� ���α׷� ����" << endl;
	cout << "��������������������������������������" << endl;
	cout << "��������������������������������������" << endl;
	while (1)
	{
		cout << "��������������������������������������" << endl;
		cout << "1. �� �α���" << endl;
		cout << "2. ������ �α���" << endl;
		cout << "0. ����" << endl;
		cout << "��������������������������������������" << endl;
		int choice;
		string ID, PW;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "ID�� �Է��ϼ���. : "; cin >> ID;
			cout << "��й�ȣ�� �Է��ϼ���. : "; cin >> PW;
			cout << "��������������������������������������" << endl;
			login(0, ID, PW);
			break;
		case 2:
			cout << "ID�� �Է��ϼ���. : "; cin >> ID;
			cout << "��й�ȣ�� �Է��ϼ���. : "; cin >> PW;
			cout << "��������������������������������������" << endl;
			login(1, ID, PW);
			break;
		case 0:
			exit(100);
			break;
		default:
			if (cin.fail())
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			break;
		}
	}
}

bool App::loadUserFiles()
{
	ifstream loadUser("User.txt");
	string line;
	Manager* manager;
	Client* client;

	while (getline(loadUser, line)) // getline�� �̿��� ���� �ε�
	{
		int _UserType; 
		stringstream get(line);
		string _Id, _Password, _Name, _Address;
		get >> _UserType;
		if (_UserType == 0) // �о���� ���� �� ����Ÿ���� 0�� ���, �� ���� ���
		{
			get >> _Id >> _Password >> _Name; // ���̵�, �н�����, �̸� �о��
			string _AddressTemp;
			
			get >> _Address;
			_AddressTemp = _Address;
			while (get >> _Address)
			{
				_AddressTemp += " ";
				_AddressTemp += _Address;				
			}
			_Address = _AddressTemp; // �ּҴ� �� ���� �� �о�� ��ħ
			client = new Client(_UserType,_Id,_Password,_Name,_Address); // �� Clinet ����
			users.push_back(client); // ���� ���� �� �ڿ� �߰�
		}
		 if (_UserType == 1) // �о���� ���� �� ����Ÿ���� 1�� ���, �� ���� ���
		{
			get >> _Id >> _Password;
			manager = new Manager(_UserType, _Id, _Password); // �� Manager ����
			users.push_back(manager); // �Ŵ��� ���� �� �ڿ� �߰�
		}
	}	
	loadUser.close();

	return 1;
}

bool App::loadRouterFiles()
{
	ifstream loadRouter("Router.txt");
	int number;
	
	router = new int*[12]; // ������ ���� �迭�� �Ҵ�

	for (int i = 0; i < 12; i++)
		router[i] = new int[12];
	
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			loadRouter >> number;
			router[i][j] = number; // ������ ����
		}
	}

	loadRouter.close();
	return 1;
}
bool App::loadMailCenterIdFiles()
{
	ifstream loadMailCenterID("MailCenterID.txt");
	string line;
	MailCenter* mailcenter;
	while (getline(loadMailCenterID, line)) // getline �Լ� ���
	{
		stringstream get(line);
		int _Id;
		string _CityName;
		get >> _Id >> _CityName; // ���̵�� ���ø� �޾ƿ�
		mailcenter = new MailCenter(_Id, _CityName); // MailCenter ����
		mailCenters.push_back(mailcenter); //���ϼ��� ���� �� �ڿ� �߰�
	}

	loadMailCenterID.close();
	return 1;
}

User* App::login(int userType, string user_id, string Password)
{
	int i = 0;
	
	while (i < 36)
	{
		if (users.at(i)->getId() == user_id) // ���̵� ��ġ�ϴ��� Ȯ��
		{
			if (users.at(i)->getPassword() == Password) // ��й�ȣ�� ��ġ�ϴ��� Ȯ��
			{
				if (userType == 0) // Client ���� �α��� �õ�
				{
					if (users.at(i)->getUserType() == 0) // �α����� �õ��� ����� Client �� ���
					{
						cout << "���������� �α��� �Ǿ����ϴ�." << endl;
						loginedUser = (users[i]); // loginedUser�� ���� ������ �ּҰ��� ����
						printClientMenu();
						return loginedUser;
					}
					else
					{
						cout << "������ �����ϴ�." << endl;
						return NULL;
					}					
				}	
				if (userType == 1) // Manager ���� �α��� �õ�
				{
					if (users.at(i)->getUserType() == 1) // �α����� �õ��� ������ Manager�� ���
					{
						cout << "���������� �α��� �Ǿ����ϴ�." << endl;
						loginedUser = (users[i]); // loginedUser�� ���� ������ �ּҰ��� ����
						printManagerMenu();
						return loginedUser;
					}
					else
					{
						cout << "������ �����ϴ�." << endl;
						return NULL;
					}
				}
			}

			else // ��й�ȣ�� ��ġ���� ���� ��� ���� ó��
			{
				cout << "Error : ��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
				return NULL;
				break;
			}
		}
		i++;
	}
	cout << "Error : ����Ʈ�� ��ġ�ϴ� ID�� �����ϴ�." << endl; // ���̵� ��ġ���� ���� ��� ���� ó��
	return NULL;
	return 0;
}

bool App::logout()
{
	loginedUser = NULL;
	return 0;
}

/*void App::saveFiles(){}*/

void App::printClientMenu()
{
	while (1)
	{
		cout << "��������������������������������������" << endl;
		cout << "����� �̸� : " << ((Client*)loginedUser)->getName() << endl;
		cout << "�ּ�        : " << ((Client*)loginedUser)->getAddress() << endl;
		cout << "��������������������������������������" << endl;
		cout << "1. ���� ������" << endl;
		cout << "2. ���� �ޱ�" << endl;
		cout << "3. ���� ���� ���" << endl;
		cout << "0. �α׾ƿ�" << endl;
		cout << "��������������������������������������" << endl;
		int choice; cin >> choice;
		switch (choice)
		{
		case 1:
			loginedUser->send(md); // ���� ������
			break;
		case 2:
			loginedUser->receive(md); // ���� �ޱ�
			break;
		case 3:
			((Client*)loginedUser)->printSendedMail(); // ���� ���� ���
			break;
		case 0:
			logout(); run(); // �α׾ƿ�
			break;
		default:
			if (cin.fail()) // �߸��� �Է½� ����ó��
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			break;
		}
	}
}

void App::printManagerMenu()
{
	while (1)
	{
		cout << "������ �������߱��� �������� �Է����ּ���." << endl;
		cout << "0�� �Է��Ͻø� ���� �޴��� ���ư��ϴ�. : ";
		string name;
		cin >> name;
		if (name == "0")  // ���� �޴���
		{
			run();
			return;
		}
		for (int i = 0; i < 12; i++)
		{
			if (name == mailCenters.at(i)->getCityName()) // ���� ���Ϳ� ��ġ�ϴ� �̸� �߰� ��
			{
				while (1)
				{
					cout << "��������������������������������������" << endl;
					((Manager*)loginedUser)->setCurrentCityName(name);
					cout << "���� �������� ���� : " << ((Manager*)loginedUser)->getCurrentCityName() << endl;
					cout << "��������������������������������������" << endl;
					cout << "1. ���� ������" << endl;
					cout << "2. ���� �ޱ�" << endl;
					cout << "0. ������" << endl;
					cout << "��������������������������������������" << endl;
					int choice; cin >> choice;
					switch (choice)
					{
					case 1:
						loginedUser->send(md); // ���� ������
						break;
					case 2:
						loginedUser->receive(md); // ���� �ޱ�
						break;
					case 0:
						printManagerMenu(); // ������
						break;
					default: // �߸��� �Է� ����ó��
						if (cin.fail())
						{
							cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
							cin.clear();
							cin.ignore(256, '\n');
							break;
						}
						cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
						break;
					}
				}
			}
		}
		cout << "Error : �Է��Ͻ� �������� �������� �ʽ��ϴ�."; // ���� �̸� �������� ���� �� ����ó��

		return;
	}
}