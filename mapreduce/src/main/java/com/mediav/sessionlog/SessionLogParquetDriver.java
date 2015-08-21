package com.mediav.sessionlog;

import com.mediav.data.log.CookieEvent;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

import parquet.hadoop.thrift.ParquetThriftInputFormat;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by Fan on 15-08-21.
 */
public class SessionLogParquetDriver extends Configured implements Tool{

  public int run(String[] args) throws Exception {
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "[etl][Count sessionlog parquet eventType][" + (new SimpleDateFormat("HH:mm").format(new Date())) + "]");
    Path inputParquet = new Path(args[0]);
    Path output = new Path(args[1]);

    job.setJarByClass(SessionLogParquetDriver.class);
    job.setMapOutputKeyClass(IntWritable.class);
    job.setMapOutputValueClass(LongWritable.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(LongWritable.class);

    job.setInputFormatClass(ParquetThriftInputFormat.class);
    ParquetThriftInputFormat.addInputPath(job, inputParquet);
    ParquetThriftInputFormat.setReadSupportClass(job, CookieEvent.class);
    ParquetThriftInputFormat.setThriftClass(job.getConfiguration(), CookieEvent.class);

    job.setMapperClass(SessionLogParquetMapper.class);
    job.setCombinerClass(SessionLogParquetCombine.class);
    job.setReducerClass(SessionLogParquetReducer.class);
    job.setNumReduceTasks(15);

    job.setOutputFormatClass(TextOutputFormat.class);
    FileOutputFormat.setOutputPath(job, output);

    boolean success = job.waitForCompletion(true);
    return success ? 0 : 1;
  }

  public static void main(String[] args) throws Exception {
    if (args.length == 2) {
      int ret = ToolRunner.run(new SessionLogParquetDriver(), args);
      System.exit(ret);
    } else {
      System.out.println("wrong args, the args.length != 3!");
      System.exit(-1);
    }
  }
}

