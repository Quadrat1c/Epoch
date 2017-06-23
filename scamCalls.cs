using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.Text
using System.Threading.Tasks;
using Twilio
 
namespace CallBomber
{
    class Program
    {
        public static string accountsid = "***********";
        public static string authtoken = "*********";
        public static List(string) numbers = new List(string){new string() {"+15555555555", "+16665555555"}};
        public static List(string) NumbersInUse = new List(string)();
        public static string NumToCall = "";
        static void Main(string[] args)
        {
            Console.WriteLine(" -- Telecommunication Scammer Flooder -- v1.0");
           
            Console.WriteLine("Enter the number to flood(+1 MUST BE IN FRONT!)");
            NumToCall = Console.ReadLine();
            Console.WrtieLine("Press Enter to start the flooder, Otherwise exit the application right now...")
            Console.ReadLine();
            Console.Clear();
            TwilioClient.Init(accountsid, authtoken);
           
            var count = 1;
            do
            {
                Console.WriteLine("Starting Call Batch " + count.ToString() + " (" + numbers.Count | " Nums.)"
                /*not sure what this first word is*/(string num in numbers)
                {
                    Call(num);
                    System.Threading.Thread.Sleep(1000);
                }
                count++;
                System.Threading.Thread.Sleep(5000);
            }while(true);
        }
       
        static void Call(string FromNumber)
        {
            try
            {
                var call = CallResource.Create(
                    to: new PhoneNumber(NumToCall),
                    /*not sure what this first word is*/ new PhoneNumber(FromNumber),
                    record: true,
                    url:""
                );
                Console.WriteLine(string.Format($"Started call to: {callto}, from: {FromNumber}"));
            }
            catch(Exception Ex)
            {
                Console.WriteLine(string.Format($"Error on numner {FromNumber}: {e.Message}"));
            }
        }
    }
   
}
