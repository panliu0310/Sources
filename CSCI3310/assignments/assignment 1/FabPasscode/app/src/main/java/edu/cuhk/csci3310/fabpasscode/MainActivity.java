// Name: Liu Hoi Pan
// SID: 1155127464
package edu.cuhk.csci3310.fabpasscode;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MainActivity extends AppCompatActivity {

    private int mPasscode = 0;
    private TextView mShowPasscode;
    private ImageView hiddenBird;
    private Button button0;
    private Button button1;
    private Button button2;
    private Button button3;
    private Button button4;
    private Button button5;
    private Button button6;
    private Button button7;
    private Button button8;
    private Button button9;
    private Button buttonUnlock;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mShowPasscode = (TextView) findViewById(R.id.passcodeView);
        hiddenBird = (ImageView) findViewById(R.id.hidden_bird);
        button0 = (Button) findViewById(R.id.button0);
        button1 = (Button) findViewById(R.id.button1);
        button2 = (Button) findViewById(R.id.button2);
        button3 = (Button) findViewById(R.id.button3);
        button4 = (Button) findViewById(R.id.button4);
        button5 = (Button) findViewById(R.id.button5);
        button6 = (Button) findViewById(R.id.button6);
        button7 = (Button) findViewById(R.id.button7);
        button8 = (Button) findViewById(R.id.button8);
        button9 = (Button) findViewById(R.id.button9);
        buttonUnlock = (Button) findViewById(R.id.button_unlock);
    }

    public void updatePasscode(View view) {
        Button button = (Button) view;
        String buttonText = button.getText().toString();
        // a new digit appended to the end of mPasscode
        // the algorithm is oldPasscodeDigit * 10 + newPasscodeDigit
        mPasscode = mPasscode * 10 + Integer.parseInt(buttonText);
        mShowPasscode.setText(String.valueOf(mPasscode));
    }

    public void unlockPasscode(View view) {
        // the last 4 digits of my sid is 7464
        Pattern pattern = Pattern.compile("7464", Pattern.CASE_INSENSITIVE);
        Matcher matcher = pattern.matcher(Integer.toString(mPasscode));
        if (matcher.find()) {
            Toast toast = Toast.makeText(this, "Bingo!", Toast.LENGTH_SHORT);
            toast.show();
            hiddenBird.setVisibility(View.VISIBLE);
            button0.setEnabled(false);
            button1.setEnabled(false);
            button2.setEnabled(false);
            button3.setEnabled(false);
            button4.setEnabled(false);
            button5.setEnabled(false);
            button6.setEnabled(false);
            button7.setEnabled(false);
            button8.setEnabled(false);
            button9.setEnabled(false);
            buttonUnlock.setEnabled(false);
        } else {
            Toast toast = Toast.makeText(this, "Incorrect Passcode", Toast.LENGTH_SHORT);
            toast.show();
            mPasscode = 0;
            mShowPasscode.setText("");
        }
    }
}