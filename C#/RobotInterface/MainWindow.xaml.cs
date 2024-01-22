using ExtendedSerialPort;
using System.IO.Ports;
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

namespace RobotInterface
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ReliableSerialPort serialPort1;
        string receivedText;

        public MainWindow()
        {

            InitializeComponent();
            serialPort1 = new ReliableSerialPort("COM4", 115200, Parity.None, 8, StopBits.One);
             
            serialPort1.OnDataReceivedEvent += SerialPort1_OnDataReceivedEvent;
            //serialPort1.Open();

        }

        private void SerialPort1_OnDataReceivedEvent(object? sender, DataReceivedArgs e)
        {// coucou c'est ici qu'on travail p11
           // receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
            //textBoxReception.Text ;

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

        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                sendMessage();
            }
        }
    }
}