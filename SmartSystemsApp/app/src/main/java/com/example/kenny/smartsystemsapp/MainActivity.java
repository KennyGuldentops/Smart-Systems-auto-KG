package com.example.kenny.smartsystemsapp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Layout;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {
    BluetoothConnection btcon = new BluetoothConnection();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //vooruit
        ImageButton vooruit = (ImageButton) findViewById(R.id.Vooruit);
        vooruit.setImageResource(R.drawable.vooruit);
        vooruit.getLayoutParams().height = 300;
        vooruit.getLayoutParams().width = 300;

        //achteruit
        ImageButton achteruit = (ImageButton) findViewById(R.id.Achteruit);
        achteruit.setImageResource(R.drawable.achteruit);
        achteruit.getLayoutParams().height = 300;
        achteruit.getLayoutParams().width = 300;

        //links
        ImageButton links = (ImageButton) findViewById(R.id.Links);
        links.setImageResource(R.drawable.links);
        links.getLayoutParams().height = 300;
        links.getLayoutParams().width = 300;

        //rechts
        ImageButton rechts = (ImageButton) findViewById(R.id.Rechts);
        rechts.setImageResource(R.drawable.rechts);
        rechts.getLayoutParams().height = 300;
        rechts.getLayoutParams().width = 300;

        //Stop
        ImageButton stop = (ImageButton) findViewById(R.id.Stop);
        stop.setImageResource(R.drawable.stop);
        stop.getLayoutParams().height = 300;
        stop.getLayoutParams().width = 900;

        //ontouchbutton test
        Button test = (Button) findViewById(R.id.button);
        test.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    try {

                        btcon.send("3".toString().getBytes());
                        Log.i("notpressed","not pressed");
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    try {
                        btcon.send("5".toString().getBytes());
                        Log.i("pressed", "pressed");
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                return true;
        }

        });

        //Vooruit ontouchevent
        vooruit.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    try {
                        btcon.send("3".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    try {
                        btcon.send("1".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                return true;
            }
        });

        //achteruit ontouchevent
        achteruit.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    try {
                        btcon.send("3".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    try{
                        btcon.send("5".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                return true;
            }
        });

        //links ontouchevent
        links.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    try {
                        btcon.send("3".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    try{
                        btcon.send("4".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                return true;
            }
        });

        rechts.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    try {
                        btcon.send("3".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    try {
                        btcon.send("2".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                return true;
            }
        });

        stop.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    try {
                        btcon.send("3".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    try{
                        btcon.send("3".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                return true;
            }
        });



        }

    //open bluetooth settings om manueel met de HC-05 te connecten
    public void OpenBluetoothSettings(View view) {
        try{
            btcon.connect();
        }  catch (BluetoothConnection.BluetoothConnectionException e){
            Log.e("Bluetooth","fout",e);
        }
        new Thread(new Runnable() {
            @Override
            public void run(){


            }}).start();

    }
}