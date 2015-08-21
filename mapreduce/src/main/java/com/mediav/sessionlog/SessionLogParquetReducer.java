package com.mediav.sessionlog;


import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

/**
 * Created by Fan on 15-08-21.
 */

public class SessionLogParquetReducer extends Reducer<IntWritable, LongWritable, Text, LongWritable> {

  enum log_type_count {
    S, T, C, V, OTHER
  }

  @Override
  public void reduce(IntWritable key, Iterable<LongWritable> value, Context context) throws IOException, InterruptedException {
    long outValue = 0;
    for (LongWritable count : value) {
      outValue += count.get();
    }
    String outputKey = null;
    switch ((char)key.get()) {
      case 's':
        context.getCounter(log_type_count.S).increment(outValue);
        outputKey = "s";
        break;
      case 't':
        context.getCounter(log_type_count.T).increment(outValue);
        outputKey = "t";
        break;
      case 'c':
        context.getCounter(log_type_count.C).increment(outValue);
        outputKey = "c";
        break;
      case 'v':
        context.getCounter(log_type_count.V).increment(outValue);
        outputKey = "v";
        break;
      default:
        context.getCounter(log_type_count.OTHER).increment(outValue);
        outputKey = "other";
    }
    context.write(new Text(outputKey), new LongWritable(outValue));
  }
}

