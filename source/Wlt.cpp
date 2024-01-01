#include "Wlt.h"
#include "Cards.h"
#include "DealerOdds.h"


Bj::Wlt::Wlt(void)
: mCheck(0.0)
, mWin(0.0)
, mTie(0.0)
, mLoss(0.0)
, mCards(0.0)
{
}

Bj::Wlt::Wlt(const double aLoss, const double aCards)
: mCheck(aLoss)
, mWin(0.0)
, mTie(0.0)
, mLoss(aLoss)
, mCards(aCards)
{
}

Bj::Wlt::Wlt(const Wlt& aObj)
: mCheck(aObj.mCheck)
, mWin(aObj.mWin)
, mTie(aObj.mTie)
, mLoss(aObj.mLoss)
, mCards(aObj.mCards)
{
}

Bj::Wlt Bj::Wlt::operator=(const Wlt& aRhs)
{
	if (this != &aRhs)
	{
	    mLoss += aRhs.mLoss;
        mWin += aRhs.mWin;
        mTie += aRhs.mTie;
        mCheck += aRhs.mCheck;
        mCards += aRhs.mCards;
	}
	return *this;
}

Bj::Wlt::~Wlt(void)
{
}

void Bj::Wlt::check() const
{
    if (!IsClose(mLoss + mWin + mTie, mCheck))
    {
        cout << "Odds didn't add up to " << mCheck << endl;
        cout << "Win  " << mWin << endl;
        cout << "Loss " << mLoss << endl;
        cout << "Tie  " << mTie << endl;
        throw;
    }
}

Bj::Wlt& Bj::Wlt::scale(const double aScale, const bool aCards)
{
    mWin *= aScale;
    mTie *= aScale;
    mLoss *= aScale;
    mCheck *= aScale;
	if (aCards)
		mCards *= aScale;
    return *this;
}

void Bj::Wlt::print(const unsigned aPrecision) const
{
    cout << " Win: " << setprecision(aPrecision) << mWin;
    cout << " Loss: " << setprecision(aPrecision) << mLoss;
    cout << " Tie: " << setprecision(aPrecision) << mTie;
	cout << " Cards: " << setprecision(aPrecision) << mCards;
    const double exp_win(mWin / (mWin + mLoss));
    const double exp_loss(mLoss / (mWin + mLoss));
    cout << " XpWin: " << setprecision(aPrecision) << exp_win;
    cout << " XpLoss: " << setprecision(aPrecision) << exp_loss;
    cout << " Exp: " << setprecision(aPrecision) << mWin - mLoss << endl;
}

double Bj::Wlt::exp() const
{
    return mWin - mLoss;
    // return (mWin + mTie) - mLoss;
}


Bj::Wlt::Wlt(const DealerOdds& aDealer, 
             const bool aNatural, 
			 const unsigned aPlayerSum,
			 const double aCards,
             const double aBjPayoff)
: mCheck(aDealer.mCheck)
, mWin(0.0)
, mTie(0.0)
, mLoss(0.0)
, mCards(aCards * mCheck + aDealer.mCards)
{
    if (aPlayerSum > 21)
    {
        mLoss = mCheck;
    }
    else if (aPlayerSum < 17)
    {
        mWin = aDealer.mBust;
        mLoss = aDealer.m17 + aDealer.m18 + aDealer.m19 + aDealer.m20 + aDealer.m21;
    }
    else
    {
        switch (aPlayerSum)
        {
        case 17: 
            {
                mWin = aDealer.mBust;
                mTie = aDealer.m17;
                mLoss = aDealer.m18 + aDealer.m19 + aDealer.m20 + aDealer.m21;
                break;
            }
        case 18: 
            {
                mWin = aDealer.m17 + aDealer.mBust;
                mTie = aDealer.m18;
                mLoss = aDealer.m19 + aDealer.m20 + aDealer.m21;
                break;
            }
        case 19: 
            {
                mWin = aDealer.m17 + aDealer.m18 + aDealer.mBust;
                mTie = aDealer.m19;
                mLoss = aDealer.m20 + aDealer.m21;
                break;
            }
        case 20: 
            {
                mWin = aDealer.m17 + aDealer.m18 + aDealer.m19 + aDealer.mBust;
                mTie = aDealer.m20;
                mLoss = aDealer.m21;
                break;
            }
        case 21: 
            {
                if (aNatural)
                {
                    // player wins automatically with Bj
                    mWin = aDealer.m17 + aDealer.m18 + aDealer.m19 + aDealer.m20 + aDealer.m21 - aDealer.mNatural + aDealer.mBust;
                    mTie = aDealer.mNatural;
                }
                else
                {
                    mWin = aDealer.m17 + aDealer.m18 + aDealer.m19 + aDealer.m20 + aDealer.mBust;
                    mTie = aDealer.m21 - aDealer.mNatural;
                    mLoss = aDealer.mNatural;
                }
                break;
            }
        }
    }

    check();

    if (aNatural)
    {
        mWin *= aBjPayoff;
    }
}