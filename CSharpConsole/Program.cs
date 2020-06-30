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

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string CallGetGameBoard(IntPtr pLettersGame);

        [DllImport("CountdownDll.dll")]
        static public extern void CallRun(IntPtr lettersGame);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string CallEndMessage(IntPtr lettersGame);

        [DllImport("CountdownDll.dll")]
        static public extern int CallGetScore(IntPtr lettersGame,
                                              string answer,
                                              Int32 answerSize);

        static void Main(string[] args)
        {
            List<char> vals = new List<char>();

            //use the functions
            IntPtr pLettersGame = CreateLettersGame();

            StringBuilder sb = new StringBuilder(256);
            int sbSize = sb.MaxCapacity;
            // Allocating memory for int
            IntPtr sbSizePointer = Marshal.AllocHGlobal(sizeof(int));

            var letterTypes = new List<string> { "c", "v", "c", "v", "c", "v", "c", "v", "c" };

            bool isInitialized = false;
            foreach (var letterType in letterTypes)
            {
                Marshal.WriteInt32(sbSizePointer, sbSize);
                isInitialized = CallInitialize(
                    pLettersGame, letterType, 1, sb, sbSizePointer);

                int outputsize = Marshal.ReadInt32(sbSizePointer);
                vals.Add(sb.ToString()[outputsize - 2]);
            }

            if (!isInitialized)
                throw new InvalidOperationException();

            var board = CallGetGameBoard(pLettersGame);
            Console.WriteLine(board);

            CallRun(pLettersGame);

            Console.WriteLine("Enter answer: ");
            var answer = Console.ReadLine();

            var score = CallGetScore(pLettersGame, answer, answer.Length);
            Console.WriteLine($"Your score is: {score}");

            Console.Write(CallEndMessage(pLettersGame));

            // Free memory
            Marshal.FreeHGlobal(sbSizePointer);
            sbSizePointer = IntPtr.Zero;
            DisposeLettersGame(pLettersGame);
            pLettersGame = IntPtr.Zero;

            Console.ReadLine();
        }
    }
}
