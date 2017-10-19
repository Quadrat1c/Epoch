using System;
using System.Security.Cryptography;

namespace QuadKeyExchange
{
    public class Crypto
    {
        private static RNGCryptoServiceProvider rngCsp = new RNGCryptoServiceProvider();

        /// <summary>
        /// Demo of a full ekey exchange between two people.
        /// </summary>
        public static void KeyExchange()
        {
            //      n              g              x              a             y              b               
            long oneFirstPrime, twoFirstPrime, onePrivateKey, onePublicKey, twoPrivateKey, twoPublicKey;


            // Info
            Console.WriteLine("\n\rFull Key Exchange Demo");
            Console.WriteLine("This demo will show a full exchange between two people.\n\r");

            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("First Person will be Red.");
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.WriteLine("First Person's non public secrets will be Dark Red.\n\r");

            Console.ForegroundColor = ConsoleColor.Blue;
            Console.WriteLine("Second Person will be Blue.");
            Console.ForegroundColor = ConsoleColor.DarkBlue;
            Console.WriteLine("Second Person's non public secrets will be Dark Red.\n\r");

            Console.ResetColor();

            Console.Write("\r\n--------------- Step 1 ---------------\r\n");
            Console.WriteLine("First person creates a random Prime (n)");
            Console.ForegroundColor = ConsoleColor.Red;
            oneFirstPrime = CreatePrime(true);
            Console.ResetColor();

            Console.WriteLine("Second person creates a random Prime (g)");
            Console.ForegroundColor = ConsoleColor.Blue;
            twoFirstPrime = CreatePrime(true);
            Console.ResetColor();

            Console.Write("\r\n--------------- Step 2 ---------------\r\n");
            Console.WriteLine("First person will create their Secret Key (x)");
            Console.ForegroundColor = ConsoleColor.DarkRed;
            onePrivateKey = CreatePrime(true);
            Console.ResetColor();

            Console.WriteLine("Second person will create  their Secret Key (y)");
            Console.ForegroundColor = ConsoleColor.DarkBlue;
            twoPrivateKey = CreatePrime(true);
            Console.ResetColor();

            Console.Write("\r\n--------------- Step 3 ---------------\r\n");
            Console.WriteLine("First person will now use his private key to create a Public Key (a)");
            Console.WriteLine("power(g, x, n) [secondPersons first prime], [first persons private key], [first persons first prime]");
            onePublicKey = power(twoFirstPrime, onePrivateKey, oneFirstPrime);
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine($"Public Key: {onePublicKey}");
            Console.ResetColor();

            Console.WriteLine("Second person will now use his private key to create a Public Key (b)");
            Console.WriteLine("power(g, y, n) [second persons first prime], [second persons private key], [first persons first prime]");
            twoPublicKey = power(twoFirstPrime, twoPrivateKey, oneFirstPrime);
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.WriteLine($"Public Key: {twoPublicKey}");
            Console.ResetColor();

            Console.Write("\r\n--------------- Step 5 ---------------\r\n");
            Console.WriteLine("First person creates final secret key.");
            Console.WriteLine("power(b, x, n) [second persons public key], [first persons private key], [first persons first prime]");
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.WriteLine("First persons key: {0}", power(twoPublicKey, onePrivateKey, oneFirstPrime));
            Console.ResetColor();

            Console.WriteLine("Second person creates final secret key.");
            Console.WriteLine("power(a, y, n) [first persons public key], [second persons private key], [first persons first prime]");
            Console.ForegroundColor = ConsoleColor.DarkBlue;
            Console.WriteLine("First persons key: {0}", power(onePublicKey, twoPrivateKey, oneFirstPrime));
            Console.ResetColor();
        }


        public static void KeyExchangeStressTest(long tries)
        {
            Console.WriteLine("Key Exchange Stress Test");
            for (int i = 1; i < tries + 1; i++)
            {
                Console.ForegroundColor = ConsoleColor.Green;
                long oneFirstPrime, twoFirstPrime, onePrivateKey, onePublicKey, twoPrivateKey, twoPublicKey, oneFinal, twoFinal;

                oneFirstPrime = CreatePrime(false);
                twoFirstPrime = CreatePrime(false);

                onePrivateKey = CreatePrime(false);
                twoPrivateKey = CreatePrime(false);

                onePublicKey = power(twoFirstPrime, onePrivateKey, oneFirstPrime);
                twoPublicKey = power(twoFirstPrime, twoPrivateKey, oneFirstPrime);

                oneFinal = power(twoPublicKey, onePrivateKey, oneFirstPrime);
                twoFinal = power(onePublicKey, twoPrivateKey, oneFirstPrime);

                if (oneFinal == twoFinal)
                {
                    Console.Write($"Exchanges: {i}/{tries}");
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.Write($" [{oneFinal}] ");
                    Console.ForegroundColor = ConsoleColor.Blue;
                    Console.Write($" [{twoFinal}] \r\n");
                }
                else
                {
                    Console.BackgroundColor = ConsoleColor.DarkRed;
                    Console.ForegroundColor = ConsoleColor.Magenta;
                    Console.WriteLine("***FAILED***");
                    Console.ResetColor();
                    Console.ForegroundColor = ConsoleColor.Magenta;
                    Console.WriteLine($"Exchanges: {i}/{tries}");
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"Key1: {oneFinal}");
                    Console.ForegroundColor = ConsoleColor.Blue;
                    Console.WriteLine($"Key2: {twoFinal}");
                    break;
                }
            }
        }

        /// <summary>
        /// Compute power.
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <param name="mod"></param>
        /// <returns></returns>
        private static long power(long a, long b, long mod)
        {
            long t;

            if (b == 1)
                return a;

            t = power(a, b / 2, mod);

            if (b % 2 == 0)
                return (t * t) % mod;
            else
                return (((t * t) % mod) * a) % mod;
        }

        /// <summary>
        /// Creates a Random Prime Number.
        /// </summary>
        /// <returns></returns>
        private static long CreatePrime(bool debug)
        {
            bool stop = false;
            int count = 0;

            do
            {
                count++;

                // Generate a random number.
                string generation = CryptoRNG(0x09).ToString() + CryptoRNG(0x09).ToString()
                                  + CryptoRNG(0x09).ToString() + CryptoRNG(0x09).ToString()
                                  + CryptoRNG(0x09).ToString() + CryptoRNG(0x09).ToString();
                long randomNumber = Convert.ToInt64(generation);

                // Check if our random number is prime.
                if (IsPrime(randomNumber))
                {
                    if (debug)
                    {
                        Console.WriteLine($"Count: {count}");
                        Console.WriteLine($"PRIME: {randomNumber}");
                    }

                    return randomNumber;
                }
            }
            while (!stop);

            throw new ArgumentException("We should not have made it here.");
        }

        /// <summary>
        /// This is magic. Don't worry.
        /// </summary>
        /// <param name="max"></param>
        /// <returns></returns>
        private static byte CryptoRNG(byte max)
        {
            if (max <= 0)
                throw new ArgumentOutOfRangeException("max byte");

            // Create a byte array to hold the random value.
            byte[] randomNumber = new byte[1];
            do
            {
                // Fill the array with a random value.
                rngCsp.GetBytes(randomNumber);
            }
            while (!IsRandom(randomNumber[0], max));

            // Return the random number mod the number of sides.
            // The possible values are zero-based, so we add one.
            return (byte)((randomNumber[0] % max) + 1);
        }

        /// <summary>
        /// Takes in a number and checks if its prime.
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        private static bool IsPrime(long number)
        {
            if ((number & 1) == 0)
                return (number == 2);

            long limit = (long)Math.Sqrt(number);

            for (int i = 3; i <= limit; i += 2)
            {
                if ((number % i) == 0)
                    return false;
            }

            return true;
        }

        /// <summary>
        /// takes in a number and max byte then
        /// checks if a number is really random.
        /// </summary>
        /// <param name="number"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        private static bool IsRandom(byte number, byte max)
        {
            // MaxValue / max full sets of numbers,
            // if we have 6 max there are 42 full sets of 1-6.
            // The 43rd set is incomplete.
            int fullSetsOfValues = Byte.MaxValue / max;

            // If its within range of random values, then we return.
            return number < max * fullSetsOfValues;
        }
    }
}
