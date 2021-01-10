using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Linq;
using TMPro;
using UnityEngine;
using UnityEngine.UI;
public class ArduinoConnector : MonoBehaviour {

    private SerialPort _serial;
    private AudioData _audioData;
    private float _amplitude;
    [SerializeField] private Slider _intensity, _r, _g, _b;
    [SerializeField] private float _threshhold = 1.5f;
    [SerializeField] private TMP_Dropdown _portSelector;
    private readonly string[] _ports = { "COM3", "COM4" };
    private string _currPort;

    private void OnEnable () {
        //force dot instead of comma
        System.Globalization.CultureInfo customCulture = (System.Globalization.CultureInfo) System.Threading.Thread.CurrentThread.CurrentCulture.Clone ();
        customCulture.NumberFormat.NumberDecimalSeparator = ".";
        System.Threading.Thread.CurrentThread.CurrentCulture = customCulture;

        GetPort ();

        _audioData = FindObjectOfType<AudioData> ();
        Application.targetFrameRate = 60;
    }

    private void OnDisable () {
        Disconnect ();
        _amplitude = 0;
    }

    private void Update () {

        if (_audioData._amplitudeBuffer >= _threshhold) {
            _amplitude = 2 * _audioData._amplitudeBuffer * _intensity.value * Time.smoothDeltaTime;
        } else {
            _amplitude = _audioData._amplitudeBuffer * _intensity.value * Time.smoothDeltaTime;
        }
        Debug.Log (_amplitude);

        string amp = _amplitude.ToString ("000.00");
        string bufferString = amp;
        for (int i = 0; i < 30; i++) {
            string val = _audioData._audioBandBuffer64[i].ToString ("0");
            bufferString += val;
        }
        WriteToArduino (bufferString);
    }

    public void Connect () {
        if (!IsConnected ()) {
            _serial = new SerialPort (_currPort, 9600);
            _serial.NewLine = "\n";
            _serial.Open ();
        }
        Debug.Log ("Connected: " + IsConnected ());
    }

    public void Disconnect () {
        if (IsConnected ()) _serial.Close ();

        Debug.Log ("Connected: " + IsConnected ());
    }

    public void WriteToArduino (string message = null) {
        if (message != null && IsConnected ())
            _serial.WriteLine (message);
    }

    private bool IsConnected () {
        return (_serial != null && _serial.IsOpen);
    }

    public void GetPort () {
        _currPort = _ports[_portSelector.value];
        Debug.Log ("Selected port: " + _currPort);
    }
}
