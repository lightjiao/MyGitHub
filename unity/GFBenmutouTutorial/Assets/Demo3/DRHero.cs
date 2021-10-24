using GameFramework.DataTable;
using UnityGameFramework.Runtime;

public class DRHero : IDataRow
{
    public int Id { get; protected set; }
    public string Name { get; protected set; }
    public int Atk { get; protected set; }

    public bool ParseDataRow(string dataRowString, object userData)
    {
        var text = dataRowString.Split('\t');
        var index = 0;
        index++;
        Id = int.Parse(text[index++]);
        Name = text[index++];
        Atk = int.Parse(text[index]);

        return true;
    }

    public bool ParseDataRow(byte[] dataRowBytes, int startIndex, int length, object userData)
    {
        Log.Error("没有实现byte格式的配置文件");
        throw new System.NotImplementedException();
    }
}