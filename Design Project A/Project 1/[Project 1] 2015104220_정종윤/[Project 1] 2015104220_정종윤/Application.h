#define MAX 20

#include "User.h"
#include "loan.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Application
{
public:
	Application(); // ���� �ε� �� ���� �ʱ�ȭ
	~Application();
public:
	void run(); // ���� ȭ�� ���
private:
	void printMenu(); // �⺻ �޴� ���
	void print_logined_user_transanctions(); // �α��ε� ������ �ŷ� ���� ���
	void print_logined_user_loans(); // �α��ε� ������ ���� ���
	void print_deposit_withdraw_menu(); // ��,��� �޴� ���
	void print_send_money_menu(); // �۱� �޴� ���
	void print_loan_menu(); // ���� �޴� ���
	void print_repayment_menu(); // ��ȯ �޴� ���

	User* login(int user_id, string Password); // ����� �α���
	void logout(); // ����� �α׾ƿ�

	bool sendMoney(int _toAccount, int _amount); // �۱�
	bool deposit(int _amount); // �Ա� 
	bool withdraw(int _amount); // ��� 
	bool loan_money(int _amount, int _repayment_priod_month); // ����
	bool repayment(); // ����� ��ȯ

	void load_user_file(); // ����� ������ �ҷ���
	void load_transaction_log_file(); // �ŷ� ���� ������ �ҷ���
	void load_loan_list_file(); // ���� ����Ʈ ������ �ҷ���
	void saveFiles(); // ���� ����

private:
	User users[MAX];
	int userCount = 0;

	transaction transactions[5 * MAX];
	int transactionCount = 0;

	loan loans[100];
	int loanCount = 0;
	
	User* loginedUser;
};

