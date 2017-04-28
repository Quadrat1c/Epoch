using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading;

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
    }
}
