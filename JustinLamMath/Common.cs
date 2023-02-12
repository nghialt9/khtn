using System;

namespace JustinLamMath
{
    public static class Common
    {
        /// <summary>
        /// Returns the sum from 1 to number 
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static long PlusFromNumbers (long number)
        {
            long sum = 0;

            for (long i = 1; i <= number; i++)
            {
                sum += i;
            }

            return sum;
        }

        /// <summary>
        /// Return the sum  from square of 1 to square of number
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static long PlusFromSquares(long number)
        {
            long sum = 0;

            for (long i = 1; i <= number; i++)
            {
                sum += i*i;
            }

            return sum;
        }

        /// <summary>
        /// Returns the sum of the results of the divisions 1/n and 1/nn
        /// </summary>
        /// <param name="number"></param>
        /// <param name="multiplier"></param>
        /// <returns></returns>
        public static double PlusFromDivisions(long number, int multiplier = 1)
        {
            double sum = 0;

            for (double i = 1; i <= number; i++)
            {
                sum += 1 / (i * multiplier);
            }

            return sum;
        }

        /// <summary>
        /// Returns the sum of the results of the divisions 1/(2n + 1)
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static double PlusFromDivisionsPlus(long number)
        {
            double sum = 0;

            for (double i = 1; i <= number; i++)
            {
                sum += 1 / (2 * i + 1);
            }

            return sum;
        }

        /// <summary>
        /// Returns the sum of the results of the divisions 1/(n * (n + 1))
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static double PlusFromDivisionsMultiply(long number)
        {
            double sum = 0;

            for (double i = 1; i <= number; i++)
            {
                sum += 1 / (i * (i + 1));
            }

            return sum;
        }

        /// <summary>
        /// Returns the sum of the results of the divisions n/(n + 1)
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static double PlusFromDivisionsOfNumber(long number)
        {
            double sum = 0;

            for (double i = 1; i <= number; i++)
            {
                sum += i / (i + 1);
            }

            return sum;
        }

        /// <summary>
        /// Returns the sum of the results of the divisions (2n + 1) / (2n + 2)
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static double PlusFromDivisionsOfNumbers(long number)
        {
            double sum = 0;

            for (double i = 1; i <= number; i++)
            {
                sum += (2 * i + 1) / (2 * i + 2);
            }

            return sum;
        }

        /// <summary>
        /// Returns the sum of the results of factorial n!
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static double PlusFromFactorial(long number)
        {
            double sum = 1;

            for (double i = 1; i <= number; i++)
            {
                sum *= i;
            }

            return sum;
        }

        /// <summary>
        /// Return the squares
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static long Squares(long number, long square)
        {
            long sum = 1;

            for (long i = 1; i <= square; i++)
            {
                sum *= number;
            }

            return sum;
        }

        /// <summary>
        /// Return the sum from recursive
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static long PlusFromRecursive(long number)
        {
            long sum = 0;
            
            for (int i = 1; i <= number; i++)
            {
                long product = 1;

                for (int j = 1; j <= i; j++)
                {
                    product *= j;
                }

                sum += product;              
            }

            return sum;
        }
        
        /// <summary>
        /// Return the sum from exponential
        /// </summary>
        /// <param name="number"></param>
        /// <param name="exponential"></param>
        /// <returns></returns>
        public static long PlusFromExponential(long number, long exponential, long n = 1)
        {
            long sum = 0;
            
            for (int i = 1; i <= exponential ; i++)
            {
                long product = 1;

                for (int j = 1; j <= i * n; j++)
                {                  
                    product *= number;
                }

                sum += product;
            }

            return sum;
        }

        /// <summary>
        /// Return the sum from exponential
        /// </summary>
        /// <param name="number"></param>
        /// <param name="exponential"></param>
        /// <returns></returns>
        public static long PlusFromExponentials(long number, long exponential)
        {
            long sum = 0;

            for (int i = 0; i < exponential; i++)
            {
                long product = 1;

                for (int j = 1; j <= i * 2 + 1; j++)
                {
                    product *= number;
                }

                sum += product;
            }

            return sum;
        }

        /// <summary>
        /// Returns the sum of the results of the divisions 1/(1+2+3...n)
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public static double PlusFromDivisionsSum(long number)
        {
            double sum = 0;

            for (double i = 1; i <= number; i++)
            {
                double total = 0;
                for (int j = 1; j <= i; j++)
                {
                    total += j;
                }

                sum += 1 / total;
            }

            return sum;
        }
    }
}
