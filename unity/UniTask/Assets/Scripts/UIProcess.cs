using System;
using System.Threading;
using Cysharp.Threading.Tasks;
using UnityEngine;
using UnityEngine.UI;
using Debug = UnityEngine.Debug;

namespace DefaultNamespace
{
    public class UIProcess : MonoBehaviour, IProgress<int>
    {
        [SerializeField] private Image processImage;
        [SerializeField] private Button button;

        private CancellationTokenSource cts;

        private void Start()
        {
            button.onClick.AddListener(ButtonClickStart);
        }

        private void ButtonClickStart()
        {
            button.onClick.RemoveListener(ButtonClickStart);
            button.onClick.AddListener(ButtonClickCancel);

            cts = new CancellationTokenSource();
            StartProcessAsync(cts);
        }

        private void ButtonClickCancel()
        {
            CancelProcess();
        }

        private void CancelProcess()
        {
            cts.Cancel();
        }

        private async void StartProcessAsync(CancellationTokenSource cts)
        {
            await UniTask.Delay(1000, cancellationToken: this.GetCancellationTokenOnDestroy());
        }

        public void Report(int value)
        {
            processImage.fillAmount = value / 100f;
        }
    }
}