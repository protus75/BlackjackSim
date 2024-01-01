#include <vector>
#include <iomanip>
#include <algorithm>

#include "DealerResults.h"
#include "Wlt.h"
#include "Divide.h"


const auto gBjPayout = double(3.0 / 2.0); // (6.0 / 5.0);
const auto gHitSoft17 = bool(false);
const auto gSurrender = bool(true);
const auto gIgnoreDealerBj = bool(true);
const auto gMaxSplit = int(4);

const auto gStrategy = bool(false);

using std::vector;

auto zero1D = vector<double>(10, 0);
auto zero2D = vector<vector<double>>(10, zero1D);

auto loss1D = vector<double>(10, -1.0);

auto sur1D = vector<double>(10, gSurrender ? -0.5 : -1.0);
auto sur2D = vector<vector<double>>(10, sur1D);

auto wlt1D = vector<Bj::Wlt>(10);
auto wlt2D = vector<vector<Bj::Wlt>>(10, wlt1D);

//vector<vector<Bj::Wlt> > gSplit(10, tmp1);

auto unk1D = vector<char>(10, '?');
auto unk2D = vector<vector<char>>(10, unk1D);

struct Wlt
{
    vector<vector<vector<Bj::Wlt>>> mDouble;
    vector<vector<vector<Bj::Wlt>>> mStand;
    vector<vector<vector<Bj::Wlt>>> mHit;

    Wlt()
        : mDouble(10, wlt2D)
        , mStand(10, wlt2D)
        , mHit(10, wlt2D)
    {}
};

struct Dbl
{
    vector<vector<vector<double>>> mDouble;
    vector<vector<vector<double>>> mStand;
    vector<vector<vector<double>>> mHit;
    vector<vector<double>> mSplit;

    Dbl()
        : mDouble(10, zero2D)
        , mStand(10, zero2D)
        , mHit(10, zero2D)
        , mSplit(10, loss1D)
    {}
};

class Expect
{
public:

    vector<vector<vector<double>>> mOdds;
    vector<vector<vector<double>>> mBest;
    vector<vector<vector<char>>> mChoice;

    Wlt mWlt;
    Dbl mDbl;

    double mExp;

    Expect(int s[11], int rem)
        : mOdds(10, zero2D)
        , mBest(10, sur2D)
        , mChoice(10, unk2D)
        , mWlt()
        , mDbl()
        , mExp(0.0)
    {
        Play(s, rem);

        Choose();

        auto odds = double(0.0);
        for (int i = 9; i >= 0; --i)
        {
            for (int j = 0; j < 10; ++j)
            {
                for (int k = 0; k <= j; ++k)
                {
                    odds += mOdds[i][k][j];
                    mExp += mOdds[i][k][j] * mBest[i][k][j];
                }
            }
        }

        if (odds != 1.0 and (abs(odds - 1.0) > 0.000001))
        {
            std::cerr << "Deck odds did not sum to 1.0.  (" << odds << ")";
        }
    }

private:
    void Odds(int s[11], int rem);

    void Stand(int s[11], int rem);
    
    void Double(int s[11], int rem);
    
    Bj::Wlt Hit(const Bj::Wlt& stand, int p[11], int s[11], int rem, int d1, int p1, int p2, double ratio);
    
    void Hit(int s[11], int rem);
    
    void Split(int s[11], int rem);
    
    double Split(int s[11], int rem, int d, int p);

    // Calculate individual cases for each hand
    void Play(int s[11], int rem)
    {
        Odds(s, rem);
        Stand(s, rem);
        Double(s, rem);
        Hit(s, rem);
        Split(s, rem);
    }

    void Choose()
    {
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                for (int k = 0; k <= j; ++k)
                {
                    mDbl.mStand[i][k][j] = mWlt.mStand[i][k][j].exp();
                    mDbl.mHit[i][k][j] = mWlt.mHit[i][k][j].exp();
                    mDbl.mDouble[i][k][j] = mWlt.mDouble[i][k][j].exp();

                    mBest[i][k][j] = mDbl.mStand[i][k][j];
                    mChoice[i][k][j] = 'S';

                    const auto hit = mDbl.mHit[i][k][j];
                    if (hit > mBest[i][k][j])
                    {
                        mBest[i][k][j] = hit;
                        mChoice[i][k][j] = 'H';
                    }

                    /// when Hit and Double are essentially the same odds, and positive, then should choose Double with a small tolerance to avoid spurious Hit instead of Double
                    const auto dbl = mDbl.mDouble[i][k][j];
                    if ((dbl >= 0.0) and ((dbl > mBest[i][k][j]) or (abs(dbl - mBest[i][k][j]) < 0.001)))
                    {
                        mBest[i][k][j] = dbl;
                        mChoice[i][k][j] = '2';
                    }

                    // can only figure surrender when ignoring dealer natural
                    /// \todo why?
                    if (gSurrender && gIgnoreDealerBj)
                    {
                        if (mBest[i][k][j] < -0.5)
                        {
                            mBest[i][k][j] = -0.5;
                            mChoice[i][k][j] = 'U';
                        }
                    }

                    // only consider split when have same rank cards
                    if (j == k)
                    {
                        if (mBest[i][k][j] < mDbl.mSplit[i][j])
                        {
                            mBest[i][k][j] = mDbl.mSplit[i][j];
                            mChoice[i][k][j] = '|';
                        }
                    }
                }
            }
        }
    }

public:

    void Print() const;
};

void Expect::Odds(int s[11], int rem)
{
    for (int p1 = 10; p1 > 0; --p1) if (s[p1])
    {
        const double p1Odds(double(s[p1]) / rem);
        --s[p1]; --rem;

        for (int p2 = p1; p2 <= 10; ++p2) if (s[p2])
        {
            const double p2Odds(double(s[p2]) / rem);
            --s[p2]; --rem;

            const double ratio = ((p1 == p2) ? 1.0 : 2.0);

            for (int d1 = 10; d1 > 0; --d1) if (s[d1])
            {
                const double d1Odds(double(s[d1]) / rem);

                mOdds[d1 - 1][p1 - 1][p2 - 1] = d1Odds * p1Odds * p2Odds * ratio;

            }

            ++s[p2]; ++rem;
        }

        ++s[p1]; ++rem;
    }
}

void Expect::Stand(int s[11], int rem)
{
    for (int p1 = 10; p1 > 0; --p1) if (s[p1])
    {
        --s[p1]; --rem;

        for (int p2 = p1; p2 <= 10; ++p2) if (s[p2])
        {
            --s[p2]; --rem;

            const bool natural(((p1 == 1) and (p2 == 10)) or ((p1 == 10) and (p2 == 1)));

            int p[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            ++p[p1];
            ++p[p2];

            for (int d1 = 10; d1 > 0; --d1) if (s[d1])
            {
                --s[d1]; --rem;

                Bj::Wlt stand;
                double dealerBj = 0.0;
                for (int d2 = 1; d2 <= 10; ++d2) if (s[d2])
                {
                    const double d2Odds(double(s[d2]) / rem);
                    --s[d2]; --rem;

                    Bj::DealerResults dr(gHitSoft17);
                    dr.Results(d1, d2, rem, s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9], s[10], 1.0, p1 + p2);
                    if (((d1 == 1) or (d2 == 1)) and ((d1 + d2) == 11))
                    {
                        dealerBj = d2Odds;
                    }
                    else
                    {
                        stand += dr.WinLoss(p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], natural, gBjPayout).scale(d2Odds);
                    }

                    ++s[d2]; ++rem;
                }

                mWlt.mStand[d1 - 1][p1 - 1][p2 - 1] = stand * (1.0 / (1.0 - dealerBj));

                ++s[d1]; ++rem;
            }

            ++s[p2]; ++rem;
        }

        ++s[p1]; ++rem;
    }
}

void Expect::Double(int s[11], int rem)
{
    const auto natural = false;

    for (int p1 = 10; p1 > 0; --p1) if (s[p1])
    {       
        --s[p1]; --rem;

        for (int p2 = p1; p2 <= 10; ++p2) if (s[p2])
        {
            --s[p2]; --rem;

            for (int d1 = 10; d1 > 0; --d1) if (s[d1])
            {
                --s[d1]; --rem;

                Bj::Wlt dbl;
                double dealerBj = 0.0;
                for (int d2 = 1; d2 <= 10; ++d2) if (s[d2])
                {
                    const double d2Odds(double(s[d2]) / rem);
                    --s[d2]; --rem;

                    if (((d1 == 1) or (d2 == 1)) and ((d1 + d2) == 11))
                    {
                        dealerBj = d2Odds;
                    }
                    else
                    {
                        for (int p3 = 1; p3 <= 10; ++p3) if (s[p3])
                        {
                            const double p3Odds(double(s[p3]) / rem);
                            --s[p3]; --rem;

                            int p[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                            ++p[p1];
                            ++p[p2];
                            ++p[p3];

                            Bj::DealerResults dr(gHitSoft17);
                            dr.Results(d1, d2, rem, s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9], s[10], 1.0, p1 + p2 + p3);
                            dbl += dr.WinLoss(p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], natural, gBjPayout).scale(p3Odds * d2Odds);

                            ++s[p3]; ++rem;
                        }
                    }

                    ++s[d2]; ++rem;
                }

                mWlt.mDouble[d1 - 1][p1 - 1][p2 - 1] = dbl * (1.0 / (1.0 - dealerBj));

                ++s[d1]; ++rem;
            }

            ++s[p2]; ++rem;
        }

        ++s[p1]; ++rem;
    }

}

bool Stop(int aP[11], int aD)
{
    int sum = 0;
    for (int i = 1; i <= 10; ++i)
    {
        sum += i * aP[i];
    }
          
    return (sum >= 17) or ((aP[1] > 0) and (sum + 10 > 17)) or ((aD <= 7) and (sum > 11));
}

void Expect::Hit(int s[11], int rem)
{
    const auto natural = false;

    for (int p1 = 10; p1 > 0; --p1) if (s[p1])
    {
        --s[p1]; --rem;

        for (int p2 = p1; p2 <= 10; ++p2) if (s[p2])
        {
            --s[p2]; --rem;

            for (int d1 = 10; d1 > 0; --d1) if (s[d1])
            {
                --s[d1]; --rem;

                Bj::Wlt hit;
                double dealerBj = 0.0;
                for (int d2 = 1; d2 <= 10; ++d2) if (s[d2])
                {
                    const double d2Odds(double(s[d2]) / rem);
                    --s[d2]; --rem;

                    if (((d1 == 1) or (d2 == 1)) and ((d1 + d2) == 11))
                    {
                        dealerBj = d2Odds;
                    }
                    else
                    {
                        for (int p3 = 1; p3 <= 10; ++p3) if (s[p3])
                        {
                            const double p3Odds(double(s[p3]) / rem);
                            --s[p3]; --rem;

                            int p[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                            ++p[p1];
                            ++p[p2];
                            ++p[p3];

                            if (Stop(p, d1))
                            {
                                Bj::DealerResults dr(gHitSoft17);
                                dr.Results(d1, d2, rem, s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9], s[10], 1.0, p1 + p2 + p3);
                                hit += dr.WinLoss(p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], natural, gBjPayout).scale(p3Odds * d2Odds);
                            }
                            else
                            {
                                for (int p4 = 1; p4 <= 10; ++p4) if (s[p4])
                                {
                                    const double p4Odds(double(s[p4]) / rem);
                                    --s[p4]; --rem;

                                    ++p[p4];

                                    if (Stop(p, d1))
                                    {
                                        Bj::DealerResults dr(gHitSoft17);
                                        dr.Results(d1, d2, rem, s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9], s[10], 1.0, p1 + p2 + p3 + p4);
                                        hit += dr.WinLoss(p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], natural, gBjPayout).scale(p4Odds * p3Odds * d2Odds);
                                    }
                                    else
                                    {
                                        for (int p5 = 1; p5 <= 10; ++p5) if (s[p5])
                                        {
                                            const double p5Odds(double(s[p5]) / rem);
                                            --s[p5]; --rem;

                                            ++p[p5];

                                            if (Stop(p, d1))
                                            {
                                                Bj::DealerResults dr(gHitSoft17);
                                                dr.Results(d1, d2, rem, s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9], s[10], 1.0, p1 + p2 + p3 + p4 + p5);
                                                hit += dr.WinLoss(p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], natural, gBjPayout).scale(p5Odds * p4Odds * p3Odds * d2Odds);
                                            }
                                            else
                                            {
                                                for (int p6 = 1; p6 <= 10; ++p6) if (s[p6])
                                                {
                                                    const double p6Odds(double(s[p6]) / rem);
                                                    --s[p6]; --rem;

                                                    ++p[p6];

                                                    Bj::DealerResults dr(gHitSoft17);
                                                    dr.Results(d1, d2, rem, s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9], s[10], 1.0, p1 + p2 + p3 + p4 + p5 + p6);
                                                    hit += dr.WinLoss(p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], natural, gBjPayout).scale(p6Odds * p5Odds * p4Odds * p3Odds * d2Odds);

                                                    --p[p6];

                                                    ++s[p6]; ++rem;
                                                }

                                            }

                                            --p[p5];

                                            ++s[p5]; ++rem;
                                        }

                                    }

                                    --p[p4];

                                    ++s[p4]; ++rem;
                                }
                            }

                            ++s[p3]; ++rem;
                        }
                    }

                    ++s[d2]; ++rem;
                }

                mWlt.mHit[d1 - 1][p1 - 1][p2 - 1] = hit * (1.0 / (1.0 - dealerBj));

                ++s[d1]; ++rem;
            }

            ++s[p2]; ++rem;
        }

        ++s[p1]; ++rem;
    }
}

double Expect::Split(int s[11], int rem, int d1, int p1)
{
    double exp(0.0);
    if (1 == p1)
    {
        double split_two(0.0);
        double cumul(0.0);
        // Only get one card per ace after splitting aces
        for (int p2a = 1; p2a <= 10; ++p2a)
        {
            if (s[p2a])
            {
                const double p2aOdds = double(s[p2a]) / rem;
                --s[p2a]; --rem;

                for (int p2b = p2a; p2b <= 10; ++p2b)
                {
                    if (s[p2b])
                    {
                        const double p2bOdds = double(s[p2b]) / rem;
                        --s[p2b]; --rem;

                        Bj::DealerResults dlr_res(gHitSoft17);

                        for (int d2 = 1; d2 <= 10; ++d2)
                        {
                            if (s[d2])
                            {
                                const double d2Odds = double(s[d2]) / rem;

                                --s[d2]; --rem;

                                dlr_res.Results(d1,d2,rem,s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9],s[10],d2Odds,-99);

                                ++s[d2]; ++rem;
                            }
                        }

                        int pa[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                        ++pa[p1];
                        ++pa[p2a];

                        int pb[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                        ++pb[p1];
                        ++pb[p2b];

                        const double expa(dlr_res.WinLoss(pa[1],pa[2],pa[3],pa[4],pa[5],pa[6],pa[7],pa[8],pa[9],pa[10],false, gBjPayout).exp());

                        const double expb(dlr_res.WinLoss(pb[1],pb[2],pb[3],pb[4],pb[5],pb[6],pb[7],pb[8],pb[9],pb[10],false, gBjPayout).exp());

                        const double odds_ratio(p2a == p2b ? 1.0 : 2.0);

                        cumul += odds_ratio * p2aOdds * p2bOdds;

                        split_two += odds_ratio * (expa + expb) * p2aOdds * p2bOdds;

                        if (false)
                        {
                            using std::setw;
                            std::cout << "d:" << setw(3) << d1;
                            std::cout << ", a:" << setw(3) << p2a << " e:" << setw(8) << expa << ", o:" << setw(8) << p2aOdds;
                            std::cout << ", b:" << setw(3) << p2b << " e:" << setw(8) << expb << ", o:" << setw(8) << p2bOdds;
                            std::cout << ", cm:" << setw(8) << cumul << ", x:" << setw(8) << split_two << std::endl;
                        }

                        ++s[p2b]; ++rem;
                    }
                }

                ++s[p2a]; ++rem;
            }
        }
        double split_thr(-1.0);
        if (s[1])
        {
        }
        exp = std::max(split_two, split_thr);
    }
    else
    {
        exp = mDbl.mSplit[d1-1][p1-1];
    }

    return exp;
}


void Expect::Split(int s[11], int rem)
{
    mDbl.mSplit[0][0] =  0.2239;
    mDbl.mSplit[0][1] = -0.422;
    mDbl.mSplit[0][2] = -0.465;
    mDbl.mSplit[0][3] = -0.527;
    mDbl.mSplit[0][4] = -0.613;
    mDbl.mSplit[0][5] = -0.617;
    mDbl.mSplit[0][6] = -0.613;
    mDbl.mSplit[0][7] = -0.363;
    mDbl.mSplit[0][8] = -0.113;
    mDbl.mSplit[0][9] =  0.097;
    mDbl.mSplit[1][0] =  0.5657;
    mDbl.mSplit[1][1] = -0.047;
    mDbl.mSplit[1][2] = -0.116;
    mDbl.mSplit[1][3] = -0.156;
    mDbl.mSplit[1][4] = -0.193;
    mDbl.mSplit[1][5] = -0.165;
    mDbl.mSplit[1][6] = -0.105;
    mDbl.mSplit[1][7] =  0.064;
    mDbl.mSplit[1][8] =  0.188;
    mDbl.mSplit[1][9] =  0.331;
    mDbl.mSplit[2][0] =  0.6128;
    mDbl.mSplit[2][1] =  0.021;
    mDbl.mSplit[2][2] = -0.031;
    mDbl.mSplit[2][3] = -0.048;
    mDbl.mSplit[2][4] = -0.104;
    mDbl.mSplit[2][5] = -0.069;
    mDbl.mSplit[2][6] = -0.020;
    mDbl.mSplit[2][7] =  0.132;
    mDbl.mSplit[2][8] =  0.242;
    mDbl.mSplit[2][9] =  0.383;
    mDbl.mSplit[3][0] =  0.6686;
    mDbl.mSplit[3][1] =  0.112;
    mDbl.mSplit[3][2] =  0.102;
    mDbl.mSplit[3][3] =  0.076;
    mDbl.mSplit[3][4] =  0.014;
    mDbl.mSplit[3][5] =  0.047;
    mDbl.mSplit[3][6] =  0.103;
    mDbl.mSplit[3][7] =  0.215;
    mDbl.mSplit[3][8] =  0.320;
    mDbl.mSplit[3][9] =  0.444;
    mDbl.mSplit[4][0] =  0.7322;
    mDbl.mSplit[4][1] =  0.239;
    mDbl.mSplit[4][2] =  0.228;
    mDbl.mSplit[4][3] =  0.197;
    mDbl.mSplit[4][4] =  0.133;
    mDbl.mSplit[4][5] =  0.172;
    mDbl.mSplit[4][6] =  0.200;
    mDbl.mSplit[4][7] =  0.312;
    mDbl.mSplit[4][8] =  0.415;
    mDbl.mSplit[4][9] =  0.521;
    mDbl.mSplit[5][0] =  0.7583;
    mDbl.mSplit[5][1] =  0.240;
    mDbl.mSplit[5][2] =  0.220;
    mDbl.mSplit[5][3] =  0.183;
    mDbl.mSplit[5][4] =  0.131;
    mDbl.mSplit[5][5] =  0.151;
    mDbl.mSplit[5][6] =  0.220;
    mDbl.mSplit[5][7] =  0.356;
    mDbl.mSplit[5][8] =  0.437;
    mDbl.mSplit[5][9] =  0.543;
    mDbl.mSplit[6][0] =  0.5407;
    mDbl.mSplit[6][1] = -0.006;
    mDbl.mSplit[6][2] = -0.068;
    mDbl.mSplit[6][3] = -0.160;
    mDbl.mSplit[6][4] = -0.228;
    mDbl.mSplit[6][5] = -0.228;
    mDbl.mSplit[6][6] = -0.056;
    mDbl.mSplit[6][7] =  0.259;
    mDbl.mSplit[6][8] =  0.364;
    mDbl.mSplit[6][9] =  0.478;
    mDbl.mSplit[7][0] =  0.4065;
    mDbl.mSplit[7][1] = -0.192;
    mDbl.mSplit[7][2] = -0.244;
    mDbl.mSplit[7][3] = -0.291;
    mDbl.mSplit[7][4] = -0.391;
    mDbl.mSplit[7][5] = -0.374;
    mDbl.mSplit[7][6] = -0.378;
    mDbl.mSplit[7][7] = -0.059;
    mDbl.mSplit[7][8] =  0.207;
    mDbl.mSplit[7][9] =  0.345;
    mDbl.mSplit[8][0] =  0.2898;
    mDbl.mSplit[8][1] = -0.373;
    mDbl.mSplit[8][2] = -0.395;
    mDbl.mSplit[8][3] = -0.459;
    mDbl.mSplit[8][4] = -0.560;
    mDbl.mSplit[8][5] = -0.542;
    mDbl.mSplit[8][6] = -0.535;
    mDbl.mSplit[8][7] = -0.383;
    mDbl.mSplit[8][8] = -0.093;
    mDbl.mSplit[8][9] =  0.172;
    mDbl.mSplit[9][0] =  0.1942;
    mDbl.mSplit[9][1] = -0.499;
    mDbl.mSplit[9][2] = -0.498;
    mDbl.mSplit[9][3] = -0.552;
    mDbl.mSplit[9][4] = -0.648;
    mDbl.mSplit[9][5] = -0.647;
    mDbl.mSplit[9][6] = -0.606;
    mDbl.mSplit[9][7] = -0.447;
    mDbl.mSplit[9][8] = -0.265;
    mDbl.mSplit[9][9] =  0.033;

    for (int d = 1; d <= 10; ++d)
    {
        if (s[d])
        {
            --s[d]; --rem;
            for (int p = 1; p <= 10; ++p)
            {
                if (s[p] >= 2)
                {
                    s[p] -= 2; rem -= 2;

                    mDbl.mSplit[d-1][p-1] = Split(s,rem,d,p);

                    s[p] += 2; rem += 2;
                }

            }
            ++s[d]; ++rem;
        }
    }
}

void ColHeader(const std::string aType)
{
    cout << std::setw(8) << aType;
    for (int c = 1; c <= 10; ++c)
    {
        std::cout << std::setw(8) << c;
    }
    cout << endl;
}

template <typename T>
void PrintTri(const vector<vector<T>>& aD)
{
    for (int j = 0; j < 10; ++j)
    {
        std::cout << std::setw(8) << j + 1;
        for (int k = 0; k <= j; ++k)
        {
            std::cout << std::setw(8) << aD[k][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Expect::Print() const
{
	// output

	std::cout.precision(4);
	std::cout.setf(std::ios::fixed);

    cout << endl << mExp << endl;

	cout << endl << "+++" << endl;

    double sum_sum_sum(0.0);

    for (int i = 9; i >= 0; --i)
    {
        cout << "Dealer Up Card: " << i + 1 << endl;
        std::cout << std::endl;

        ColHeader("Stand");
        PrintTri(mDbl.mStand[i]);

        ColHeader("Hit");
        PrintTri(mDbl.mHit[i]);

        ColHeader("Double");
        PrintTri(mDbl.mDouble[i]);

        ColHeader("Split");
        std::cout << std::setw(8) << " ";
        for (int j = 0; j < 10; ++j)
        {
            std::cout << std::setw(8) << mDbl.mSplit[i][j];
        }
        std::cout << std::endl;
        std::cout << std::endl;

        ColHeader("Best");
        PrintTri(mBest[i]);
        PrintTri(mChoice[i]);

        {
            ColHeader("Odds");
            PrintTri(mOdds[i]);

            vector<double> sum(10, 0.0);
            for (int j = 0; j < 10; ++j)
            {
                for (int k = 0; k <= j; ++k)
                {
                    sum[k] += mOdds[i][k][j];
                }
            }
            cout << std::setw(8) << "Sum";

            double sum_sum(0.0);
            for (int j = 0; j < 10; ++j)
            {
                sum_sum += sum[j];
                std::cout << std::setw(8) << sum[j];
            }
            std::cout << std::setw(8) << sum_sum << std::endl;
            std::cout << std::endl;
        }
/////////////////////////////////////////////////////////////////////////////
        {
            ColHeader("Exp");
            //PrintTri(m[i]);

            vector<double> sum(10, 0.0);
            for (int j = 0; j < 10; ++j)
            {
                std::cout << std::setw(8) << j + 1;
                for (int k = 0; k <= j; ++k)
                {
                    sum[k] += mOdds[i][k][j] * mBest[i][k][j];
                    std::cout << std::setw(8) << mOdds[i][k][j] * mBest[i][k][j];
                }
                std::cout << std::endl;
            }
            cout << std::setw(8) << "Sum";
            double sum_sum(0.0);
            for (int j = 0; j < 10; ++j)
            {
                sum_sum += sum[j];
                std::cout << std::setw(8) << sum[j];
            }
            std::cout << std::setw(8) << sum_sum << std::endl;
            std::cout << std::endl;

            sum_sum_sum += sum_sum;
        }

        cout << "---" << endl;
    }
    std::cout << std::setw(8) << sum_sum_sum << std::endl;

}

int main(int argc, char* argv[])
{
    const int d = 1;
    const int r = 4;

    int s[11] = { 0, d * r, d * r, d * r, d * r, d * r, d * r, d * r, d * r, d * r, 4 * d * r };
    int rem = d * r * 13;

    Bj::InitialDivide();

    const auto e = Expect(s, rem);

    e.Print();

    return 0;
}


    #if 0
for (int i = 1; i <= 10; ++i)
{
    if (s[i])
    {
        const double p1Odds(double(s[i]) / rem);
        sum += i; ++cards; 

        if (sum > 21)
        {
            Bj::DealerOdds dlr_odds;
            dlr_odds.m21 = 1.0;
            hit += Bj::Wlt(dlr_odds, false, sum, gIgnoreDealerBj).scale(p1Odds);
        }
        else
        {
            --s[i]; --rem; ++p[i];

            Bj::DealerResults dlr_res(gHitSoft17);
            Bj::Wlt wr;

            for (int d2 = 1; d2 <= 10; ++d2)
            {
                if (s[d2])
                {
                    const double d2Odds = double(s[d2]) / rem;

                    --s[d2]; --rem;

                    dlr_res.Results(d1,d2,rem,s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9],s[10],d2Odds,sum);

                    ++s[d2]; ++rem;
                }
            }

            Bj::Wlt hit_stand(dlr_res.WinLoss(p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],false,gIgnoreDealerBj));
            hit += Bj::Wlt(std::max(hit_stand,
                                    Hit(hit_stand, p, s, rem, d1, p1, p2))).scale(p1Odds);
    #else
    #endif

