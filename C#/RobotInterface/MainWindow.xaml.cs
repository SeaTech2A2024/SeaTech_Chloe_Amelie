using ExtendedSerialPort_NS;
using System.CodeDom;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Security.RightsManagement;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace RobotInterface
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ExtendedSerialPort serialPort1;
        DispatcherTimer timerAffichage;
        Robot robot = new Robot();

        byte checksum;
       
        


        public MainWindow()
        {

            InitializeComponent();
            serialPort1 = new ExtendedSerialPort("COM21", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();




            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick;
            timerAffichage.Start();

        }

        private void TimerAffichage_Tick(object? sender, EventArgs e)
        {
            //if (robot.receivedText != "")
            //{
            //    textBoxReception.Text += robot.receivedText;
            //    robot.receivedText = "";
            //}
            while (robot.byteListReceived.Count > 0)
            {
                byte b = robot.byteListReceived.Dequeue();
                //textBoxReception.Text += b.ToString() + " ";
                //textBoxReception.Text += "0x" + b.ToString("X2") + " ";
                DecodeMessage(b);
            }
                
        }

        private void SerialPort1_DataReceived(object? sender, DataReceivedArgs e)
        {
            robot.receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
            for (int i = 0; i < e.Data.Length; i++)
            {
                robot.byteListReceived.Enqueue(e.Data[i]);
            }

        }

        
        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void sendMessage()
        {
            //textBoxReception.Text += "Reçu : " + textBoxEmission.Text + "\n";
            serialPort1.WriteLine(textBoxEmission.Text + "\n");
            textBoxEmission.Text = string.Empty;
        }


        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            if (buttonEnvoyer.Background == Brushes.RoyalBlue)
            {
                buttonEnvoyer.Background = Brushes.Beige;
            }
            else
                buttonEnvoyer.Background = Brushes.RoyalBlue;

            sendMessage();

        }

        private void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            textBoxReception.Text = "";
        }

        private void buttonTest_Click(object sender, RoutedEventArgs e)
        {
            //Test1
            //byte[] byteList = new byte[20];
            //for (int i = 0; i < byteList.Length; i++)
            //{
            //    byteList[i] = (byte)(2 * i);
            //}
            //serialPort1.Write(byteList, 0, byteList.Length);


            //Test2
            //string s = "Bonjour";
            //byte[] array = Encoding.ASCII.GetBytes(s);
            //UartEncodeAndSendMessage(0x0080, array.Length, array);

            //Test3
            string toto = "coucou";
            byte[] lolo = Encoding.ASCII.GetBytes(toto);
            UartEncodeAndSendMessage((int)Commands.Texte, lolo.Length, lolo);
            UartEncodeAndSendMessage((int)Commands.Led, 2, new byte[] { 2, 1 });
            UartEncodeAndSendMessage((int)Commands.TelemetreIR, 3, new byte[] { 40, 30, 25});
            UartEncodeAndSendMessage((int)Commands.Speed, 2, new byte[] { 65, 15 });
            

        }

        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                sendMessage();
            }
        }

        byte CalculateChecksum(int msgFunction, int msgPayloadLength, byte[] msgPayload)
        {
            checksum = 0;
            checksum ^= 0xFE;
            checksum ^=(byte)(msgFunction >> 8);
            checksum ^= (byte)(msgFunction >> 0);
            checksum ^= (byte)(msgPayloadLength >> 8);
            checksum ^= (byte)(msgPayloadLength >> 0);
            for (int i = 0; i < msgPayloadLength; i++)
            {
                checksum ^= msgPayload[i];
            }
            return checksum;
        }

        void UartEncodeAndSendMessage(int msgFunction, int msgPayloadLength, byte[] msgPayload)
        {
            byte[] msgUart = new byte[msgPayloadLength + 6];
            int pos = 0;
            msgUart[pos++] = (byte)(0xFE);
            msgUart[pos++] = (byte)(msgFunction >> 8); 
            msgUart[pos++] = (byte)(msgFunction >> 0);
            msgUart[pos++] = (byte)(msgPayloadLength >> 8); 
            msgUart[pos++] = (byte)(msgPayloadLength >> 0);
            for (int i = 0; i < msgPayloadLength ; i++)
            {
                msgUart[pos++] = msgPayload[i];
            }
            msgUart[pos++] = (byte)(CalculateChecksum( msgFunction, msgPayloadLength, msgPayload));
            serialPort1.Write(msgUart, 0, pos);

        }

        public enum StateReception
        {
            Waiting,
            FunctionMSB,
            FunctionLSB,
            PayloadLengthMSB,
            PayloadLengthLSB,
            Payload,
            CheckSum
        }
        StateReception rcvState = StateReception.Waiting;
        int msgDecodedFunction = 0;
        int msgDecodedPayloadLength = 0;
        byte[] msgDecodedPayload;
        int msgDecodedPayloadIndex = 0;
        private void DecodeMessage(byte c)
        {

            switch (rcvState)
            {
                case StateReception.Waiting:
                    if(c==0xFE)
                        rcvState = StateReception.FunctionMSB;
                    break;
                case StateReception.FunctionMSB:
                    msgDecodedFunction = c << 8;
                    rcvState = StateReception.FunctionLSB;
                    break;
                case StateReception.FunctionLSB:
                    msgDecodedFunction |= c << 0;
                    rcvState |= StateReception.PayloadLengthMSB;
                    break;
                case StateReception.PayloadLengthMSB:
                    msgDecodedPayloadLength = c << 8;
                    rcvState = StateReception.PayloadLengthLSB;

                    break;
                case StateReception.PayloadLengthLSB:
                    msgDecodedPayloadLength |= c << 0;
                    rcvState |= StateReception.Payload;

                    if (msgDecodedPayloadLength == 0)
                        rcvState = StateReception.CheckSum;
                    else if (msgDecodedPayloadLength >= 256)
                        rcvState = StateReception.Waiting;
                    else
                    {
                        rcvState = StateReception.Payload;
                        msgDecodedPayloadIndex = 0;
                        msgDecodedPayload = new byte[msgDecodedPayloadLength];
                    }
                    break;
                case StateReception.Payload:
                    msgDecodedPayload[msgDecodedPayloadIndex] = c;
                    msgDecodedPayloadIndex++;
                    if (msgDecodedPayloadIndex >= msgDecodedPayloadLength)
                        rcvState = StateReception.CheckSum;
                    break;
                case StateReception.CheckSum:
                    byte receivedChecksum = c;
                    byte calculatedChecksum = CalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);

                    if (calculatedChecksum == receivedChecksum)
                    {
                        //Success, on a un message valide
                        ProcessDecodedMessage(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
                        rcvState = StateReception.Waiting;
                        Debug.WriteLine("Youpi!");

                    }
                    else
                    {
                        rcvState = StateReception.Waiting;
                        //Debug.WriteLine("Mince !");
                    }
                    break;
                default:
                    rcvState = StateReception.Waiting;
                    break;
            }
        }

        void ProcessDecodedMessage(int msgFunction, int msgPayloadLength, byte[] msgPayload)
        {
            switch (msgFunction)
            {
                case (int)Commands.Texte:
                    textBoxReception.Text += " ";
                    for (int i = 0; i < msgPayloadLength; i++)
                    {
                        byte b = msgPayload[i];
                        textBoxReception.Text += b.ToString("X2") + " ";
                    }
                    break;

                case (int)Commands.Led:
                    CheckBoxRouge.IsChecked =false;
                    CheckBoxBleue.IsChecked = false;
                    CheckBoxBlanche.IsChecked = false;

                    switch (msgPayload[0])
                    {
                        case 1:
                            CheckBoxRouge.IsChecked = (msgPayload[1] == 1);
                            break;
                        case 2:
                            CheckBoxBleue.IsChecked = (msgPayload[1] == 1);
                            break;
                        case 3:
                            CheckBoxBlanche.IsChecked = (msgPayload[1] == 1);
                            break;
                    }
                   
                    break;

                case (int)Commands.TelemetreIR:
                    LabelIRG.Content = msgPayload[0] + "cm";
                    LabelIRC.Content = msgPayload[1] + "cm";
                    LabelIRD.Content = msgPayload[2] + "cm";
                    break;

                case (int)Commands.Speed:
                    LabelVG.Content = msgPayload[0] + "%";
                    LabelVC.Content = msgPayload[1] + "%";
                    break;
                
                default:
                    Debug.WriteLine("OuinOuin msg non valide");
                    break;


            }
        }
    }

public enum Commands{
    Texte = 0x0080,
    Led = 0x0020, 
    TelemetreIR = 0x0030, 
    Speed = 0x0040
};

}
