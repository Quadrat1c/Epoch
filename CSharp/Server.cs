using System.IO;
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
            writer.WriteLine(@"___________                    .__     ");
            writer.WriteLine(@"\_   _____/_____   ____   ____ |  |__  ");
            writer.WriteLine(@" |    __)_\____ \ /  _ \_/ ___\|  |  \ ");
            writer.WriteLine(@" |        \  |_> >  <_> )  \___|   Y  \");
            writer.WriteLine(@"/_______  /   __/ \____/ \___  >___|  /");
            writer.WriteLine(@"        \/|__|               \/     \/ ");
            // get clients ip address

            // command loop - swtch
            for (string line = reader.ReadLine(); line != null; line = reader.ReadLine())
            {
                switch (line)
                {
                    case "test":
                        writer.WriteLine("[CB} Test");
                        break;

                    case "exit":
                        break;

                    default:
                        writer.WriteLine("Unknown Command: " + line);
                        break;
                }
            }
        }
    }
}
