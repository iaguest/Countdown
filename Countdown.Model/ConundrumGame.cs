using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Countdown.Model
{
    public class ConundrumGame : AbstractGame
    {
        #region Dll Marshalling

        [DllImport("CountdownDll.dll")]
        static public extern IntPtr CreateConundrumGame();

        [DllImport("CountdownDll.dll")]
        static public extern void DisposeConundrumGame(IntPtr pConundrumGame);

        [DllImport("CountdownDll.dll")]
        static public extern bool InitializeConundrumGame(IntPtr pConundrumGame,
                                                        string input,
                                                        Int32 inputSize,
                                                        StringBuilder output,
                                                        IntPtr outputSize);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string GetConundrumGameStartMessage(IntPtr ConundrumGame);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string GetConundrumGameBoard(IntPtr pConundrumGame);

        [DllImport("CountdownDll.dll")]
        static public extern void RunConundrumGame(IntPtr ConundrumGame);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string GetConundrumGameEndMessage(IntPtr ConundrumGame);

        [DllImport("CountdownDll.dll")]
        static public extern int GetConundrumGameScore(IntPtr ConundrumGame, string answer, Int32 answerSize);

        #endregion

        protected override IntPtr CreateGame()
        {
            return CreateConundrumGame();
        }

        protected override void DisposeGame(IntPtr gamePointer)
        {
            DisposeConundrumGame(gamePointer);
        }

        protected override bool Initialize(IntPtr gamePointer,
                                           string input,
                                           int inputSize,
                                           StringBuilder output,
                                           IntPtr outputSize)
        {
            return InitializeConundrumGame(gamePointer, input, inputSize, output, outputSize);
        }

        protected override string InitializationMessage => "Press Enter to reveal today's Countdown conundrum";

        protected override string StartMessage(IntPtr gamePointer)
        {
            return GetConundrumGameStartMessage(gamePointer);
        }

        protected override string GetGameBoard(IntPtr gamePointer)
        {
            return GetConundrumGameBoard(gamePointer);
        }

        protected override void Run(IntPtr gamePointer)
        {
            RunConundrumGame(gamePointer);
        }

        protected override string EndMessage(IntPtr gamePointer)
        {
            return GetConundrumGameEndMessage(gamePointer);
        }

        protected override int GetScore(IntPtr gamePointer, string answer, Int32 answerSize)
        {
            return GetConundrumGameScore(gamePointer, answer, answer.Length);
        }
    }
}
