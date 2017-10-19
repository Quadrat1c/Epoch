using System;

namespace QuadKeyExchange
{
    class Program
    {
        static void Main(string[] args)
        {
            // Key Exchange Stress Test
            Console.Write("Input number of exchanges: ");
            long tries = Convert.ToInt64(Console.ReadLine());
            crypto.KeyExchangeStressTest(tries);

            Console.ReadLine();

            // Key Exchange Demo
            Console.BackgroundColor = ConsoleColor.Green;
            Console.ForegroundColor = ConsoleColor.Black;
            Console.WriteLine("Quad Encryption Demo");
            Console.ResetColor();
            crypto.KeyExchange();

            Console.ReadLine();
        }
    }
}
