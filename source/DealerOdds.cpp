#include "DealerOdds.h"
#include "cards.h"
Bj::DealerOdds::DealerOdds()
: mCheck(1.0)
, m17(0.0)
, m18(0.0)
, m19(0.0)
, m20(0.0)
, m21(0.0)
, mBust(0.0)
, mNatural(0.0)
, mCards(0.0)
{
}


Bj::DealerOdds::DealerOdds(const DealerOdds& aObj)
: mCheck(aObj.mCheck)
, m17(aObj.m17)
, m18(aObj.m18)
, m19(aObj.m19)
, m20(aObj.m20)
, m21(aObj.m21)
, mBust(aObj.mBust)
, mNatural(aObj.mNatural)
, mCards(aObj.mCards)
{
}

Bj::DealerOdds Bj::DealerOdds::operator=(const DealerOdds& aObj)
{
	if (this != &aObj)
	{
	mCheck=aObj.mCheck;
	m17=aObj.m17;
	m18=aObj.m18;
	m19=aObj.m19;
	m20=aObj.m20;
	m21=aObj.m21;
	mBust=aObj.mBust;
	mNatural=aObj.mNatural;
	mCards=aObj.mCards;
	}
	return *this;
}


Bj::DealerOdds::~DealerOdds()
{
}

void Bj::DealerOdds::check() const
{
    if (!IsClose(m17 + m18 + m19 + m20 + m21 + mBust, mCheck))
    {
        cout << "Odds didn't add up to " << mCheck << endl;
        exit(1);
    }

}

void Bj::DealerOdds::scale(const double aScale, const bool aCards)
{
    m17 *= aScale;
    m18 *= aScale;
    m19 *= aScale;
    m20 *= aScale;
    m21 *= aScale;
    mBust *= aScale;
    mNatural *= aScale;
    mCheck *= aScale;
	if (aCards)
		mCards *= aScale;
}

void Bj::DealerOdds::print(const unsigned aPrecision) const
{
    cout << " 17: " << setprecision(aPrecision) << m17;
    cout << " 18: " << setprecision(aPrecision) << m18;
    cout << " 19: " << setprecision(aPrecision) << m19;
    cout << " 20: " << setprecision(aPrecision) << m20;
    cout << " 21: " << setprecision(aPrecision) << m21;
    cout << " Bust: " << setprecision(aPrecision) << mBust;
    cout << " Nat: " <<  setprecision(aPrecision) << mNatural;
    cout << " Cards: " <<  setprecision(aPrecision) << mCards << endl;
    check();
}

Bj::DealerOdds& Bj::operator+=(Bj::DealerOdds& aLhs, const Bj::DealerOdds& aRhs)
    {
        aLhs.m17 += aRhs.m17;
        aLhs.m18 += aRhs.m18;
        aLhs.m19 += aRhs.m19;
        aLhs.m20 += aRhs.m20;
        aLhs.m21 += aRhs.m21;
        aLhs.mBust += aRhs.mBust;
        aLhs.mNatural += aRhs.mNatural;
        aLhs.mCheck += aRhs.mCheck;
        aLhs.mCards += aRhs.mCards;
        return aLhs;
    }
	Bj::DealerOdds& Bj::operator*=(Bj::DealerOdds& aLhs, const double aRhs)
    {
        aLhs.scale(aRhs);
        return aLhs;
    }
	Bj::DealerOdds Bj::operator*(const Bj::DealerOdds& aLhs, const double aRhs)
    {
        Bj::DealerOdds res(aLhs);
        res *= aRhs;
        return res;
    }