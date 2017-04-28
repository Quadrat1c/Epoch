namespace Epoch
{
    public class cmd
    {
        public static string version()
        {
            return "0.1";
        }

        public static string intro()
        {
            return @"___________                    .__     " + "\r\n" +
                @"\_   _____/_____   ____   ____ |  |__   " + "\r\n" +
                @" |    __)_\____ \ /  _ \_/ ___\|  |  \  " + "\r\n" +
                @" |        \  |_> >  <_> )  \___|   Y  \ " + "\r\n" +
                @"/_______  /   __/ \____/ \___  >___|  / " + "\r\n" +
                @"        \/|__|               \/     \/  " + "\r\n" + "\r\n" +
                "ECNN-QCP (Epoch) " + version()  + " - Type `help` for a list of commands." + "\r\n";
            //return intro;
        }

        public static string about()
        {
            return "Epoch the beginning of a distinctive period of history of someone or something." + "r\n" +
                "";
        }

        public static string help()
        {
            return "\r\n" +
                " [Main] \r\n" +
                "   help  - Displays a list of commands. \r\n" +
                "   about - Displays information about (Epoch) \r\n" +
                "   ver   - Displays version history \r\n" +
                "\r\n" +
                " [Network] \r\n" +
                "\r\n" +
                " [Data] \r\n" +
                "\r\n" +
                " [Crypto] \r\n" +
                "\r\n" +
                " [AI] \r\n" +
                "\r\n" +
                " [Algotelli] \r\n" +
                "\r\n" +
                " [Warden] \r\n";
        }

        public static string history()
        {
            return "ECNN-QCP (Epoch) " + version() + " - Type `help` for a list of commands." + "\r\n" +
                "[0.1.2] Beginning platform \r\n";
        }
    }
}
