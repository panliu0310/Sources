package edu.cuhk.csci3310.cusweetspot;

// TODO:
// Include your personal particular here
//

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import java.io.File;
import java.util.LinkedList;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    private RecyclerView mRecyclerView;
    private SweetListAdapter mAdapter;
    static LinkedList<String> mImagePathList = new LinkedList<>();
    // TODO:
    // Define other attributes as needed

    //final String mRawFilePath = "android.resource://edu.cuhk.csci3310.cusweetspot/raw/";
    final String mAppFilePath = "/data/data/edu.cuhk.csci3310.cusweetspot/";
    final String mDrawableFilePath = "android.resource://edu.cuhk.csci3310.cusweetspot/drawable/";

    // ... Rest of MainActivity code ...
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Put initial data into the image list.
        if(mImagePathList.isEmpty())
            for (int i = 1; i <= 10; i++) {
                mImagePathList.addLast(mDrawableFilePath + "image" + String.format("%02d",i));
            }

        // Get a handle to the RecyclerView.
        mRecyclerView = findViewById(R.id.recyclerview);
        // Create an adapter and supply the data to be displayed.
        // Currently only an image path list is passed

        // TODO:
        // Update and pass more information as needed
        mAdapter = new SweetListAdapter(this, mImagePathList);

        // Connect the adapter with the RecyclerView.
        mRecyclerView.setAdapter(mAdapter);

        // Give the RecyclerView a default layout manager.
        // TODO:
        // Set up Grid according to the orientation of phone
        mRecyclerView.setLayoutManager(new GridLayoutManager(this, 2));

    }

    // TODO:
    // Add more utility methods as needed

}
