using System;
using System.Runtime.InteropServices;
using System.Text;

namespace CSharpConsole
{
    public class LettersGame : Game
    {
        #region Dll Marshalling

        [DllImport("CountdownDll.dll")]
        static public extern IntPtr CreateLettersGame();

        [DllImport("CountdownDll.dll")]
        static public extern void DisposeLettersGame(IntPtr pLettersGame);

        [DllImport("CountdownDll.dll")]
        static public extern bool InitializeLettersGame(IntPtr pLettersGame, string input, Int32 inputSize, StringBuilder output, IntPtr outputSize);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string GetLettersGameStartMessage(IntPtr lettersGame);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string GetLettersGameBoard(IntPtr pLettersGame);

        [DllImport("CountdownDll.dll")]
        static public extern void RunLettersGame(IntPtr lettersGame);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string GetLettersGameEndMessage(IntPtr lettersGame);

        [DllImport("CountdownDll.dll")]
        static public extern int GetLettersGameScore(IntPtr lettersGame, string answer, Int32 answerSize);

        #endregion

        protected override IntPtr CreateGame()
        {
            return CreateLettersGame();
        }

        protected override void DisposeGame()
        {
            DisposeLettersGame(gamePointer);
        }

        protected override bool Initialize(IntPtr gamePointer, string input, int inputSize, StringBuilder output, IntPtr outputSize)
        {
            return InitializeLettersGame(gamePointer, input, inputSize, output, outputSize);
        }

        public override string StartMessage()
        {
            return GetLettersGameStartMessage(gamePointer);
        }

        public override string GetGameBoard()
        {
            return GetLettersGameBoard(gamePointer);
        }

        public override void Run()
        {
            RunLettersGame(gamePointer);
        }

        public override string EndMessage()
        {
            return GetLettersGameEndMessage(gamePointer);
        }

        public override int GetScore(string answer)
        {
            return GetLettersGameScore(gamePointer, answer, answer.Length);
        }
    }
}
