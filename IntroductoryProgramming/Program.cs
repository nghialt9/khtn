using JustinLamMath;
using System;

namespace IntroductoryProgramming
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(Common.PlusFromNumbers(5)); // 1
            Console.WriteLine(Common.PlusFromSquares(5)); // 2
            Console.WriteLine(Common.PlusFromDivisions(5)); // 3
            Console.WriteLine(Common.PlusFromDivisions(5, 2)); // 4
            Console.WriteLine(Common.PlusFromDivisionsPlus(5)); // 5
            Console.WriteLine(Common.PlusFromDivisionsMultiply(5)); // 6
            Console.WriteLine(Common.PlusFromDivisionsOfNumber(5)); // 7
            Console.WriteLine(Common.PlusFromDivisionsOfNumbers(5)); // 8
            Console.WriteLine(Common.PlusFromFactorial(5)); // 9
            Console.WriteLine(Common.Squares(2, 5)); // 10
            Console.WriteLine(Common.PlusFromRecursive(5)); // 11
            Console.WriteLine(Common.PlusFromExponential(2, 5)); // 12
            Console.WriteLine(Common.PlusFromExponential(2, 3, 2)); // 13
            Console.WriteLine(Common.PlusFromExponentials(2, 3)); // 14
            Console.WriteLine(Common.PlusFromDivisionsSum(5)); // 12

        }
    }
}
