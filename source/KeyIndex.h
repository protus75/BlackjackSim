#ifndef KEY_INDEX
#define KEY_INDEX

namespace BJ
{

    typedef int Key;
    typedef int Index;
    
    const int EXIST_A(0x80000000);
    const int EXIST_2(0x40000000);
    const int EXIST_3(0x20000000);
    const int EXIST_4(0x10000000);
    const int EXIST_5(0x08000000);
    const int EXIST_6(0x04000000);
    const int EXIST_7(0x02000000);
    const int EXIST_8(0x01000000);
    const int EXIST_9(0x00800000);
    const int EXIST_T(0x00400000);
    const int EXIST[11] = {0, EXIST_A, EXIST_2, EXIST_3, EXIST_4, EXIST_5, EXIST_6, EXIST_7, EXIST_8, EXIST_9, EXIST_T};
    
    const int COUNT_A(0x00300000);
    const int COUNT_2(0x000C0000);
    const int COUNT_3(0x00030000);
    const int COUNT_4(0x0000C000);
    const int COUNT_5(0x00003000);
    const int COUNT_6(0x00000C00);
    const int COUNT_7(0x00000300);
	const int COUNT_8(0x000000C0);
	const int COUNT_9(0x00000030);
    const int COUNT_T(0x0000000F);
    const int COUNT[11] = {0, COUNT_A, COUNT_2, COUNT_3, COUNT_4, COUNT_5, COUNT_6, COUNT_7, COUNT_8, COUNT_9, COUNT_T};
    
    const int SHIFT_A(20);
    const int SHIFT_2(18);
    const int SHIFT_3(16);
    const int SHIFT_4(14);
    const int SHIFT_5(12);
    const int SHIFT_6(10);
    const int SHIFT_7(08);
    const int SHIFT_8(06);
    const int SHIFT_9(04);
    const int SHIFT_T(00);
    const int SHIFT[11] = {0, SHIFT_A, SHIFT_2, SHIFT_3, SHIFT_4, SHIFT_5, SHIFT_6, SHIFT_7, SHIFT_8, SHIFT_9, SHIFT_T};
    
    const int ONE_A(0b00000000000100000000000000000000);
    const int ONE_2(0b00000000000001000000000000000000);
    const int ONE_3(0b00000000000000010000000000000000);
    const int ONE_4(0b00000000000000000100000000000000);
    const int ONE_5(0b00000000000000000001000000000000);
    const int ONE_6(0b00000000000000000000010000000000);
    const int ONE_7(0b00000000000000000000000100000000);
    const int ONE_8(0b00000000000000000000000001000000);
    const int ONE_9(0b00000000000000000000000000010000);
    const int ONE_T(0b00000000000000000000000000000001);
    const int ONE[11] = {0, ONE_A, ONE_2, ONE_3, ONE_4, ONE_5, ONE_6, ONE_7, ONE_8, ONE_9, ONE_T};
    
    const int OFFSET_A(5);
    const int OFFSET_2(5*5);
    const int OFFSET_3(5*5*5);
    const int OFFSET_4(5*5*5*5);
    const int OFFSET_5(5*5*5*5*5);
    const int OFFSET_6(5*5*5*5*5*5);
    const int OFFSET_7(5*5*5*5*5*5*5);
    const int OFFSET_8(5*5*5*5*5*5*5*5);
    const int OFFSET_9(5*5*5*5*5*5*5*5*5);
    const int OFFSET_T(5*5*5*5*5*5*5*5*5*5);
    const int OFFSET[11] = {0, OFFSET_A, OFFSET_2, OFFSET_3, OFFSET_4, OFFSET_5, OFFSET_6, OFFSET_7, OFFSET_8, OFFSET_9, OFFSET_T};
    
    
    bool Exists(const int aCard, const Key aKey)
    {
        return EXIST[aCard] & aKey; 
    }
    
    int Count(const int aCard, const Key aKey, const int aZero = 0)
    {
        return Exists(aCard,aKey) ? ((COUNT[aCard] & aKey) >> SHIFT[aCard]) + 1: aZero;
    }
    
    int KeyFromIndex(const Index aIndex)
    {
        /// \todo
    }
    
    int IndexFromKey(const Key aKey)
    {
        int index(0);
        for (int i = 1; i < 10; ++i)
        {
            index += OFFSET[i] * Count(i,aKey,5);
        }
        index += OFFSET[10] * Count(10,aKey,17);
        return index; 
    }
    
    void Add(const int aCard, Key& aKey)
    {
        if (!Exists(aCard, aKey))
        {
            aKey = aKey & ~COUNT[aCard];
            aKey = aKey | EXIST[aCard];
        }
        else
        {
            aKey += ONE[aCard];
        }
    }
    
    void Sub(const int aCard, Key& aKey)
    {
        if (Count(aCard,aKey) == 1)
        {
            aKey = aKey & ~EXIST[aCard];
        }
        aKey -= ONE[aCard];
    }

    int CardsFromKey(const Key aKey)
    {
        int cards(0);
        for (int i = 1; i <= 10; ++i)
        {
            cards += Count(i,aKey);
        }
        return cards; 
    }
}
#endif
