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

    public abstract class AbstractGameBase : IDisposable
    {
        private bool disposedValue = false; // To detect redundant calls
        protected IntPtr gamePointer;

        public AbstractGameBase()
        {
            gamePointer = CreateGame();
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
                DisposeGame();
                // TODO: set large fields to null.
                gamePointer = IntPtr.Zero;

                disposedValue = true;
            }
        }

        // TODO: override a finalizer only if Dispose(bool disposing) above has code to free unmanaged resources.
        ~AbstractGameBase()
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

        public abstract IntPtr CreateGame();

        public abstract void DisposeGame();
    }

    public class LettersGame : AbstractGameBase, IGame
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

        #region AbstractGame

        public override IntPtr CreateGame()
        {
            return CreateLettersGame();
        }

        public override void DisposeGame()
        {
            DisposeLettersGame(gamePointer);
        }

        #endregion AbstractGame

        #region IGame

        public bool Initialize(string input, out string output)
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

        public string GetGameBoard()
        {
            return CallGetGameBoard(gamePointer);
        }

        public void Run()
        {
            CallRun(gamePointer);
        }

        public string EndMessage()
        {
            return CallEndMessage(gamePointer);
        }

        public int GetScore(string answer)
        {
            return CallGetScore(gamePointer, answer, answer.Length);
        }

        #endregion IGame
    }

    //public class LettersGame

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

            //Console.ReadLine();
        }
    }
}
