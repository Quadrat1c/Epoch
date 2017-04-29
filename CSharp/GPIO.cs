using Raspberry.IO.GeneralPurpose;

namespace Epoch
{
    public class GPIO
    {
        public static void blinkLed()
        {
            var led1 = ConnectorPin.P1Pin22.Output();

            var connection = new GpioConnection(led1);

            for (var i = 0; i < 100; i++)
            {
                // toggle
                connection.Toggle(led1);
                System.Threading.Thread.Sleep(250);
            }

            connection.Close();
        }
    }
}
