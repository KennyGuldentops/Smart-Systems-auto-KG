package com.example.kenny.smartsystemsapp;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;
import android.widget.TextView;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;

public class BluetoothConnection {


    private OutputStream mOutputStream;
    private BluetoothAdapter mBluetoothAdapter;
    BluetoothSocket socket;
    BluetoothDevice device = null;
    final String macAddress = "98:D3:31:FC:11:51";
    boolean connected = false;
    public TextView StatusTV;


    //Enable emulated RS-232 serial port via Bluetooth
    public void connect() throws BluetoothConnectionException {

        // Assign the Bluetooth adapter to mBluetoothAdapter
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        //If Bluetooth adapter does not exists throw exception
        if (mBluetoothAdapter == null)
            throw new BluetoothConnectionException("Device does not support Bluetooth");

        // Check if Bluetooth is disabled
        if (!mBluetoothAdapter.isEnabled()) {
            throw new BluetoothConnectionException("Bluetooth is disabled");
        }


        new Thread(new Runnable() {
            @Override
            public void run(){


                device = mBluetoothAdapter.getRemoteDevice(macAddress);
                if(connected)Log.e("Oxygen Bluetooth","already connected");
                try {
                    if(!connected) {
                        socket = device.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
                        socket.connect();
                        Log.e("Oxygen Bluetooth", "connected");

                    }
                    mOutputStream = socket.getOutputStream();
                    connected = true;
                }catch (IOException e){
                    Log.e("Oxygen Bluetooth", "error" + e);
                    connected = false;
                }
                        }}).start();
    }

    public void send(byte[] data) throws BluetoothConnectionException, IOException {
        if (mOutputStream == null)
            throw new BluetoothConnectionException("Socket not connected");

        mOutputStream.write(data, 0, data.length);
    }


    //Define Bluetooth Exception
    public static class BluetoothConnectionException extends Exception {
        public BluetoothConnectionException(String message) {
            super(message);
        }
    }
}






