package com.mediav.sessionlog;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.mapreduce.Mapper;

import com.mediav.data.log.CookieEvent;

/**
 * Created by Fan on 15-08-21.
 */
public class SessionLogParquetMapper extends Mapper<LongWritable, CookieEvent, IntWritable, LongWritable> {
  LongWritable one = new LongWritable(1);

  @Override
  public void map(LongWritable key, CookieEvent value, Context context) throws IOException, InterruptedException {
    if (value != null) {
      if (value.isSetEventType()) {
        context.write(new IntWritable(value.getEventType()), one);
      }
    }
  }
}
