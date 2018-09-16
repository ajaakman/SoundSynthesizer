using SynthCLI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpSynth
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Start");
            CLISynth synth = new CLISynth();
            Console.WriteLine("End");
            Console.ReadLine();
        }
    }
}
