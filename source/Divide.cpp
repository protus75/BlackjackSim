#include "Divide.h"

namespace
{
	const int cardsPer(52);
	const int maxRankPer(16);
	const int maxDeck(8);
    std::vector<std::vector<double> > gDivide((maxDeck * cardsPer) + 1, std::vector<double>((maxDeck * maxRankPer) + 1, 0));
}

const std::vector<std::vector<double> >& Bj::Divide()
{
    return gDivide;
}

void Bj::InitialDivide()
{
    for (int i = 1; i <= (maxDeck * cardsPer); ++i)
    {
        for (int j = 1; j <= (maxDeck * maxRankPer); ++j)
        {
            gDivide[i][j] = static_cast<double>(j) / i;
        }
    }
}
