package edu.cuhk.csci3310.cueat;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private String mDetailsMessage;
    public static final String EXTRA_MESSAGE =
            "edu.cuhk.csci3310.cueat.extra.MESSAGE";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ImageView imageKebab = (ImageView) findViewById(R.id.kebab);
        ImageView imagePizza = (ImageView) findViewById(R.id.pizza);

        imageKebab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mDetailsMessage = getString(R.string.kebab_details_message);
                showKebabDetails(v);
                Intent intent = new Intent(MainActivity.this, DetailedViewActivity.class);
                intent.putExtra(EXTRA_MESSAGE, mDetailsMessage);
                startActivity(intent);
            }
        });
        imagePizza.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                mDetailsMessage = getString(R.string.pizza_details_message);
                showPizzaDetails(v);
                Intent intent = new Intent(MainActivity.this, DetailedViewActivity.class);
                intent.putExtra(EXTRA_MESSAGE, mDetailsMessage);
                startActivity(intent);
            }
        });

    }

    public void displayToast(String message) {
        Toast.makeText(getApplicationContext(), message, Toast.LENGTH_SHORT).show();
    }

    /**
     Shows a message that the kebab image was clicked.
     */
    public void showKebabDetails (View view) {
        displayToast(getString(R.string.kebab_details_message));
    }

    /**
     Shows a message that the pizza image was clicked.
     */
    public void showPizzaDetails(View view) {
        displayToast(getString(R.string.pizza_details_message));
    }
}