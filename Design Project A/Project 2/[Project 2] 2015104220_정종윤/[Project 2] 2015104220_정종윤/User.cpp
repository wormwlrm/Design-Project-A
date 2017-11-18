#include "User.h"


User::User()
{
}

User::~User()
{
}

bool Client::send(MailDelivery& md)
{
	Mail* Temp; // 보낼 것
	vector<User*>* TempUser; // 현재 유저
	cout << "───────────────────" << endl;
	cout << "1. 편지 보내기" << endl;
	cout << "2. 소포 보내기" << endl;
	cout << "0. 나가기" << endl;
	cout << "───────────────────" << endl;
	int choice, index; cin >> choice;	
	string name2, address;

	bool find = false;
	switch (choice)
	{
	case 1: // 편지 보낼 때
		Temp = new Letter(); // 보낼 것 = 편지
		Temp->setMailType(0); // 속성을 편지로
		Temp->setSenderId(this->getName()); // 보낸 사람
		Temp->setSenderAddr(this->getAddress()); // 보낸 사람 주소
		cout << "우편물을 받는 사람의 이름을 입력해주세요. : "; cin >> name2;
		TempUser = md.getpointerOfUsers();
		for (int i = 0; i < TempUser->size(); i++) // 유저 숫자만큼 반복
		{
			if (TempUser->at(i)->getUserType() == 0) // 유저가 Clinet일 때만
			{
				if (name == name2) // 자기자신에게 보낼 때 예외처리
				{
					cout << "Error : 자기 자신에게 보낼 수 없습니다." << endl;
					return 0;
				}
				if (((Client*)TempUser->at(i))->getName() == name2) // 보낼 사람을 찾을 경우
				{
					Temp->setReceiverId(name2);
					find = true; // 찾았음을 확인
					index = i;
					break;
				}
			}
		}
		if (find == false) // 보낼 사람을 찾지 못했을 때 예외처리
		{
			cout << "Error : 없는 이름입니다." << endl;
			return 0;
		}
		find = false;
		cout << "우편물을 받는 사람의 주소를 입력해주세요. : ";
		getline(cin, address);
		getline(cin, address);
		TempUser = md.getpointerOfUsers();
					
		if (((Client*)TempUser->at(index))->getAddress() == address) // 아까 이름 입력한 사람의 주소와 입력한 주소가 일치할 경우
		{
			Temp->setReceiverAddr(address);
			find = true; // 찾았음을 확인
		}		
		if (find == false) // 주소가 잘못입력된 경우 예외처리
		{
			cout << "Error : 주소를 잘못 입력하셨습니다." << endl;
			return 0;
		}
		
		md.clientSendMail(this,Temp); // md에서 메일 센터로 메일 보냄

		for (int i = 0; i < 36; i++)
		{
			if (TempUser->at(i)->getUserType() == 0) // 유저 타입이 고객일 때만
			{
				if (((Client*)TempUser->at(i))->getAddress() == address)
				{
					cout << "배송비는 " << ((Letter*)Temp)->calculateCost(md.getTotalDistance(md.getMailCenterIdByAddress(((Client*)TempUser)->getAddress()), md.getMailCenterIdByAddress(address))) << "원 입니다." << endl;
					sendMailList.push_back(Temp); // 보낸 메일 리스트에 추가
					cout << "성공적으로 발송되었습니다." << endl;
					break;
				}
			}
		}
		break;

	case 2: // 소포 보낼 때
		Temp = new Package(); // 보낼것 = 소포
		Temp->setMailType(1); // 속성을 소포로
		Temp->setSenderId(this->getName()); // 보낸 사람
		Temp->setSenderAddr(this->getAddress()); // 받는 사람
		cout << "우편물을 받는 사람의 이름을 입력해주세요. : "; cin >> name2;
		TempUser = md.getpointerOfUsers();
		for (int i = 0; i < TempUser->size(); i++)
		{
			if (TempUser->at(i)->getUserType() == 0)
			{
				if (name == name2) // 자기 자신에게 보낼 떄 예외처리
				{
					cout << "Error : 자기 자신에게 보낼 수 없습니다." << endl;
					return 0;
				}
				if (((Client*)TempUser->at(i))->getName() == name2) // 찾았을 때
				{
					Temp->setReceiverId(name2);
					find = true;
					index = i;
					break;
				}
			}
		}
		if (find == false) // 이름 찾지 못했을 때 예외처리
		{
			cout << "Error : 없는 이름입니다." << endl;
			return 0;
		}
		find = false;
		cout << "우편물을 받는 사람의 주소를 입력해주세요. : ";
		getline(cin, address);
		getline(cin, address);
		TempUser = md.getpointerOfUsers();

		if (((Client*)TempUser->at(index))->getAddress() == address) // 찾았을 때
		{
			Temp->setReceiverAddr(address);
			find = true;
		}
		if (find == false) // 주소 잘못 입력했을 때 예외처리
		{
			cout << "Error : 주소를 잘못 입력하셨습니다." << endl;
			return 0;
		}

		int weight;
		cout << "소포의 무게를 입력해주세요. : ";
		cin >> weight;
		if (weight <= 0 || cin.fail()) // 무게에 음수나 문자가 들어갔을 때 예외처리
		{
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return 0;
		}
		((Package*)Temp)->setWeight(weight); // 무게 설정
		md.clientSendMail(this, Temp);

		for (int i = 0; i < 36; i++)
		{
			if (TempUser->at(i)->getUserType() == 0)
			{
				if (((Client*)TempUser->at(i))->getAddress() == address)
				{
					cout << "배송비는 " << ((Package*)Temp)->calculateCost(md.getTotalDistance(md.getMailCenterIdByAddress(((Client*)TempUser)->getAddress()), md.getMailCenterIdByAddress(address))) << "원 입니다." << endl;
					sendMailList.push_back(Temp);
					cout << "성공적으로 발송되었습니다." << endl;
					break;
				}
			}
		}
		break;

	case 0:
		break;

	default: // 잘못된 입력 예외처리
		if (cin.fail())
		{
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return 0;
			break;
		}
		cout << "Error : 올바르지 않은 선택입니다." << endl;
		break;
	}
	
	return 0;
}

bool Client::receive(MailDelivery& md)
{
	vector<Mail*>* receivedMailList = getReceivedMail(); // 받은 우편물 리스트
	if (receivedMailList->size() == 0) // 받은 우편물 리스트가 0일때
	{
		cout << "Error : 도착한 우편물이 없습니다." << endl;
		return 0;
	}
	
	for (int i = 0; i < receivedMailList->size(); i++)
	{
		
		cout << endl << "──────받은 우편물 ───────" << endl;

		receivedMailList->at(i)->printData();
		cout << endl;
	}
	receivedMailList->clear(); // 받은 후 출력하고 삭제
	return 0;
}

bool Manager::send(MailDelivery& md)
{
	md.managerSendMail(currentCityName); // md로 우편물 전송
	return 0;
}

bool Manager::receive(MailDelivery& md)
{
	md.managerReceiveMail(currentCityName);	 // md로 우편물 받음
	return 0;
}

void Client::printSendedMail()
{
	if (sendMailList.size() == 0) // 보낸 우편물 리스트가 0일때 예외처리
	{
		cout << "Error : 보낸 우편물이 없습니다." << endl;
		return;
	}

	cout << endl << "──────보낸 우편물 ───────" << endl;

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