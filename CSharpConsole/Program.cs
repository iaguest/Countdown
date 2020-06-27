using System;
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
            //use the functions
            IntPtr pLettersGame = CreateLettersGame();

            //CallFunction(pClassName);
            //var s = "BobbyBobBob";
            //CallPrintChars(pClassName, s, s.Length);

            //var s = new StringBuilder("1234567");
            //for (int i = 0; i < 7; ++i)
            //{
            //    CallInitialize(pLettersGame, new String('v', i + 1), i + 1, s);
            //}
            //Console.WriteLine(s.ToString());

            DisposeLettersGame(pLettersGame);

            pLettersGame = IntPtr.Zero;

            Console.ReadLine();
        }
    }
}
