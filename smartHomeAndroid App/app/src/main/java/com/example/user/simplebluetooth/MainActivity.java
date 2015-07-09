package com.example.user.simplebluetooth;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class MainActivity extends Activity {
    public static final UUID BTMODULEUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");  // SPP UUID service
    public static String address;
    public static boolean flagHide = true;
    // Signals START
    public static String led1 = "1";
    public static String led2 = "2";
    public static String perde = "3";
    public static String powerTV = "4";
    public static String volUp = "5";
    public static String volDown = "6";
    public static String chUp = "7";
    public static String chDown = "8";
    // Signals END
    final int handlerState = 0;
    public TextView txtString, txtStringLength, txtTempr, txtLog;
    public Button btnLED1, btnLED2, btnClear, btnHide, btnChUp, btnChDown, btnVolUp, btnVolDown;
    public ToggleButton tbtnTv;
    public Switch swLED1, swLED2;
    public BluetoothAdapter btAdapter = null;
    public BluetoothSocket btSocket = null;
    public StringBuilder recDataString = new StringBuilder();
    public ConnectedThread mConnectedThread;
    Handler bluetoothIn;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Link the buttons and textViews
        btnLED1 = (Button) findViewById(R.id.btnLED1);
        btnLED2 = (Button) findViewById(R.id.btnLED2);
        btnClear = (Button) findViewById(R.id.btnClear);
        btnHide = (Button) findViewById(R.id.btnHide);
        btnChUp = (Button) findViewById(R.id.btnChUp);
        btnChDown = (Button) findViewById(R.id.btnChDown);
        btnVolUp = (Button) findViewById(R.id.btnVolUp);
        btnVolDown = (Button) findViewById(R.id.btnVolDown);
        tbtnTv = (ToggleButton) findViewById(R.id.tbtnTV);
        swLED1 = (Switch) findViewById(R.id.swLED1);
        swLED2 = (Switch) findViewById(R.id.swLED2);
        txtString = (TextView) findViewById(R.id.txtMsg);
        txtStringLength = (TextView) findViewById(R.id.txtMsgLength);
        txtTempr = (TextView) findViewById(R.id.txtTempr);
        txtLog = (TextView) findViewById(R.id.txtLog);

        bluetoothIn = new Handler() {
            @SuppressWarnings("HandlerLeak")
            public void handleMessage(android.os.Message msg) {
                if (recDataString.length() > 1)
                    recDataString.delete(0, recDataString.length());    // Delete old message data

                String readMessage = (String) msg.obj;                  // msg.arg1 <= bytes from connect thread
                recDataString.append(readMessage);                      // Keep appending to string

                String dataInPrint = recDataString.toString();          // Extract All data from recieved message
                int dataLength = dataInPrint.length();                  // Get length of recieved message
                txtString.setText("Data Received = " + dataInPrint);    // Put revieved message to txtMsg field
                txtStringLength.setText("String Length = " + String.valueOf(dataLength));//Similiar to above one

                txtTempr.setText("Temperature = " + dataInPrint + " C");
                txtLog.append("L=" + dataInPrint + "\n");
            }
        };

        btAdapter = BluetoothAdapter.getDefaultAdapter();        // Get Bluetooth adapter
        checkBTState();

        // LED1 OnChecked Listener
        swLED1.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (swLED1.isChecked()) {
                    mConnectedThread.write(Encryption.encrypt(led1));    // Send "1" via Bluetooth -> TurnOn Signal
                    Toast.makeText(getBaseContext(), "LED 1 -> On", Toast.LENGTH_SHORT).show();
                } else {
                    mConnectedThread.write(Encryption.encrypt(led1));    // Send "1" via Bluetooth -> TurnOff Signal
                    Toast.makeText(getBaseContext(), "LED 1 -> Off", Toast.LENGTH_SHORT).show();
                }
            }
        });
        // LED2 OnChecked Listener
        swLED2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (swLED2.isChecked()) {
                    mConnectedThread.write(Encryption.encrypt(led2));
                    Toast.makeText(getBaseContext(), "LED 2 -> On", Toast.LENGTH_SHORT).show();
                } else {
                    mConnectedThread.write(Encryption.encrypt(led2));
                    Toast.makeText(getBaseContext(), "LED 2 -> Off", Toast.LENGTH_SHORT).show();
                }
            }
        });
        // ChannelUp OnClick Listener
        btnChUp.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                mConnectedThread.write(Encryption.encrypt(chUp));
                Toast.makeText(getBaseContext(), "Next Channel", Toast.LENGTH_SHORT).show();
            }
        });
        // ChannelDown OnClick Listener
        btnChDown.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                mConnectedThread.write(Encryption.encrypt(chDown));
                Toast.makeText(getBaseContext(), "Previous Channel", Toast.LENGTH_SHORT).show();
            }
        });
        // VolumeUp OnClick Listener
        btnVolUp.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                mConnectedThread.write(Encryption.encrypt(volUp));
                Toast.makeText(getBaseContext(), "Volume Increased", Toast.LENGTH_SHORT).show();
            }
        });
        // VolumeDown OnClick Listener
        btnVolDown.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                mConnectedThread.write(Encryption.encrypt(volDown));
                Toast.makeText(getBaseContext(), "Volume Decreased", Toast.LENGTH_SHORT).show();
            }
        });
        // toggleButton TV OnChange Listener
        tbtnTv.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (tbtnTv.isChecked()) {
                    mConnectedThread.write(Encryption.encrypt(powerTV));
                    Toast.makeText(getBaseContext(), "Opening TV", Toast.LENGTH_SHORT).show();
                } else {
                    mConnectedThread.write(Encryption.encrypt(powerTV));
                    Toast.makeText(getBaseContext(), "Closing TV", Toast.LENGTH_SHORT).show();
                }
            }
        });
        // Clear OnClick Listener
        btnClear.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                txtLog.setText("");
            }
        });
        // Hide OnClick Listener
        btnHide.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                if (flagHide) {
                    //Hide Log
                    txtLog.setVisibility(View.GONE);
                    btnClear.setVisibility(View.GONE);
                    txtString.setVisibility(View.GONE);
                    txtStringLength.setVisibility(View.GONE);
                    btnHide.setText("Show Log");
                    flagHide = false;
                } else {
                    //Show Log
                    txtLog.setVisibility(View.VISIBLE);
                    btnClear.setVisibility(View.VISIBLE);
                    txtString.setVisibility(View.VISIBLE);
                    txtStringLength.setVisibility(View.VISIBLE);
                    btnHide.setText("Hide");
                    flagHide = true;
                }
            }
        });
        btnHide.performClick();  // Defatults of buttons are left as Log Open
        // FROM HERE ON TO BE DELETED ON FUTURE
        // SyncLED1 OnClick Listener
        btnLED1.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                recDataString.delete(0, recDataString.length()); // Delete old message data
                // Login
                mConnectedThread.write("kaan654321");
            }
        });
        // SyncLED2 OnClick Listener
        btnLED2.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                recDataString.delete(0, recDataString.length()); // Delete old message data
                mConnectedThread.write(Encryption.encrypt(led2));
            }
        });

    }

    private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
        return device.createRfcommSocketToServiceRecord(BTMODULEUUID); // Creates secure outgoing connecetion with BT device using UUID
    }

    @Override
    public void onResume() {
        super.onResume();

        // Get MAC address from DeviceListActivity via intent
        Intent intent = getIntent();

        // Get the MAC address from the DeviceListActivty via EXTRA
        address = intent.getStringExtra(DeviceListActivity.EXTRA_DEVICE_ADDRESS);

        // Create device and set the MAC address
        BluetoothDevice device = btAdapter.getRemoteDevice(address);

        try {
            btSocket = createBluetoothSocket(device);
        } catch (IOException e) {
            Toast.makeText(getBaseContext(), "Socket creation failed", Toast.LENGTH_LONG).show();
        }
        // Establish the Bluetooth socket connection.
        try {
            btSocket.connect();
        } catch (IOException e) {
            try {
                btSocket.close();
            } catch (IOException e2) {
                // Codes can be adde here to deal with exception here!!
            }
        }
        mConnectedThread = new ConnectedThread(btSocket);
        mConnectedThread.start();
    }

    @Override
    public void onPause() {
        super.onPause();
        try {
            // End bluetooth sockets on close.
            btSocket.close();
        } catch (IOException e2) {
            // Codes can be adde here to deal with exception here!!
        }
    }

    // Check device has Bluetooth and it is turned on
    public void checkBTState() {
        if (btAdapter == null)
            Toast.makeText(getBaseContext(), "Device does not support bluetooth", Toast.LENGTH_LONG).show();
        else if (!btAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, 1);
        }
    }

    // Create new class for connect thread
    private class ConnectedThread extends Thread {
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        // Creation of the connect thread
        public ConnectedThread(BluetoothSocket socket) {
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            try {
                // Create I/O streams for connection
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException ignored) {
            }

            mmInStream = tmpIn;
            mmOutStream = tmpOut;
        }

        public void run() {
            byte[] buffer = new byte[256];
            int bytes;

            // Keep looping to listen for received messages
            while (true) {
                try {
                    bytes = mmInStream.read(buffer);       // Read bytes from input buffer
                    String readMessage = new String(buffer, 0, bytes);
                    // Send the obtained bytes to the UI Activity via handler
                    bluetoothIn.obtainMessage(handlerState, bytes, -1, readMessage).sendToTarget();
                } catch (IOException e) {
                    break;
                }
            }
        }

        // Write method
        public void write(String input) {
            byte[] msgBuffer = input.getBytes();           // Converts entered String into bytes
            try {
                mmOutStream.write(msgBuffer);              // Write bytes over BT connection via outstream
            } catch (IOException e) {
                // If you cannot write, close the application
                Toast.makeText(getBaseContext(), "Connection Failure", Toast.LENGTH_LONG).show();
                finish();

            }
        }
    }

}