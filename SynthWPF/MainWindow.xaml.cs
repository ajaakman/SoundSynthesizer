using System;
using SynthCLI;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace SynthWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        CLISynth synth = new CLISynth();

        public MainWindow()
        {
            InitializeComponent();

            synth.SetMasterVolume(0.1);
            synth.SetAttackTime(0.0);
            synth.SetDecayTime(0.0);
            synth.SetReleaseTime(1.0);
            synth.SetStartAmplitude(1.0);
            synth.SetSusatainAmplitude(1.0);

            synth.SetWaveAmplitude(0.3, 1);
            synth.SetWaveAmplitude(0.4, 2);
            synth.SetWaveAmplitude(0.5, 3);

            synth.SetWaveType(2, 0, 1);
            synth.SetWaveType(1, 0, 2);
            synth.SetWaveType(3, 0, 3);

            synth.SetTune(-12, 1);
            synth.SetTune(0, 2);
            synth.SetTune(12, 3);

            synth.SetFineTune(0.0, 1);
            synth.SetFineTune(-0.1, 2);
            synth.SetFineTune(0.1, 3);

            synth.SetTremoloAmplitude(0.003, 1);
            synth.SetTremoloFrequency(5.0, 1);
            synth.SetTremoloAmplitude(0.003, 2);
            synth.SetTremoloFrequency(5.0, 2);
            synth.SetTremoloAmplitude(0.003, 3);
            synth.SetTremoloFrequency(5.0, 3);

            synth.SetVibratoAmplitude(0.003, 1);
            synth.SetVibratoFrequency(5.0, 1);
            synth.SetVibratoAmplitude(0.003, 2);
            synth.SetVibratoFrequency(5.0, 2);
            synth.SetVibratoAmplitude(0.003, 3);
            synth.SetVibratoFrequency(5.0, 3);
        }

        private void OnKeyDownHandler(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Q)
                synth.PianoKeyPress(0);
            else if (e.Key == Key.D2)
                synth.PianoKeyPress(1);
            else if (e.Key == Key.W)
                synth.PianoKeyPress(2);
            else if (e.Key == Key.D3)
                synth.PianoKeyPress(3);
            else if (e.Key == Key.E)
                synth.PianoKeyPress(4);
            else if (e.Key == Key.R)
                synth.PianoKeyPress(5);
            else if (e.Key == Key.D5)
                synth.PianoKeyPress(6);
            else if (e.Key == Key.T)
                synth.PianoKeyPress(7);
            else if (e.Key == Key.D6)
                synth.PianoKeyPress(8);
            else if (e.Key == Key.Y)
                synth.PianoKeyPress(9);
            else if (e.Key == Key.D7)
                synth.PianoKeyPress(10);
            else if (e.Key == Key.U)
                synth.PianoKeyPress(11);
            else if (e.Key == Key.I)
                synth.PianoKeyPress(12);
            else if (e.Key == Key.D9)
                synth.PianoKeyPress(13);
            else if (e.Key == Key.O)
                synth.PianoKeyPress(14);
            else if (e.Key == Key.D0)
                synth.PianoKeyPress(15);
            else if (e.Key == Key.P)
                synth.PianoKeyPress(16);
            else if (e.Key == Key.OemOpenBrackets)
                synth.PianoKeyPress(17);
            else if (e.Key == Key.OemPlus)
                synth.PianoKeyPress(18);
            else if (e.Key == Key.OemCloseBrackets)
                synth.PianoKeyPress(19);
            else if (e.Key == Key.Back)
                synth.PianoKeyPress(20);
        }

        private void OnKeyUpHandler(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Q)
                synth.PianoKeyRelease(0);
            else if (e.Key == Key.D2)
                synth.PianoKeyRelease(1);
            else if (e.Key == Key.W)
                synth.PianoKeyRelease(2);
            else if (e.Key == Key.D3)
                synth.PianoKeyRelease(3);
            else if (e.Key == Key.E)
                synth.PianoKeyRelease(4);
            else if (e.Key == Key.R)
                synth.PianoKeyRelease(5);
            else if (e.Key == Key.D5)
                synth.PianoKeyRelease(6);
            else if (e.Key == Key.T)
                synth.PianoKeyRelease(7);
            else if (e.Key == Key.D6)
                synth.PianoKeyRelease(8);
            else if (e.Key == Key.Y)
                synth.PianoKeyRelease(9);
            else if (e.Key == Key.D7)
                synth.PianoKeyRelease(10);
            else if (e.Key == Key.U)
                synth.PianoKeyRelease(11);
            else if (e.Key == Key.I)
                synth.PianoKeyRelease(12);
            else if (e.Key == Key.D9)
                synth.PianoKeyRelease(13);
            else if (e.Key == Key.O)
                synth.PianoKeyRelease(14);
            else if (e.Key == Key.D0)
                synth.PianoKeyRelease(15);
            else if (e.Key == Key.P)
                synth.PianoKeyRelease(16);
            else if (e.Key == Key.OemOpenBrackets)
                synth.PianoKeyRelease(17);
            else if (e.Key == Key.OemPlus)
                synth.PianoKeyRelease(18);
            else if (e.Key == Key.OemCloseBrackets)
                synth.PianoKeyRelease(19);
            else if (e.Key == Key.Back)
                synth.PianoKeyRelease(20);
        }

        private void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetMasterVolume(slValue.Value);
        }

    }
}
