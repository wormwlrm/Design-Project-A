#include "App.h"


App::App()
{
	loadUserFiles(); // User 파일 로드
	loadRouterFiles(); // Router 파일 로드
	loadMailCenterIdFiles(); // MailCenterId 파일 로드
	md.setDBPointers(&users, &mailCenters, router); // md의 멤버 변수를 App의 멤버 변수로 초기화
}

App::~App()
{
}

void App::run()
{
	cout << "┌─────────────────┐" << endl;
	cout << "│┌───────────────┐│" << endl;
	cout << "││≪ 우편물 배송관리 프로그램 ≫││" << endl;
	cout << "│└───────────────┘│" << endl;
	cout << "└─────────────────┘" << endl;
	while (1)
	{
		cout << "───────────────────" << endl;
		cout << "1. 고객 로그인" << endl;
		cout << "2. 관리자 로그인" << endl;
		cout << "0. 종료" << endl;
		cout << "───────────────────" << endl;
		int choice;
		string ID, PW;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "ID를 입력하세요. : "; cin >> ID;
			cout << "비밀번호를 입력하세요. : "; cin >> PW;
			cout << "───────────────────" << endl;
			login(0, ID, PW);
			break;
		case 2:
			cout << "ID를 입력하세요. : "; cin >> ID;
			cout << "비밀번호를 입력하세요. : "; cin >> PW;
			cout << "───────────────────" << endl;
			login(1, ID, PW);
			break;
		case 0:
			exit(100);
			break;
		default:
			if (cin.fail())
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
			cout << "Error : 올바르지 않은 선택입니다." << endl;
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

	while (getline(loadUser, line)) // getline을 이용해 문자 로드
	{
		int _UserType; 
		stringstream get(line);
		string _Id, _Password, _Name, _Address;
		get >> _UserType;
		if (_UserType == 0) // 읽어들인 문자 중 유저타입이 0일 경우, 즉 고객일 경우
		{
			get >> _Id >> _Password >> _Name; // 아이디, 패스워드, 이름 읽어옴
			string _AddressTemp;
			
			get >> _Address;
			_AddressTemp = _Address;
			while (get >> _Address)
			{
				_AddressTemp += " ";
				_AddressTemp += _Address;				
			}
			_Address = _AddressTemp; // 주소는 한 어절 씩 읽어와 합침
			client = new Client(_UserType,_Id,_Password,_Name,_Address); // 새 Clinet 생성
			users.push_back(client); // 유저 벡터 맨 뒤에 추가
		}
		 if (_UserType == 1) // 읽어들인 문자 중 유저타입이 1일 경우, 즉 고객일 경우
		{
			get >> _Id >> _Password;
			manager = new Manager(_UserType, _Id, _Password); // 새 Manager 생성
			users.push_back(manager); // 매니저 벡터 맨 뒤에 추가
		}
	}	
	loadUser.close();

	return 1;
}

bool App::loadRouterFiles()
{
	ifstream loadRouter("Router.txt");
	int number;
	
	router = new int*[12]; // 이차원 동적 배열을 할당

	for (int i = 0; i < 12; i++)
		router[i] = new int[12];
	
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			loadRouter >> number;
			router[i][j] = number; // 데이터 대입
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
	while (getline(loadMailCenterID, line)) // getline 함수 사용
	{
		stringstream get(line);
		int _Id;
		string _CityName;
		get >> _Id >> _CityName; // 아이디와 도시명 받아옴
		mailcenter = new MailCenter(_Id, _CityName); // MailCenter 생성
		mailCenters.push_back(mailcenter); //메일센터 벡터 맨 뒤에 추가
	}

	loadMailCenterID.close();
	return 1;
}

User* App::login(int userType, string user_id, string Password)
{
	int i = 0;
	
	while (i < 36)
	{
		if (users.at(i)->getId() == user_id) // 아이디가 일치하는지 확인
		{
			if (users.at(i)->getPassword() == Password) // 비밀번호가 일치하는지 확인
			{
				if (userType == 0) // Client 모드로 로그인 시도
				{
					if (users.at(i)->getUserType() == 0) // 로그인을 시도한 사람이 Client 일 경우
					{
						cout << "성공적으로 로그인 되었습니다." << endl;
						loginedUser = (users[i]); // loginedUser에 현재 유저의 주소값을 저장
						printClientMenu();
						return loginedUser;
					}
					else
					{
						cout << "권한이 없습니다." << endl;
						return NULL;
					}					
				}	
				if (userType == 1) // Manager 모드로 로그인 시도
				{
					if (users.at(i)->getUserType() == 1) // 로그인을 시도한 계정이 Manager일 경우
					{
						cout << "성공적으로 로그인 되었습니다." << endl;
						loginedUser = (users[i]); // loginedUser에 현재 유저의 주소값을 저장
						printManagerMenu();
						return loginedUser;
					}
					else
					{
						cout << "권한이 없습니다." << endl;
						return NULL;
					}
				}
			}

			else // 비밀번호가 일치하지 않을 경우 예외 처리
			{
				cout << "Error : 비밀번호가 일치하지 않습니다." << endl;
				return NULL;
				break;
			}
		}
		i++;
	}
	cout << "Error : 리스트에 일치하는 ID가 없습니다." << endl; // 아이디가 일치하지 않을 경우 예외 처리
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
		cout << "───────────────────" << endl;
		cout << "사용자 이름 : " << ((Client*)loginedUser)->getName() << endl;
		cout << "주소        : " << ((Client*)loginedUser)->getAddress() << endl;
		cout << "───────────────────" << endl;
		cout << "1. 우편물 보내기" << endl;
		cout << "2. 우편물 받기" << endl;
		cout << "3. 보낸 우편물 목록" << endl;
		cout << "0. 로그아웃" << endl;
		cout << "───────────────────" << endl;
		int choice; cin >> choice;
		switch (choice)
		{
		case 1:
			loginedUser->send(md); // 우편물 보내기
			break;
		case 2:
			loginedUser->receive(md); // 우편물 받기
			break;
		case 3:
			((Client*)loginedUser)->printSendedMail(); // 보낸 우편물 목록
			break;
		case 0:
			logout(); run(); // 로그아웃
			break;
		default:
			if (cin.fail()) // 잘못된 입력시 예외처리
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			break;
		}
	}
}

void App::printManagerMenu()
{
	while (1)
	{
		cout << "관리할 우편집중국의 지역명을 입력해주세요." << endl;
		cout << "0을 입력하시면 이전 메뉴로 돌아갑니다. : ";
		string name;
		cin >> name;
		if (name == "0")  // 이전 메뉴로
		{
			run();
			return;
		}
		for (int i = 0; i < 12; i++)
		{
			if (name == mailCenters.at(i)->getCityName()) // 메일 센터와 일치하는 이름 발견 시
			{
				while (1)
				{
					cout << "───────────────────" << endl;
					((Manager*)loginedUser)->setCurrentCityName(name);
					cout << "현재 관리중인 지역 : " << ((Manager*)loginedUser)->getCurrentCityName() << endl;
					cout << "───────────────────" << endl;
					cout << "1. 우편물 보내기" << endl;
					cout << "2. 우편물 받기" << endl;
					cout << "0. 나가기" << endl;
					cout << "───────────────────" << endl;
					int choice; cin >> choice;
					switch (choice)
					{
					case 1:
						loginedUser->send(md); // 우편물 보내기
						break;
					case 2:
						loginedUser->receive(md); // 우편물 받기
						break;
					case 0:
						printManagerMenu(); // 나가기
						break;
					default: // 잘못된 입력 예외처리
						if (cin.fail())
						{
							cout << "Error : 올바르지 않은 선택입니다." << endl;
							cin.clear();
							cin.ignore(256, '\n');
							break;
						}
						cout << "Error : 올바르지 않은 선택입니다." << endl;
						break;
					}
				}
			}
		}
		cout << "Error : 입력하신 지역명이 존재하지 않습니다."; // 도시 이름 존재하지 않을 시 예외처리

		return;
	}
}