
#include <iostream> 
#include <locale.h> 
#include <string>
#include "BankAccount.h"
#include "Tran.cpp"

using namespace std;

void showMenu() {
    cout << "\t\t\t\t1 - Пополнить баланс" << endl;
    cout << "\t\t\t\t2 - Снять со счёта" << endl;
    cout << "\t\t\t\t3 - Показать баланс" << endl;
    cout << "\t\t\t\t4 - Откатить последнюю операцию" << endl;
    cout << "\t\t\t\t5 - История операций" << endl;
    cout << "\t\t\t\t6 - Посмотреть механизм транзакций" << endl;
    cout << "\t\t\t\t0 - Выйти из этого круга ада" << endl;
    cout << "\t\t\t>> ";
}


int main()
{
    string log = "";
    Tran<BankAccount> tr;
    setlocale(LC_ALL, "Russian");
    int choice = 0;
    double sum;
    tr.Show(false);
    cout << "\t\t\t\t\tThe bank!" << endl;
    do {
        showMenu();
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            cout << "\tВведите сумму для пополнения: ";
            cin >> sum;
            if (tr.Begin()) {
                tr->replenish(sum);
                log += "\nПополнение: " + to_string(sum);
            }
            else {
                cout << "Ошибка в создании транзакции!";
                log += "\nПополнение: Ошибка в создании транзакции!";
            }
            break;
        case 2:
            cout << "\tВведите сумму для снятия: ";
            cin >> sum;
            if (tr.Begin()) {
                tr->withdraw(sum);
                log += "\nСнятие: " + to_string(sum);
            }
            else {
                cout << "Ошибка в создании транзакции!";
                log += "\nCнятие: Ошибка в создании транзакции!";
            }

            if (tr->get() < 0) {
                cout << "\tОбнаружен отрицательный баланс(недостаточно средств для снятия), проводится откат операци..." << endl;
                log += "\nCнятие: отрицательный баланс - откат назад";
                tr.Back();
            }

            break;
        case 3:
            cout << "\t\t";
            tr->show();
            break;
        case 4:
            tr.Back();
            log += " - откат назад";
            break;
        case 5:
            cout << endl << log << endl << endl;
            break;
        case 6:
            tr.Show(true);
            break;
        default:
            break;
        }
    } while (choice != 0);

    tr.Show(true);
    return 0;
}
