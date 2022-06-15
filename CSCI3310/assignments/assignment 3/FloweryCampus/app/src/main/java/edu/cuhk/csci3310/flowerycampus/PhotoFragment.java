package edu.cuhk.csci3310.flowerycampus;

// Include your personal particular here
// Name: Liu Hoi Pan
// SID: 1155127464

import android.net.Uri;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import java.util.LinkedList;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link PhotoFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class PhotoFragment extends Fragment {

    // Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_ITEM_NUMBER = "item_number";

    // Rename and change types of parameters
    private String itemNumber;
    private static LinkedList<String> mImagePathList;

    public PhotoFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param itemNumber Parameter 1.
     * @return A new instance of fragment PhotoFragment.
     */
    // Rename and change types and number of parameters
    public static PhotoFragment newInstance(String itemNumber, LinkedList<String> imagePathList) {
        PhotoFragment fragment = new PhotoFragment();
        Bundle args = new Bundle();
        args.putString(ARG_ITEM_NUMBER, itemNumber);
        mImagePathList = imagePathList;
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            itemNumber = getArguments().getString(ARG_ITEM_NUMBER);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_photo, container, false);
    }

    // Add other callback methods for View setup as needed

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        int id = Integer.parseInt(itemNumber) + 1;
        ImageView imageView = view.findViewById(R.id.imageView);
        Uri uri = Uri.parse(mImagePathList.get(id));
        imageView.setImageURI(uri);
    }

}