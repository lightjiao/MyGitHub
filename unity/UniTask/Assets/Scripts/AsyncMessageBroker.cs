using System;
using Cysharp.Threading.Tasks;
using Cysharp.Threading.Tasks.Linq;

/// <summary>
/// 利用 Channel 来实现的 生产者/消费者 模型
/// </summary>
/// <typeparam name="T"></typeparam>
public class AsyncMessageBroker<T> : IDisposable
{
    private readonly Channel<T> _channel;

    private readonly IConnectableUniTaskAsyncEnumerable<T> _multicastSource;
    private readonly IDisposable _connection;

    public AsyncMessageBroker()
    {
        _channel = Channel.CreateSingleConsumerUnbounded<T>();
        _multicastSource = _channel.Reader.ReadAllAsync().Publish();
        _connection = _multicastSource.Connect();
    }

    public void Publish(T value)
    {
        _channel.Writer.TryWrite(value);
    }

    public IUniTaskAsyncEnumerable<T> Subscribe()
    {
        return _multicastSource;
    }

    public void Dispose()
    {
        _channel.Writer.TryComplete();
        _connection.Dispose();
    }
}