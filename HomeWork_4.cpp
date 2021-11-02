#include <iostream>
#include <string>
#include <vector>
#include "ArrayInt.h"

////// exercise 3

enum ECardSuit { SPADES, CLUBS, DIAMONDS, HEARTS };
enum ECardValue {
    ACE   = 1,
    TWO   = 2,
    THREE = 3,
    FOUR  = 4,
    FIVE  = 5,
    SIX   = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE  = 9,
    TEN   = 10,
    JACK  = 10,
    QUEEN = 10,
    KING  = 10
};
class Card {
    ECardSuit suit;
    ECardValue value;
    bool isCoverUp;
public:
    Card(ECardSuit _suit, ECardValue _value) : suit(_suit), value(_value) {
        isCoverUp = true;
    }

    void flip() {
        isCoverUp = !isCoverUp;
    }
    ECardValue getValue() const {
        return value;
    }
};

class Hand {
protected:
    int sum;
    std::vector<Card*> m_Cards;
public:
    void Add(Card* pCard) {
        m_Cards.push_back(pCard);
    }
    void Clear() {
        m_Cards.clear();
    }
    int GetTotal() {
        bool ace = false;
        if (m_Cards.empty())
        {
            return 0;
        }
        for (size_t i = 0; i < m_Cards.size(); i++)
        {
            sum +=m_Cards[i]->getValue();
        }
        for (size_t i = 0; i < m_Cards.size(); i++)
        {
            if (m_Cards[i]->getValue() == 1)
            {
                ace = 1;
            }
        }
        if (sum <= 11 && ace == 1)
        {
            return sum + 10;
        }
        else
        {
            return sum;
        }
    }
};

class GenericPlayer : public Hand {
protected:
    std::string m_Name;
    int total = GetTotal();
public:
    virtual bool IsHitting() const = 0;
    bool IsBoosted() const {
        if (total > 21)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void Bust() const {
        if (IsBoosted() == true)
        {
            std::cout << "Too Much" << std::endl;
        }
    }
};

class Player : public GenericPlayer {
public:
    virtual bool IsHitting() const {
        if (total < 17)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void Win() const {
        std::cout << "Player Won!" << std::endl;
    }
    void Lose() const {
        std::cout << "Player Lose!" << std::endl;
    }
    void Push() const {
        std::cout << "A zero-sum game!" << std::endl;
    }
};

class House : public GenericPlayer {
public:
    virtual bool IsHitting() const override {
        if (total < 17)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void FlipFirstCard() {
        m_Cards[0]->flip();
    }
};

class Deck : public Hand {
public:
    void Populate() { }
    void Shuffle() { }
    void Deal(Hand& aHand) { }
    void AddltionalCards(GenericPlayer& aGenericPlayer) { }
};

class Game {
    Deck m_Deck;
    House m_House;
    std::vector<Player> m_Players;
public:
    void Play(){}
};

//////

int main()
{
    //// exercise 1

    ArrayInt a;
    a.push_back(5);
    a.push_back(4);
    a.push_back(3);
    a.push_back(2);
    a.push_back(1);
    a.print();
    a.sort();
    a.print();
    a.pop_back();
    a.pop_front();
    a.print();

    //////

    /// exercise 2

    std::vector<int> array{ 1,8,2,3,4,5,6,6,6,1,2,3,8,9};
    int count = 0;
    int different = 0;

    std::vector<int>::iterator it = array.begin();
    std::vector<int>::iterator it2 = array.begin()+1;
    while (it != array.end())
    {
        while (it2 != array.end())
        {
            if (it == it2)
            {
                it2++;
                continue;
            }
            else if (*it != *it2)
            {
                count++;
            }
            else if (*it == *it2) {
                break;
            }
            it2++;
        }
        if (count == array.size()-1)
        {
            different++;
            count = 0;
        }
        count = 0;
        it++;
        it2 = array.begin();
    }
    std::cout << "Various: " << different << std::endl;

    //////
    
    /// exercise 3

    Card c0(SPADES, ACE);
    Card c1(CLUBS, QUEEN);
    Hand h1;
    h1.Add(&c0);
    h1.Add(&c1);
    std::cout << h1.GetTotal() << std::endl;
    h1.Clear();
    std::cout << h1.GetTotal() << std::endl;

    //////
    
    system("pause");
    return 0;
}
