#include <iostream>
#include <windows.h>
using namespace std;
class cards {
    int* _mass;
public:
    cards() { 
        _mass = new int[52];
        for (size_t i = 0; i < 52; i++)
        {
            _mass[i] = 2;
            if (i > 3)
                _mass[i] = 3;
            if (i > 7)
                _mass[i] = 4;
            if (i > 11)
                _mass[i] = 5;
            if (i > 15)
                _mass[i] = 6;
            if (i > 19)
                _mass[i] = 7;
            if (i > 23)
                _mass[i] = 8;
            if (i > 27)
                _mass[i] = 9;
            if (i > 31)
                _mass[i] = 10;
            if (i > 47)
                _mass[i] = 11;
        }
    }
    ~cards() {
        delete _mass;
    }
    void full() {
        for (size_t i = 0; i < 52; i++)
        {
            _mass[i] = 2;
            if (i > 3)
                _mass[i] = 3;
            if (i > 7)
                _mass[i] = 4;
            if (i > 11)
                _mass[i] = 5;
            if (i > 15)
                _mass[i] = 6;
            if (i > 19)
                _mass[i] = 7;
            if (i > 23)
                _mass[i] = 8;
            if (i > 27)
                _mass[i] = 9;
            if (i > 31)
                _mass[i] = 10;
            if (i > 47)
                _mass[i] = 11;
        }
    }
    void print() {
        for (size_t i = 0; i < 52; i++)
        {
            cout << _mass[i] << " ";
        }
        cout << endl;
    }
    int getcard() {
        srand(time(NULL));
        int index = rand() % 52;
        int temp;
        while (1)
        {
            if (_mass[index] == 0)
            {
                index = rand() % 52;
                continue;
            }
            else
            {
                temp = _mass[index];
                break;
            }
        }
        _mass[index] = 0;
        return temp;
    }
};

class player {
    int* _Hand;
    int _cash;
    static int _PlayerSize;
public:
    player(int cash) {
        _cash = cash;
        _Hand = nullptr;
        _PlayerSize = 0;
    }
    ~player() {
        delete[] _Hand;
    }
    player& PlayerMove(cards& obj) {
        srand(time(NULL));
        Sleep(1000);
        cout << "Игрок получает карту" << endl;
        if (_PlayerSize > 0)
        {
            int* temp = new int[_PlayerSize];
            for (size_t i = 0; i < _PlayerSize; i++)
            {
                temp[i] = _Hand[i];
            }
            delete[]_Hand;
            _PlayerSize++;
            _Hand = new int[_PlayerSize];
            for (size_t i = 0; i < _PlayerSize-1; i++)
            {
                _Hand[i] = temp[i];
            }
            _Hand[_PlayerSize -1] = obj.getcard();
        }
        else
        {
            _PlayerSize++;
            _Hand = new int[_PlayerSize];
            _Hand[0] = obj.getcard();
        }
        return*this;
    }
    void printHand() {
        cout << "Рука игрока: ";
        for (size_t i = 0; i < _PlayerSize; i++)
        {
            cout<< _Hand[i]<<" ";
        }
        cout << endl;
    }
    void setHand(int* Hand) { _Hand=Hand; }
    void setPlayerSize(static int PlayerSize) { _PlayerSize = PlayerSize; }
    int* getHand() { return _Hand; }
    static int getPlayerSize() { return _PlayerSize; }
    void setCash(int cash) { _cash = cash; }
    int getCash() { return _cash; }
};
int player::_PlayerSize{ 0 };

class dealer {
    int* _DealerHand;
    static int _DealerSize;
public:
    dealer() {
        _DealerHand = nullptr;
    }
    ~dealer() {
        delete[] _DealerHand;
    }
    dealer& DealerMove(cards& obj) {
        srand(time(NULL));
        Sleep(1000);
        cout << "Дилер получает карту" << endl;
        if (_DealerSize > 0)
        {
            int* temp = new int[_DealerSize];
            for (size_t i = 0; i < _DealerSize; i++)
            {
                temp[i] = _DealerHand[i];
            }
            delete[]_DealerHand;
            _DealerSize++;
            _DealerHand = new int[_DealerSize];
            for (size_t i = 0; i < _DealerSize-1; i++)
            {
                _DealerHand[i] = temp[i];
            }
            _DealerHand[_DealerSize - 1] = obj.getcard();
        }
        else
        {
            _DealerSize++;
            _DealerHand = new int[_DealerSize];
            _DealerHand[0] = obj.getcard();
        }
        return*this;
    }
    void printHand() {
        cout << "Рука дилера: ";
        for (size_t i = 0; i < _DealerSize; i++)
        {
            cout << _DealerHand[i] << " ";
        }
        cout << endl;
    }
    void setHand(int* dealHand) { _DealerHand = dealHand; }
    void setDEalerSize(static int DealerSize) { _DealerSize = DealerSize; }
    int* getHand() { return _DealerHand; }
    static int getDealerSize() { return _DealerSize; }
};
int dealer::_DealerSize{ 0 };

void EndRound(cards& allcard, player& player, dealer& dealer) {
    cout << "Конец раунда" << endl<<endl;
    player.setHand(nullptr);
    player.setPlayerSize(0);
    dealer.setHand(nullptr);
    dealer.setDEalerSize(0);
    allcard.full();
}

bool Options1(cards& allcard, player& player, dealer& dealer) {
    int summa1{ 0 },summa2{0};
    bool flag = 0;
    for (size_t i = 0; i < player.getPlayerSize(); i++)
    {
        summa1 += player.getHand()[i];
    }
    for (size_t i = 0; i < dealer.getDealerSize(); i++)
    {
        summa2 += dealer.getHand()[i];
    }
    if (summa1 == 21 && summa2==21) {
        dealer.printHand();
        cout << "Ничья" << endl;
        cout << "Очков: " << player.getCash() << endl;
        EndRound(allcard, player, dealer);
        flag = 1;
        return flag;
    }
    if (summa1 == 21 && summa2!=21) {
        dealer.printHand();
        cout << "Игрок выйграл раунд. +100 очков" << endl;
        player.setCash(player.getCash() + 100);
        cout << "Очков: " << player.getCash()<<endl;
        EndRound(allcard, player, dealer);
        flag = 1;
        return flag;
    }
    if (summa1 != 21 && summa2 == 21) {
        dealer.printHand();
        cout << "Игрок проиграл раунд. -100 очков" << endl;
        player.setCash(player.getCash() - 100);
        cout << "Очков: " << player.getCash() << endl;
        EndRound(allcard, player, dealer);
        flag = 1;
        return flag;
    }
    else 
    {
        flag = 0;
        return flag;
    }
}
void Options2(cards& allcard, player& player, dealer& dealer) {
    int summa1{ 0 }, summa2{ 0 };
    for (size_t i = 0; i < player.getPlayerSize(); i++)
    {
        summa1 += player.getHand()[i];
    }
    for (size_t i = 0; i < dealer.getDealerSize(); i++)
    {
        summa2 += dealer.getHand()[i];
    }
    if (summa1 == summa2) {
        dealer.printHand();
        cout << "Ничья" << endl;
        cout << "Очков: " << player.getCash() << endl;
        EndRound(allcard, player, dealer);
        return;
    }
    if (summa1 == 21 || summa2 > 21) {
        dealer.printHand();
        cout << "Игрок выйграл раунд. +100 очков" << endl;
        player.setCash(player.getCash() + 100);
        cout << "Очков: " << player.getCash() << endl;
        EndRound(allcard, player, dealer);
        return;
    }
    if (summa2 == 21 || summa1 > 21) {
        dealer.printHand();
        cout << "Игрок проиграл раунд. -100 очков" << endl;
        player.setCash(player.getCash() - 100);
        cout << "Очков: " << player.getCash() << endl;
        EndRound(allcard, player, dealer);
        return;
    }
    if (summa1 > summa2) {
        dealer.printHand();
        cout << "Игрок выйграл раунд. +100 очков" << endl;
        player.setCash(player.getCash() + 100);
        cout << "Очков: " << player.getCash() << endl;
        EndRound(allcard, player, dealer);
        return;
    }
    if (summa1 < summa2) {
        dealer.printHand();
        cout << "Игрок проиграл раунд. -100 очков" << endl;
        player.setCash(player.getCash() - 100);
        cout << "Очков: " << player.getCash() << endl;
        EndRound(allcard, player, dealer);
        return;
    }
    if ((summa1 >21 && summa2 >21) && summa1>summa2) {
        dealer.printHand();
        cout << "Игрок проиграл раунд. -100 очков" << endl;
        player.setCash(player.getCash() - 100);
        cout << "Очков: " << player.getCash() << endl;
        EndRound(allcard, player, dealer);
        return;
    }
    if ((summa1 > 21 && summa2 > 21) && summa1 < summa2) {
        dealer.printHand();
        cout << "Игрок выйграл раунд. +100 очков" << endl;
        player.setCash(player.getCash() + 100);
        cout << "Очков: " << player.getCash() << endl;
        EndRound(allcard, player, dealer);
        return;
    }
}

void DealerChoise(cards& allcard, player& player, dealer& dealer) {
    int summa1{ 0 }, summa2{ 0 };
    for (size_t i = 0; i < dealer.getDealerSize(); i++)
    {
        summa1 += dealer.getHand()[i];
    }
    for (size_t i = 0; i < player.getPlayerSize(); i++)
    {
        summa2 += player.getHand()[i];
    }
    while (summa1 < 17)
    {
        summa1 = 0;
        for (size_t i = 0; i < dealer.getDealerSize(); i++)
        {
            summa1 += dealer.getHand()[i];
        }
        if (summa1 < 17)
        {
            dealer.DealerMove(allcard);
        }
        else
            continue;
    }
    while (1)
    {
        if (summa2 <= 21 && summa2 > summa1)
        {
            summa1 = 0;
            for (size_t i = 0; i < dealer.getDealerSize(); i++)
            {
                summa1 += dealer.getHand()[i];
            }
            if (summa1 > 21)
                return;
            dealer.DealerMove(allcard);
        }
        else
            return;
    }
    return;
}
void PlayerChoise(cards& allcard, player& player, dealer& dealer) {
    char choise;
    int summa1{ 0 };
    do
    {
        summa1= 0 ;
        for (size_t i = 0; i < player.getPlayerSize(); i++)
        {
            summa1 += player.getHand()[i];
        }
        if (summa1 > 21)
            return;
        cout << "добавить еще одну карту?\n введите Y-если да, N-если нет" << endl;
        cin >> choise;
        if (choise == 'y') {
            player.PlayerMove(allcard);
            player.printHand();
        }
        if (choise == 'n') {
            if (summa1 < 17)
                cout << "сумма очков на картах должна быть минимум 17\n";
            else
            {
                player.printHand();
                return;
            }
        }
    } while (1);
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    cards AllCards;
    player player1(1000);
    dealer dealer1;

    while (player1.getCash()==0 || player1.getCash()<3000)
    {

        Sleep(1000);
        player1.PlayerMove(AllCards);
        player1.PlayerMove(AllCards);
        dealer1.DealerMove(AllCards);
        dealer1.DealerMove(AllCards);
        player1.printHand();
        if (Options1(AllCards, player1, dealer1) == 1)
            continue;
        PlayerChoise(AllCards, player1, dealer1);
        DealerChoise(AllCards, player1, dealer1);
        Options2(AllCards, player1, dealer1);
    }
    if (player1.getCash() == 0)
        cout << "Вы прогиграли все свои деньги.";
    else
        cout<< "Вы выйграли слишком много. Вас попросили удалиться.";
}
