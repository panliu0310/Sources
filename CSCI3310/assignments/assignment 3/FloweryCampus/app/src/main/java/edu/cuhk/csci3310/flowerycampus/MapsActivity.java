package edu.cuhk.csci3310.flowerycampus;

// Include your personal particular here
// Name: Liu Hoi Pan
// SID: 1155127464

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.LatLngBounds;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import com.opencsv.CSVReader;

import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Locale;
import java.util.Stack;

public class MapsActivity extends AppCompatActivity implements OnMapReadyCallback {

    private static final String TAG = "FloweryCampus";
    private GoogleMap mMap;

    // TODO: Define other attributes as needed
    // read data from csv
    String[] nextLine;
    String[] imageName = new String[10];
    String[] flowerName = new String[10];
    String[] latitude = new String[10];
    String[] longitude = new String[10];

    private final LinkedList<String> mImagePathList = new LinkedList<>();
    private String mDrawaleFilePath = "android.resource://edu.cuhk.csci3310.flowerycampus/drawable/";

    // define markers
    Marker[] markers = new Marker[10];

    // define backStack
    Stack<String> backStackId = new Stack<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);

        // read CSV
        readCSV();

        // By default map fragment is added statically via the SupportMapFragment obtained
        // and get notified when the map is ready to be used.
        //
        // Modify the following code to include mapFragment and other fragments dynamically
        // add mapFragment statically: SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.map);
        // add fragment dynamically
        SupportMapFragment mapFragment = SupportMapFragment.newInstance();
        getSupportFragmentManager()
                .beginTransaction()
                .add(R.id.map, mapFragment)
                .commit();
        mapFragment.getMapAsync(this);

    }


    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */
    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        // By default a marker in SHB of CUHK is added and move the camera
        //
        // Modify the following code to
        // 1. read flowery locations from a CSV,
        // 2. set up markers, view bounds and zoom
        // 3. add listeners to handle different map clicking events
        // 4. include extra data structure to handle non-system "Back-pressing" states
        //
        LatLng cuhk_shb = new LatLng(22.418014,	114.207259);
        mMap.moveCamera(CameraUpdateFactory.newLatLng(cuhk_shb));
        mMap.animateCamera(CameraUpdateFactory.zoomTo(16));

        // Create a LatLngBounds
        LatLngBounds CUBounds = new LatLngBounds(
                new LatLng(22.414, 114.202), // SW bounds
                new LatLng(22.427, 114.210)  // NE bounds
        );
        // Constrain the camera target to the bounds
        mMap.setLatLngBoundsForCameraTarget(CUBounds);

        setFlowerTagOnMap(mMap);

        // 3. add listeners to handle different map clicking events
        mMap.setOnMarkerClickListener(new GoogleMap.OnMarkerClickListener() {
            @SuppressLint("LongLogTag")
            @Override
            public boolean onMarkerClick(Marker marker) {
                resetMarkerColor();
                marker.setIcon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_RED));
                mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(marker.getPosition(), 19));
                addPhotoFragment(marker.getId().substring(1));
                backStackId.push(marker.getId().substring(1));
                return false;
            }
        });

        mMap.setOnMapClickListener(new GoogleMap.OnMapClickListener() {
            @Override
            public void onMapClick(LatLng latLng) {
                Log.d("latitude", String.valueOf(latLng.latitude));
                Log.d("longitude", String.valueOf(latLng.longitude));
                resetMarkerColor();
                mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(latLng, 16));
                backStackId.clear();
                removeAllPhotoFragment();
            }
        });

    }

    /**
     * Include customized handling on pressing Back button
     * This callback is triggered when the Back is pressed.
     * This is where we can include extra BackStack handling not done by system by default
     * e.g. markers status etc.
     */
    // 4. include extra data structure to handle non-system "Back-pressing" states
    @Override
    public void onBackPressed() {
        super.onBackPressed();
        //
        // include addition BackStack handling, e.g. for markers, here
        //
        if (backStackId.size() > 1){
            // if the back stack store more than 1 fragment
            backStackId.pop(); // remove the top element in stack
            int id = Integer.parseInt(backStackId.pop()) + 1; // get the previous element in stack
            backStackId.push(String.valueOf(id)); // push the present fragment to stack
            resetMarkerColor();
            markers[id].setIcon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_RED));
            mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(markers[id].getPosition(), 19));
            markers[id].showInfoWindow();
        } else if (backStackId.size() == 1) {
            // go back to default marker in SHB of CUHK
            resetMarkerColor(); hideInfoWindows();
            mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(new LatLng(22.418014,	114.207259), 16));
        }

    }

    // Add more utility methods
    // 1. read flowery locations from a CSV
    private void readCSV() {
        // read data from csv
        try {
            CSVReader reader = new CSVReader(new InputStreamReader(getResources().openRawResource(R.raw.cu_flowers)));
            int counter = 0;
            while ((nextLine = reader.readNext()) != null) {
                // nextLine[] is an array of values from the line
                imageName[counter] = nextLine[0].substring(0, nextLine[0].length() - 4);
                mImagePathList.addLast(mDrawaleFilePath + imageName[counter]);
                flowerName[counter] = nextLine[1];
                latitude[counter] = nextLine[2];
                longitude[counter] = nextLine[3];
                counter++;
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // 2. set up markers
    private void setFlowerTagOnMap(final GoogleMap map) {
        for (int i = 1; i < 10; i++){
            String snippet = String.format(Locale.getDefault(),
                    "Lat: %1$.5s, Long: %2$.5s",
                    latitude[i],
                    longitude[i]);
            markers[i] = map.addMarker(new MarkerOptions()
                    .position(new LatLng(Double.parseDouble(latitude[i]), Double.parseDouble(longitude[i])))
                    .title(flowerName[i])
                    .snippet(snippet)
                    .icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_CYAN)));
        }
    }

    // 3. handling events
    private void addPhotoFragment(String id) {
        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();

        PhotoFragment newPhotoFragment = PhotoFragment.newInstance(id, mImagePathList);

        fragmentTransaction.add(R.id.photo, newPhotoFragment).addToBackStack(null).commit();
    }

    private void removeAllPhotoFragment() {
        FragmentManager fragmentManager = getSupportFragmentManager();
        for (int i = 0; i < 10; i++){
            fragmentManager.popBackStack();
        }
    }

    private void resetMarkerColor() {
        for (int i = 1; i < 10; i++){
            markers[i].setIcon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_CYAN));
        }
    }

    private void hideInfoWindows() {
        for (int i = 1; i < 10; i++){
            markers[i].hideInfoWindow();
        }
    }
}
