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

        public override IntPtr CreateGame()
        {
            return CreateLettersGame();
        }

        public override void DisposeGame()
        {
            DisposeLettersGame(gamePointer);
        }

        public override bool Initialize(string input, out string output)
        {
            StringBuilder sb = new StringBuilder(256);
            int sbSize = sb.MaxCapacity;
            // Allocating memory for int
            IntPtr sbSizePointer = Marshal.AllocHGlobal(sizeof(int));
            Marshal.WriteInt32(sbSizePointer, sbSize);

            bool isInitialized = InitializeLettersGame(
                gamePointer, input, 1, sb, sbSizePointer);

            int outputsize = Marshal.ReadInt32(sbSizePointer);
            output = sb.ToString()[outputsize - 2].ToString();

            // Free memory
            Marshal.FreeHGlobal(sbSizePointer);
            sbSizePointer = IntPtr.Zero;

            return isInitialized;
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
