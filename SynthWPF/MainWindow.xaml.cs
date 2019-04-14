using System;
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
using System.Threading;

namespace SynthWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {       
        private ControlHost PianoControl;

        public MainWindow()
        {
            InitializeComponent();
            PianoControl = null;
        }

        private void On_UIReady(object sender, EventArgs e)
        {      
            PianoControl = new ControlHost(ControlHostElement.ActualHeight, ControlHostElement.ActualWidth);
            ControlHostElement.Child = PianoControl;            
        }   

        private void OnKeyDownHandler(object sender, KeyEventArgs e)
        {
            if (PianoControl != null)
            {
                if (e.Key == Key.Q)
                    PianoControl.synth.PianoKeyPress(0);
                else if (e.Key == Key.D2)
                    PianoControl.synth.PianoKeyPress(1);
                else if (e.Key == Key.W)
                    PianoControl.synth.PianoKeyPress(2);
                else if (e.Key == Key.D3)
                    PianoControl.synth.PianoKeyPress(3);
                else if (e.Key == Key.E)
                    PianoControl.synth.PianoKeyPress(4);
                else if (e.Key == Key.R)
                    PianoControl.synth.PianoKeyPress(5);
                else if (e.Key == Key.D5)
                    PianoControl.synth.PianoKeyPress(6);
                else if (e.Key == Key.T)
                    PianoControl.synth.PianoKeyPress(7);
                else if (e.Key == Key.D6)
                    PianoControl.synth.PianoKeyPress(8);
                else if (e.Key == Key.Y)
                    PianoControl.synth.PianoKeyPress(9);
                else if (e.Key == Key.D7)
                    PianoControl.synth.PianoKeyPress(10);
                else if (e.Key == Key.U)
                    PianoControl.synth.PianoKeyPress(11);
                else if (e.Key == Key.I)
                    PianoControl.synth.PianoKeyPress(12);
                else if (e.Key == Key.D9)
                    PianoControl.synth.PianoKeyPress(13);
                else if (e.Key == Key.O)
                    PianoControl.synth.PianoKeyPress(14);
                else if (e.Key == Key.D0)
                    PianoControl.synth.PianoKeyPress(15);
                else if (e.Key == Key.P)
                    PianoControl.synth.PianoKeyPress(16);
                else if (e.Key == Key.OemOpenBrackets)
                    PianoControl.synth.PianoKeyPress(17);
                else if (e.Key == Key.OemPlus)
                    PianoControl.synth.PianoKeyPress(18);
                else if (e.Key == Key.OemCloseBrackets)
                    PianoControl.synth.PianoKeyPress(19);
                else if (e.Key == Key.Back)
                    PianoControl.synth.PianoKeyPress(20);
            }
        }

        private void OnKeyUpHandler(object sender, KeyEventArgs e)
        {
            if (PianoControl != null)
            {
                if (e.Key == Key.Q)
                    PianoControl.synth.PianoKeyRelease(0);
                else if (e.Key == Key.D2)
                    PianoControl.synth.PianoKeyRelease(1);
                else if (e.Key == Key.W)
                    PianoControl.synth.PianoKeyRelease(2);
                else if (e.Key == Key.D3)
                    PianoControl.synth.PianoKeyRelease(3);
                else if (e.Key == Key.E)
                    PianoControl.synth.PianoKeyRelease(4);
                else if (e.Key == Key.R)
                    PianoControl.synth.PianoKeyRelease(5);
                else if (e.Key == Key.D5)
                    PianoControl.synth.PianoKeyRelease(6);
                else if (e.Key == Key.T)
                    PianoControl.synth.PianoKeyRelease(7);
                else if (e.Key == Key.D6)
                    PianoControl.synth.PianoKeyRelease(8);
                else if (e.Key == Key.Y)
                    PianoControl.synth.PianoKeyRelease(9);
                else if (e.Key == Key.D7)
                    PianoControl.synth.PianoKeyRelease(10);
                else if (e.Key == Key.U)
                    PianoControl.synth.PianoKeyRelease(11);
                else if (e.Key == Key.I)
                    PianoControl.synth.PianoKeyRelease(12);
                else if (e.Key == Key.D9)
                    PianoControl.synth.PianoKeyRelease(13);
                else if (e.Key == Key.O)
                    PianoControl.synth.PianoKeyRelease(14);
                else if (e.Key == Key.D0)
                    PianoControl.synth.PianoKeyRelease(15);
                else if (e.Key == Key.P)
                    PianoControl.synth.PianoKeyRelease(16);
                else if (e.Key == Key.OemOpenBrackets)
                    PianoControl.synth.PianoKeyRelease(17);
                else if (e.Key == Key.OemPlus)
                    PianoControl.synth.PianoKeyRelease(18);
                else if (e.Key == Key.OemCloseBrackets)
                    PianoControl.synth.PianoKeyRelease(19);
                else if (e.Key == Key.Back)
                    PianoControl.synth.PianoKeyRelease(20);
            }
        }

        private void slMasterAmplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)            
                PianoControl.synth.SetMasterVolume(slMasterAmplitude.Value);
        }

        private void slAttackTime_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetAttackTime(slAttackTime.Value);
        }

        private void slStartAmplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetStartAmplitude(slStartAmplitude.Value);
        }

        private void slDecayTime_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetDecayTime(slDecayTime.Value);
        }

        private void slSustainAmplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetSusatainAmplitude(slSustainAmplitude.Value);
        }

        private void slReleaseTime_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetReleaseTime(slReleaseTime.Value);
        }
        /////////////////////////////
        private void slOSC1Amplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetWaveAmplitude(slOSC1Amplitude.Value, 1);
        }                

        private void slOSC1Tune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetTune((int)slOSC1Tune.Value, 1);
        }

        private void slOSC1FineTune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetFineTune(slOSC1FineTune.Value, 1);
        }

        private void OSC1Wave_Checked(object sender, RoutedEventArgs e)
        {
            if (PianoControl != null)
            {
            var radioButton = sender as RadioButton;
            if (radioButton == null)
                return;
            if (radioButton.Content.ToString() == "Sine")
                PianoControl.synth.SetWaveType((uint)Wave.Sine, 0, 1);
            else if (radioButton.Content.ToString() == "Saw")
                PianoControl.synth.SetWaveType((uint)Wave.Saw, 0, 1);
            else if (radioButton.Content.ToString() == "Square")
                PianoControl.synth.SetWaveType((uint)Wave.Square, 0, 1);
            else if (radioButton.Content.ToString() == "Triangle")
                PianoControl.synth.SetWaveType((uint)Wave.Triange, 0, 1);
            else if (radioButton.Content.ToString() == "Noise")
                PianoControl.synth.SetWaveType((uint)Wave.Noise, 0, 1);
            }
        }

        private void slOSC1TremAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetTremoloAmplitude(slOSC1TremAmp.Value, 1);
        }

        private void slOSC1TremFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetTremoloFrequency(slOSC1TremFreq.Value, 1);
        }

        private void slOSC1VibFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetVibratoFrequency(slOSC1VibFreq.Value, 1);
        }

        private void slOSC1VibAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetVibratoAmplitude(slOSC1VibAmp.Value, 1);
        }
        ///////////////////////
        private void slOSC2Amplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetWaveAmplitude(slOSC2Amplitude.Value, 2);
        }

        private void slOSC2Tune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetTune((int)slOSC2Tune.Value, 2);
        }

        private void slOSC2FineTune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetFineTune(slOSC2FineTune.Value, 2);
        }

        private void OSC2Wave_Checked(object sender, RoutedEventArgs e)
        {
            if (PianoControl != null)
            {
            var radioButton = sender as RadioButton;
            if (radioButton == null)
                return;
            if (radioButton.Content.ToString() == "Sine")
                PianoControl.synth.SetWaveType((uint)Wave.Sine, 0, 2);
            else if (radioButton.Content.ToString() == "Saw")
                PianoControl.synth.SetWaveType((uint)Wave.Saw, 0, 2);
            else if (radioButton.Content.ToString() == "Square")
                PianoControl.synth.SetWaveType((uint)Wave.Square, 0, 2);
            else if (radioButton.Content.ToString() == "Triangle")
                PianoControl.synth.SetWaveType((uint)Wave.Triange, 0, 2);
            else if (radioButton.Content.ToString() == "Noise")
                PianoControl.synth.SetWaveType((uint)Wave.Noise, 0, 2);
            }
        }

        private void slOSC2TremAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetTremoloAmplitude(slOSC2TremAmp.Value, 2);
        }

        private void slOSC2TremFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetTremoloFrequency(slOSC2TremFreq.Value, 2);
        }

        private void slOSC2VibFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetVibratoFrequency(slOSC2VibFreq.Value, 2);
        }

        private void slOSC2VibAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetVibratoAmplitude(slOSC2VibAmp.Value, 2);
        }
        ////////////////
        private void slOSC3Amplitude_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetWaveAmplitude(slOSC3Amplitude.Value, 3);
        }

        private void slOSC3Tune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetTune((int)slOSC3Tune.Value, 3);
        }

        private void slOSC3FineTune_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetFineTune(slOSC3FineTune.Value, 3);
        }

        private void OSC3Wave_Checked(object sender, RoutedEventArgs e)
        {
            if (PianoControl != null)
            {
                var radioButton = sender as RadioButton;
                if (radioButton == null)
                    return;
                if (radioButton.Content.ToString() == "Sine")
                    PianoControl.synth.SetWaveType((uint)Wave.Sine, 0, 3);
                else if (radioButton.Content.ToString() == "Saw")
                    PianoControl.synth.SetWaveType((uint)Wave.Saw, 0, 3);
                else if (radioButton.Content.ToString() == "Square")
                    PianoControl.synth.SetWaveType((uint)Wave.Square, 0, 3);
                else if (radioButton.Content.ToString() == "Triangle")
                    PianoControl.synth.SetWaveType((uint)Wave.Triange, 0, 3);
                else if (radioButton.Content.ToString() == "Noise")
                    PianoControl.synth.SetWaveType((uint)Wave.Noise, 0, 3);
            }
        }

        private void slOSC3TremAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetTremoloAmplitude(slOSC3TremAmp.Value, 3);
        }

        private void slOSC3TremFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetTremoloFrequency(slOSC3TremFreq.Value, 3);
        }

        private void slOSC3VibFreq_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetVibratoFrequency(slOSC3VibFreq.Value, 3);
        }

        private void slOSC3VibAmp_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (PianoControl != null)
                PianoControl.synth.SetVibratoAmplitude(slOSC3VibAmp.Value, 3);
        }

    }
}
