using System;
using BASE = uint;

namespace BigNum
{
    class BigNumber
    {
        public static int BASE_SIZE = (sizeof(BASE) * 8);
        internal int sign;
        internal BASE[] coeff;
        public int maxLen; 
        public BigNumber() : this(1)
        { }
        public BigNumber(int MaxLen)
        {
            maxLen = MaxLen;
            coeff = new BASE[maxLen];
            for(int i = 0; i < maxLen; i++)
                coeff[i] = 0;
        }
        public BigNumber(int MaxLen, bool flag)
        {
            maxLen = MaxLen;
            coeff = new BASE[maxLen];
            Random rand = new Random();
            for(int i = 0; i < maxLen; i++)
            {
                coeff[i] = (BASE)rand.Next((int)(-Math.Pow(2, (int)(BASE_SIZE - 2))),(int)(Math.Pow(2, (int)(BASE_SIZE - 2))));
                Console.WriteLine(coeff[i]);
            }    
        }

        public BigNumber(BigNumber bigNumber)
        {
            maxLen = bigNumber.maxLen;
            sign = bigNumber.sign;
            coeff = new BASE[maxLen];
            for(int i = 0; i < maxLen; i++)
                coeff[i] = bigNumber.coeff[i];
        }
        ~BigNumber()
        {
            Array.Clear(coeff, 0, maxLen);
            coeff = null;
        }
        static void Main()
        {
            BigNumber bigNumber = new BigNumber(10, false);
            BigNumber Big = new BigNumber(bigNumber);
            //Console.WriteLine(BASE_SIZE);
        }
    }
    
}