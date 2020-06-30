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
        static public extern bool CallInitialize(IntPtr pLettersGame, string input, Int32 inputSize, StringBuilder output, IntPtr outputSize);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string CallGetGameBoard(IntPtr pLettersGame);

        [DllImport("CountdownDll.dll")]
        static public extern void CallRun(IntPtr lettersGame);

        [DllImport("CountdownDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        static public extern string CallEndMessage(IntPtr lettersGame);

        [DllImport("CountdownDll.dll")]
        static public extern int CallGetScore(IntPtr lettersGame, string answer, Int32 answerSize);

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

            bool isInitialized = CallInitialize(
                gamePointer, input, 1, sb, sbSizePointer);

            int outputsize = Marshal.ReadInt32(sbSizePointer);
            output = sb.ToString()[outputsize - 2].ToString();

            // Free memory
            Marshal.FreeHGlobal(sbSizePointer);
            sbSizePointer = IntPtr.Zero;

            return isInitialized;
        }

        public override string GetGameBoard()
        {
            return CallGetGameBoard(gamePointer);
        }

        public override void Run()
        {
            CallRun(gamePointer);
        }

        public override string EndMessage()
        {
            return CallEndMessage(gamePointer);
        }

        public override int GetScore(string answer)
        {
            return CallGetScore(gamePointer, answer, answer.Length);
        }
    }
}
