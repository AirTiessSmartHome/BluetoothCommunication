package com.example.user.simplebluetooth;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class Login extends Activity {
    public static String EXTRA_DEVICE_ADDRESS = "device_address";
    public TextView txtusername, txtpassword;
    public EditText etxtusername, etxtpassword;
    public Button btnLogin;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login_main);

        txtusername = (TextView) findViewById(R.id.txtUsername);
        txtpassword = (TextView) findViewById(R.id.txtPassword);
        etxtusername = (EditText) findViewById(R.id.etxtUsername);
        etxtpassword = (EditText) findViewById(R.id.etxtPassword);
        btnLogin = (Button) findViewById(R.id.btnLogin);

        // UserName EditText OnClick Listener
        etxtusername.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                etxtusername.setText("");
            }
        });

        // Password EditText OnClick Listener
        etxtpassword.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                etxtpassword.setText("");
            }
        });

        // Login Button OnClick Listener
        btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String userN = etxtusername.getText().toString();
                String Pass = etxtpassword.getText().toString();
                if (userN.equals("kaan") & Pass.equals("12345")) {
                    Intent intent = new Intent(Login.this, DeviceListActivity.class);
                    startActivity(intent);
                } else
                    Toast.makeText(getBaseContext(), "Wrong username or Password!!", Toast.LENGTH_SHORT).show();
            }
        });
    }

    public void onResume() {
        super.onResume();
    }
}
