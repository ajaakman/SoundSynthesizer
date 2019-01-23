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
            synth.SetReleaseTime(5.0);
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

        private void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            synth.SetMasterVolume(slValue.Value);
        }

    }
}
