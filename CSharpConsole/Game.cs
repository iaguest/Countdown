using System;
using System.Runtime.InteropServices;
using System.Text;

namespace CSharpConsole
{
    public abstract class Game : IDisposable, IGame
    {
        private bool disposedValue = false; // To detect redundant calls
        protected IntPtr gamePointer;

        public Game()
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
        ~Game()
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

        public abstract string StartMessage();

        public abstract string GetGameBoard();

        public abstract void Run();

        public abstract string EndMessage();

        public abstract int GetScore(string answer);

        protected abstract IntPtr CreateGame();

        protected abstract void DisposeGame();

        protected abstract bool Initialize(IntPtr gamePointer,
                                           string input,
                                           Int32 inputSize,
                                           StringBuilder output,
                                           IntPtr outputSize);

        public bool Initialize(string input, out string output)
        {
            StringBuilder sb = new StringBuilder(256);
            int sbSize = sb.MaxCapacity;
            // Allocating memory for int
            IntPtr sbSizePointer = Marshal.AllocHGlobal(sizeof(int));
            Marshal.WriteInt32(sbSizePointer, sbSize);

            bool isInitialized = Initialize(gamePointer, input, 1, sb, sbSizePointer);

            int outputsize = Marshal.ReadInt32(sbSizePointer);
            output = sb.ToString()[outputsize - 2].ToString();

            // Free memory
            Marshal.FreeHGlobal(sbSizePointer);
            sbSizePointer = IntPtr.Zero;

            return isInitialized;
        }
    }
}
