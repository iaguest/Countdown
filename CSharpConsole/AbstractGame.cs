using System;
using System.Runtime.InteropServices;
using System.Text;

namespace CSharpConsole
{
    public abstract class AbstractGame : IDisposable, IGame
    {
        private bool disposedValue = false; // To detect redundant calls
        private IntPtr gamePointer;

        public AbstractGame()
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
                DisposeGame(gamePointer);
                // TODO: set large fields to null.
                gamePointer = IntPtr.Zero;

                disposedValue = true;
            }
        }

        // TODO: override a finalizer only if Dispose(bool disposing) above has code to free unmanaged resources.
        ~AbstractGame()
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

        #region IGame

        public virtual bool Initialize(string input, out string output)
        {
            StringBuilder sb = new StringBuilder(256);
            int sbSize = sb.MaxCapacity;
            // Allocating memory for int
            IntPtr sbSizePointer = Marshal.AllocHGlobal(sizeof(int));
            Marshal.WriteInt32(sbSizePointer, sbSize);

            bool isInitialized = Initialize(gamePointer, input, 1, sb, sbSizePointer);

            int outputsize = Marshal.ReadInt32(sbSizePointer);
            output = sb.ToString().Substring(0, outputsize);

            // Free memory
            Marshal.FreeHGlobal(sbSizePointer);
            sbSizePointer = IntPtr.Zero;

            return isInitialized;
        }

        public string StartMessage()
        {
            return StartMessage(gamePointer);
        }

        public string GetGameBoard()
        {
            return GetGameBoard(gamePointer);
        }

        public void Run()
        {
            Run(gamePointer);
        }

        public string EndMessage()
        {
            return EndMessage(gamePointer);
        }

        public int GetScore(string answer)
        {
            return GetScore(gamePointer, answer, answer.Length);
        }

        #endregion

        protected abstract IntPtr CreateGame();

        protected abstract void DisposeGame(IntPtr gamePointer);

        protected abstract bool Initialize(IntPtr gamePointer,
                                           string input,
                                           Int32 inputSize,
                                           StringBuilder output,
                                           IntPtr outputSize);

        protected abstract string StartMessage(IntPtr gamePointer);

        protected abstract string GetGameBoard(IntPtr gamePointer);

        protected abstract void Run(IntPtr gamePointer);

        protected abstract string EndMessage(IntPtr gamePointer);

        protected abstract int GetScore(IntPtr lettersGame, string answer, Int32 answerSize);
    }
}
