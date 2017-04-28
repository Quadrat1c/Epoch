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
            writer.WriteLine(cmd.intro());
            // get clients ip address

            // command loop - swtch
            for (string line = reader.ReadLine(); line != null; line = reader.ReadLine())
            {
                switch (line)
                {
                    // [Main]
                    case "test":
                        writer.WriteLine("[CB} Test");
                        break;

                    case "help":
                        writer.WriteLine(cmd.help());
                        break;

                    case "about":
                        writer.WriteLine(cmd.about());
                        break;

                    case "ver":
                        writer.WriteLine(cmd.version());
                        break;

                    default:
                        writer.WriteLine("Unknown Command: " + line);
                        break;
                }
            }
        }
    }
}
