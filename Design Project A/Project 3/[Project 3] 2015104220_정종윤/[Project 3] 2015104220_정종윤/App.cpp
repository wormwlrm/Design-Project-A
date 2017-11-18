#include "App.h"

//�⺻ ������
App::App()
{
	system("title 2015104220 ������ - �� ��õ ���α׷�");
	loadUserFile();
	loadRoomFile();
	//���� �ʱ� �� ����
	isFilter1Skipped = true;
	isFilter2Skipped = true;
	isFilter3Skipped = true;
}

//�Ҹ���
App::~App()
{
	
}


//���� ������ ���� �ε�
void App::loadUserFile()
{
	ifstream loadUser("User.txt");
	int _UserType, _X, _Y, _Search, _SearchID, _Request, _RequestID, _Rooms, _RoomID;
	string _ID, _PW;
	User* CurUser;

	while (loadUser >> _UserType)
	{
		//������ �Ǹ����� ���
		if (_UserType == 0)
		{
			CurUser = new Seller;
			loadUser >> _ID >> _PW;
			CurUser->setId(_ID);
			CurUser->setPassword(_PW);
			CurUser->setUserType(0);

			loadUser >> _Rooms;
			//����� �� ����
			for (int i = 0; i < _Rooms; i++)
			{
				loadUser >> _RoomID;
				((Seller*)CurUser)->getRegisteredRoomList()->push_back(_RoomID); 
			}
		}
		//������ �������� ���
		else if (_UserType == 1)
		{
			CurUser = new Buyer;
			loadUser >> _ID >> _PW;
			CurUser->setId(_ID);
			CurUser->setPassword(_PW);
			CurUser->setUserType(1);

			loadUser >> _X >> _Y >> _Search;
			((Buyer*)CurUser)->setXCoord(_X);
			((Buyer*)CurUser)->setYCoord(_Y);
			//�ֱ� �˻� ���� �߰�
			for (int i = 0; i < _Search; i++)
			{
				loadUser >> _SearchID;
				(((Buyer*)CurUser)->getRecentlySearched())->push_back(_SearchID);
			}
			//���� ��û ���� �߰�
			loadUser >> _Request;
			for (int j = 0; j < _Request; j++)
			{
				loadUser >> _RequestID;
				(((Buyer*)CurUser)->getRoomsRequestToBuy())->push_back(_RequestID);
			}
		}
		users.push_back(CurUser);
	}
	loadUser.close();
}

//�� ������ ���� �ε�
void App::loadRoomFile()
{
	ifstream loadRoom("Room.txt");
	int _RoomType, _RoomID, _X, _Y, _Request, _Deposit, _Monthly, _Cost;
	string _RoomName, _RequestID, _SellerID;
	Room* CurRoom;

	while (loadRoom >> _RoomType)
	{
		//���� ������ ���
		if (_RoomType == 0)
		{
			CurRoom = new RoomForRent;
			loadRoom >> _RoomID >> _SellerID >> _RoomName >> _X >> _Y >> _Request;
			CurRoom->setRoomID(_RoomID);
			CurRoom->setSellerID(_SellerID);
			CurRoom->setRoomName(_RoomName);
			CurRoom->setXCoord(_X);
			CurRoom->setYCoord(_Y);
			CurRoom->setRoomType(0);
			//���� ��û ���̵� �߰�
			for (int i = 0; i < _Request; i++)
			{
				loadRoom >> _RequestID;
				(((RoomForRent*)CurRoom)->getUsersRequestToBuyList())->push_back(_RequestID);
			}
			loadRoom >> _Deposit >> _Monthly;
			((RoomForRent*)CurRoom)->setDeposit(_Deposit);
			((RoomForRent*)CurRoom)->setMonthlyPay(_Monthly);
		}

		//���� �Ÿ��� ���
		else if (_RoomType == 1)
		{
			CurRoom = new RoomForSale;
			loadRoom >> _RoomID >> _SellerID >> _RoomName >> _X >> _Y >> _Request;
			CurRoom->setRoomID(_RoomID);
			CurRoom->setSellerID(_SellerID);
			CurRoom->setRoomName(_RoomName);
			CurRoom->setXCoord(_X);
			CurRoom->setYCoord(_Y);
			CurRoom->setRoomType(1);			
			//���� ��û ���̵� �߰�
			for (int i = 0; i < _Request; i++)
			{
				loadRoom >> _RequestID;
				(((RoomForSale*)CurRoom)->getUsersRequestToBuyList())->push_back(_RequestID);
			}
			loadRoom >> _Cost;
			(((RoomForSale*)CurRoom))->setCost(_Cost);
		}

		rooms.push_back(CurRoom);
	}
	//����
	Room* Temp;
	for (size_t i = 0; i < rooms.size() - 1; i++)
	{
		for (size_t j = 0; j < rooms.size() - 1 - i; j++)
		{
			if (rooms.at(j)->getRoomID() > rooms.at(j + 1)->getRoomID())
			{
				Temp = rooms.at(j);
				rooms.at(j) = rooms.at(j + 1);
				rooms.at(j + 1) = Temp;
			}
		}
	}
	loadRoom.close();
}


//���� ����
void App::saveFiles()
{
	ofstream saveUser("User.txt");
	ofstream saveRoom("Room.txt");

	//���� ���� ����
	for (size_t i = 0; i < users.size(); i++)
	{
		int userType = users.at(i)->getUserType();
		string ID = users.at(i)->getId();
		string PW = users.at(i)->getPassword();
		saveUser << userType << "\t" << ID << "\t" << PW << "\t";
		//������ �������� ���
		if (userType == 1)
		{
			int X = ((Buyer*)users.at(i))->getXCoord();
			int Y = ((Buyer*)users.at(i))->getYCoord();
			saveUser << X << "\t" << Y << "\t";
			int Recently = ((Buyer*)users.at(i))->getRecentlySearched()->size();
			saveUser << Recently << "\t";
			//�ֱ� �˻� ���� ����
			for (int j = 0; j < Recently; j++)
			{
				saveUser << ((Buyer*)users.at(i))->getRecentlySearched()->at(j) << "\t";
			}
			int Request = ((Buyer*)users.at(i))->getRoomsRequestToBuy()->size();
			saveUser << Request << "\t";
			//���� ��û ���� ����
			for (int j = 0; j < Request; j++)
			{
				saveUser << ((Buyer*)users.at(i))->getRoomsRequestToBuy()->at(j) << "\t";
			}
			saveUser << "\n";
		}
		//������ �Ǹ����� ���
		else if (userType == 0)
		{
			int Rooms = ((Seller*)users.at(i))->getRegisteredRoomList()->size();
			saveUser << Rooms << "\t";
			for (int j = 0; j < Rooms; j++)
			{
				saveUser << ((Seller*)users.at(i))->getRegisteredRoomList()->at(j) << "\t";
			}
			saveUser << "\n";
		}
	}

	//�� ���� ����
	for (size_t i = 0; i < rooms.size(); i++)
	{
		int RoomType = rooms.at(i)->getRoomType();
		int ID = rooms.at(i)->getRoomID();
		string seller = rooms.at(i)->getSellerID();
		string Name = rooms.at(i)->getRoomName();
		int X = rooms.at(i)->getXCoord();
		int Y = rooms.at(i)->getYCoord();
		int Request = rooms.at(i)->getUsersRequestToBuyList()->size();
		saveRoom << RoomType << "\t" << ID << "\t" << seller << "\t" << Name << "\t" << X << "\t" << Y << "\t" << Request << "\t";
		for (int j = 0; j < Request; j++)
		{
			string Requester = rooms.at(i)->getUsersRequestToBuyList()->at(j);
			saveRoom << Requester << "\t";
		}
		//���� ������ ���
		if (RoomType == 0)
		{
			int Deposit = ((RoomForRent*)rooms.at(i))->getDeposit();
			int Monthly = ((RoomForRent*)rooms.at(i))->getMonthlyPay();
			saveRoom << Deposit << "\t" << Monthly << "\t";
		}
		//���� �Ÿ��� ���
		else if (RoomType == 1)
		{
			int Cost = ((RoomForSale*)rooms.at(i))->getCost();
			saveRoom << Cost << "\t";
		}
		saveRoom << "\n";
	}

	saveUser.close();
	saveRoom.close();
}


//���α׷� ����
void App::run()
{
	printMenu();
}

//���� 1 ��ȯ �Լ�
vector<Room*> App::getFilter1Result()
{
	return resultOfFilter1;
}

//���� 2 ��ȯ �Լ�
vector<Room*> App::getFilter2Result()
{
	return resultOfFilter2;
}

//���� 3 ��ȯ �Լ�
vector<Room*> App::getFilter3Result()
{
	return resultOfFilter3;
}

//�޴� ���
void App::printMenu()
{
//	system("pause");
//	system("cls");
	while (1)
	{
		cout << "��������������������������������������" << endl;
		cout << "��������������������������������������" << endl;
		cout << "������     �� ��õ ���α׷�     ����" << endl;
		cout << "��������������������������������������" << endl;
		cout << "��������������������������������������" << endl;
		cout << "1. ������ �α���" << endl;
		cout << "2. �Ǹ��� �α���" << endl;
		cout << "0. ����" << endl;
		cout << "��������������������������������������" << endl;
		int choice;
		string ID, PW;
		cin >> choice;
		switch (choice)
		{
		case 1: // ������ �α���
			if (loginedUser != NULL)
			{
				cout << "Error : �̹� �α��� �� �����Դϴ�." << endl;
				cout << "������ �α��� �� �������� �����մϴ�." << endl;
				if (loginedUser->getUserType() == 1)
				{
					printBuyerMenu();
					break;
				}
				else
				{
					printSellerMenu();
					break;
				}
			}
			cout << "ID�� �Է��ϼ���. : "; cin >> ID;
			cout << "��й�ȣ�� �Է��ϼ���. : "; cin >> PW;
			cout << "��������������������������������������" << endl;
			login(1, ID, PW);
			break;
		case 2: // �Ǹ��� �α���
			if (loginedUser != NULL)
			{
				cout << "Error : �̹� �α��� �� �����Դϴ�." << endl;
				cout << "������ �α��� �� �������� �����մϴ�." << endl;
				if (loginedUser->getUserType() == 1)
				{
					printBuyerMenu();
					break;
				}
				else
				{
					printSellerMenu();
					break;
				}
			}
			cout << "ID�� �Է��ϼ���. : "; cin >> ID;
			cout << "��й�ȣ�� �Է��ϼ���. : "; cin >> PW;
			cout << "��������������������������������������" << endl;
			login(0, ID, PW);
			break;
		case 0: // ����
			saveFiles();
			exit(100);
			return;
			break;
		default: // �߸��� �Է� ���� ó��
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

void App::printBuyerMenu()
{
	int choice;	
	while (1)
	{
		cout << "��������������������������������������" << endl;
		cout << "��           ������ �޴�            ��" << endl;
		cout << "��������������������������������������" << endl;
		loginedUser->printUserInfo();
		cout << "��������������������������������������" << endl;
		cout << "1. �˻� ���� ����" << endl;
		cout << "2. �� �˻�" << endl;
		cout << "3. �ֱ� �˻� ��� ���" << endl;
		cout << "4. ���� ��û ��� ���" << endl;
		cout << "0. �α׾ƿ�" << endl;
		cout << "��������������������������������������" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: // �˻� ���� ����
			setFilters();
			break;
		case 2: // �� �˻�
			searchRooms();
			break;
		case 3: // �ֱ� �˻� ��� ���
			printRecentlySearcedRoomsOfLoginedUser();
			break;
		case 4: // ���� ��û ��� ���
			printRequestToBuyList();
			break;
		case 0: // �α׾ƿ�
			resultOfFilter1.clear(); isFilter1Skipped = true;
			resultOfFilter2.clear(); isFilter2Skipped = true;
			resultOfFilter3.clear(); isFilter3Skipped = true;
			logout() ? cout << "���������� �α׾ƿ� �Ͽ����ϴ�." << endl : cout << "Error : �α��� �� ������ �����ϴ�." << endl;
			printMenu();
			break;
		default: // �߸��� �Է� ���� ó��
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

void App:: printSellerMenu()
{
	int choice;
	while (1)
	{
		cout << "��������������������������������������" << endl;
		cout << "��           �Ǹ��� �޴�            ��" << endl;
		cout << "��������������������������������������" << endl;
		loginedUser->printUserInfo();
		cout << "��������������������������������������" << endl;
		cout << " ����� �� ��� : " << endl;
		if (((Seller*)loginedUser)->getRegisteredRoomList()->size() != 0)
		{
			for (size_t i = 0; i < ((Seller*)loginedUser)->getRegisteredRoomList()->size(); i++)
			{
				cout << "�� " << getRoomByID((((Seller*)loginedUser)->getRegisteredRoomList()->at(i)))->getRoomName() << endl; /**/
			}
		}
		else
		{
			cout << "���� ��ϵ� ���� �����ϴ�." << endl;
		}
		cout << "��������������������������������������" << endl;
		cout << "1. �� ���" << endl;
		cout << "2. �� ����" << endl;
		cout << "0. �α׾ƿ�" << endl;
		cout << "��������������������������������������" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: // �� ���
			registerNewRoom();
			break;
		case 2: // �� ����
			deleteRoom();
			break;
		case 0: // �α׾ƿ�
			logout() ? cout << "���������� �α׾ƿ� �Ͽ����ϴ�." << endl : cout << "Error : �α��� �� ������ �����ϴ�." << endl;
			printMenu();
			break;
		default: // �߸��� �Է� ���� ó��
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

//�α���
bool App::login(int userType, string userID, string password)
{
	size_t i = 0;
	while (i < users.size())
	{
		// ���̵� ��ġ�ϴ��� Ȯ��
		if (users.at(i)->getId() == userID) 
		{
			// ��й�ȣ�� ��ġ�ϴ��� Ȯ��
			if (users.at(i)->getPassword() == password)
			{
				// �Ǹ��� ���� �α��� �õ�
				if (userType == 0) 
				{
					// �α����� �õ��� ����� �Ǹ��� �� ���
					if (users.at(i)->getUserType() == 0) 
					{
						cout << "���������� �α��� �Ǿ����ϴ�." << endl;
						loginedUser = (users[i]); // loginedUser�� ���� ������ �ּҰ��� ����
						printSellerMenu();
						return 1;
					}
					else
					{
						cout << "������ �����ϴ�." << endl;
						return NULL;
					}
				}
				// ������ ���� �α��� �õ�
				if (userType == 1) 
				{
					// �α����� �õ��� ������ �������� ���
					if (users.at(i)->getUserType() == 1) 
					{
						cout << "���������� �α��� �Ǿ����ϴ�." << endl;
						loginedUser = (users[i]); // loginedUser�� ���� ������ �ּҰ��� ����
						resultOfFilter3 = rooms;
						printBuyerMenu();
						return 1;
					}
					else
					{
						cout << "������ �����ϴ�." << endl;
						return 0;
					}
				}
			}
			// ��й�ȣ�� ��ġ���� ���� ��� ���� ó��
			else 
			{
				cout << "Error : ��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
				return 0;
				break;
			}
		}
		i++;
	}
	// ���̵� ��ġ���� ���� ��� ���� ó��
	cout << "Error : ����Ʈ�� ��ġ�ϴ� ID�� �����ϴ�." << endl; 
	return 0;
}

//�α׾ƿ�
bool App::logout()
{
	if (loginedUser == NULL)
	{
		return false;
	}
	loginedUser = NULL;
	return true;
}

//���� ����
void App::setFilters()
{
	cout << "��������������������������������������" << endl;
	cout << "��             ���� ����            ��" << endl;
	cout << "��������������������������������������" << endl;

	//���� 1 ����
	cout << "�˻��� �ݰ��� �����Ͻðڽ��ϱ�?" << endl;
	cout << "��������������������������������������" << endl;
	cout << "1. ��" << endl;
	cout << "2. �ƴϿ�" << endl;
	cout << "��������������������������������������" << endl;
	int choice; cin >> choice;
	switch (choice)
	{
	case 1: // �˻��� �ݰ� ����
		isFilter1Skipped = false;
		cout << "��������������������������������������" << endl;
		cout << "�������� ���� ��ġ�� " << ((Buyer*)loginedUser)->getXCoord() << " , " << ((Buyer*)loginedUser)->getYCoord() << " �Դϴ�." << endl;
		cout << "�˻��� �ݰ��� �Է��� �ֽʽÿ�. : ";
		cin >> searchAreaRadius;
		if (cin.fail() || searchAreaRadius < 0)
		{
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "��������������������������������������" << endl;
		resultOfFilter1.clear();
		if (0 < searchAreaRadius && isFilter1Skipped == false)
		{
			double distance;
			for (size_t i = 0; i < rooms.size(); i++)
			{
				distance = pow(pow(((Buyer*)loginedUser)->getXCoord() - rooms.at(i)->getXCoord(), 2) + pow(((Buyer*)loginedUser)->getYCoord() - rooms.at(i)->getYCoord(), 2), 0.5);
				if (distance < searchAreaRadius)
				{
					resultOfFilter1.push_back(rooms.at(i));
				}
			}
		}
		break;
	case 2: // ���� 1 ����
		isFilter1Skipped = true;
		resultOfFilter1.clear();
		for (size_t i = 0; i < rooms.size(); i++)
		{
			resultOfFilter1.push_back(rooms.at(i));
		}
		break;
	default: // �߸��� �Է� ���� ó��
		if (cin.fail())
		{
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
		return;
	}

	//���� 2 ����
	cout << "���� ������ �����Ͻðڽ��ϱ�?" << endl;
	cout << "��������������������������������������" << endl;
	cout << "1. ��" << endl;
	cout << "2. �ƴϿ�" << endl;
	cout << "��������������������������������������" << endl;
	int choice2; cin >> choice2;	
	switch (choice2)
	{
	case 1: // ���� ���� ����
		isFilter2Skipped = false;
		cout << "��������������������������������������" << endl;
		cout << "������ �ִ밪, �ּҰ��� �Է��Ͻʽÿ�. : "; cin >> maxMonthlyPay >> minMonthlyPay;
		if (cin.fail() || maxMonthlyPay < minMonthlyPay)
		{
			cout << "Error : �ùٸ��� ���� �����̰ų� ���� �Է��� �߸��Ǿ����ϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "�������� �ִ밪, �ּҰ��� �Է��Ͻʽÿ�. : "; cin >> maxDeposit >> minDeposit;
		if (cin.fail() || maxDeposit < minDeposit)
		{
			cout << "Error : �ùٸ��� ���� �����̰ų� ������ �Է��� �߸��Ǿ����ϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "�ŸŰ��� �ִ밪, �ּҰ��� �Է��Ͻʽÿ�. : "; cin >> maxCost >> minCost;
		if (cin.fail() || maxCost < minCost)
		{
			cout << "Error : �ùٸ��� ���� �����̰ų� �ŸŰ� �Է��� �߸��Ǿ����ϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		resultOfFilter2.clear();
		for (size_t i = 0; i < resultOfFilter1.size(); i++)
		{
			//����
			if (resultOfFilter1.at(i)->getRoomType() == 0)
			{
				if (((RoomForRent*)resultOfFilter1.at(i))->getDeposit() > minDeposit && ((RoomForRent*)resultOfFilter1.at(i))->getDeposit() < maxDeposit &&
					((RoomForRent*)resultOfFilter1.at(i))->getMonthlyPay() > minMonthlyPay && ((RoomForRent*)resultOfFilter1.at(i))->getMonthlyPay() < maxMonthlyPay)
				{
					resultOfFilter2.push_back(resultOfFilter1.at(i));

				}
			}

			//�Ÿ�
			if (resultOfFilter1.at(i)->getRoomType() == 1)
			{
				if (((RoomForSale*)resultOfFilter1.at(i))->getCost() > minCost && ((RoomForSale*)resultOfFilter1.at(i))->getCost() < maxCost)
				{
					resultOfFilter2.push_back(resultOfFilter1.at(i));
				}
			}
		}
		break;
	case 2: // ���� 2 ����
		isFilter2Skipped = true;
		resultOfFilter2.clear();
		for (size_t i = 0; i < resultOfFilter1.size(); i++)
		{
			resultOfFilter2.push_back(resultOfFilter1.at(i));
		}
		break;
	default: // �߸��� �Է� ���� ó��
		if (cin.fail())
		{
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
		return;
		break;
	}

	//���� 3 ����
	cout << "�˻�� �����Ͻðڽ��ϱ�?" << endl;
	cout << "��������������������������������������" << endl;
	cout << "1. ��" << endl;
	cout << "2. �ƴϿ�" << endl;
	cout << "��������������������������������������" << endl;
	int choice3; cin >> choice3; string getName;
	switch (choice3)
	{
	case 1: // �˻��� ����
		isFilter3Skipped = false;
		cout << "��������������������������������������" << endl;
		cout << "�˻�� �Է��Ͻʽÿ�. : "; cin >> searchKey;
		resultOfFilter3.clear();
		for (size_t i = 0; i < resultOfFilter2.size(); i++)
		{
			if (resultOfFilter2.at(i)->getRoomName().find(searchKey) != string::npos)
			{
				resultOfFilter3.push_back(resultOfFilter2.at(i));
			}
		}
		break;
	case 2: // ���� 3 ����
		isFilter3Skipped = true;
		resultOfFilter3.clear();
		for (size_t i = 0; i < resultOfFilter2.size(); i++)
		{
			resultOfFilter3.push_back(resultOfFilter2.at(i));
		}
		break;
	default: // �߸��� �Է� ���� ó��
		if (cin.fail())
		{
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
		return;
		break;
	}

	cout << "���� ������ �Ϸ�Ǿ����ϴ�." << endl;

	return;
}

//�ֱ� �˻� ���� ���
void App::printRecentlySearcedRoomsOfLoginedUser()
{
	cout << "��������������������������������������" << endl;
	cout << "��          �ֱ� �˻� ����          ��" << endl;
	cout << "��������������������������������������" << endl;
	// �˻� ������ �������� ���� ��� ���� ó��
	if (((Buyer*)loginedUser)->getRecentlySearched()->size() == 0)
	{
		cout << "Error : �ֱ� �˻� ������ �������� �ʽ��ϴ�." << endl;
		return;
	}

	// ���� Ž�� ����
	int* arr = new int[rooms.size()];
	for (size_t i = 0; i < rooms.size(); i++)
	{
		*(arr + i) = rooms.at(i)->getRoomID();
	}
	for (size_t i = 0; i < ((Buyer*)loginedUser)->getRecentlySearched()->size(); i++)
	{
		getRoomByID(RecusiveBinSearch(arr, arr[0], arr[(rooms.size()) - 1], ((Buyer*)loginedUser)->getRecentlySearched()->at(i)))->printRoomInfo();
	}

	delete[] arr;
}

//ID�� �̿��� Room ��ȯ
Room* App::getRoomByID(int _roomID)
{
	Room* Temp;
	for (size_t i = 0; i < rooms.size(); i++)
	{
		if (rooms.at(i)->getRoomID() == _roomID)
		{
			Temp = rooms.at(i);
			return Temp;
		}
	}
	return NULL;
}

//���� ���͵��� ������ ���
bool App::printFilterConditions()
{
	cout << "��������������������������������������" << endl;
	cout << "��        ����  ������  ����        ��" << endl;
	cout << "��������������������������������������" << endl;
	cout << "�˻� �ݰ�   : ";
	isFilter1Skipped == true ? cout << "��� ����" << endl : cout << "������" << endl;
	cout << "��� ����   : ";
	isFilter2Skipped == true ? cout << "��� ����" << endl : cout << "������" << endl;
	cout << "Ư�� �˻��� : ";
	isFilter3Skipped == true ? cout << "��� ����" << endl : cout << "������" << endl;
	return 0;
}

//���� ��û ���� ���
void App::printRequestToBuyList()
{
	cout << "��������������������������������������" << endl;
	cout << "��          ���� ��û ����          ��" << endl;
	cout << "��������������������������������������" << endl;
	//���� ��û ������ �������� ���� ��� ���� ó��
	if (((Buyer*)loginedUser)->getRoomsRequestToBuy()->size() == 0)
	{
		cout << "Error : ���� ��û ������ �������� �ʽ��ϴ�." << endl;
		return;
	}

	//���� ��û ���� ���
	for (size_t i = 0; i < ((Buyer*)loginedUser)->getRoomsRequestToBuy()->size(); i++)
	{
		getRoomByID(((Buyer*)loginedUser)->getRoomsRequestToBuy()->at(i))->printRoomInfo();
	}
}

//�� �˻�
void App::searchRooms()
{
	cout << "��������������������������������������" << endl;
	cout << "��             �˻� ���            ��" << endl;
	cout << "��������������������������������������" << endl;
	//������ ������ ����� ���� ��� ���� ó��
	if (resultOfFilter3.size() == 0)
	{
		cout << "Error : �˻� ����� �����ϴ�." << endl;
		return;
	}
	cout << "�� " << resultOfFilter3.size() << " ���� �˻� ����� �ֽ��ϴ�." << endl;
	printFilterConditions();
	cout << "��������������������������������������" << endl;
	for (size_t i = 0; i < resultOfFilter3.size(); i++)
	{
		cout << i + 1 << ". " << resultOfFilter3.at(i)->getRoomName() << endl;
	}
	cout << "��������������������������������������" << endl;
	cout << "��ȣ�� �Է��Ͽ� �ڼ��� ������ Ȯ���մϴ�. : ";  
	size_t choice; cin >> choice;
	
	//�߸��� �Է� ���� ó��
	if (cin.fail() || choice > resultOfFilter3.size() || choice <= 0)
	{
		cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	
	resultOfFilter3.at(--choice)->printRoomInfo();
	//�ֱ� �˻� ������ �߰�
	
	((Buyer*)loginedUser)->getRecentlySearched()->push_back((resultOfFilter3.at(choice)->getRoomID()));
	//�ֱ� �˻� ������ 5���� Ŭ ��� ������ �ͺ��� ����
	if (((Buyer*)loginedUser)->getRecentlySearched()->size() > 5)
	{
		((Buyer*)loginedUser)->getRecentlySearched()->erase(((Buyer*)loginedUser)->getRecentlySearched()->begin());
	}

	cout << "��������������������������������������" << endl;
	cout << "��             ���� ��û            ��" << endl;
	cout << "��������������������������������������" << endl;
	cout << "1. ��" << endl;
	cout << "2. �ƴϿ�" << endl;
	cout << "��������������������������������������" << endl;
	int choice2; cin >> choice2;
	switch (choice2)
	{
	case 1:
		//�̹� ���ſ�û�� ���� �ٽ� �����Ϸ��� �ϴ� ��� ���� ó��
		for (size_t i = 0; i < (((Buyer*)loginedUser)->getRoomsRequestToBuy())->size(); i++)
		{
			if ((((Buyer*)loginedUser)->getRoomsRequestToBuy())->at(i) == resultOfFilter3.at(choice)->getRoomID())
			{
				cout << "Error : �̹� ���� ��û�� ���Դϴ�." << endl;
				return;
			}
		}
		//�������� ���� ��û ������ �߰�
		(((Buyer*)loginedUser)->getRoomsRequestToBuy())->push_back(resultOfFilter3.at(choice)->getRoomID());
		//���� ���� ��û ����Ʈ�� �߰�
		resultOfFilter3.at(choice)->getUsersRequestToBuyList()->push_back(loginedUser->getId());
		cout << "���� ��û�� �Ϸ�Ǿ����ϴ�." << endl;
		break;
	case 2:
		return;
		break;
	default:
		//�߸��� �Է� ���� ó��
		if (cin.fail())
		{
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
		break;
	}
}

// �� ���
void App::registerNewRoom()
{
	cout << "��������������������������������������" << endl;
	cout << "��              �� ���             ��" << endl;
	cout << "��������������������������������������" << endl;
	cout << "�� ���� ����Ͻðڽ��ϱ�?" << endl;
	cout << "1. ��" << endl;
	cout << "2. �ƴϿ�" << endl;
	cout << "��������������������������������������" << endl;
	int choice, choice2; cin >> choice;

	int Biggest = rooms.at(rooms.size()-1)->getRoomID();
	Room* NewRoom;
	string RoomName;
	int RoomX, RoomY, RoomD, RoomM, RoomC;

	switch (choice)
	{
	case 1: // �� �� ���
		cout << "�� ������ ������ �ּ���." << endl;
		cout << "1. ����" << endl;
		cout << "2. �Ÿ�" << endl;
		cout << "��������������������������������������" << endl;
		cin >> choice2;
		switch (choice2)
		{
		case 1: // ���� ���
			cout << "�� �̸��� �Է����ּ���. : "; cin >> RoomName;
			cout << "���� X��ǥ�� �Է����ּ���. : "; cin >> RoomX;
			//�߸��� �Է� ���� ó��
			if (cin.fail() || RoomX < 0)
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "���� Y��ǥ�� �Է����ּ���. : "; cin >> RoomY;
			//�߸��� �Է� ���� ó��
			if (cin.fail() || RoomY < 0)
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "���� ������(����)�� �Է����ּ���. : "; cin >> RoomD;
			//�߸��� �Է� ���� ó��
			if (cin.fail() || RoomD < 0)
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "���� ����(����)�� �Է����ּ���. : "; cin >> RoomM;
			//�߸��� �Է� ���� ó��
			if (cin.fail() || RoomM < 0)
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			NewRoom = new RoomForRent;
			NewRoom->setRoomID(Biggest+1);
			NewRoom->setRoomName(RoomName);
			NewRoom->setRoomType(0);
			NewRoom->setSellerID(((Seller*)loginedUser)->getId());
			NewRoom->setXCoord(RoomX);
			NewRoom->setYCoord(RoomY);
			((RoomForRent*)NewRoom)->setDeposit(RoomD);
			((RoomForRent*)NewRoom)->setMonthlyPay(RoomM);
			//��ü �� ��Ͽ� �߰�
			rooms.push_back(NewRoom);
			//����� �� ��Ͽ� �߰�
			((Seller*)loginedUser)->getRegisteredRoomList()->push_back(Biggest+1);
			cout << "���������� ��ϵǾ����ϴ�." << endl;
			break;
		case 2: // �Ÿ� ���
			cout << "�� �̸��� �Է����ּ���. : "; cin >> RoomName;
			cout << "���� X��ǥ�� �Է����ּ���. : "; cin >> RoomX;
			//�߸��� �Է� ���� ó��
			if (cin.fail() || RoomX < 0)
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "���� Y��ǥ�� �Է����ּ���. : "; cin >> RoomY;
			//�߸��� �Է� ���� ó��
			if (cin.fail() || RoomY < 0)
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "���� �ŸŰ�(����)�� �Է����ּ���. : "; cin >> RoomC;
			//�߸��� �Է� ���� ó��
			if (cin.fail() || RoomC < 0)
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			NewRoom = new RoomForSale;
			NewRoom->setRoomID(Biggest + 1);
			NewRoom->setRoomName(RoomName);
			NewRoom->setRoomType(1);
			NewRoom->setSellerID(((Seller*)loginedUser)->getId());
			NewRoom->setXCoord(RoomX);
			NewRoom->setYCoord(RoomY);
			((RoomForSale*)NewRoom)->setCost(RoomC);
			//��ü �� ��Ͽ� �߰�
			rooms.push_back(NewRoom);
			//����� �� ��Ͽ� �߰�
			((Seller*)loginedUser)->getRegisteredRoomList()->push_back(Biggest + 1);
			cout << "���������� ��ϵǾ����ϴ�." << endl;
			break;
		default: // �߸��� �Է� ���� ó��
			if (cin.fail())
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			return;
			break;
		}
		break;
	case 2: // �� ����� ���
		return;
		break;
	default: // �߸��� �Է� ���� ó��
		if (cin.fail())
		{
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
		return;
		break;
	}
}

//�� ����
void App::deleteRoom()
{
	cout << "��������������������������������������" << endl;
	cout << "��              �� ����             ��" << endl;
	cout << "��������������������������������������" << endl;
	//������ ���� ���� ��� ���� ó��
	if (((Seller*)loginedUser)->getRegisteredRoomList()->size() == 0)
	{
		cout << "Error : ������ ���� �������� �ʽ��ϴ�." << endl;
		return;
	}
	cout << "���� ��ϵ� ���� �� " << ((Seller*)loginedUser)->getRegisteredRoomList()->size() <<" �� �Դϴ�."<< endl;
	
	cout << "��������������������������������������" << endl;
	cout << "�� ID ��             �� �̸�          " << endl;
	cout << "��������������������������������������" << endl;
	if (((Seller*)loginedUser)->getRegisteredRoomList()->size() != 0)
	{
		for (size_t i = 0; i < ((Seller*)loginedUser)->getRegisteredRoomList()->size(); i++)
		{			   
			cout << "�� " << setw(2) << getRoomByID((((Seller*)loginedUser)->getRegisteredRoomList()->at(i)))->getRoomID() << " ��" << " " << getRoomByID((((Seller*)loginedUser)->getRegisteredRoomList()->at(i)))->getRoomName() << endl; /**/
		}
	}
	cout << "��������������������������������������" << endl;
	cout << "�����Ͻ� ���� ID�� �Է����ֽʽÿ�." << endl;
	cout << "��������������������������������������" << endl;
	int choice, roomAtWhere; cin >> choice;

	//������ ���� �ִ��� �˻�
	bool rightChoice = false;

	for (size_t i = 0; i < ((Seller*)loginedUser)->getRegisteredRoomList()->size(); i++)
	{
		//������ ���� ã�� ���
		if (getRoomByID(((Seller*)loginedUser)->getRegisteredRoomList()->at(i))->getRoomID() == choice)
		{
			rightChoice = true;
			//���� ���� ���
			getRoomByID(((Seller*)loginedUser)->getRegisteredRoomList()->at(i))->printRoomInfo();
			cout << "��������������������������������������" << endl;
			cout << "��     �� ���� ���� ��û�� ���     ��" << endl;
			cout << "��������������������������������������" << endl;
			//���� ��û�� ��� ���
			for (size_t k = 0; k < rooms.size(); k++)
			{
				if (rooms.at(k)->getRoomName() == getRoomByID(((Seller*)loginedUser)->getRegisteredRoomList()->at(i))->getRoomName())
				{
					for (size_t j = 0; j < getRoomByID(((Seller*)loginedUser)->getRegisteredRoomList()->at(i))->getUsersRequestToBuyList()->size(); j++)
					{
						cout << "�� "<< rooms.at(k)->getUsersRequestToBuyList()->at(j) << endl ;
					}
				}
			}
			cout << "��������������������������������������" << endl;
			cout << "�� ���� �����Ͻðڽ��ϱ�?" << endl;
			cout << "1. ��" << endl;
			cout << "2. �ƴϿ�" << endl;
			cout << "��������������������������������������" << endl;
			int choice2; cin >> choice2;
			switch (choice2)
			{
			case 1: // �� ����
				for (size_t k = 0; k < users.size(); k++)
				{
					if (users.at(k)->getUserType() == 1)
					{
						//�˻� ��Ͽ��� ����
						for (size_t j = 0; j < ((Buyer*)users.at(k))->getRecentlySearched()->size(); j++)
						{
							if (((Buyer*)users.at(k))->getRecentlySearched()->at(j) == choice)
								((Buyer*)users.at(k))->getRecentlySearched()->erase(((Buyer*)users.at(k))->getRecentlySearched()->begin()+j);
						}

						//���� ��û �������� ����
						for (size_t l = 0; l < ((Buyer*)users.at(k))->getRoomsRequestToBuy()->size(); l++)
						{
							if ((((Buyer*)users.at(k))->getRoomsRequestToBuy()->at(l) == choice))
								((Buyer*)users.at(k))->getRoomsRequestToBuy()->erase(((Buyer*)users.at(k))->getRoomsRequestToBuy()->begin() + l);
						}
					}
				}

				//�Ǹ����� �Ǹ����� �� ��Ͽ��� ����
				((Seller*)loginedUser)->getRegisteredRoomList()->erase(((Seller*)loginedUser)->getRegisteredRoomList()->begin() + i);

				//��ü �� ��Ͽ��� ����
				for (size_t j = 0; j < rooms.size(); j++)
				{
					if (rooms.at(j)->getRoomID() == choice)
					{
						roomAtWhere = j;
					}
				}
				rooms.erase(rooms.begin() + roomAtWhere);

				cout << "���������� �����Ǿ����ϴ�." << endl;
				return;
				break;
			case 2: // ���� ���
				return;
				break;
			default: // �߸��� �Է� ���� ó��
				if (cin.fail() || rightChoice == false)
				{
					cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					return;
				}
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				return;
				break;
			}
			break;
		}
	}

	//�߸��� �Է� ���� ó��
	if (cin.fail() || rightChoice == false)
	{
		cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}	
}

int App::RecusiveBinSearch(int nArr[], int nBegin, int nEnd, int nTarget)
{
	int nMid = 0;
	if (nBegin > nEnd)
	{
		return -1;  //Ż�� ���� �� Ž�� ����
	}
	nMid = (nBegin + nEnd) / 2;

	if (nTarget < nMid)
	{
		return RecusiveBinSearch(nArr, nBegin, nMid - 1, nTarget);
	}
	else if (nTarget > nMid)
	{
		return RecusiveBinSearch(nArr, nMid + 1, nEnd, nTarget);
	}
	else if (nMid == nTarget)
	{
		return nMid;            //ã��
	}

	return 0;
}

