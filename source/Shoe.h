#ifndef SHOE_H
#define SHOE_H

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setprecision;
using std::setw;

#include "Cards.h"
#include "Card.h"

namespace Bj
{
    class Shoe
    {
    public:
        Shoe(int aDecks, int aPer = 4, int aDiff = 10, int aExtra = 3) 
        : mDecks(aDecks)
        , mPer(aPer)
        , mDiff(aDiff)
        , mExtra(aExtra)
        , mSize((aDiff + aExtra) * aPer * aDecks)
        , mRemaining(aDiff + 1, aDecks * aPer)
        {
            mRemaining[mDiff] *= (mExtra + 1);
            mRemaining[0] = 0;
        }

        int Remain(int aValue) const
        {
            return mRemaining.at(aValue);
        }

        bool Empty() const
        {
            return mSize == 0;
        }

        int Size() const
        {
            return mSize;
        }

        double Odds(int aValue) const
        {
            return double(Remain(aValue)) / Size();
        }

        Card Pop(int aValue)
        {
            Card card(aValue, TOdds(Remain(aValue), Size()));
            --mRemaining.at(aValue);
            --mSize;
            if (mSize < -1)
                exit(1);
            return card;
        }

        void Push(const Card& aCard)
        {
            ++mRemaining.at(aCard.mValue);
            ++mSize;
        }

        void Print() const
        {
            unsigned int i(0);
            for (i = 1; i < mRemaining.size(); ++i)
            {
                cout << setw(7) << i;
            }
            cout << endl;
            for (i = 1; i < mRemaining.size(); ++i)
            {
                cout << setw(7) << Remain(i);
            }
            cout << endl;
            cout << setprecision(3);
            for (i = 1; i < mRemaining.size(); ++i)
            {
                cout << setw(7) << Odds(i);
            }
            cout << endl;
        }

        int Range() const
        {
            return int(mRemaining.size()) - 1;
        }


    private:
        int mDecks;
        int mPer;
        int mDiff;
        int mExtra;
        int mSize;
        vector<int> mRemaining;

        Shoe(const Shoe&);
        Shoe& operator=(const Shoe&);
    };
}

#endif 