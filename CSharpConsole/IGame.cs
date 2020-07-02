namespace CSharpConsole
{
    public interface IGame
    {
        bool Initialize(string input, out string output);
        string StartMessage();
        string GetGameBoard();
        void Run();
        string EndMessage();
        int GetScore(string answer);
    }
}