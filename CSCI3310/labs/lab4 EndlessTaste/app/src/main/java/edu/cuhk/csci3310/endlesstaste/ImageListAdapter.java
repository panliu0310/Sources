package edu.cuhk.csci3310.endlesstaste;

import android.content.Context;
import android.net.Uri;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.LinkedList;

public class ImageListAdapter extends
        RecyclerView.Adapter<ImageListAdapter.ImageViewHolder> {

    private LayoutInflater mInflater;
    private final LinkedList<String> mImagePathList;

    public ImageListAdapter(Context context,
                            LinkedList<String> imagePathList) {
        mInflater = LayoutInflater.from(context);
        this.mImagePathList = imagePathList;
    }

    class ImageViewHolder extends RecyclerView.ViewHolder {
        public final ImageView imageItemView;
        final ImageListAdapter mAdapter;

        public ImageViewHolder(View itemView, ImageListAdapter adapter)  {
            super(itemView);
            imageItemView = itemView.findViewById(R.id.image);
            this.mAdapter = adapter;
        }
    }

    @NonNull
    @Override
    public ImageListAdapter.ImageViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View mItemView = mInflater.inflate(R.layout.imagelist_item, parent, false);
        return new ImageViewHolder(mItemView, this);
    }

    @Override
    public void onBindViewHolder(@NonNull ImageListAdapter.ImageViewHolder holder, int position) {
        String mImagePath = mImagePathList.get(position);
        Uri uri = Uri.parse(mImagePath);
        holder.imageItemView.setImageURI(uri);
    }

    @Override
    public int getItemCount() {
        return mImagePathList.size();
    }
}
