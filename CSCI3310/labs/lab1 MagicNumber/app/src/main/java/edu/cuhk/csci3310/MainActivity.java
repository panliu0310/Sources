package edu.cuhk.csci3310;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private int mGuessNumber = 1;
    private int guessTime = 0;
    private TextView mShowNumber;
    private Button buttonGuess;
    private Button buttonPlus;
    private Button buttonMinus;

    private int magicNumber = new Random().nextInt(10) + 1;

    private String toast_message;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mShowNumber = (TextView) findViewById(R.id.show_number);
        buttonGuess = (Button) findViewById(R.id.button_guess);
        buttonPlus = (Button) findViewById(R.id.button_plus);
        buttonMinus = (Button) findViewById(R.id.button_minus);
        Log.d("magicNumber", String.valueOf(magicNumber));
    }

    public void showToast(View view) {
        guessTime++;
        if (mGuessNumber == magicNumber){
            toast_message = "Bingo! You made it in " + guessTime + " guess";
            if (guessTime > 1) toast_message += "es";
            disableButton();
        } else if (Math.abs(mGuessNumber - magicNumber) <= 2){
            toast_message = "Close!";
            if (guessTime >= 3){
                toast_message = "Game Over! The magic number is " + magicNumber;
                disableButton();
            }
        } else {
            if (mGuessNumber > magicNumber)
                toast_message = "Too large!";
            else
                toast_message = "Too small!";
            if (guessTime > 3){
                toast_message = "Game Over! The magic number is " + magicNumber;
                disableButton();
            }
        }
        Toast toast = Toast.makeText(this, toast_message, Toast.LENGTH_SHORT);
        toast.show();
    }

    public void countUp(View view) {
        mGuessNumber++;
        if (mShowNumber != null)
            mShowNumber.setText(Integer.toString(mGuessNumber));
    }

    public void countDown(View view) {
        mGuessNumber--;
        if (mShowNumber != null)
            mShowNumber.setText(Integer.toString(mGuessNumber));
    }

    private void disableButton() {
        buttonGuess.setEnabled(false);
        buttonPlus.setEnabled(false);
        buttonMinus.setEnabled(false);
    }
}