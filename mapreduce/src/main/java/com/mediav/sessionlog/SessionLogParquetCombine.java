package com.mediav.sessionlog;


import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;

/**
 * Created by Fan on 15-08-21.
 */

public class SessionLogParquetCombine extends Reducer<IntWritable, LongWritable, IntWritable, LongWritable> {

  @Override
  public void reduce(IntWritable key, Iterable<LongWritable> value, Context context) throws IOException, InterruptedException {
    long outValue = 0;
    for (LongWritable count : value) {
      outValue += count.get();
    }
    context.write(key, new LongWritable(outValue));
  }
}

