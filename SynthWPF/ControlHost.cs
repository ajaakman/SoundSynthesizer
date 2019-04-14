using System;
using SynthCLI;
using System.Runtime.InteropServices;
using System.Windows.Interop;

namespace SynthWPF
{
    enum Wave { Sine, Square, Saw, Triange, AnalogSaw, Noise };

    public class ControlHost : HwndHost
    {
        internal const int
            WsChild = 0x40000000,
            WsVisible = 0x10000000,
            LbsNotify = 0x00000001,
            HostId = 0x00000002,
            ListboxId = 0x00000001,
            WsVscroll = 0x00200000,
            WsBorder = 0x00800000;

        private readonly int HostHeight;
        private readonly int HostWidth;
        private IntPtr HWND_Host;

        public CLISynth synth = new CLISynth();

        public ControlHost(double height, double width)
        {
            HostHeight = (int)height;
            HostWidth = (int)width;

            synth.SetMasterVolume(0.09);

            synth.SetAttackTime(0.05);
            synth.SetStartAmplitude(1.0);
            synth.SetDecayTime(0.7);
            synth.SetSusatainAmplitude(0.7);
            synth.SetReleaseTime(0.7);

            synth.SetWaveAmplitude(0.9, 1);
            synth.SetWaveAmplitude(0.8, 2);
            synth.SetWaveAmplitude(1.0, 3);

            synth.SetWaveType((uint)Wave.Saw, 0, 1);
            synth.SetWaveType((uint)Wave.Square, 0, 2);
            synth.SetWaveType((uint)Wave.Triange, 0, 3);

            synth.SetTune(-12, 1);
            synth.SetTune(0, 2);
            synth.SetTune(12, 3);

            synth.SetFineTune(0.0, 1);
            synth.SetFineTune(0.1, 2);
            synth.SetFineTune(-0.1, 3);

            synth.SetTremoloAmplitude(0.03, 1);
            synth.SetTremoloFrequency(5.0, 1);
            synth.SetTremoloAmplitude(0.03, 2);
            synth.SetTremoloFrequency(5.0, 2);
            synth.SetTremoloAmplitude(0.03, 3);
            synth.SetTremoloFrequency(5.0, 3);

            synth.SetVibratoAmplitude(0.003, 1);
            synth.SetVibratoFrequency(5.0, 1);
            synth.SetVibratoAmplitude(0.003, 2);
            synth.SetVibratoFrequency(5.0, 2);
            synth.SetVibratoAmplitude(0.003, 3);
            synth.SetVibratoFrequency(5.0, 3);
        }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            HWND_Host = IntPtr.Zero;
            HWND_Host = synth.Create("", WsChild | WsVisible, 0, 0, 0, HostWidth, HostHeight, hwndParent.Handle, (IntPtr)HostId);
            return new HandleRef(this, HWND_Host);
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            handled = false;
            return IntPtr.Zero;
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            //DestroyWindow(hwnd.Handle);
        }

    }
}