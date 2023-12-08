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
        exit(1);
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


Bj::Wlt::Wlt(const DealerOdds& aOdds, 
             const bool aNatural, 
			 const unsigned aPlayerSum,
			 const double aCards,
             const bool aIgnoreDealerBj)
: mCheck(aOdds.mCheck)
, mWin(0.0)
, mTie(0.0)
, mLoss(0.0)
, mCards(aCards * mCheck + aOdds.mCards)
{
    const double ign(aIgnoreDealerBj ? aOdds.mNatural : 0.0);

    if (aPlayerSum > 21)
    {
        mLoss = mCheck - ign;
    }
    else if (aPlayerSum < 17)
    {
        mWin = aOdds.mBust;
        mLoss = aOdds.m17 + aOdds.m18 + aOdds.m19 + aOdds.m20 + aOdds.m21 - ign;
    }
    else
    {
        switch (aPlayerSum)
        {
        case 17: 
            {
                mWin = aOdds.mBust;
                mTie = aOdds.m17;
                mLoss = aOdds.m18 + aOdds.m19 + aOdds.m20 + aOdds.m21 - ign;
                break;
            }
        case 18: 
            {
                mWin = aOdds.m17 + aOdds.mBust;
                mTie = aOdds.m18;
                mLoss = aOdds.m19 + aOdds.m20 + aOdds.m21 - ign;
                break;
            }
        case 19: 
            {
                mWin = aOdds.m17 + aOdds.m18 + aOdds.mBust;
                mTie = aOdds.m19;
                mLoss = aOdds.m20 + aOdds.m21 - ign;
                break;
            }
        case 20: 
            {
                mWin = aOdds.m17 + aOdds.m18 + aOdds.m19 + aOdds.mBust;
                mTie = aOdds.m20;
                mLoss = aOdds.m21 - ign;
                break;
            }
        case 21: 
            {
                if (aNatural)
                {
                    // player wins automatically with Bj
                    mWin = aOdds.m17 + aOdds.m18 + aOdds.m19 + aOdds.m20 + aOdds.m21 - aOdds.mNatural + aOdds.mBust;
                    mTie = aOdds.mNatural - ign;
                }
                else
                {
                    mWin = aOdds.m17 + aOdds.m18 + aOdds.m19 + aOdds.m20 + aOdds.mBust;
                    mTie = aOdds.m21 - aOdds.mNatural;
                    mLoss = aOdds.mNatural - ign;
                }
                break;
            }
        }
    }

    if (aIgnoreDealerBj) 
    {
        if (!IsClose(mCheck, ign))
        {
            const double tmp(mCheck);
            mCheck -= ign;
            scale(tmp / (tmp - ign));
        }
        else
        {
            scale(0.0);
        }

    }

    check();
}