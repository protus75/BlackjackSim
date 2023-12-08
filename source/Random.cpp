#include <list>
#include <cmath>
#include <iostream>
#include <string>
#include <numeric>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

const bool gHitSoft17(false);
const bool gSurrender(true);
const int gMaxSplit(4);

int gdecks(6);
int gplayers(6);
int gshoes(30);
int gbox(0);
double ggrab(0.75);
int gpenetration((int)floor(gdecks * 52 * 0.6));

typedef enum
{
	HIT = 1,
	STD = 2,
	DBL = 3,
	SPT = 4,
	SUR = 5
} tstrat;

             
tstrat strat[10][10][10]
              // A    2    3    4    5    6    7    8    9    T    ACE 	
	      = {{{SPT, HIT, HIT, HIT, HIT, HIT, HIT, STD, STD, STD}  // A   
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT}  // 2
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT}  // 3
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT}  // 4
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT}  // 5
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT}  // 6
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, STD}  // 7 
			 ,{STD, HIT, HIT, HIT, HIT, HIT, HIT, SPT, STD, STD}  // 8
			 ,{STD, HIT, HIT, HIT, HIT, HIT, HIT, STD, STD, STD}  // 9
			 ,{STD, HIT, HIT, HIT, HIT, HIT, STD, STD, STD, STD}} // T
             // ------------------------------------------------------                                                     
			 // A    2    3    4    5    6    7    8    9    T    TWO 
	        ,{{SPT, HIT, HIT, HIT, HIT, HIT, DBL, STD, STD, STD}  // A
			 ,{HIT, SPT, HIT, HIT, HIT, HIT, HIT, DBL, DBL, HIT}  // 2
			 ,{HIT, HIT, SPT, HIT, HIT, HIT, DBL, DBL, HIT, STD}  // 3
			 ,{HIT, HIT, HIT, HIT, HIT, DBL, DBL, HIT, STD, STD}  // 4
			 ,{HIT, HIT, HIT, HIT, DBL, DBL, HIT, STD, STD, STD}  // 5
			 ,{HIT, HIT, HIT, DBL, DBL, SPT, STD, STD, STD, STD}  // 6
			 ,{DBL, HIT, DBL, DBL, HIT, STD, SPT, STD, STD, STD}  // 7
			 ,{STD, DBL, DBL, HIT, STD, STD, STD, SPT, STD, STD}  // 8
			 ,{STD, DBL, HIT, STD, STD, STD, STD, STD, SPT, STD}  // 9
			 ,{STD, HIT, STD, STD, STD, STD, STD, STD, STD, STD}} // T
             // ------------------------------------------------------                                                     
			 // A    2    3    4    5    6    7    8    9    T    THREE
	        ,{{SPT, HIT, HIT, HIT, HIT, DBL, DBL, STD, STD, STD}  // A
			 ,{HIT, SPT, HIT, HIT, HIT, HIT, DBL, DBL, DBL, HIT}  // 2
			 ,{HIT, HIT, SPT, HIT, HIT, DBL, DBL, DBL, HIT, STD}  // 3
			 ,{HIT, HIT, HIT, HIT, DBL, DBL, DBL, HIT, STD, STD}  // 4
			 ,{HIT, HIT, HIT, DBL, DBL, DBL, HIT, STD, STD, STD}  // 5
			 ,{DBL, HIT, DBL, DBL, DBL, SPT, STD, STD, STD, STD}  // 6
			 ,{DBL, DBL, DBL, DBL, HIT, STD, SPT, STD, STD, STD}  // 7
			 ,{STD, DBL, DBL, HIT, STD, STD, STD, SPT, STD, STD}  // 8
			 ,{STD, DBL, HIT, STD, STD, STD, STD, STD, SPT, STD}  // 9
			 ,{STD, HIT, STD, STD, STD, STD, STD, STD, STD, STD}} // T
             // ------------------------------------------------------                                                     
			 // A    2    3    4    5    6    7    8    9    T    FOUR 
	        ,{{SPT, HIT, HIT, DBL, DBL, DBL, DBL, STD, STD, STD}  // A
			 ,{HIT, SPT, HIT, HIT, HIT, HIT, DBL, DBL, DBL, STD}  // 2
			 ,{HIT, HIT, SPT, HIT, HIT, DBL, DBL, DBL, STD, STD}  // 3
			 ,{DBL, HIT, HIT, HIT, DBL, DBL, DBL, STD, STD, STD}  // 4
			 ,{DBL, HIT, HIT, DBL, DBL, DBL, STD, STD, STD, STD}  // 5
			 ,{DBL, HIT, DBL, DBL, DBL, SPT, STD, STD, STD, STD}  // 6
			 ,{DBL, DBL, DBL, DBL, STD, STD, SPT, STD, STD, STD}  // 7
			 ,{STD, DBL, DBL, STD, STD, STD, STD, SPT, STD, STD}  // 8
			 ,{STD, DBL, STD, STD, STD, STD, STD, STD, SPT, STD}  // 9
			 ,{STD, STD, STD, STD, STD, STD, STD, STD, STD, STD}} // T
             // ------------------------------------------------------                                                     
			 // A    2    3    4    5    6    7    8    9    T    FIVE 
	        ,{{SPT, DBL, DBL, DBL, DBL, DBL, DBL, STD, STD, STD}  // A
			 ,{DBL, SPT, HIT, HIT, HIT, HIT, DBL, DBL, DBL, STD}  // 2
			 ,{DBL, HIT, SPT, HIT, HIT, DBL, DBL, DBL, STD, STD}  // 3
			 ,{DBL, HIT, HIT, SPT, DBL, DBL, DBL, STD, STD, STD}  // 4
			 ,{DBL, HIT, HIT, DBL, DBL, DBL, STD, STD, STD, STD}  // 5
			 ,{DBL, HIT, DBL, DBL, DBL, SPT, STD, STD, STD, STD}  // 6
			 ,{DBL, DBL, DBL, DBL, STD, STD, SPT, STD, STD, STD}  // 7
			 ,{STD, DBL, DBL, STD, STD, STD, STD, SPT, STD, STD}  // 8
			 ,{STD, DBL, STD, STD, STD, STD, STD, STD, SPT, STD}  // 9
			 ,{STD, STD, STD, STD, STD, STD, STD, STD, STD, STD}} // T
             // ------------------------------------------------------                                                     
			 // A    2    3    4    5    6    7    8    9    T    SIX 
	        ,{{SPT, DBL, DBL, DBL, DBL, DBL, DBL, DBL, STD, STD}  // A
			 ,{DBL, SPT, HIT, HIT, HIT, HIT, DBL, DBL, DBL, STD}  // 2
			 ,{DBL, HIT, SPT, HIT, HIT, DBL, DBL, DBL, STD, STD}  // 3
			 ,{DBL, HIT, HIT, SPT, DBL, DBL, DBL, STD, STD, STD}  // 4
			 ,{DBL, HIT, HIT, DBL, DBL, DBL, STD, STD, STD, STD}  // 5
			 ,{DBL, HIT, DBL, DBL, DBL, SPT, STD, STD, STD, STD}  // 6
			 ,{DBL, DBL, DBL, DBL, STD, STD, SPT, STD, STD, STD}  // 7
			 ,{DBL, DBL, DBL, STD, STD, STD, STD, SPT, STD, STD}  // 8
			 ,{STD, DBL, STD, STD, STD, STD, STD, STD, SPT, STD}  // 9
			 ,{STD, STD, STD, STD, STD, STD, STD, STD, STD, STD}} // T
             // ------------------------------------------------------                                                     
			 // A    2    3    4    5    6    7    8    9    T    SEVEN 
	        ,{{SPT, HIT, HIT, HIT, HIT, HIT, STD, STD, STD, STD}  // A
			 ,{HIT, SPT, HIT, HIT, HIT, HIT, HIT, DBL, DBL, HIT}  // 2
			 ,{HIT, HIT, SPT, HIT, HIT, HIT, DBL, DBL, HIT, HIT}  // 3
			 ,{HIT, HIT, HIT, HIT, HIT, DBL, DBL, HIT, HIT, HIT}  // 4
			 ,{HIT, HIT, HIT, HIT, DBL, DBL, HIT, HIT, HIT, HIT}  // 5
			 ,{HIT, HIT, HIT, DBL, DBL, SPT, HIT, HIT, HIT, HIT}  // 6
			 ,{STD, HIT, DBL, DBL, HIT, HIT, SPT, HIT, HIT, STD}  // 7
			 ,{STD, DBL, DBL, HIT, HIT, HIT, HIT, SPT, STD, STD}  // 8
			 ,{STD, DBL, HIT, HIT, HIT, HIT, HIT, STD, STD, STD}  // 9
			 ,{STD, HIT, HIT, HIT, HIT, HIT, STD, STD, STD, STD}} // T
             // ------------------------------------------------------                                                     
			 // A    2    3    4    5    6    7    8    9    T    EIGHT 
	        ,{{SPT, HIT, HIT, HIT, HIT, HIT, STD, STD, STD, STD}  // A
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, HIT, DBL, DBL, HIT}  // 2
			 ,{HIT, HIT, SPT, HIT, HIT, HIT, DBL, DBL, HIT, HIT}  // 3
			 ,{HIT, HIT, HIT, HIT, HIT, DBL, DBL, HIT, HIT, HIT}  // 4
			 ,{HIT, HIT, HIT, HIT, DBL, DBL, HIT, HIT, HIT, HIT}  // 5
			 ,{HIT, HIT, HIT, DBL, DBL, HIT, HIT, HIT, HIT, HIT}  // 6
			 ,{STD, HIT, DBL, DBL, HIT, HIT, SPT, HIT, HIT, STD}  // 7
			 ,{STD, DBL, DBL, HIT, HIT, HIT, HIT, SPT, STD, STD}  // 8
			 ,{STD, DBL, HIT, HIT, HIT, HIT, HIT, STD, SPT, STD}  // 9
			 ,{STD, HIT, HIT, HIT, HIT, HIT, STD, STD, STD, STD}} // T
             // ------------------------------------------------------                                                     
			 // A    2    3    4    5    6    7    8    9    T    NINE
	        ,{{SPT, HIT, HIT, HIT, HIT, HIT, HIT, STD, STD, STD}  // A
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, HIT, DBL, DBL, HIT}  // 2
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, DBL, DBL, HIT, HIT}  // 3
			 ,{HIT, HIT, HIT, HIT, HIT, DBL, DBL, HIT, HIT, HIT}  // 4
			 ,{HIT, HIT, HIT, HIT, DBL, DBL, HIT, HIT, HIT, HIT}  // 5
			 ,{HIT, HIT, HIT, DBL, DBL, HIT, HIT, HIT, HIT, HIT}  // 6
			 ,{HIT, HIT, DBL, DBL, HIT, HIT, HIT, HIT, HIT, STD}  // 7
			 ,{STD, DBL, DBL, HIT, HIT, HIT, HIT, SPT, STD, STD}  // 8
			 ,{STD, DBL, HIT, HIT, HIT, HIT, HIT, STD, SPT, STD}  // 9
			 ,{STD, HIT, HIT, HIT, HIT, HIT, STD, STD, STD, STD}} // T
             // ------------------------------------------------------                                                     
			 // A    2    3    4    5    6    7    8    9    T    TEN 
	        ,{{SPT, HIT, HIT, HIT, HIT, HIT, HIT, STD, STD, STD}  // A
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, HIT, HIT, DBL, HIT}  // 2
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, HIT, DBL, HIT, HIT}  // 3
			 ,{HIT, HIT, HIT, HIT, HIT, HIT, DBL, HIT, HIT, HIT}  // 4
			 ,{HIT, HIT, HIT, HIT, HIT, DBL, HIT, HIT, HIT, HIT}  // 5
			 ,{HIT, HIT, HIT, HIT, DBL, HIT, HIT, HIT, HIT, HIT}  // 6
			 ,{HIT, HIT, HIT, DBL, HIT, HIT, HIT, HIT, HIT, STD}  // 7
			 ,{STD, HIT, DBL, HIT, HIT, HIT, HIT, SPT, STD, STD}  // 8
			 ,{STD, DBL, HIT, HIT, HIT, HIT, HIT, STD, STD, STD}  // 9
			 ,{STD, HIT, HIT, HIT, HIT, HIT, STD, STD, STD, STD}} // T
            };


tstrat strategy(int d, int p1, int p2)
{
	int j(p1 < p2 ? p1 : p2);
	int k(p1 < p2 ? p2 : p1);
	return strat[d-1][j-1][k-1];
}

typedef list<int> tdeck;

#if 0
const bool gDebug(false);
#else
bool gDebug(true);
#endif

#define Debug(x) if (gDebug) {x;}

	char print(const tdeck::value_type& aelem)
	{
		if (aelem >= (int)'A')
		{
			return (char)aelem;
		}
		else
		{
			switch (aelem)
			{
			case 1: return 'A';
			case 2: return '2';
			case 3: return '3';
			case 4: return '4';
			case 5: return '5';
			case 6: return '6';
			case 7: return '7';
			case 8: return '8';
			case 9: return '9';
			case 10: return 'T';
			default: return '?';
			}
		}
		return '?';
	}

	void print(const tdeck& adeck, const std::string& aname = "")
	{
		cout << aname << ' ' << adeck.size() << '\n';
		const int decks(adeck.size() / 52);
		tdeck::const_iterator it(adeck.begin());
		for (int i = 0; i < decks; ++i)
		{
			for (int j = 0; j < 52; ++j, ++it)
			{
				cout << print(*it);
			}
			cout << '\n';
		}
		const int leftover(adeck.size() % 52);
		if (leftover > 0)
		{
			for (int j = 0; j < leftover; ++j, ++it)
			{
				cout << print(*it);
			}
			cout << '\n';
		}
	}

double drand()
{
	return (double)rand() / RAND_MAX;
}

int uniform(int amax)
{
	return (int)floor(drand() * amax * 2 + 0.5) - amax;
}

int bell(int amax)
{
	return uniform(amax);
}

int pos_bell(int amax)
{
	return abs(bell(amax));
}

tdeck& blend(tdeck& adeck)
{
	return adeck;
}

tdeck::iterator iter(tdeck& adeck, int pos)
{
	tdeck::iterator it(adeck.begin());
	for (int i = 0; i < pos; ++i, ++it)
		;
	return it;
}

int packet(int rem)
{
	const double r(drand());
	int p(3);
	if (r < 0.66)
		p = 1;
	else if (r < 0.96)
		p = 2;
	return min(rem, p);
}

int offset()
{
	const double r(drand());
	int p(5);
	if (r < 0.40)
		p = 1;
	else if (r < 0.70)
		p = 2;
	else if (r < 0.92)
		p = 3;
	else if (r < 0.98)
		p = 4;
	return (drand() < 0.5) ? p : -p;
}

/// grab a chunk of cards off the top of deck
/// \note the deck is reduced by chunk taken
/// \return the chunk taken
tdeck grab(tdeck& adeck)
{
	const int cards(int(52 * ggrab) + offset());
	tdeck::iterator it(iter(adeck, cards));
	tdeck top(adeck.begin(), it);
	tdeck(it, adeck.end()).swap(adeck);
	return top;
}


/// riffle two decks together into a single deck
/// \note input decks are cleared out
/// \return the interleaved combination of decks
tdeck riffle(tdeck& aleft, tdeck& aright)
{
	tdeck riff;
	while (!aleft.empty() && !aright.empty())
	{
		const int left(packet(aleft.size()));
		for (int i = 0; i < left; ++i)
		{
			riff.push_back(aleft.front());
			aleft.pop_front();
		}
		const int right(packet(aright.size()));
		for (int i = 0; i < right; ++i)
		{
			riff.push_back(aright.front());
			aright.pop_front();
		}
	}
	while (!aleft.empty())
	{
		riff.push_back(aleft.front());
		aleft.pop_front();
	}
	while (!aright.empty())
	{
		riff.push_back(aright.front());
		aright.pop_front();
	}
	return riff;
}

tdeck& box(tdeck& adeck)
{
	for (int i = 0; i < gbox; ++i)
	{
		/// \todo
	}
	return adeck;
}

/// cut a deck and restack
/// \note cuts dissallowed in first & last half decks
/// \note verified
tdeck& cut(tdeck& adeck)
{
	const int loc(rand() % (adeck.size() - 52));
	tdeck::iterator it(iter(adeck, loc + 26));
	tdeck deck(it, adeck.end());
	deck.insert(deck.end(), adeck.begin(), it);
	adeck.swap(deck);
	return adeck;
}

/// cut a deck into two pieces with chance to be unequal
/// \note deck is cleared
/// \note verified
pair<tdeck, tdeck> split(tdeck& adeck)
{
	const int half((adeck.size() / 2) + offset());
	tdeck::iterator it(iter(adeck, half));
	pair<tdeck, tdeck> halves(tdeck(adeck.begin(), it), 
							  tdeck(it, adeck.end()));
	adeck.clear();
	return halves;
}

/// 
void add(tdeck& adeck, const tdeck& aextra)
{
	adeck.insert(adeck.end(), aextra.begin(), aextra.end());
}

/// add to the top of a face down deck
void addtop(tdeck& adeck, const tdeck& aextra)
{
	adeck.insert(adeck.begin(), aextra.begin(), aextra.end());
}

tdeck& shuffle(tdeck& adeck) 
{
	pair<tdeck, tdeck> halves(split(adeck));

	addtop(adeck, box(riffle(grab(halves.first), grab(halves.second))));

	const int reps((int)floor(((double)gdecks / ggrab / 2) + 0.5) - 2);
	for (int i = 0; i < reps; ++i)
	{
		addtop(adeck, box(riffle(grab(halves.first), grab(adeck))));

		addtop(adeck, box(riffle(grab(adeck), grab(halves.second))));
	}
	addtop(adeck, box(riffle(halves.first, grab(adeck))));

	addtop(adeck, box(riffle(grab(adeck), halves.second)));

	return adeck;
}

/// create the original order of cards out of a new box
/// \note A23456789TJQK A23456789TJQK KQJT98765432A KQJT98765432A
void fill(tdeck& adeck)
{
	for (int d = 0; d < gdecks; ++d)
	{
		for (int s = 0; s < 2; ++s)
		{
			for (int c = 1; c < 10; ++c)
			{
				adeck.push_back(c);
			}
			for (int t = 0; t < 4; ++t)
			{
				adeck.push_back(10);
			}
		}
		for (int s = 0; s < 2; ++s)
		{
			for (int t = 0; t < 4; ++t)
			{
				adeck.push_back(10);
			}
			for (int c = 1; c < 10; ++c)
			{
				adeck.push_back(10 - c);
			}
		}
	}
}
	
void check(const tdeck& adeck) 
{
	int tens(0);
	int tens1(0);
	int tens2(0);
	tdeck::const_iterator it(adeck.begin());
	int prev(*it);
	++it;
	for (unsigned i = 0; it != adeck.end(); ++it, ++i)
	{
		if (10 == prev)
		{
			if (10 == *it)
			{
				++tens;
				if (i > (adeck.size() / 2))
					++tens2;
				else
					++tens1;
			}
		}

		prev = *it;
	}
	cout << "tens  " << tens << " " << tens/95.0 << " " << 4/13.0 << '\n';
	cout << "tens1 " << tens1 << " " << tens1/47.0 << " " << 95/311.0 << '\n';
	cout << "tens2 " << tens2 << " " << tens2/47.0 << " " << 95/311.0 << '\n';
	print(adeck, "check");
}

/// is there an ace in the hand
bool soft(const tdeck& ahand)
{
	const int acc(std::accumulate(ahand.begin(), ahand.end(), 0, std::plus<tdeck::value_type>()));

	tdeck::const_iterator it(ahand.begin());
	for (; it != ahand.end(); it++) 
		if (*it == 1) break;

    return (acc <= 11) && (it != ahand.end());
}

/// hand value
/// \note if hand is soft will report the higher sum
int sum(const tdeck& adeck)
{
	int acc(std::accumulate(adeck.begin(), adeck.end(), 0, std::plus<tdeck::value_type>()));
	if (soft(adeck))
		acc += 10;
	return acc;
}

tstrat strategy(int d, const tdeck& ahand)
{
	const int s(sum(ahand));
	tstrat strat(STD);
	if (soft(ahand))
	{
		strat = strategy(d, 1, s - 11);
	}
	else if (s < 12)
	{
		strat = strategy(d, 2, s - 2);
	}
	else
	{
		strat = strategy(d, 10, s - 10 <= 10 ? s - 10 : s - 20);
	}
	
	// correct decisions that only apply to first 2 cards
	if (ahand.size() > 2)
	{
		switch (strat)
		{
		case DBL: strat = HIT; break;
		case SUR: strat = HIT; break;
		case SPT: exit(1); break;
		}
	}
	return strat;
}


/// check if 2 cards are A and T
bool bj(const tdeck& adeck)
{
	return (adeck.size() == 2) 
		    && (sum(adeck) == 21);
}


class ttable
{
public:
	ttable(int aplayers)
		: mplayers(aplayers)
	{
		fill(mdeck);
	}

	void play(int ashoes)
	{
		check(mdeck);
		blend(mdeck);
		check(mdeck);
		for (int i = 0; i < ashoes; ++i)
		{
			shuffle(mdeck);
			cut(mdeck);
			check(mdeck);
			burn();
			while (!done())
				deal();
			combine();
		}
	}

private:


	/// check if dealt beyond the stop card
	bool done() 
	{
		return (mdiscards.size() > (unsigned)gpenetration);
	}

	/// move the hand to discard pile
	/// \note clears hand
	void lose(tdeck& ahand)
	{
		addtop(mdiscards, ahand);
		ahand.clear();
	}

	/// take one card from shoe and add to hand
	void hit(tdeck& ahand)
	{
		ahand.push_front(mdeck.front());
		mdeck.pop_front();
	}

	/// take card from shoe and place into discards
	void burn() 
	{
		mdiscards.push_front(mdeck.front());
		mdeck.pop_front();
	}

	bool hit(const tdeck& ahand, const tdeck::value_type& aup)
	{
		return (HIT == strategy(aup, ahand));
	}

	void play(const int adealer, tdeck& ahand)
	{
		tstrat astrat(strategy(adealer, ahand.front(), ahand.back()));
		if (DBL == astrat)
		{
			hit(ahand);
			if (sum(ahand) > 21)
			{
				lose(ahand);
			}
		}
		else if (HIT == astrat)
		{
			int s(sum(ahand));
			do
			{
				hit(ahand);
				s = sum(ahand);
			}
			while ((s <= 21) && hit(ahand, adealer));
			if (sum(ahand) > 21)
			{
				lose(ahand);
			}
		}
		else if (SUR == astrat)
		{
			lose(ahand);
		}
	}

	void deal() 
	{
		// deal out the hands
		std::list<tdeck> spots(gplayers + 1);
		for (int c = 0; c < 2; c++)
		{
			for (std::list<tdeck>::iterator it = spots.begin(); it != spots.end(); ++it)
			{
				it->push_front(mdeck.front());
				mdeck.pop_front();
			}
		}

		// don't play out hand when dealer blackjack
		if (!bj(spots.back()))
		{
			const int up(spots.back().back());

			std::list<tdeck>::iterator it(spots.begin());
			std::list<tdeck>::iterator next(it);
			++next;
			for (; next != spots.end(); ++it, ++next)
			{
				if (SPT == strategy(up, it->front(), it->back()))
				{
					tdeck first;
					first.push_front(it->front());

					tdeck second;
					second.push_front(it->back());

					tdeck third;
					tdeck fourth;

					if (1 == first.front())
					{
						// can't resplit aces, get 1 card only, can never bust
						hit(first);
						hit(second);
					}
					else
					{
						hit(first);
						if (first.front() == first.back())
						{
							third.push_front(first.front());
							first.pop_front();
							hit(first);
							if (first.front() == first.back())
							{
								fourth.push_front(first.front());
								first.pop_front();
								hit(first);
							}
						}						
						play(up, first);

						hit(second);
						if (second.front() == second.back())
						{
							if (third.empty())
							{
								third.push_front(first.front());
								first.pop_front();
								hit(second);
								if (second.front() == second.back())
								{
									fourth.push_front(first.front());
									first.pop_front();
									hit(second);
								}
							}
							else if (fourth.empty())
							{
								fourth.push_front(first.front());
								first.pop_front();
								hit(second);
							}
						}
						play(up, second);

						if (!third.empty())
						{
							hit(third);
							if ((third.front() == third.back()) && fourth.empty())
							{
								fourth.push_front(third.front());
								third.pop_front();
								hit(third);
							}
							play(up, third);
						}

						if (!fourth.empty())
						{
							hit(fourth);
							play(up, fourth);
						}
					}
					it->clear();
					add(*it, first);
					add(*it, second);
					add(*it, third);
					add(*it, fourth);
				}
				else 
				{
					play(up, *it);
				}
			}

			// play the dealer hand
			while (sum(spots.back()) < 17)
			{
				spots.back().push_front(mdeck.front());
				mdeck.pop_front();
			}
		}

		// hand over, pick up remaining cards 
		for (std::list<tdeck>::iterator it = spots.begin(); it != spots.end(); ++it)
		{
		addtop(mdiscards, *it);
		}
	}

	/// put the leftover slug of cards back together with discards
	void combine() 
	{
		/// \todo usually a different method than just place on top discards
		add(mdiscards, mdeck);
		mdeck.clear();

		mdeck.swap(mdiscards);
	}

	int mplayers;
	tdeck mdeck;
	list<int> mdiscards;
};

int main(int argc, char* argv[])
{
	tdeck rifcheck;
	std::string t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < 52; ++i)
		rifcheck.push_back((int)t[i]);
	print(rifcheck, "Riffle Before");
	pair<tdeck, tdeck> halves(split(rifcheck));
	print(riffle(halves.first, halves.second), "Riffle After");
	std::cout << '\n';

	tdeck cutcheck;
	int i = 0;
	for (; i < 26; ++i)
		cutcheck.push_back((int)'X');
	for (; i < 78; ++i)
		cutcheck.push_back((int)t[i-26]);
	for (; i < 104; ++i)
		cutcheck.push_back((int)'X');
	print(cutcheck, "Cut Before");
	cut(cutcheck);
	print(cutcheck, "Cut Before");
	std::cout << '\n';

	ttable table(gplayers);
	table.play(gshoes);

    return 0;
}
