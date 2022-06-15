package edu.cuhk.csci3310.cusweetspot;

// TODO:
// Include your personal particular here
//

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

public class DetailActivity extends AppCompatActivity {
    private static final String TAG = "DetailActivity";
    // TODO:
    // Define other attributes as needed

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        // TODO:
        // 1. Obtain data via Intent
        // 2. Setup Views based on the data received
        // 3. Setup event handler
        // 4. Perform necessary data-persistence steps

    }

    @Override
    protected void onStop() {
        super.onStop();
        // TODO:
        // Perform necessary data-persistence steps

    }


    // TODO:
    // Add more utility methods as needed

}