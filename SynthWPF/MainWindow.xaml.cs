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

        enum Wave { Sine, Square, Saw, Triange, AnalogSaw, Noise };

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
            synth.SetWaveAmplitude(0.0, 2);
            synth.SetWaveAmplitude(0.0, 3);

            synth.SetWaveType((uint)Wave.Square, 0, 1);
            synth.SetWaveType((uint)Wave.Saw, 0, 2);
            synth.SetWaveType((uint)Wave.Triange, 0, 3);

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

        private void slMasterAmplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetMasterVolume(slMasterAmplitude.Value);
        }

        private void slAttackTime_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetAttackTime(slAttackTime.Value);
        }

        private void slStartAmplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetStartAmplitude(slStartAmplitude.Value);
        }

        private void slDecayTime_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetDecayTime(slDecayTime.Value);
        }

        private void slSustainAmplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetSusatainAmplitude(slSustainAmplitude.Value);
        }

        private void slReleaseTime_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetReleaseTime(slReleaseTime.Value);
        }
        /////////////////////////////
        private void slOSC1Amplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetWaveAmplitude(slOSC1Amplitude.Value, 1);
        }                

        private void slOSC1Tune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetTune((int)slOSC1Tune.Value, 1);
        }

        private void slOSC1FineTune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetFineTune(slOSC1FineTune.Value, 1);
        }

        private void OSC1Wave_Checked(object sender, RoutedEventArgs e)
        {
            var radioButton = sender as RadioButton;
            if (radioButton == null)
                return;
            if (radioButton.Content.ToString() == "Sine")
                synth.SetWaveType((uint)Wave.Sine, 0, 1);
            else if (radioButton.Content.ToString() == "Saw")
                synth.SetWaveType((uint)Wave.Saw, 0, 1);
            else if (radioButton.Content.ToString() == "Square")
                synth.SetWaveType((uint)Wave.Square, 0, 1);
            else if (radioButton.Content.ToString() == "Triangle")
                synth.SetWaveType((uint)Wave.Triange, 0, 1);
            else if (radioButton.Content.ToString() == "Noise")
                synth.SetWaveType((uint)Wave.Noise, 0, 1);
        }

        private void slOSC1TremAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetTremoloAmplitude(slOSC1TremAmp.Value, 1);
        }

        private void slOSC1TremFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetTremoloFrequency(slOSC1TremFreq.Value, 1);
        }

        private void slOSC1VibFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetVibratoFrequency(slOSC1VibFreq.Value, 1);
        }

        private void slOSC1VibAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetVibratoAmplitude(slOSC1VibAmp.Value, 1);
        }
        ///////////////////////
        private void slOSC2Amplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetWaveAmplitude(slOSC2Amplitude.Value, 2);
        }

        private void slOSC2Tune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetTune((int)slOSC2Tune.Value, 2);
        }

        private void slOSC2FineTune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetFineTune(slOSC2FineTune.Value, 2);
        }

        private void OSC2Wave_Checked(object sender, RoutedEventArgs e)
        {
            var radioButton = sender as RadioButton;
            if (radioButton == null)
                return;
            if (radioButton.Content.ToString() == "Sine")
                synth.SetWaveType((uint)Wave.Sine, 0, 2);
            else if (radioButton.Content.ToString() == "Saw")
                synth.SetWaveType((uint)Wave.Saw, 0, 2);
            else if (radioButton.Content.ToString() == "Square")
                synth.SetWaveType((uint)Wave.Square, 0, 2);
            else if (radioButton.Content.ToString() == "Triangle")
                synth.SetWaveType((uint)Wave.Triange, 0, 2);
            else if (radioButton.Content.ToString() == "Noise")
                synth.SetWaveType((uint)Wave.Noise, 0, 2);
        }

        private void slOSC2TremAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetTremoloAmplitude(slOSC2TremAmp.Value, 2);
        }

        private void slOSC2TremFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetTremoloFrequency(slOSC2TremFreq.Value, 2);
        }

        private void slOSC2VibFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetVibratoFrequency(slOSC2VibFreq.Value, 2);
        }

        private void slOSC2VibAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetVibratoAmplitude(slOSC2VibAmp.Value, 2);
        }
        ////////////////
        private void slOSC3Amplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetWaveAmplitude(slOSC3Amplitude.Value, 3);
        }

        private void slOSC3Tune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetTune((int)slOSC3Tune.Value, 3);
        }

        private void slOSC3FineTune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetFineTune(slOSC3FineTune.Value, 3);
        }

        private void OSC3Wave_Checked(object sender, RoutedEventArgs e)
        {
            var radioButton = sender as RadioButton;
            if (radioButton == null)
                return;
            if (radioButton.Content.ToString() == "Sine")
                synth.SetWaveType((uint)Wave.Sine, 0, 3);
            else if (radioButton.Content.ToString() == "Saw")
                synth.SetWaveType((uint)Wave.Saw, 0, 3);
            else if (radioButton.Content.ToString() == "Square")
                synth.SetWaveType((uint)Wave.Square, 0, 3);
            else if (radioButton.Content.ToString() == "Triangle")
                synth.SetWaveType((uint)Wave.Triange, 0, 3);
            else if (radioButton.Content.ToString() == "Noise")
                synth.SetWaveType((uint)Wave.Noise, 0, 3);
        }

        private void slOSC3TremAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetTremoloAmplitude(slOSC3TremAmp.Value, 3);
        }

        private void slOSC3TremFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetTremoloFrequency(slOSC3TremFreq.Value, 3);
        }

        private void slOSC3VibFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetVibratoFrequency(slOSC3VibFreq.Value, 3);
        }

        private void slOSC3VibAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetVibratoAmplitude(slOSC3VibAmp.Value, 3);
        }

    }
}
