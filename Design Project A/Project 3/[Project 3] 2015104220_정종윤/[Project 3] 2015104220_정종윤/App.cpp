#include "App.h"

//기본 생성자
App::App()
{
	system("title 2015104220 정종윤 - 방 추천 프로그램");
	loadUserFile();
	loadRoomFile();
	//필터 초기 값 설정
	isFilter1Skipped = true;
	isFilter2Skipped = true;
	isFilter3Skipped = true;
}

//소멸자
App::~App()
{
	
}


//유저 데이터 파일 로드
void App::loadUserFile()
{
	ifstream loadUser("User.txt");
	int _UserType, _X, _Y, _Search, _SearchID, _Request, _RequestID, _Rooms, _RoomID;
	string _ID, _PW;
	User* CurUser;

	while (loadUser >> _UserType)
	{
		//유저가 판매자일 경우
		if (_UserType == 0)
		{
			CurUser = new Seller;
			loadUser >> _ID >> _PW;
			CurUser->setId(_ID);
			CurUser->setPassword(_PW);
			CurUser->setUserType(0);

			loadUser >> _Rooms;
			//등록한 방 설정
			for (int i = 0; i < _Rooms; i++)
			{
				loadUser >> _RoomID;
				((Seller*)CurUser)->getRegisteredRoomList()->push_back(_RoomID); 
			}
		}
		//유저가 구매자인 경우
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
			//최근 검색 내역 추가
			for (int i = 0; i < _Search; i++)
			{
				loadUser >> _SearchID;
				(((Buyer*)CurUser)->getRecentlySearched())->push_back(_SearchID);
			}
			//구매 요청 내역 추가
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

//방 데이터 파일 로드
void App::loadRoomFile()
{
	ifstream loadRoom("Room.txt");
	int _RoomType, _RoomID, _X, _Y, _Request, _Deposit, _Monthly, _Cost;
	string _RoomName, _RequestID, _SellerID;
	Room* CurRoom;

	while (loadRoom >> _RoomType)
	{
		//방이 월세인 경우
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
			//구매 요청 아이디 추가
			for (int i = 0; i < _Request; i++)
			{
				loadRoom >> _RequestID;
				(((RoomForRent*)CurRoom)->getUsersRequestToBuyList())->push_back(_RequestID);
			}
			loadRoom >> _Deposit >> _Monthly;
			((RoomForRent*)CurRoom)->setDeposit(_Deposit);
			((RoomForRent*)CurRoom)->setMonthlyPay(_Monthly);
		}

		//방이 매매인 경우
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
			//구매 요청 아이디 추가
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
	//정렬
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


//파일 저장
void App::saveFiles()
{
	ofstream saveUser("User.txt");
	ofstream saveRoom("Room.txt");

	//유저 파일 저장
	for (size_t i = 0; i < users.size(); i++)
	{
		int userType = users.at(i)->getUserType();
		string ID = users.at(i)->getId();
		string PW = users.at(i)->getPassword();
		saveUser << userType << "\t" << ID << "\t" << PW << "\t";
		//유저가 구매자인 경우
		if (userType == 1)
		{
			int X = ((Buyer*)users.at(i))->getXCoord();
			int Y = ((Buyer*)users.at(i))->getYCoord();
			saveUser << X << "\t" << Y << "\t";
			int Recently = ((Buyer*)users.at(i))->getRecentlySearched()->size();
			saveUser << Recently << "\t";
			//최근 검색 내역 저장
			for (int j = 0; j < Recently; j++)
			{
				saveUser << ((Buyer*)users.at(i))->getRecentlySearched()->at(j) << "\t";
			}
			int Request = ((Buyer*)users.at(i))->getRoomsRequestToBuy()->size();
			saveUser << Request << "\t";
			//구매 요청 내역 저장
			for (int j = 0; j < Request; j++)
			{
				saveUser << ((Buyer*)users.at(i))->getRoomsRequestToBuy()->at(j) << "\t";
			}
			saveUser << "\n";
		}
		//유저가 판매자인 경우
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

	//방 파일 저장
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
		//방이 월세인 경우
		if (RoomType == 0)
		{
			int Deposit = ((RoomForRent*)rooms.at(i))->getDeposit();
			int Monthly = ((RoomForRent*)rooms.at(i))->getMonthlyPay();
			saveRoom << Deposit << "\t" << Monthly << "\t";
		}
		//방이 매매인 경우
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


//프로그램 시행
void App::run()
{
	printMenu();
}

//필터 1 반환 함수
vector<Room*> App::getFilter1Result()
{
	return resultOfFilter1;
}

//필터 2 반환 함수
vector<Room*> App::getFilter2Result()
{
	return resultOfFilter2;
}

//필터 3 반환 함수
vector<Room*> App::getFilter3Result()
{
	return resultOfFilter3;
}

//메뉴 출력
void App::printMenu()
{
//	system("pause");
//	system("cls");
	while (1)
	{
		cout << "┌─────────────────┐" << endl;
		cout << "│┌───────────────┐│" << endl;
		cout << "││≪     방 추천 프로그램     ≫││" << endl;
		cout << "│└───────────────┘│" << endl;
		cout << "└─────────────────┘" << endl;
		cout << "1. 구매자 로그인" << endl;
		cout << "2. 판매자 로그인" << endl;
		cout << "0. 종료" << endl;
		cout << "───────────────────" << endl;
		int choice;
		string ID, PW;
		cin >> choice;
		switch (choice)
		{
		case 1: // 구매자 로그인
			if (loginedUser != NULL)
			{
				cout << "Error : 이미 로그인 된 상태입니다." << endl;
				cout << "기존에 로그인 된 계정으로 접속합니다." << endl;
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
			cout << "ID를 입력하세요. : "; cin >> ID;
			cout << "비밀번호를 입력하세요. : "; cin >> PW;
			cout << "───────────────────" << endl;
			login(1, ID, PW);
			break;
		case 2: // 판매자 로그인
			if (loginedUser != NULL)
			{
				cout << "Error : 이미 로그인 된 상태입니다." << endl;
				cout << "기존에 로그인 된 계정으로 접속합니다." << endl;
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
			cout << "ID를 입력하세요. : "; cin >> ID;
			cout << "비밀번호를 입력하세요. : "; cin >> PW;
			cout << "───────────────────" << endl;
			login(0, ID, PW);
			break;
		case 0: // 종료
			saveFiles();
			exit(100);
			return;
			break;
		default: // 잘못된 입력 예외 처리
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

void App::printBuyerMenu()
{
	int choice;	
	while (1)
	{
		cout << "┌─────────────────┐" << endl;
		cout << "│           구매자 메뉴            │" << endl;
		cout << "└─────────────────┘" << endl;
		loginedUser->printUserInfo();
		cout << "───────────────────" << endl;
		cout << "1. 검색 필터 설정" << endl;
		cout << "2. 방 검색" << endl;
		cout << "3. 최근 검색 목록 출력" << endl;
		cout << "4. 구매 요청 목록 출력" << endl;
		cout << "0. 로그아웃" << endl;
		cout << "───────────────────" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: // 검색 필터 설정
			setFilters();
			break;
		case 2: // 방 검색
			searchRooms();
			break;
		case 3: // 최근 검색 목록 출력
			printRecentlySearcedRoomsOfLoginedUser();
			break;
		case 4: // 구매 요청 목록 출력
			printRequestToBuyList();
			break;
		case 0: // 로그아웃
			resultOfFilter1.clear(); isFilter1Skipped = true;
			resultOfFilter2.clear(); isFilter2Skipped = true;
			resultOfFilter3.clear(); isFilter3Skipped = true;
			logout() ? cout << "성공적으로 로그아웃 하였습니다." << endl : cout << "Error : 로그인 한 계정이 없습니다." << endl;
			printMenu();
			break;
		default: // 잘못된 입력 예외 처리
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

void App:: printSellerMenu()
{
	int choice;
	while (1)
	{
		cout << "┌─────────────────┐" << endl;
		cout << "│           판매자 메뉴            │" << endl;
		cout << "└─────────────────┘" << endl;
		loginedUser->printUserInfo();
		cout << "───────────────────" << endl;
		cout << " 등록한 방 목록 : " << endl;
		if (((Seller*)loginedUser)->getRegisteredRoomList()->size() != 0)
		{
			for (size_t i = 0; i < ((Seller*)loginedUser)->getRegisteredRoomList()->size(); i++)
			{
				cout << "† " << getRoomByID((((Seller*)loginedUser)->getRegisteredRoomList()->at(i)))->getRoomName() << endl; /**/
			}
		}
		else
		{
			cout << "현재 등록된 방이 없습니다." << endl;
		}
		cout << "───────────────────" << endl;
		cout << "1. 방 등록" << endl;
		cout << "2. 방 삭제" << endl;
		cout << "0. 로그아웃" << endl;
		cout << "───────────────────" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: // 방 등록
			registerNewRoom();
			break;
		case 2: // 방 삭제
			deleteRoom();
			break;
		case 0: // 로그아웃
			logout() ? cout << "성공적으로 로그아웃 하였습니다." << endl : cout << "Error : 로그인 한 계정이 없습니다." << endl;
			printMenu();
			break;
		default: // 잘못된 입력 예외 처리
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

//로그인
bool App::login(int userType, string userID, string password)
{
	size_t i = 0;
	while (i < users.size())
	{
		// 아이디가 일치하는지 확인
		if (users.at(i)->getId() == userID) 
		{
			// 비밀번호가 일치하는지 확인
			if (users.at(i)->getPassword() == password)
			{
				// 판매자 모드로 로그인 시도
				if (userType == 0) 
				{
					// 로그인을 시도한 사람이 판매자 일 경우
					if (users.at(i)->getUserType() == 0) 
					{
						cout << "성공적으로 로그인 되었습니다." << endl;
						loginedUser = (users[i]); // loginedUser에 현재 유저의 주소값을 저장
						printSellerMenu();
						return 1;
					}
					else
					{
						cout << "권한이 없습니다." << endl;
						return NULL;
					}
				}
				// 구매자 모드로 로그인 시도
				if (userType == 1) 
				{
					// 로그인을 시도한 계정이 구매자일 경우
					if (users.at(i)->getUserType() == 1) 
					{
						cout << "성공적으로 로그인 되었습니다." << endl;
						loginedUser = (users[i]); // loginedUser에 현재 유저의 주소값을 저장
						resultOfFilter3 = rooms;
						printBuyerMenu();
						return 1;
					}
					else
					{
						cout << "권한이 없습니다." << endl;
						return 0;
					}
				}
			}
			// 비밀번호가 일치하지 않을 경우 예외 처리
			else 
			{
				cout << "Error : 비밀번호가 일치하지 않습니다." << endl;
				return 0;
				break;
			}
		}
		i++;
	}
	// 아이디가 일치하지 않을 경우 예외 처리
	cout << "Error : 리스트에 일치하는 ID가 없습니다." << endl; 
	return 0;
}

//로그아웃
bool App::logout()
{
	if (loginedUser == NULL)
	{
		return false;
	}
	loginedUser = NULL;
	return true;
}

//필터 설정
void App::setFilters()
{
	cout << "┌─────────────────┐" << endl;
	cout << "│             필터 설정            │" << endl;
	cout << "└─────────────────┘" << endl;

	//필터 1 설정
	cout << "검색할 반경을 설정하시겠습니까?" << endl;
	cout << "───────────────────" << endl;
	cout << "1. 예" << endl;
	cout << "2. 아니오" << endl;
	cout << "───────────────────" << endl;
	int choice; cin >> choice;
	switch (choice)
	{
	case 1: // 검색할 반경 설정
		isFilter1Skipped = false;
		cout << "───────────────────" << endl;
		cout << "구매자의 현재 위치는 " << ((Buyer*)loginedUser)->getXCoord() << " , " << ((Buyer*)loginedUser)->getYCoord() << " 입니다." << endl;
		cout << "검색할 반경을 입력해 주십시오. : ";
		cin >> searchAreaRadius;
		if (cin.fail() || searchAreaRadius < 0)
		{
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "───────────────────" << endl;
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
	case 2: // 필터 1 생략
		isFilter1Skipped = true;
		resultOfFilter1.clear();
		for (size_t i = 0; i < rooms.size(); i++)
		{
			resultOfFilter1.push_back(rooms.at(i));
		}
		break;
	default: // 잘못된 입력 예외 처리
		if (cin.fail())
		{
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "Error : 올바르지 않은 선택입니다." << endl;
		return;
	}

	//필터 2 설정
	cout << "가격 범위를 설정하시겠습니까?" << endl;
	cout << "───────────────────" << endl;
	cout << "1. 예" << endl;
	cout << "2. 아니오" << endl;
	cout << "───────────────────" << endl;
	int choice2; cin >> choice2;	
	switch (choice2)
	{
	case 1: // 가격 범위 설정
		isFilter2Skipped = false;
		cout << "───────────────────" << endl;
		cout << "월세의 최대값, 최소값을 입력하십시오. : "; cin >> maxMonthlyPay >> minMonthlyPay;
		if (cin.fail() || maxMonthlyPay < minMonthlyPay)
		{
			cout << "Error : 올바르지 않은 선택이거나 월세 입력이 잘못되었습니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "보증금의 최대값, 최소값을 입력하십시오. : "; cin >> maxDeposit >> minDeposit;
		if (cin.fail() || maxDeposit < minDeposit)
		{
			cout << "Error : 올바르지 않은 선택이거나 보증금 입력이 잘못되었습니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "매매가의 최대값, 최소값을 입력하십시오. : "; cin >> maxCost >> minCost;
		if (cin.fail() || maxCost < minCost)
		{
			cout << "Error : 올바르지 않은 선택이거나 매매가 입력이 잘못되었습니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		resultOfFilter2.clear();
		for (size_t i = 0; i < resultOfFilter1.size(); i++)
		{
			//월세
			if (resultOfFilter1.at(i)->getRoomType() == 0)
			{
				if (((RoomForRent*)resultOfFilter1.at(i))->getDeposit() > minDeposit && ((RoomForRent*)resultOfFilter1.at(i))->getDeposit() < maxDeposit &&
					((RoomForRent*)resultOfFilter1.at(i))->getMonthlyPay() > minMonthlyPay && ((RoomForRent*)resultOfFilter1.at(i))->getMonthlyPay() < maxMonthlyPay)
				{
					resultOfFilter2.push_back(resultOfFilter1.at(i));

				}
			}

			//매매
			if (resultOfFilter1.at(i)->getRoomType() == 1)
			{
				if (((RoomForSale*)resultOfFilter1.at(i))->getCost() > minCost && ((RoomForSale*)resultOfFilter1.at(i))->getCost() < maxCost)
				{
					resultOfFilter2.push_back(resultOfFilter1.at(i));
				}
			}
		}
		break;
	case 2: // 필터 2 생략
		isFilter2Skipped = true;
		resultOfFilter2.clear();
		for (size_t i = 0; i < resultOfFilter1.size(); i++)
		{
			resultOfFilter2.push_back(resultOfFilter1.at(i));
		}
		break;
	default: // 잘못된 입력 예외 처리
		if (cin.fail())
		{
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "Error : 올바르지 않은 선택입니다." << endl;
		return;
		break;
	}

	//필터 3 설정
	cout << "검색어를 설정하시겠습니까?" << endl;
	cout << "───────────────────" << endl;
	cout << "1. 예" << endl;
	cout << "2. 아니오" << endl;
	cout << "───────────────────" << endl;
	int choice3; cin >> choice3; string getName;
	switch (choice3)
	{
	case 1: // 검색어 설정
		isFilter3Skipped = false;
		cout << "───────────────────" << endl;
		cout << "검색어를 입력하십시오. : "; cin >> searchKey;
		resultOfFilter3.clear();
		for (size_t i = 0; i < resultOfFilter2.size(); i++)
		{
			if (resultOfFilter2.at(i)->getRoomName().find(searchKey) != string::npos)
			{
				resultOfFilter3.push_back(resultOfFilter2.at(i));
			}
		}
		break;
	case 2: // 필터 3 생략
		isFilter3Skipped = true;
		resultOfFilter3.clear();
		for (size_t i = 0; i < resultOfFilter2.size(); i++)
		{
			resultOfFilter3.push_back(resultOfFilter2.at(i));
		}
		break;
	default: // 잘못된 입력 예외 처리
		if (cin.fail())
		{
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "Error : 올바르지 않은 선택입니다." << endl;
		return;
		break;
	}

	cout << "필터 설정이 완료되었습니다." << endl;

	return;
}

//최근 검색 내역 출력
void App::printRecentlySearcedRoomsOfLoginedUser()
{
	cout << "┌─────────────────┐" << endl;
	cout << "│          최근 검색 내역          │" << endl;
	cout << "└─────────────────┘" << endl;
	// 검색 내역이 존재하지 않을 경우 예외 처리
	if (((Buyer*)loginedUser)->getRecentlySearched()->size() == 0)
	{
		cout << "Error : 최근 검색 내역이 존재하지 않습니다." << endl;
		return;
	}

	// 이진 탐색 시작
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

//ID를 이용해 Room 반환
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

//현재 필터들의 설정을 출력
bool App::printFilterConditions()
{
	cout << "┌─────────────────┐" << endl;
	cout << "│        현재  설정된  필터        │" << endl;
	cout << "└─────────────────┘" << endl;
	cout << "검색 반경   : ";
	isFilter1Skipped == true ? cout << "상관 없음" << endl : cout << "설정됨" << endl;
	cout << "계약 조건   : ";
	isFilter2Skipped == true ? cout << "상관 없음" << endl : cout << "설정됨" << endl;
	cout << "특정 검색어 : ";
	isFilter3Skipped == true ? cout << "상관 없음" << endl : cout << "설정됨" << endl;
	return 0;
}

//구매 요청 내역 출력
void App::printRequestToBuyList()
{
	cout << "┌─────────────────┐" << endl;
	cout << "│          구매 요청 내역          │" << endl;
	cout << "└─────────────────┘" << endl;
	//구매 요청 내역이 존재하지 않을 경우 예외 처리
	if (((Buyer*)loginedUser)->getRoomsRequestToBuy()->size() == 0)
	{
		cout << "Error : 구매 요청 내역이 존재하지 않습니다." << endl;
		return;
	}

	//구매 요청 내역 출력
	for (size_t i = 0; i < ((Buyer*)loginedUser)->getRoomsRequestToBuy()->size(); i++)
	{
		getRoomByID(((Buyer*)loginedUser)->getRoomsRequestToBuy()->at(i))->printRoomInfo();
	}
}

//방 검색
void App::searchRooms()
{
	cout << "┌─────────────────┐" << endl;
	cout << "│             검색 결과            │" << endl;
	cout << "└─────────────────┘" << endl;
	//마지막 필터의 결과가 없을 경우 예외 처리
	if (resultOfFilter3.size() == 0)
	{
		cout << "Error : 검색 결과가 없습니다." << endl;
		return;
	}
	cout << "총 " << resultOfFilter3.size() << " 건의 검색 결과가 있습니다." << endl;
	printFilterConditions();
	cout << "───────────────────" << endl;
	for (size_t i = 0; i < resultOfFilter3.size(); i++)
	{
		cout << i + 1 << ". " << resultOfFilter3.at(i)->getRoomName() << endl;
	}
	cout << "───────────────────" << endl;
	cout << "번호를 입력하여 자세한 정보를 확인합니다. : ";  
	size_t choice; cin >> choice;
	
	//잘못된 입력 예외 처리
	if (cin.fail() || choice > resultOfFilter3.size() || choice <= 0)
	{
		cout << "Error : 올바르지 않은 선택입니다." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	
	resultOfFilter3.at(--choice)->printRoomInfo();
	//최근 검색 내역에 추가
	
	((Buyer*)loginedUser)->getRecentlySearched()->push_back((resultOfFilter3.at(choice)->getRoomID()));
	//최근 검색 내역이 5보다 클 경우 오래된 것부터 삭제
	if (((Buyer*)loginedUser)->getRecentlySearched()->size() > 5)
	{
		((Buyer*)loginedUser)->getRecentlySearched()->erase(((Buyer*)loginedUser)->getRecentlySearched()->begin());
	}

	cout << "┌─────────────────┐" << endl;
	cout << "│             구매 요청            │" << endl;
	cout << "└─────────────────┘" << endl;
	cout << "1. 예" << endl;
	cout << "2. 아니오" << endl;
	cout << "───────────────────" << endl;
	int choice2; cin >> choice2;
	switch (choice2)
	{
	case 1:
		//이미 구매요청한 방을 다시 구매하려고 하는 경우 예외 처리
		for (size_t i = 0; i < (((Buyer*)loginedUser)->getRoomsRequestToBuy())->size(); i++)
		{
			if ((((Buyer*)loginedUser)->getRoomsRequestToBuy())->at(i) == resultOfFilter3.at(choice)->getRoomID())
			{
				cout << "Error : 이미 구매 요청한 방입니다." << endl;
				return;
			}
		}
		//구매자의 구매 요청 내역에 추가
		(((Buyer*)loginedUser)->getRoomsRequestToBuy())->push_back(resultOfFilter3.at(choice)->getRoomID());
		//방의 구매 요청 리스트에 추가
		resultOfFilter3.at(choice)->getUsersRequestToBuyList()->push_back(loginedUser->getId());
		cout << "구매 요청이 완료되었습니다." << endl;
		break;
	case 2:
		return;
		break;
	default:
		//잘못된 입력 예외 처리
		if (cin.fail())
		{
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "Error : 올바르지 않은 선택입니다." << endl;
		break;
	}
}

// 방 등록
void App::registerNewRoom()
{
	cout << "┌─────────────────┐" << endl;
	cout << "│              방 등록             │" << endl;
	cout << "└─────────────────┘" << endl;
	cout << "새 방을 등록하시겠습니까?" << endl;
	cout << "1. 예" << endl;
	cout << "2. 아니오" << endl;
	cout << "───────────────────" << endl;
	int choice, choice2; cin >> choice;

	int Biggest = rooms.at(rooms.size()-1)->getRoomID();
	Room* NewRoom;
	string RoomName;
	int RoomX, RoomY, RoomD, RoomM, RoomC;

	switch (choice)
	{
	case 1: // 새 방 등록
		cout << "방 종류를 선택해 주세요." << endl;
		cout << "1. 월세" << endl;
		cout << "2. 매매" << endl;
		cout << "───────────────────" << endl;
		cin >> choice2;
		switch (choice2)
		{
		case 1: // 월세 등록
			cout << "방 이름을 입력해주세요. : "; cin >> RoomName;
			cout << "방의 X좌표를 입력해주세요. : "; cin >> RoomX;
			//잘못된 입력 예외 처리
			if (cin.fail() || RoomX < 0)
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "방의 Y좌표를 입력해주세요. : "; cin >> RoomY;
			//잘못된 입력 예외 처리
			if (cin.fail() || RoomY < 0)
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "방의 보증금(만원)을 입력해주세요. : "; cin >> RoomD;
			//잘못된 입력 예외 처리
			if (cin.fail() || RoomD < 0)
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "방의 월세(만원)을 입력해주세요. : "; cin >> RoomM;
			//잘못된 입력 예외 처리
			if (cin.fail() || RoomM < 0)
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
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
			//전체 방 목록에 추가
			rooms.push_back(NewRoom);
			//등록한 방 목록에 추가
			((Seller*)loginedUser)->getRegisteredRoomList()->push_back(Biggest+1);
			cout << "성공적으로 등록되었습니다." << endl;
			break;
		case 2: // 매매 등록
			cout << "방 이름을 입력해주세요. : "; cin >> RoomName;
			cout << "방의 X좌표를 입력해주세요. : "; cin >> RoomX;
			//잘못된 입력 예외 처리
			if (cin.fail() || RoomX < 0)
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "방의 Y좌표를 입력해주세요. : "; cin >> RoomY;
			//잘못된 입력 예외 처리
			if (cin.fail() || RoomY < 0)
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "방의 매매가(만원)를 입력해주세요. : "; cin >> RoomC;
			//잘못된 입력 예외 처리
			if (cin.fail() || RoomC < 0)
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
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
			//전체 방 목록에 추가
			rooms.push_back(NewRoom);
			//등록한 방 목록에 추가
			((Seller*)loginedUser)->getRegisteredRoomList()->push_back(Biggest + 1);
			cout << "성공적으로 등록되었습니다." << endl;
			break;
		default: // 잘못된 입력 예외 처리
			if (cin.fail())
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			return;
			break;
		}
		break;
	case 2: // 방 만들기 취소
		return;
		break;
	default: // 잘못된 입력 예외 처리
		if (cin.fail())
		{
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			return;
		}
		cout << "Error : 올바르지 않은 선택입니다." << endl;
		return;
		break;
	}
}

//방 삭제
void App::deleteRoom()
{
	cout << "┌─────────────────┐" << endl;
	cout << "│              방 삭제             │" << endl;
	cout << "└─────────────────┘" << endl;
	//삭제할 방이 없을 경우 예외 처리
	if (((Seller*)loginedUser)->getRegisteredRoomList()->size() == 0)
	{
		cout << "Error : 삭제할 방이 존재하지 않습니다." << endl;
		return;
	}
	cout << "현재 등록된 방은 총 " << ((Seller*)loginedUser)->getRegisteredRoomList()->size() <<" 개 입니다."<< endl;
	
	cout << "┌──┬───────────────" << endl;
	cout << "│ ID │             방 이름          " << endl;
	cout << "├──┼───────────────" << endl;
	if (((Seller*)loginedUser)->getRegisteredRoomList()->size() != 0)
	{
		for (size_t i = 0; i < ((Seller*)loginedUser)->getRegisteredRoomList()->size(); i++)
		{			   
			cout << "│ " << setw(2) << getRoomByID((((Seller*)loginedUser)->getRegisteredRoomList()->at(i)))->getRoomID() << " │" << " " << getRoomByID((((Seller*)loginedUser)->getRegisteredRoomList()->at(i)))->getRoomName() << endl; /**/
		}
	}
	cout << "└──┴───────────────" << endl;
	cout << "삭제하실 방의 ID를 입력해주십시오." << endl;
	cout << "───────────────────" << endl;
	int choice, roomAtWhere; cin >> choice;

	//삭제할 방이 있는지 검사
	bool rightChoice = false;

	for (size_t i = 0; i < ((Seller*)loginedUser)->getRegisteredRoomList()->size(); i++)
	{
		//삭제할 방을 찾을 경우
		if (getRoomByID(((Seller*)loginedUser)->getRegisteredRoomList()->at(i))->getRoomID() == choice)
		{
			rightChoice = true;
			//방의 정보 출력
			getRoomByID(((Seller*)loginedUser)->getRegisteredRoomList()->at(i))->printRoomInfo();
			cout << "┌─────────────────┐" << endl;
			cout << "│     이 방을 구매 요청한 사람     │" << endl;
			cout << "└─────────────────┘" << endl;
			//구매 요청한 사람 출력
			for (size_t k = 0; k < rooms.size(); k++)
			{
				if (rooms.at(k)->getRoomName() == getRoomByID(((Seller*)loginedUser)->getRegisteredRoomList()->at(i))->getRoomName())
				{
					for (size_t j = 0; j < getRoomByID(((Seller*)loginedUser)->getRegisteredRoomList()->at(i))->getUsersRequestToBuyList()->size(); j++)
					{
						cout << "† "<< rooms.at(k)->getUsersRequestToBuyList()->at(j) << endl ;
					}
				}
			}
			cout << "───────────────────" << endl;
			cout << "이 방을 삭제하시겠습니까?" << endl;
			cout << "1. 예" << endl;
			cout << "2. 아니오" << endl;
			cout << "───────────────────" << endl;
			int choice2; cin >> choice2;
			switch (choice2)
			{
			case 1: // 방 삭제
				for (size_t k = 0; k < users.size(); k++)
				{
					if (users.at(k)->getUserType() == 1)
					{
						//검색 목록에서 삭제
						for (size_t j = 0; j < ((Buyer*)users.at(k))->getRecentlySearched()->size(); j++)
						{
							if (((Buyer*)users.at(k))->getRecentlySearched()->at(j) == choice)
								((Buyer*)users.at(k))->getRecentlySearched()->erase(((Buyer*)users.at(k))->getRecentlySearched()->begin()+j);
						}

						//구매 요청 내역에서 삭제
						for (size_t l = 0; l < ((Buyer*)users.at(k))->getRoomsRequestToBuy()->size(); l++)
						{
							if ((((Buyer*)users.at(k))->getRoomsRequestToBuy()->at(l) == choice))
								((Buyer*)users.at(k))->getRoomsRequestToBuy()->erase(((Buyer*)users.at(k))->getRoomsRequestToBuy()->begin() + l);
						}
					}
				}

				//판매자의 판매중인 방 목록에서 삭제
				((Seller*)loginedUser)->getRegisteredRoomList()->erase(((Seller*)loginedUser)->getRegisteredRoomList()->begin() + i);

				//전체 방 목록에서 삭제
				for (size_t j = 0; j < rooms.size(); j++)
				{
					if (rooms.at(j)->getRoomID() == choice)
					{
						roomAtWhere = j;
					}
				}
				rooms.erase(rooms.begin() + roomAtWhere);

				cout << "성공적으로 삭제되었습니다." << endl;
				return;
				break;
			case 2: // 삭제 취소
				return;
				break;
			default: // 잘못된 입력 예외 처리
				if (cin.fail() || rightChoice == false)
				{
					cout << "Error : 올바르지 않은 선택입니다." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					return;
				}
				cout << "Error : 올바르지 않은 선택입니다." << endl;
				return;
				break;
			}
			break;
		}
	}

	//잘못된 입력 예외 처리
	if (cin.fail() || rightChoice == false)
	{
		cout << "Error : 올바르지 않은 선택입니다." << endl;
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
		return -1;  //탈출 조건 및 탐색 실패
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
		return nMid;            //찾음
	}

	return 0;
}

