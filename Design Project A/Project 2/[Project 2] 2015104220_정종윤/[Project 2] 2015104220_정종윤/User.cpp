#include "User.h"


User::User()
{
}

User::~User()
{
}

bool Client::send(MailDelivery& md)
{
	Mail* Temp; // ���� ��
	vector<User*>* TempUser; // ���� ����
	cout << "��������������������������������������" << endl;
	cout << "1. ���� ������" << endl;
	cout << "2. ���� ������" << endl;
	cout << "0. ������" << endl;
	cout << "��������������������������������������" << endl;
	int choice, index; cin >> choice;	
	string name2, address;

	bool find = false;
	switch (choice)
	{
	case 1: // ���� ���� ��
		Temp = new Letter(); // ���� �� = ����
		Temp->setMailType(0); // �Ӽ��� ������
		Temp->setSenderId(this->getName()); // ���� ���
		Temp->setSenderAddr(this->getAddress()); // ���� ��� �ּ�
		cout << "������ �޴� ����� �̸��� �Է����ּ���. : "; cin >> name2;
		TempUser = md.getpointerOfUsers();
		for (int i = 0; i < TempUser->size(); i++) // ���� ���ڸ�ŭ �ݺ�
		{
			if (TempUser->at(i)->getUserType() == 0) // ������ Clinet�� ����
			{
				if (name == name2) // �ڱ��ڽſ��� ���� �� ����ó��
				{
					cout << "Error : �ڱ� �ڽſ��� ���� �� �����ϴ�." << endl;
					return 0;
				}
				if (((Client*)TempUser->at(i))->getName() == name2) // ���� ����� ã�� ���
				{
					Temp->setReceiverId(name2);
					find = true; // ã������ Ȯ��
					index = i;
					break;
				}
			}
		}
		if (find == false) // ���� ����� ã�� ������ �� ����ó��
		{
			cout << "Error : ���� �̸��Դϴ�." << endl;
			return 0;
		}
		find = false;
		cout << "������ �޴� ����� �ּҸ� �Է����ּ���. : ";
		getline(cin, address);
		getline(cin, address);
		TempUser = md.getpointerOfUsers();
					
		if (((Client*)TempUser->at(index))->getAddress() == address) // �Ʊ� �̸� �Է��� ����� �ּҿ� �Է��� �ּҰ� ��ġ�� ���
		{
			Temp->setReceiverAddr(address);
			find = true; // ã������ Ȯ��
		}		
		if (find == false) // �ּҰ� �߸��Էµ� ��� ����ó��
		{
			cout << "Error : �ּҸ� �߸� �Է��ϼ̽��ϴ�." << endl;
			return 0;
		}
		
		md.clientSendMail(this,Temp); // md���� ���� ���ͷ� ���� ����

		for (int i = 0; i < 36; i++)
		{
			if (TempUser->at(i)->getUserType() == 0) // ���� Ÿ���� ���� ����
			{
				if (((Client*)TempUser->at(i))->getAddress() == address)
				{
					cout << "��ۺ�� " << ((Letter*)Temp)->calculateCost(md.getTotalDistance(md.getMailCenterIdByAddress(((Client*)TempUser)->getAddress()), md.getMailCenterIdByAddress(address))) << "�� �Դϴ�." << endl;
					sendMailList.push_back(Temp); // ���� ���� ����Ʈ�� �߰�
					cout << "���������� �߼۵Ǿ����ϴ�." << endl;
					break;
				}
			}
		}
		break;

	case 2: // ���� ���� ��
		Temp = new Package(); // ������ = ����
		Temp->setMailType(1); // �Ӽ��� ������
		Temp->setSenderId(this->getName()); // ���� ���
		Temp->setSenderAddr(this->getAddress()); // �޴� ���
		cout << "������ �޴� ����� �̸��� �Է����ּ���. : "; cin >> name2;
		TempUser = md.getpointerOfUsers();
		for (int i = 0; i < TempUser->size(); i++)
		{
			if (TempUser->at(i)->getUserType() == 0)
			{
				if (name == name2) // �ڱ� �ڽſ��� ���� �� ����ó��
				{
					cout << "Error : �ڱ� �ڽſ��� ���� �� �����ϴ�." << endl;
					return 0;
				}
				if (((Client*)TempUser->at(i))->getName() == name2) // ã���� ��
				{
					Temp->setReceiverId(name2);
					find = true;
					index = i;
					break;
				}
			}
		}
		if (find == false) // �̸� ã�� ������ �� ����ó��
		{
			cout << "Error : ���� �̸��Դϴ�." << endl;
			return 0;
		}
		find = false;
		cout << "������ �޴� ����� �ּҸ� �Է����ּ���. : ";
		getline(cin, address);
		getline(cin, address);
		TempUser = md.getpointerOfUsers();

		if (((Client*)TempUser->at(index))->getAddress() == address) // ã���� ��
		{
			Temp->setReceiverAddr(address);
			find = true;
		}
		if (find == false) // �ּ� �߸� �Է����� �� ����ó��
		{
			cout << "Error : �ּҸ� �߸� �Է��ϼ̽��ϴ�." << endl;
			return 0;
		}

		int weight;
		cout << "������ ���Ը� �Է����ּ���. : ";
		cin >> weight;
		if (weight <= 0 || cin.fail()) // ���Կ� ������ ���ڰ� ���� �� ����ó��
		{
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return 0;
		}
		((Package*)Temp)->setWeight(weight); // ���� ����
		md.clientSendMail(this, Temp);

		for (int i = 0; i < 36; i++)
		{
			if (TempUser->at(i)->getUserType() == 0)
			{
				if (((Client*)TempUser->at(i))->getAddress() == address)
				{
					cout << "��ۺ�� " << ((Package*)Temp)->calculateCost(md.getTotalDistance(md.getMailCenterIdByAddress(((Client*)TempUser)->getAddress()), md.getMailCenterIdByAddress(address))) << "�� �Դϴ�." << endl;
					sendMailList.push_back(Temp);
					cout << "���������� �߼۵Ǿ����ϴ�." << endl;
					break;
				}
			}
		}
		break;

	case 0:
		break;

	default: // �߸��� �Է� ����ó��
		if (cin.fail())
		{
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return 0;
			break;
		}
		cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
		break;
	}
	
	return 0;
}

bool Client::receive(MailDelivery& md)
{
	vector<Mail*>* receivedMailList = getReceivedMail(); // ���� ���� ����Ʈ
	if (receivedMailList->size() == 0) // ���� ���� ����Ʈ�� 0�϶�
	{
		cout << "Error : ������ ������ �����ϴ�." << endl;
		return 0;
	}
	
	for (int i = 0; i < receivedMailList->size(); i++)
	{
		
		cout << endl << "���������������� ���� ��������������" << endl;

		receivedMailList->at(i)->printData();
		cout << endl;
	}
	receivedMailList->clear(); // ���� �� ����ϰ� ����
	return 0;
}

bool Manager::send(MailDelivery& md)
{
	md.managerSendMail(currentCityName); // md�� ���� ����
	return 0;
}

bool Manager::receive(MailDelivery& md)
{
	md.managerReceiveMail(currentCityName);	 // md�� ���� ����
	return 0;
}

void Client::printSendedMail()
{
	if (sendMailList.size() == 0) // ���� ���� ����Ʈ�� 0�϶� ����ó��
	{
		cout << "Error : ���� ������ �����ϴ�." << endl;
		return;
	}

	cout << endl << "���������������� ���� ��������������" << endl;

	for (int i = 0; i < sendMailList.size(); i++)
	{
		sendMailList.at(i)->printData();
	}
}

Client::Client()
{
}

Client::Client(int _UserType, string _Id, string _Password, string _Name, string _Address)
{
	userType = _UserType;
	id = _Id;
	password = _Password;
	name = _Name;
	address = _Address;
}

void Client::setClient(int _UserType, string _Id, string _Password, string _Name, string _Address)
{
	userType = _UserType;
	id = _Id;
	password = _Password;
	name = _Name;
	address = _Address;
}

Manager::Manager()
{

}

Manager::Manager(int _UserType, string _Id, string _Password)
{
	userType = _UserType;
	id = _Id;
	password = _Password;
}

void Manager::setManager(int _UserType, string _Id, string _Password)
{
	userType = _UserType;
	id = _Id;
	password = _Password;
}

void User::setUserType(int _UserType){ userType = _UserType; }
void User::setId(string _Id){ id = _Id; }
void User::setPassword(string _Password){ password = _Password; }
int User::getUserType(){ return userType; }
string User::getId(){ return id; }
string User::getPassword(){ return password; }
void Client::setName(string _Name){}
void Client::setAddress(string _Address){}
string Client::getName(){ return name; }
string Client::getAddress(){ return address; }
void Manager::setCurrentCityName(string _CurrentCityName){ currentCityName = _CurrentCityName; }
string Manager::getCurrentCityName(){ return currentCityName; }