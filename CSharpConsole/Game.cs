using System;

namespace CSharpConsole
{
    public abstract class Game : IDisposable
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

        public abstract IntPtr CreateGame();

        public abstract void DisposeGame();

        public abstract bool Initialize(string input, out string output);

        public abstract string StartMessage();

        public abstract string GetGameBoard();

        public abstract void Run();

        public abstract string EndMessage();

        public abstract int GetScore(string answer);
    }
}
