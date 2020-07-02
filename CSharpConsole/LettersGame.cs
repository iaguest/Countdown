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
        static public extern bool InitializeLettersGame(IntPtr pLettersGame,
                                                        string input,
                                                        Int32 inputSize,
                                                        StringBuilder output,
                                                        IntPtr outputSize);

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

        protected override void DisposeGame(IntPtr gamePointer)
        {
            DisposeLettersGame(gamePointer);
        }

        public override bool Initialize(string input, out string output)
        {
            bool isInitialized = base.Initialize(input, out output);
            // get last character which is the generated vowel or consonant.
            output = output[output.Length - 2].ToString();
            return isInitialized;
    }

        protected override bool Initialize(IntPtr gamePointer,
                                           string input,
                                           int inputSize,
                                           StringBuilder output,
                                           IntPtr outputSize)
        {
            return InitializeLettersGame(gamePointer, input, inputSize, output, outputSize);
        }

        protected override string StartMessage(IntPtr gamePointer)
        {
            return GetLettersGameStartMessage(gamePointer);
        }

        protected override string GetGameBoard(IntPtr gamePointer)
        {
            return GetLettersGameBoard(gamePointer);
        }

        protected override void Run(IntPtr gamePointer)
        {
            RunLettersGame(gamePointer);
        }

        protected override string EndMessage(IntPtr gamePointer)
        {
            return GetLettersGameEndMessage(gamePointer);
        }

        protected override int GetScore(IntPtr gamePointer, string answer, Int32 answerSize)
        {
            return GetLettersGameScore(gamePointer, answer, answer.Length);
        }
    }
}
