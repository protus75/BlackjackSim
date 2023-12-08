#ifndef CARD_H
#define CARD_H

#include "Cards.h"

namespace Bj
{
    class Card
    {
    public:
        Card(int aValue) : mValue(aValue)
        {
        }

        Card(int aValue, TOdds aOdds) : mValue(aValue), mOdds(aOdds)
        {
        }

        double Odds() const
        {
            double o = double(mOdds.first) / mOdds.second;
            if (o > 1.0)
                exit(1);
            return o;
        }

        Card(const Card& obj) : mValue(obj.mValue), mOdds(obj.mOdds)
        {
        }

        Card& operator=(const Card& obj)
        {
            if (this != &obj)
            {
                mValue = obj.mValue;
                mOdds.first = obj.mOdds.first;
                mOdds.second = obj.mOdds.second;
            }
            return *this;
        }

        int mValue;
        TOdds mOdds;
    };
}

#endif 