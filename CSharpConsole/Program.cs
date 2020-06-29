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
        static public extern string CallGetGameBoard(IntPtr pLettersGame);

        static void Main(string[] args)
        {
            List<char> vals = new List<char>();

            //use the functions
            IntPtr pLettersGame = CreateLettersGame();

            StringBuilder sb = new StringBuilder(256);
            int sbSize = sb.MaxCapacity;
            // Allocating memory for int
            IntPtr sbSizePointer = Marshal.AllocHGlobal(sizeof(int));

            while (true)
            {
                Marshal.WriteInt32(sbSizePointer, sbSize);
                bool isInitialized = CallInitialize(
                    pLettersGame,new string('c', 1), 1, sb, sbSizePointer);
                if (isInitialized)
                    break;

                int outputsize = Marshal.ReadInt32(sbSizePointer);
                var toAdd = sb.ToString()[outputsize-2];
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
