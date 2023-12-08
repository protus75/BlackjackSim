#ifndef HAND_H
#define HAND_H

#include <algorithm>

#include "cards.h"
#include "Card.h"

namespace Bj
{
    class Hand
    {
    public:
        Hand() : mBet(1.0), mFreq(0.0)
        {
        }

        bool Push(const Card& aCard)
        {
            mHand.push_back(aCard);
            return aCard.mOdds.first > 0;
        }

        Card Pop()
        {
            Card card(mHand.back());
            mHand.pop_back();
            return card;
        }

        double Odds(int index) const
        {
            double o = mHand.at(index).Odds();
            return o;
        }

        double Odds() const
        {
            double o = 1.0;
            for (unsigned i = 2; i < mHand.size(); ++i)
                o *= mHand.at(i).Odds();

            return o * mFreq;
        }

        double Odds2() const
        {
            return mHand.at(0).Odds() * mHand.at(1).Odds();
        }

        int Rank(int index) const
        {
            return mHand.at(index).mValue;
        }

        int Val(int index) const
        {
            return std::min(Rank(index), 10);
        }

        bool IsAce2() const
        {
            return(Rank(0) == 1 || Rank(1) == 1);
        }

        bool IsAce() const
        {
        }

        bool IsBj() const
        {
            return(IsAce2() && (Rank(1) >= 10 || Rank(0) >= 10));
        }

        bool IsPair() const
        {
            /// TODO is 10 J a pair because both 10s?
            return(Rank(0) == Rank(1));
        }

        Kind Kind2() const
        {
            // Consider BJ and anything not a Pair or Soft as Hard
            Kind k = Hard;

            if (IsPair())
            {
                k = Pair;
            }
            else if (IsAce2() && !IsBj())
            {
                k = Soft;
            }

            return k;
        }

        Kind KindH() const
        {
            Kind k = Hard;
            if ((mHand.size() == 2) && IsPair())
            {
                k = Pair;
            }
            else
            {
                int s = 0;
                bool ace = false;
                for (unsigned i = 0; i < mHand.size(); ++i)
                {
                    ace = ace || (Val(i) == 1);
                    s += Val(i);
                }
                if (ace && (s < 11))
                    k = Soft;
            }
            return k;
        }

        int Up() const
        {
            return Val(1);
        }

        int Sum2() const
        {
            int total = Val(0) + Val(1);
            if (IsAce2())
                total += 10;
            return total;
        }

        int Sum() const
        {
            int s = 0;
            bool ace = false;
            for (unsigned i = 0; i < mHand.size(); ++i)
            {
                ace = ace || (Rank(i) == 1);
                s += Val(i);
            }
            if (ace && (s <= 11))
                s += 10;
            return s;
        }

        int Cards() const
        {
            return int(mHand.size());
        }

        Hand(const Hand& obj) : mBet(obj.mBet), mFreq(obj.mFreq), mHand(obj.mHand)
        {
        }

        Hand& operator=(const Hand& obj)
        {
            if (this != &obj)
            {
                mBet = obj.mBet;
                mFreq = obj.mFreq;
                mHand = obj.mHand;
            }
            return *this;
        }

        double mBet;
        double mFreq;
    private:

        vector<Card> mHand;
    };

}

#endif 