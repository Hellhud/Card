#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>

class Card
{
public:
    enum Rank {
        Ace = 1, Two, Three, Four, Five, Six, Seven,
        Eight, Nine, Ten, Jack, Queen, King, RankEnd
    };
    enum Suit { Spades, Hearts, Diamonds, Clubs, SuitEnd };

    Card(Rank rank, Suit suit)
        : m_rank(rank), m_suit(suit)
    {
        if (rank < Ace || rank > King) {
            std::stringstream errMsg;
            errMsg << "Card(): rank '" << rank << "' out of range";
            throw std::range_error(errMsg.str());
        }
        else if (suit < Spades || suit > Clubs) {
            std::stringstream errMsg;
            errMsg << "Card(): suit '" << suit << "' out of range";
            throw std::range_error(errMsg.str());
        }
    }

    Rank rank() const { return m_rank; }
    Suit suit() const { return m_suit; }
    std::string str() const
    {
        std::stringstream ret;
        ret << sRanks[m_rank] << " of " << sSuits[m_suit];
        return ret.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card)
    {
        return os << card.cRanks[card.m_rank] << card.cSuits[card.m_suit];
        //  return os << card.sRanks[card.m_rank] << " of " << card.sSuits[card.m_suit];
    }

private:
    static const std::string sRanks[14];
    static const std::string sSuits[4];
    static const char cRanks[14];
    static const char cSuits[4];
    Rank m_rank;
    Suit m_suit;
};

const std::string Card::sRanks[14] = {
    "\0", "Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
    "Eight", "Nine", "Ten", "Jack", "Queen", "King"
};
const std::string Card::sSuits[4] = { "Spades", "Hearts", "Diamonds", "Clubs" };
const char Card::cRanks[14] = {
    '\0', 'A', '2', '3', '4', '5', '6', '7',
    '8', '9', 'T', 'J', 'Q', 'K'
};
const char Card::cSuits[4] = { 's', 'h', 'd', 'c' };


Card::Rank& operator++(Card::Rank& rank)
{
    return rank = Card::Rank(static_cast<int>(rank) + 1);
}

Card::Suit& operator++(Card::Suit& suit)
{
    return suit = Card::Suit(static_cast<int>(suit) + 1);
}


int main()
{
    std::vector<Card> deck;
    for (Card::Suit suit = Card::Spades; suit < Card::SuitEnd; ++suit)
        for (Card::Rank rank = Card::Ace; rank < Card::RankEnd; ++rank) {
            deck.push_back(Card(rank, suit));
            std::cout << deck.back() << "\n";
        }

    return 0;
}