#ifndef WLT_H
#define WLT_H

namespace Bj
{
    class DealerOdds;

    class Wlt
    {
    public:
        Wlt();

        Wlt(const double aLoss,
			const double aCards);

		Wlt(const Wlt& aObj);

		Wlt operator=(const Wlt& aObj);

		~Wlt(void);

        explicit Wlt(const DealerOdds& aOdds, 
                     const bool aNatural, 
					 const unsigned aSum,
					 const double aCards,
                     const bool aIgnoreDealerBj);

        double mCheck;
        double mWin;
        double mLoss;
        double mTie;

		double mCards;

        void check() const;
        Wlt& scale(const double aScale, const bool aCards = true);
        void print(const unsigned aPrecision) const;

        double exp() const;

    };

    static Wlt& operator+=(Wlt& aLhs, const Wlt& aRhs)
    {
        aLhs.mLoss += aRhs.mLoss;
        aLhs.mWin += aRhs.mWin;
        aLhs.mTie += aRhs.mTie;
        aLhs.mCheck += aRhs.mCheck;
        aLhs.mCards += aRhs.mCards;
        return aLhs;
    }
    static Wlt& operator*=(Wlt& aLhs, const double aRhs)
    {
        aLhs.scale(aRhs);
        return aLhs;
    }
    static Wlt operator*(const Wlt& aLhs, const double aRhs)
    {
        Wlt res(aLhs);
        res *= aRhs;
        return res;
    }
    static bool operator<(const Wlt& aLhs, const Wlt& aRhs)
    {
        return aLhs.exp() < aRhs.exp();
    }
}

#endif