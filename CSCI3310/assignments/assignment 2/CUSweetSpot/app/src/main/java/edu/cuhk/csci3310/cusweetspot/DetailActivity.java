package edu.cuhk.csci3310.cusweetspot;

// Include your personal particular here
// Name: Liu Hoi Pan
// SID: 1155127464
// CSCI3310 Assignment 2: CU Sweet Spot
//

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import com.opencsv.CSVReader;
import com.opencsv.CSVWriter;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class DetailActivity extends AppCompatActivity {
    private static final String TAG = "DetailActivity";
    // TODO:
    // Define other attributes as needed
    ImageView mImageView;
    EditText mEditText;
    TextView mTextViewLink;
    TextView mTextViewRating;

    int position;
    // read data from csv
    String[] nextLine;
    String[] imageName = new String[11];
    String[] sweetName = new String[11];
    String[] restaurantName = new String[11];
    int[] rating = new int[11];

    private SharedPreferences mPreferences;
    private String sharedPrefFile = "edu.cuhk.csci3310.cusweetspot";
    private final String SWEETNAME_KEY = "sweetName";
    private final String RATING_KEY = "rating";

    @SuppressLint("LongLogTag")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        mImageView = findViewById(R.id.image_large);
        mEditText = findViewById(R.id.edit_name);
        mTextViewLink = findViewById(R.id.link_cu_map);
        mTextViewRating = findViewById(R.id.value_rating);

        // TODO:
        // 1. Obtain data via Intent
        // 2. Setup Views based on the data received
        // 3. Setup event handler
        // 4. Perform necessary data-persistence steps

        // 1. Obtain position
        Intent intent = getIntent();
        position = intent.getIntExtra("position", -1);
        position++;
        // read data from csv
        try {
            CSVReader reader = new CSVReader(new InputStreamReader(getResources().openRawResource(R.raw.cu_sweeties)));
            int counter = 0;
            while ((nextLine = reader.readNext()) != null) {
                // nextLine[] is an array of values from the line
                imageName[counter] = nextLine[0];
                sweetName[counter] = nextLine[1];
                restaurantName[counter] = nextLine[2];
                counter++;
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        // get data in shared preference
        mPreferences = getSharedPreferences(sharedPrefFile, MODE_PRIVATE);
        sweetName[position] = mPreferences.getString(SWEETNAME_KEY+position, sweetName[position]);
        rating[position] = mPreferences.getInt(RATING_KEY+position, 3);

        // 2. Setup Views
        // set image
        Context c = getApplicationContext();
        String s = imageName[position]; // need to remove .jpg in order to make getIdentifier() work
        int imageId = c.getResources().getIdentifier("drawable/"+s.substring(0, s.length() - 4), null, c.getPackageName());
        mImageView.setImageResource(imageId);

        mEditText.setText(sweetName[position]);

        mTextViewLink.setText(restaurantName[position]);
        // 3. Event handler
        mTextViewLink.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent impIntent = new Intent(Intent.ACTION_VIEW);
                impIntent.setData(Uri.parse("https://www.openrice.com/en/hongkong/restaurants?what="+restaurantName[position]));
                startActivity(impIntent);
            }
        });

        mTextViewRating.setText(String.format("%s", rating[position]));

    }

    @Override
    protected void onStop() {
        super.onStop();
        // TODO:
        // Perform necessary data-persistence steps
        SharedPreferences.Editor preferencesEditor = mPreferences.edit();
        preferencesEditor.putString(SWEETNAME_KEY+position, mEditText.getText().toString());
        preferencesEditor.putInt(RATING_KEY+position, Integer.parseInt(mTextViewRating.getText().toString()));
        preferencesEditor.apply();
    }

    // TODO:
    // Add more utility methods as needed
    @SuppressLint("SetTextI18n")
    public void plusRating(View view) {
        int rating = Integer.parseInt(mTextViewRating.getText().toString());
        if (rating < 5)
            rating++;
        mTextViewRating.setText(Integer.toString(rating));
    }

    @SuppressLint("SetTextI18n")
    public void minusRating(View view) {
        int rating = Integer.parseInt(mTextViewRating.getText().toString());
        if (rating > 1)
            rating--;
        mTextViewRating.setText(Integer.toString(rating));
    }
}