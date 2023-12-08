#ifndef DEALER_ODDS_H
#define DEALER_ODDS_H

namespace Bj
{
    class DealerOdds
    {
    public:
        DealerOdds();
        DealerOdds(const DealerOdds& aObj);
        DealerOdds operator=(const DealerOdds& aObj);
        ~DealerOdds();

        double mCheck;
        double m17;
        double m18;
        double m19;
        double m20;
        double m21;
        double mBust;
        double mNatural;
        double mCards;
        void check() const;
        void scale(const double aScale, const bool aCards = true);
        void print(const unsigned aPrecision = 5) const;
    };
    DealerOdds& operator+=(DealerOdds& aLhs, const DealerOdds& aRhs);
    DealerOdds& operator*=(DealerOdds& aLhs, const double aRhs);
    DealerOdds operator*(const DealerOdds& aLhs, const double aRhs);
}

#endif