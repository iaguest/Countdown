using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace CSharpConsole
{
    class Program
    {
        [DllImport("CountdownDll.dll")]
        static public extern IntPtr CreateLettersGame();

        [DllImport("CountdownDll.dll")]
        static public extern void DisposeLettersGame(IntPtr pLettersGame);

        [DllImport("CountdownDll.dll")]
        static public extern bool CallInitialize(IntPtr pLettersGame,
                                                 string input,
                                                 Int32 inputSize,
                                                 StringBuilder output,
                                                 IntPtr outputSize);

        [DllImport("CountdownDll.dll")]
        static public extern StringBuilder CallGetGameBoard(IntPtr pLettersGame);

        static void Main(string[] args)
        {
            // TODO:
            // might be good to have a post build step for the dll build
            // not only have to copy dll but resource files into the C# build folder


            List<string> vals = new List<string>();

            //use the functions
            IntPtr pLettersGame = CreateLettersGame();

            StringBuilder sb = new StringBuilder(256);
            int sbSize = sb.MaxCapacity;
            // Allocating memory for int
            IntPtr sbSizePointer = Marshal.AllocHGlobal(sizeof(int));

            while (true)
            {
                Marshal.WriteInt32(sbSizePointer, sbSize);
                bool isInitialized = CallInitialize(pLettersGame, new string('c', 1), 1, sb, sbSizePointer);
                if (isInitialized)
                    break;

                var output = sb.ToString();
                int outputsize = Marshal.ReadInt32(sbSizePointer);
                string toAdd = output.Substring(0, outputsize);
                Console.WriteLine(toAdd);
                vals.Add(toAdd);
            }

            // Free memory
            Marshal.FreeHGlobal(sbSizePointer);
            sbSizePointer = IntPtr.Zero;
            DisposeLettersGame(pLettersGame);
            pLettersGame = IntPtr.Zero;

            Console.ReadLine();
        }
    }
}
