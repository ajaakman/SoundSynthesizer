using SynthCLI;
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

namespace SynthWPF.UserControls
{
    /// <summary>
    /// Interaction logic for MasterControlsView.xaml
    /// </summary>
    public partial class MasterControlsView : Page
    {
        CLISynth synth = new CLISynth();
        public MasterControlsView()
        {
            InitializeComponent();
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
    }
}
