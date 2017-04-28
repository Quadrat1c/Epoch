using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace Epoch
{
    class Program
    {
        static void Main(string[] args)
        {
            // Start TCP Server
            Console.WriteLine("Epoch Server");
            TcpListener listener = new TcpListener(IPAddress.Any, 1337);
            listener.Start();

            while (true)
            {
                TCPServer handler = new TCPServer(listener.AcceptTcpClient());
                Thread thread = new Thread(new ThreadStart(handler.Run));
                thread.Start();
            }
        }
    }
}
