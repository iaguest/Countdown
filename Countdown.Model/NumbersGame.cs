using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Countdown.Model
{
    public class NumbersGame : AbstractGame
    {
        #region Dll Marshalling

        [DllImport("CountdownDll.dll")]
        static public extern IntPtr CreateNumbersGame();

        [DllImport("CountdownDll.dll")]
        static public extern void DisposeNumbersGame(IntPtr pNumbersGame);

        [DllImport("CountdownDll.dll")]
        static public extern bool InitializeNumbersGame(IntPtr pNumbersGame,
                                                        string input,
                                                        Int32 inputSize,
                                                        StringBuilder output,
                                                        IntPtr outputSize);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string GetNumbersGameStartMessage(IntPtr NumbersGame);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string GetNumbersGameBoard(IntPtr pNumbersGame);

        [DllImport("CountdownDll.dll")]
        static public extern void RunNumbersGame(IntPtr NumbersGame);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string GetNumbersGameEndMessage(IntPtr NumbersGame);

        [DllImport("CountdownDll.dll")]
        static public extern int GetNumbersGameScore(IntPtr NumbersGame, string answer, Int32 answerSize);

        #endregion

        protected override IntPtr CreateGame()
        {
            return CreateNumbersGame();
        }

        protected override void DisposeGame(IntPtr gamePointer)
        {
            DisposeNumbersGame(gamePointer);
        }

        protected override bool Initialize(IntPtr gamePointer,
                                           string input,
                                           int inputSize,
                                           StringBuilder output,
                                           IntPtr outputSize)
        {
            return InitializeNumbersGame(gamePointer, input, inputSize, output, outputSize);
        }

        protected override string GameTypeString => "Numbers";

        protected override string InitializationMessage => "Enter number of large numbers (0->4)";

        protected override string StartMessage(IntPtr gamePointer)
        {
            return GetNumbersGameStartMessage(gamePointer);
        }

        protected override string GetGameBoard(IntPtr gamePointer)
        {
            return GetNumbersGameBoard(gamePointer);
        }

        protected override void Run(IntPtr gamePointer)
        {
            RunNumbersGame(gamePointer);
        }

        protected override string EndMessage(IntPtr gamePointer)
        {
            return GetNumbersGameEndMessage(gamePointer);
        }

        protected override int GetScore(IntPtr gamePointer, string answer, Int32 answerSize)
        {
            return GetNumbersGameScore(gamePointer, answer, answer.Length);
        }
    }
}
