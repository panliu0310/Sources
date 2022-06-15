package edu.cuhk.csci3310.cusweetspot;

// TODO:
// Include your personal particular here
//

import android.content.Context;
import android.net.Uri;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RatingBar;
import android.widget.TextView;

import java.util.LinkedList;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.RecyclerView.Adapter;

public class SweetListAdapter extends Adapter<SweetListAdapter.SweetViewHolder>  {
    private static final String TAG = "SweetListAdapter";
    private Context context;
    private LayoutInflater mInflater;

    private LinkedList<String> mImagePathList;

    // the following pre-set res image path is for debugging, but good to let students to start with
    private String mDrawableFilePath = "android.resource://edu.cuhk.csci3310.cusweetspot/drawable/";

    class SweetViewHolder extends RecyclerView.ViewHolder {

        public ImageView imageItemView;
        public TextView nameTextView, locTextView, wikiTextView;
        public RatingBar flowerRichnessBar;
        final SweetListAdapter mAdapter;

        public SweetViewHolder(View itemView, SweetListAdapter adapter) {
            super(itemView);
            imageItemView = itemView.findViewById(R.id.image);
            this.mAdapter = adapter;

            // TODO:
            // Add event handler for image to transit to another DetailActivity

        }
    }

    public SweetListAdapter(Context context,
                            LinkedList<String> imagePathList) {
        mInflater = LayoutInflater.from(context);
        this.mImagePathList = imagePathList;
    }

    // TODO:
    // Update the following callback methods as needed
    //
    @NonNull
    @Override
    public SweetViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View mItemView = mInflater.inflate(R.layout.imagelist_item, parent, false);
        return new SweetViewHolder(mItemView, this);
    }

    @Override
    public void onBindViewHolder(@NonNull SweetViewHolder holder, int position) {
        String mImagePath = mImagePathList.get(position);
        Uri uri = Uri.parse(mImagePath);
        holder.imageItemView.setImageURI(uri);
    }

    public long getItemId(int position) {
        return position;
    }

    @Override
    public int getItemCount() {
        return mImagePathList.size();
    }

    public void updateData(LinkedList<String> imagePathList) {
        this.mImagePathList = imagePathList;
        // Notify the adapter, that the data has changed so it can
        // update the RecyclerView to display the data.
        notifyDataSetChanged();
    }
}