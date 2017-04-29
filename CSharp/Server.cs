using System;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace Epoch
{
    public class TCPServer
    {
        TcpClient client;
        NetworkStream stream;
        StreamReader reader;
        StreamWriter writer;

        public TCPServer(TcpClient client)
        {
            this.client = client;
            stream = client.GetStream();
            reader = new StreamReader(stream);
            writer = new StreamWriter(stream);
            writer.NewLine = "\r\n";
            writer.AutoFlush = true;
        }

        public void Run()
        {
            writer.WriteLine(cmd.intro());

            // get clients ip address
            string clientIp = ((IPEndPoint)client.Client.RemoteEndPoint).Address.ToString();
            Console.WriteLine("New Connection: " + clientIp);

            // command loop - swtch
            for (string line = reader.ReadLine(); line != null; line = reader.ReadLine())
            {
                switch (line)
                {
                    // [Main]
                    case "test":
                        writer.WriteLine("[CB} Test");
                        Console.WriteLine("[test:" + clientIp + "}");
                        break;

                    case "help":
                        writer.WriteLine(cmd.help());
                        Console.WriteLine("[help:" + clientIp + "}");
                        break;

                    case "about":
                        writer.WriteLine(cmd.about());
                        Console.WriteLine("[about:" + clientIp + "}");
                        break;

                    case "ver":
                        writer.WriteLine(cmd.version());
                        Console.WriteLine("[ver:" + clientIp + "}");
                        break;

                    default:
                        writer.WriteLine("Unknown Command: " + line);
                        Console.WriteLine("[UC:" + clientIp + "} " + line);
                        break;
                }
            }
        }
    }
}
