using SynthCLI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SynthWPF
{    
    public class Midi
    {
        private NativeMethods.MidiInProc midiInProc;
        private IntPtr handle;
        private CLISynth synth;

        public Midi(CLISynth s)
        {
            synth = s;
            midiInProc = new NativeMethods.MidiInProc(MidiProc);
            handle = IntPtr.Zero;
        }

        public static int InputCount
        {
            get { return NativeMethods.midiInGetNumDevs(); }
        }

        public bool Close()
        {
            bool result = NativeMethods.midiInClose(handle)
                == NativeMethods.MMSYSERR_NOERROR;
            handle = IntPtr.Zero;
            return result;
        }

        public bool Open(int id)
        {
            return NativeMethods.midiInOpen(
                out handle,
                id,
                midiInProc,
                IntPtr.Zero,
                NativeMethods.CALLBACK_FUNCTION)
                    == NativeMethods.MMSYSERR_NOERROR;
        }

        public bool Start()
        {
            return NativeMethods.midiInStart(handle)
                == NativeMethods.MMSYSERR_NOERROR;
        }

        public bool Stop()
        {
            return NativeMethods.midiInStop(handle)
                == NativeMethods.MMSYSERR_NOERROR;
        }

        private void MidiProc(IntPtr hMidiIn,
            int wMsg,
            IntPtr dwInstance,
            int dwParam1,
            int dwParam2)
        {
            if (wMsg == 963)
                if ((byte)(dwParam1 >> 0) == 144)
                {
                    //string num = Convert.ToString(dwParam1, 2).PadLeft(32, '0');
                    //Console.WriteLine(dwParam1 >> 15);
                    if ((byte)(dwParam1 >> 16) != 0)
                        synth.PianoKeyPress((byte)(dwParam1 >> 8) - 60);
                    else
                        synth.PianoKeyRelease((byte)(dwParam1 >> 8) - 60);
                }
        }
    }

    internal static class NativeMethods
    {
        internal const int MMSYSERR_NOERROR = 0;
        internal const int CALLBACK_FUNCTION = 0x00030000;

        internal delegate void MidiInProc(
            IntPtr hMidiIn,
            int wMsg,
            IntPtr dwInstance,
            int dwParam1,
            int dwParam2);

        [DllImport("winmm.dll")]
        internal static extern int midiInGetNumDevs();

        [DllImport("winmm.dll")]
        internal static extern int midiInClose(
            IntPtr hMidiIn);

        [DllImport("winmm.dll")]
        internal static extern int midiInOpen(
            out IntPtr lphMidiIn,
            int uDeviceID,
            MidiInProc dwCallback,
            IntPtr dwCallbackInstance,
            int dwFlags);

        [DllImport("winmm.dll")]
        internal static extern int midiInStart(
            IntPtr hMidiIn);

        [DllImport("winmm.dll")]
        internal static extern int midiInStop(
            IntPtr hMidiIn);
    }    
}
