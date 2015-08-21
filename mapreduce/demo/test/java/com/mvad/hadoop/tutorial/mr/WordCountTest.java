package com.mvad.hadoop.tutorial.mr;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mrunit.mapreduce.MapDriver;
import org.apache.hadoop.mrunit.mapreduce.MapReduceDriver;
import org.apache.hadoop.mrunit.mapreduce.ReduceDriver;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by guangbin on 15-1-20.
 */
public class WordCountTest {
  MapDriver<LongWritable, Text, Text, IntWritable> mapDriver;
  ReduceDriver<Text, IntWritable, Text, IntWritable> reduceDriver;
  MapReduceDriver<LongWritable, Text, Text, IntWritable, Text, IntWritable> mapReduceDriver;

  @Before
  public void setUp() {
    WordCount.TokenizerMapper mapper = new WordCount.TokenizerMapper();
    WordCount.IntSumReducer reducer = new WordCount.IntSumReducer();
    mapDriver = MapDriver.newMapDriver(mapper);
    reduceDriver = ReduceDriver.newReduceDriver(reducer);
    mapReduceDriver = MapReduceDriver.newMapReduceDriver(mapper, reducer);
  }

  @Test
  public void testMapper() throws IOException {
    mapDriver.withInput(new LongWritable(), new Text(
            "Dear Bear River"));
    mapDriver.addOutput(new Text("Dear"), new IntWritable(1));
    mapDriver.addOutput(new Text("Bear"), new IntWritable(1));
    mapDriver.addOutput(new Text("River"), new IntWritable(1));
    mapDriver.runTest();
  }

  @Test
  public void testReducer() throws IOException {
    List<IntWritable> values = new ArrayList<IntWritable>();
    values.add(new IntWritable(1));
    values.add(new IntWritable(1));
    reduceDriver.withInput(new Text("Bear"), values);
    reduceDriver.withOutput(new Text("Bear"), new IntWritable(2));
    reduceDriver.runTest();
  }

  @Test
  public void testMapReduce() throws IOException {
    mapReduceDriver.addInput(new LongWritable(), new Text(
            "Dear Bear River"));
    mapReduceDriver.addInput(new LongWritable(), new Text(
            "Car Car River"));
    mapReduceDriver.addInput(new LongWritable(), new Text(
            "Dear Car Bear"));
    mapReduceDriver.addOutput(new Text("Bear"), new IntWritable(2));
    mapReduceDriver.addOutput(new Text("Car"), new IntWritable(3));
    mapReduceDriver.addOutput(new Text("Dear"), new IntWritable(2));
    mapReduceDriver.addOutput(new Text("River"), new IntWritable(2));

    mapReduceDriver.runTest();
  }
}