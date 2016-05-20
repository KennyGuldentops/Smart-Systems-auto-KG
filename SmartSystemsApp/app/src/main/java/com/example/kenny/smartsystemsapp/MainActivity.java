package com.example.kenny.smartsystemsapp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Layout;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Switch;

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

        //Draw
        Button draw = (Button) findViewById(R.id.Drawing);

        //Switch
        final Switch togglestate = (Switch) findViewById(R.id.switch1);
        togglestate.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    togglestate.setText("Driving automatic");
                    try {
                        btcon.send("6".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                else {
                    togglestate.setText("Driving manual");
                    try {
                        btcon.send("7".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
            }
        });

        //draw function
        draw.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    btcon.send("8".toString().getBytes());
                } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                    Log.e("Oxygen Bluetooth", "exception: " + e);
                }
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
                    try {
                        btcon.send("1".toString().getBytes());
                    } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
                        Log.e("Oxygen Bluetooth", "exception: " + e);
                    }
                }
                return true;
            }
        });

        //vooruit ontouchevent
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
        }

    //open bluetooth settings om manueel met de HC-05 te connecten
    public void OpenBluetoothSettings(View view) {
        try{
            btcon.connect();
        }  catch (BluetoothConnection.BluetoothConnectionException e){
            Log.e("Bluetooth","fout",e);
        }
    }

    public void Stopdrawing(View view) {
        try {
            btcon.send("9".toString().getBytes());
        } catch (IOException | BluetoothConnection.BluetoothConnectionException e) {
            Log.e("Oxygen Bluetooth", "exception: " + e);
        }
    }
}
