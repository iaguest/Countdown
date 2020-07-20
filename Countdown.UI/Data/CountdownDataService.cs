using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace Countdown.UI.Data
{
    [Serializable()]
    public class CountdownDataService : ICountdownDataService
    {
        private const string FileName = "CountdownDataService.bin";

        public CountdownDataService()
        {
        }

        public int HighScore { get; set; }

        public void Load()
        {
            if (File.Exists(FileName))
            {
                Stream openFileStream = File.OpenRead(FileName);
                BinaryFormatter deserializer = new BinaryFormatter();
                var cds = (CountdownDataService)deserializer.Deserialize(openFileStream);
                HighScore = cds.HighScore;
                openFileStream.Close();
            }
        }

        public void Save()
        {
            Stream SaveFileStream = File.Create(FileName);
            BinaryFormatter serializer = new BinaryFormatter();
            serializer.Serialize(SaveFileStream, this);
            SaveFileStream.Close();
        }
    }
}
