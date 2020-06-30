using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace CSharpConsole
{
    public interface IGame
    {
        bool Initialize(string input, out string output);

        string GetGameBoard();

        void Run();

        string EndMessage();

        int GetScore(string answer);
    }

    public class LettersGame : IDisposable, IGame
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

        private bool disposedValue = false; // To detect redundant calls
        private IntPtr lettersGamePointer;

        public LettersGame()
        {
            lettersGamePointer = CreateLettersGame();
        }

        #region IDisposable Support

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    // TODO: dispose managed state (managed objects).
                }

                // TODO: free unmanaged resources (unmanaged objects) and override a finalizer below.
                DisposeLettersGame(lettersGamePointer);
                // TODO: set large fields to null.
                lettersGamePointer = IntPtr.Zero;

                disposedValue = true;
            }
        }

        // TODO: override a finalizer only if Dispose(bool disposing) above has code to free unmanaged resources.
        ~LettersGame()
        {
            // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
            Dispose(false);
        }

        // This code added to correctly implement the disposable pattern.
        public void Dispose()
        {
            // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
            Dispose(true);
            // TODO: uncomment the following line if the finalizer is overridden above.
            GC.SuppressFinalize(this);
        }

        #endregion

        public bool Initialize(string input, out string output)
        {
            StringBuilder sb = new StringBuilder(256);
            int sbSize = sb.MaxCapacity;
            // Allocating memory for int
            IntPtr sbSizePointer = Marshal.AllocHGlobal(sizeof(int));
            Marshal.WriteInt32(sbSizePointer, sbSize);

            bool isInitialized = CallInitialize(
                lettersGamePointer, input, 1, sb, sbSizePointer);

            int outputsize = Marshal.ReadInt32(sbSizePointer);
            output = sb.ToString()[outputsize - 2].ToString();

            // Free memory
            Marshal.FreeHGlobal(sbSizePointer);
            sbSizePointer = IntPtr.Zero;

            return isInitialized;
        }

        public string GetGameBoard()
        {
            return CallGetGameBoard(lettersGamePointer);
        }

        public void Run()
        {
            CallRun(lettersGamePointer);
        }

        public string EndMessage()
        {
            return CallEndMessage(lettersGamePointer);
        }

        public int GetScore(string answer)
        {
            return CallGetScore(lettersGamePointer, answer, answer.Length);
        }
    }

    class Program
    {

        static void Main(string[] args)
        {
            var game = new LettersGame();

            var letterTypes = new List<string> { "c", "v", "c", "v", "c", "v", "c", "v", "c" };

            bool isInitialized = false;
            foreach (var letterType in letterTypes)
                isInitialized = game.Initialize(letterType, out string s);

            if (!isInitialized)
                throw new InvalidOperationException();

            var board = game.GetGameBoard();
            Console.WriteLine(board);

            game.Run();

            Console.WriteLine("Enter answer: ");
            var answer = Console.ReadLine();

            var score = game.GetScore(answer);
            Console.WriteLine($"Your score is: {score}");

            Console.Write(game.EndMessage());

            Console.ReadLine();
        }
    }
}
